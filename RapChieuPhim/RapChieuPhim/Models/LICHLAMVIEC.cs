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
    
    public partial class LICHLAMVIEC
    {
        public string MALLV { get; set; }
        public string MANV { get; set; }
        public Nullable<System.DateTime> NGAYLAMVIEC { get; set; }
        public string CONGVIEC { get; set; }
        public string MAPHONGCHIEU { get; set; }
        public string MACA { get; set; }
        public string MANGS { get; set; }
        public string TINHTRANG { get; set; }
    
        public virtual CALAM CALAM { get; set; }
        public virtual NHANVIEN NHANVIEN { get; set; }
        public virtual NHANVIEN NHANVIEN1 { get; set; }
    }
}
