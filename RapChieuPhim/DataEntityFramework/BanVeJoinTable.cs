using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataEntityFramework
{
    public class BanVeJoinTable
    {
        public string MALICHCHIEU { get; set; }
        public string MAPHIM { get; set; }
        public string PHIENBAN { get; set; }
        public string MAPHONGCHIEU { get; set; }
        public Nullable<System.DateTime> NGAYCHIEU { get; set; }
        public string GIOBATDAU { get; set; }
        public string GIOKETTHUC { get; set; }
        public string TINHTRANG { get; set; }

        public string TENPHIM { get; set; }
        public string CONGNGHE { get; set; }
        public string THELOAI { get; set; }
        public string QUOCGIA { get; set; }
        public Nullable<int> THOILUONG { get; set; }
        public string DAODIEN { get; set; }
        public string DIENVIEN { get; set; }
        public string CHITIET { get; set; }

        public Nullable<int> STTGHE { get; set; }

        public string TENPHONGCHIEU { get; set; }
        public Nullable<int> SOGHE { get; set; }
    }
}
