using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.ManagementConsole.Internal;
using System.Net;
using System.Xml;
using System.IO;
using Microsoft.ManagementConsole;
using System.Diagnostics;

namespace SiteView.MmcShell
{
    public partial class ShellUserControl : UserControl,ISnapInPlatform
    {
        #region private fields

        private ShellSetup setup = new ShellSetup();
        private NavigatorUserControl navigator = null;
        private ViewUserControl view = null;
        private WebClient webclient = null;

        private ILoadSnapIns loadSnapInService;
        private ISnapInManager snapInManager;

        #endregion

        public ShellUserControl()
        {
            this.webclient = new WebClient();
            this.webclient.Encoding = Encoding.UTF8;

            InitializeComponent();
        }


        #region public properties

        /// <summary>
        /// 
        /// </summary>
        public ShellSetup ShellSetup
        {
            get { return this.setup; }
            set 
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value"
                        ,"ShellSetup不能为空，是否在App.Config中配置SiteViewShell节点?");
                }
                this.setup = value; 
            }
        }

        #endregion

        #region internal properties

        internal ILoadSnapIns LoadSnapInService
        {
            get
            {
                if (this.loadSnapInService == null)
                {
                    this.loadSnapInService = new Serivices.LoadSnapInImpl(this.setup, this.webclient);
                }
                return this.loadSnapInService;
            }
        }

        internal ISnapInManager SnapInManager
        {
            get
            {
                if (this.snapInManager == null)
                {
                    this.snapInManager = new Serivices.SnapInManagerImpl(this.setup);
                }
                return this.snapInManager;
            }
           
        }

        #endregion

        private void ShellUserControl_Load(object sender, EventArgs e)
        {
            this.navigator = new NavigatorUserControl();
            this.view = new ViewUserControl();

            this.navigator.Dock = DockStyle.Fill;
            this.view.Dock = DockStyle.Fill;

            this.mainSplitContainer.Panel1.Controls.Add(this.navigator);
            this.mainSplitContainer.Panel2.Controls.Add(this.view);

            this.LoadSnapInService.Load();
            this.SnapInManager.Init(this);
        }

        #region ISnapInPlatform Members

        public CommandResult ProcessCommand(Command command)
        {

#if DEBUG
            TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 0,
                "Command:" + command.ToString());
#endif
            CommandResult result = null;
            if (command is ViewCommand)
            {
                result = this.view.ProcessCommand(command);
            }
            else if (command is InsertScopeNodesCommand)
            {
                result = this.navigator.ProcessCommand(command as InsertScopeNodesCommand);
            }
            else if (command is DeleteScopeNodesCommand)
            {
                result = this.navigator.ProcessCommand(command as DeleteScopeNodesCommand);
            }
            else if (command is UpdateScopeNodeCommand)
            {
                result = this.navigator.ProcessCommand(command as UpdateScopeNodeCommand);
            }

#if DEBUG
            TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 0, 
                "CommandResult:" + (result == null ? "null" : result.ToString()));
#endif

            return result;
        }

        #endregion
    }
}
