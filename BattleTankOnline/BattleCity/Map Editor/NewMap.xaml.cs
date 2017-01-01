using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Map_Editor
{
    /// <summary>
    /// Interaction logic for NewMap.xaml
    /// </summary>
    public partial class NewMap : Window
    {
        public delegate void MapInfo(int width, int height);
        public delegate void EnableMainWindow();

        public MapInfo newMapInfo;
        public EnableMainWindow enableMainWindow;

        public const int MIN_WIDTH = 512, MIN_HEIGHT = 512;

        public NewMap()
        {
            InitializeComponent();
            this.tbWidth.Text = ">= " + MIN_WIDTH;
            this.tbHeight.Text = ">= " + MIN_HEIGHT;
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (!(string.IsNullOrEmpty(this.tbHeight.Text) && string.IsNullOrEmpty(this.tbWidth.Text)))
            {
                if (newMapInfo != null)
                {
                    try
                    {
                        // kiểm tra xem size of map có đạt tiêu chuẩn hay k
                        if (Int32.Parse(this.tbWidth.Text) < MIN_WIDTH || Int32.Parse(this.tbHeight.Text) < MIN_HEIGHT)
                        {
                            MessageBox.Show("The size of map is smaller than requiring!");
                            return;
                        }

                        newMapInfo(Int32.Parse(this.tbWidth.Text), Int32.Parse(this.tbHeight.Text));
                        this.Close();
                    }
                    catch (Exception ex)
                    {
                        newMapInfo(MIN_WIDTH, MIN_HEIGHT);
                        this.Close();
                    }
                }
            }
            else
            {
                MessageBox.Show("You aren't still complete information for new map!");
            }
        }

        private void tbWidth_GotFocus_1(object sender, RoutedEventArgs e)
        {
            this.tbWidth.Text = "";
        }

        private void tbHeight_GotFocus_1(object sender, RoutedEventArgs e)
        {
            this.tbHeight.Text = "";
        }

        private void Window_KeyDown_1(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                this.Button_Click_1(this, new RoutedEventArgs());
            }
        }

        private void Window_Closing_1(object sender, System.ComponentModel.CancelEventArgs e)
        {
            enableMainWindow();
        }
    }
}
