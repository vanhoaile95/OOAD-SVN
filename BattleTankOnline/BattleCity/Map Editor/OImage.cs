using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Map_Editor
{
    /// <summary>
    /// Lớp image đối tượng
    /// </summary>
    class OImage
    {
        public Image Bitmap { get; private set; }

        // khởi tạo các đối tượng cho Image Bitmap, dùng để load lên listbox
        public OImage(BObjectName name, string filename, int width = 50, int height = 50)
        {
            this.Bitmap = new Image();
            this.Bitmap.Tag = (int)name;
            this.Bitmap.Source = new BitmapImage(new Uri(filename, UriKind.Relative));
            this.Bitmap.Width = width;
            this.Bitmap.Height = height; 
        }
    }
}
