
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
    
public partial class VE
{

    public VE()
    {

        this.HOADONs = new HashSet<HOADON>();

    }


    public string MAVE { get; set; }

    public string MALICHCHIEU { get; set; }

    public int STTGHE { get; set; }

    public string MAKH { get; set; }

    public System.DateTime NGAYBAN { get; set; }

    public string MANVBAN { get; set; }

    public int GIAVE { get; set; }

    public string TINHTRANG { get; set; }



    public virtual LICHCHIEU LICHCHIEU { get; set; }

    public virtual ICollection<HOADON> HOADONs { get; set; }

}

}
