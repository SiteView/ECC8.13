using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Collections;

namespace Logistics
{
    namespace SubServer
    {
        public partial class Main : Form
        {
            private XmppServer server = null;
            private Dictionary<string, RichTextBox> outputList;

            public Main()
            {
                InitializeComponent();

                outputList = new Dictionary<string, RichTextBox>();
                
                ///≈‰÷√œÍœ∏º”‘ÿ
                ConfigManager.Load();//gt
                
                server = new XmppServer();
                //server.ClientStart = ClientStartHandler;//gt
                //server.ClientEnd = ClientEndHandler;//gt
                //server.Output = OutputHandler;//gt

                this.btnStart.Enabled = true;
                this.btnStop.Enabled = false;

            }

            private void Start()
            {
                server.StartService();
            }

              public void ServerStart()
              {
                    ThreadStart ts = new ThreadStart(Start);
                    Thread td = new Thread(ts);
                    td.Start();

              }
            private void btnStart_Click(object sender, EventArgs e)
            {
                ThreadStart ts = new ThreadStart(Start);
                Thread td = new Thread(ts);
                td.Start();

                //server.StartService();

                this.btnStart.Enabled = false;
                this.btnStop.Enabled = true;
            }

            private void btnStop_Click(object sender, EventArgs e)
            {
                server.StopService();
                this.btnStart.Enabled = true;
                this.btnStop.Enabled = false;
            }

            //private void ClientStartHandler(XmppSeverConnection conn)
            //{
            //      ArrayList parameters = new ArrayList();
            //      parameters.Add(conn);

            //      BeginInvoke(new UpdateUIHandler(UpdateUI), new object[] { EventType.Start, parameters });

            //}

            //private void ClientEndHandler(XmppSeverConnection conn)
            //{
            //      ArrayList parameters = new ArrayList();
            //      parameters.Add(conn);

            //      BeginInvoke(new UpdateUIHandler(UpdateUI), new object[] { EventType.End, parameters });

            //}
            //private void OutputHandler(XmppSeverConnection conn, string strType, string strData)
            //{
            //      ArrayList parameters = new ArrayList();
            //      parameters.Add(conn);
            //      parameters.Add(strType);
            //      parameters.Add(strData);

            //      BeginInvoke(new UpdateUIHandler(UpdateUI), new object[] { EventType.Output, parameters });

            //}

            //private enum EventType
            //{
            //      Start,
            //      End,
            //      Output
            //}

            //private delegate void UpdateUIHandler(EventType eventType, ArrayList parameters);

            //private void UpdateUI(EventType eventType, ArrayList parameters)
            //{
            //      XmppSeverConnection conn = parameters[0] as XmppSeverConnection;
            //      switch (eventType)
            //      {
            //            case EventType.Start:
            //                  StartEventHandler(conn);
            //                  break;
            //            case EventType.End:
            //                  EndEventHandler(conn);
            //                  break;
            //            case EventType.Output:
            //                  string strType = parameters[1] as string;
            //                  string strData = parameters[2] as string;
            //                  OutputEventHandler(conn, strType, strData);
            //                  break;
            //            default:
            //                  break;
            //      }

            //      parameters.Clear();
            //      parameters = null;

            //}


            //private void StartEventHandler(XmppSeverConnection conn)
            //{
            //      string strKey = conn.ClientIPAddress + "@" + conn.SessionId;
            //      if (!this.tabClientConn.TabPages.ContainsKey(strKey))
            //      {

            //            TabPage page = new TabPage(strKey);
            //            this.tabClientConn.TabPages.Add(page);

            //            RichTextBox console = new RichTextBox();
            //            outputList.Add(strKey, console);
            //            page.Controls.Add(console);
            //            console.Dock = DockStyle.Fill;
            //      }
            //}

            //private void EndEventHandler(XmppSeverConnection conn)
            //{
            //      string strKey = conn.ClientIPAddress + "@" + conn.SessionId;
            //      foreach (TabPage page in this.tabClientConn.TabPages)
            //      {
            //            if (page.Text == strKey)
            //            {

            //                  page.Controls.Clear();

            //                  this.tabClientConn.TabPages.Remove(page);

            //                  outputList.Remove(strKey);
            //            }
            //      }

            //}

            //private void OutputEventHandler(XmppSeverConnection conn, string strType, string strData)
            //{
            //      string strKey = conn.ClientIPAddress + "@" + conn.SessionId;
            //      if (this.outputList.ContainsKey(strKey))
            //      {
            //            this.outputList[strKey].SelectionStart = this.outputList[strKey].Text.Length;
            //            this.outputList[strKey].SelectionLength = 0;
            //            if (strType == "Sending")
            //            {
            //                  this.outputList[strKey].SelectionColor = Color.Blue;
            //            }
            //            else
            //            {
            //                  this.outputList[strKey].SelectionColor = Color.Red;
            //            }
            //            this.outputList[strKey].AppendText(strType + ":");

            //            this.outputList[strKey].SelectionStart = this.outputList[strKey].Text.Length;
            //            this.outputList[strKey].SelectionLength = 0;
            //            this.outputList[strKey].SelectionColor = Color.Black;
            //            this.outputList[strKey].AppendText(strData);
            //            this.outputList[strKey].AppendText("\r\n\r\n");

            //      }
            //}

            private void Main_FormClosing(object sender, FormClosingEventArgs e)
            {
                if (this.btnStop.Enabled)
                {
                    server.StopService();
                }
            }
            
        }
    }
}