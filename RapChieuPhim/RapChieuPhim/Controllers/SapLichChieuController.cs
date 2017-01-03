using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using BusinessTier;
namespace RapChieuPhim.Controllers
{
    public class SapLichChieuController : Controller
    {
        //
        // GET: /SapLichChieu/
        QuanLyCinemaEntities db = null;
        [HttpGet]
        public ActionResult Index(string PhongChieu,DateTime? NgayChieu,string TinhTrang,string Error,string Duyet)
        {
            db = new QuanLyCinemaEntities();
            

           
            ViewBag.TenPhim = db.PHIMs.ToList(); // List Phim
            
         
            //Combobox Tình trạng
            if (TinhTrang == null)
            { TinhTrang = "Chờ duyệt"; }
            ViewBag.TinhTrang = new List<string> { "Chờ duyệt", "Chưa chiếu" }; 
            ViewBag.TinhTrangDaChon = TinhTrang;

            //Combobox Phòng chiếu
            if (PhongChieu == null) //Set giá trị đầu tiên trong lần load lần tiên
            { PhongChieu = db.PHONGCHIEUx.First().MAPHONGCHIEU; }
            ViewBag.PhongChieu = db.PHONGCHIEUx.ToList(); // List phòng chiếu
            ViewBag.PhongChieuDaChon = PhongChieu;

            //Input Ngày chiếu
            if (NgayChieu == null)
            {NgayChieu = DateTime.Parse(DateTime.Now.ToString("yyyy-MM-dd"));}
            ViewBag.NgayChieu = NgayChieu;
          


            //Load Table Lịch chiếu
               List<LICHCHIEU> LichChieu = db.LICHCHIEUx.SqlQuery(
                @"select * from LICHCHIEU where NGAYCHIEU ='" 
                + NgayChieu.Value.Year + "-" 
                + NgayChieu.Value.Month + "-"
                + NgayChieu.Value.Day + "' and TINHTRANG = N'" + TinhTrang + "'and MAPHONGCHIEU = '"+ PhongChieu + "' order by cast(LEFT(GIOBATDAU,LEN(GIOBATDAU) - 3) as int) ASC ").ToList();

            //Duyệt phim thành "Chưa chiếu"
         
               List<LICHCHIEU> LichChieuDaCo = db.LICHCHIEUx.SqlQuery(
                 @"select * from LICHCHIEU where NGAYCHIEU ='"
                 + NgayChieu.Value.Year + "-"
                 + NgayChieu.Value.Month + "-"
                 + NgayChieu.Value.Day + "' and TINHTRANG = N'Chưa chiếu' and MAPHONGCHIEU = '" + PhongChieu + "' order by cast(LEFT(GIOBATDAU,LEN(GIOBATDAU) - 3) as int) ASC ").ToList();
            if (Duyet != null)
            {
               

                if (LichChieuDaCo.Count == 0)
                {

                    foreach (var item in LichChieu)
                    {
                        item.TINHTRANG = "Chưa chiếu";
                        db.Entry(item).State = System.Data.EntityState.Modified;
                        db.SaveChanges();


                    }
                    LichChieu = db.LICHCHIEUx.SqlQuery(
                    @"select * from LICHCHIEU where NGAYCHIEU ='"
                    + NgayChieu.Value.Year + "-"
                    + NgayChieu.Value.Month + "-"
                    + NgayChieu.Value.Day + "' and TINHTRANG = N'" + "Chưa chiếu" + "'and MAPHONGCHIEU = '" + PhongChieu + "' order by cast(LEFT(GIOBATDAU,LEN(GIOBATDAU) - 3) as int) ASC ").ToList();
                    ViewBag.TinhTrangDaChon = "Chưa chiếu";
                }
                else
                {
                    ModelState.AddModelError(string.Empty, "Lỗi : Lịch này đã duyệt, không cho phép chỉnh sửa !");
                    LichChieu = db.LICHCHIEUx.SqlQuery(
               @"select * from LICHCHIEU where NGAYCHIEU ='"
               + NgayChieu.Value.Year + "-"
               + NgayChieu.Value.Month + "-"
               + NgayChieu.Value.Day + "' and TINHTRANG = N'Chờ duyệt'and MAPHONGCHIEU = '" + PhongChieu + "' order by cast(LEFT(GIOBATDAU,LEN(GIOBATDAU) - 3) as int) ASC ").ToList();
                }
            }

            

            //Tính giờ trống trong ngày
           
           List<LICHCHIEU> LichChieuSang = new List<LICHCHIEU>();
           List<LICHCHIEU> LichChieuChieu = new List<LICHCHIEU>();
            foreach(var item in LichChieu)
            {
                if ( int.Parse(item.GIOBATDAU.Split(',').First()) <= 12)
                {
                    LichChieuSang.Add(item);
                }
                if (int.Parse(item.GIOBATDAU.Split(',').First()) > 12)
                {
                    LichChieuChieu.Add(item);
                }
            }
            ViewBag.LichChieuSang = LichChieuSang;
            ViewBag.LichChieuChieu = LichChieuChieu;

           if (LichChieuSang != null)
           {
               List<string> GioTrongSang = new List<string>();
               List<string> NumberSang = new List<string>();

               //Tính giờ trống
               for (int i = 0; i < LichChieuSang.Count - 1; i++)
               {
                   string[] namebd = LichChieuSang[i + 1].GIOBATDAU.Split(',');
                   string[] namekt = LichChieuSang[i].GIOKETTHUC.Split(',');

                   int Phutkt = int.Parse(namekt.First()) * 60 + int.Parse(namekt.Last());
                   int Phutbd = int.Parse(namebd.First()) * 60 + int.Parse(namebd.Last());
                   int ThoiGianDuRa = Phutbd - Phutkt;
                   if (ThoiGianDuRa > 0)
                   {
                       string temp = LichChieuSang[i].GIOKETTHUC + "-" + LichChieuSang[i + 1].GIOBATDAU;
                       GioTrongSang.Add(temp);
                   }
               }
               ViewBag.GioTrongSang = GioTrongSang;
               //Tính number của các ID
               for (int i = 0; i < GioTrongSang.Count; i++)
               {
                   string temp = GioTrongSang[i].Split('-').Last().Split(',').First();
                   NumberSang.Add(temp);

               }
               ViewBag.NumberSang = NumberSang;
           }


           if (LichChieuChieu != null)
           {
               List<string> GioTrongChieu = new List<string>();
               List<string> NumberChieu = new List<string>();

               //Tính giờ trống
               for (int i = 0; i < LichChieuChieu.Count - 1; i++)
               {
                   string[] namebd = LichChieuChieu[i + 1].GIOBATDAU.Split(',');
                   string[] namekt = LichChieuChieu[i].GIOKETTHUC.Split(',');

                   int Phutkt = int.Parse(namekt.First()) * 60 + int.Parse(namekt.Last());
                   int Phutbd = int.Parse(namebd.First()) * 60 + int.Parse(namebd.Last());
                   int ThoiGianDuRa = Phutbd - Phutkt;
                   if (ThoiGianDuRa > 0)
                   {
                       string temp = LichChieuChieu[i].GIOKETTHUC + "-" + LichChieuChieu[i + 1].GIOBATDAU;
                       GioTrongChieu.Add(temp);
                   }
               }
               ViewBag.GioTrongChieu = GioTrongChieu;
               //Tính number của các ID
               for (int i = 0; i < GioTrongChieu.Count; i++)
               {
                   string temp = GioTrongChieu[i].Split('-').Last().Split(',').First();
                   NumberChieu.Add(temp);

               }
               ViewBag.NumberChieu = NumberChieu;
           }

            
            

         
          //Error
            if (Error != null)
            {
                ModelState.AddModelError(string.Empty, "Lỗi : Thời lượng phim quá dài so với khung giờ còn trống !");
            }
            else if (LichChieuDaCo.Count == 0)
            {
                foreach (var modelValue in ModelState.Values)
                    modelValue.Errors.Clear();
            }
            
          
           
           return View();

           
        }
         [HttpPost, ActionName("Index")]
        public ActionResult Index(string _PhongChieu, DateTime _NgayChieu, string _TenPhim, string _PhienBan, DateTime? _GioChieu,DateTime? _LimitTime,string Save,string Xoa,string _TinhTrang,string _DuyetPhim)
        {
            if (Save != null) // Lưu mới lịch chiếu
            {
                if (!new SapLichChieuBS().Insert(_TenPhim,_PhienBan,_PhongChieu,_NgayChieu,_GioChieu,_LimitTime))
                {
                    return RedirectToAction("Index", new { PhongChieu = _PhongChieu, NgayChieu = _NgayChieu ,Error = "Error",TinhTrang = _TinhTrang});
                }
                
            }
             if (Xoa != null)// Xóa lịch chiếu
             {
                     new SapLichChieuBS().Xoa(_PhongChieu, _NgayChieu, Xoa);
                 
             }

             if (_DuyetPhim != null) // Đổi lịch chiếu thành tình trạng : "Chưa chiếu"
             {
                 return RedirectToAction("Index", new { PhongChieu = _PhongChieu, NgayChieu = _NgayChieu, TinhTrang = _TinhTrang,Duyet = "OK" });
             }

             return RedirectToAction("Index", new { PhongChieu = _PhongChieu, NgayChieu = _NgayChieu, TinhTrang = _TinhTrang });
        }

        [HttpPost]
        public JsonResult PhienBan(string TenPhim)
     {
         db = new QuanLyCinemaEntities();

            //Get Phiên bản theo tên phim
         var PB = db.CT_PHIM
             .Where(x => x.MAPHIM == TenPhim)
             .Select(a => new
             {
                 _PhienBan = a.PHIENBAN,
             }).ToList();
            

          
         
         return Json( PB ,JsonRequestBehavior.AllowGet);
     }
    }
}
