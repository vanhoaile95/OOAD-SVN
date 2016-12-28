using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTier;
using DataEntityFramework;
namespace BusinessTier
{
    
  public  class SapLichChieuBS
    {
      SapLichChieuDT db = new SapLichChieuDT();
        public void Insert(string _TenPhim, string PhienBan, string PhongChieu, DateTime? _NgayChieu,DateTime? GioChieu)
        {
            
            db.Insert(_TenPhim,PhienBan,PhongChieu,_NgayChieu,GioChieu);
        }
    }
}
