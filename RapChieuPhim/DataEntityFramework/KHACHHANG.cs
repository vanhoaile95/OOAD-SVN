
//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace DataEntityFramework
{

    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.ComponentModel.DataAnnotations;

    public partial class KHACHHANG
    {
        public KHACHHANG()
        {
            this.HOADONs = new HashSet<HOADON>();
        }
        [DisplayName("Mã khách hàng")]
        public string MAKH { get; set; }
        [DisplayName("Loại Khách Hàng")]
        public string MALOAI { get; set; }
        [DisplayName("Điểm tích lũy")]
        public Nullable<int> DIEMTICHLUY { get; set; }

        [Required(ErrorMessage = "Họ tên không được để trống !!")]
        [DisplayName("Họ tên")]
        public string HOTEN { get; set; }
        [DisplayName("Ngày sinh")]
        public Nullable<System.DateTime> NGAYSINH { get; set; }
        [DisplayName("Ngày đăng ký")]
        public Nullable<System.DateTime> NGAYDK { get; set; }
        [DisplayName("CMND")]
        public string CMND { get; set; }
        [DisplayName("SDT")]
        public string SDT { get; set; }
        [DisplayName("Địa chỉ")]
        public string DIACHI { get; set; }

        public virtual ICollection<HOADON> HOADONs { get; set; }
        public virtual LOAIKH LOAIKH { get; set; }
    }

}
