//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace RapChieuPhim.Models
{
    using System;
    using System.Collections.Generic;
    
    public partial class KHACHHANG
    {
        public KHACHHANG()
        {
            this.HOADONs = new HashSet<HOADON>();
        }
    
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
