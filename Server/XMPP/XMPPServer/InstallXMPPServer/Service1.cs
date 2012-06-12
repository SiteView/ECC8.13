using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;

using System.Threading;
using System.Windows.Forms;
namespace WindowsService1
{

    public partial class Service1 : ServiceBase
    {
        //private XmppServer server = null;
        Process p = null;
        public Service1()
        {
              try
              {
                    InitializeComponent();
                    //server = new XmppServer();
                    //Process p = new Process();
              }
              catch (Exception ex)
              {
                    MessageBox.Show(ex.ToString());
              }
        }

        protected override void OnStart(string[] args)
        {
              try
              {
                    //ThreadStart ts = new ThreadStart(Start);
                    //Thread td = new Thread(ts);
                    //td.Start();
                    Excute("");
              }
              catch (Exception ex)
              {
                    //MessageBox.Show(ex.ToString());
              }
        }

          private void Start()
          {
                try
                {
                      //server.StartService();
                }
                catch (Exception ex)
                {
                      MessageBox.Show(ex.ToString());
                }
               
          }

        protected override void OnStop()
        {
              //try
              //{
              //      server.StopService();
              //}
              //catch (Exception ex)
              //{
              //      MessageBox.Show(ex.ToString());
              //}

              try
              {
                    p.Kill();
                    p.Close();
              }
              catch (Exception e)
              {
                    ;
              }
        }

          public void Excute(string cmdText)
          {
                try
                {

                      p = new Process();

                      p.StartInfo.WorkingDirectory = AppDomain.CurrentDomain.BaseDirectory;
                      //MessageBox.Show(AppDomain.CurrentDomain.BaseDirectory);
                      p.StartInfo.FileName = AppDomain.CurrentDomain.BaseDirectory + "SubServer.exe";
                      //p.StartInfo.FileName = "E:\\工作代码及文件资料\\缓存\\SubServer\\bin\\Debug\\SubServer.exe";
                      p.StartInfo.UseShellExecute = false;

                      p.StartInfo.RedirectStandardInput = true;

                      p.StartInfo.RedirectStandardOutput = true;

                      p.StartInfo.RedirectStandardError = true;

                      p.StartInfo.CreateNoWindow = true;

                      p.Start();
                      //server = new XmppServer();
                      //server.StartService();
                      //p.StandardInput.WriteLine("\"" + cmdText + "\"");
                      //p.StandardInput.WriteLine("exit");
                      //while (!p.HasExited)
                      //{
                      //    p.WaitForExit();
                      //}
                      //p.Close();
                }
                catch (Exception e)
                {
                      ;
                }
          }
    }
}
