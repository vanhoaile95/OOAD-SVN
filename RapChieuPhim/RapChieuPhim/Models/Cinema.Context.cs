﻿//------------------------------------------------------------------------------
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
    using System.Data.Entity;
    using System.Data.Entity.Infrastructure;
    
    public partial class QuanLyCinemaEntities : DbContext
    {
        public QuanLyCinemaEntities()
            : base("name=QuanLyCinemaEntities")
        {
        }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            throw new UnintentionalCodeFirstException();
        }
    
        public DbSet<BANGLUONG> BANGLUONGs { get; set; }
        public DbSet<CALAM> CALAMs { get; set; }
        public DbSet<CHUCVU> CHUCVUs { get; set; }
        public DbSet<CT_BANGLUONG> CT_BANGLUONG { get; set; }
        public DbSet<CT_PHIM> CT_PHIM { get; set; }
        public DbSet<HOADON> HOADONs { get; set; }
        public DbSet<KHACHHANG> KHACHHANGs { get; set; }
        public DbSet<LICHCHIEU> LICHCHIEUx { get; set; }
        public DbSet<LICHLAMVIEC> LICHLAMVIECs { get; set; }
        public DbSet<LOAIKH> LOAIKHs { get; set; }
        public DbSet<NHANVIEN> NHANVIENs { get; set; }
        public DbSet<PHIM> PHIMs { get; set; }
        public DbSet<PHONGCHIEU> PHONGCHIEUx { get; set; }
        public DbSet<VE> VEs { get; set; }
    }
}
