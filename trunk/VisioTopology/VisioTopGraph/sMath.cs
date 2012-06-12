using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace SiteView.Panel
{
    
    class sMath
    {

        /// <summary>
        /// 根据参照点，按任意角度旋转某一点
        /// </summary>
        /// <param name="rPoint">要旋转的点</param>
        /// <param name="cPoint">参照点</param>
        /// <param name="angle">旋转角度</param>
        /// <returns>旋转后的点</returns>
        public static PointF RotationPoint(PointF rPoint, PointF cPoint, double angle)
        {

            double x = rPoint.X - cPoint.X;
            double y = rPoint.Y - cPoint.Y;
            double length = Math.Sqrt(Math.Pow(x, 2) + Math.Pow(y, 2));
            double angle1 = 0;

            if (x >= 0 && y <= 0)
            {
                angle1 = Math.Asin(x / length) / Math.PI * 180.0;
            }
            if (x >= 0 && y >= 0)
            {
                angle1 = 180.0 - Math.Asin(x / length) / Math.PI * 180.0;
            }
            if (x <= 0 && y >= 0)
            {
                angle1 = 180.0 + Math.Asin(x / length) / Math.PI * 180.0;
            }
            if (x <= 0 && y <= 0)
            {
                angle1 = 360.0 + Math.Asin(x / length) / Math.PI * 180.0;
            }
            x = length * Math.Sin((angle1 + angle) / 180.0 * Math.PI);
            y = length * Math.Cos((angle1 + angle) / 180.0 * Math.PI);
            if ((angle1 + angle) <= 270 || (angle1 + angle) > 90)
            {
                y = -y;
            }

            return new PointF(Convert.ToSingle(x + cPoint.X), Convert.ToSingle(y + cPoint.Y));

        }

        /// <summary>
        /// 获取指定角度的正弦值
        /// </summary>
        /// <param name="angle">角度</param>
        /// <returns>正弦值</returns>
        public static double Sin(double angle)
        {

            return Math.Sin(angle / 180.0 * Math.PI);

        }

        /// <summary>
        /// 获取指定角度的余弦值
        /// </summary>
        /// <param name="angle">角度</param>
        /// <returns>余弦值</returns>
        public static double Cos(double angle)
        {

            return Math.Cos(angle / 180.0 * Math.PI);

        }

    }

}
