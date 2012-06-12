using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.ManagementConsole.Internal;

using SiteView.MmcShell.Controls;

namespace SiteView.MmcShell
{
    public partial class NavigatorUserControl : UserControl
    {
        private IDictionary<int, ScopeTreeNode> nodeTable = new Dictionary<int, ScopeTreeNode>();

        public NavigatorUserControl()
        {
            InitializeComponent();
        }

        public CommandResult ProcessCommand(InsertScopeNodesCommand command)
        {
            using (InsertScopeNodesCommandReader reader = new InsertScopeNodesCommandReader(command))
            {
                ScopeNodeInsert scopeNodeInsert = reader.ReadScopeNodeInsert();
                ScopeTreeNode scopeTreeNode = ScopeTreeNode.CreateScopeTreeNode(scopeNodeInsert.NodeData);
                scopeTreeNode.SetActionData(scopeNodeInsert.Actions);
                if (scopeNodeInsert.ParentScopeNodeId == -1)
                {
                    this.tvNavigator.Nodes.Insert(scopeNodeInsert.InsertionIndex, scopeTreeNode);
                }
                else
                {
                    ScopeTreeNode parentNode = this.nodeTable[scopeNodeInsert.ParentScopeNodeId];
                    parentNode.Nodes.Insert(scopeNodeInsert.InsertionIndex, scopeTreeNode);
                }
                this.nodeTable.Add(scopeNodeInsert.NodeData.Id, scopeTreeNode);
            }
            return null;
        }

        public CommandResult ProcessCommand(DeleteScopeNodesCommand command)
        {
            return null;
        }

        public CommandResult ProcessCommand(UpdateScopeNodeCommand command)
        {
            ScopeTreeNode scopeTreeNode = this.nodeTable[command.NodeData.Id];
            ScopeTreeNode.UpdateScopeTreeNode(command.NodeData, scopeTreeNode);
            return null;
        }
    }
}
