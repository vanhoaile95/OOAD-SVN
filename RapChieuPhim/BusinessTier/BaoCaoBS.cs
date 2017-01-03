using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTier;
using DataEntityFramework;

namespace BusinessTier
{
    public class BaoCaoBS
    {
        BaoCaoDT BaoCao = new BaoCaoDT();

        public List<BanVeJoinTable> TK_NgayChieu(DateTime Time)
        {
            return BaoCao.BC_NgayChieu(Time);
        }

        public List<BanVeJoinTable> TK_NhanVien(DateTime Time)
        {
            return BaoCao.TK_NhanVien(Time);
        }
    }
}
