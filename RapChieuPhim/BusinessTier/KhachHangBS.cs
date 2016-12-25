using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTier;
using DataEntityFramework;
namespace BusinessTier
{
    public class KhachHangBS
    {
        KhachHangDT Db = new KhachHangDT();
        public IEnumerable<KhachHangJoinTable> SelectAll_KhachHang(int Page, int PageSize)
        {
            return Db.SelectAll_KhachHang(Page, PageSize);
        }

        public void UpdateKhachHang(KHACHHANG kh, string MAKH)
        {
            Db.UpdateKhachHang(kh, MAKH);
        }
        public void InsertKhachHang(KHACHHANG kh)
        {
            Db.InsertKhachHang(kh);
        }
    }
}
