using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using DataEntityFramework;

namespace RapChieuPhim.Models.KhachHang
{
    public class JoinTable
    {
        public string MAKH { get; set; }
        public string MALOAI { get; set; }
        public Nullable<int> DIEMTICHLUY { get; set; }
        public string HOTEN { get; set; }
        public Nullable<System.DateTime> NGAYSINH { get; set; }
        public Nullable<System.DateTime> NGAYDK { get; set; }
        public string CMND { get; set; }
        public string SDT { get; set; }
        public string DIACHI { get; set; }
        public virtual ICollection<HOADON> HOADONs { get; set; }
        public virtual LOAIKH LOAIKH { get; set; }
    }
}