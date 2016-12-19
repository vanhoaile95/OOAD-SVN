using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.IO;
using DataEntityFramework;
using BusinessTier;
namespace RapChieuPhim.Controllers
{
    public class HomeController : Controller
    {
      public static object PathIM = null;
    
     
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
                    var nv = Session["User"] as NHANVIEN;


                    if (current_password == nv.PASSWORD)
                    {

                        nv.PASSWORD = new_password;
                        Session["User"] = nv;
                        new HomeBS().DoiMatKhauUser(nv);
                        

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
        [HttpGet]
        public ActionResult Detail()
          {

              return View(Session["User"] as NHANVIEN);
          }
        [HttpPost]
        public ActionResult Detail(NHANVIEN nv, HttpPostedFileBase FileName = null)
        {

            var path = "";
            if (FileName != null && FileName.ContentLength > 0)
            {
                //Get Path image
                // extract only the fielname
                var fileName = Path.GetFileName(FileName.FileName);
                // Lưu the file inside ~Images folder
                path = Path.Combine(Server.MapPath("~/Images"), fileName);
                FileName.SaveAs(path);

               


               
            } 
            
                try
                {
                    //Update dữ liệu chi tiết user
                    string MANV = (Session["User"] as NHANVIEN).MANV;
                    new HomeBS().UpdateUser(nv, MANV,path);
                    Session["User"] = new QuanLyCinemaEntities().NHANVIENs.SingleOrDefault(n => n.MANV == MANV);
                    //Xóa ảnh từ ~Image folder
                    if (System.IO.File.Exists(path))
                    {
                        System.IO.File.Delete(path);
                    }

                    return View(Session["User"] as NHANVIEN);
                }
                catch
                {
                    return View(Session["User"] as NHANVIEN);
                }
            
            
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
