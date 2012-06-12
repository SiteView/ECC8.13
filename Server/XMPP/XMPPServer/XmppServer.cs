using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Net;

namespace Logistics
{
    namespace SubServer
    {

        public class XmppServer
        {
            internal AccountManager AccountManager;
            private AccountComparer accountcomparer;

            internal BaseService[] ServiceList;

            internal Dictionary<Account, Dictionary<string, XmppSeverConnection>> ClientConnections;
            internal static List<XmppSeverConnection> ClientConnectionList = new List<XmppSeverConnection>();
              internal static Dictionary<string, bool> ClientResponseList = new Dictionary<string, bool>();
              internal static Dictionary<XmppSeverConnection, string> GlobeEntityIdList = new Dictionary<XmppSeverConnection, string>();

            internal static Dictionary<string, XmppSeverConnection> ClientList = new Dictionary<string, XmppSeverConnection>();
            internal static Dictionary<string, XmppSeverConnection> ClientLoginNameList = new Dictionary<string,XmppSeverConnection>();
            internal static List<string> ClientLoginNameListTmp = new List<string>();
            internal static bool IsSendData = false;
             // internal static GetSVDBDataBuffer m_GetSVDBDataBuffer = null;
            internal Dictionary<agsXMPP.Jid, agsXMPP.protocol.client.Message> CacheMessages;
            internal Dictionary<agsXMPP.Jid, agsXMPP.protocol.client.Presence> CachePresences;

            private ManualResetEvent allDone;
            private Socket listener;
            private bool bListening;

            public ClientStartHandler ClientStart;
            public ClientEndHandler ClientEnd;
            public OutputHandler Output;

            public XmppServer()
            {
                ServiceManager serviceManager = new ServiceManager();
                ServiceList = serviceManager.Services;
                
                AccountManager = new AccountManager();

                foreach (BaseService service in this.ServiceList)
                {
                    Account serviceAccount = new Account();
                    serviceAccount.Type = AccountType.Service;
                    serviceAccount.Company = null;

                    if (service.ServiceType == ServiceType.FileTransfer)
                    {
                        TransferService trans = service as TransferService;
                        serviceAccount.UserName = trans.Name;
                        serviceAccount.UserID = trans.JID.ToString();                        
                    }
                    else if(service.ServiceType == ServiceType.ContactSearch)
                    {
                        SearchService search = service as SearchService;
                        serviceAccount.UserName = search.Name;
                        serviceAccount.UserID = search.JID.ToString();
                    }
                    else if (service.ServiceType == ServiceType.GroupChat)
                    {
                        MucService muc = service as MucService;
                        serviceAccount.UserName = muc.Name;
                        serviceAccount.UserID = muc.JID.ToString();
                    }
                    else
                    {

                    }

                    AccountManager.Accounts.Add(serviceAccount);

                }

                accountcomparer = new AccountComparer();
                ClientConnections = new Dictionary<Account, Dictionary<string, XmppSeverConnection>>(accountcomparer);

                CacheMessages = new Dictionary<agsXMPP.Jid, agsXMPP.protocol.client.Message>();

                CachePresences = new Dictionary<agsXMPP.Jid, agsXMPP.protocol.client.Presence>();

                allDone = new ManualResetEvent(false);

                //IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, ConfigManager.Port);

                //bListening = false;

                //// Create a TCP/IP socket.
                //listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                //listener.Bind(localEndPoint);
                //listener.Listen(100);

                //ThreadStart listenTS = new ThreadStart(Listen);
                //Thread listenTD = new Thread(listenTS);

                //listenTD.Start();

            }

            private T GetService<T>(ServiceType serviceType) 
                where T:BaseService
            {
                foreach (BaseService service in this.ServiceList)
                {
                    if (service.ServiceType == serviceType)
                    {
                        return service as T;
                    }
                }

                return null;
            }

            public SearchService GetSearchService()
            {
                SearchService result = GetService<SearchService>(ServiceType.ContactSearch);
                return result;
            }

            public TransferService GetTransferService()
            {
                TransferService result = GetService<TransferService>(ServiceType.FileTransfer);
                return result;
            }

            public MucService GetMucService()
            {
                MucService result = GetService<MucService>(ServiceType.GroupChat);
                return result;
            }

            public bool StartService()
            {


                //GetSVDBDataBuffer.GetObj().StartProcess();
                  
                TransferService trans = GetService<TransferService>(ServiceType.FileTransfer);
                if (trans != null)
                {
                    trans.Start();
                }
                  
                //IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, ConfigManager.Port);//gt
                int port = 5632;//gt
                IPAddress ServerIp = IPAddress.Any;//Dns.GetHostEntry(Dns.GetHostName()).AddressList[0];

                IPEndPoint localEndPoint = new IPEndPoint(ServerIp, port);//gt
                // Create a TCP/IP socket.
                listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                
                listener.Bind(localEndPoint);
                //listener.Bind(localEndPoint);
                //listener.Bind(localEndPoint);
                listener.Listen(100);

                bListening = true;
                //System.Windows.Forms.MessageBox.Show(ServerIp.ToString());
                //System.Windows.Forms.MessageBox.Show(Dns.GetHostEntry(Dns.GetHostName()).AddressList.Length.ToString());
                Listen();
                
                return true;
            }
            /// <summary>
            /// 深度拷贝数据类型
            /// </summary>
            /// <param name="obj">源对象</param>
            /// <returns>对象副本</returns>
            public static object GetDeepCopy(object obj)
            {

                  Object DeepCopyObj = null;

                  if (obj.GetType().IsValueType == true)//值类型
                  {
                        DeepCopyObj = obj;
                  }
                  else//引用类型
                  {
                        
                        DeepCopyObj = System.Activator.CreateInstance(obj.GetType()); //创建引用对象
                        System.Reflection.MemberInfo[] memberCollection = obj.GetType().GetMembers();

                        foreach (System.Reflection.MemberInfo member in memberCollection)
                        {
                              /*if (member.MemberType == System.Reflection.MemberTypes.Field)
                              {
                                  System.Reflection.FieldInfo field = (System.Reflection.FieldInfo)member;
                                  Object fieldValue = field.GetValue(obj);
                                  field.SetValue(DeepCopyObj, GetDeepCopy(fieldValue));
                              }*/
                              if (member.MemberType == System.Reflection.MemberTypes.Field)
                              {
                                    System.Reflection.FieldInfo field = (System.Reflection.FieldInfo)member;
                                    Object fieldValue = field.GetValue(obj);

                                    if (fieldValue is ICloneable)
                                    {
                                          field.SetValue(DeepCopyObj, (fieldValue as ICloneable).Clone());
                                    }
                                    else
                                    {
                                          field.SetValue(DeepCopyObj, GetDeepCopy(fieldValue));
                                    }
                              }

                        }
                  }

                  return DeepCopyObj;

            }
            public bool StopService()
            {
                TransferService trans = GetService<TransferService>(ServiceType.FileTransfer);
                if (trans != null)
                {
                    trans.Stop();
                }

                bListening = false;

                //internal Dictionary<Account, Dictionary<string, XmppSeverConnection>> ClientConnections;
                foreach (Dictionary<string, XmppSeverConnection> item in this.ClientConnections.Values)
                {
                    if (item.Values.Count > 0)
                    {
                        XmppSeverConnection[] connections = new XmppSeverConnection[item.Values.Count];
                        item.Values.CopyTo(connections, 0);
                        foreach (XmppSeverConnection conn in connections)
                        {
                            conn.Stop();
                        }

                        item.Clear();
                    }
                }

                listener.Close();

                this.ClientConnections.Clear();
                this.CacheMessages.Clear();
                this.CachePresences.Clear();
                if (ClientConnectionList != null)
                {
                      ClientConnectionList.Clear();
                }
                return true;
            }

            public bool ResetService()
            {
                return true;
            }

            private void Listen()
            {
                // Bind the socket to the local endpoint and listen for incoming connections.
                try
                {
                    //Console.WriteLine("************************************************************************");
                    //Console.WriteLine("*************************Xmpp Server Start******************************");
                    //Console.WriteLine("************************************************************************");

                    //while (bListening)
                    //{

                    //    // Set the event to nonsignaled state.
                    //    allDone.Reset();

                    //    // Start an asynchronous socket to listen for connections.
                    //    Console.WriteLine("Xmpp Server Waiting for a connection from client...");
                    //    listener.BeginAccept(new AsyncCallback(AcceptCallback), null);

                    //    // Wait until a connection is made before continuing.

                    //    allDone.WaitOne();

                    //}
                    listener.BeginAccept(new AsyncCallback(AcceptCallback), null);


                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }

            }

            private void AcceptCallback(IAsyncResult ar)
            {
                // Signal the main thread to continue.
                  try
                  {
                        //GetSVDBDataBuffer.GetObj().StartProcess();
                        allDone.Set();

                        if (!bListening)
                        {
                              return;
                        }

                        // Get the socket that handles the client request.
                        Socket clientSock = listener.EndAccept(ar);
                        
                   
                        XmppSeverConnection clientConnection = new XmppSeverConnection(this, clientSock);

                        clientConnection.OnClientStart += new ClientStartHandler(clientConnection_OnClientStart);
                        clientConnection.OnClientEnd += new ClientEndHandler(clientConnection_OnClientEnd);
                        clientConnection.OnOutput += new OutputHandler(clientConnection_OnOutput);
                        //clientConnection.Send("asd");
                        //ClientConnections.Add(clientConnection);
                        XmppSeverConnection tmp = null;
                        for (int i = 0; i < ClientConnectionList.Count; i++)
                        {
                            if (!ClientConnectionList[i].m_Sock.Connected)
                            {
                                tmp = ClientConnectionList[i];
                                break;
                            }
                        }
                        if (tmp != null)
                        {
                            ClientConnectionList.Remove(tmp);
                        }
                        ClientConnectionList.Add(clientConnection);
                        
                        listener.BeginAccept(new AsyncCallback(AcceptCallback), null);
                        //Socket tmp = GetDeepCopy(clientSock) as Socket; ;
                        
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—Add—ClientConnectionList" + "—" + ClientConnectionList.Count.ToString());
                  }
                  catch (Exception ex)
                  {
                        listener.BeginAccept(new AsyncCallback(AcceptCallback), null);
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppServer" + "—AcceptCallback" + "—" + ex.Message);
                        //System.Windows.Forms.MessageBox.Show("AcceptCallback" + "----" + ex.ToString());
                  }
            }
             

            void clientConnection_OnClientStart(XmppSeverConnection conn)
            {
                if (ClientStart != null)
                {
                    ClientStart(conn);
                }
            }

            void clientConnection_OnClientEnd(XmppSeverConnection conn)
            {
                if (ClientEnd != null)
                {
                    ClientEnd(conn);
                }
            }

            void clientConnection_OnOutput(XmppSeverConnection conn, string strType, string strData)
            {
                if (Output != null)
                {
                    Output(conn, strType, strData);
                }
            }

        }
    }
}
