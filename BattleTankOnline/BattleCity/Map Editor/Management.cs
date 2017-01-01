using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Map_Editor
{
    public class Management
    {
        static List<BObjectName> ExclusivelyObjects;
        // load các đối tượng lên các listbox
        public static void InitializeListObjectImages(
            ListBox lbDynamicObject, ListBox lbStaticObject)
        {
            ExclusivelyObjects = Factory.GetExclusivelyObjects();


            //Dynamic Objects
            lbDynamicObject.Items.Add((new OImage(BObjectName.PLAYER0, @"\Images\player1.png")).Bitmap);
            lbDynamicObject.Items.Add((new OImage(BObjectName.PLAYER1, @"\Images\player2.png")).Bitmap);
            lbDynamicObject.Items.Add((new OImage(BObjectName.PLAYER2, @"\Images\player3.png")).Bitmap);
            lbDynamicObject.Items.Add((new OImage(BObjectName.PLAYER3, @"\Images\player4.png")).Bitmap);
            //Static Objects
            lbStaticObject.Items.Add((new OImage(BObjectName.SMALL_BRICK, @"\Images\small_brick.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.BRICK, @"\Images\brick.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.LARGE_BRICK, @"\Images\large_brick.png")).Bitmap);

            lbStaticObject.Items.Add((new OImage(BObjectName.SMALL_BLOCK, @"\Images\small_block.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.BLOCK, @"\Images\block.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.LARGE_BLOCK, @"\Images\large_block.png")).Bitmap);

            lbStaticObject.Items.Add((new OImage(BObjectName.SMALL_IRONBLOCK, @"\Images\small_ironblock.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.IRONBLOCK, @"\Images\ironblock.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.LARGE_IRONBLOCK, @"\Images\large_ironblock.png")).Bitmap);

            lbStaticObject.Items.Add((new OImage(BObjectName.SMALL_WATER, @"\Images\small_water.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.WATER, @"\Images\water.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.LARGE_WATER, @"\Images\large_water.png")).Bitmap);

            lbStaticObject.Items.Add((new OImage(BObjectName.SMALL_TREE, @"\Images\small_tree.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.TREE, @"\Images\tree.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.LARGE_TREE, @"\Images\large_tree.png")).Bitmap);

            lbStaticObject.Items.Add((new OImage(BObjectName.BASE1, @"\Images\base1.png")).Bitmap);
            lbStaticObject.Items.Add((new OImage(BObjectName.BASE2, @"\Images\base2.png")).Bitmap);
        }

        // tạo lưới map
        public static void CreateMapGrid(Canvas cvMap)
        {
            int nHorizontalLine, nVerticalLine;

            nHorizontalLine = (int)cvMap.Height / MainWindow.OBJECT_HEIGHT + 1;
            nVerticalLine = (int)cvMap.Width / MainWindow.OBJECT_WIDTH + 1;

            // vẽ hàng chiều ngang
            for (int i = 0; i < nHorizontalLine; i++)
            {
                Line l = new Line();

                l.X1 = 0;
                l.X2 = cvMap.Width;
                l.Y1 = l.Y2 = i * MainWindow.OBJECT_HEIGHT;
                l.Stroke = new SolidColorBrush(Colors.Gray);
                l.StrokeThickness = 2;

                cvMap.Children.Insert(0, l); //cvMap.Children.Add(l);
            }

            // vẽ hàng dọc
            for (int i = 0; i < nVerticalLine; i++)
            {
                Line l = new Line();

                l.X1 = l.X2 = i * MainWindow.OBJECT_WIDTH;
                l.Y1 = 0;
                l.Y2 = cvMap.Height;
                l.Stroke = new SolidColorBrush(Colors.Gray);
                l.StrokeThickness = 2;

                cvMap.Children.Insert(0, l); //cvMap.Children.Add(l);
            }
        }

        // xóa lưới map
        public static void RemoveMapGrid(Canvas cvMap)
        {
            if (cvMap.Children != null && cvMap.Children.Count > 0)
            {
                List<UIElement> removeItems = new List<UIElement>(); // lưu các item sẽ xóa
                foreach (var item in cvMap.Children)
                {
                    if (item is Line)
                    {
                        removeItems.Add((Line)item);
                    }
                }

                foreach (UIElement item in removeItems) // xóa các item
                {
                    cvMap.Children.Remove(item);
                }
            }
        }

        // thêm đối tượng vào canvas
        public static void AddObjectToCanvas(
            Canvas cvMap,
            Image image,
            int X, int Y,
            MouseButtonEventHandler mouseDown, MouseButtonEventHandler mouseUp,
            bool canOverlap)
        {
            if (image != null)
            {
                #region Kiểm tra duy nhất 

                BObjectName tag = (BObjectName)(int)image.Tag;

                foreach (BObjectName item in ExclusivelyObjects)
                {
                    if(item == tag)
                    {
                        if (HasObjectAdded(cvMap, tag))
                        {
                            MessageBox.Show("Object has already been added into map!");
                            return;
                        }
                    }
                }
                #endregion

                #region Thêm image vào canvas
                Image i = new Image();
                int w, h;

                Factory.ConvertToStandardImage(image, out w, out h);
                i.Width = w;
                i.Height = h;
                i.Source = image.Source;
                i.Tag = image.Tag;
                i.MouseLeftButtonDown += mouseDown;
                i.MouseLeftButtonUp += mouseUp;

                if (!canOverlap) 
                {
                    if (cvMap.Children.Count > 0)
                    {
                        foreach (var item in cvMap.Children)
                        {
                            // nếu đã tồn tại đối tượng tại vị trí (X, Y) thì k add vào canvas, return khỏi hàm
                            if (item is Image && ((Image)item).Opacity != 0.5f) 
                            {
                                if ((int)Canvas.GetLeft((Image)item) == X && (int)Canvas.GetTop((Image)item) == Y)
                                {
                                    MessageBox.Show("This coordinate has a object!");
                                    return;
                                }
                            }
                        }
                    }
                }

                Image rel_X, rel_Y;
                Alignment.Direction dir;
                Point p = Alignment.GetAutoAlignOffset(cvMap, X, Y, w, h, 3, 3, out rel_X, out rel_Y, out dir);

                if (p != (new Point(0, 0)))
                {
                    X += (int)p.X;
                    Y += (int)p.Y;
                }

                Canvas.SetLeft(i, X);
                Canvas.SetTop(i, Y);

                //if (Factory.CheckObjectCollisionAbility((EObjectName)i.Tag) == false)
                //{
                //    if ((EObjectName)i.Tag == EObjectName.FLAG_POSITION)
                //    {
                //        cvMap.Children.Add(i);
                //    }
                //    else
                //    {
                //        cvMap.Children.Insert(0, i);
                //    }
                //}
                //else
                //{
                //    if ((EObjectName)i.Tag == EObjectName.TOWER)
                //    {
                //        cvMap.Children.Insert(0, i);
                //    }
                //    else
                //    {
                //        cvMap.Children.Add(i);
                //    }
                //}
                cvMap.Children.Add(i);
                #endregion
            }
        }

        // Xóa 1 object tại tọa độ tương ứng
        public static void DeleteOneObject(Canvas cvMap, int X, int Y)
        {
            int w, h;
            int left, top;
            if (cvMap.Children.Count > 0)
            {
                foreach (var item in cvMap.Children)
                {
                    if (item is Image && ((Image)item).Opacity != 0.5f)
                    {
                        Image img = (Image)item;
                        //if ((MObjectName)(int)img.Tag != MObjectName.BACKGROUND)
                        //{
                            Factory.ConvertToStandardImage((Image)item, out w, out h);
                            left = (int)Canvas.GetLeft((Image)item);
                            top = (int)Canvas.GetTop((Image)item);
                            if (left <= X && X < (left + w) && top <= Y && Y < (top + h))  // đúng cho cả trường hợp tương đối và tuyệt đối (nếu có dấu = thì chỉ đúng với trường hợp tuyệt đối)
                            {
                                cvMap.Children.Remove((Image)item);
                                return;
                            }
                        //}      
                    }
                }
            }
        }

        // Kiểm tra xem đã thêm object vào map hay chưa
        public static bool HasObjectAdded(Canvas cvMap,BObjectName ObjectName)
        {
            if (cvMap.Children != null && cvMap.Children.Count > 0)
            {
                foreach (var item in cvMap.Children)
                {
                    if ((item is Image) && ((Image)item).Opacity != 0.5f && (BObjectName)(int)((Image)item).Tag == ObjectName)
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        public static bool HasAlreadyOverLap(Canvas cvMap, int X, int Y)
        {
            // kiểm tra tại offset đó có đối tượng hay chưa
            if (cvMap.Children.Count > 0)
            {
                foreach (var item in cvMap.Children)
                {
                    // nếu đã tồn tại đối tượng tại vị trí (X, Y) thì k add vào canvas, return khỏi hàm
                    if (item is Image && ((Image)item).Opacity != 0.5f) // Opacity == 0.5 là hình vẽ tạm thời
                    {
                        if ((int)Canvas.GetLeft((Image)item) == X && (int)Canvas.GetTop((Image)item) == Y)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        public static void TranslatePosition(Canvas cvMap, int dx, int dy)
        {


            if (cvMap.Children.Count > 0)
            {
                int x, y;
                foreach (UIElement item in cvMap.Children)
                {
                    x = (int)Canvas.GetLeft(item);
                    y = (int)Canvas.GetTop(item);

                    Canvas.SetLeft(item, x + dx);
                    Canvas.SetTop(item, y + dy);
                }
            }
        }

        public static Vector GetBoundOfMap(Canvas cvMap, ref int width, ref int height)
        {
            int min_X, min_Y, max_X, max_Y;
            Vector delta = new Vector(0, 0);

            if (cvMap.Children.Count > 0)
            {
                min_X = min_Y = int.MaxValue;
                max_X = max_Y = int.MinValue;

                int X, Y;
                foreach (var item in cvMap.Children)
                {
                    if (item is Image && ((Image)item).Opacity != 0.5f)
                    {
                        X = (int)Canvas.GetLeft((Image)item);
                        Y = (int)Canvas.GetTop((Image)item);

                        if (min_X > X)
                            min_X = X;

                        if (min_Y > Y)
                            min_Y = Y;

                        if (max_X < X)
                            max_X = X;

                        int w, h;
                        Factory.ConvertToStandardImage((Image)item, out w, out h);
                        int _bot_Y = Y + h;
                        if (max_Y < _bot_Y)
                            max_Y = _bot_Y;
                    }
                }

                delta = new Vector(min_X, height - max_Y);

                width = max_X - min_X;
                height = max_Y - min_Y;

                if (width < 700)
                    width = 700;
                if (height < 700)
                    height = 700;
            }

            return delta;
        }

        public static int GetHorBoundOfMap(Canvas cvMap)
        {
            int max_X = 700;

            if (cvMap.Children.Count > 0)
            {
                max_X = int.MinValue;

                int X;
                foreach (var item in cvMap.Children)
                {
                    if (item is Image && ((Image)item).Opacity != 0.5f)
                    {
                        X = (int)Canvas.GetLeft((Image)item);

                        int w, h;
                        Factory.ConvertToStandardImage((Image)item, out w, out h);

                        if (max_X < X + w)
                        {
                            max_X = X + w;
                        }
                    }
                }

                if (max_X < 700)
                    max_X = 700;
            }

            int i = 1;
            while (700 * Math.Pow(2, i) < max_X)
            {
                i++;
            }
            max_X = 700 * (int)Math.Pow(2, i);

            return max_X;
        }

        public static int GetVerBoundOfMap(Canvas cvMap)
        {
            int max_Y = 700;

            if (cvMap.Children.Count > 0)
            {
                max_Y = int.MinValue;

                int Y;
                foreach (var item in cvMap.Children)
                {
                    if (item is Image && ((Image)item).Opacity != 0.5f)
                    {
                        Y = (int)Canvas.GetTop((Image)item);

                        int w, h;
                        Factory.ConvertToStandardImage((Image)item, out w, out h);

                        if (max_Y < Y + h)
                        {
                            max_Y = Y + w;
                        }
                    }
                }

                if (max_Y < 700)
                    max_Y = 700;
            }

            int i = 1;
            while (700 * Math.Pow(2, i) < max_Y)
            {
                i++;
            }
            max_Y = 700 * (int)Math.Pow(2, i);

            return max_Y;
        }
    }
}
