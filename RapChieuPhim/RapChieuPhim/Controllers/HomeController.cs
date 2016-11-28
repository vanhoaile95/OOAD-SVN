using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using RapChieuPhim.Models;
using BusinessTier;
namespace RapChieuPhim.Controllers
{
    public class HomeController : Controller
    {
        
      
        public ActionResult Index(string username,string password,string Email,string Phone,string delete)
        {
                //Xóa cookie khi click Logout (truyền delete = 'yes' khi click Logout)
                if (delete == "Yes")
                {
                    XoaCookie();
                    return RedirectToAction("Index");
                }
                
                //Tạo cookie khi Login
                if (username != null || password != null || Email != null || Phone != null)
                {
                    QuanLyCinemaEntities data = new QuanLyCinemaEntities();
                    NHANVIEN nv = data.NHANVIENs.SingleOrDefault(n => n.MANV == username && n.PASSWORD == password);
                    if (nv != null)  // Nếu login thành công (Get đc dữ liệu của nv từ database)
                    {
                        //Tạo cookie trên máy client
                        AddCookie(nv);
                        
                    }
                    else
                    {
                        //Thông báo lỗi
                        ModelState.AddModelError(string.Empty, "Tên đăng nhập hoặc mật khẩu không đúng !");
                    }

                }
               
                return View();
            

        }

        public ActionResult ChangePassword(string current_password, string new_password)
        {
            if (current_password != null && new_password != null)
            {
                NHANVIEN nv = Session["User"] as NHANVIEN;
                if (current_password == nv.PASSWORD)
                {

                    return RedirectToAction("Index");
                }
                else
                {
                    ModelState.AddModelError(string.Empty, "Mật khẩu hiện tại không đúng !");
                }
            }
            else
            {
                foreach (var modelValue in ModelState.Values)
                        modelValue.Errors.Clear();

            }
            return View();
            
        }



        public void XoaCookie()
        {
            HttpCookie ck = Request.Cookies["TenDangNhap"];
            ck.Expires = DateTime.Now.AddDays(-1);
            Response.Cookies.Add(ck);
            Session["User"] = null;
        }
        public void AddCookie(NHANVIEN nv)
        {
            HttpCookie ck = new HttpCookie("TenDangNhap");
            ck.Value = nv.MANV;
            ck.Expires = DateTime.Now.AddDays(1);
            Response.Cookies.Add(ck);
            Session["User"] = nv;
        }
    }
   
}
