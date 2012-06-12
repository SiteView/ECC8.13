using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SiteView.MmcShell
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class ShellSetup
    {
        private string url;
        private string local;

        public string Url
        {
            get { return this.url; }
            set { this.url = value; }
        }

        public string Local
        {
            get { return this.local; }
            set { this.local = value; }
        }
    }
}
