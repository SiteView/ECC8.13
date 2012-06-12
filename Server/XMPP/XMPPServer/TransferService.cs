using System;
using System.Threading;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace Logistics
{
    namespace SubServer
    {
        public class TransferService : BaseService
        {
            private Dictionary<string, ByteStream> proxyList = null;

            private ManualResetEvent AllDone = null;
            private Socket listener = null;
            private bool bListening = false;

            public TransferService()
            {
                this.ServiceType = ServiceType.FileTransfer;
                this.proxyList = new Dictionary<string, ByteStream>();
                this.AllDone = new ManualResetEvent(false);
                this.listener = null;
                this.bListening = false;
            }

            public Dictionary<string, ByteStream> GetByteStreams()
            {
                return this.proxyList;
            }

            private void OnSocket5Processed(Socket5 sender, bool result)
            {
                List<string> keys = new List<string>();
                foreach (KeyValuePair<string, ByteStream> byteStream in this.proxyList)
                {
                    if (byteStream.Value.Initiator != null && byteStream.Value.Target != null)
                    {
                        if (!byteStream.Value.Initiator.Connected || !byteStream.Value.Target.Connected)
                        {
                            keys.Add(byteStream.Key);
                        }
                    }
                }

                foreach (string key in keys)
                {
                    this.proxyList.Remove(key);
                }

                keys.Clear();

                if (result)
                {
                    if (!this.proxyList.ContainsKey(sender.BindAddress))
                    {
                        ByteStream byteStream = new ByteStream();
                        byteStream.Target = sender.SocketConnection;
                        this.proxyList.Add(sender.BindAddress, byteStream);
                    }
                    else
                    {
                        ByteStream byteStream = this.proxyList[sender.BindAddress];
                        byteStream.Initiator = sender.SocketConnection;
                        this.proxyList[sender.BindAddress] = byteStream;
                    }
                }
                else
                {
                    sender.OnSocket5Processed -= new Socket5Handler(OnSocket5Processed);
                    sender.Stop();

                }
            }

            public void Start()
            {
                ThreadStart ts = new ThreadStart(StartService);
                Thread td = new Thread(ts);
                td.Start();
            }

            public void Stop()
            {
                AllDone.Set();
                this.bListening = false;

                foreach (ByteStream byteStream in this.proxyList.Values)
                {
                    byteStream.DisableByteStream();
                }

                this.proxyList.Clear();

                //listener.Shutdown(SocketShutdown.Both);
                listener.Close();
            }

            private void StartService()
            {
                AllDone.Set();
                this.bListening = true;

                IPEndPoint lep = new IPEndPoint(IPAddress.Any, 7777);
                listener = new Socket(lep.Address.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                listener.Bind(lep);
                listener.Listen(0);

                Listen();
            }

            private void Listen()
            {
                try
                {
                    Console.WriteLine(string.Empty);
                    Console.WriteLine(string.Empty);
                    Console.WriteLine("************************************************************************");
                    Console.WriteLine("***********************Proxy65 Server Start*****************************");
                    Console.WriteLine("************************************************************************");

                    while (this.bListening)
                    {
                        AllDone.Reset();

                        Console.WriteLine("File Transfer Server Waiting for a connection from client...");
                        listener.BeginAccept(new AsyncCallback(EndAccept), listener);

                        AllDone.WaitOne();
                    }

                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

            private void EndAccept(IAsyncResult ar)
            {
                if (!bListening)
                {
                    return;
                }

                // Retrieve the state object and the handler socket
                // from the async state object.
                Console.WriteLine("Socket Accepted");

                // Get the socket that handles the client request.
                Socket listener = (Socket)ar.AsyncState;
                Socket socket = listener.EndAccept(ar);

                Socket5 socket5 = new Socket5(socket);
                socket5.OnSocket5Processed += new Socket5Handler(OnSocket5Processed);
                socket5.Start();

                AllDone.Set();

            } 

        }//end class

    }//end SubServer

}//end Logistics