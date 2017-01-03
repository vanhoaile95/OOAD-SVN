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

        public IEnumerable<BanVeJoinTable> getAll_LichChieu(int Page, int PageSize, DateTime NgayChieu)
        {
            return BanVe.getAll_LichChieu(Page, PageSize, NgayChieu);
        }

        public List<BanVeJoinTable> getInfo_LichChieu(string MaLichChieu)
        {
            return BanVe.getInfo_LichChieu(MaLichChieu).ToList();
        }

        public string getNextMAVE()
        {
            return BanVe.getNextMAVE();
        }

        public List<ReportVE> getInfo_Ve(string MaVe)
        {
            return BanVe.getInfo_Ve(MaVe);
        }


        public string getGiaVe()
        {
            return BanVe.getGiaVe();
        }

        public bool IsInVe(string MaVe)
        {
            return BanVe.IsInVe(MaVe);
        }

        public bool TestLichChieu(string NgayChieu)
        {
            return BanVe.TestLichChieu(NgayChieu);
        }

        public bool TestAllLichChieu(string NgayChieu)
        {
            return BanVe.TestAllLichChieu(NgayChieu);
        }

        public void UpdateAllLichChieu()
        {
            BanVe.UpdateAllLichChieu();
        }

        public bool CheckStatusLichChieu(string MaLichChieu)
        {
            return BanVe.CheckStatusLichChieu(MaLichChieu);
        }

    }
}
