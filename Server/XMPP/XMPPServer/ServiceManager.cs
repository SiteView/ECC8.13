using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace Logistics
{
    namespace SubServer
    {
        class ServiceManager
        {
            private string strServiceFile = null;
            private XmlDocument doc = null;

            public ServiceManager()
            {
                doc = new XmlDocument();
                doc.Load("ServiceDB.xml");
            }

            public bool Load(string strServiceFile)
            {
                if (!System.IO.File.Exists(strServiceFile))
                {
                    return false;
                }

                this.strServiceFile = strServiceFile;

                doc = new XmlDocument();
                doc.Load(strServiceFile);

                return true;

            }

            public void Save()
            {
                if (doc != null)
                {
                    doc.Save(this.strServiceFile);
                }
            }

            public void SaveAs(string strFilePath)
            {
                if (doc != null)
                {
                    doc.Save(strFilePath);
                }
            }

            public BaseService[] Services
            {
                get
                {
                    XmlNodeList serviceList = doc.DocumentElement.SelectNodes("Service");
                    BaseService[] services = new BaseService[serviceList.Count];
                    int i = 0;
                    foreach (XmlNode serviceNode in serviceList)
                    {
                        XmlElement service = serviceNode as XmlElement;
                        string strServiceType = service.GetAttribute("type");
                        ServiceType serviceType = (ServiceType)Enum.Parse(typeof(ServiceType), strServiceType);

                        string strName = service.SelectSingleNode("Name").InnerText;
                        string strJID = service.SelectSingleNode("JID").InnerText;

                        switch (serviceType)
                        {
                            case ServiceType.FileTransfer:
                                TransferService trans = new TransferService();
                                trans.Name = strName;
                                trans.JID = new agsXMPP.Jid(strJID + "@" + ConfigManager.Server);
                                services[i] = trans;
                                break;
                            case ServiceType.GroupChat:

                                MucService muc = new MucService();
                                muc.Name = strName;
                                muc.JID = new agsXMPP.Jid(strJID);
                                services[i] = muc;
                                break;
                            case ServiceType.ContactSearch:
                                SearchService search = new SearchService();
                                search.Name = strName;
                                search.JID = new agsXMPP.Jid(strJID);
                                services[i] = search;
                                break;
                            default:
                                break;
                        }

                        i++;
                    }

                    return services;
                }
            }

            //public 
        }
    }
}