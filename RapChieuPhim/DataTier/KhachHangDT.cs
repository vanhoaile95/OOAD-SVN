using DataEntityFramework;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using PagedList;
using System.Text;
using System.Threading.Tasks;

namespace DataTier
{
    public class KhachHangDT
    {
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();

        public IEnumerable<KhachHangJoinTable> SelectAll_KhachHang(int Page, int PageSize)
        {
            var list = from a in db.KHACHHANGs
                       select new KhachHangJoinTable
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
            return list.OrderByDescending(x => x.HOTEN).ToPagedList(Page, PageSize);
        }


        public void UpdateKhachHang(KHACHHANG khtemp, string MAKH)
        {
            KHACHHANG kh = db.KHACHHANGs.SingleOrDefault(n => n.MAKH == MAKH);
            kh.HOTEN = khtemp.HOTEN;
            kh.NGAYSINH = khtemp.NGAYSINH;
            kh.CMND = khtemp.CMND;
            kh.SDT = khtemp.SDT;
            kh.DIACHI = khtemp.DIACHI;

            db.Entry(kh).State = System.Data.EntityState.Modified;
            db.SaveChanges();
        }
        public void UpdateMaLoaiKH( string MAKH,string MALOAI)
        {
            KHACHHANG kh = db.KHACHHANGs.SingleOrDefault(n => n.MAKH == MAKH);
            kh.MALOAI = MALOAI;
            db.Entry(kh).State = System.Data.EntityState.Modified;
            db.SaveChanges();
        }
        public void InsertKhachHang(KHACHHANG khtemp)
        {
            KHACHHANG kh = db.KHACHHANGs.Add(khtemp);

            db.Entry(kh).State = System.Data.EntityState.Added;
            db.SaveChanges();
        }
    }
}
