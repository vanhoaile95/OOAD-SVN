using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataEntityFramework;
using PagedList;

namespace DataTier
{
    public class BanVeDT
    {
        QuanLyCinemaEntities db = new QuanLyCinemaEntities();

        public IEnumerable<BanVeJoinTable> getAll_LichChieu(int Page, int PageSize)
        {
            var list = from a in db.LICHCHIEUx
                       join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                       join c in db.PHONGCHIEUx on a.MAPHONGCHIEU equals c.MAPHONGCHIEU
                       where a.TINHTRANG == "Chưa chiếu"
                       select new BanVeJoinTable
                       {
                           MALICHCHIEU = a.MALICHCHIEU,
                           TENPHIM = b.TENPHIM,
                           PHIENBAN = a.PHIENBAN,
                           TENPHONGCHIEU = c.TENPHONGCHIEU,
                           NGAYCHIEU = a.NGAYCHIEU,
                           GIOBATDAU = a.GIOBATDAU.Replace(",", " giờ "),
                           GIOKETTHUC = a.GIOKETTHUC.Replace(",", " giờ "),
                           TINHTRANG = a.TINHTRANG,
                       };
            return list.OrderByDescending(x=>x.NGAYCHIEU).ToPagedList(Page,PageSize);
        }

        public List<BanVeJoinTable> getInfo_LichChieu(string MaLichChieu)
        {

            // Kiếm các ghế đã được mua trong mã lịch chiếu này
            var listSTTGhe = from a in db.LICHCHIEUx
                             join b in db.VEs on a.MALICHCHIEU equals b.MALICHCHIEU
                             where a.MALICHCHIEU == MaLichChieu
                             select new
                             {
                                 STTghe = b.STTGHE,
                             };

            int countGHE = 0; // đếm để biết rằng ở mã lịch chiếu này có ghế nào được mua chưa

            foreach (var item in listSTTGhe)
            {
                countGHE++;  // chỉ cần đếm được 1 ghế cũng đủ
                break;
            }

            if (countGHE > 0) // nếu có ghế đã được mua thi Join với bảng VE
            {
                var list = from a in db.LICHCHIEUx
                           join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                           join c in db.PHONGCHIEUx on a.MAPHONGCHIEU equals c.MAPHONGCHIEU
                           join d in db.VEs on a.MALICHCHIEU equals d.MALICHCHIEU
                           where a.MALICHCHIEU == MaLichChieu
                           select new BanVeJoinTable
                           {
                               MALICHCHIEU = a.MALICHCHIEU,
                               TENPHIM = b.TENPHIM,
                               PHIENBAN = a.PHIENBAN,
                               TENPHONGCHIEU = c.TENPHONGCHIEU,
                               NGAYCHIEU = a.NGAYCHIEU,
                               GIOBATDAU = a.GIOBATDAU.Replace(",", " giờ "),
                               GIOKETTHUC = a.GIOKETTHUC.Replace(",", " giờ "),
                               TINHTRANG = a.TINHTRANG,
                               STTGHE = d.STTGHE, // danh sách các ghế đã bán vé trong mã lịch phim này
                           };
                return list.ToList();
            }

            else // là lịch chiếu này chưa có ghế nào được mua
            {
                var list = from a in db.LICHCHIEUx
                           join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                           join c in db.PHONGCHIEUx on a.MAPHONGCHIEU equals c.MAPHONGCHIEU
                           where a.MALICHCHIEU == MaLichChieu
                           select new BanVeJoinTable
                           {
                               MALICHCHIEU = a.MALICHCHIEU,
                               TENPHIM = b.TENPHIM,
                               PHIENBAN = a.PHIENBAN,
                               TENPHONGCHIEU = c.TENPHONGCHIEU,
                               NGAYCHIEU = a.NGAYCHIEU,
                               GIOBATDAU = a.GIOBATDAU.Replace(",", " giờ "),
                               GIOKETTHUC = a.GIOKETTHUC.Replace(",", " giờ "),
                               TINHTRANG = a.TINHTRANG,
                               STTGHE = 0, // danh sách các ghế đã bán vé trong mã lịch phim này
                           };
                return list.ToList();
            }
        }
    }
}
