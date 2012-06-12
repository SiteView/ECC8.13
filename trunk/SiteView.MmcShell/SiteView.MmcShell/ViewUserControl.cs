using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.ManagementConsole.Internal;

namespace SiteView.MmcShell
{
    public partial class ViewUserControl : UserControl,ISnapInPlatform
    {
        public ViewUserControl()
        {
            InitializeComponent();
        }

        #region ISnapInPlatform Members

        public CommandResult ProcessCommand(Command command)
        {
            return null;
        }

        #endregion
    }
}
