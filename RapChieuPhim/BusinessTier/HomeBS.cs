using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTier;
using RapChieuPhim.Models;
namespace BusinessTier
{
    public class HomeBS
    {
        HomeDT Db = new HomeDT();
        public void DoiMatKhauUser( NHANVIEN nv)
        {
            Db.DoiMatKhauUser( nv);
        }
       
    }
}
