using System;
using System.IO;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Microsoft.Win32;

using agsXMPP;
using agsXMPP.Xml;
using agsXMPP.Xml.Dom;
using agsXMPP.protocol;
using agsXMPP.protocol.tls;
using agsXMPP.protocol.client;
using agsXMPP.protocol.stream;
using agsXMPP.protocol.stream.feature;
using agsXMPP.protocol.x.data;
using agsXMPP.protocol.iq;
using agsXMPP.protocol.iq.auth;
using agsXMPP.protocol.iq.roster;
using agsXMPP.protocol.iq.vcard;
using agsXMPP.protocol.iq.disco;
using agsXMPP.protocol.iq.agent;
using agsXMPP.protocol.iq.search;
using agsXMPP.protocol.extensions.si;
using agsXMPP.protocol.extensions.bytestreams;


namespace Logistics
{
    namespace SubServer
    {

        public delegate void ClientStartHandler(XmppSeverConnection conn);
        public delegate void ClientEndHandler(XmppSeverConnection conn);
        public delegate void OutputHandler(XmppSeverConnection conn, string strType, string strData);
        
        /// <summary>
        /// XMPPSeverConnection.
        /// </summary>
        public class XmppSeverConnection
        {
            //int TeccInterface(char *licStr, char *key)
            [DllImport("eccInterface.dll")]
            //private static extern int TeccInterface(byte[] licStr, byte[] key);
            private static extern int TeccInterface(string licStr, string key);
            
            #region << Constructors >>
            public XmppSeverConnection()
            {
                m_StreamParser = new StreamParser();
                m_StreamParser.OnStreamStart += new StreamHandler(StreamParser_OnStreamStart);
                m_StreamParser.OnStreamEnd += new StreamHandler(StreamParser_OnStreamEnd);
                m_StreamParser.OnStreamElement += new StreamHandler(StreamParser_OnStreamElement);
                m_StreamParser.OnStreamRead += new streamRead(m_StreamParser_OnStreamRead);//gt
            }

              
            public XmppSeverConnection(XmppServer server, Socket sock)
                : this()
            {
                this.m_SessionId = SessionID.CreateNewId();

                this.strClientIP = ((IPEndPoint)sock.RemoteEndPoint).Address.ToString();
               
                m_Sock = sock;
                m_Server = server;
                m_Sock.BeginReceive(buffer, 0, BUFFERSIZE, 0, new AsyncCallback(ReadCallback), null);

                m_AuthenticatedClient = false;

            }
            #endregion

            private string strClientIP;
            public string ClientIPAddress
            {
                get
                {
                    return strClientIP;
                }
            }

            private string strClientVersion;
            private System.Globalization.CultureInfo objClientlanguage;

            public event ClientStartHandler OnClientStart;
            public event ClientEndHandler OnClientEnd;
            public event OutputHandler OnOutput;

            public Socket m_Sock;
            private XmppServer m_Server;
            private StreamParser m_StreamParser;

            private string strBindResource = null;
            private string tempAuthName = null;
            private agsXMPP.protocol.sasl.MechanismType clientMechanismType;

            private const int BUFFERSIZE = 8192;
            private byte[] buffer = new byte[BUFFERSIZE];

            private bool m_AuthenticatedClient;
            private Account m_ClientAccount;

            public void ReadCallback(IAsyncResult ar)
            {
                try
                {
                    // Retrieve the state object and the handler socket
                    // from the asynchronous state object

                    // Read data from the client socket. 
                      
                      if (this.m_Sock == null)
                      {
                            if (XmppServer.ClientConnectionList.Count > 0 && XmppServer.ClientConnectionList.Contains(this))
                            {
                                  XmppServer.ClientConnectionList.Remove(this);
                                  ErrorLog Log = new ErrorLog();
                                  Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—ReadCallback");
                                  return;
                            }
                      }
                      
                    int bytesRead = 0;
                    if (m_Sock.Connected)
                    {
                        bytesRead = m_Sock.EndReceive(ar);
                    }

                    if (bytesRead > 0)
                    {
                        //string strTemp = Encoding.Default.GetString(buffer, 0, bytesRead);
                        //if (strTemp == "<Scan><Query>CompanyID</Query></Scan>")
                        //{
                        //    byte[] byteData = Encoding.UTF8.GetBytes(ConfigManager.Company.ID);

                        //    // Begin sending the data to the remote device.
                        //    m_Sock.Send(byteData);

                        //    m_Sock.Close();

                        //    return;
                        //}
                         
                        m_StreamParser.Push(buffer, 0, bytesRead);

                        if (m_Sock.Connected)
                        {
                            // Not all data received. Get more.
                            m_Sock.BeginReceive(buffer, 0, BUFFERSIZE, 0, new AsyncCallback(ReadCallback), null);
                        }
                    }
                    else
                    {
                        //m_Sock.Shutdown(SocketShutdown.Both);
                        m_Sock.Close();
                    }
                }
                catch (SocketException se)
                {
                    //Console.WriteLine(se.Message);
                    EndClientConnection();
                }
            }

            private void SendCallback(IAsyncResult ar)
            {
                try
                {
                    //// Complete sending the data to the remote device.
                    //int bytesSent = m_Sock.EndSend(ar);
                    ////Console.WriteLine("Sent {0} bytes to client.", bytesSent);

                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

            public void Send(string data)
            {
                // Convert the string data to byte data using ASCII encoding.
                  try
                  {
                        if (this.m_Sock == null)
                        {
                              if (XmppServer.ClientConnectionList.Count > 0 && XmppServer.ClientConnectionList.Contains(this))
                              {
                                    XmppServer.ClientConnectionList.Remove(this);
                                    ErrorLog Log = new ErrorLog();
                                    Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—Send1");
                                    return;
                              }
                        }
                        
                        byte[] byteData = Encoding.UTF8.GetBytes(data);

                        ErrorLog Log1 = new ErrorLog();
                        string tmp = data.Replace("g", "组");
                        tmp = tmp.Replace("a", "添加");
                        tmp = tmp.Replace("e", "设备");
                        tmp = tmp.Replace("m", "监测器");
                        tmp = tmp.Replace("d", "删除");
                        if (!data.Contains("test"))
                        {


                              Log1.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—BSend—" + m_Sock.RemoteEndPoint.ToString() + "—" + tmp.Trim(new char[1] { '\0' }));

                        }
                        m_Sock.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), null);
                        if (!data.Contains("test"))
                        {
                              Log1.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—ASend—" + m_Sock.RemoteEndPoint.ToString() + "—" + tmp.Trim(new char[1] { '\0' }));
                        }
                        
                  }
                  catch (Exception ex)
                  {
                        
                        if (XmppServer.ClientConnectionList.Count > 0 && XmppServer.ClientConnectionList.Contains(this))
                        {
                              XmppServer.ClientConnectionList.Remove(this);
                        }
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—Send" + "—" + ex.Message);
                  }

                //Console.WriteLine("");
                //Console.WriteLine("=========================sending==========================");
                //Console.WriteLine(data);

                //if (this.OnOutput != null)
                //{
                //    this.OnOutput(this, "Sending", data);
                //}

            }

            private void Send(Element el)
            {
                Send(el.ToString());
            }

            private void SendOpenStream()
            {

                //// Recv:<stream:stream xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' from='myjabber.net' id='1075705237'>

                //// Send the Opening Strem to the client
                //string ServerDomain = ConfigManager.Server;

                ////this.SessionId = SessionID.CreateNewId();

                //StringBuilder sb = new StringBuilder();

                //sb.Append("<stream:stream from='");
                //sb.Append(ServerDomain);

                //sb.Append("' xmlns='");
                //sb.Append(agsXMPP.Uri.CLIENT);

                //sb.Append("' xmlns:stream='");
                //sb.Append(agsXMPP.Uri.STREAM);

                //sb.Append("' id='");
                //sb.Append(this.SessionId);

                //if (this.strClientVersion != null)
                //{
                //    sb.Append("' version='");
                //    sb.Append(this.strClientVersion);
                //}

                //sb.Append("' xml:lang='");
                //sb.Append(this.objClientlanguage.Name.Replace('-', '_'));

                //sb.Append("'>");

                //Send(sb.ToString());

                //sb.Remove(0, sb.Length);

                //if (this.strClientVersion != null && float.Parse(this.strClientVersion) >= float.Parse("1.0"))
                //{
                //    Features features = new Features();
                //    features.Prefix = "stream";

                //    if (!this.m_AuthenticatedClient)
                //    {

                //        Register regster = new Register();
                //        features.Register = regster;

                //        //StartTls tls = new StartTls();
                //        //features.StartTls = tls;

                //        Element auth = new Element("auth");
                //        auth.Namespace = agsXMPP.Uri.FEATURE_IQ_AUTH;
                //        features.AddChild(auth);

                //        agsXMPP.protocol.sasl.Mechanisms mechanisms = new agsXMPP.protocol.sasl.Mechanisms();

                //        agsXMPP.protocol.sasl.Mechanism mechanism = null;

                //        mechanism = new agsXMPP.protocol.sasl.Mechanism(agsXMPP.protocol.sasl.MechanismType.PLAIN);
                //        mechanisms.AddMechanism(mechanism);

                //        mechanism = new agsXMPP.protocol.sasl.Mechanism(agsXMPP.protocol.sasl.MechanismType.DIGEST_MD5);
                //        mechanisms.AddMechanism(mechanism);

                //        //mechanism = new agsXMPP.protocol.sasl.Mechanism(agsXMPP.protocol.sasl.MechanismType.ANONYMOUS);
                //        //mechanisms.AddMechanism(mechanism);

                //        //mechanism = new agsXMPP.protocol.sasl.Mechanism(agsXMPP.protocol.sasl.MechanismType.X_GOOGLE_TOKEN);
                //        //mechanisms.AddMechanism(mechanism);

                //        features.Mechanisms = mechanisms;
                //    }
                //    else
                //    {
                //        agsXMPP.protocol.iq.bind.Bind bind = new agsXMPP.protocol.iq.bind.Bind();
                //        agsXMPP.protocol.iq.session.Session session = new agsXMPP.protocol.iq.session.Session();
                //        agsXMPP.protocol.stream.feature.compression.Compression compression = new agsXMPP.protocol.stream.feature.compression.Compression();
                //        compression.AddMethod(agsXMPP.protocol.extensions.compression.CompressionMethod.zlib);

                //        features.Bind = bind;
                //        features.AddChild(session);
                //        //features.Compression = compression;
                //    }

                //    sb.Append(features.ToString());
                //}

                //if (sb.Length > 0)
                //{
                //    Send(sb.ToString());
                //}

            }

            private void EndClientConnection()
            {

                  try
                  {
                        if (XmppServer.ClientConnectionList != null && XmppServer.ClientConnectionList.Count > 0)
                        {
                              if(XmppServer.ClientConnectionList.Contains(this))
                              {
                               XmppServer.ClientConnectionList.Remove(this);
                              }
                              if(XmppServer.GlobeEntityIdList.ContainsKey(this))
                              {
                                    XmppServer.GlobeEntityIdList.Remove(this);
                              }
                              ErrorLog Log = new ErrorLog();
                              Log.WriteFiles(DateTime.Now.ToString() + "—Delete—ClientConnectionList" + "—" + XmppServer.ClientConnectionList.Count.ToString());
                        }

                        if (XmppServer.ClientLoginNameList.Count > 0)
                        {
                              string UserName = "";
                              foreach (string key in XmppServer.ClientLoginNameList.Keys)
                              {
                                    if (XmppServer.ClientLoginNameList[key].m_Sock.RemoteEndPoint.ToString().Split(new char[1] { ':' })[0] == this.m_Sock.RemoteEndPoint.ToString().Split(new char[1] { ':' })[0])
                                    {
                                          UserName = key;
                                          break;

                                    }
                              }

                              if (XmppServer.ClientLoginNameList.ContainsKey(UserName))
                              {
                                    XmppServer.ClientLoginNameList.Remove(UserName);
                              }
                        }
                        if (this.m_ClientAccount != null)
                        {
                              if (this.m_Server.ClientConnections[this.m_ClientAccount].ContainsKey(this.strBindResource))
                              {
                                    this.m_Server.ClientConnections[this.m_ClientAccount].Remove(this.strBindResource);
                              }

                              Presence newPresence = new Presence();
                              newPresence.Type = PresenceType.unavailable;
                              newPresence.From = this.m_ClientAccount.JID;

                              foreach (Friend friend in this.m_ClientAccount.Friends)
                              {
                                    Send(friend.JID, newPresence);
                              }
                        }

                        if (this.OnClientEnd != null)
                        {
                              this.OnClientEnd(this);
                        }

                        //m_Sock.Shutdown(SocketShutdown.Both);
                        if (m_Sock.Connected)
                        {
                              m_Sock.Shutdown(SocketShutdown.Both);
                              m_Sock.Close();
                        }

                  }
                  catch (Exception ex)
                  {
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—EndClientConnection" + "—" + ex.Message);
                        //System.Windows.Forms.MessageBox.Show("EndClientConnection" + "----" + ex.ToString());

                  }
                //Console.WriteLine("Close");
            }

            public void Stop()
            {
                Send("</stream:stream>");
                //			client.Close();
                //			_TcpServer.Stop();

                //m_Sock.Shutdown(SocketShutdown.Both);
                //m_Sock.Close();

                EndClientConnection();
            }

            #region << Properties and Member Variables >>
            //		private int			m_Port			= 5222;		
            private string m_SessionId = null;

            public string SessionId
            {
                get
                {
                    return m_SessionId;
                }
                set
                {
                    m_SessionId = value;
                }
            }
            #endregion

            private void StreamParser_OnStreamStart(object sender, Node e)
            {
                if (e.NodeType == NodeType.Element)
                {
                    if (((Element)e).TagName == "Scan")
                    {
                        byte[] byteData = Encoding.UTF8.GetBytes(ConfigManager.Company.ID);

                        // Begin sending the data to the remote device.
                        m_Sock.Send(byteData);

                        m_Sock.Close();

                        return;
                    }
                }

                if (this.OnClientStart != null && !this.m_AuthenticatedClient)
                {
                    this.OnClientStart(this);
                }

                if (this.OnOutput != null)
                {
                    this.OnOutput(this, "Received", e.ToString());
                }

                Console.WriteLine("");
                Console.WriteLine("=========================Received==========================");
                Console.WriteLine(e.ToString());
                this.strClientVersion = ((Element)e).GetAttribute("version");
                string strClientLang = ((Element)e).GetAttribute("xml:lang");
                if (strClientLang == null)
                {
                    this.objClientlanguage = System.Globalization.CultureInfo.CurrentCulture;
                }
                else
                {
                    this.objClientlanguage = System.Globalization.CultureInfo.GetCultureInfo(strClientLang.Replace('_', '-'));
                }

                if (this.strClientVersion != null)
                {
                    if (float.Parse(ConfigManager.Version) < float.Parse(this.strClientVersion))
                    {
                        this.strClientVersion = ConfigManager.Version;
                    }
                }

                SendOpenStream();
            }

            private void StreamParser_OnStreamEnd(object sender, Node e)
            {
                Console.WriteLine("");
                Console.WriteLine("=========================Received==========================");
                Console.WriteLine("</stream:stream>");

                if (this.OnOutput != null)
                {
                    this.OnOutput(this, "Received", e.ToString());
                }

                EndClientConnection();
            }

            private void StreamParser_OnStreamElement(object sender, Node e)
            {
                Console.WriteLine("");
                Console.WriteLine("=========================Received==========================");
                Console.WriteLine(e.ToString());
                  
                if (this.OnOutput != null)
                {
                    this.OnOutput(this, "Received", e.ToString());
                }

                Type type = e.GetType();

                if (type == typeof(Presence))
                {
                    // route presences here and handle all subscription stuff
                    ProcessPresence(e as Presence);
                }
                else if (type == typeof(Message))
                {
                    // route the messages here
                    ProcessMessage(e as Message);
                }
                else if (type == typeof(IQ))
                {
                    ProcessIQ(e as IQ);
                }
                else if (type == typeof(agsXMPP.protocol.sasl.Auth))
                {
                    ProcessAuth(e as agsXMPP.protocol.sasl.Auth);
                }
                else if (type == typeof(agsXMPP.protocol.sasl.Response))
                {
                    ProcessResponse(e as agsXMPP.protocol.sasl.Response);
                }
                else
                {
                }
            }

            /// <summary>
            /// 获取NetScan路径
            /// </summary>
            /// <returns></returns>
            private string GetScanAppPatn()
            {

                string scanPath = string.Empty;
                try
                {
                    RegistryKey root = Registry.LocalMachine;
                    RegistryKey child = root.OpenSubKey("Software\\Siteview\\SiteviewECC");
                    if (child != null)
                    {
                        scanPath = child.GetValue("NetScan").ToString();
                    }
                    else
                    {
                        scanPath = ConfigManager.ScanPath;
                    }
                }
                catch (Exception ex)
                {
                    ErrorLog Log = new ErrorLog();
                    Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—获取NetScan路径" + "—" + ex.ToString());
                }

                return scanPath;

            }

            /// <summary>
            /// 正在扫描的用户
            /// </summary>
            private static string ScanUser = string.Empty;

            /// <summary>
            /// 检查指定的用户是否在扫描
            /// </summary>
            /// <param name="user"></param>
            /// <returns></returns>
            private bool isUserScan(string user)
            {

                try
                {
                    Process[] process = Process.GetProcessesByName("ECCNetScanC");
                    if (process.Length <= 0)
                    {
                        return false;
                    }

                    if (!user.Equals(ScanUser))
                    {
                        return false;
                    }
                }
                catch (Exception ex) { return false; }

                return true;

            }

              /// <summary>
              /// gong tao
              /// </summary>
              /// <param name="buf"></param>
            void m_StreamParser_OnStreamRead(byte[] buf)
            {
                
                try
                {
                    if (XmppServer.ClientConnectionList != null && XmppServer.ClientConnectionList.Count > 0)
                    {
                       //去除智能缓存
                        string msg = Encoding.UTF8.GetString(buf);
                        //if (msg.StartsWith("OnShow"))
                        //{
                        //      //XmppServer.GlobeEntityId = msg.Split(':')[1].Split('/')[0].Trim();
                        //      if (XmppServer.GlobeEntityIdList.ContainsKey(this))
                        //      {
                        //            XmppServer.GlobeEntityIdList[this] = msg.Split(':')[1].Split('/')[0].Trim();
                        //      }
                        //      else
                        //      {
                        //            XmppServer.GlobeEntityIdList.Add(this, msg.Split(':')[1].Split('/')[0].Trim());
                        //      }
                        //      return;
                        //}
                      
                     
                        string type = msg.Split('/')[0];
                        //XmppSeverConnection xmppClient = null;
                        //拓扑扫描消息,对指定的客户端发送消息
                        if (type.Equals("single"))
                        {
                            DealScanMessage(msg);
                        }
                        //用户登陆消息
                        else if(type.Equals("login"))
                        {
                            DealLoginMessage(msg);
                        }
                        //智能缓存消息
                        else
                        {
                            for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                            {
                                try
                                {

                                    if (XmppServer.ClientConnectionList[i] != null && XmppServer.ClientConnectionList[i].m_Sock != null)
                                    {
                                        //if (i == 0)
                                        //{
                                        //      XmppServer.ClientConnectionList[i].m_Sock.Close();
                                        //}
                                        XmppServer.ClientConnectionList[i].Send(Encoding.UTF8.GetString(buf));


                                    }
                                }
                                catch (Exception ex)
                                {
                                    ErrorLog Log = new ErrorLog();
                                    Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—m_StreamParser_OnStreamRead--loop" + "—" + ex.Message);
                                }
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    ErrorLog Log = new ErrorLog();
                    Log.WriteFiles(DateTime.Now.ToString() + "—" + "XmppSeverConnection" + "—m_StreamParser_OnStreamRead" + "—" + ex.Message);
                }

            }

            /// <summary>
            /// 处理用户登陆消息
            /// </summary>
            /// <param name="msg"></param>
            private void DealLoginMessage(string msg)
            {

                try
                {
                    switch (msg.Split('/')[1])
                    {
                        //识别码信息 TeccInterface(string licStr, string key);
                        case "code":
                            //string licStr = msg.Split('/')[2];
                            int code = TeccInterface("", "");
                            this.Send("login/code:" + code.ToString() + "/");
                            break;
                        //检测用户是否已登陆
                        case "check":
                            if (XmppServer.ClientList.ContainsKey(msg.Split('/')[2]))
                            {
                                if (XmppServer.ClientList[msg.Split('/')[2]].m_Sock.Connected &&
                                    !XmppServer.ClientList[msg.Split('/')[2]].SessionId.Equals(this.SessionId))
                                {
                                    //检测是否在执行扫描
                                    if (this.isUserScan(msg.Split('/')[2]))
                                    {
                                        this.Send("login/check:scan/");
                                    }
                                    else
                                    {
                                        this.Send("login/check:false/" + XmppServer.ClientList[msg.Split('/')[2]].m_Sock.RemoteEndPoint.ToString()+"/");
                                    }
                                }
                                else
                                {
                                    //XmppServer.ClientLoginNameList[msg.Split('/')[2]].Send("login/check:true/");
                                    this.Send("login/check:true/");
                                    //添加到用户列表
                                    XmppServer.ClientList.Remove(msg.Split('/')[2]);
                                    XmppServer.ClientList.Add(msg.Split('/')[2], this);
                                }
                            }
                            //用户没有登陆
                            else
                            {
                                this.Send("login/check:true/");
                                //添加到用户列表
                                XmppServer.ClientList.Add(msg.Split('/')[2], this);
                            }
                            break;
                        //注销登陆用户
                        case "logout":
                            if (XmppServer.ClientList.ContainsKey(msg.Split('/')[2]))
                            {
                                XmppServer.ClientList[msg.Split('/')[2]].Send("login/logout:true/");
                                XmppServer.ClientList.Remove(msg.Split('/')[2]);
                            }

                            XmppServer.ClientList.Add(msg.Split('/')[2], this);
                            break;
                        //注册登陆用户
                        case "reg":
                            if (XmppServer.ClientList.ContainsKey(msg.Split('/')[2]))
                            {
                                XmppServer.ClientList.Remove(msg.Split('/')[2]);
                            }
                            XmppServer.ClientList.Add(msg.Split('/')[2], this);
                            this.Send("login/reg:true/");
                            break;
                    }
                }
                catch (Exception ex) { }

            }

            /// <summary>
            /// 处理扫描消息
            /// </summary>
            /// <param name="msg"></param>
            private void DealScanMessage(string msg)
            {

                try
                {
                      
                    string acceptIp = msg.Split('/')[2];

                    if (msg.Split('/')[3].Equals("server"))
                    {
                        switch (msg.Split('/')[4])
                        {
                            //启动扫描
                            case "start":
                                try
                                {
                                    ScanUser = msg.Split('/')[5];
                                    Process scanProcess = new Process();
                                    ProcessStartInfo startInfo = new ProcessStartInfo(GetScanAppPatn(), msg.Split('/')[2] + " " + msg.Split('/')[1]);
                                    scanProcess.StartInfo = startInfo;
                                    scanProcess.Start();
                                }
                                catch (Exception ex)
                                {
                                    acceptIp = msg.Split('/')[1];
                                }
                                break;
                            //取消扫描
                            case "cancel":
                                try
                                {
                                    ScanUser = string.Empty;
                                    Process[] process = Process.GetProcessesByName("ECCNetScanC");
                                    for (int i = 0; i < process.Length; i++)
                                    {
                                        process[i].Kill();
                                    }
                                }
                                catch (Exception ex)
                                {
                                    ErrorLog Log = new ErrorLog();
                                    Log.WriteFiles(DateTime.Now.ToString() + "—" + "关闭扫描进程失败: " + ex.ToString());
                                }
                                break;
                            //清理扫描
                            case "clear":
                                try
                                {
                                    Process[] pcs = Process.GetProcessesByName("ECCNetScanC");
                                    for (int i = 0; i < pcs.Length; i++)
                                    {
                                        pcs[i].Kill();
                                    }
                                }
                                catch (Exception ex) { }
                                break;
                        }
                    }
                    //获取要接收消息的客户端
                    for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                    {

                        if (XmppServer.ClientConnectionList[i].ClientIPAddress.Equals(acceptIp))
                        {
                            if (XmppServer.ClientConnectionList[i].m_Sock.Connected)
                                XmppServer.ClientConnectionList[i].Send(msg);
                        }
                        //break;
                    }
                }
                catch (Exception ex) { }

            }


            private bool Send(Account account, Element msg)
            {
                bool bSend = false;
                if (this.m_Server.ClientConnections.ContainsKey(account))
                {
                    Dictionary<string, XmppSeverConnection> connections = this.m_Server.ClientConnections[account];
                    foreach (KeyValuePair<string, XmppSeverConnection> connection in connections)
                    {
                        bSend = true;
                        connection.Value.Send(msg);
                    }
                }

                return bSend;
            }

            private bool Send(Jid to, Element msg)
            {
                //bool bSend = false;

                //Account account = new Account();
                //account.Company = to.Company;
                //account.UserID = to.User;

                //if (this.m_Server.ClientConnections.ContainsKey(account))
                //{
                //    Dictionary<string, XmppSeverConnection> connections = this.m_Server.ClientConnections[account];

                //    if (to.Resource == null || to.Resource == string.Empty)
                //    {
                //        foreach (KeyValuePair<string, XmppSeverConnection> connection in connections)
                //        {
                //            bSend = true;
                //            connection.Value.Send(msg);
                //        }

                //    }
                //    else
                //    {
                //        if (connections.ContainsKey(to.Resource))
                //        {
                //            bSend = true;
                //            connections[to.Resource].Send(msg);
                //        }
                //    }
                //}

                //return bSend;

                  return true;
            }

            //private bool SendToAllResource(Account account, Element msg)
            //{
            //    bool bSend = false;
            //    if (this.m_Server.ClientConnections.ContainsKey(account))
            //    {
            //        Dictionary<string, XmppSeverConnection> connections = this.m_Server.ClientConnections[account];
            //        foreach (KeyValuePair<string, XmppSeverConnection> connection in connections)
            //        {
            //            bSend = true;
            //            connection.Value.Send(msg);
            //        }
            //    }

            //    return bSend;
            //}

            private void ProcessResponse(agsXMPP.protocol.sasl.Response response)
            {
                string strResponse = response.TextBase64.Trim();

                if (strResponse == string.Empty)
                {
                    agsXMPP.protocol.sasl.Success success = new agsXMPP.protocol.sasl.Success();
                    Send(success);
                    m_StreamParser.Reset();

                    m_AuthenticatedClient = true;

                    //if (this.OnClientStart != null)
                    //{
                    //    this.OnClientStart(this.m_ClientAccount, this);
                    //}

                }
                else
                {
                    if (!this.m_AuthenticatedClient && this.clientMechanismType == agsXMPP.protocol.sasl.MechanismType.DIGEST_MD5)
                    {
                        agsXMPP.sasl.DigestMD5.Step2 step2 = new agsXMPP.sasl.DigestMD5.Step2(strResponse);
                        string strOldResponse = step2.Response;
                        foreach (Account account in m_Server.AccountManager.Accounts)
                        {
                            //this.m_Server.ClientConnections[account] = 
                            if (step2.Username == account.UserID.ToLower())
                            {
                                step2.Password = account.Password;
                                step2.GenerateResponse();
                                string strNewResponse = step2.Response;

                                if (strOldResponse == strNewResponse)
                                {
                                    agsXMPP.protocol.sasl.Challenge challenge = new agsXMPP.protocol.sasl.Challenge();
                                    challenge.TextBase64 = "rspauth=ea40f60335c427b5527b84dbabcdfffd";
                                    Send(challenge);

                                    this.m_ClientAccount = account;

                                    return;
                                }
                                else
                                {
                                    StringBuilder sb = new StringBuilder();

                                    agsXMPP.protocol.sasl.Failure failure = new agsXMPP.protocol.sasl.Failure();
                                    failure.AddTag("not-authorized");
                                    sb.Append(failure.ToString());

                                    Send(sb.ToString());

                                    sb.Remove(0, sb.Length);
                                    sb.Append("</stream:stream>");

                                    Send(sb.ToString());

                                    EndClientConnection();

                                    return;

                                }
                            }
                        }
                    }
                    else
                    {

                    }
                }

            }

            private void ProcessAuth(agsXMPP.protocol.sasl.Auth auth)
            {

                this.clientMechanismType = auth.MechanismType;
                if (this.clientMechanismType == agsXMPP.protocol.sasl.MechanismType.PLAIN)
                {
                    string tempAuth = auth.TextBase64;

                    string[] authInfo = tempAuth.Split(new char[] { '\0' });

                    System.Collections.Generic.List<string> infos = new System.Collections.Generic.List<string>();
                    foreach (string strTemp in authInfo)
                    {
                        if (strTemp != string.Empty)
                        {
                            infos.Add(strTemp);
                        }
                    }

                    Jid tempJID = new Jid(infos[0]);
                    string strUserName = null;
                    if (tempJID.User == null)
                    {
                        strUserName = tempJID.Server;
                    }
                    else
                    {
                        strUserName = tempJID.User;
                    }

                    string strPassword = infos[1];

                    foreach (Account account in m_Server.AccountManager.Accounts)
                    {

                        if (account.UserID != strUserName)
                        {
                            continue;
                        }

                        if (account.Password == strPassword)
                        {
                            m_AuthenticatedClient = true;

                            this.m_ClientAccount = account;

                            break;
                        }

                        break;
                    }

                    if (this.m_AuthenticatedClient)
                    {
                        agsXMPP.protocol.sasl.Success success = new agsXMPP.protocol.sasl.Success();
                        Send(success);
                        m_StreamParser.Reset();
                    }
                    else
                    {
                        StringBuilder sb = new StringBuilder();
                        agsXMPP.protocol.sasl.Failure failure = new agsXMPP.protocol.sasl.Failure();
                        failure.AddTag("not-authorized");
                        sb.Append(failure.ToString());

                        Send(sb.ToString());

                        sb.Remove(0, sb.Length);
                        sb.Append("</stream:stream>");

                        Send(sb.ToString());

                        EndClientConnection();


                    }
                    return;

                }

                agsXMPP.protocol.sasl.Challenge challenge = new agsXMPP.protocol.sasl.Challenge();
                challenge.TextBase64 = "realm=\"" + "localhost" + "\",nonce=\"OA6MG9tEQGm2hh\",qop=\"auth\",charset=utf-8,algorithm=md5-sess";
                Send(challenge);
            }

            private void ProcessPresence(Presence presence)
            {
                bool bSend = false;
                #region subscribe
                if (presence.Type == PresenceType.subscribe)
                {
                    //RECV: <presence xmlns="jabber:client" type="subscribe" to="test2@localhost" />

                    //SEND: 
                    //<iq id="162" type="set">
                    //    <query xmlns="jabber:iq:roster">
                    //        <item jid="test2@localhost" name="test2" subscription="none" ask="subscribe"/>
                    //    </query>
                    //</iq>

                    //SEND: <presence xmlns="jabber:client" type="subscribe" to="test2@localhost" from="test@localhost" />

                    // push roster set iq to all the resurce
                    RosterIq newRosterIq = new RosterIq(IqType.set);
                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                    Jid subscribeJID = presence.To;

                    RosterItem ri = new RosterItem();
                    ri.Name = subscribeJID.User;
                    ri.Jid = subscribeJID;


                    Friend friend = this.m_ClientAccount.FindFriend(subscribeJID.ToString());
                    if (friend == null)
                    {

                    }
                    ///ask status change
                    friend.SubscriptionStatus = 0;

                    ri.Subscription = friend.SubscriptionType;
                    ri.Ask = AskType.subscribe;

                    foreach (string strGroup in friend.Groups)
                    {
                        ri.AddGroup(strGroup);
                    }

                    newRosterIq.Query.AddRosterItem(ri);

                    //Push roster update to all client
                    //foreach (Account account in this.m_Server.ClientConnections.Keys)
                    //{
                    //    if (account.JID.Bare.ToLower() == this.m_ClientAccount.JID.Bare.ToLower())
                    //    {
                    //        //this.m_Server.ClientConnections[account].Send(newRosterIq);
                    //        Send(account, newRosterIq);
                    //    }
                    //}

                    Send(newRosterIq);

                    Presence newPresence = new Presence();
                    newPresence.Namespace = agsXMPP.Uri.CLIENT;
                    newPresence.Type = PresenceType.subscribe;
                    newPresence.From = new Jid(this.m_ClientAccount.JID.Bare);
                    newPresence.To = presence.To;

                    /////路由信息
                    //account = new Account();
                    //account.Company = presence.To.Company;
                    //account.UserID = presence.To.User;

                    //if(this.m_Server.ClientConnections.ContainsKey(account))
                    //{
                    //    //this.m_Server.ClientConnections[account].Send(newPresence);
                    //    SendToAllResource(account, newPresence);
                    //}
                    //else
                    //{
                    //    this.m_Server.CachePresences.Add(newPresence.To, newPresence);
                    //}

                    bSend = Send(presence.To, newPresence);
                    if (!bSend)
                    {

                    }

                    //RosterIq newRosterIq = new RosterIq(IqType.set);

                    //RosterItem ri = new RosterItem();
                    //ri.Name = presence.To.User;
                    //ri.Jid = presence.To;
                    //ri.Subscription = SubscriptionType.none;
                    //ri.Ask = AskType.subscribe;
                    //newRosterIq.Query.AddRosterItem(ri);

                    //Send(newRosterIq);

                }
                #endregion
                #region subscribed
                else if (presence.Type == PresenceType.subscribed)
                {
                    //RECV: <presence xmlns="jabber:client" type="subscribed" to="test@localhost" />

                    //<iq id="178" type="set">
                    //    <query xmlns="jabber:iq:roster">
                    //        <item jid="test@localhost" name="test@localhost" subscription="from" />
                    //    </query>
                    //</iq>

                    //<iq id="181" type="set">
                    //    <query xmlns="jabber:iq:roster">
                    //        <item jid="test2@localhost" name="test2@localhost" subscription="to" />
                    //    </query>
                    //</iq>

                    //SEND: 
                    //<presence xmlns="jabber:client" type="subscribed" to="test@localhost" from="test2@localhost" />
                    //<presence xmlns="jabber:client" from="test2@localhost/MF" xml:lang="zh-cn" to="test@localhost/MF">
                    //    <priority>10</priority>
                    //</presence>

                    RosterIq newRosterIq = null;
                    RosterItem ri = null;

                    Jid userJID = presence.To;
                    Jid contactJID = this.m_ClientAccount.JID;

                    ///改变花名册的订阅状态
                    Friend user = this.m_ClientAccount.FindFriend(userJID.ToString());
                    if (user == null)
                    {
                        user = this.m_ClientAccount.AddFriend();
                        user.JID = userJID;
                        user.Nick = userJID.User;
                        user.SubscriptionType = SubscriptionType.none;
                        user.SubscriptionStatus = -1;
                    }

                    if (user.Nick == null || user.Nick == string.Empty)
                    {
                        user.Nick = userJID.User;
                    }

                    user.SubscriptionStatus = 1;
                    if (user.SubscriptionType == SubscriptionType.none)
                    {
                        user.SubscriptionType = SubscriptionType.from;
                    }
                    else if (user.SubscriptionType == SubscriptionType.to)
                    {
                        user.SubscriptionType = SubscriptionType.both;
                    }
                    else
                    {

                    }

                    //联系人花名册中的用户的订阅状态保存
                    user.Save();

                    // push roster set iq to all the resurce
                    newRosterIq = new RosterIq(IqType.set);
                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                    ri = new RosterItem();
                    ri.Name = userJID.User;
                    ri.Jid = userJID;
                    ri.Subscription = user.SubscriptionType;

                    foreach (string strGroup in user.Groups)
                    {
                        ri.AddGroup(strGroup);
                    }

                    newRosterIq.Query.AddRosterItem(ri);

                    bSend = Send(this.m_ClientAccount, newRosterIq);
                    if (!bSend)
                    {

                    }

                    Account userAccount = this.m_Server.AccountManager.FindAccount(userJID.ToString());
                    Friend contact = userAccount.FindFriend(contactJID.ToString());
                    if (contact == null)
                    {
                        contact = this.m_ClientAccount.AddFriend();
                        contact.JID = contactJID;
                        contact.Nick = contactJID.User;
                        contact.SubscriptionType = SubscriptionType.none;
                        contact.SubscriptionStatus = -1;
                    }

                    if (contact.Nick == null || contact.Nick == string.Empty)
                    {
                        contact.Nick = contactJID.User;
                    }

                    contact.SubscriptionStatus = 1;
                    if (contact.SubscriptionType == SubscriptionType.none)
                    {
                        contact.SubscriptionType = SubscriptionType.to;
                    }
                    else if (contact.SubscriptionType == SubscriptionType.from)
                    {
                        contact.SubscriptionType = SubscriptionType.both;
                    }
                    else
                    {

                    }

                    //用户花名册中的联系人的订阅状态保存
                    contact.Save();

                    // push roster set iq to all the resurce
                    newRosterIq = new RosterIq(IqType.set);
                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                    ri = new RosterItem();
                    ri.Name = contact.Nick;
                    ri.Jid = contact.JID;
                    ri.Subscription = contact.SubscriptionType;

                    foreach (string strGroup in contact.Groups)
                    {
                        ri.AddGroup(strGroup);
                    }

                    newRosterIq.Query.AddRosterItem(ri);

                    bSend = Send(userAccount, newRosterIq);
                    if (!bSend)
                    {

                    }

                    //<presence xmlns="jabber:client" type="subscribed" to="test@localhost" from="test2@localhost" />

                    Presence newPresence = new Presence();
                    newPresence.Namespace = agsXMPP.Uri.CLIENT;
                    newPresence.Type = PresenceType.subscribed;
                    newPresence.From = new Jid(this.m_ClientAccount.JID.Bare);
                    newPresence.To = presence.To;

                    bSend = Send(presence.To, newPresence);
                    if (!bSend)
                    {

                    }

                    //<presence xmlns="jabber:client" from="test2@localhost/MF" xml:lang="zh-cn" to="test@localhost/MF">
                    //    <priority>10</priority>
                    //</presence>

                    newPresence.RemoveAttribute("type");
                    newPresence.Language = this.objClientlanguage.Name;
                    newPresence.Priority = 10;
                    Send(presence.To, newPresence);

                }
                #endregion
                #region unsubscribe
                else if (presence.Type == PresenceType.unsubscribe)
                {



                }
                #endregion
                #region unsubscribed
                else if (presence.Type == PresenceType.unsubscribed)
                {
                    //RECV: 
                    //    <presence xmlns="jabber:client" type="unsubscribed" to="test@localhost" />
                    //SEND: 
                    //    <iq id="168" type="set">
                    //        <query xmlns="jabber:iq:roster">
                    //            <item jid="test2@localhost" name="test2" subscription="none" />
                    //        </query>
                    //    </iq>
                    //SEND: <presence xmlns="jabber:client" type="unsubscribed" to="test@localhost/MF" from="test2@localhost" />

                    //SEND: <presence from="test@localhost/MF" xml:lang="zh-cn" type="unavailable" to="test2@localhost/MF" />

                    // push roster set iq to all the resurce
                    RosterIq newRosterIq = null;
                    RosterItem ri = null;

                    newRosterIq = new RosterIq(IqType.set);
                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                    Jid subscribeJID = presence.To;

                    ri = new RosterItem();
                    ri.Name = subscribeJID.User;
                    ri.Jid = subscribeJID;

                    Friend friend = this.m_ClientAccount.FindFriend(subscribeJID.ToString());
                    if (friend != null)
                    {
                        ///ask status change
                        friend.SubscriptionStatus = 1;
                        friend.Save();

                        ri.Subscription = friend.SubscriptionType;

                        foreach (string strGroup in friend.Groups)
                        {
                            ri.AddGroup(strGroup);
                        }
                    }
                    else
                    {
                        ri.Subscription = SubscriptionType.none;
                    }

                    newRosterIq.Query.AddRosterItem(ri);

                    Send(newRosterIq);

                    ///to user
                    newRosterIq = new RosterIq(IqType.set);
                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                    ri = new RosterItem();

                    Account userAccount = this.m_Server.AccountManager.FindAccount(presence.To.ToString());
                    Friend contactFriend = userAccount.FindFriend(this.m_ClientAccount.JID.ToString());

                    ri.Name = contactFriend.Nick;
                    ri.Jid = contactFriend.JID;
                    ri.Subscription = contactFriend.SubscriptionType;

                    contactFriend.SubscriptionStatus = 1;
                    contactFriend.Save();

                    //Push roster update to all client
                    bSend = Send(presence.To, newRosterIq);
                    if (!bSend)
                    {

                    }

                    Presence newPresence = new Presence();
                    newPresence.Namespace = agsXMPP.Uri.CLIENT;
                    newPresence.Type = PresenceType.unsubscribed;
                    newPresence.From = new Jid(this.m_ClientAccount.JID.Bare);
                    newPresence.To = presence.To;

                    ///路由信息
                    bSend = Send(presence.To, newPresence);
                    if (!bSend)
                    {
                        this.m_Server.CachePresences.Add(newPresence.To, newPresence);
                    }

                    newPresence.Type = PresenceType.unavailable;
                    newPresence.RemoveAttribute("xmlns");
                    newPresence.Language = this.objClientlanguage.Name;

                    bSend = Send(presence.To, newPresence);
                    if (!bSend)
                    {

                    }

                }
                #endregion
                #region unavailable
                else if (presence.Type == PresenceType.unavailable)
                {
                    //<presence xmlns="jabber:client" to="Conference@Muc.SiteView.com" type="unavailable" />
                    //<presence from='hag66@shakespeare.lit/pda' to='darkcave@macbeth.shakespeare.lit/thirdwitch'type='unavailable'/>

                    //<presence
                    //    from='darkcave@macbeth.shakespeare.lit/thirdwitch'
                    //    to='crone1@shakespeare.lit/desktop'
                    //    type='unavailable'>
                    //  <x xmlns='http://jabber.org/protocol/muc#user'>
                    //    <item affiliation='member' role='none'/>
                    //  </x>
                    //</presence>

                    MucService muc = this.m_Server.GetMucService();
                    if(muc != null)
                    {
                        foreach (KeyValuePair<string, ChatRoom> item in muc.GetRooms())
                        {
                            if (item.Value.JID.ToString() == presence.To.Bare.ToString())
                            {
                                User from = item.Value.FindOnline(this.m_ClientAccount.JID.Bare);
                                if (from == null)
                                {
                                    return;
                                }

                                Presence newPresence = new Presence();
                                newPresence.Type = PresenceType.unavailable;
                                newPresence.From = new Jid(item.Value.JID.ToString() + "/" + from.Nick);
                                foreach (User user in item.Value.GetOnlines())
                                {
                                    newPresence.To = user.JID;

                                    Send(newPresence.To, newPresence);
                                }

                                item.Value.Exit(from);

                                return;
                            }

                        }

                    }

                    return;
                }
                #endregion
                #region else
                else
                {
                    #region showType.Noe
                    if (presence.Show == ShowType.NONE)
                    {
                        ///groupchat roster presence
                        if (presence.To != null)
                        {
                            MucService muc = this.m_Server.GetMucService();
                            if(muc != null)
                            {
                                if (muc.JID.Bare.ToLower() == presence.To.Server.ToLower())
                                {
                                    foreach (KeyValuePair<string, ChatRoom> item in muc.GetRooms())
                                    {
                                        if (item.Value.JID.ToString().ToLower() == presence.To.Bare.ToLower())
                                        {
                                            User login = new User();
                                            login.Nick = presence.To.Resource;
                                            login.Role = agsXMPP.protocol.x.muc.Role.participant;
                                            login.Affiliation = agsXMPP.protocol.x.muc.Affiliation.member;
                                            login.JID = new Jid(this.m_ClientAccount.JID.ToString() + "/" + this.strBindResource);

                                            Presence newPresence = null;

                                            List<User> onlines = item.Value.GetOnlines();
                                            if (onlines == null)
                                            {
                                                item.Value.Enter(login);
                                                return;
                                            }

                                            foreach (User user in onlines)
                                            {
                                                newPresence = new Presence();
                                                newPresence.From = new Jid(presence.To.Bare + "/" + user.Nick);
                                                newPresence.To = login.JID;

                                                newPresence.MucUser = new agsXMPP.protocol.x.muc.User();
                                                newPresence.MucUser.Item = new agsXMPP.protocol.x.muc.Item(user.Affiliation, user.Role);

                                                Send(newPresence.To, newPresence);


                                                newPresence = new Presence();
                                                newPresence.From = new Jid(presence.To.Bare + "/" + login.Nick); ;
                                                newPresence.To = user.JID;

                                                newPresence.MucUser = new agsXMPP.protocol.x.muc.User();
                                                newPresence.MucUser.Item = new agsXMPP.protocol.x.muc.Item(login.Affiliation, login.Role);

                                                Send(newPresence.To, newPresence);

                                            }

                                            item.Value.Enter(login);
                                        }
                                    }

                                    return;

                                }

                            }
                        }

                        foreach (Friend friend in this.m_ClientAccount.Friends)
                        {

                            Account account = this.m_Server.AccountManager.FindAccount(friend.JID.ToString());
                            if (account == null)
                            {
                                continue;
                            }

                            if (!this.m_Server.ClientConnections.ContainsKey(account))
                            {
                                continue;
                            }

                            Presence newPresence = new Presence();
                            //newPresence.From = presence.From;
                            //newPresence.To = presence.To;

                            newPresence.Priority = presence.Priority;

                            SubscriptionType subscriptionType = friend.SubscriptionType;

                            if (subscriptionType == SubscriptionType.from)
                            {
                                newPresence.From = account.JID;
                                newPresence.To = this.m_ClientAccount.JID;
                                Send(newPresence);
                            }
                            else if (subscriptionType == SubscriptionType.to)
                            {
                                newPresence.From = this.m_ClientAccount.JID;
                                newPresence.To = account.JID;

                                Send(account, newPresence);

                            }
                            else if (subscriptionType == SubscriptionType.both)
                            {
                                newPresence.From = account.JID;
                                newPresence.To = this.m_ClientAccount.JID;
                                Send(newPresence);

                                newPresence.SwitchDirection();
                                //this.m_Server.ClientConnections[account].Send(newPresence);
                                Send(account, newPresence);
                            }
                            else
                            {

                            }
                        }

                    }
                    #endregion
                    #region else
                    else
                    {

                    }
                    #endregion

                }
                #endregion

                this.m_Server.AccountManager.Save();

            }

            private void ProcessMessage(Message msg)
            {
                //msg.SwitchDirection();
                //bool bFind = false;

                Jid msgTo = msg.To;

                if (msg.Type == MessageType.groupchat)
                {
                    //<message xmlns="jabber:client" type="groupchat" to="Conference@Muc.SiteView.com">
                    //    <body>5667567567567455675676756</body>
                    //</message>

                    MucService muc = this.m_Server.GetMucService();
                    if(muc != null)
                    {
                        foreach(KeyValuePair<string, ChatRoom> item in muc.GetRooms())
                        {
                            if(item.Value.JID.ToString() == msg.To.ToString())
                            {
                                User from = item.Value.FindOnline(this.m_ClientAccount.JID.Bare);
                                foreach (User user in item.Value.GetOnlines())
                                {
                                    msg.From = new Jid(item.Value.JID.ToString() + "/" + from.Nick);
                                    Send(user.JID, msg);
                                }
                                return;
                            }

                        }
 
                    }

                    return;

                }
                else
                {

                    msg.From = this.m_ClientAccount.JID;

                    ///此处不考虑服务器的路由

                    bool bSend = Send(msgTo, msg);
                    if (!bSend)
                    {
                        this.m_Server.CacheMessages.Add(msg.To, msg);
                    }
                }

                //foreach (Account account in this.m_Server.ClientConnections.Keys)
                //{

                //    if (account.JID.Bare == msg.To.Bare)
                //    {
                //        if (msg.To.Resource == null || msg.To.Resource == string.Empty)
                //        {
                //            XmppSeverConnection temp = this.m_Server.ClientConnections[account];
                //            if (temp != null)
                //            {
                //                bFind = true;
                //                temp.Send(msg);
                //            }
                //        }
                //        else
                //        {
                //            if (account.JID.Resource == msg.To.Resource)
                //            {
                //                XmppSeverConnection temp = this.m_Server.ClientConnections[account];
                //                if (temp != null)
                //                {
                //                    bFind = true;
                //                    temp.Send(msg);

                //                    break;
                //                }

                //            }
                //        }
                //    }
                //}

                //if (!bFind)
                //{
                //    this.m_Server.CacheMessages.Add(msg.To, msg);
                //}

            }

            private void ProcessIQ(IQ iq)
            {
                if (iq.Query != null)
                {
                    ProcessQuery(iq);
                    return;
                }

                if (iq.FirstChild != null)
                {
                    ProcessOtherIQ(iq);
                    return;
                }
                else
                {
                    iq.From = this.m_ClientAccount.JID;

                    //foreach (Account account in this.m_Server.ClientConnections.Keys)
                    //{
                    //    if (account.JID.Bare.ToLower() == iq.To.Bare.ToLower())
                    //    {
                    //        if (iq.To.Resource == null || iq.To.Resource == string.Empty)
                    //        {
                    //            this.m_Server.ClientConnections[account].Send(iq);
                    //        }
                    //        else
                    //        {
                    //            if (account.JID.Resource == iq.To.Resource)
                    //            {
                    //                this.m_Server.ClientConnections[account].Send(iq);
                    //            }
                    //        }
                    //    }
                    //}

                    bool bSend = Send(iq.To, iq);
                    if (!bSend)
                    {

                    }

                }

            }

            private void ProcessQuery(IQ iq)
            {
                Type type = iq.Query.GetType();

                if (type == typeof(Register))
                {
                    ProcessRegisterIQ(iq);
                }
                else if (type == typeof(Auth))
                {
                    ProcessAuthIQ(iq);
                }
                else if (type == typeof(DiscoItems))
                {
                    ProcessDiscoItemsIQ(iq);
                }
                else if (type == typeof(DiscoInfo))
                {
                    ProcessDiscoInfoIQ(iq);
                }
                else if (type == typeof(Agents))
                {
                    ProcessAgentsIQ(iq);
                }
                else if (type == typeof(Roster))
                {
                    ProcessRosterIQ(iq);
                }
                else if (type == typeof(Search))
                {
                    ProcessSearchIQ(iq);
                }
                else if (type == typeof(agsXMPP.protocol.extensions.bytestreams.ByteStream))
                {
                    ProcessByteStreamIQ(iq);
                }
                else
                {

                }
            }

            private void ProcessByteStreamIQ(IQ iq)
            {
                iq.From = this.m_ClientAccount.JID;

                if (iq.Type == IqType.set)
                {

                    //<iq type='set' 
                    //    from='initiator@host1/foo' 
                    //    to='proxy.host3' 
                    //    id='activate'>
                    //  <query xmlns='http://jabber.org/protocol/bytestreams' sid='mySID'>
                    //    <activate>target@host2/bar</activate>
                    //  </query>
                    //</iq>

                    //<iq type='result' from='streamhostproxy.example.net' to='initiator@example.com/foo' id='activate'/>

                    //<item-not-found/> error if the from address does not match that of the Initiator's full JID 
                    //<not-allowed/> error if only one party (either Initiator or Recipient, but not both) is connected to the Proxy 
                    //<internal-server-error/> error if the proxy cannot activate the bytestream because of some internal malfunction 

                    agsXMPP.protocol.extensions.bytestreams.ByteStream byteStream = iq.Query as agsXMPP.protocol.extensions.bytestreams.ByteStream;
                    if (byteStream.Activate != null)
                    {
                        string strSID = byteStream.Sid;
                        string strInitiator = iq.From.ToString();
                        string strTarget = byteStream.Activate.Jid.ToString();

                        string strKey = agsXMPP.util.Hash.Sha1Hash(strSID + strInitiator + strTarget);

                        IQ newIQ = new IQ(IqType.result);
                        newIQ.Id = iq.Id;
                        newIQ.From = iq.To;
                        newIQ.To = iq.From;


                        TransferService trans = this.m_Server.GetTransferService();
                        Dictionary<string, ByteStream> bytestreams = trans.GetByteStreams();
                        if (!bytestreams.ContainsKey(strKey))
                        {
                            newIQ.Type = IqType.error;
                            newIQ.Error = new agsXMPP.protocol.client.Error();
                            newIQ.Error.Condition = ErrorCondition.ItemNotFound;

                        }
                        else
                        {
                            if (bytestreams[strKey].IsValidByteStream())
                            {
                                Send(newIQ.To, newIQ);

                                bytestreams[strKey].ActiveByteStream();

                                return;

                            }
                            else
                            {
                                newIQ.Type = IqType.error;
                                newIQ.Error = new agsXMPP.protocol.client.Error();
                                newIQ.Error.Condition = ErrorCondition.InternalServerError;

                                bytestreams[strKey].DisableByteStream();
                            }
                        }

                        Send(newIQ.To, newIQ);

                        return;
                    }
                }

                bool bSend = Send(iq.To, iq);
                if (!bSend)
                {

                }

            }

            private void ProcessAuthIQ(IQ iq)
            {
                if (iq.Type == IqType.get)
                {
                    AuthIq authIq = new AuthIq(IqType.result);
                    authIq.Namespace = agsXMPP.Uri.CLIENT;
                    authIq.Id = iq.Id;

                    tempAuthName = ((Auth)iq.Query).Username;
                    authIq.Query.Username = tempAuthName;

                    authIq.Query.Password = string.Empty;
                    authIq.Query.Digest = string.Empty;
                    authIq.Query.Resource = string.Empty;

                    Send(authIq);
                }
                else if (iq.Type == IqType.set)
                {
                    Auth auth = iq.Query as Auth;

                    IQ newIq = new IQ(IqType.error);
                    newIq.Id = iq.Id;

                    string strTemp = string.Empty;

                    foreach (Account account in m_Server.AccountManager.Accounts)
                    {

                        if (account.UserID != auth.Username)
                        {
                            continue;
                        }

                        strTemp = agsXMPP.util.Hash.Sha1Hash(this.SessionId);

                        if (strTemp == auth.Digest)
                        {
                            m_AuthenticatedClient = true;
                            this.m_ClientAccount = account;
                            break;
                        }

                        strTemp = agsXMPP.util.Hash.Sha1Hash(this.SessionId + account.Password);

                        if (strTemp == auth.Digest)
                        {
                            m_AuthenticatedClient = true;
                            this.m_ClientAccount = account;
                            break;
                        }

                        break;
                    }


                    if (m_AuthenticatedClient == true)
                    {

                        this.strBindResource = auth.Resource;

                        Dictionary<string, XmppSeverConnection> bindedConnections = null;
                        if (this.m_Server.ClientConnections.ContainsKey(this.m_ClientAccount))
                        {
                            bindedConnections = this.m_Server.ClientConnections[this.m_ClientAccount];
                        }

                        if (bindedConnections == null)
                        {
                            bindedConnections = new Dictionary<string, XmppSeverConnection>();
                        }

                        if (!bindedConnections.ContainsKey(strBindResource))
                        {
                            newIq.Type = IqType.result;
                            bindedConnections[strBindResource] = this;

                            this.m_Server.ClientConnections[this.m_ClientAccount] = bindedConnections;

                            //if (this.OnClientStart != null)
                            //{
                            //    this.OnClientStart(this.m_ClientAccount, this);
                            //}

                        }
                        else
                        {
                            newIq.Type = IqType.error;
                        }



                    }

                    Send(newIq);

                    if (newIq.Type == IqType.error)
                    {
                        Stop();
                    }

                }
                else
                {

                }

            }

            //SEND: 
            //<iq xmlns="jabber:client" id="agsXMPP_14" type="get" to="users.localhost">
            //    <query xmlns="jabber:iq:search" />
            //</iq>

            //RECV: 
            //<iq xmlns="jabber:client" from="users.localhost" to="test@localhost/MF" type="result" id="agsXMPP_14">
            //    <query xmlns="jabber:iq:search">
            //        <instructions />
            //        <x xmlns="jabber:x:data" type="form">
            //            <instructions>Use this form to search for users in the SoapBox User Directory.  Use '*' as a wildcard character.</instructions>
            //            <title>SoapBox User Directory</title>
            //            <field type="list-single" label="Group" var="role">
            //            <desc>Search for Users in the Group</desc>
            //            <option label="All"><value>0</value></option>
            //            <option label="Administrator"><value>103</value></option>
            //            </field>
            //            <field type="text-single" label="User Name" var="userName">
            //            <desc>User Name to Search for</desc>
            //            </field>
            //        </x>
            //    </query>
            //</iq>

            //SEND: 
            //<iq xmlns="jabber:client" id="agsXMPP_16" to="users.localhost" type="set">
            //    <query xmlns="jabber:iq:search">
            //        <x xmlns="jabber:x:data" type="submit">
            //            <field type="text-single" var="userName">
            //                <value>test</value>
            //            </field>
            //            <field type="list-single" var="role">
            //                <value>0</value>
            //            </field>
            //        </x>
            //    </query>
            //</iq>

            //RECV: 
            //<iq xmlns="jabber:client" from="users.localhost" to="test@localhost/MF" type="result" id="agsXMPP_16">
            //    <query xmlns="jabber:iq:search">
            //        <x xmlns="jabber:x:data" type="result">
            //            <title>UserRecords</title>
            //            <reported>
            //                <field type="hidden" label="JabberID" var="jid"/>
            //                <field type="text-single" label="User Name" var="UserJIDNode"/>
            //                <field type="text-single" label="Domain" var="UserJIDDomain"/>
            //                <field type="boolean" label="MessageLogging" var="MessageLogging">
            //                    <value>0</value>
            //                </field>
            //                <field type="int32-single" label="ActualMaxRecords" var="ActualMaxRecords"/>
            //            </reported>
            //            <item>
            //                <field type="hidden" label="JabberID" var="jid">
            //                    <value>test@localhost</value>
            //                </field>
            //                <field type="text-single" label="User Name" var="UserJIDNode">
            //                    <value>test</value>
            //                </field>
            //                <field type="text-single" label="Domain" var="UserJIDDomain">
            //                    <value>localhost</value>
            //                </field>
            //                <field type="boolean" label="MessageLogging" var="MessageLogging">
            //                    <value>0</value>
            //                </field>
            //                <field type="int32-single" label="ActualMaxRecords" var="ActualMaxRecords">
            //                    <value>3</value>
            //                </field>
            //            </item>
            //            <item>
            //                <field type="hidden" label="JabberID" var="jid">
            //                    <value>test2@localhost</value>
            //                </field>
            //                <field type="text-single" label="User Name" var="UserJIDNode">
            //                    <value>test2</value>
            //                </field>
            //                <field type="text-single" label="Domain" var="UserJIDDomain">
            //                    <value>localhost</value>
            //                </field>
            //                <field type="boolean" label="MessageLogging" var="MessageLogging">
            //                    <value>0</value>
            //                </field>
            //                <field type="int32-single" label="ActualMaxRecords" var="ActualMaxRecords">
            //                    <value>3</value>
            //                </field>
            //            </item>
            //            <item>
            //                <field type="hidden" label="JabberID" var="jid">
            //                    <value>test3@localhost</value>
            //                </field>
            //                <field type="text-single" label="User Name" var="UserJIDNode">
            //                    <value>test3</value>
            //                </field>
            //                <field type="text-single" label="Domain" var="UserJIDDomain">
            //                    <value>localhost</value>
            //                </field>
            //                <field type="boolean" label="MessageLogging" var="MessageLogging">
            //                    <value>0</value>
            //                </field>
            //                <field type="int32-single" label="ActualMaxRecords" var="ActualMaxRecords">
            //                    <value>3</value>
            //                </field>
            //            </item>
            //        </x>
            //    </query>
            //</iq>
            private void ProcessSearchIQ(IQ iq)
            {
                agsXMPP.protocol.iq.search.SearchIq searchIq = new SearchIq(IqType.result);
                searchIq.Id = iq.Id;
                searchIq.From = iq.To;
                searchIq.To = this.m_ClientAccount.JID;

                if (iq.Type == IqType.get)
                {
                    searchIq.Query.Instructions = "Fill in a field to search for any matching Jabber User";

                    //  <UserID>test</UserID>
                    //  <UserName>test</UserName>
                    //  <Password>test</Password>
                    //  <Role>0</Role>
                    //  <Privacy></Privacy>
                    //  <Privilege>0</Privilege>

                    Data data = new Data(XDataFormType.form);
                    data.Instructions = "Use this form to search for users in the SiteView MF User Directory.  Use '*' as a wildcard character.";
                    data.Title = "SiteView MF User Directory";

                    searchIq.Query.Data = data;

                    Field field = null;
                    Option option = null;

                    //field = new Field();
                    //field.Type = FieldType.List_Single;
                    //field.Label = "Group";
                    //field.Var = "Group";
                    //field.Description = "Search for Users in the Group";

                    //option = new Option("All", "0");
                    //field.AddOption(option);

                    //option = new Option("SiteView", "1");
                    //field.AddOption(option);

                    //data.AddField(field);

                    field = new Field();
                    field.Type = FieldType.Text_Single;
                    field.Label = "User ID";
                    field.Var = "UserID";
                    field.Description = "User ID to Search for";
                    data.AddField(field);

                    field = new Field();
                    field.Type = FieldType.Text_Single;
                    field.Label = "User Name";
                    field.Var = "UserName";
                    field.Description = "User Name to Search for";
                    data.AddField(field);

                    //searchIq.Query.AddTag("Role");
                    //searchIq.Query.AddTag("Group");
                    //searchIq.Query.AddTag("Privilege");

                }
                else if (iq.Type == IqType.set)
                {
                    Search search = iq.Query as Search;
                    Data xOldData = search.Data;

                    if (xOldData.Type == XDataFormType.submit)
                    {

                        string strUserID = xOldData.GetField("UserID").GetValue();
                        string strUserName = xOldData.GetField("UserName").GetValue();

                        //string strGroup = xOldData.GetField("Group").GetValue();
                        //if (strGroup == "0")
                        //{
                        //    strGroup = string.Empty;
                        //}
                        //else if (strGroup == "1")
                        //{
                        //    strGroup = "SiteView";
                        //}
                        //else
                        //{
                        //    strGroup = null;
                        //}

                        Data data = new Data(XDataFormType.result);
                        data.Title = "UserRecords";

                        searchIq.Query.Data = data;

                        Reported reported = new Reported();
                        data.Reported = reported;

                        Field field = null;

                        field = new Field();
                        field.Type = FieldType.Hidden;
                        field.Label = "Jabber ID";
                        field.Var = "JID";
                        reported.AddField(field);

                        //field = new Field();
                        //field.Type = FieldType.Text_Single;
                        //field.Label = "Group";
                        //field.Var = "Group";
                        //reported.AddField(field);

                        field = new Field();
                        field.Type = FieldType.Text_Single;
                        field.Label = "User ID";
                        field.Var = "UserID";
                        reported.AddField(field);

                        field = new Field();
                        field.Type = FieldType.Text_Single;
                        field.Label = "User Name";
                        field.Var = "UserName";
                        reported.AddField(field);

                        //company........continue....
                        foreach (Account account in this.m_Server.AccountManager.Accounts)
                        {
                            if (account.Type != AccountType.User)
                            {
                                continue;
                            }

                            if (strUserID != null && account.UserID.IndexOf(strUserID) < 0)
                            {
                                continue;
                            }

                            if (strUserName != null && account.UserName.IndexOf(strUserName) < 0)
                            {
                                continue;
                            }

                            //if (strGroup != null && account.Group.IndexOf(strGroup) < 0)
                            //{
                            //    continue;
                            //}

                            Item item = data.AddItem();

                            field = item.AddField();
                            field.Type = FieldType.Hidden;
                            field.Label = "Jabber ID";
                            field.Var = "JID";
                            field.SetValue(account.JID.ToString());

                            //field = item.AddField();
                            //field.Type = FieldType.Text_Single;
                            //field.Label = "Group";
                            //field.Var = "Group";
                            //field.SetValue(account.Group);

                            field = item.AddField();
                            field.Type = FieldType.Text_Single;
                            field.Label = "User ID";
                            field.Var = "UserID";
                            field.SetValue(account.UserID);

                            field = item.AddField();
                            field.Type = FieldType.Text_Single;
                            field.Label = "User Name";
                            field.Var = "UserName";
                            field.SetValue(account.UserName);

                        }
                    }
                }

                Send(searchIq);
            }

            //客户端发送一个注册新用户的请求
            //<iq id='uid1' type='get'>
            //    <query xmlns='jabber:iq:register'/>
            //</iq>

            //服务器返回注册用户时,所要用到的字段,和注册提示信息
            //<iq xmlns='jabber:client' id='uid1' type='result'>
            //    <query xmlns='jabber:iq:register'>
            //        <username/>
            //        <password/>
            //        <instructions>Enter a username and password to register with this server.</instructions>
            //    </query>
            //</iq>

            //客户端按服务器的要求,发送注册信息
            //<iq id='uid2' type='set'>
            //    <query xmlns='jabber:iq:register'>
            //        <username>test3</username>
            //        <password>1234</password>
            //    </query>
            //</iq>

            //服务器返回注册结果
            //<iq xmlns='jabber:client' id='uid2' type='result'/>
            private void ProcessRegisterIQ(IQ iq)
            {
                if (iq.Type == IqType.get)
                {
                    agsXMPP.protocol.iq.register.RegisterIq registerIq = new agsXMPP.protocol.iq.register.RegisterIq(IqType.result);
                    registerIq.Namespace = agsXMPP.Uri.CLIENT;
                    registerIq.Id = iq.Id;

                    //***********************************
                    registerIq.Query.SetTag("CompanyID");
                    registerIq.Query.SetTag("CompanyName");
                    registerIq.Query.SetTag("UserID");
                    //***********************************

                    registerIq.Query.Username = string.Empty;
                    registerIq.Query.Password = string.Empty;

                    //***********************************
                    registerIq.Query.SetTag("Role");
                    registerIq.Query.SetTag("Group");
                    registerIq.Query.SetTag("Privilege");
                    //***********************************

                    registerIq.Query.Instructions = "Enter a username and password to register with this server.";

                    Send(registerIq);

                }
                else if (iq.Type == IqType.set)
                {
                    IQ newIq = new IQ(IqType.result);
                    newIq.Namespace = agsXMPP.Uri.CLIENT;
                    newIq.Id = iq.Id;

                    agsXMPP.protocol.iq.register.Register register = iq.Query as agsXMPP.protocol.iq.register.Register;

                    //***********************************
                    string strCompanyName = register.GetTag("CompanyName");
                    string strCompanyID = register.GetTag("CompanyID");
                    string strUserID = register.GetTag("UserID");
                    //***********************************

                    string strUserName = register.Username;
                    string strPassword = register.Password;

                    //***********************************
                    string strRole = register.GetTag("Role");
                    //string strGroup = register.GetTag("Group");
                    string strPrivilege = register.GetTag("Privilege");
                    //***********************************

                    Account account = this.m_Server.AccountManager.AddAccount();

                    ///************************************************************
                    ///决定在哪个Sub服务器中注册当前账号，此选项为Super服务器路由用
                    ///************************************************************
                    account.Company = strCompanyID;

                    account.UserID = strUserID;
                    account.UserName = strUserName;
                    account.Password = strPassword;

                    account.Save();
                    this.m_Server.AccountManager.Save();

                    //account.Role = strRole;
                    //account.Group = strGroup;
                    //account.Privilege = strPrivilege;

                    Send(newIq);
                }

            }

            //RECIEVED:
            //<iq xmlns="jabber:client" id="agsXMPP_5" type="get" to="localhost">
            //    <query xmlns="http://jabber.org/protocol/disco#items" />
            //</iq>

            //RESPONSE:
            //<iq xmlns="jabber:client" from="localhost" to="test@localhost/MF" type="result" id="agsXMPP_5">
            //    <query xmlns="http://jabber.org/protocol/disco#items">
            //        <item name="Coversant XMPP Administractive Gateway" jid="administration.localhost" />
            //        <item jid="administration.localhost" node="http://winfessor.com/protocol/administration/policy" />
            //        <item name="pubsub - Publish Subscribe Gateway" jid="pubsub.localhost" />
            //        <item name="Open S2S Sessions" jid="s2s.localhost" />
            //        <item name="conference - Multi User Chat" jid="conference.localhost" />
            //        <item name="SoapBox User Directory" jid="users.localhost" />
            //        <item name="jabber - Default Jabber Gateway" jid="localhost" />
            //        <item jid="localhost" node="http://jabber.org/protocol/commands" />
            //    </query>
            //</iq>
            private void ProcessDiscoItemsIQ(IQ iq)
            {

                DiscoItemsIq discoItemsIq = new DiscoItemsIq(IqType.result);
                discoItemsIq.Namespace = agsXMPP.Uri.CLIENT;
                discoItemsIq.Id = iq.Id;
                discoItemsIq.From = iq.To;
                discoItemsIq.To = this.m_ClientAccount.JID;

                ///*******此处为配置扩展******************
                ///当前仅实现服务发现
                ///***************************************
                DiscoItem discoItem = null;
                foreach (BaseService service in this.m_Server.ServiceList)
                {

                    discoItem = new DiscoItem();
                    discoItem.Name = service.Name;
                    discoItem.Jid = service.JID;

                    if (iq.To.Bare.ToLower().Contains(service.JID.Bare.ToLower()))
                    {

                        discoItemsIq.Query.RemoveAllChildNodes();

                        if (service.ServiceType == ServiceType.GroupChat)
                        {
                            MucService muc = service as MucService;
                            if (service.JID.Bare.ToLower() == iq.To.Bare.ToLower())
                            {
                                //<iq from='macbeth.shakespeare.lit'
                                //    id='disco2'
                                //    to='hag66@shakespeare.lit/pda'
                                //    type='result'>
                                //  <query xmlns='http://jabber.org/protocol/disco#items'>
                                //    <item jid='heath@macbeth.shakespeare.lit'
                                //          name='A Lonely Heath'/>
                                //    <item jid='darkcave@macbeth.shakespeare.lit'
                                //          name='A Dark Cave'/>
                                //    <item jid='forres@macbeth.shakespeare.lit'
                                //          name='The Palace'/>
                                //    <item jid='inverness@macbeth.shakespeare.lit'
                                //          name='Macbeth&apos;s Castle'/>
                                //  </query>
                                //</iq>


                                foreach (KeyValuePair<string, ChatRoom> item in muc.GetRooms())
                                {
                                    discoItem = new DiscoItem();
                                    discoItem.Name = item.Key;
                                    discoItem.Jid = item.Value.JID;

                                    discoItemsIq.Query.AddDiscoItem(discoItem);

                                }


                            }
                            else if (iq.To.Bare.ToLower().EndsWith("@" + service.JID.Bare.ToLower()))
                            {

                            }
                            else
                            {

                            }

                        }
                        else if (service.ServiceType == ServiceType.ContactSearch)
                        {

                        }
                        else if (service.ServiceType == ServiceType.FileTransfer)
                        {

                        }
                        else
                        {

                        }

                        break;
                    }
                    else
                    {
                        discoItemsIq.Query.AddDiscoItem(discoItem);
                    }

                }

                Send(discoItemsIq);

            }

            //SEND: 
            //<iq xmlns="jabber:client" id="agsXMPP_11" type="get" to="users.localhost">
            //  <query xmlns="http://jabber.org/protocol/disco#info" />
            //</iq>
            //
            //RECV: 
            //<iq xmlns="jabber:client" from="users.localhost" to="test@localhost/MF" type="result" id="agsXMPP_11">
            //  <query xmlns="http://jabber.org/protocol/disco#info">
            //      <feature var="jabber:iq:time" />
            //      <feature var="jabber:iq:search" />
            //      <feature var="http://jabber.org/protocol/disco#info" />
            //      <feature var="jabber:iq:version" />
            //      <feature var="soapbox:limits" />
            //      <feature var="http://jabber.org/protocol/disco#items" />
            //      <identity name="SoapBox User Directory" category="directory" type="user" />
            //  </query>
            //</iq>
            private void ProcessDiscoInfoIQ(IQ iq)
            {

                agsXMPP.protocol.iq.disco.DiscoInfoIq discoInfoIq = new DiscoInfoIq(IqType.result);
                discoInfoIq.Namespace = agsXMPP.Uri.CLIENT;
                discoInfoIq.Id = iq.Id;
                discoInfoIq.From = iq.To;
                discoInfoIq.To = this.m_ClientAccount.JID;


                ///*******此处为配置扩展******************
                ///当前仅实现服务查找
                ///***************************************
                //RECV: 
                //<iq xmlns="jabber:client" id="agsXMPP_8" type="get" to="Proxy65@192.165.6.26">
                //    <query xmlns="http://jabber.org/protocol/disco#info" />
                //</iq>

                //SEND: 
                //<iq xmlns="jabber:client" type="result" id="agsXMPP_6" from="Search.SiteView.com" to="test@192.168.6.26:SiteView">
                //    <query xmlns="http://jabber.org/protocol/disco#info">
                //        <feature var="jabber:iq:time"/>
                //        <feature var="jabber:iq:search"/>
                //        <feature var="http://jabber.org/protocol/disco#info"/>
                //        <feature var="jabber:iq:version"/>
                //        <feature var="http://jabber.org/protocol/disco#items"/>
                //        <identity type="user" name="Site View MF Directory" category="Search"/>
                //    </query>
                //</iq>


                // <iq from='proxy.cachet.myjabber.net' to='gnauck@jabber.org/Exodus' type='result' id='jcl_19'>
                //  <query xmlns='http://jabber.org/protocol/disco#info'>
                //      <identity category='proxy' name='SOCKS5 Bytestreams Service' type='bytestreams'/>
                //      <feature var='http://jabber.org/protocol/bytestreams'/>
                //      <feature var='http://jabber.org/protocol/disco#info'/>
                //  </query>
                // </iq>

                System.Collections.Generic.List<string> vars = new System.Collections.Generic.List<string>();
                DiscoIdentity identity = null;

                foreach (BaseService service in this.m_Server.ServiceList)
                {
                    if (!iq.To.Bare.ToLower().Contains(service.JID.Bare.ToLower()))
                    {
                        continue;
                    }

                    identity = new DiscoIdentity(service.ServiceType.ToString(), service.Name, service.ServiceType.ToString());
                    if (service.ServiceType == ServiceType.ContactSearch)
                    {
                        vars.Add(agsXMPP.Uri.IQ_SEARCH);
                    }
                    else if (service.ServiceType == ServiceType.GroupChat)
                    {
                        vars.Add(agsXMPP.Uri.MUC);
                    }
                    else if (service.ServiceType == ServiceType.FileTransfer)
                    {
                        vars.Add(agsXMPP.Uri.BYTESTREAMS);
                    }
                    else
                    {

                    }

                    break;
                }

                DiscoFeature feature = null;
                foreach (string var in vars)
                {
                    feature = new DiscoFeature(var);
                    discoInfoIq.Query.AddFeature(feature);
                }

                discoInfoIq.Query.AddIdentity(identity);

                Send(discoInfoIq);

            }

            //SEND: 
            //<iq xmlns="jabber:client" id="agsXMPP_3" type="get" to="localhost">
            //    <query xmlns="jabber:iq:agents" />
            //</iq>
            //
            //RECV: 
            //<iq xmlns="jabber:client" from="localhost" to="test@localhost/MF" type="result" id="agsXMPP_3">
            //    <query xmlns="jabber:iq:agents" />
            //</iq>
            private void ProcessAgentsIQ(IQ iq)
            {
                AgentsIq agentsIq = new AgentsIq(IqType.result);
                agentsIq.Namespace = agsXMPP.Uri.CLIENT;
                agentsIq.Id = iq.Id;
                agentsIq.From = iq.To;
                agentsIq.To = this.m_ClientAccount.JID;

                ///*******此处为配置扩展******************
                ///当前仅代理网关仅为空
                ///***************************************

                Send(agentsIq);
            }

            private void ProcessOtherIQ(IQ iq)
            {
                Element child = iq.FirstChild;
                if (child.GetType() == typeof(agsXMPP.protocol.iq.bind.Bind))
                {
                    ProcessBind(iq);
                }
                else if (child.GetType() == typeof(agsXMPP.protocol.iq.session.Session))
                {
                    ProcessSession(iq);
                }
                else if (child.GetType() == typeof(agsXMPP.protocol.extensions.si.SI))
                {
                    ProcessSI(iq);
                }
                else if (child.GetType() == typeof(agsXMPP.protocol.iq.vcard.Vcard))
                {
                    ProcessVcard(iq);
                }
                else
                {

                }
            }

            private void ProcessVcard(IQ iq)
            {

                if (iq.Type == IqType.get)
                {
                    Jid to = iq.To;
                    foreach (Account account in this.m_Server.AccountManager.Accounts)
                    {
                        if (account.JID.Bare.ToLower() == iq.To.Bare.ToLower())
                        {
                            VcardIq newIQ = new VcardIq(IqType.result);
                            newIQ.Id = iq.Id;
                            newIQ.To = iq.To;

                            newIQ.Vcard.Fullname = account.UserID;
                            newIQ.Vcard.JabberId = account.JID;
                            newIQ.Vcard.Name = new Name("SiteView", "test", "test");
                            newIQ.Vcard.Nickname = account.UserName;
                            newIQ.Vcard.Organization = new Organization("SiteView", account.Company);
                            newIQ.Vcard.Role = account.Type.ToString();
                            newIQ.Vcard.Url = "http://www.siteview.com";
                            newIQ.Vcard.Birthday = DateTime.Now;
                            newIQ.Vcard.Photo = new Photo("http://www.siteview.com/siteview/images/logo.gif");

                            Send(newIQ);

                        }
                    }

                }
                else if (iq.Type == IqType.set)
                {

                }
                else
                {

                }
            }

            private void ProcessSI(IQ iq)
            {
                //Recived:
                //<iq xmlns="jabber:client" id="agsXMPP_14" to="test2@localhost/MiniClient" type="set">
                //    <si xmlns="http://jabber.org/protocol/si" profile="http://jabber.org/protocol/si/profile/file-transfer" id="365ac9e1-aa00-40f2-be54-b412cfeb9f89">
                //        <file xmlns="http://jabber.org/protocol/si/profile/file-transfer" name="新建 文本文档.txt" size="10515">
                //            <range/>
                //        </file>
                //        <feature xmlns="http://jabber.org/protocol/feature-neg">
                //            <x xmlns="jabber:x:data" type="form">
                //                <field type="list-single" var="stream-method">
                //                    <option>
                //                        <value>http://jabber.org/protocol/bytestreams</value>
                //                    </option>
                //                </field>
                //            </x>
                //        </feature>
                //    </si>
                //</iq>

                //SEND:
                //<iq xmlns="jabber:client" from="test@localhost/MiniClient" to="test2@localhost/MiniClient" type="set" id="agsXMPP_14">
                //    <si xmlns="http://jabber.org/protocol/si" profile="http://jabber.org/protocol/si/profile/file-transfer" id="365ac9e1-aa00-40f2-be54-b412cfeb9f89">
                //        <file xmlns="http://jabber.org/protocol/si/profile/file-transfer" size="10515" name="新建 文本文档.txt">
                //            <range/>
                //        </file>
                //        <feature xmlns="http://jabber.org/protocol/feature-neg">
                //            <x xmlns="jabber:x:data" type="form">
                //                <field type="list-single" var="stream-method">
                //                    <option>
                //                        <value>http://jabber.org/protocol/bytestreams</value>
                //                    </option>
                //                </field>
                //            </x>
                //        </feature>
                //    </si>
                //</iq>

                //<iq xmlns="jabber:client" from="test2@localhost/MiniClient" to="test@localhost/MiniClient" type="error" id="agsXMPP_14">
                //    <error code="403" type="cancel">
                //        <forbidden xmlns="urn:ietf:params:xml:ns:xmpp-stanzas"/>
                //        <text xmlns="urn:ietf:params:xml:ns:xmpp-stanzas" xml:lang="en"/>
                //    </error>
                //</iq>

                //<iq xmlns="jabber:client" from="test2@localhost/MiniClient" to="test@localhost/MiniClient" type="result" id="agsXMPP_15">
                //    <si xmlns="http://jabber.org/protocol/si" id="100a7ae5-b2b6-476d-b1d5-5edfee0ed87c">
                //        <feature xmlns="http://jabber.org/protocol/feature-neg">
                //            <x xmlns="jabber:x:data" type="submit">
                //                <field var="stream-method">
                //                    <value>http://jabber.org/protocol/bytestreams</value>
                //                </field>
                //            </x>
                //        </feature>
                //    </si>
                //</iq>

                //<iq xmlns="jabber:client" id="agsXMPP_16" to="test2@localhost/MiniClient" type="set">
                //    <query xmlns="http://jabber.org/protocol/bytestreams" sid="100a7ae5-b2b6-476d-b1d5-5edfee0ed87c">
                //        <streamhost jid="test@localhost/MiniClient" host="192.168.6.26" port="1000"/>
                //        <streamhost jid="proxy.ag-software.de" host="proxy.ag-software.de" port="7777"/>
                //    </query>
                //</iq>

                //<iq xmlns="jabber:client" from="test2@localhost/MiniClient" to="test@localhost/MiniClient" type="result" id="agsXMPP_16">
                //    <query xmlns="http://jabber.org/protocol/bytestreams">
                //        <streamhost-used jid="test@localhost/MiniClient"/>
                //    </query>
                //</iq>

                iq.From = this.m_ClientAccount.JID;

                Send(iq.To, iq);
                //foreach (Account account in this.m_Server.ClientConnections.Keys)
                //{
                //    if (account.JID.Bare == iq.To.Bare)
                //    {
                //        if (iq.To.Resource == null || iq.To.Resource == string.Empty)
                //        {
                //            this.m_Server.ClientConnections[account].Send(iq);
                //        }
                //        else
                //        {
                //            if (account.JID.Resource == iq.To.Resource)
                //            {
                //                this.m_Server.ClientConnections[account].Send(iq);
                //            }
                //        }
                //    }
                //}

            }

            private void ProcessBind(IQ iq)
            {
                Dictionary<string, XmppSeverConnection> bindedConnections = null;
                if (this.m_Server.ClientConnections.ContainsKey(this.m_ClientAccount))
                {
                    bindedConnections = this.m_Server.ClientConnections[this.m_ClientAccount];
                }

                if (bindedConnections == null)
                {
                    bindedConnections = new Dictionary<string, XmppSeverConnection>();
                }

                agsXMPP.protocol.iq.bind.Bind bind = iq.FirstChild as agsXMPP.protocol.iq.bind.Bind;

                strBindResource = bind.Resource;
                if (strBindResource == null)
                {
                    strBindResource = SessionID.CreateNewId();
                }

                if (bindedConnections.ContainsKey(strBindResource))
                {
                    strBindResource = SessionID.CreateNewId();
                }

                bindedConnections[strBindResource] = this;

                this.m_Server.ClientConnections[this.m_ClientAccount] = bindedConnections;

                agsXMPP.protocol.iq.bind.BindIq bindIq = new agsXMPP.protocol.iq.bind.BindIq(IqType.result);
                bindIq.Id = iq.Id;
                bindIq.Query.Jid = this.m_ClientAccount.JID;

                Send(bindIq);

            }

            private void ProcessSession(IQ iq)
            {

                agsXMPP.protocol.iq.session.SessionIq sessionIq = new agsXMPP.protocol.iq.session.SessionIq(IqType.result);

                sessionIq.Namespace = agsXMPP.Uri.CLIENT;
                sessionIq.Id = iq.Id;
                sessionIq.From = iq.To;
                sessionIq.To = this.m_ClientAccount.JID;

                Send(sessionIq);

            }

            private void ProcessRosterIQ(IQ iq)
            {
                bool bSend = false;
                if (iq.Type == IqType.get)
                {
                    // Send the roster
                    // we send a dummy roster here, you should retrieve it from a
                    // database or some kind of directory (LDAP, AD etc...)

                    RosterIq rosterIq = new RosterIq(IqType.result);
                    rosterIq.Namespace = agsXMPP.Uri.CLIENT;
                    rosterIq.Id = iq.Id;
                    rosterIq.From = iq.To;
                    rosterIq.To = this.m_ClientAccount.JID;

                    foreach (Friend friend in this.m_ClientAccount.Friends)
                    {
                        RosterItem ri = new RosterItem();
                        ri.Name = friend.Nick;
                        ri.Subscription = friend.SubscriptionType;

                        ////............
                        //friend.JID.Resource = friend.Resource[0];

                        ri.Jid = friend.JID;
                        foreach (string strGroup in friend.Groups)
                        {
                            ri.AddGroup(strGroup);
                        }

                        rosterIq.Query.AddRosterItem(ri);
                    }

                    Send(rosterIq);

                }
                else if (iq.Type == IqType.set)
                {
                    //Received: 
                    //<iq xmlns="jabber:client" id="agsXMPP_18" type="set">
                    //    <query xmlns="jabber:iq:roster">
                    //        <item jid="test2@localhost"/>
                    //    </query>
                    //</iq>

                    //Send: 
                    //<iq xmlns="jabber:client" type="set" id="712">
                    //    <query xmlns="jabber:iq:roster">
                    //        <item name="test2" jid="test2@localhost" subscription="none"/>
                    //    </query>
                    //</iq>

                    //Send: 
                    //<iq xmlns="jabber:client" from="test@localhost/MF" to="test@localhost/MF" type="result" id="agsXMPP_18" />

                    Roster oldRoster = iq.Query as Roster;

                    RosterItem[] rosterItems = oldRoster.GetRoster();

                    Friend friend = null;

                    foreach (RosterItem rosterItem in rosterItems)
                    {
                        if (rosterItem.HasAttribute("subscription"))
                        {
                            if (rosterItem.Subscription == SubscriptionType.remove)
                            {
                                friend = this.m_ClientAccount.FindFriend(rosterItem.Jid.ToString());
                                if (friend == null)
                                {
                                    IQ error = new IQ(IqType.error);
                                    error.Namespace = iq.Namespace;
                                    error.Id = iq.Id;
                                    error.To = this.m_ClientAccount.JID;

                                    Send(error);
                                }

                                this.m_ClientAccount.RemoveFriend(friend);


                                RosterIq newRosterIq = null;
                                RosterItem ri = null;

                                Presence newPresence = null;

                                Account contactAccount = this.m_Server.AccountManager.FindAccount(rosterItem.Jid.ToString());
                                Friend userFriend = contactAccount.FindFriend(this.m_ClientAccount.JID.ToString());
                                if (userFriend == null)
                                {

                                    //RECV: 
                                    //<iq xmlns="jabber:client" id="agsXMPP_17" type="set">
                                    //    <query xmlns="jabber:iq:roster">
                                    //        <item jid="test@localhost" subscription="remove" />
                                    //    </query>
                                    //</iq>

                                    //SEND: <iq type="result" id="agsXMPP_17" to="test2@localhost/MF" from="test2@localhost/MF" />

                                    IQ result = new IQ(IqType.result);
                                    result.Id = iq.Id;
                                    result.From = this.m_ClientAccount.JID;
                                    result.To = this.m_ClientAccount.JID;
                                    Send(result);


                                    //SEND: 
                                    //<iq id="221" type="set">
                                    //    <query xmlns="jabber:iq:roster">
                                    //        <item jid="test@localhost" subscription="remove" />
                                    //    </query>
                                    //</iq>

                                    newRosterIq = new RosterIq(IqType.set);
                                    newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                    ri = new RosterItem();
                                    ri.Name = rosterItem.Name;
                                    ri.Jid = rosterItem.Jid;
                                    ri.Subscription = rosterItem.Subscription;

                                    newRosterIq.Query.AddRosterItem(ri);

                                    Send(newRosterIq);


                                    //SEND: <presence from="test2@localhost/MF" xml:lang="zh-cn" type="unavailable" to="test@localhost/MF" />
                                    newPresence = new Presence();
                                    newPresence.From = this.m_ClientAccount.JID;
                                    newPresence.To = rosterItem.Jid;
                                    newPresence.Type = PresenceType.unavailable;
                                    newPresence.Language = this.objClientlanguage.Name;

                                    bSend = Send(newPresence.To, newPresence);
                                    if (!bSend)
                                    {

                                    }

                                }
                                else
                                {
                                    if (userFriend.SubscriptionType == SubscriptionType.both)
                                    {

                                        userFriend.SubscriptionType = SubscriptionType.to;
                                        userFriend.Save();

                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = userFriend.Nick;
                                        ri.Jid = userFriend.JID;
                                        ri.Subscription = userFriend.SubscriptionType;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        bSend = Send(rosterItem.Jid, newRosterIq);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence = new Presence();
                                        newPresence.From = this.m_ClientAccount.JID;
                                        newPresence.To = rosterItem.Jid;

                                        newPresence.Type = PresenceType.unsubscribe;
                                        bSend = Send(rosterItem.Jid, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        userFriend.SubscriptionType = SubscriptionType.none;
                                        userFriend.Save();

                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = userFriend.Nick;
                                        ri.Jid = userFriend.JID;
                                        ri.Subscription = userFriend.SubscriptionType;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        bSend = Send(rosterItem.Jid, newRosterIq);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence.Type = PresenceType.unsubscribed;
                                        bSend = Send(rosterItem.Jid, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence = new Presence();
                                        newPresence.From = rosterItem.Jid;
                                        newPresence.To = this.m_ClientAccount.JID;
                                        newPresence.Type = PresenceType.unavailable;
                                        newPresence.Language = this.objClientlanguage.Name;

                                        bSend = Send(newPresence.To, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence.SwitchDirection();
                                        bSend = Send(newPresence.To, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        IQ result = new IQ(IqType.result);
                                        result.Id = iq.Id;
                                        result.From = this.m_ClientAccount.JID;
                                        result.To = this.m_ClientAccount.JID;
                                        Send(result);


                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = rosterItem.Name;
                                        ri.Jid = rosterItem.Jid;
                                        ri.Subscription = rosterItem.Subscription;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        Send(newRosterIq);


                                    }
                                    else if (userFriend.SubscriptionType == SubscriptionType.from)
                                    {
                                        contactAccount.RemoveFriend(userFriend);
                                        contactAccount.Save();

                                        newPresence = new Presence();
                                        newPresence.From = this.m_ClientAccount.JID;
                                        newPresence.To = rosterItem.Jid;
                                        newPresence.Type = PresenceType.unavailable;
                                        newPresence.Language = this.objClientlanguage.Name;

                                        bSend = Send(newPresence.To, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        IQ result = new IQ(IqType.result);
                                        result.Id = iq.Id;
                                        result.From = this.m_ClientAccount.JID;
                                        result.To = this.m_ClientAccount.JID;
                                        Send(result);


                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = rosterItem.Name;
                                        ri.Jid = rosterItem.Jid;
                                        ri.Subscription = rosterItem.Subscription;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        Send(newRosterIq);

                                    }
                                    else if (userFriend.SubscriptionType == SubscriptionType.to)
                                    {
                                        userFriend.SubscriptionType = SubscriptionType.none;
                                        userFriend.Save();

                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = userFriend.Nick;
                                        ri.Jid = userFriend.JID;
                                        ri.Subscription = userFriend.SubscriptionType;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        bSend = Send(rosterItem.Jid, newRosterIq);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence = new Presence();
                                        newPresence.From = this.m_ClientAccount.JID;
                                        newPresence.To = rosterItem.Jid;
                                        newPresence.Type = PresenceType.unsubscribed;
                                        bSend = Send(newPresence.To, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        newPresence = new Presence();
                                        newPresence.From = this.m_ClientAccount.JID;
                                        newPresence.To = rosterItem.Jid;
                                        newPresence.Type = PresenceType.unavailable;
                                        newPresence.Language = this.objClientlanguage.Name;

                                        bSend = Send(newPresence.To, newPresence);
                                        if (!bSend)
                                        {

                                        }

                                        IQ result = new IQ(IqType.result);
                                        result.Id = iq.Id;
                                        result.From = this.m_ClientAccount.JID;
                                        result.To = this.m_ClientAccount.JID;
                                        Send(result);


                                        newRosterIq = new RosterIq(IqType.set);
                                        newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                        ri = new RosterItem();
                                        ri.Name = rosterItem.Name;
                                        ri.Jid = rosterItem.Jid;
                                        ri.Subscription = rosterItem.Subscription;

                                        newRosterIq.Query.AddRosterItem(ri);

                                        Send(newRosterIq);


                                    }
                                    else
                                    {

                                    }
                                }

                                ///Save friend Roster to Xml
                                this.m_Server.AccountManager.Save();

                                return;

                            }
                            else
                            {
                                friend = this.m_ClientAccount.FindFriend(rosterItem.Jid.ToString());
                                if (friend == null)
                                {
                                    friend = this.m_ClientAccount.AddFriend();
                                }

                                ///******************************************************
                                ///JID中已经包含有Company，Friend中是否还需要Company信息
                                ///******************************************************
                                friend.JID = rosterItem.Jid;
                                friend.Nick = rosterItem.Name;

                                friend.SubscriptionType = rosterItem.Subscription;
                                friend.SubscriptionStatus = int.Parse(rosterItem.Ask.ToString("D"));

                                foreach (Element groupItem in rosterItem.GetGroups())
                                {
                                    friend.AddGroup(groupItem.InnerXml);
                                }
                                friend.Save();


                                //if (friend.Groups.Count == 0)
                                //{
                                //    friend.AddGroup(friend.Company);
                                //}

                                // push roster set iq to all the resurce
                                RosterIq newRosterIq = new RosterIq(IqType.set);
                                newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                                RosterItem ri = new RosterItem();
                                if (rosterItem.Name == null || rosterItem.Name == string.Empty)
                                {
                                    ri.Name = rosterItem.Jid.User;
                                }
                                else
                                {
                                    ri.Name = rosterItem.Name;
                                }

                                ri.Jid = rosterItem.Jid;
                                ri.Subscription = SubscriptionType.none;

                                ///******************************************************
                                ///订阅用户的分组信息需要考虑？
                                ///******************************************************
                                foreach (Element groupItem in rosterItem.GetGroups())
                                {
                                    ri.AddGroup(groupItem.InnerXml);
                                }

                                newRosterIq.Query.AddRosterItem(ri);

                                //Push roster update to all client
                                //foreach (Account account in this.m_Server.ClientConnections.Keys)
                                //{
                                //    if (account.JID.Bare.ToLower() == this.m_ClientAccount.JID.Bare.ToLower())
                                //    {
                                //        //this.m_Server.ClientConnections[account].Send(newRosterIq);
                                //        SendToAllResource(account, newRosterIq);
                                //    }
                                //}

                                bSend = Send(this.m_ClientAccount, newRosterIq);
                                if (!bSend)
                                {

                                }

                            }
                        }
                        else
                        {
                            friend = this.m_ClientAccount.FindFriend(rosterItem.Jid.ToString());
                            if (friend == null)
                            {
                                friend = this.m_ClientAccount.AddFriend();

                                ///******************************************************
                                ///JID中已经包含有Company，Friend中是否还需要Company信息
                                ///******************************************************
                                friend.JID = rosterItem.Jid;
                                friend.SubscriptionType = SubscriptionType.none;
                                friend.SubscriptionStatus = -1;
                            }

                            friend.Nick = rosterItem.Name;

                            friend.Groups.Clear();

                            foreach (Element groupItem in rosterItem.GetGroups())
                            {
                                friend.AddGroup(groupItem.InnerXml);
                            }

                            friend.Save();

                            //if (friend.Groups.Count == 0)
                            //{
                            //    friend.AddGroup(friend.Company);
                            //}

                            // push roster set iq to all the resurce
                            RosterIq newRosterIq = new RosterIq(IqType.set);
                            newRosterIq.Namespace = agsXMPP.Uri.CLIENT;

                            RosterItem ri = new RosterItem();
                            if (rosterItem.Name == null || rosterItem.Name == string.Empty)
                            {
                                ri.Name = rosterItem.Jid.User;
                            }
                            else
                            {
                                ri.Name = rosterItem.Name;
                            }
                            ri.Jid = rosterItem.Jid;
                            ri.Subscription = friend.SubscriptionType;

                            ///******************************************************
                            ///订阅用户的分组信息需要考虑？
                            ///******************************************************
                            foreach (string strGroup in friend.Groups)
                            {
                                ri.AddGroup(strGroup);
                            }

                            newRosterIq.Query.AddRosterItem(ri);

                            //Push roster update to all client
                            //foreach (Account account in this.m_Server.ClientConnections.Keys)
                            //{
                            //    if (account.JID.Bare.ToLower() == this.m_ClientAccount.JID.Bare.ToLower())
                            //    {
                            //        //this.m_Server.ClientConnections[account].Send(newRosterIq);
                            //        SendToAllResource(account, newRosterIq);
                            //    }
                            //}

                            bSend = Send(this.m_ClientAccount, newRosterIq);
                            if (!bSend)
                            {

                            }

                        }


                        //Send Result IQ
                        IQ newIq = new IQ(IqType.result);
                        newIq.Namespace = agsXMPP.Uri.CLIENT;
                        newIq.Id = iq.Id;
                        //newIq.From = this.m_ClientAccount.JID;
                        //newIq.To = this.m_ClientAccount.JID;
                        Send(newIq);

                        ///Save friend Roster to Xml
                        this.m_Server.AccountManager.Save();
                    }

                }
            }

        }
    }
}