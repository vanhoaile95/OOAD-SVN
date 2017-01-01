using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor
{
    public class Rectangle
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }

        public Rectangle()
        {
            X = Y = Width = Height = 0;
        }

        public Rectangle(int x, int y, int w, int h)
        {
            X = x;
            Y = y;
            Width = w;
            Height = h;
        }

        public bool IntersectWith(Rectangle r2)
        {
            if (X + Width <= r2.X) // r1 bên trái r2
                return false;
            if (r2.X + r2.Width <= X) // r1 bên phải r2
                return false;
            if (Y - Height >= r2.Y) // r1 trên r2
                return false;
            if (r2.Y - r2.Height >= Y) // r1 dưới r2
                return false;

            return true;
        }

        public static Rectangle Intersect(Rectangle r1, Rectangle r2)
        {
            if (r1 == null || r2 == null)
                return null;

            int X, Y, width, height;

            if (r1.X <= r2.X) // r1 ben trai r2
            {
                X = r2.X;
                if (r2.X + r2.Width < r1.X + r1.Width) // th r2 nho hon r1 va nam trong r1
                {
                    width = r2.Width;
                }
                else
                {
                    width = (r1.X + r1.Width) - r2.X;
                }
            }
            else
            {
                X = r1.X;
                if (r1.X + r1.Width < r2.X + r2.Width)
                {
                    width = r1.Width;
                }
                else
                {
                    width = (r2.X + r2.Width) - r1.X;
                }
            }

            if (r1.Y >= r2.Y) // r1 ben tren r2
            {
                Y = r2.Y;
                if (r1.Y - r1.Height < r2.Y - r2.Height)
                {
                    height = r2.Height;
                }
                else
                {
                    height = r2.Y - (r1.Y - r1.Height);
                }
            }
            else
            {
                Y = r1.Y;
                if (r2.Y - r2.Height < r1.Y - r1.Height)
                {
                    height = r1.Height;
                }
                else
                {
                    height = r1.Y - (r2.Y - r2.Height);
                }
            }

            if (width <= 0 || height <= 0)
                return null;

            return new Rectangle(X, Y, width, height);
        }
    }
}
