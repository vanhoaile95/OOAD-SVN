using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using BusinessTier;
using PagedList;
using System.IO;
using CrystalDecisions.CrystalReports.Engine;
using CrystalDecisions.Shared; // sử dung để phân trang

namespace RapChieuPhim.Controllers
{
    public class BanVeController : Controller
    {
        //
        // GET: /BanVe/
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        BanVeBS BanVe = new BanVeBS();
        public string DataGheChon = ""; // khai bao toàn cục

        [HttpGet]
        public ActionResult Index(int Page = 1, int PageSize = 10)
        {
            BanVe.UpdateAllLichChieu();

            DateTime Time = DateTime.Now.Date; // lấy ngày hôm nay

            if (BanVe.TestLichChieu(Time.ToString()) == true)// hôm nay có lịch chiếu
            {
                var list = BanVe.getAll_LichChieu(Page, PageSize, Time); // lấy các lịch chiếu hôm nay
                return View(list);
            }
            else // hôm nay ko có lịch chiếu
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }

            // hàm phân trang ko chấp nhận dữ liệu bị chuyển thành .ToList(), mà tất cả phải chuyển qua kiêu IEnumrable
            // Page : mặc định trang đầu tiên là 1
            // PageSize : là số phần tử trong 1 trang
        }

        [HttpPost]
        public ActionResult Index(FormCollection f, int Page = 1, int PageSize = 10)
        {
            string TimeClick = f["theDate"].ToString();

            if (BanVe.TestLichChieu(TimeClick) == true)// hôm nay có lịch chiếu
            {
                DateTime Time = Convert.ToDateTime(TimeClick);
                var list = BanVe.getAll_LichChieu(Page, PageSize, Time); // lấy các lịch chiếu hôm nay
                return View(list);
            }
            else // hôm nay ko có lịch chiếu
            {
                ViewBag.ThongBao = "NoData";
                return View();
            }

        }


        [HttpGet]
        public ActionResult LoadGhe(string MaLichChieu)
        {
            if (BanVe.CheckStatusLichChieu(MaLichChieu) == true)
            {
                var list = BanVe.getInfo_LichChieu(MaLichChieu);
                return View(list.ToList());
            }
            else
            {
                ViewBag.ThongBao = "Đã chiếu";
                return View();
            }
        }

        [HttpPost]// Thanh Toán
        public ActionResult LoadGhe(FormCollection f)
        {
            // f lấy value của các thẻ có name tương ứng => f["name"].ToString();
            this.DataGheChon = f["gheChon"].ToString();
            string[] listGheChon = this.DataGheChon.Split(new char[] { ',' }); // danh sách các ghế được chọn

            string listMaVe = ""; //copy

            var user = Session["User"] as NHANVIEN; // lấy thông tin User hiện tại đang đăng nhập

            VE temp_Ve = new VE();

            for (int i = 0; i < listGheChon.Length; i++)
            {
                temp_Ve = new VE();
                temp_Ve.MAVE = BanVe.getNextMAVE(); // tạo mã vé tiếp theo
                temp_Ve.NGAYBAN = DateTime.Now;
                temp_Ve.MAKH = f["tbMaKH"].ToString(); // Mã KH mua vé
                temp_Ve.MALICHCHIEU = f["tbMaLichChieu"].ToString(); // thông tin của lịch chiếu đang bán vé
                temp_Ve.MANVBAN = user.MANV;
                temp_Ve.STTGHE = Convert.ToInt32(listGheChon[i].ToString());
                temp_Ve.GIAVE = Convert.ToInt32(BanVe.getGiaVe());
                temp_Ve.TINHTRANG = "CHUAIN"; // chưa in vé

                listMaVe += temp_Ve.MAVE + ","; // copy lại các Mã Vé

                db.VEs.Add(temp_Ve); // lưu vào bảng tạm
                db.SaveChanges(); // lưu xuống database

            }

            // Cộng điểm KH
            string MaKH = f["tbMaKH"].ToString();

            if (MaKH.CompareTo("") != 0)// có nhập MaKH
            {
                string Diem = f["txtTongTien"].ToString();
                for (int i = 0; i < Diem.Length; i++)
                {
                    if (Diem[i].CompareTo(',') == 0)
                    {
                        Diem = Diem.Remove(i, 1);
                        i--;
                    }
                }


                KHACHHANG kh = new KHACHHANG();
                kh = db.KHACHHANGs.SingleOrDefault(x => x.MAKH == MaKH);
                kh.DIEMTICHLUY += Convert.ToInt32(Diem.ToString());
                db.SaveChanges();
            }

            return new RedirectResult(Url.Action("InVe", "BanVe", new { DataMaVe = listMaVe, DataGheChon = f["gheChon"].ToString() }));
        }


        public ActionResult InVe(string DataMaVe, string DataGheChon)
        {
            string[] listGheChon = DataGheChon.Split(new char[] { ',' });
            string[] listMaVe = DataMaVe.Split(new char[] { ',' });

            List<ReportVE> list = new List<ReportVE>();
            ReportVE temp = new ReportVE();
            for (int i = 0; i < listGheChon.Length; i++)
            {
                if (BanVe.IsInVe(listMaVe[i].ToString()) == false) // Vé này chưa có In
                {
                    temp = new ReportVE();
                    temp.MAVE = listMaVe[i].ToString();
                    temp.STTGHE = Convert.ToInt32(listGheChon[i].ToString());
                    list.Add(temp);
                }
            }

            return View(list.ToList());
        }


        public ActionResult Export_Ve(string MaVe)
        {

            // Cập nhật lại là Vé đã IN
            VE temp = db.VEs.SingleOrDefault(x => x.MAVE == MaVe);
            temp.TINHTRANG = "DAIN"; // Vé đã được IN
            db.SaveChanges();
            //---------------------------------------------

            List<ReportVE> list = BanVe.getInfo_Ve(MaVe);

            ReportDocument rd = new ReportDocument();
            rd.Load(Path.Combine(Server.MapPath("~/Report/CrystalReportVe.rpt")));
            rd.SetDataSource(db.VEs);

            foreach (var item in list)
            {
                string TenPhim = item.TENPHIM.ToString();

                if (TenPhim.Length > 20)
                {
                    TenPhim = TenPhim.Substring(0, 19) + "...";
                }

                SetCurrentValuesForParameterField(rd, "MaVe", item.MAVE.ToString());
                SetCurrentValuesForParameterField(rd, "TenPhim", TenPhim);
                SetCurrentValuesForParameterField(rd, "NgayChieu", string.Format("{0:dd/MM/yyyy}", item.NGAYCHIEU));
                SetCurrentValuesForParameterField(rd, "GioChieu", item.GIOBATDAU.ToString());
                SetCurrentValuesForParameterField(rd, "GiaVe", string.Format("{0:#,000 VNĐ}", item.GIAVE));
                SetCurrentValuesForParameterField(rd, "SoGhe", item.STTGHE.ToString());
                SetCurrentValuesForParameterField(rd, "NgayBan", string.Format("{0:dd/MM/yyyy}", item.NGAYBAN));
                SetCurrentValuesForParameterField(rd, "PhongChieu", item.TENPHONGCHIEU.ToString());
                SetCurrentValuesForParameterField(rd, "MaNVBAN", item.MANVBAN.ToString());
                SetCurrentValuesForParameterField(rd, "PhienBan", item.PHIENBAN.ToString());
            }

            Response.Buffer = false;
            Response.ClearHeaders();
            Response.ClearContent();

            try
            {
                Stream stream = rd.ExportToStream
                    (CrystalDecisions.Shared.ExportFormatType.PortableDocFormat);
                stream.Seek(0, SeekOrigin.Begin);
                return File(stream, "application/pdf", "Ve.pdf");
            }
            catch (Exception e)
            {
                throw;
            }

        }

        public void SetCurrentValuesForParameterField(ReportDocument reportDocument, string paramFieldName, string value)
        {
            ParameterDiscreteValue parameterDiscreteValue = new ParameterDiscreteValue();
            parameterDiscreteValue.Value = value;

            ParameterValues currentParameterValues = new ParameterValues();
            currentParameterValues.Add(parameterDiscreteValue);

            reportDocument.DataDefinition.ParameterFields[paramFieldName].ApplyCurrentValues(currentParameterValues);
        }



    }
}
