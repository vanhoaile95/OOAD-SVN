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
      
    
    }
}
