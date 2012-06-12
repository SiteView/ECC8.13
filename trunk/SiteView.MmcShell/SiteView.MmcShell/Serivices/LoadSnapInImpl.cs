using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Xml;
using System.IO;

namespace SiteView.MmcShell.Serivices
{
    /// <summary>
    /// 
    /// </summary>
    public class LoadSnapInImpl : ILoadSnapIns
    {
        private ShellSetup setup = null;
        private WebClient webclient = null;

        public LoadSnapInImpl(ShellSetup setup, WebClient webclient)
        {
            this.setup = setup;
            this.webclient = webclient;
        }

        #region ILoadSnapIns Members

        public void Load()
        {
            this.LoadSnapIns();
        }

        private void LoadSnapIns()
        {
            string snapInUrl = this.setup.Url + "SnapIns.ashx";

            string xmlStr = this.webclient.DownloadString(snapInUrl);
            XmlDocument xmldoc = new XmlDocument();
            xmldoc.LoadXml(xmlStr);
            DirectoryInfo snapInDir = null;

            foreach (XmlNode xmlNode in xmldoc.SelectNodes("//SnapIns/SnapIn"))
            {
                string path = Path.Combine(this.setup.Local, xmlNode.Attributes["name"].Value);
                snapInDir = new DirectoryInfo(path);
                if (!snapInDir.Exists)
                {
                    snapInDir.Create();
                }
                this.DownloadFile(snapInDir, xmlNode);
            }
        }

        private void DownloadFile(DirectoryInfo currentDir, XmlNode xmlnode)
        {
            foreach (XmlNode child in xmlnode.ChildNodes)
            {
                if ("file".Equals(child.Name))
                {
                    string filepath = Path.Combine(currentDir.FullName, child.Attributes["name"].Value);
                    try
                    {
                        using (FileStream fs = new FileStream(filepath, FileMode.OpenOrCreate, FileAccess.ReadWrite))
                        {
                            Uri url = this.GetFileUrl(child);
                            byte[] buffer = this.webclient.DownloadData(url);
                            fs.Write(buffer, 0, buffer.Length);
                            fs.Close();
                        }
                    }
                    catch (Exception ex)
                    {
                    }
                }
                else if ("directory".Equals(child.Name))
                {
                    string dirStr = Path.Combine(currentDir.FullName, child.Attributes["name"].Value);
                    DirectoryInfo newDir = new DirectoryInfo(dirStr);
                    if (!newDir.Exists)
                    {
                        newDir.Create();
                    }
                    this.DownloadFile(newDir, child);
                }
            }
        }

        private Uri GetFileUrl(XmlNode child)
        {
            string path = String.Format("{0}/{1}",
                this.GetDirUrl(String.Empty, child.ParentNode),
                child.Attributes["name"].Value);
            return new Uri(path);
        }

        private string GetDirUrl(string url, XmlNode child)
        {
            if (!"SnapIn".Equals(child.Name))
            {
                return this.GetDirUrl(child.Attributes["name"].Value + "/" + url, child.ParentNode);
            }
            return String.Format("{0}SnapIns/{1}/{2}", this.setup.Url, child.Attributes["name"].Value, url);
        }

        #endregion
    }
}
