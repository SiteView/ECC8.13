using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.ManagementConsole.Internal;
using System.Xml;
using System.Reflection;

namespace SiteView.MmcShell.Serivices
{
    public class SnapInManagerImpl : ISnapInManager
    {
        private ShellSetup setup;
        private IDictionary<string, ISnapInClient> snapInClients;

        public SnapInManagerImpl(ShellSetup setup)
        {
            this.setup = setup;
            this.snapInClients = new Dictionary<string, ISnapInClient>();
        }

        #region ISnapInManager Members

        public void Init(ISnapInPlatform snapInPlatform)
        {
            DirectoryInfo snapInsDir = new DirectoryInfo(this.setup.Local);
            AppDomain appDomain = null;
            AppDomainSetup appDomainSetup = null;
            XmlDocument xmldoc = null;
            foreach (DirectoryInfo snapInDir in snapInsDir.GetDirectories())
            {   
                xmldoc = new XmlDocument();
                xmldoc.Load(Path.Combine(snapInDir.FullName, "info.xml"));

                IDictionary<string, string> infoTable = new Dictionary<string, string>();
                foreach (XmlNode xmlNode in xmldoc.DocumentElement)
                {
                    infoTable.Add(xmlNode.Name, xmlNode.InnerText);
                }
                appDomainSetup = new AppDomainSetup();
                appDomainSetup.ApplicationBase = snapInDir.FullName;

                appDomain = AppDomain.CreateDomain("SNAPIN_" + infoTable["name"], null, appDomainSetup);
                IClassLibraryServices classLiberary = appDomain.CreateInstanceAndUnwrap("Microsoft.ManagementConsole",
                "Microsoft.ManagementConsole.Internal.ClassLibraryServices",
                        false,
                        BindingFlags.NonPublic | BindingFlags.Instance,
                        null, null, null, null, null) as IClassLibraryServices;

                ISnapInClient snapInClient = classLiberary.CreateSnapIn(infoTable["assemblyName"], infoTable["class"]);
                snapInClient.Initialize(snapInPlatform);

                this.snapInClients.Add(infoTable["guid"], snapInClient);
            }
        }

        #endregion
    }
}
