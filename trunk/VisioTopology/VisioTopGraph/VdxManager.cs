using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Windows.Forms;

namespace SiteView.Panel
{

    /// <summary>
    /// 设备信息
    /// </summary>
    [Serializable]
    public struct EquipVdx
    {

        //设备oid
        public string Sysoid;
        //设备厂商
        public string Factory;
        //设备型号
        public string Model;
        //设备类型
        //0, 三层交换机(路由交换机)
        //1,二层交换机
        //2,路由器
        //3,防火墙
        public int Type;
        //设备vdx文件名
        public string FileName;
        ///设备vdx临时文件
        public string tempFileName;
        //包的起始位置
        public long PackIndex;
        //包的长度
        public long PackLength;

    };

    public class VdxManager
    {

        //保存Vdx信息的数据文件
        private string _FileDat = string.Empty;
        private string _FileMpg = string.Empty;

        /// <summary>
        /// 构造对象
        /// </summary>
        public VdxManager()
        {
            
        }

        /// <summary>
        /// 设备vdx信息文件
        /// </summary>
        public string FileDat
        {

            set
            {
                _FileDat = value;
            }

        }

        /// <summary>
        /// 设备vdx文件数据文件
        /// </summary>
        public string FileMpg
        {

            set
            {
                _FileMpg = value;
            }

        }

        private ProgressBar _ProgressBar = new ProgressBar();
        /// <summary>
        /// 获取或设置进度条
        /// </summary>
        public ProgressBar ProgressBar
        {

            get
            {
                return _ProgressBar;
            }
            set
            {
                _ProgressBar = value;
            }

        }

        private ToolStripStatusLabel _PackInfo;
        /// <summary>
        /// 打包信息
        /// </summary>
        public ToolStripStatusLabel PackInfo
        {

            get
            {
                return _PackInfo;
            }
            set
            {
                _PackInfo = value;
            }

        }

        /// <summary>
        /// 把设备信息写入到数据库中
        /// </summary>
        /// <param name="EquipVdx">设备信息数组</param>
        /// <returns>写入成功返回true,失败返回false</returns>
        public bool WriteVdxInfo(EquipVdx[] equipVdx)
        {
            
            try
            {
                string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.dat");
                if (File.Exists(FilePath))
                {
                    File.Delete(FilePath);
                }
                string FilePath_mpg = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.mpg");
                if (File.Exists(FilePath_mpg))
                {
                    File.Delete(FilePath_mpg);
                }
                
                using (FileStream VdxStream = new FileStream(FilePath, FileMode.OpenOrCreate))
                {
                    FileStream packStream = new FileStream(FilePath_mpg, FileMode.OpenOrCreate);
                    ProgressBar.Visible = true;
                    ProgressBar.Value = 0;
                    int length = equipVdx.Length;
                    int step = ProgressBar.Maximum / length;

                    for (int i = 0; i < length; i++)
                    {
                        //
                        WriteVdxToPackage(ref equipVdx[i], ref packStream);
                        ProgressBar.Value += step;
                        PackInfo.Text = (i + 1) + "/" + length.ToString();
                        Application.DoEvents();
                    }                    
                    BinaryFormatter bf = new BinaryFormatter();
                    bf.Serialize(VdxStream, equipVdx);
                    VdxStream.Close();
                    packStream.Flush();
                    packStream.Close();
                    packStream.Dispose();

                    ProgressBar.Value = ProgressBar.Maximum;
                    ProgressBar.Visible = false;
                    PackInfo.Text = string.Empty;
                }
                //压缩dat文件
                string tempFilePath = "c:\\SiteView.tmp";
                FileStream inStream = File.OpenRead(FilePath);
                FileStream outStream = File.Create(tempFilePath);
                DataManager.Compress(inStream, outStream);
                inStream.Close();
                outStream.Close();
                File.Delete(FilePath);
                File.Move(tempFilePath, FilePath);
            }
            catch (Exception ex)
            {
                Log.WriteLog("写入设备信息出错！错误： " + ex.ToString());
                ProgressBar.Visible = false;
                return false;
            }
            return true;

        }

        /// <summary>
        /// 根据设备oid号,从数据库中返回设备信息
        /// </summary>
        /// <param name="Sysoid">设备OID</param>
        /// <param name="EquipVdx">设备信息</param>
        /// <returns>读取成功返回true,失败返回false</returns>
        public bool ReadVdxInfo(ref EquipVdx equipVdx)
        {

            try
            {
                //清理历史vdx文件
                foreach (string vdx in Directory.GetFiles(Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\"), "*.vdx"))
                {
                    File.Delete(vdx);
                }

                string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.dat");
                string tempFilePath = "c:\\SiteView.tmp";
                FileStream inStream = File.OpenRead(FilePath);
                FileStream outStream = File.Create(tempFilePath);
                DataManager.Decompress(inStream, outStream);

                using (FileStream VdxStream = new FileStream(tempFilePath, FileMode.OpenOrCreate))
                {
                    BinaryFormatter bf = new BinaryFormatter();
                    EquipVdx[] eqVdx = (EquipVdx[])bf.Deserialize(VdxStream);
                    for (int i = 0; i < eqVdx.Length; i++)
                    {
                        if (eqVdx[i].Sysoid == equipVdx.Sysoid)
                        {
                            equipVdx = eqVdx[i];
                            ReadVdxFromPackage(ref equipVdx);
                            break;
                        }
                    }
                    VdxStream.Close();
                }
            }
            catch (Exception ex)
            {
                Log.WriteLog("读取设备信息出错！错误： " + ex.ToString());
                return false;
            }

            return true;

        }

        /// <summary>
        /// 打包设备Vdx文件
        /// </summary>
        /// <param name="VdxFileName">要打包的Vdx文件信息</param>
        /// <returns>打包成功返回true,失败返回false</returns>
        private bool WriteVdxToPackage(ref EquipVdx equipVdx, ref FileStream packStream)
        {

            try
            {
                //string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.mpg");
                //using (FileStream packStream = new FileStream(FilePath, FileMode.OpenOrCreate))
                {
                    equipVdx.PackIndex = packStream.Length;
                    //压缩文件
                    using (FileStream inStream = File.OpenRead(equipVdx.tempFileName))
                    {
                        FileStream coStream = File.Create("c:\\VisioCo.tmp");
                        if (!DataManager.Compress(inStream, coStream))
                        {
                            return false;
                        }
                        //写入包中
                        coStream = File.OpenRead("c:\\VisioCo.tmp");
                        byte[] coVdx = new byte[coStream.Length];
                        int size = coStream.Read(coVdx, 0, coVdx.Length);
                        byte[] enVdx;
                        //加密
                        if (!DataManager.Encrypt(coVdx, out enVdx))
                        {
                            return false;
                        }

                        packStream.Position = packStream.Length;
                        packStream.Write(enVdx, 0, enVdx.Length);
                        equipVdx.PackLength = enVdx.Length;

                        inStream.Close();
                        coStream.Close();
                        coStream.Dispose();
                    }
                    //packStream.Flush();
                    //packStream.Close();
                }
                //File.Delete("c:\\VisioEn.tmp");
                File.Delete("c:\\VisioCo.tmp");
            }
            catch (Exception ex)
            {
                Log.WriteLog("打包设备信息出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// 解包设备Vdx
        /// </summary>
        /// <param name="VdxFileName">解包出来的Vdx文件信息</param>
        /// <returns>解包成功返回true,失败返回false</returns>
        private bool ReadVdxFromPackage(ref EquipVdx equipVdx)
        {

            try
            {
                string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.mpg");
                string vdxFilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("data\\" + equipVdx.FileName));
                using (FileStream packStream = File.OpenRead(FilePath))
                {
                    //从包中取出
                    byte[] packVdx = new byte[packStream.Length];
                    int size = packStream.Read(packVdx, 0, packVdx.Length);
                    using (FileStream coStream = File.Create("c:\\VisioCo.tmp"))
                    {
                        //解密
                        FileStream enStream = File.Create("c:\\VisioEn.tmp");
                        enStream.Write(packVdx, Convert.ToInt32(equipVdx.PackIndex), Convert.ToInt32(equipVdx.PackLength));
                        enStream.Flush();
                        enStream.Close();
                        byte[] coVdx = new byte[equipVdx.PackLength];
                        enStream = File.OpenRead("c:\\VisioEn.tmp");
                        enStream.Read(coVdx, 0, coVdx.Length);
                        byte[] enVdx;
                        if (!DataManager.Decrypt(coVdx, out enVdx))
                        {
                            return false;
                        }
                        coStream.Write(enVdx, 0, enVdx.Length);
                        //解压缩文件
                        coStream.Position = 0;
                        using (FileStream outStream = File.Create(vdxFilePath))
                        {
                            if (!DataManager.Decompress(coStream, outStream))
                            {
                                return false;
                            }
                            outStream.Close();
                        }

                        equipVdx.tempFileName = vdxFilePath;

                        enStream.Dispose();
                        coStream.Close();
                    }
                }

                File.Delete("c:\\VisioCo.tmp");
                File.Delete("c:\\VisioEn.tmp");
            }
            catch (Exception ex)
            {
                Log.WriteLog("解包设备信息出错！错误： " + ex.ToString());
                return false;
            }
            return true;

        }

    }

}
