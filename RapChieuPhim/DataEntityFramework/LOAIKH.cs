
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
    
public partial class LOAIKH
{

    public LOAIKH()
    {

        this.KHACHHANGs = new HashSet<KHACHHANG>();

    }


    public string MALOAI { get; set; }

    public Nullable<int> DIEM { get; set; }



    public virtual ICollection<KHACHHANG> KHACHHANGs { get; set; }

}

}
