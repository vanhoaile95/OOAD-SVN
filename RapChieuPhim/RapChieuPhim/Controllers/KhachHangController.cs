using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using BusinessTier;

namespace RapChieuPhim.Controllers
{
    public class KhachHangController : Controller
    {
        //
        // GET: /KhanhHang/
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        KhachHangBS KhachHang = new KhachHangBS();
        public ActionResult Index(int Page = 1, int PageSize = 10)
        {
            var list = KhachHang.SelectAll_KhachHang(Page, PageSize);
            return View(list);
        }

        [HttpPost]
        [ActionName("Detail")]
        public ActionResult DetailPost(KHACHHANG kh,string MAKH)
        {
            try
            {
                new KhachHangBS().UpdateKhachHang(kh, MAKH);
            }
            catch
            {

            }
            return View(GetKhachHang(MAKH));
        }
        public ActionResult Detail(string MAKH)
        {
            return View(GetKhachHang(MAKH));
        }

        public ActionResult InsertKhachHang(KHACHHANG kh,string MAKH)
        {
            return View(GetNextKhachHang());
        }
        [HttpPost]
        [ActionName("InsertKhachHang")]
        public ActionResult InsertKhachHangPost(KHACHHANG kh,string MAKH)
        {
            try
            {

                var listloaikh = (from a in db.LOAIKHs
                                  select new
                                  {
                                      MALOAI = a.MALOAI,
                                      DIEM = a.DIEM,
                                  }).ToList();

                kh.MALOAI = listloaikh[0].MALOAI;
                kh.DIEMTICHLUY = 0;
                new KhachHangBS().InsertKhachHang(kh);
            }
            catch
            {

            }
            return View(GetKhachHang(MAKH));
        }


        public KHACHHANG GetKhachHang(string MAKH)
        {
            var kh = db.KHACHHANGs.SingleOrDefault(makh => makh.MAKH == MAKH);
            return kh;
        }

        public KHACHHANG GetNextKhachHang()
        {
            // Get KhachHang

            var list = from a in db.KHACHHANGs
            select new
            {
                MAKH = a.MAKH,
                MALOAI = a.MALOAI,
                DIEMTICHLUY = a.DIEMTICHLUY,
                HOTEN = a.HOTEN,
                NGAYSINH = a.NGAYSINH,
                NGAYDK = a.NGAYDK,
                CMND = a.CMND,
                SDT = a.SDT,
                DIACHI = a.DIACHI,
                LOAIKH = a.LOAIKH,
            };

            //Lấy mã khách hàng tiếp
            int index = 0;
            int.TryParse(list.ToList()[list.Count() - 1].MAKH.Replace("KH",""),out index);
            index++;
            string makh = index.ToString();
            for (int i = makh.Count(); i < 3; i++)
            {
                makh = "0" + makh;
            }
            makh = "KH" + makh;
            //Loại Khách Hàng 
            var listloaikh = (from a in db.LOAIKHs
            select new
            {
                MALOAI = a.MALOAI,
                DIEM = a.DIEM,
            }).ToList();

            KHACHHANG kh = new KHACHHANG();
            kh.MAKH = makh;
            kh.MALOAI = listloaikh[0].MALOAI;
            kh.DIEMTICHLUY = 0;
            kh.HOTEN = "";
            kh.NGAYSINH = DateTime.Today;
            kh.NGAYDK = DateTime.Today;
            kh.CMND = "";
            kh.SDT = "";
            kh.DIACHI = "";
            return kh;
        }
    }
}
