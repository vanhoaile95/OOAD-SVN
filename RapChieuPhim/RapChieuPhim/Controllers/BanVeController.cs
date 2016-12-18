using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using RapChieuPhim.Models.BanVe;

namespace RapChieuPhim.Controllers
{
    public class BanVeController : Controller
    {
        //
        // GET: /BanVe/
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        public ActionResult Index()
        {
            var list = from a in db.LICHCHIEUx
                       join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                       join c in db.PHONGCHIEUx on a.MAPHONGCHIEU equals c.MAPHONGCHIEU
                       select new JoinTable
                       {
                           MALICHCHIEU = a.MALICHCHIEU,
                           TENPHIM = b.TENPHIM,
                           PHIENBAN = a.PHIENBAN,
                           TENPHONGCHIEU = c.TENPHONGCHIEU,
                           NGAYCHIEU = a.NGAYCHIEU,
                           GIOBATDAU = a.GIOBATDAU,
                           GIOKETTHUC = a.GIOKETTHUC,
                           TINHTRANG = a.TINHTRANG,
                       };
            return View(list.ToList());
        }


        public ActionResult LoadGhe()
        {
            return View();
        }

    }
}
