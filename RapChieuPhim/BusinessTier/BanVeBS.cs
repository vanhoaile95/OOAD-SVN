using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataEntityFramework;
using DataTier;

namespace BusinessTier
{
    public class BanVeBS
    {
        BanVeDT BanVe = new BanVeDT();

        public IEnumerable<BanVeJoinTable> getAll_LichChieu(int Page, int PageSize)
        {
            return BanVe.getAll_LichChieu(Page, PageSize);
        }

        public List<BanVeJoinTable> getInfo_LichChieu(string MaLichChieu)
        {
            return BanVe.getInfo_LichChieu(MaLichChieu).ToList();
        }

    }
}
