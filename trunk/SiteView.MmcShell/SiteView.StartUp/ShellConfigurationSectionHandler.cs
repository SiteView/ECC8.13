using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using SiteView.MmcShell;

namespace SiteView.StartUp
{
    /// <summary>
    /// 
    /// </summary>
    public class ShellConfigurationSectionHandler : IConfigurationSectionHandler
    {
        #region IConfigurationSectionHandler Members

        /// <summary>
        /// 
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="configContext"></param>
        /// <param name="section"></param>
        /// <returns></returns>
        public object Create(object parent, object configContext, System.Xml.XmlNode section)
        {
            if (section == null)
            {
                throw new ArgumentNullException("section");
            }
            if (section.Attributes["Url"] == null)
            {
                throw new ArgumentException("配置节点必须设置Url","section");
            }
            if (section.Attributes["Local"] == null)
            {
                throw new ArgumentException("配置节点必须设置Local", "section");
            }

            ShellSetup setup = new ShellSetup();
            setup.Url = section.Attributes["Url"].Value;
            setup.Local = section.Attributes["Local"].Value;
            return setup;
        }

        #endregion
    }
}
