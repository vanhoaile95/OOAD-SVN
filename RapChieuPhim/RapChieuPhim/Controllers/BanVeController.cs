using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using DataEntityFramework;
using BusinessTier;
using PagedList; // sử dung để phân trang

namespace RapChieuPhim.Controllers
{
    public class BanVeController : Controller
    {
        //
        // GET: /BanVe/
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        BanVeBS BanVe = new BanVeBS();
        public ActionResult Index(int Page = 1, int PageSize = 10)
        {
            var list = BanVe.getAll_LichChieu(Page,PageSize);
            return View(list);
            // hàm phân trang ko chấp nhận dữ liệu bị chuyển thành .ToList(), mà tất cả phải chuyển qua kiêu IEnumrable
            // Page : mặc định trang đầu tiên là 1
            // PageSize : là số phần tử trong 1 trang
        }


        public ActionResult LoadGhe(string MaLichChieu)
        {
            var list = BanVe.getInfo_LichChieu(MaLichChieu);
            return View(list.ToList());
        }


    }
}
