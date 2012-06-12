using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using SiteView.Ecc.Core;
using SiteView.Ecc.WSClient;
namespace MyAddin5
{
      class SendToWebSevice
      {
            private System.ComponentModel.BackgroundWorker SendVdxFile;
            public SendToWebSevice()
            {

                  SendVdxFile = new System.ComponentModel.BackgroundWorker();
                  SendVdxFile.DoWork += new System.ComponentModel.DoWorkEventHandler(SendVdxFile_DoWork);
                  SendVdxFile.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(SendVdxFile_RunWorkerCompleted);
            }

            void SendVdxFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
            {
                  if (sendWait != null && !sendWait.IsDisposed)
                  {
                        sendWait.Close();
                        sendWait.Dispose();
                  }
            }

            void SendVdxFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
            {

                  string FilePath = (e.Argument as string[])[0];
                  string FileName = (e.Argument as string[])[1];
                  SiteView.Ecc.Core.UserPermissionContext.Instance.Url = "http://218.249.196.87:18080/webservice/InterfaceEccService";
                  Helper.NeedDecoding = true;

                  UserPermissionContext.Instance.CurrentUser = new SiteView.Ecc.Core.Models.User();
                  UserPermissionContext.Instance.CurrentUser.UserName = "管理员";
                  UserPermissionContext.Instance.CurrentUser.LoginName = "admin";



                  SiteView.Ecc.WSClient.TuopuDaoImpl TuopuDao = new SiteView.Ecc.WSClient.TuopuDaoImpl();
                  //TuopuDao.UploadTuopuFile();
                  try
                  {
                        //      //if (!File.Exists("c:\\temp.vdx")) 
                        //      //{
                        //      //      File.Create("c:\\temp.vdx");
                        //      //}
                        File.Copy(FilePath, "c:\\" + FileName, true);
                        //      FileStream fs = File.Open("c:\\temp.vdx", FileMode.Open, FileAccess.Read);
                        //      byte[] file = new byte[fs.Length];
                        //      fs.Read(file, 0, file.Length);
                        //      TuopuDao.UploadTuopuFile(file, "\\..\\TuopuList\\gongtao.zip", true);
                        //      fs.Dispose();
                        string tmpName = FileName.Split(new char[] { '.' })[0];

                        //TuopuDao.UploadTuopuFile("c:\\"+FileName, "\\..\\TuopuList\\"+tmpName+".zip", true);
                        TuopuDao.UploadTuopuFile("c:\\" + FileName, "\\..\\TuopuList\\" + FileName + ".zip", true);
                        MessageBox.Show("上传成功");
                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.ToString());
                  }

            }

            frmSendWait sendWait = null;
            public void SendFile(string FilePath,string FileName,frmSendWait sendWait)
            {


                  this.sendWait = sendWait;
                  
                  string[] file = new string[2]{FilePath,FileName};
                  
                  SendVdxFile.RunWorkerAsync(file);
                  //SiteView.Ecc.Core.UserPermissionContext.Instance.Url = "http://218.249.196.87:18080/webservice/InterfaceEccService";
                  //Helper.NeedDecoding = true;

                  //UserPermissionContext.Instance.CurrentUser = new SiteView.Ecc.Core.Models.User();
                  //UserPermissionContext.Instance.CurrentUser.UserName = "管理员";
                  //UserPermissionContext.Instance.CurrentUser.LoginName = "admin";



                  //SiteView.Ecc.WSClient.TuopuDaoImpl TuopuDao = new SiteView.Ecc.WSClient.TuopuDaoImpl();
                  ////TuopuDao.UploadTuopuFile();
                  //try
                  //{
                  ////      //if (!File.Exists("c:\\temp.vdx")) 
                  ////      //{
                  ////      //      File.Create("c:\\temp.vdx");
                  ////      //}
                  //      File.Copy(FilePath, "c:\\"+FileName, true);
                  ////      FileStream fs = File.Open("c:\\temp.vdx", FileMode.Open, FileAccess.Read);
                  ////      byte[] file = new byte[fs.Length];
                  ////      fs.Read(file, 0, file.Length);
                  ////      TuopuDao.UploadTuopuFile(file, "\\..\\TuopuList\\gongtao.zip", true);
                  ////      fs.Dispose();
                  //      string tmpName = FileName.Split(new char[] { '.' })[0];
                    
                  //      //TuopuDao.UploadTuopuFile("c:\\"+FileName, "\\..\\TuopuList\\"+tmpName+".zip", true);
                  //      TuopuDao.UploadTuopuFile("c:\\" + FileName, "\\..\\TuopuList\\" + FileName + ".zip", true);
                  //      MessageBox.Show("上传成功");
                  //}
                  //catch (Exception ex)
                  //{
                  //      MessageBox.Show(ex.ToString());
                  //}

                  
                  ////string context = "";
                  ////try
                  ////{
                  ////      FileStream fi = new FileStream(FilePath, FileMode.Open);
                  ////      StreamReader sr = new StreamReader(fi, Encoding.UTF8);

                  ////      byte[] contextByte = new byte[fi.Length];
                  ////      fi.Read(contextByte, 0, (int)fi.Length);

                  ////      //context = sr.ReadToEnd();
                  ////      fi.Read(contextByte, 0, (int)fi.Length);
                  ////      TuopuDao.UploadTuopuFile(contextByte, "\\..\\TuopuList\\gongtao.zip", true);
                  ////      //while (!sr.EndOfStream)
                  ////      //{
                  ////      //      string RecordLine = sr.ReadLine();
                  ////      //      sendMailAddressTmp.Add(RecordLine);
                  ////      //}
                  ////      sr.Close();
                  ////      fi.Close();
                  ////      MessageBox.Show("s");
                  ////}
                  ////catch (Exception ex)
                  ////{
                  ////      MessageBox.Show(ex.ToString());
                  ////}


            }

            public void SaveFile(string fileName)
            {
              
                
            }
      }
}
