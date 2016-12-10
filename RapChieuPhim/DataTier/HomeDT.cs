using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data;
using RapChieuPhim.Models;

namespace DataTier
{
    
    public class HomeDT
    {
        QuanLyCinemaEntities db = null;
        public void DoiMatKhauUser( NHANVIEN nvtemp)
        {

            db = new QuanLyCinemaEntities();
            NHANVIEN nv = db.NHANVIENs.SingleOrDefault(n => n.MANV == nvtemp.MANV);
            nv.PASSWORD = nvtemp.PASSWORD;
          
                db.Entry(nv).State = System.Data.EntityState.Modified;
                db.SaveChanges();
          
           
        }
        public void UpdateUser(NHANVIEN nvtemp,string MANV)
        {
            db = new QuanLyCinemaEntities();
            NHANVIEN nv = db.NHANVIENs.SingleOrDefault(n => n.MANV == MANV);
            nv.HOTEN = nvtemp.HOTEN;
            nv.NGAYSINH = nvtemp.NGAYSINH;
            nv.GIOITINH = nvtemp.GIOITINH;
            nv.CMND = nvtemp.CMND;
            nv.EMAIL = nvtemp.EMAIL;
            nv.SDT = nvtemp.SDT;
            nv.DIACHI = nvtemp.DIACHI;
           
                db.Entry(nv).State = System.Data.EntityState.Modified;
                db.SaveChanges();
            
          
        }
      
    
    }
}
