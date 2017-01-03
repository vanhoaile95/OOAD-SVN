using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using PagedList;
using BusinessTier;

namespace RapChieuPhim.Controllers
{
    public class BaoCaoController : Controller
    {
        //
        // GET: /BaoCao/

        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        BanVeBS BanVe = new BanVeBS();
        BaoCaoBS BaoCao = new BaoCaoBS();

        //-------------Thống kê theo ngày chiếu ----------------------------
        [HttpGet]
        public ActionResult Index(int Page = 1, int PageSize = 10)
        {

            DateTime Time = DateTime.Now.Date; // lấy ngày hôm nay

            if (BanVe.TestAllLichChieu(Time.ToString()) == true)// hôm nay có lịch chiếu
            {

                IEnumerable<BanVeJoinTable> IE_BC;
                List<BanVeJoinTable> listBC = new List<BanVeJoinTable>();

                listBC = BaoCao.TK_NgayChieu(Time);
                IE_BC = (IEnumerable<BanVeJoinTable>)listBC.OrderByDescending(x => x.SL_VE).ToPagedList(Page, PageSize);
                return View(IE_BC);
            }
            else // hôm nay ko có lịch chiếu
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }
        }


        [HttpPost]
        public ActionResult Index(FormCollection f, int Page = 1, int PageSize = 10)
        {

            DateTime Time = Convert.ToDateTime(f["thedate"].ToString()); // lấy ngày hôm nay

            if (BanVe.TestAllLichChieu(f["thedate"].ToString()) == true)// hôm nay có lịch chiếu
            {
                IEnumerable<BanVeJoinTable> IE_BC;
                List<BanVeJoinTable> listBC = new List<BanVeJoinTable>();

                listBC = BaoCao.TK_NgayChieu(Time);
                IE_BC = (IEnumerable<BanVeJoinTable>)listBC.OrderByDescending(x => x.SL_VE).ToPagedList(Page, PageSize);
                return View(IE_BC);
            }
            else // hôm nay ko có lịch chiếu
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }
        }



        //------------------------------------------------------------------------

        ///----------------Thống kê theo nhân viên bán vé -------------------------

        [HttpGet]
        public ActionResult TK_NhanVien(int Page = 1, int PageSize = 10)
        {
            DateTime Time = DateTime.Now.Date;

            var listNV = from a in db.VEs
                         where a.NGAYBAN.Day == Time.Day && a.NGAYBAN.Month == Time.Month && a.NGAYBAN.Year == Time.Year
                         group a by a.MANVBAN into list
                         select new
                         {
                             MANV = list.Key,
                             SL_VeBAN = list.Count(),
                             THANHTIEN = list.Sum(x => x.GIAVE),
                         };

            if (listNV != null)
            {

                IEnumerable<BanVeJoinTable> IE_BaoCao;
                List<BanVeJoinTable> listBaoCao = new List<BanVeJoinTable>();

                listBaoCao = BaoCao.TK_NhanVien(Time);
                IE_BaoCao = (IEnumerable<BanVeJoinTable>)listBaoCao.OrderBy(x => x.MANVBAN).ToPagedList(Page, PageSize);

                return View(IE_BaoCao);
            }
            else
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }
        }


        [HttpPost]
        public ActionResult TK_NhanVien(FormCollection f, int Page = 1, int PageSize = 10)
        {
            DateTime Time = Convert.ToDateTime(f["thedate"].ToString());

            var listNV = from a in db.VEs
                         where a.NGAYBAN.Day == Time.Day && a.NGAYBAN.Month == Time.Month && a.NGAYBAN.Year == Time.Year
                         group a by a.MANVBAN into list
                         select new
                         {
                             MANV = list.Key,
                             SL_VeBAN = list.Count(),
                             THANHTIEN = list.Sum(x => x.GIAVE),
                         };

            if (listNV.ToList().Count() > 0)
            {
                List<BanVeJoinTable> listBaoCao = new List<BanVeJoinTable>();
                IEnumerable<BanVeJoinTable> IE_BaoCao;

                listBaoCao = BaoCao.TK_NhanVien(Time);
                IE_BaoCao = (IEnumerable<BanVeJoinTable>)listBaoCao.OrderBy(x => x.MANVBAN).ToPagedList(Page, PageSize);

                return View(IE_BaoCao);
            }
            else
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }
        }

        //-------------------------------------------------------------------------

        ///--------------Thống kê theo phim ---------------------------------------
        public ActionResult TK_Phim(int Page = 1, int PageSize = 10)
        {
            var listSLVe = from a in db.VEs // group các vé lại tính SL Vé, Thành tiền.
                           group a by a.MALICHCHIEU into SL // 1 Mã lịch chiếu có thể bán vé nhiều ngày, nên ko thể lọc theo ngày
                           select new
                           {
                               MALICHCHIEU = SL.Key,
                               SL_VE = SL.Count(),
                               THANHTIEN = SL.Sum(a => a.GIAVE),
                           };

            var listLC = from a in db.LICHCHIEUx // lấy các lịch chiếu hôm nay
                         join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                         select new
                         {
                             MALICHCHIEU = a.MALICHCHIEU,
                             TENPHIM = b.TENPHIM,
                             PHIENBAN = a.PHIENBAN,
                         };

            List<BanVeJoinTable> listBaoCaotemp = new List<BanVeJoinTable>();
            BanVeJoinTable temp = new BanVeJoinTable();
            bool Check = false;

            foreach (var item in listLC)
            {
                Check = false;

                foreach (var item1 in listSLVe)
                {
                    if (item.MALICHCHIEU == item1.MALICHCHIEU)
                    {
                        temp = new BanVeJoinTable();
                        temp.MALICHCHIEU = item.MALICHCHIEU;
                        temp.TENPHIM = item.TENPHIM;
                        temp.PHIENBAN = item.PHIENBAN;
                        temp.SL_VE = item1.SL_VE;
                        temp.THANHTIEN = item1.THANHTIEN;

                        listBaoCaotemp.Add(temp);
                        Check = true;
                        break;
                    }
                }

                if (Check == false)
                {
                    temp = new BanVeJoinTable();
                    temp.MALICHCHIEU = item.MALICHCHIEU;
                    temp.TENPHIM = item.TENPHIM;
                    temp.PHIENBAN = item.PHIENBAN;
                    temp.SL_VE = 0;
                    temp.THANHTIEN = 0;

                    listBaoCaotemp.Add(temp);
                }
            }

            int count, length;

            IEnumerable<BanVeJoinTable> IE_BaoCao;
            List<BanVeJoinTable> listBaoCao = new List<BanVeJoinTable>();

            foreach (var item in listBaoCaotemp)
            {
                count = 0;
                length = 0;

                if (listBaoCao == null)
                {
                    listBaoCao.Add(item);
                }
                else
                    if (listBaoCao != null)
                    {
                        foreach (var item1 in listBaoCao)
                        {
                            length++;
                            if (item.TENPHIM != item1.TENPHIM || item.PHIENBAN != item1.PHIENBAN)
                            {
                                count++;
                            }
                            else
                            {
                                item1.SL_VE += item.SL_VE;
                                item1.THANHTIEN += item.THANHTIEN;
                            }
                        }

                        if (length == count)
                        {
                            listBaoCao.Add(item);
                        }
                    }
            }

            IE_BaoCao = (IEnumerable<BanVeJoinTable>)listBaoCao.OrderBy(x => x.TENPHIM).ToPagedList(Page, PageSize);
            return View(IE_BaoCao);
        }

    }
}
