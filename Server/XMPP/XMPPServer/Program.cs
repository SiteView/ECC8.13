using System;
using System.Collections.Generic;
using System.Text;

using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;

namespace Logistics
{
    namespace SubServer
    {
        class Program
        {
            /// <summary>
            /// Der Haupteinstiegspunkt f�r die Anwendung.
            /// </summary>
            [STAThread]
            static void Main()
            {
                Application.EnableVisualStyles();
                Application.DoEvents();
                Main main = new Main();
                main.ServerStart();
                //ȥ�����ܻ���
               //GetSVDBDataBuffer.GetObj().StartProcess();
                Application.Run(main);
                
            }

            //static void Main()
            //{
            //    ///������ϸ����
            //    ConfigManager.Load();

            //    XmppServer server = new XmppServer();
            //    server.StartService();
            //}

        }
    }
}
