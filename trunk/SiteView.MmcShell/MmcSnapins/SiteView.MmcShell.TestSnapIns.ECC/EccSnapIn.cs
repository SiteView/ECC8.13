using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.ManagementConsole;
using System.ComponentModel;

namespace SiteView.MmcShell.TestSnapIns.ECC
{
    [SnapInSettings("{7AA15882-7009-4002-AE3F-7BCDD0085CD5}", DisplayName = "Test.ECC")]
    public class EccSnapIn : SnapIn
    {
        protected override void OnInitialize()
        {
            this.RootNode = new ScopeNode();
            this.RootNode.DisplayName = "SiteView.ECC";

            ScopeNode node = new ScopeNode();
            node.DisplayName = "Users";
            this.RootNode.Children.Add(node);

            node = new ScopeNode();
            node.DisplayName = "Files";
            this.RootNode.Children.Add(node);
        }
    }

    [RunInstaller(true)]
    public class EccInstaller : SnapInInstaller
    {
    }
}
