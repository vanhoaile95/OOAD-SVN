using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataEntityFramework;

namespace DataTier
{
    public class BaoCaoDT
    {
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();
        public List<BanVeJoinTable> BC_NgayChieu(DateTime Time)
        {
            var listSLVe = from a in db.VEs // group các vé lại tính SL Vé, Thành tiền.
                           group a by a.MALICHCHIEU into SL // 1 Mã lịch chiếu có thể bán vé nhiều ngày, nên ko thể lọc theo ngày
                           select new
                           {
                               MALICHCHIEU = SL.Key,
                               SL_VE = SL.Count(),
                               THANHTIEN = SL.Sum(a => a.GIAVE),
                           };

            var listLC = from a in db.LICHCHIEUx // lấy các lịch chiếu hôm nay
                         join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                         where a.NGAYCHIEU.Day == Time.Day && a.NGAYCHIEU.Month == Time.Month && a.NGAYCHIEU.Year == Time.Year
                         select new
                         {
                             MALICHCHIEU = a.MALICHCHIEU,
                             TENPHIM = b.TENPHIM,
                             PHIENBAN = a.PHIENBAN,
                             NGAYDUOCCHON = Time,
                         };

            List<BanVeJoinTable> listBCtemp = new List<BanVeJoinTable>();
            BanVeJoinTable temp = new BanVeJoinTable();
            bool Check = false;

            foreach (var item in listLC)
            {
                Check = false;

                foreach (var item1 in listSLVe)
                {
                    if (item.MALICHCHIEU == item1.MALICHCHIEU)
                    {
                        temp = new BanVeJoinTable();
                        temp.MALICHCHIEU = item.MALICHCHIEU;
                        temp.TENPHIM = item.TENPHIM;
                        temp.PHIENBAN = item.PHIENBAN;
                        temp.NGAYDUOCCHON = item.NGAYDUOCCHON;
                        temp.SL_VE = item1.SL_VE;
                        temp.THANHTIEN = item1.THANHTIEN;
                        temp.SL_SUATCHIEU = 1;

                        listBCtemp.Add(temp);
                        Check = true;
                        break;
                    }
                }

                if (Check == false)
                {
                    temp = new BanVeJoinTable();
                    temp.MALICHCHIEU = item.MALICHCHIEU;
                    temp.TENPHIM = item.TENPHIM;
                    temp.PHIENBAN = item.PHIENBAN;
                    temp.NGAYDUOCCHON = item.NGAYDUOCCHON;
                    temp.SL_VE = 0;
                    temp.THANHTIEN = 0;
                    temp.SL_SUATCHIEU = 1;

                    listBCtemp.Add(temp);
                }
            }

            int count, length;
            List<BanVeJoinTable> listBC = new List<BanVeJoinTable>();

            foreach (var item in listBCtemp)
            {
                count = 0;
                length = 0;

                if (listBC == null)
                {
                    listBC.Add(item);
                }
                else
                    if (listBC != null)
                    {
                        foreach (var item1 in listBC)
                        {
                            length++;
                            if (item.TENPHIM != item1.TENPHIM || item.PHIENBAN != item1.PHIENBAN)
                            {
                                count++;
                            }
                            else
                            {
                                item1.SL_VE += item.SL_VE;
                                item1.THANHTIEN += item.THANHTIEN;
                                item1.SL_SUATCHIEU += item.SL_SUATCHIEU;
                            }
                        }

                        if (length == count)
                        {
                            listBC.Add(item);
                        }
                    }
            }

            return listBC.ToList();
        }

        public List<BanVeJoinTable> TK_NhanVien(DateTime Time)
        {
            var listNV = from a in db.VEs
                         where a.NGAYBAN.Day == Time.Day && a.NGAYBAN.Month == Time.Month && a.NGAYBAN.Year == Time.Year
                         group a by a.MANVBAN into list
                         select new
                         {
                             MANV = list.Key,
                             SL_VeBAN = list.Count(),
                             THANHTIEN = list.Sum(x => x.GIAVE),
                         };

            BanVeJoinTable temp = new BanVeJoinTable();
            List<BanVeJoinTable> listBaoCao = new List<BanVeJoinTable>();

            foreach (var item in listNV)
            {
                var listTemp = db.NHANVIENs.SingleOrDefault(x => x.MANV == item.MANV);
                temp = new BanVeJoinTable();
                temp.MANVBAN = item.MANV;
                temp.SL_VE = item.SL_VeBAN;
                temp.THANHTIEN = item.THANHTIEN;
                temp.HOTENNV = listTemp.HOTEN;
                temp.NGAYDUOCCHON = Time; // Ngày hiển thị lên Calendar

                listBaoCao.Add(temp);
            }

            return listBaoCao.ToList();
        }
    }
}
