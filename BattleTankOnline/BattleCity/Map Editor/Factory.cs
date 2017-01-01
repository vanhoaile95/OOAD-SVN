using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace Map_Editor
{
    public enum BObjectName
    {

        PLAYER0,
        PLAYER1,
        PLAYER2,
        PLAYER3,

        BASE1,
        BASE2,

        BRICK,
        SMALL_BRICK,
        LARGE_BRICK,
        BLOCK,
        SMALL_BLOCK,
        LARGE_BLOCK,
        IRONBLOCK,
        SMALL_IRONBLOCK,
        LARGE_IRONBLOCK,
        TREE,
        SMALL_TREE,
        LARGE_TREE,
        WATER,
        SMALL_WATER,
        LARGE_WATER,

        NONE,
    };

    public enum ObjectType
    {
        STATIC,
        NON_STATIC
    }

    public class Factory
    {
        // chuyển tới kích thước chuẩn trong game
        public static void ConvertToStandardImage(System.Windows.Controls.Image image, out int width, out int height)
        {
            int id = (int)image.Tag;

            switch ((BObjectName)id)
            {
                case BObjectName.BASE1:
                case BObjectName.BASE2:
                case BObjectName.BRICK:
                case BObjectName.BLOCK:
                case BObjectName.IRONBLOCK:
                case BObjectName.WATER:
                case BObjectName.TREE:
                    width =2* MainWindow.OBJECT_WIDTH;
                    height =2* MainWindow.OBJECT_HEIGHT;
                    break;
                case BObjectName.LARGE_BRICK:
                case BObjectName.LARGE_BLOCK:
                case BObjectName.LARGE_IRONBLOCK:
                case BObjectName.LARGE_WATER:
                case BObjectName.LARGE_TREE:
                    width =4* MainWindow.OBJECT_WIDTH;
                    height =4* MainWindow.OBJECT_HEIGHT;
                    break;
                default:
                    width = MainWindow.OBJECT_WIDTH;
                    height = MainWindow.OBJECT_HEIGHT;
                    break;
            }
        }

        public static BitmapImage GetBitmapImage(BObjectName type)
        {
            BitmapImage bitmap = null;
            switch (type)
            {
                case BObjectName.PLAYER0:
                    bitmap = new BitmapImage(new Uri(@"\Images\player1.png", UriKind.Relative));
                    break;
                case BObjectName.PLAYER1:
                    bitmap = new BitmapImage(new Uri(@"\Images\player2.png", UriKind.Relative));
                    break;
                case BObjectName.PLAYER2:
                    bitmap = new BitmapImage(new Uri(@"\Images\player3.png", UriKind.Relative));
                    break;
                case BObjectName.PLAYER3:
                    bitmap = new BitmapImage(new Uri(@"\Images\player4.png", UriKind.Relative));
                    break;
           
                case BObjectName.SMALL_BRICK:
                    bitmap = new BitmapImage(new Uri(@"\Images\small_brick.png", UriKind.Relative));
                    break;
                case BObjectName.SMALL_BLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\small_block.png", UriKind.Relative));
                    break;
                case BObjectName.SMALL_IRONBLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\small_ironblock.png", UriKind.Relative));
                    break;
                case BObjectName.SMALL_TREE:
                    bitmap = new BitmapImage(new Uri(@"\Images\small_tree.png", UriKind.Relative));
                    break;
                case BObjectName.SMALL_WATER:
                    bitmap = new BitmapImage(new Uri(@"\Images\small_water.png", UriKind.Relative));
                    break;


                case BObjectName.BRICK:
                    bitmap = new BitmapImage(new Uri(@"\Images\brick.png", UriKind.Relative));
                    break;
                case BObjectName.BLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\block.png", UriKind.Relative));
                    break;
                case BObjectName.IRONBLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\ironblock.png", UriKind.Relative));
                    break;
                case BObjectName.TREE:
                    bitmap = new BitmapImage(new Uri(@"\Images\tree.png", UriKind.Relative));
                    break;
                case BObjectName.WATER:
                    bitmap = new BitmapImage(new Uri(@"\Images\water.png", UriKind.Relative));
                    break;


                case BObjectName.LARGE_BRICK:
                    bitmap = new BitmapImage(new Uri(@"\Images\large_brick.png", UriKind.Relative));
                    break;
                case BObjectName.LARGE_BLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\large_block.png", UriKind.Relative));
                    break;
                case BObjectName.LARGE_IRONBLOCK:
                    bitmap = new BitmapImage(new Uri(@"\Images\large_ironblock.png", UriKind.Relative));
                    break;
                case BObjectName.LARGE_TREE:
                    bitmap = new BitmapImage(new Uri(@"\Images\large_tree.png", UriKind.Relative));
                    break;
                case BObjectName.LARGE_WATER:
                    bitmap = new BitmapImage(new Uri(@"\Images\large_water.png", UriKind.Relative));
                    break;


                case BObjectName.BASE1:
                    bitmap = new BitmapImage(new Uri(@"\Images\base1.png", UriKind.Relative));
                    break;
                case BObjectName.BASE2:
                    bitmap = new BitmapImage(new Uri(@"\Images\base2.png", UriKind.Relative));
                    break;


                default:
                    break;
            }
            return bitmap;
        }

        // Chuyển từ QNode -> Node để lưu
        public static List<Node> TransformFromQNodeToNode(List<QNode> listQNodes)
        {
            List<Node> nodes = new List<Node>();

            if (listQNodes == null || listQNodes.Count == 0)
                return null;

            foreach (var item in listQNodes)
            {
                Node tmpNode = new Node();

                // lấy thông tin QNode
                tmpNode.ID = item.ID;
                tmpNode.X = item.Bound.X;
                tmpNode.Y = item.Bound.Y;
                tmpNode.Width = item.Bound.Width;
                tmpNode.Height = item.Bound.Height;

                // lấy thông tin các đối tượng trong QNode
                tmpNode.GameObjects = new GameObject[item.ListObjects.Count];
                if (item.ListObjects.Count > 0)
                {
                    for (int i = 0; i < item.ListObjects.Count; i++)
                    {
                        GameObject go = new GameObject();
                        
                        go.ID = item.ListObjects[i].ID;
                        go.Type = item.ListObjects[i].Type;
                        // Chuyển tọa độ xuống góc dưới,trái
                        go.X = item.ListObjects[i].Bound.X; 
                        go.Y = item.ListObjects[i].Bound.Y - item.ListObjects[i].Bound.Height; 

                        tmpNode.GameObjects[i] = go;
                    }
                }
                nodes.Add(tmpNode);
            }

            return nodes;
        }

        // kiểm tra 1 đối tượng là động hay tĩnh <có thể di chuyển được>
        //public static ObjectType CheckObjectType(MObjectName obj)
        //{
        //    switch (obj)
        //    {
        //        case MObjectName.PLAYER1:
        //        case MObjectName.PLAYER2:
        //        case MObjectName.PLAYER3:
        //        case MObjectName.PLAYER4:
        //            return ObjectType.NON_STATIC;
        //        default:
        //            return ObjectType.STATIC;
        //    }
        //}

        // kiểm tra xem đối tượng có thể xét va chạm đc k
        public static bool CheckObjectCollisionAbility(BObjectName obj)
        {
            switch (obj)
            {
                case BObjectName.LARGE_TREE:
                case BObjectName.TREE:
                case BObjectName.SMALL_TREE:
                case BObjectName.LARGE_WATER:
                case BObjectName.WATER:
                case BObjectName.SMALL_WATER:
                    return false;
                default:
                    return true;
            }
        }
        public static bool CheckObjectMovableAbility(BObjectName obj)
        {
            switch (obj)
            {
                case BObjectName.PLAYER0:
                case BObjectName.PLAYER1:
                case BObjectName.PLAYER2:
                case BObjectName.PLAYER3:
                    return true;
                default:
                    return false;
            }
        }
        public static List<BObjectName> GetExclusivelyObjects()
        {
            List<BObjectName> ListObject = new List<BObjectName>();
            ListObject.Add(BObjectName.PLAYER0);
            ListObject.Add(BObjectName.PLAYER1);
            ListObject.Add(BObjectName.PLAYER2);
            ListObject.Add(BObjectName.PLAYER3);
            return ListObject;
        }
    }
}
