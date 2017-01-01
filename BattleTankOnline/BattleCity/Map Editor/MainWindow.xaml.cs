using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Serialization;

namespace Map_Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public const int OBJECT_WIDTH = 32, OBJECT_HEIGHT = 32; // kích thước đối tượng
        private int _origin;
        private int _begin_X, _begin_Y;

        private Image _image;

        private bool isAutoAlign;
        private bool canOverlap;

        private SaveData _saveData;

        private string _curFilename;
        private bool _isUnsaved;

        private bool flags; // false nếu dùng sự kiện phím bắt cho WIndow, true nếu control khác (một số phím: LEFT, UP, RIGHT, DOWN)

        public MainWindow()
        {
            InitializeComponent();
            Management.InitializeListObjectImages(this.lbDynamicObject, this.lbStatiObject);
            ResetAll();
        }

        #region Menu Chức năng
        // tạo map mới
        private void miNew_Click_1(object sender, RoutedEventArgs e)
        {
            if (this._isUnsaved) // nếu trước đó tạo map mà chưa lưu thì hỏi
            {
                MessageBoxResult result = MessageBox.Show("You haven't still saved the map yet. Are you want to save it?",
                                                   "Create New Question", MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (result == MessageBoxResult.Yes)
                {
                    this.miSave_Click_1(this, new RoutedEventArgs());
                }
            }

            NewMap newMapForm = new NewMap();
            newMapForm.Show();
            newMapForm.Topmost = true;
            this.IsEnabled = false;
            newMapForm.newMapInfo = new NewMap.MapInfo(InitializeMap);
            newMapForm.enableMainWindow = new NewMap.EnableMainWindow(this.EnableWindow);
        }

        // mở file map có sẵn
        private void miOpen_Click_1(object sender, RoutedEventArgs e)
        {
            if (this._isUnsaved) // nếu trước đó tạo map mà chưa lưu thì hỏi
            {
                MessageBoxResult r = MessageBox.Show("You haven't still saved the map yet. Are you want to save it?",
                                                   "Create New Question", MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (r == MessageBoxResult.Yes)
                {
                    this.miSave_Click_1(this, new RoutedEventArgs());
                }
            }

            Stream stream;
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.Filter = "Mario Game Map (*.xml)|*.xml";
            ofd.FilterIndex = 1;
            ofd.RestoreDirectory = true;

            Nullable<bool> result = ofd.ShowDialog();
            if (result == true)
            {
                try
                {
                    string filename = ofd.FileName;
                    stream = File.OpenRead(filename);

                    XmlSerializer ser = new XmlSerializer(typeof(SaveData));
                    this._saveData = (SaveData)ser.Deserialize(stream);

                    stream.Close();

                    // tạo mới map và load các đối tượng trong file map vào canvas
                    this.cvMap.Children.RemoveRange(0, this.cvMap.Children.Count);
                    this.InitializeMap(this._saveData.Width, this._saveData.Height); // khởi tạo mới map
                    this._origin = this._saveData.Height;

                    // Tạo list các đối tượng
                    List<GameObject> objects = new List<GameObject>();
                    bool flag;
                    foreach (var item in this._saveData.Nodes)
                    {
                        if (item.GameObjects.Length > 0)
                        {
                            foreach (var i in item.GameObjects)
                            {
                                flag = false;
                                if (objects.Count > 0)
                                {
                                    foreach (var o in objects)
                                    {
                                        if (o.ID == i.ID)
                                            flag = true; // tồn lại đối tượng trong list
                                    }
                                }
                                if (flag == false) // chưa tồn tại đối tượng trong list
                                {
                                    objects.Add(i);
                                }
                            }
                        }
                    }
                    if (objects.Count > 0) // add các đối tượng có trong file
                    {
                        foreach (var item in objects)
                        {
                            Image i = new Image();

                            i.Tag = item.Type;
                            int w, h;
                            Factory.ConvertToStandardImage(i, out w, out h);
                            i.Width = w;
                            i.Height = h;
                            i.MouseLeftButtonDown += i_MouseLeftButtonDown;
                            i.MouseLeftButtonUp += i_MouseLeftButtonUp;

                            Canvas.SetLeft(i, item.X);
                            Canvas.SetTop(i, (this._origin - (item.Y + i.Height)));

                            i.Source = Factory.GetBitmapImage((BObjectName)i.Tag);

                            this.cvMap.Children.Add(i);
                        }
                    }

                    this.swMap.Visibility = System.Windows.Visibility.Visible;
                    this.gbInfo.Visibility = System.Windows.Visibility.Visible;
                    this._curFilename = string.Copy(filename);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        // lưu map
        private void miSave_Click_1(object sender, RoutedEventArgs e)
        {
            if (this._isUnsaved)
            {
                //if (!Management.HasObjectAdded(this.cvMap,))
                //{
                //    MessageBox.Show("Mario hasn't still added on map yet. Please add Mario on map!");
                //    return;
                //}

                if (!string.IsNullOrEmpty(this._curFilename))
                {
                    try
                    {
                        Stream stream;
                        string filename;
                        XmlSerializer ser;
                        List<QGameObject> qGameObjects = new List<QGameObject>();

                        #region DRAW
                        QNode.Mode = QMode.DRAW;
                        this._saveData = LoadSaveData.CreateSaveData(qGameObjects, this.cvMap, (int)this.cvMap.Width, (int)this.cvMap.Height, QNode.Mode); // tạo data để lưu vào file

                        filename = this._curFilename;
                        if (File.Exists(filename)) // nếu có file thì xóa để tránh lỗi file xảy ra
                        {
                            File.Delete(filename);
                        }

                        stream = File.OpenWrite(filename);
                        ser = new XmlSerializer(typeof(SaveData));
                        ser.Serialize(stream, _saveData);

                        stream.Close();
                        #endregion

                        this._isUnsaved = false;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
                else
                {
                    this.miSaveAs_Click_1(sender, e);
                }
            }
        }

        // save as
        private void miSaveAs_Click_1(object sender, RoutedEventArgs e)
        {
            //if (!Management.HasMarioAdded(this.cvMap))
            //{
            //    MessageBox.Show("Mario hasn't still added on map yet. Please add Mario on map!");
            //    return;
            //}

            SaveFileDialog sfd = new SaveFileDialog();

            sfd.Filter = "Battle City (*.xml)|*.xml";
            sfd.FilterIndex = 1;
            sfd.RestoreDirectory = true;

            Nullable<bool> result = sfd.ShowDialog();
            if (result == true)
            {
                try
                {
                    string filename;
                    Stream stream;
                    XmlSerializer ser;
                    List<QGameObject> qGameObjects = new List<QGameObject>();

                    #region DRAW
                    QNode.Mode = QMode.DRAW;
                    this._saveData = LoadSaveData.CreateSaveData(qGameObjects, this.cvMap, (int)this.cvMap.Width, (int)this.cvMap.Height, QNode.Mode); // tạo data để lưu vào file

                    filename = sfd.FileName;
                    this._curFilename = filename;
                    if (File.Exists(filename)) // nếu có file thì xóa để tránh lỗi file xảy ra
                    {
                        File.Delete(filename);
                    }

                    stream = File.OpenWrite(filename);
                    ser = new XmlSerializer(typeof(SaveData));
                    ser.Serialize(stream, _saveData);

                    stream.Close();
                    #endregion

                    this._isUnsaved = false;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        // đóng của sổ map làm việc hiện tại
        private void miClose_Click_1(object sender, RoutedEventArgs e)
        {
            if (this._isUnsaved)
            {
                MessageBoxResult result = MessageBox.Show("You haven't still saved the map yet. Are you want to save it?",
                                        "Quit Question", MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (result == MessageBoxResult.Yes)
                {
                    this.miSave_Click_1(this, new RoutedEventArgs());
                }
            }

            ResetAll();
        }

        // thoát
        private void miExit_Click_1(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        // thoát bằng nút x
        private void Window_Closing_1(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (this._isUnsaved)
            {
                MessageBoxResult result = MessageBox.Show("You haven't still saved the map yet. Are you want to save it?",
                                    "Quit Question", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (result == MessageBoxResult.Yes)
                {
                    this.miSave_Click_1(this, new RoutedEventArgs());
                }
                else if (result == MessageBoxResult.No)
                {
                    Application.Current.Shutdown();
                }
                else
                {
                    e.Cancel = true;
                }
            }
            else
            {
                MessageBoxResult result = MessageBox.Show("Are you want to quit?",
                                                   "Quit Question", MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (result == MessageBoxResult.Yes)
                {
                    Application.Current.Shutdown();
                }
                else
                {
                    e.Cancel = true;
                }
            }
        }
        #endregion

        // Enable WINdow
        private void EnableWindow()
        {
            this.IsEnabled = true;
        }

        // Khởi tạo map
        private void InitializeMap(int width, int height)
        {
            this.ResetAll();
            this.swMap.Visibility = System.Windows.Visibility.Visible;
            this.cvMap.IsEnabled = true;
            this.cvMap.Visibility = System.Windows.Visibility.Visible;
            this.cvMap.Width = width;
            this.cvMap.Height = height;
            //this.cvMap_GridMap();
            this._origin = (int)this.cvMap.Height;
            this.gbInfo.Visibility = System.Windows.Visibility.Visible;
        }

        // di chuyển lưới tự động khi chuột nằm vào các vị trí xác định
        private bool isAutoMoveVerticalScroll;
        private bool isAutoMoveHorizontalScroll;
        private void ScrollViewer_MouseMove_1(object sender, MouseEventArgs e)
        {
            Point mPoint = e.GetPosition(this.swMap);

            // cuộn ngang
            if (isAutoMoveHorizontalScroll)
            {
                    if (mPoint.X >= this.swMap.ActualWidth - MainWindow.OBJECT_WIDTH)
                    {
                        if (this.swMap.HorizontalOffset + this.swMap.ViewportWidth < this.cvMap.Width - 0.5)
                        {
                            this.swMap.ScrollToHorizontalOffset(this.swMap.HorizontalOffset + 0.5);
                        }
                    }
                    else if (mPoint.X <= MainWindow.OBJECT_WIDTH)
                    {
                        if (this.swMap.HorizontalOffset > 0.5)
                        {
                            this.swMap.ScrollToHorizontalOffset(this.swMap.HorizontalOffset - 0.5);
                        }
                    }
            }

            // cuộn dọc
            if (isAutoMoveVerticalScroll)
            {
                if (mPoint.Y >= this.swMap.ActualHeight - MainWindow.OBJECT_HEIGHT)
                {
                    if (this.swMap.VerticalOffset + this.swMap.ViewportHeight < this.cvMap.Height - 0.5)
                    {
                        this.swMap.ScrollToVerticalOffset(this.swMap.VerticalOffset + 0.5);
                    }
                }
                else if (mPoint.Y <= MainWindow.OBJECT_HEIGHT)
                {
                    if (this.swMap.HorizontalOffset > 0.5)
                    {
                        this.swMap.ScrollToVerticalOffset(this.swMap.VerticalOffset - 0.5);
                    }
                }
            }
        }

        // vẽ hình giả và sự kiện thêm đối tượng vào map
        private Image lastImage = null;
        private Image curImage = null;
        private MouseButtonState preMouseState;
        private MouseButtonState curMouseState;
        private void cvMap_MouseMove(object sender, MouseEventArgs e)
        {
            int X, Y; // tọa độ của chuột
            if (isAutoAlign) // tự đọng căn, vẽ tọa độ tương đối
            {
                X = (int)(e.GetPosition(this.cvMap).X / MainWindow.OBJECT_WIDTH) * MainWindow.OBJECT_WIDTH;
                Y = (int)(e.GetPosition(this.cvMap).Y / MainWindow.OBJECT_HEIGHT) * MainWindow.OBJECT_HEIGHT;
            }
            else // vẽ bằng tay, tọa độ tuyệt đối
            {
                X = (int)e.GetPosition(this.cvMap).X;
                Y = (int)e.GetPosition(this.cvMap).Y;
            }

            if (selectedImage == null)
            {
                this.tbX.Text = X.ToString();
                this.tbY.Text = (this._origin - Y).ToString();
            }
            else
            {
                this.tbX.Text = ((int)Canvas.GetLeft(selectedImage)).ToString();
                this.tbY.Text = ((int)(this._origin - Canvas.GetTop(selectedImage))).ToString();
            }

            // remove line căn nếu đã add
            if (this.cvMap.Children.Count > 0)
            {
                List<UIElement> lines = new List<UIElement>();
                foreach (UIElement item in this.cvMap.Children)
                {
                    if (item is Line)
                    {
                        Line l = item as Line;
                         if(l.Tag != null && l.Tag.ToString() == "Align")
                         {
                            lines.Add(item);
                         }
                    }
                }

                if (lines.Count > 0)
                {
                    foreach (var item in lines)
                    {
                        this.cvMap.Children.Remove(item);
                    }
                }
            }

            // tạo hình giả theo chuột
            if (this._image != null)
            {
                if (lastImage != null && lastImage.Opacity == 0.5f)
                {
                    this.cvMap.Children.Remove(lastImage);
                }

                curImage = new Image();
                int w, h;

                Factory.ConvertToStandardImage(this._image, out w, out h);
                curImage.Width = w;
                curImage.Height = h;
                curImage.Source = this._image.Source;
                curImage.Opacity = 0.5f; // dùng để nhận biết và phân biệt với image đc vẽ trong canvas

                Image rel_X, rel_Y;
                Alignment.Direction dir;
                Point p = Alignment.GetAutoAlignOffset(this.cvMap, X, Y, w, h, 3, 3, out rel_X, out rel_Y, out dir);

                if (p != (new Point(0, 0)))
                {
                    X += (int)p.X;
                    Y += (int)p.Y;
                    Alignment.AddAlignLine(this.cvMap, X, Y, w, h, rel_X, rel_Y, dir);
                }

                Canvas.SetLeft(curImage, X);
                Canvas.SetTop(curImage, Y);

                this.cvMap.Children.Add(curImage);
                lastImage = curImage;
                curImage = null;

                curMouseState = e.LeftButton;
                if (curMouseState == MouseButtonState.Pressed && preMouseState == MouseButtonState.Released) // nhấn chuột trái
                {
                    Management.AddObjectToCanvas(this.cvMap, this._image, X, Y, i_MouseLeftButtonDown, i_MouseLeftButtonUp, canOverlap);
                    _isUnsaved = true;
                    _begin_X = X;
                    _begin_Y = Y;
                }
                else if (curMouseState == MouseButtonState.Pressed && e.RightButton == MouseButtonState.Pressed)
                {
                    if (e.GetPosition(this.cvMap).X > _begin_X)
                    {
                        int iWidth, iHeight;
                        Factory.ConvertToStandardImage(this._image, out iWidth, out iHeight);

                        while (_begin_X + iWidth < e.GetPosition(this.cvMap).X)
                        {
                            _begin_X += iWidth;
                            if (Management.HasAlreadyOverLap(this.cvMap, _begin_X, _begin_Y) == false)
                            {
                                Management.AddObjectToCanvas(this.cvMap, this._image, _begin_X, _begin_Y, i_MouseLeftButtonDown, i_MouseLeftButtonUp, canOverlap);
                            }
                        }
                    }
                    else if (e.GetPosition(this.cvMap).X < _begin_X)
                    {
                        int iWidth, iHeight;
                        Factory.ConvertToStandardImage(this._image, out iWidth, out iHeight);

                        while (_begin_X - iWidth > e.GetPosition(this.cvMap).X)
                        {
                            _begin_X -= iWidth;
                            if (Management.HasAlreadyOverLap(this.cvMap, _begin_X, _begin_Y) == false)
                            {
                                Management.AddObjectToCanvas(this.cvMap, this._image, _begin_X, _begin_Y, i_MouseLeftButtonDown, i_MouseLeftButtonUp, canOverlap);
                            }
                        }
                    }
                }

                preMouseState = curMouseState;
            }
            else if (this.selectedImage != null)
            {
                if (e.LeftButton == MouseButtonState.Pressed)
                {
                    isDragDrop = true;

                    selected_Offset_X = (int)e.GetPosition(this.cvMap).X - (selected_X + delta_X);
                    selected_Offset_Y = (selected_Y + delta_Y) - (int)e.GetPosition(this.cvMap).Y;

                    Image rel_X, rel_Y;
                    Alignment.Direction dir;
                    Point p = Alignment.GetAutoAlignOffset(
                        this.cvMap,
                        (int)e.GetPosition(this.cvMap).X - delta_X,
                        (int)e.GetPosition(this.cvMap).Y - delta_Y,
                        (int)selectedImage.Width, (int)selectedImage.Height, 3, 3, out rel_X, out rel_Y, out dir);

                    if (p != (new Point(0, 0)))
                    {
                        selected_Offset_X += (int)p.X;
                        selected_Offset_Y -= (int)p.Y;
                        Alignment.AddAlignLine(this.cvMap, selected_X + selected_Offset_X, selected_Y - selected_Offset_Y, (int)selectedImage.Width, (int)selectedImage.Height, rel_X, rel_Y, dir);
                    }

                    this.tbOffsetX.Text = selected_Offset_X.ToString();
                    this.tbOffsetY.Text = selected_Offset_Y.ToString();
                }
                else
                {
                    this.i_MouseLeftButtonUp(null, null);
                }
            }
        }

        // xác định image đc chọn
        private Image selectedImage = null;
        private int selected_X, selected_Y;
        private int selected_Offset_X, selected_Offset_Y;
        private int delta_X, delta_Y;
        private bool isDragDrop;
        void i_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (this._image == null)
            {
                if (selectedImage != null)
                {
                    selectedImage.Opacity = 1.0f;
                }

                selectedImage = sender as Image;
                selectedImage.Opacity = 0.6f;

                selected_X = (int)Canvas.GetLeft(selectedImage);
                selected_Y = (int)Canvas.GetTop(selectedImage);

                selected_Offset_X = 0;
                selected_Offset_Y = 0;

                delta_X = (int)e.GetPosition(this.selectedImage).X;
                delta_Y = (int)e.GetPosition(this.selectedImage).Y;
            }
        }

        void i_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (selectedImage != null && isDragDrop)
            {
                this._isUnsaved = true;
                selectedImage.Opacity = 1.0f;
                selectedImage = null;
                tbOffsetX.Text = "";
                tbOffsetY.Text = "";
                this.selected_X = 0;
                this.selected_Y = 0;
                this.isDragDrop = false;
            }
        }

        // hỗ trợ việc thêm vào đối tượng khi mousemove không hoạt động (khi nằm ngoài hình -> MouseMove cho là chuột k di chuyển)
        private void cvMap_MouseLeftButtonDown_1(object sender, MouseButtonEventArgs e)
        {
            int X, Y;
            if (isAutoAlign) // tự đọng căn, vẽ tọa độ tương đối
            {
                X = (int)(e.GetPosition(this.cvMap).X / MainWindow.OBJECT_WIDTH) * MainWindow.OBJECT_WIDTH;
                Y = (int)(e.GetPosition(this.cvMap).Y / MainWindow.OBJECT_HEIGHT) * MainWindow.OBJECT_HEIGHT;
            }
            else // vẽ bằng tay, tọa độ tuyệt đối
            {
                X = (int)e.GetPosition(this.cvMap).X;
                Y = (int)e.GetPosition(this.cvMap).Y;
            }

            if (selectedImage == null)
            {
                this.tbX.Text = X.ToString();
                this.tbY.Text = (this._origin - Y).ToString();
            }
            else
            {
                this.tbX.Text = ((int)Canvas.GetLeft(selectedImage)).ToString();
                this.tbY.Text = ((int)(this._origin - Canvas.GetTop(selectedImage))).ToString();
            }

            if (this._image != null)
            {
                if (selectedImage == null) // tránh xảy ra khi selectedImage != null -> sự kiện nhấn chuột ở selectedImage xảy ra
                {
                    Management.AddObjectToCanvas(this.cvMap, this._image, X, Y, i_MouseLeftButtonDown, i_MouseLeftButtonUp, canOverlap);
                    _isUnsaved = true;
                }
            }
        }

        // hỗ trợ việc xóa đối tượng khi mousemove không hoạt động (khi nằm ngoài hình -> MouseMove cho là chuột k di chuyển)
        private void cvMap_MouseRightButtonDown_1(object sender, MouseButtonEventArgs e)
        {
            this._isUnsaved = true;
            int X, Y;
            if (isAutoAlign) // tự đọng căn, vẽ tọa độ tương đối
            {
                X = (int)(e.GetPosition(this.cvMap).X / MainWindow.OBJECT_WIDTH) * MainWindow.OBJECT_WIDTH;
                Y = (int)(e.GetPosition(this.cvMap).Y / MainWindow.OBJECT_HEIGHT) * MainWindow.OBJECT_HEIGHT;
            }
            else // vẽ bằng tay, tọa độ tuyệt đối
            {
                X = (int)e.GetPosition(this.cvMap).X;
                Y = (int)e.GetPosition(this.cvMap).Y;
            }

            Management.DeleteOneObject(this.cvMap, X, Y);
        }

        // xóa hình giả trong canvas khi di chuyển chuột ra ngoài
        private void cvMap_MouseLeave_1(object sender, MouseEventArgs e)
        {
            if (lastImage != null)
            {
                this.cvMap.Children.Remove(lastImage);
            }

            if (curImage != null)
            {
                this.cvMap.Children.Remove(curImage);
            }

            this.tbX.Text = "";
            this.tbY.Text = "";
        }

        // sự kiện nhấn phím
        private void Window_KeyDown_1(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                this.cvMap_MouseLeave_1(null, null);
                this.curImage = null;

                if (selectedImage != null)
                {
                    this.tbOffsetX.Text = "0";
                    this.tbOffsetY.Text = "0";
                    this.tbOffsetX_TextChanged(null, null);
                    this.tbOffsetY_TextChanged(null, null);
                    selectedImage.Opacity = 1.0f;
                    selectedImage = null;
                }

                this.lbStatiObject.SelectedIndex = -1;
                this.lbDynamicObject.SelectedIndex = -1;
            }
            else if (e.Key == Key.Enter)
            {
                if (selectedImage != null) // xác nhận vị trí mới, và selectedImage về null
                {
                    this._isUnsaved = true;
                    selectedImage.Opacity = 1.0f;
                    selectedImage = null;
                    tbOffsetX.Text = "";
                    tbOffsetY.Text = "";
                    this.selected_X = 0;
                    this.selected_Y = 0;
                }
            }


            this.swMap.IsEnabled = false;
            if (selectedImage != null)
            {
                this.tbX.Text = ((int)Canvas.GetLeft(selectedImage)).ToString();
                this.tbY.Text = ((int)(this._origin - Canvas.GetTop(selectedImage))).ToString();

                if (!flags)
                {
                    if (e.Key == Key.Left)
                    {
                        this._isUnsaved = true;
                        Canvas.SetLeft(selectedImage, Canvas.GetLeft(selectedImage) - 1);
                        this.selected_Offset_X--;
                    }
                    else if (e.Key == Key.Right)
                    {
                        this._isUnsaved = true;
                        Canvas.SetLeft(selectedImage, Canvas.GetLeft(selectedImage) + 1);
                        this.selected_Offset_X++;
                    }
                    else if (e.Key == Key.Up)
                    {
                        this._isUnsaved = true;
                        Canvas.SetTop(selectedImage, Canvas.GetTop(selectedImage) - 1);
                        this.selected_Offset_Y++;
                    }
                    else if (e.Key == Key.Down)
                    {
                        this._isUnsaved = true;
                        Canvas.SetTop(selectedImage, Canvas.GetTop(selectedImage) + 1);
                        this.selected_Offset_Y--;
                    }

                    this.tbOffsetX.Text = this.selected_Offset_X.ToString();
                    this.tbOffsetY.Text = this.selected_Offset_Y.ToString();
                }
            }
        }

        private void Window_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            // khi nhả phím, enable scrollviews
            this.swMap.IsEnabled = true;
        }

        // reset lại các đối tượng
        private void ResetAll()
        {
            this.lbDynamicObject.SelectedIndex = -1;
            this.lbStatiObject.SelectedIndex = -1;
            this._image = null;
            this._curFilename = null;
            this._isUnsaved = false;
            this.cvMap.IsEnabled = false;
            this.cvMap.Visibility = System.Windows.Visibility.Hidden;
            this.swMap.Visibility = System.Windows.Visibility.Hidden;
            this.gbInfo.Visibility = System.Windows.Visibility.Hidden;
            this.tbX.Text = "";
            this.tbY.Text = "";
            this.tbOffsetX.Text = "";
            this.tbOffsetY.Text = "";
            this.selectedImage = null;
            this.selected_X = 0;
            this.selected_Y = 0;
            this.selected_Offset_X = 0;
            this.selected_Offset_Y = 0;
            this.delta_X = 0;
            this.delta_Y = 0;
            this.isDragDrop = false;
            this.isAutoMoveVerticalScroll = true;
            this.isAutoMoveHorizontalScroll = true;
            this.canExpandHorizontal = false;
            this.isAutoAlign = false;
            this.canOverlap = false;
            this.miIsAutoMoveHorizontalScroll.IsChecked = true;
            this.miIsAutoMoveVerticalScroll.IsChecked = false;
            this.miExpandHorizontal.IsChecked = false;
            this.miExpandVertical.IsChecked = false;
            this.miShowGridMap.IsChecked = false;
            this.miAutoAlign.IsChecked = false;
            this.miOverlap.IsChecked = false;
            this.flags = false;

            if (this.cvMap.Children.Count > 0)
            {
                this.cvMap.Children.RemoveRange(0, this.cvMap.Children.Count);
            }
        }

        // Thay đổi lựa chọn, tránh trường hợp chuyển tab, nhưng vẫn bị ảnh hưởng bởi các item ở tab cũ
        private void lb_SelectionChanged_1(object sender, SelectionChangedEventArgs e)
        {
            ListBox lb = sender as ListBox;
            this._image = (Image)lb.SelectedItem;

            if (selectedImage != null)
            {
                selectedImage.Opacity = 1.0f;
                selectedImage = null;
            }
        }

        private void TabItem_GotFocus_1(object sender, RoutedEventArgs e)
        {
            this.lbStatiObject.SelectedIndex = -1;
        }

        private void TabItem_GotFocus_2(object sender, RoutedEventArgs e)
        {
            this.lbDynamicObject.SelectedIndex = -1;
        }

        // Vẽ lưới map
        private void miShowGridMap_Checked(object sender, RoutedEventArgs e)
        {
            Management.CreateMapGrid(this.cvMap);
        }

        // Xóa lưới map
        private void miShowGridMap_Unchecked(object sender, RoutedEventArgs e)
        {
            Management.RemoveMapGrid(this.cvMap);
        }

        // các sự kiện thay đổi chế độ auto move scroll
        private void miIsAutoMoveVerticalScroll_Checked_1(object sender, RoutedEventArgs e)
        {
            this.isAutoMoveVerticalScroll = true;
        }

        private void miIsAutoMoveVerticalScroll_Unchecked_1(object sender, RoutedEventArgs e)
        {
            this.isAutoMoveVerticalScroll = false;
        }

        private void miIsAutoMoveHorizontalScroll_Checked_1(object sender, RoutedEventArgs e)
        {
            this.isAutoMoveHorizontalScroll = true;
        }

        private void miIsAutoMoveHorizontalScroll_Unchecked_1(object sender, RoutedEventArgs e)
        {
            this.isAutoMoveHorizontalScroll = false;
        }

        // Tự động căn
        private void miAutoAlign_Checked(object sender, RoutedEventArgs e)
        {
            this.isAutoAlign = true;
        }

        // Bỏ tự động căn
        private void miAutoAlign_Unchecked(object sender, RoutedEventArgs e)
        {
            this.isAutoAlign = false;
        }

        private void miOverlap_Checked(object sender, RoutedEventArgs e)
        {
            this.canOverlap = true;
        }

        private void miOverlap_Unchecked(object sender, RoutedEventArgs e)
        {
            this.canOverlap = false;
        }

        // set vị trí offsetX tạm thời
        private void tbOffsetX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Int32.TryParse(tbOffsetX.Text, out selected_Offset_X) && selectedImage != null)
            {
                if (selected_X + selected_Offset_X < 0) // trường hợp value âm
                {
                    selected_Offset_X = -selected_X;
                    this.tbOffsetX.Text = selected_Offset_X.ToString();
                }
                else if (selected_X + selected_Offset_X + selectedImage.Width > this.cvMap.Width)
                {
                    selected_Offset_X = (int)(this.cvMap.Width - selected_X - selectedImage.Width - 1);
                    this.tbOffsetX.Text = selected_Offset_X.ToString();
                }

                if (selectedImage != null)
                {
                    Canvas.SetLeft(selectedImage, selected_X + selected_Offset_X);
                }
            }
            else
            {
                if (!(tbOffsetX.Text == "-"))
                {
                    tbOffsetX.Text = "";
                }
            }
        }

        // set vị trí offsetY tạm thời
        private void tbOffsetY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Int32.TryParse(tbOffsetY.Text, out selected_Offset_Y) && selectedImage != null)
            {
                if (selected_Y - selected_Offset_Y < 0) // trường hợp selected_Offset_Y âm
                {
                    selected_Offset_Y = -selected_Y;
                    this.tbOffsetY.Text = selected_Offset_Y.ToString();
                }
                else if (selected_Y - selected_Offset_Y + selectedImage.Height > this.cvMap.Height)
                {
                    selected_Offset_Y = (int)(selected_Y + selectedImage.Height - this.cvMap.Height + 1);
                    //this.tbOffsetY.Text = selected_Offset_Y.ToString();
                }

                if (selectedImage != null)
                {
                    Canvas.SetTop(selectedImage, selected_Y - selected_Offset_Y);
                }
            }
            else
            {
                if (!(tbOffsetY.Text == "-"))
                {
                    tbOffsetY.Text = "";
                }
            }
        }

        private void tbOffset_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (flags)
            {
                int value;
                TextBox tb = sender as TextBox;

                if (string.IsNullOrEmpty(tb.Text))
                {
                    tb.Text = "0";
                }

                if (Int32.TryParse(tb.Text, out value))
                {
                    if (e.Key == Key.Up)
                    {
                        value++;
                    }
                    else if (e.Key == Key.Down)
                    {
                        value--;
                    }

                    tb.Text = value.ToString();
                }
            }
        }

        private void tbOffset_GotFocus_1(object sender, RoutedEventArgs e)
        {
            flags = true;
        }

        private void tbOffset_LostFocus_1(object sender, RoutedEventArgs e)
        {
            flags = false;
        }

        private void swMap_ScrollChanged_1(object sender, ScrollChangedEventArgs e)
        {
            if (this.swMap.HorizontalOffset + this.swMap.ViewportWidth == this.swMap.ExtentWidth)
            {
                if (canExpandHorizontal)
                {
                    this.cvMap.Width += 5;
                    //this.miShowGridMap_Unchecked(null, null);
                    //this.miShowGridMap_Checked(null, null);
                }
            }

            if (this.swMap.VerticalOffset + this.swMap.ViewportHeight == this.swMap.ExtentHeight)
            {
                if (canExpandVertical)
                {
                    this.cvMap.Height += 5;
                    Management.TranslatePosition(this.cvMap, 0, 5);
                }
            }
        }

        // kiểm tra sự có thể mở rộng của map
        private bool canExpandHorizontal;
        private bool canExpandVertical;
        private void miExpandHorizontal_Checked_1(object sender, RoutedEventArgs e)
        {
            canExpandHorizontal = true;
        }

        private void miExpandHorizontal_Unchecked_1(object sender, RoutedEventArgs e)
        {
            canExpandHorizontal = false;
        }

        private void miExpandVertical_Unchecked_1(object sender, RoutedEventArgs e)
        {
            canExpandVertical = false;
        }

        private void miExpandVertical_Checked_1(object sender, RoutedEventArgs e)
        {
            canExpandVertical = true;
        }
    }
}
