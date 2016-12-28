using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataEntityFramework;
namespace DataTier
{
   public class SapLichChieuDT
    {
        QuanLyCinemaEntities db = null;
       public void SetAuto_Ma(LICHCHIEU LichChieu)
        {
           //Get 3 số cuối của lịch LC003 -> 003
            var Last_LichChieu =  db.Database.SqlQuery<string>(@"SELECT top 1 Right(MALICHCHIEU,LEN(MALICHCHIEU) - 2)
                                                                                      from LICHCHIEU
                                                                                      order by cast(Right(MALICHCHIEU,LEN(MALICHCHIEU) - 2) as int) DESC").ToList();


            //Nếu  nằm trong khoảng 00x -> 009
            if (Last_LichChieu[0][0] == '0' && Last_LichChieu[0][1] == '0')
            {
                LichChieu.MALICHCHIEU = "LC00" + (int.Parse(Last_LichChieu[0]) + 1).ToString();
            }
            //Nếu nằm trong khoảng 010 -> 099
            else if (Last_LichChieu[0][0] == '0')
            {
                LichChieu.MALICHCHIEU = "LC0" + (int.Parse(Last_LichChieu[0]) + 1).ToString();
            }
            //Nếu nằm trong khoảng 100 -> 999
            else
            {
                LichChieu.MALICHCHIEU = "LC" + (int.Parse(Last_LichChieu[0]) + 1).ToString();
            }
        }
        public void Insert(string _TenPhim,string PhienBan,string PhongChieu,DateTime? _NgayChieu,DateTime? GioChieu)
        {
            db = new QuanLyCinemaEntities();
            LICHCHIEU temp = new LICHCHIEU();
            SetAuto_Ma(temp);
     
            temp.MAPHIM = _TenPhim;
            temp.PHIENBAN = PhienBan;
            temp.MAPHONGCHIEU = PhongChieu;
            temp.NGAYCHIEU = _NgayChieu;
            if (GioChieu.Value.Minute == 0)
                temp.GIOBATDAU = GioChieu.Value.Hour + "," + "00";
            else
                temp.GIOBATDAU = GioChieu.Value.Hour + "," + GioChieu.Value.Minute;

            int? H = (db.PHIMs.SingleOrDefault(maphim => maphim.MAPHIM == _TenPhim).THOILUONG / 60) + GioChieu.Value.Hour;
            int? M = (db.PHIMs.SingleOrDefault(maphim => maphim.MAPHIM == _TenPhim).THOILUONG % 60) + GioChieu.Value.Minute;
            if (M >= 60)
            {
                H = H + M / 60;
                M = M % 60;
            }
            if (H >= 24)
            {
                H = H - 24;
            }
            temp.GIOKETTHUC = H.ToString() + "," + M.ToString();

            temp.TINHTRANG = "Chờ duyệt";
            db.LICHCHIEUx.Add(temp);
            db.SaveChanges();
        }
    }
}
