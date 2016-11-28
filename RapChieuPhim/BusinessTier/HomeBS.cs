using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataTier;
namespace BusinessTier
{
    public class HomeBS
    {
        HomeDT Db = new HomeDT();
        public void DoiMatKhauUser()
        {
            Db.DoiMatKhauUser();
        }
       
    }
}
