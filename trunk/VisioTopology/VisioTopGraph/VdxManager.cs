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
    /// �豸��Ϣ
    /// </summary>
    [Serializable]
    public struct EquipVdx
    {

        //�豸oid
        public string Sysoid;
        //�豸����
        public string Factory;
        //�豸�ͺ�
        public string Model;
        //�豸����
        //0, ���㽻����(·�ɽ�����)
        //1,���㽻����
        //2,·����
        //3,����ǽ
        public int Type;
        //�豸vdx�ļ���
        public string FileName;
        ///�豸vdx��ʱ�ļ�
        public string tempFileName;
        //������ʼλ��
        public long PackIndex;
        //���ĳ���
        public long PackLength;

    };

    public class VdxManager
    {

        //����Vdx��Ϣ�������ļ�
        private string _FileDat = string.Empty;
        private string _FileMpg = string.Empty;

        /// <summary>
        /// �������
        /// </summary>
        public VdxManager()
        {
            
        }

        /// <summary>
        /// �豸vdx��Ϣ�ļ�
        /// </summary>
        public string FileDat
        {

            set
            {
                _FileDat = value;
            }

        }

        /// <summary>
        /// �豸vdx�ļ������ļ�
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
        /// ��ȡ�����ý�����
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
        /// �����Ϣ
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
        /// ���豸��Ϣд�뵽���ݿ���
        /// </summary>
        /// <param name="EquipVdx">�豸��Ϣ����</param>
        /// <returns>д��ɹ�����true,ʧ�ܷ���false</returns>
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
                //ѹ��dat�ļ�
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
                Log.WriteLog("д���豸��Ϣ�������� " + ex.ToString());
                ProgressBar.Visible = false;
                return false;
            }
            return true;

        }

        /// <summary>
        /// �����豸oid��,�����ݿ��з����豸��Ϣ
        /// </summary>
        /// <param name="Sysoid">�豸OID</param>
        /// <param name="EquipVdx">�豸��Ϣ</param>
        /// <returns>��ȡ�ɹ�����true,ʧ�ܷ���false</returns>
        public bool ReadVdxInfo(ref EquipVdx equipVdx)
        {

            try
            {
                //������ʷvdx�ļ�
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
                Log.WriteLog("��ȡ�豸��Ϣ�������� " + ex.ToString());
                return false;
            }

            return true;

        }

        /// <summary>
        /// ����豸Vdx�ļ�
        /// </summary>
        /// <param name="VdxFileName">Ҫ�����Vdx�ļ���Ϣ</param>
        /// <returns>����ɹ�����true,ʧ�ܷ���false</returns>
        private bool WriteVdxToPackage(ref EquipVdx equipVdx, ref FileStream packStream)
        {

            try
            {
                //string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.mpg");
                //using (FileStream packStream = new FileStream(FilePath, FileMode.OpenOrCreate))
                {
                    equipVdx.PackIndex = packStream.Length;
                    //ѹ���ļ�
                    using (FileStream inStream = File.OpenRead(equipVdx.tempFileName))
                    {
                        FileStream coStream = File.Create("c:\\VisioCo.tmp");
                        if (!DataManager.Compress(inStream, coStream))
                        {
                            return false;
                        }
                        //д�����
                        coStream = File.OpenRead("c:\\VisioCo.tmp");
                        byte[] coVdx = new byte[coStream.Length];
                        int size = coStream.Read(coVdx, 0, coVdx.Length);
                        byte[] enVdx;
                        //����
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
                Log.WriteLog("����豸��Ϣ�������� " + ex.ToString());
                return false;
            }
            return true;

        }

        /// <summary>
        /// ����豸Vdx
        /// </summary>
        /// <param name="VdxFileName">���������Vdx�ļ���Ϣ</param>
        /// <returns>����ɹ�����true,ʧ�ܷ���false</returns>
        private bool ReadVdxFromPackage(ref EquipVdx equipVdx)
        {

            try
            {
                string FilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), "data\\SiteViewVdx.mpg");
                string vdxFilePath = Path.Combine(Path.GetFullPath(AppDomain.CurrentDomain.BaseDirectory), ("data\\" + equipVdx.FileName));
                using (FileStream packStream = File.OpenRead(FilePath))
                {
                    //�Ӱ���ȡ��
                    byte[] packVdx = new byte[packStream.Length];
                    int size = packStream.Read(packVdx, 0, packVdx.Length);
                    using (FileStream coStream = File.Create("c:\\VisioCo.tmp"))
                    {
                        //����
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
                        //��ѹ���ļ�
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
                Log.WriteLog("����豸��Ϣ�������� " + ex.ToString());
                return false;
            }
            return true;

        }

    }

}
