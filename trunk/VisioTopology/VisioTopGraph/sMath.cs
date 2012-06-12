using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace SiteView.Panel
{
    
    class sMath
    {

        /// <summary>
        /// ���ݲ��յ㣬������Ƕ���תĳһ��
        /// </summary>
        /// <param name="rPoint">Ҫ��ת�ĵ�</param>
        /// <param name="cPoint">���յ�</param>
        /// <param name="angle">��ת�Ƕ�</param>
        /// <returns>��ת��ĵ�</returns>
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
        /// ��ȡָ���Ƕȵ�����ֵ
        /// </summary>
        /// <param name="angle">�Ƕ�</param>
        /// <returns>����ֵ</returns>
        public static double Sin(double angle)
        {

            return Math.Sin(angle / 180.0 * Math.PI);

        }

        /// <summary>
        /// ��ȡָ���Ƕȵ�����ֵ
        /// </summary>
        /// <param name="angle">�Ƕ�</param>
        /// <returns>����ֵ</returns>
        public static double Cos(double angle)
        {

            return Math.Cos(angle / 180.0 * Math.PI);

        }

    }

}
