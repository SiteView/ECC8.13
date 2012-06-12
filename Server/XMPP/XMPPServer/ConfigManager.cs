using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace Logistics
{
    namespace SubServer
    {
        internal enum HostType
        {
            IP,
            Domain
        }

        class ConfigManager
        {
            private static XmlDocument doc = null;

            private static Company company = null;

            private static string strConfigFile = null;
            private static string strVersion = null;

            private static string strServer = null;
            private static int nPort;
            private static HostType enumServerType;

            private static string xfireUrl = string.Empty;
            private static string scanPath = string.Empty;

            //<Logistics>
            //  <Version>
            //    <Type>Desktop</Type>
            //    <Code>0.9</Code>
            //  </Version>
            //  <Server type="IP">
            //    <Name>192.168.6.26</Name>
            //    <Port>5222</Port>
            //  </Server>
            //  <Company>
            //    <ID>SiteView</ID>
            //    <Name>SiteView</Name>
            //  </Company>
            //  <XFireServerUrl>192.168.0.97:18080</XFireServerUrl>
            //  <NetScanPath>"C:\siteview\SiteView ECC\NetScan\ECCNetScanC.exe"</NetScanPath>
            //</Logistics>

            private static void Init()
            {
                
                try
                {
                    nPort = 5222;
                    doc = new XmlDocument();
                    doc.Load(strConfigFile);

                    XmlNode server = doc.DocumentElement.SelectSingleNode("Server");

                    string strTemp = null;
                    strTemp = ((XmlElement)server).GetAttribute("type");
                    enumServerType = (HostType)Enum.Parse(typeof(HostType), strTemp);

                    strServer = server.SelectSingleNode("Name").InnerText;
                    if (server.SelectSingleNode("Port") == null || server.SelectSingleNode("Port").InnerText == string.Empty)
                    {
                        strTemp = "5222";
                    }
                    else
                    {
                        strTemp = server.SelectSingleNode("Port").InnerText;
                    }

                    nPort = int.Parse(strTemp);

                    company = new Company(doc.DocumentElement.SelectSingleNode("Company"));

                    strVersion = doc.DocumentElement.SelectSingleNode("Version").SelectSingleNode("Code").InnerText;

                    xfireUrl = doc.DocumentElement.SelectSingleNode("XFireServerUrl").InnerText;
                    scanPath = doc.DocumentElement.SelectSingleNode("NetScanPath").InnerText;
                }catch(Exception ex){}

            }

            public static void Load()
            {
                strConfigFile = @"Config.ini";
                Init();
            }

            public static void Load(string strConfigFile)
            {
                ConfigManager.strConfigFile = strConfigFile;
                Init();
            }

            public static string XfireUrl
            {
                get { return xfireUrl; }
            }

            public static string ScanPath
            {
                get { return scanPath; }
            }

            public static Company Company
            {
                get
                {
                    return company;
                }
            }

            public static HostType ServerType
            {
                get
                {
                    return enumServerType;
                }
            }

            public static string Server
            {
                get
                {
                    return strServer;
                }
            }

            public static int Port
            {
                get
                {
                    return nPort;
                }
            }

            public static string Version
            {
                get
                {
                    return strVersion;
                }
            }

       }

    }
}
