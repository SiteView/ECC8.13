using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Security.Cryptography;
using System.IO;
using ICSharpCode.SharpZipLib.BZip2;

namespace SiteView.Panel
{

    public class DataManager
    {

        /// <summary>
        /// 构造对象
        /// </summary>
        public DataManager()
        {

        }

        #region 数据加密,解密

        private static byte[] _Key = new byte[] { 0x01, 0x02, 0x03, 0x04, 0x05, 0xf6, 0x07, 0x08, 0x09, 0x10, 0x11, 0x02, 0x13, 0x14, 0x15, 0x16 };
        /// <summary>
        /// 密钥
        /// </summary>
        public byte[] Key
        {

            get
            {
                return _Key;
            }
            set
            {
                _Key = value;
            }

        }

        private static byte[] _IV = new byte[] { 0x01, 0x02, 0x03, 0xd4, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x04, 0x15, 0x16 };
        /// <summary>
        /// 向量
        /// </summary>
        public byte[] IV
        {

            get
            {
                return _IV;
            }
            set
            {
                _IV = value;
            }

        }

        private static RijndaelManaged rjMananger = new RijndaelManaged();
        /// <summary>
        /// 数据加密
        /// </summary>
        /// <param name="EncryptByte">要加密的字节数组</param>
        public static bool Encrypt(byte[] EncryptByte, out byte[] outByte)
        {

            outByte = null;
            try
            {

                MemoryStream ms = new MemoryStream();
                CryptoStream cs = new CryptoStream(ms, rjMananger.CreateEncryptor(_Key, _IV), CryptoStreamMode.Write);

                cs.Write(EncryptByte, 0, EncryptByte.Length);
                cs.FlushFinalBlock();

                outByte = new byte[ms.Length];
                ms.Position = 0;
                ms.Read(outByte, 0, outByte.Length);
            }
            catch (CryptographicException ce)
            {
                Log.WriteLog("数据加密出错！错误： " + ce.ToString());
                return false;
            }
            catch (Exception ex)
            {
                Log.WriteLog("数据加密出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// 数据解密
        /// </summary>
        /// <param name="DecryptByte">要解密的字节数组</param>
        /// <returns></returns>
        public static bool Decrypt(byte[] DecryptByte, out byte[] outByte)
        {

            outByte = null;
            try
            {
                byte[] fromByte;

                MemoryStream ms = new MemoryStream(DecryptByte);
                CryptoStream cs = new CryptoStream(ms, rjMananger.CreateDecryptor(_Key, _IV), CryptoStreamMode.Read);

                fromByte = new byte[DecryptByte.Length];
                int length = cs.Read(fromByte, 0, fromByte.Length);

                outByte = new byte[length];
                for (int i = 0; i < length; i++)
                {
                    outByte[i] = fromByte[i];
                }
            }
            catch (CryptographicException ce)
            {
                Log.WriteLog("数据解密出错！错误： " + ce.ToString());
                return false;
            }
            catch (Exception ex)
            {
                Log.WriteLog("数据解密出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

        #endregion

        #region 数据压缩,解压缩

        /// <summary>
        /// 压缩数据
        /// </summary>
        /// <param name="inStream">输入的数据流</param>
        /// <param name="outStream">压缩后输出的数据流</param>
        public static bool Compress(FileStream inStream, FileStream outStream)
        {

            try
            {
                BZip2.Compress(inStream, outStream, Convert.ToInt32(inStream.Length));
            }
            catch (Exception ex)
            {
                Log.WriteLog("数据压缩出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// 解压数据
        /// </summary>
        /// <param name="inStream">输入的数据流</param>
        /// <param name="outStream">解压后输出的数据流</param>
        public static bool Decompress(FileStream inStream, FileStream outStream)
        {

            try
            {
                BZip2.Decompress(inStream, outStream);
            }
            catch (Exception ex)
            {
                Log.WriteLog("数据解压出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

        #endregion

    }

}
