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
        
        public ActionResult Index(DateTime? NgayChieu ,string TenPhim /*Tên phim đã chọn*/ )
        {
            db = new QuanLyCinemaEntities();

            //Gán TenPhim = Tên Phim mặc định đầu tiên trong database, chỉ 1 lần
            if (TenPhim == null)
            {
                TenPhim = db.PHIMs.First().TENPHIM;
            }

            if (NgayChieu != null)
            {
                //Load lịch phim bên phải
            }
            
                //Load Phiên bản phim kèm theo khi chọn Tên Phim
                PHIM MaPhim = db.PHIMs.SingleOrDefault(maphim => maphim.TENPHIM == TenPhim);
                ViewBag.PhienBan =  db.CT_PHIM.SqlQuery("select * from CT_PHIM where MAPHIM ='" + MaPhim.MAPHIM +"'").ToList();
                ViewBag.TenPhimDaChon = TenPhim;
            
           
            ViewBag.TenPhim = db.PHIMs.ToList();
            ViewBag.PhongChieu = db.PHONGCHIEUx.ToList();
            ViewBag.NgayChieu = NgayChieu;
           
            
          
           
           return View();

           
        }
     [HttpPost]
        public ActionResult Index(string _TenPhim,string PhienBan,string PhongChieu,DateTime? _NgayChieu) // Thêm giờ chiếu)
        {
        
            new SapLichChieuBS().Insert(_TenPhim,PhienBan,PhongChieu,_NgayChieu);
            

            return RedirectToAction("Index", new {NgayChieu =  _NgayChieu,TenPhim = _TenPhim});
        }

    }
}
