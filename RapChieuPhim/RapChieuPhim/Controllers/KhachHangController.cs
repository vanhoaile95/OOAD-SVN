using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System;
using RapChieuPhim.Models;
using RapChieuPhim.Models.KhachHang;

namespace RapChieuPhim.Controllers
{
    public class KhachHangController : Controller
    {
        //
        // GET: /KhanhHang/
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        public ActionResult Index()
        {
            var list = from a in db.KHACHHANGs
                       select new JoinTable
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

            return View(list.ToList());
        }
        public ActionResult LoadKhachHang()
        {
            return View();
        }
    }
}
