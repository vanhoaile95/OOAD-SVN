using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Threading.Tasks;
using DataTier;
using DataEntityFramework;
namespace BusinessTier
{
    public class HomeBS
    {
        HomeDT Db = new HomeDT();
        public void DoiMatKhauUser(NHANVIEN nv)
        {
            Db.DoiMatKhauUser(nv);
        }

        public void UpdateUser(NHANVIEN nv, string MANV, string path)
        {
            Db.UpdateUser(nv, MANV, path);
        }
    }
}
