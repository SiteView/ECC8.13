using System;
using System.Collections.Generic;
using System.Text;
//using SiteView.Ecc.WSClient.XFireWebService;
using SiteView.Ecc.Core;
//using SiteView.Ecc.WSClient;
using System.Collections.Specialized;
using SiteView.Ecc.MMC.Nodes;
using SiteView.Ecc.Core.Dao;
using SiteView.Ecc.Core.Models;
using System.ComponentModel;
using SiteView.Ecc.MMC.Forms;
using SiteView.PluginFramework;
using System.Windows.Forms;
using SiteView.Ecc.MMC.UserContorls;
using SiteView.Ecc.MMC.Views;
using System.Threading;
using SiteView.Ecc.WSClient;
//using Microsoft.ManagementConsole;
//using SiteView.PluginFramework.MMC;
namespace Logistics
{
      namespace SubServer
      {
            public class GetSVDBDataBuffer
            {

                  private static List<IList<NameValueCollection>> m_DataBuffer = new List<IList<NameValueCollection>>();

                  //public static List<GetSVDBDataBuffer> m_GetSVDBDataBuffer = new List<GetSVDBDataBuffer>();
                  public static GetSVDBDataBuffer m_GetSVDBDataBuffer = null;
                  private BackgroundWorker Worker = null;
                  private System.Windows.Forms.Timer timer = null;
                  public GetSVDBDataBuffer()
                  {

                        //m_GetSVDBDataBuffer = this;
                        Worker = new BackgroundWorker();
                        Worker.DoWork += new DoWorkEventHandler(Worker_DoWork);
                        timer = new System.Windows.Forms.Timer();
                        timer.Tick += new EventHandler(timer_Tick);
                        timer.Interval = 180000;
                       

                  }

                  void timer_Tick(object sender, EventArgs e)
                  {
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—" + "GetSVDBDataBuffer" + "—timer_Tick_B");
                        if (!Worker.IsBusy)
                        {
                              Worker.RunWorkerAsync();
                              Log.WriteFiles(DateTime.Now.ToString() + "—" + "GetSVDBDataBuffer" + "—timer_Tick_A");
                        }
                  }

                  void Worker_DoWork(object sender, DoWorkEventArgs e)
                  {
                        GetAllSVDBData();
                  }

                  public static GetSVDBDataBuffer GetObj()
                  {
                        if (m_GetSVDBDataBuffer == null)
                        {
                              m_GetSVDBDataBuffer = new GetSVDBDataBuffer();
                        }
                        return m_GetSVDBDataBuffer;
                      
                  }

                  public void StartProcess()
                  {
                        timer.Enabled = true;
                        timer.Start();
                        Worker.RunWorkerAsync();
                        ErrorLog Log = new ErrorLog();
                        Log.WriteFiles(DateTime.Now.ToString() + "—" + "GetSVDBDataBuffer" + "—StartProcess");
                  }

                  public void GetAllSVDBData()
                  {
                        
                        try
                        {
                              ErrorLog Log = new ErrorLog();
                              Log.WriteFiles(DateTime.Now.ToString() + "—" + "GetSVDBDataBuffer" + "—GetAllSVDBData_A");
                              string XFireUrl = Log.ReadFile();
                              XFireUrl = XFireUrl.Split(new char[1] { '=' })[1].Trim();
                              UserPermissionContext.Instance.Url = "http://"+ConfigManager.XfireUrl +"//webservice//InterfaceEccService";

                              ITreeDao treeDao = MicroKernelUtil.GetDefaultKernel()[typeof(ITreeDao)] as ITreeDao;
                              IList<NameValueCollection> tree = treeDao.GetAll2();
                              Dictionary<XmppSeverConnection, string> ReturnStr = new Dictionary<XmppSeverConnection, string>();
                              if (m_DataBuffer.Count < 1)
                              {
                                    m_DataBuffer.Add(tree);
                              }
                              else
                              {
                                    ReturnStr = CompareDataState(tree);
                                    m_DataBuffer.RemoveAt(0);
                                    m_DataBuffer.Add(tree);
                                    if (ReturnStr.Count == 0)
                                    {
                                          return;
                                    }
                                    foreach (XmppSeverConnection key in ReturnStr.Keys)
                                    {
                                          
                                          if (ReturnStr[key] != "Norefresh")
                                          {

                                                

                                                List<string> SentStrList = new List<string>();

                                                //if (ReturnStr.Length > 8192)
                                                //{
                                                //      SentStrList = GetbatchdisableSendList(ReturnStr, "refresh<");

                                                //}
                                                //else
                                                {
                                                      string sendStr = ReturnStr[key];
                                                      sendStr = sendStr + ">stop";
                                                      key.Send(sendStr);
                                                      //XmppServer.ClientConnectionList[i].Send(SentStrList[j]);
                                                      System.Threading.Thread.Sleep(1000);
                                                }

                                                //if (XmppServer.IsSendData)
                                                //{
                                                //if (SentStrList == null || SentStrList.Count == 0)
                                                //{
                                                //      for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                                //      {
                                                //            XmppServer.ClientConnectionList[i].Send(ReturnStr);
                                                //            System.Threading.Thread.Sleep(1000);
                                                //      }
                                                //}
                                                //else
                                                //{
                                                //      for (int j = 0; j < SentStrList.Count; j++)
                                                //      {
                                                //            for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                                //            {
                                                //                  XmppServer.ClientConnectionList[i].Send(SentStrList[j]);
                                                //                  System.Threading.Thread.Sleep(1000);
                                                //            }
                                                //      }
                                                //}

                                                //      System.Threading.Thread.Sleep(5000);
                                                //      List<string> ClientResponseKeyList = new List<string>();
                                                //      if (XmppServer.ClientResponseList.Count > 0)
                                                //      {
                                                //            foreach (string key in XmppServer.ClientResponseList.Keys)
                                                //            {
                                                //                  ClientResponseKeyList.Add(key);
                                                //                  if (!XmppServer.ClientResponseList[key])
                                                //                  {
                                                //                        for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                                //                        {
                                                //                              if (XmppServer.ClientConnectionList[i].ClientIPAddress == key)
                                                //                              {
                                                //                                    if (SentStrList == null || SentStrList.Count == 0)
                                                //                                    {
                                                //                                          //for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                                //                                          {
                                                //                                                XmppServer.ClientConnectionList[i].Send(ReturnStr);
                                                //                                                //System.Threading.Thread.Sleep(1000);
                                                //                                          }
                                                //                                    }
                                                //                                    else
                                                //                                    {
                                                //                                          for (int j = 0; j < SentStrList.Count; j++)
                                                //                                          {
                                                //                                                //for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                                //                                                {
                                                //                                                      XmppServer.ClientConnectionList[i].Send(SentStrList[j]);
                                                //                                                      //System.Threading.Thread.Sleep(1000);
                                                //                                                }
                                                //                                          }
                                                //                                    }
                                                //                              }
                                                //                        }


                                                //                  }
                                                //                  else
                                                //                  {

                                                //                  }
                                                //            }
                                                //            for (int i = 0; i < ClientResponseKeyList.Count; i++)
                                                //            {
                                                //                  if (XmppServer.ClientResponseList.ContainsKey(ClientResponseKeyList[i]))
                                                //                  {
                                                //                        XmppServer.ClientResponseList[ClientResponseKeyList[i]] = false;
                                                //                  }
                                                //            }
                                                //      }

                                                //}
                                                Log.WriteFiles(DateTime.Now.ToString() + "—" + "GetSVDBDataBuffer" + "—GetAllSVDBData_B");

                                          }
                                    }
                              }

                        }
                        catch (Exception ex)
                        {
                        }

                        
                  }

                  public Dictionary<XmppSeverConnection, string> CompareDataState(IList<NameValueCollection> tree)
                  {
                        try
                        {
                              string ReturnStr = "";
                              Dictionary<XmppSeverConnection, string> returnList = new Dictionary<XmppSeverConnection, string>();
                              //bool IsFind1 = true;
                              if (m_DataBuffer.Count == 1)
                              {
                                    //bool IsFind = false;
                                    //bool IsStateC = false;
                                    if (tree == null)
                                    {
                                          return returnList;
                                    }
                                    Dictionary<XmppSeverConnection, List<string>> MonitorIdList = new Dictionary<XmppSeverConnection, List<string>>();
                                    if (XmppServer.GlobeEntityIdList != null || XmppServer.GlobeEntityIdList.Count != 0)
                                    {

                                          foreach (XmppSeverConnection key in XmppServer.GlobeEntityIdList.Keys)
                                          {


                                                if (XmppServer.GlobeEntityIdList[key] != null && XmppServer.GlobeEntityIdList[key] != "-")
                                                {
                                                      foreach (NameValueCollection obj in tree)
                                                      {

                                                            string type = obj["type"];
                                                            string svid = obj["sv_id"];


                                                            if (type == "monitor")
                                                            {

                                                                  if (GetParentId(svid) == XmppServer.GlobeEntityIdList[key])
                                                                  {
                                                                        //MonitorIdList.Add(svid);
                                                                        if (!MonitorIdList.ContainsKey(key))
                                                                        {
                                                                              MonitorIdList.Add(key, new List<string>());
                                                                              MonitorIdList[key].Add(svid);
                                                                        }
                                                                        else
                                                                        {
                                                                              MonitorIdList[key].Add(svid);
                                                                        }
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }
                                    //IMonitorDao monitorDao = MicroKernelUtil.GetDefaultKernel()["MonitorDao"] as IMonitorDao;
                                    //SiteView.Ecc.Core.Models.Monitor[] monitors = monitorDao.FindByParentId(XmppServer.GlobeEntityId, false);
                                    
                                    //for (int i = 0; i < monitors.Length; i++)
                                    //{
                                    //      MonitorIdList.Add(monitors[i].ID);
                                    //}
                                   

                                    Dictionary<string, NameValueCollection> OldSV_IdList = new Dictionary<string, NameValueCollection>();
                                    Dictionary<string, NameValueCollection> NewSV_IdList = new Dictionary<string, NameValueCollection>();
                                    for (int i = 0; i < m_DataBuffer[0].Count; i++)
                                    {
                                          //if (m_DataBuffer[0][i]["type"] == "monitor")
                                          {
                                                if (!OldSV_IdList.ContainsKey(m_DataBuffer[0][i]["sv_id"]))
                                                {
                                                      OldSV_IdList.Add(m_DataBuffer[0][i]["sv_id"], m_DataBuffer[0][i]);
                                                }
                                          }
                                          
                                    }


                                    for (int i = 0; i < tree.Count; i++)
                                    {
                                          //if (tree[i]["type"] == "monitor")
                                          {
                                                if (!NewSV_IdList.ContainsKey(tree[i]["sv_id"]))
                                                {
                                                      NewSV_IdList.Add(tree[i]["sv_id"], tree[i]);
                                                }
                                          }

                                    }
                                    //List<string> 
                                    //List<string> DeleteList = new List<string>();
                                    List<string> StateCList = new List<string>();
                                    Dictionary<string, string> DstrCList = new Dictionary<string, string>();
                                    List<string> CreattimeCList = new List<string>();
                                    Dictionary<XmppSeverConnection, Dictionary<string, string>> DstrCListClient = new Dictionary<XmppSeverConnection, Dictionary<string, string>>();
                                    Dictionary<XmppSeverConnection, List<string>> CreattimeCListClient = new Dictionary<XmppSeverConnection, List<string>>();
                                    foreach (string key in OldSV_IdList.Keys)
                                    {
                                          //if (!NewSV_IdList.ContainsKey(key))
                                          //{
                                          //      DeleteList.Add(key);
                                          //}
                                          //else
                                          {
                                                if (OldSV_IdList[key]["status"] != NewSV_IdList[key]["status"])
                                                {
                                                     
                                                      StateCList.Add(key);
                                                }
                                                //foreach (string key1 in MonitorIdList.Keys)
                                                {
                                                      //if (MonitorIdList[key1].Contains(key))
                                                      {
                                                            if (OldSV_IdList[key]["type"] == "monitor")
                                                            {

                                                                  if (OldSV_IdList[key]["dstr"] != NewSV_IdList[key]["dstr"])
                                                                  {
                                                                        string CompareDstrStr = "";
                                                                        if (!OldSV_IdList[key]["dstr"].Contains(","))
                                                                        {
                                                                              CompareDstrStr = NewSV_IdList[key]["dstr"];
                                                                        }
                                                                        else
                                                                        {
                                                                              int OldSVLength = OldSV_IdList[key]["dstr"].Split(new char[1] { ',' }).Length;
                                                                              int NewSVLength = NewSV_IdList[key]["dstr"].Split(new char[1] { ',' }).Length;
                                                                              for (int i = 0; i < OldSVLength; i++)
                                                                              {

                                                                                    for (int j = 0; j < NewSVLength; j++)
                                                                                    {
                                                                                          if (i == j)
                                                                                          {
                                                                                                string OldStr = OldSV_IdList[key]["dstr"].Split(new char[1] { ',' })[i];
                                                                                                string NewStr = NewSV_IdList[key]["dstr"].Split(new char[1] { ',' })[j];
                                                                                                if (OldStr == NewStr)
                                                                                                {
                                                                                                      CompareDstrStr = CompareDstrStr + "-,";
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                      CompareDstrStr = CompareDstrStr + NewStr + ",";
                                                                                                }
                                                                                                break;
                                                                                          }

                                                                                    }
                                                                              }
                                                                        }
                                                                        DstrCList.Add(key, CompareDstrStr);
                                                                  }
                                                                  //if (OldSV_IdList[key]["dstr"] != NewSV_IdList[key]["dstr"])
                                                                  //{
                                                                  //      DstrCList.Add(key, CompareDstrStr);
                                                                  //}
                                                                  if (OldSV_IdList[key]["creat_time"] != NewSV_IdList[key]["creat_time"])
                                                                  {
                                                                        CreattimeCList.Add(key);
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }

                                    foreach (XmppSeverConnection key1 in MonitorIdList.Keys)
                                    {
                                          for (int i = 0; i < MonitorIdList[key1].Count; i++)
                                          {
                                                for(int j = 0;j< CreattimeCList.Count;j++)
                                                {
                                                    if(MonitorIdList[key1].Contains(CreattimeCList[j]))
                                                    {
                                                          if (!CreattimeCListClient.ContainsKey(key1))
                                                          {
                                                                CreattimeCListClient.Add(key1, new List<string>());
                                                                CreattimeCListClient[key1].Add(CreattimeCList[j]);
                                                          }
                                                          else
                                                          {
                                                                if (!CreattimeCListClient[key1].Contains(CreattimeCList[j]))
                                                                {
                                                                      CreattimeCListClient[key1].Add(CreattimeCList[j]);
                                                                }
                                                          }
                                                    }
                                                }
                                                foreach (string key in DstrCList.Keys)
                                                {
                                                      if (MonitorIdList[key1].Contains(key))
                                                      {
                                                            if (!DstrCListClient.ContainsKey(key1))
                                                            {
                                                                  DstrCListClient.Add(key1, new Dictionary<string, string>());
                                                                  DstrCListClient[key1].Add(key, DstrCList[key]);
                                                            }
                                                            else
                                                            {
                                                                  if (!DstrCListClient[key1].ContainsKey(key))
                                                                  {
                                                                        DstrCListClient[key1].Add(key, DstrCList[key]);
                                                                  }
                                                            }
                                                      }
                                                }
                                                
                                               
                                          }
                                    }
                                    //List<string> AddList = new List<string>();

                                    //foreach (string key in NewSV_IdList.Keys)
                                    //{
                                    //      if (!OldSV_IdList.ContainsKey(key))
                                    //      {
                                    //            AddList.Add(key);
                                    //      }
                                    //}
                                    
                                    //if (DeleteList.Count == 0 && AddList.Count == 0 && StateCList.Count == 0 && DstrCList.Count == 0 && CreattimeCList.Count == 0)
                                    if (XmppServer.ClientConnectionList.Count == 0)
                                    {
                                          return returnList;
                                    }
                                    for (int i = 0; i < XmppServer.ClientConnectionList.Count; i++)
                                    {
                                          if (!XmppServer.ClientConnectionList[i].m_Sock.Connected)
                                          {
                                                continue;
                                          }
                                          if (StateCList.Count == 0 && DstrCList.Count == 0 && CreattimeCList.Count == 0)
                                          {
                                                ReturnStr = "Norefresh";
                                                if (!returnList.ContainsKey(XmppServer.ClientConnectionList[i]))
                                                {
                                                      returnList.Add(XmppServer.ClientConnectionList[i], ReturnStr);
                                                }
                                                
                                          }
                                          else
                                          {
                                                ReturnStr = "refresh<";
                                                //for (int i = 0; i < DeleteList.Count; i++)
                                                //{
                                                //      ReturnStr = ReturnStr + "d" + DeleteList[i]+ "/";
                                                //}
                                                //for (int i = 0; i < AddList.Count; i++)
                                                //{
                                                //      ReturnStr = ReturnStr + "a" + AddList[i] + "/";
                                                //}
                                                for (int j = 0; j < StateCList.Count; j++)
                                                {
                                                      if (NewSV_IdList.ContainsKey(StateCList[j]))
                                                      {
                                                            ReturnStr = ReturnStr + "r" + StateCList[j] + "," + NewSV_IdList[StateCList[j]]["status"] + "/";
                                                      }
                                                }
                                                if (DstrCListClient.ContainsKey(XmppServer.ClientConnectionList[i]))
                                                {
                                                      Dictionary<string, string> DstrCListTmp = DstrCListClient[XmppServer.ClientConnectionList[i]];
                                                      foreach (string key in DstrCListTmp.Keys)
                                                      {
                                                            ReturnStr = ReturnStr + "s" + key + "," + DstrCListTmp[key] + "/";//NewSV_IdList[DstrCList[i]]["dstr"] + "/";
                                                      }
                                                }
                                                if (CreattimeCListClient.ContainsKey(XmppServer.ClientConnectionList[i]))
                                                {
                                                      List<string> CreattimeCListTmp = CreattimeCListClient[XmppServer.ClientConnectionList[i]];
                                                      for (int j = 0; j < CreattimeCListTmp.Count; j++)
                                                      {
                                                            ReturnStr = ReturnStr + "t" + CreattimeCListTmp[j] + "," + NewSV_IdList[CreattimeCListTmp[j]]["creat_time"] + "/";
                                                      }
                                                }
                                                if (!returnList.ContainsKey(XmppServer.ClientConnectionList[i]))
                                                {
                                                      returnList.Add(XmppServer.ClientConnectionList[i], ReturnStr);
                                                }
                                          }
                                    }
                                    return returnList;
                                    
                                    //if (m_DataBuffer[0].Count != tree.Count)
                                    //{
                                    //      IsFind1 = false;
                                    //}



                                    //for (int i = 0; i < m_DataBuffer[0].Count; i++)
                                    //{

                                    //      for (int j = 0; j < tree.Count; j++)
                                    //      {
                                    //            if (m_DataBuffer[0][i]["sv_id"] == tree[j]["sv_id"])
                                    //            {
                                    //                  IsFind = true;
                                    //                  if (m_DataBuffer[0][i]["type"] == "monitor" && m_DataBuffer[0][i]["status"] != tree[j]["status"])
                                    //                  {
                                    //                        IsStateC = true;

                                    //                  }
                                    //                  break;

                                    //            }
                                    //            IsFind = false;
                                    //      }

                                    //      if (!IsFind)
                                    //      {
                                    //            IsFind1 = false;
                                    //      }
                                    //      if (!IsFind1 && IsStateC)
                                    //      {
                                    //            return "refresh1,refresh2";
                                    //      }
                                    //      //if (!IsFind)
                                    //      //{
                                    //      //      return true;
                                    //      //}

                                    //}
                                    //if (!IsFind1 && IsStateC)
                                    //{
                                    //      return "refresh1,refresh2";
                                    //}
                                    //if (!IsFind1 && !IsStateC)
                                    //{
                                    //      return "refresh1";
                                    //}
                                    //if (IsFind1 && IsStateC)
                                    //{
                                    //      return "refresh2";
                                    //}
                                    ////if(!IsFind)
                              }
                              return null;
                        }
                        catch (Exception ex)
                        {
                              return null;
                        }
                  }
                  private string GetParentId(string subId)
                  {
                        try
                        {
                              return subId.Remove(subId.LastIndexOf("."));
                        }
                        catch (Exception ex)
                        {
                              //Log.LogManage.cache(DateTime.Now.ToString() + "—" + "MonitorBufferThread" + "—GetParentId(string subId)—" + ex.Message);
                              return "";

                        }
                  }

                  private List<string> GetbatchdisableSendList(string SentStr1, string FJStr)
                  {

                        string trunkStr = "";
                        List<string> SentStrList = new List<string>();
                        bool flag = false;
                        try
                        {
                              while (SentStr1.Length > 8192)
                              {
                                    //string[] strTmp;
                                    string tmp = "";
                                    //int length;
                                    //length = SentStr1.Substring(0, 8192).Split(new char[] { ',' }).Length;
                                    trunkStr = SentStr1.Substring(0, 8192).Substring(SentStr1.Substring(0, 8192).LastIndexOf("/") + 1);
                                    if (flag)
                                    {
                                          tmp = FJStr + trunkStr + SentStr1.Substring(0, 8192).Remove(SentStr1.Substring(0, 8192).LastIndexOf("/")) + ">";
                                    }
                                    else
                                    {
                                          tmp = SentStr1.Substring(0, 8192).Remove(SentStr1.Substring(0, 8192).LastIndexOf("/")) + ">";
                                    }
                                    SentStrList.Add(tmp);
                                    SentStr1 = SentStr1.Substring(8191);
                                    flag = true;
                              }
                              SentStrList.Add(FJStr + trunkStr + SentStr1);
                              if (SentStrList.Count > 0)
                              {
                                  SentStrList[SentStrList.Count - 1] = SentStrList[SentStrList.Count - 1] + "stop";
                              }
                              return SentStrList;
                        }
                        catch (Exception ex)
                        {
                              //Log.LogManage.cache(DateTime.Now.ToString() + "—" + "XMPPClient" + "—GetbatchdisableSendList1—" + ex.Message);
                              return SentStrList;
                        }
                  }

                  //private void UserLogin()
                  //{
                  //      try
                  //      {
                  //            if (String.IsNullOrEmpty(this.tbUserName.Text.Trim().ToString()))
                  //            {
                  //                  MessageBox.Show("请输入用户名", "提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                  //                  this.tbUserName.Focus();
                  //                  return;
                  //            }
                  //            if (string.IsNullOrEmpty(this.CB_web.Text))
                  //            {
                  //                  MessageBox.Show("请选择服务器", "提示", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                  //                  this.CB_web.Focus();
                  //                  return;
                  //            }

                  //            string username = "";//this.tbUserName.Text.Trim();
                  //            string password = "";//this.tbPassword.Text.Trim();
                  //            string url = "";

                  //            if (CB_web.SelectedItem != null)
                  //            {
                  //                  //UserPermissionContext.Instance.Url = "http://localhost:8080/axis2/services/ECCWebServiceComponent/ECCWebService";

                  //                  #region  add by huangyimei
                  //                  url = ((KeyValuePair<string, string>)CB_web.SelectedItem).Value;
                  //                  //if (!url.Contains(":18080"))
                  //                  //{
                  //                  //    url = url + ":18080/webservice/InterfaceEccService";
                  //                  //}
                  //                  //else
                  //                  //{
                  //                  if (!url.Contains("webservice/InterfaceEccService"))
                  //                  {
                  //                        if (url.EndsWith("/"))
                  //                              url = url + "webservice/InterfaceEccService";
                  //                        else
                  //                              url = url + "/webservice/InterfaceEccService";
                  //                  }
                  //                  //}
                  //                  UserPermissionContext.Instance.Url = url;
                  //                  #endregion

                  //                  //UserPermissionContext.Instance.Url = ((KeyValuePair<string, string>)CB_web.SelectedItem).Value;
                  //                  Json.HttpGet.SetHostUrl(UserPermissionContext.Instance.Url + "/");
                  //            }
                  //            else
                  //            {
                  //                  //UserPermissionContext.Instance.Url = "http://localhost:8080/axis2/services/ECCWebServiceComponent/ECCWebService";

                  //                  #region  add by huangyimei
                  //                  url = ((KeyValuePair<string, string>)CB_web.Items[0]).Value;
                  //                  //if (!url.Contains(":18080"))
                  //                  //{
                  //                  //    url = url + ":18080/webservice/InterfaceEccService";
                  //                  //}
                  //                  //else
                  //                  //{
                  //                  if (!url.Contains("webservice/InterfaceEccService"))
                  //                  {
                  //                        if (url.EndsWith("/"))
                  //                              url = url + "webservice/InterfaceEccService";
                  //                        else
                  //                              url = url + "/webservice/InterfaceEccService";
                  //                  }
                  //                  //}
                  //                  UserPermissionContext.Instance.Url = url;
                  //                  #endregion

                  //                  //UserPermissionContext.Instance.Url = ((KeyValuePair<string, string>)CB_web.Items[0]).Value;
                  //                  Json.HttpGet.SetHostUrl(UserPermissionContext.Instance.Url + "/");
                  //            }

                  //            BackgroundWorker bw_Login = new BackgroundWorker();
                  //            bw_Login.DoWork += new DoWorkEventHandler(delegate(object sender1, DoWorkEventArgs e1)
                  //            {
                  //                  IIniFileDao iniFileDao = null;
                  //                  IDictionary<string, NameValueCollection> file = null;
                  //                  iniFileDao = MicroKernelUtil.GetDefaultKernel()["IniDao"] as IIniFileDao;
                  //                  file = iniFileDao.GetIniFileBySection("general.ini", "IPCheck");
                  //                  if (file.ContainsKey("IPCheck"))
                  //                  {
                  //                        string isCheckIp = file["IPCheck"]["isCheck"];
                  //                        if ("1".Equals(isCheckIp))
                  //                        {
                  //                              bool isValidIp = false;
                  //                              string IPAddress = file["IPCheck"]["IPAddress"];
                  //                              IPAddress = IPAddress.Replace("*", "\\d").Replace("?", "[0-9]");
                  //                              List<string> ipList = new List<string>();
                  //                              ipList.AddRange(IPAddress.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries));

                  //                              List<Regex> regList = new List<Regex>();
                  //                              foreach (string key in ipList)
                  //                              {
                  //                                    Regex reg = new Regex(key);
                  //                                    regList.Add(reg);
                  //                              }
                  //                              Hashtable ht = SiteView.Utils.CommIpOper.GetHostAddressList();
                  //                              foreach (object key in ht.Keys)
                  //                              {
                  //                                    if (!(key as string).Equals("127.0.0.1"))
                  //                                    {
                  //                                          foreach (Regex reg in regList)
                  //                                          {
                  //                                                if (reg.IsMatch(key as string))
                  //                                                {
                  //                                                      isValidIp = true;
                  //                                                      break;
                  //                                                }
                  //                                          }
                  //                                          if (isValidIp)
                  //                                          {
                  //                                                break;
                  //                                          }
                  //                                    }
                  //                              }

                  //                              if (!isValidIp)
                  //                              {
                  //                                    e1.Result = "本机IP地址不在允许登录范围内，登录被终止。";
                  //                                    throw new Exception("本机IP地址不在允许登录范围内，登录被终止。");
                  //                                    return;
                  //                              }
                  //                        }
                  //                  }

                  //                  if (UserPermissionContext.Instance.UserDao == null)
                  //                  {
                  //                        UserPermissionContext.Instance.UserDao
                  //                            = MicroKernelUtil.GetDefaultKernel()[typeof(IUserDao)] as IUserDao;
                  //                  }
                  //                  User user = null;
                  //                  string errorMessage = "";
                  //                  try
                  //                  {
                  //                        user = UserPermissionContext.Instance.UserDao.Login(username, password);
                  //                  }
                  //                  catch (Exception ex)
                  //                  {
                  //                        user = null;
                  //                        errorMessage = ex.Message;
                  //                  }
                  //                  if (user != null)
                  //                  {
                  //                        //验证成功 则 赋节点权限

                  //                        //1、获取user.ini的值
                  //                        file = iniFileDao.GetIniFile("user.ini");

                  //                        //2、根据user.ini的值 赋节点权限
                  //                        if (file.ContainsKey(user.Section))
                  //                        {
                  //                              foreach (string strKey in file[user.Section].AllKeys)
                  //                              {
                  //                                    if (strKey.StartsWith("m_") || strKey.EndsWith(".htm"))
                  //                                    {
                  //                                          if (user.IsAdministrator)
                  //                                                user.NodeRight.Add(strKey, true);
                  //                                          else
                  //                                          {
                  //                                                if ("1".Equals(file[user.Section][strKey]))
                  //                                                {
                  //                                                      user.NodeRight.Add(strKey, true);
                  //                                                }
                  //                                                else
                  //                                                {
                  //                                                      user.NodeRight.Add(strKey, false);
                  //                                                }
                  //                                          }
                  //                                    }
                  //                              }
                  //                        }

                  //                        UserPermissionContext.Instance.CurrentUser = user;
                  //                  }
                  //                  else
                  //                  {
                  //                        if (errorMessage.Contains("无法读取 user.ini 或发生跟该文件相关的错误。"))
                  //                        {
                  //                              e1.Result = "服务没有启动或其他原因无法读取认证信息！";
                  //                        }
                  //                        else
                  //                        {
                  //                              if (errorMessage.Contains("无法连接到远程服务器"))
                  //                              {
                  //                                    e1.Result = "无法连接到远程服务器";
                  //                              }
                  //                              else
                  //                              {
                  //                                    if (errorMessage.Contains("超过有效使用期了(invalid)。"))
                  //                                    {
                  //                                          e1.Result = "超过有效使用期了!";
                  //                                    }
                  //                                    else
                  //                                    {
                  //                                          if (errorMessage.Contains("用户") && errorMessage.Contains("已经被禁用"))
                  //                                                e1.Result = errorMessage;
                  //                                          else
                  //                                                e1.Result = "用户名或密码错误！";
                  //                                    }
                  //                              }
                  //                        }
                  //                        //throw new Exception("用户名或密码错误");
                  //                        //return;
                  //                        errorMessage = "";
                  //                  }
                  //            });

                  //            bw_Login.RunWorkerCompleted += new RunWorkerCompletedEventHandler(delegate(object sender1, RunWorkerCompletedEventArgs e1)
                  //            {
                  //                  this.Cursor = Cursors.Default;
                  //                  if (e1.Error != null)
                  //                  {
                  //                        MessageBox.Show("登录出现异常：\n\n" + e1.Error.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                  //                  }
                  //                  else if (!string.IsNullOrEmpty(e1.Result as string))
                  //                  {
                  //                        this.tbPassword.Focus();
                  //                        MessageBox.Show(e1.Result as string, "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                  //                  }
                  //                  else
                  //                  {
                  //                        this.DialogResult = DialogResult.OK;

                  //                        #region 登录成功则记下用户名和Web Service  add by huangyimei
                  //                        try
                  //                        {
                  //                              EccRootNode.useCache();   //判断是否启用缓存
                  //                              EccRootNode.CacheTime();  //获取缓存时间

                  //                              System.Configuration.Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                  //                              AppSettingsSection appSection = (AppSettingsSection)config.GetSection("appSettings");
                  //                              appSection.Settings.Clear();
                  //                              appSection.Settings.Add("ECCService_EccDefaultService*", "ECCService_" + ((KeyValuePair<string, string>)this.CB_web.SelectedItem).Key);
                  //                              foreach (KeyValuePair<string, string> keyvalue in CB_web.Items)
                  //                              {
                  //                                    appSection.Settings.Add("ECCService_" + keyvalue.Key, keyvalue.Value);
                  //                              }
                  //                              config.Save();

                  //                              string recentUser = ReadValue("userlogin", "recentUser", path);
                  //                              if (recentUser == tbUserName.Text.Trim())
                  //                                    return;
                  //                              WritePrivateProfileString("userlogin", "recentUser", tbUserName.Text.Trim(), path);

                  //                              string valueAll = ReadValue("userlogin", "userName", path);
                  //                              string[] values = valueAll.Split(',');
                  //                              foreach (string value in values)
                  //                              {
                  //                                    if (value.Equals(tbUserName.Text.Trim()))
                  //                                          return;
                  //                              }
                  //                              string newValue = valueAll + "," + tbUserName.Text.Trim();
                  //                              WritePrivateProfileString("userlogin", "userName", newValue, path);
                  //                        }
                  //                        catch
                  //                        { }
                  //                        #endregion

                  //                  }
                  //            });

                  //            this.Cursor = Cursors.WaitCursor;
                  //            bw_Login.RunWorkerAsync();
                  //      }
                  //      catch (Exception ex)
                  //      {
                  //            if (MessageBox.Show(ex.Message + ",是否关闭窗体？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
                  //                == DialogResult.Yes)
                  //            {
                  //                  this.DialogResult = DialogResult.Cancel;
                  //                  //this.Close();
                  //            }
                  //      }
                  //}

            }

      }
}
