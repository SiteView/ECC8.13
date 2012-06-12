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
        /// �������
        /// </summary>
        public DataManager()
        {

        }

        #region ���ݼ���,����

        private static byte[] _Key = new byte[] { 0x01, 0x02, 0x03, 0x04, 0x05, 0xf6, 0x07, 0x08, 0x09, 0x10, 0x11, 0x02, 0x13, 0x14, 0x15, 0x16 };
        /// <summary>
        /// ��Կ
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
        /// ����
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
        /// ���ݼ���
        /// </summary>
        /// <param name="EncryptByte">Ҫ���ܵ��ֽ�����</param>
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
                Log.WriteLog("���ݼ��ܳ������� " + ce.ToString());
                return false;
            }
            catch (Exception ex)
            {
                Log.WriteLog("���ݼ��ܳ������� " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// ���ݽ���
        /// </summary>
        /// <param name="DecryptByte">Ҫ���ܵ��ֽ�����</param>
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
                Log.WriteLog("���ݽ��ܳ������� " + ce.ToString());
                return false;
            }
            catch (Exception ex)
            {
                Log.WriteLog("���ݽ��ܳ������� " + ex.ToString());
                return false;
            }
            return true;

        }

        #endregion

        #region ����ѹ��,��ѹ��

        /// <summary>
        /// ѹ������
        /// </summary>
        /// <param name="inStream">�����������</param>
        /// <param name="outStream">ѹ���������������</param>
        public static bool Compress(FileStream inStream, FileStream outStream)
        {

            try
            {
                BZip2.Compress(inStream, outStream, Convert.ToInt32(inStream.Length));
            }
            catch (Exception ex)
            {
                Log.WriteLog("����ѹ���������� " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// ��ѹ����
        /// </summary>
        /// <param name="inStream">�����������</param>
        /// <param name="outStream">��ѹ�������������</param>
        public static bool Decompress(FileStream inStream, FileStream outStream)
        {

            try
            {
                BZip2.Decompress(inStream, outStream);
            }
            catch (Exception ex)
            {
                Log.WriteLog("���ݽ�ѹ�������� " + ex.ToString());
                return false;
            }
            return true;

        }

        #endregion

    }

}
