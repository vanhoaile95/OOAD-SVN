using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using RapChieuPhim.Models.BanVe;
namespace RapChieuPhim.Controllers
{
    public class SapLichChieuController : Controller
    {
        //
        // GET: /SapLichChieu/
        QuanLyCinemaEntities db = null;
        public ActionResult Index(DateTime? NgayChieu )
        {
            if (NgayChieu != null)
            {
                
            }
            db = new QuanLyCinemaEntities();
            ViewBag.TenPhim = db.PHIMs.ToList();
            ViewBag.PhongChieu = db.PHONGCHIEUx.ToList();
            ViewBag.NgayChieu = NgayChieu;
            return View();

           
        }

    }
}
