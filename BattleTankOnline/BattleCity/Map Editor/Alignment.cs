using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Map_Editor
{
    public class Alignment
    {
        public enum Direction
        {
            NONE = 0,
            LEFT = 1,
            TOP = 2,
            RIGHT = 4,
            BOTTOM = 8
        }

        // lấy về độ dời căn tự động vs các Image
        public static Point GetAutoAlignOffset(
            Canvas cvMap,
            int image_X, int image_Y,
            int width, int height,
            int dis_X, int dis_Y,
            out Image relative_X, out Image relative_Y,
            out Direction dir)
        {
            Point offset = new Point(0, 0);
            relative_X = null;
            relative_Y = null;
            dir = Direction.NONE;

            if (cvMap.Children.Count > 0)
            {
                int left, top, right, bottom;
                int min_X, min_Y;
                bool? isLeft, isTop;

                left = image_X;
                top = image_Y;
                right = left + width;
                bottom = top + height;
                min_X = min_Y = int.MaxValue;
                isLeft = isTop = null;
                foreach (var item in cvMap.Children)
                {
                    if (item is Image && (item as Image).Opacity != 0.5f) // k phải hình giả
                    {
                        Image i = item as Image;

                        int l, t, r, b;

                        l = (int)Canvas.GetLeft(i);
                        t = (int)Canvas.GetTop(i);
                        r = l + (int)i.Width;
                        b = t + (int)i.Height;

                        if (Math.Abs(l - left) < Math.Abs(min_X))
                        {
                            min_X = l - left;
                            isLeft = true;
                            relative_X = i;
                        }
                        if (Math.Abs(r - left) < Math.Abs(min_X))
                        {
                            min_X = r - left;
                            isLeft = false;
                            relative_X = i;
                        }
                        if (Math.Abs(l - right) < Math.Abs(min_X))
                        {
                            min_X = l - right;
                            isLeft = true;
                            relative_X = i;
                        }
                        if (Math.Abs(r - right) < Math.Abs(min_X))
                        {
                            min_X = r - right;
                            isLeft = false;
                            relative_X = i;
                        }

                        if (Math.Abs(t - top) < Math.Abs(min_Y))
                        {
                            min_Y = t - top;
                            isTop = true;
                            relative_Y = i;
                        }
                        if (Math.Abs(b - top) < Math.Abs(min_Y))
                        {
                            min_Y = b - top;
                            isTop = false;
                            relative_Y = i;
                        }
                        if (Math.Abs(t - bottom) < Math.Abs(min_Y))
                        {
                            min_Y = t - bottom;
                            isTop = true;
                            relative_Y = i;
                        }
                        if (Math.Abs(b - bottom) < Math.Abs(min_Y))
                        {
                            min_Y = b - bottom;
                            isTop = false;
                            relative_Y = i;
                        }
                    }
                }

                // cập nhật offset Point
                if (Math.Abs(min_X) <= dis_X)
                {
                    offset.X = min_X;
                    if (isLeft == true)
                    {
                        dir |= Direction.LEFT;
                    }
                    else if (isLeft == false)
                    {
                        dir |= Direction.RIGHT;
                    }
                }

                if (Math.Abs(min_Y) <= dis_Y)
                {
                    offset.Y = min_Y;
                    if (isTop == true)
                    {
                        dir |= Direction.TOP;
                    }
                    else if (isTop == false)
                    {
                        dir |= Direction.BOTTOM;
                    }
                }
            }

            return offset;
        }

        public static void AddAlignLine(
            Canvas cvMap,
            int image_X, int image_Y,
            int width, int height,
            Image relative_X, Image relative_Y,
            Direction dir)
        {
            if ((dir & Direction.LEFT) == Direction.LEFT)
            {
                Line l = new Line();

                l.X1 = l.X2 = Canvas.GetLeft(relative_X);
                l.Y2 = Canvas.GetTop(relative_X);
                if (image_Y < Canvas.GetTop(relative_X))
                {
                    l.Y1 = image_Y;
                    l.Y2 = Canvas.GetTop(relative_X) + relative_X.Height;
                }
                else
                {
                    l.Y1 = image_Y + height;
                    l.Y2 = Canvas.GetTop(relative_X);
                }

                l.Tag = "Align";
                l.Stroke = new SolidColorBrush(Colors.Yellow);
                l.StrokeThickness = 3;

                cvMap.Children.Add(l);
            }
            else if ((dir & Direction.RIGHT) == Direction.RIGHT)
            {
                Line l = new Line();

                l.X1 = l.X2 = Canvas.GetLeft(relative_X) + relative_X.Width;
                if (image_Y < Canvas.GetTop(relative_X))
                {
                    l.Y1 = image_Y;
                    l.Y2 = Canvas.GetTop(relative_X) + relative_X.Height;
                }
                else
                {
                    l.Y1 = image_Y + height;
                    l.Y2 = Canvas.GetTop(relative_X);
                }

                l.Tag = "Align";
                l.Stroke = new SolidColorBrush(Colors.Yellow);
                l.StrokeThickness = 3;

                cvMap.Children.Add(l);
            }

            if ((dir & Direction.TOP) == Direction.TOP)
            {
                Line l = new Line();

                l.Y1 = l.Y2 = Canvas.GetTop(relative_Y);
                if (image_X < Canvas.GetLeft(relative_Y))
                {
                    l.X1 = image_X;
                    l.X2 = Canvas.GetLeft(relative_Y) + relative_Y.Width;
                }
                else
                {
                    l.X1 = image_X + width;
                    l.X2 = Canvas.GetLeft(relative_Y);
                }

                l.Tag = "Align";
                l.Stroke = new SolidColorBrush(Colors.Yellow);
                l.StrokeThickness = 3;

                cvMap.Children.Add(l);
            }
            else if ((dir & Direction.BOTTOM) == Direction.BOTTOM)
            {
                Line l = new Line();

                l.Y1 = l.Y2 = Canvas.GetTop(relative_Y) + relative_Y.Height;
                if (image_X < Canvas.GetLeft(relative_Y))
                {
                    l.X1 = image_X;
                    l.X2 = Canvas.GetLeft(relative_Y) + relative_Y.Width;
                }
                else
                {
                    l.X1 = image_X + width;
                    l.X2 = Canvas.GetLeft(relative_Y);
                }

                l.Tag = "Align";
                l.Stroke = new SolidColorBrush(Colors.Yellow);
                l.StrokeThickness = 3;

                cvMap.Children.Add(l);
            }
        }
    }
}
