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

        public IEnumerable<BanVeJoinTable> getAll_LichChieu(int Page, int PageSize, DateTime NgayChieu)
        {
            var list = from a in db.LICHCHIEUx
                       join b in db.PHIMs on a.MAPHIM equals b.MAPHIM
                       join c in db.PHONGCHIEUx on a.MAPHONGCHIEU equals c.MAPHONGCHIEU
                       where a.TINHTRANG == "Chưa chiếu" && c.TINHTRANG == "Đang sử dụng"
                       && a.NGAYCHIEU.Day == NgayChieu.Day && a.NGAYCHIEU.Month == NgayChieu.Month && a.NGAYCHIEU.Year == NgayChieu.Year
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
                           NGAYDUOCCHON = NgayChieu,
                       };

            return list.OrderBy(x => x.GIOBATDAU).ToPagedList(Page, PageSize);
            // chuyển dữ liệu thành các page, trước khi chuyển bắt buộc phải sắp xếp
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

        public string getNextMAVE()
        {

            int NowVE = Convert.ToInt32(db.VEs.Max(x => x.MAVE).Substring(2)) + 1; // Tăng lên 1

            string NextVE = "";

            if (NowVE < 10)
            {
                NextVE = "VE00" + NowVE.ToString();
            }
            else if (NowVE < 100)
            {
                NextVE = "VE0" + NowVE.ToString();
            }
            else
            {
                NextVE = "VE" + NowVE.ToString();
            }

            return NextVE;
        }

        public List<ReportVE> getInfo_Ve(string MaVe)
        {
            var list = from a in db.VEs
                       join b in db.LICHCHIEUx on a.MALICHCHIEU equals b.MALICHCHIEU
                       join c in db.PHONGCHIEUx on b.MAPHONGCHIEU equals c.MAPHONGCHIEU
                       join d in db.PHIMs on b.MAPHIM equals d.MAPHIM
                       join e in db.NHANVIENs on a.MANVBAN equals e.MANV
                       where a.MAVE.CompareTo(MaVe) == 0
                       select new ReportVE
                       {
                           MAVE = MaVe,
                           TENPHIM = d.TENPHIM,
                           GIOBATDAU = b.GIOBATDAU.Replace(",", " : "),
                           TENPHONGCHIEU = c.TENPHONGCHIEU,
                           MANVBAN = a.MANVBAN,
                           TENNVBAN = e.HOTEN,
                           GIAVE = a.GIAVE,
                           NGAYCHIEU = b.NGAYCHIEU,
                           NGAYBAN = a.NGAYBAN,
                           STTGHE = a.STTGHE,
                           PHIENBAN = b.PHIENBAN,
                       };
            return list.ToList();
        }

        public string getGiaVe()
        {
            foreach (var item in db.THAMSOes)
            {
                return item.GIAVE.ToString();
            }
            return "0";
        }

        public bool IsInVe(string MaVe)
        {
            VE temp = db.VEs.SingleOrDefault(x => x.MAVE == MaVe);
            if (temp.TINHTRANG == "CHUAIN")
            {
                return false;
            }
            return true;
        }

        // Kiểm tra xem vào ngày đó, có lịch chiếu nào không ?
        public bool TestLichChieu(string NgayChieu) // chỉ dành cho lịch chiếu "Chưa chiếu"
        {
            DateTime temp = Convert.ToDateTime(NgayChieu);
            var list = from a in db.LICHCHIEUx
                       join b in db.PHONGCHIEUx on a.MAPHONGCHIEU equals b.MAPHONGCHIEU
                       where a.TINHTRANG == "Chưa chiếu" && b.TINHTRANG == "Đang sử dụng" &&
                       a.NGAYCHIEU.Day == temp.Day && a.NGAYCHIEU.Month == temp.Month
                       && a.NGAYCHIEU.Year == temp.Year
                       select new BanVeJoinTable
                       {
                           MALICHCHIEU = a.MALICHCHIEU
                       };
            // nếu ngày được chọn, ko có cái lịch chiếu nào
            int count = 0;
            foreach (var item in list)
            {
                count++;
            }

            if (count == 0) return false;

            return true;

        }

        // Kiểm tra xem vào ngày đó, có lịch chiếu nào không ?
        public bool TestAllLichChieu(string NgayChieu) // dành cho tất cả lịch chiếu,ko quan tâm Tình trạng
        {
            DateTime temp = Convert.ToDateTime(NgayChieu);
            var list = from a in db.LICHCHIEUx
                       join b in db.PHONGCHIEUx on a.MAPHONGCHIEU equals b.MAPHONGCHIEU
                       where a.NGAYCHIEU.Day == temp.Day && a.NGAYCHIEU.Month == temp.Month
                       && a.NGAYCHIEU.Year == temp.Year
                       select new BanVeJoinTable
                       {
                           MALICHCHIEU = a.MALICHCHIEU
                       };
            // nếu ngày được chọn, ko có cái lịch chiếu nào
            int count = 0;
            foreach (var item in list)
            {
                count++;
            }

            if (count == 0) return false;

            return true;

        }

        public void UpdateAllLichChieu()
        {
            // Update các lịch chiếu trong quá khứ
            string Date = DateTime.Now.Date.ToString("dd/MM/yyyy");
            var list = from a in db.LICHCHIEUx
                       join b in db.PHONGCHIEUx on a.MAPHONGCHIEU equals b.MAPHONGCHIEU
                       where a.TINHTRANG == "Chưa chiếu" && b.TINHTRANG == "Đang sử dụng"
                       && a.NGAYCHIEU.Day < DateTime.Now.Day && a.NGAYCHIEU.Month == DateTime.Now.Month
                       && a.NGAYCHIEU.Year == DateTime.Now.Year
                       select new BanVeJoinTable
                       {
                           MALICHCHIEU = a.MALICHCHIEU,
                       };

            foreach (var item in list)
            {
                LICHCHIEU temp = db.LICHCHIEUx.SingleOrDefault(x => x.MALICHCHIEU == item.MALICHCHIEU);
                temp.TINHTRANG = "Đã chiếu";
            }
            db.SaveChanges();

            // Update các lịch chiếu của hôm nay
            list = from a in db.LICHCHIEUx
                   join b in db.PHONGCHIEUx on a.MAPHONGCHIEU equals b.MAPHONGCHIEU
                   where a.TINHTRANG == "Chưa chiếu" && b.TINHTRANG == "Đang sử dụng"
                    && a.NGAYCHIEU.Day == DateTime.Now.Day && a.NGAYCHIEU.Month == DateTime.Now.Month
                    && a.NGAYCHIEU.Year == DateTime.Now.Year
                   select new BanVeJoinTable
                   {
                       MALICHCHIEU = a.MALICHCHIEU,
                       GIOBATDAU = a.GIOBATDAU,
                   };

            string[] GiovaPhut;
            int GioChieu, PhutChieu;
            int GioNow = DateTime.Now.Hour;
            int PhutNow = DateTime.Now.Minute;

            foreach (var item in list)
            {
                GiovaPhut = new string[5];
                GiovaPhut = item.GIOBATDAU.Split(new char[] { ',' });
                GioChieu = Convert.ToInt32(GiovaPhut[0].ToString());
                PhutChieu = Convert.ToInt32(GiovaPhut[1].ToString());

                if ((GioChieu == GioNow && PhutChieu <= PhutNow) || (GioChieu < GioNow))
                {
                    LICHCHIEU temp = db.LICHCHIEUx.SingleOrDefault(x => x.MALICHCHIEU == item.MALICHCHIEU);
                    temp.TINHTRANG = "Đã chiếu";

                }
            }
            db.SaveChanges();
        }

        public bool CheckStatusLichChieu(string MaLichChieu)
        {
            UpdateAllLichChieu();

            LICHCHIEU temp = db.LICHCHIEUx.SingleOrDefault(x => x.MALICHCHIEU == MaLichChieu);
            if (temp.TINHTRANG == "Đã chiếu") return false;
            return true;
        }

    }
}
