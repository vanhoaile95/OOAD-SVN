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
    
    public partial class CT_PHIM
    {
        public CT_PHIM()
        {
            this.LICHCHIEUx = new HashSet<LICHCHIEU>();
        }
    
        public string MAPHIM { get; set; }
        public string PHIENBAN { get; set; }
    
        public virtual PHIM PHIM { get; set; }
        public virtual ICollection<LICHCHIEU> LICHCHIEUx { get; set; }
    }
}
