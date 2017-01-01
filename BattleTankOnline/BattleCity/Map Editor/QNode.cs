using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor
{
    public enum NodePosition
    {
        TOP_LEFT = 1,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    }

    public enum QMode
    {
        DRAW,
        UPDATE
    }

    public class QNode
    {
        public static QMode Mode = QMode.DRAW;

        private const int MEDIUM_NODE_SIZE = 128;
        private const int MIN_NODE_SIZE = MEDIUM_NODE_SIZE/2;
        private const int MIN_SIZE_IN_INTERSECT = 3; // 3 pixels

        private int Id;
        private QNode tl, tr, bl, br;
        private Rectangle bound;
        private List<QGameObject> listObjects;
        private int size;

        public int ID
        {
            get { return Id; }
            set { Id = value; }
        }

        public List<QGameObject> ListObjects
        {
            get { return listObjects; }
            set { listObjects = value; }
        }
        
        public Rectangle Bound
        {
            get { return bound; }
            set { bound = value; }
        }

        public QNode(int parentID, NodePosition pos, Rectangle parentRect)
        {
            Id = parentID * 8 + (int)pos;
            listObjects = new List<QGameObject>();
            tl = null;
            tr = null;
            bl = null;
            br = null;

            if (pos == NodePosition.TOP_LEFT)
            {
                bound = new Rectangle(parentRect.X, parentRect.Y, parentRect.Width / 2, parentRect.Height / 2);
            }
            else if (pos == NodePosition.TOP_RIGHT)
            {
                bound = new Rectangle(parentRect.X + parentRect.Width / 2, parentRect.Y, parentRect.Width / 2, parentRect.Height / 2);
            }
            else if (pos == NodePosition.BOTTOM_LEFT)
            {
                bound = new Rectangle(parentRect.X, parentRect.Y - parentRect.Height / 2, parentRect.Width / 2, parentRect.Height / 2);
            }
            else
            {
                bound = new Rectangle(parentRect.X + parentRect.Width / 2, parentRect.Y - parentRect.Height / 2, parentRect.Width / 2, parentRect.Height / 2);
            }
        }

        public void Insert(QGameObject obj)
        {
            Rectangle rect = Rectangle.Intersect(bound, obj.RangeMovement);
            if (rect == null) // k giao nhau
                return;

            if (rect.Width < MIN_SIZE_IN_INTERSECT || rect.Height < MIN_SIZE_IN_INTERSECT)
                return;

            if (QNode.Mode == QMode.UPDATE)
            {
                this.size = MIN_NODE_SIZE;
            }
            else
            {
                this.size = MEDIUM_NODE_SIZE;
            }

            if (bound.Width >= 2 * this.size) // chưa đạt min, chia 4 node con
            {
                if (this.tl == null)
                {
                    this.tl = new QNode(this.Id, NodePosition.TOP_LEFT, this.bound);
                    this.tr = new QNode(this.Id, NodePosition.TOP_RIGHT, this.bound);
                    this.bl = new QNode(this.Id, NodePosition.BOTTOM_LEFT, this.bound);
                    this.br = new QNode(this.Id, NodePosition.BOTTOM_RIGHT, this.bound);
                }

                this.tl.Insert(obj);
                this.tr.Insert(obj);
                this.bl.Insert(obj);
                this.br.Insert(obj);
            }
            else // khi đạt min, add obj
            {
                listObjects.Add(obj);
            }
        }

        public void GetNode(ref List<QNode> listNodes) // Get node hiện tại và các node con
        {
            listNodes.Add(this);

            if (tl != null)
            {
                tl.GetNode(ref listNodes);
            }

            if (tr != null)
            {
                tr.GetNode(ref listNodes);
            }

            if (bl != null)
            {
                bl.GetNode(ref listNodes);
            }

            if (br != null)
            {
                br.GetNode(ref listNodes);
            }
        }
    }

    public class QGameObject
    {
        private const int MAX_RANGE_OF_MOVEMENT = 3600;
        private const int MAX_RANGE_STATIC_INMAP = 800;

        private int Id;
        private int type;
        private Rectangle bound; // kích thước thực của object
        private Rectangle rangeMovement; // dùng để xét và đưa vào quadtree

        public int ID
        {
            get { return Id; }
            set { Id = value; }
        }

        public int Type
        {
            get { return type; }
            set { type = value; }
        }

        public Rectangle Bound
        {
            get { return bound; }
            set { bound = value; }
        }

        public Rectangle RangeMovement
        {
            get { return rangeMovement; }
            set { rangeMovement = value; }
        }

        public QGameObject(int ID, int type, Rectangle bound, bool isNonStatic)
        {
            this.Id = ID;
            this.type = type;
            this.bound = bound;
            //if (type == (int)MObjectName.BACKGROUND)
            //{
            //    this.rangeMovement = bound;
            //}
            //else 
            this.rangeMovement = new Rectangle(bound.X, bound.Y + MAX_RANGE_STATIC_INMAP / 2, bound.Width, MAX_RANGE_STATIC_INMAP);
            //if (isNonStatic) // dynamic
            //{
            //    this.rangeMovement = new Rectangle(bound.X - MAX_RANGE_OF_MOVEMENT / 2, bound.Y + MAX_RANGE_OF_MOVEMENT / 2, MAX_RANGE_OF_MOVEMENT, MAX_RANGE_OF_MOVEMENT);
            //}
            //else
            //{
            //    this.rangeMovement = new Rectangle(bound.X, bound.Y + MAX_RANGE_STATIC_INMAP / 2, bound.Width, MAX_RANGE_STATIC_INMAP);
            //}
        }
    }
}
