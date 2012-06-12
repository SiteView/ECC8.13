namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole;
    using System;

    public class PrimaryScopeNode
    {
        private ScopeNodeCollection _children = new ScopeNodeCollection();
        private NodeSyncManager _nodeSyncManager;
        private Guid _nodeType;
        private Microsoft.ManagementConsole.SharedData _sharedData = new Microsoft.ManagementConsole.SharedData();

        internal PrimaryScopeNode()
        {
            this._children.ItemsChanged += new ScopeNodeCollection.ScopeNodeCollectionEventHandler(this.OnChildrenChanged);
        }

        internal void Initialize(NodeSyncManager nodeSyncManager, Guid nodeType)
        {
            if (nodeSyncManager == null)
            {
                throw new ArgumentNullException("nodeSyncManager");
            }
            this._nodeSyncManager = nodeSyncManager;
            this._nodeType = nodeType;
            if (this._children.Count > 0)
            {
                this._nodeSyncManager.AddNodes(this._children.ToArray(), 0);
            }
        }

        private void OnChildrenChanged(object sender, ScopeNodeCollectionEventArgs e)
        {
            switch (e.ChangeType)
            {
                case ScopeNodeCollectionChangeType.Add:
                    if (this._nodeSyncManager == null)
                    {
                        break;
                    }
                    this._nodeSyncManager.AddNodes(e.GetItems(), e.Index);
                    return;

                case ScopeNodeCollectionChangeType.Remove:
                    if (this._nodeSyncManager != null)
                    {
                        this._nodeSyncManager.RemoveNodes(e.GetItems());
                    }
                    break;

                default:
                    return;
            }
        }

        public ScopeNodeCollection Children
        {
            get
            {
                return this._children;
            }
        }

        public Guid NodeType
        {
            get
            {
                return this._nodeType;
            }
        }

        public Microsoft.ManagementConsole.SharedData SharedData
        {
            get
            {
                return this._sharedData;
            }
        }
    }
}

