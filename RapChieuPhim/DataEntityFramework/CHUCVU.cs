
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
    
public partial class CHUCVU
{

    public CHUCVU()
    {

        this.NHANVIENs = new HashSet<NHANVIEN>();

    }


    public string MACHUCVU { get; set; }

    public string TENCHUCVU { get; set; }

    public Nullable<int> LUONG { get; set; }



    public virtual ICollection<NHANVIEN> NHANVIENs { get; set; }

}

}
