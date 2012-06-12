using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.ManagementConsole.Internal;

namespace SiteView.MmcShell.Controls
{
    /// <summary>
    /// Mmc ScopeNode
    /// </summary>
    public class ScopeTreeNode : TreeNode
    {
        private ScopeNodeData nodeData = null;

        public ScopeNodeData NodeData
        {
            get { return this.nodeData; }
            set { this.nodeData = value; }
        }

        internal void SetActionData(ActionsPaneRootData actionsPaneRootData)
        {
            ActionsPaneItemCollectionData actionsData = actionsPaneRootData.Read();
        }

        #region 静态方法
        private static void RebuildTreeNode(ScopeTreeNode treeNode)
        {
            NodeData nodeData = treeNode.NodeData;
            
            treeNode.Text = nodeData.DisplayName;
        }

        /// <summary>
        /// 创建节点
        /// </summary>
        /// <param name="nodeData"></param>
        /// <returns></returns>
        internal static ScopeTreeNode CreateScopeTreeNode(ScopeNodeData nodeData)
        {
            ScopeTreeNode node = new ScopeTreeNode();
            node.NodeData = nodeData;
            RebuildTreeNode(node);
            return node;
        }

        /// <summary>
        /// 更新节点
        /// </summary>
        /// <param name="nodeData"></param>
        /// <param name="treeNode"></param>
        internal static void UpdateScopeTreeNode(ScopeNodeData nodeData, ScopeTreeNode treeNode)
        {
            treeNode.NodeData = nodeData;
            RebuildTreeNode(treeNode);
        }
        #endregion

        
    }
}
