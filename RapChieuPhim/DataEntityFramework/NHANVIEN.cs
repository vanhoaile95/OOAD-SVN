﻿//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
namespace DataEntityFramework
{
    using System;
    using System.Collections.Generic;
    
    public partial class NHANVIEN
    {
        public NHANVIEN()
        {
            this.CT_BANGLUONG = new HashSet<CT_BANGLUONG>();
            this.HOADONs = new HashSet<HOADON>();
            this.LICHLAMVIECs = new HashSet<LICHLAMVIEC>();
            this.LICHLAMVIECs1 = new HashSet<LICHLAMVIEC>();
        }
        [DisplayName("Mã nhân viên")]
        public string MANV { get; set; }
        public string PASSWORD { get; set; }
        [DisplayName("Họ Tên")]
        public string HOTEN { get; set; }
        [DisplayName("Ngày sinh")]
        public Nullable<System.DateTime> NGAYSINH { get; set; }
        [DisplayName("Giới tính")]
        public string GIOITINH { get; set; }
        public string MACHUCVU { get; set; }
        [DisplayName("Ngày vào làm")]
        public Nullable<System.DateTime> NGAYVAOLAM { get; set; }
        public string CMND { get; set; }
        [EmailAddress(ErrorMessage = "Email sai cú pháp (VD: vanhoai@gmail.com)")]
        public string EMAIL { get; set; }
        [DisplayName("Điện thoại")]
        public string SDT { get; set; }
        [DisplayName("Địa chỉ")]
        public string DIACHI { get; set; }
            [DisplayName("Tình trạng")]
        public string TINHTRANG { get; set; }
        public byte[] AVARTA { get; set; }
    
        public virtual CHUCVU CHUCVU { get; set; }
        public virtual ICollection<CT_BANGLUONG> CT_BANGLUONG { get; set; }
        public virtual ICollection<HOADON> HOADONs { get; set; }
        public virtual ICollection<LICHLAMVIEC> LICHLAMVIECs { get; set; }
        public virtual ICollection<LICHLAMVIEC> LICHLAMVIECs1 { get; set; }
    }
}
