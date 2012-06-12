namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    [Serializable, StructLayout(LayoutKind.Sequential), EditorBrowsable(EditorBrowsableState.Never)]
    public struct ScopeNodeInsert
    {
        private int _parentScopeNodeId;
        private int _insertionIndex;
        private ScopeNodeData _scopeNodeData;
        private SharedDataObjectUpdate _initialSharedData;
        private ActionsPaneRootData _actions;
        private ActionsPaneRootData _helpActions;
        public int ParentScopeNodeId
        {
            get
            {
                return (this._parentScopeNodeId - 1);
            }
            set
            {
                if (value == 0x7fffffff)
                {
                    throw new ArgumentOutOfRangeException("value");
                }
                this._parentScopeNodeId = value + 1;
            }
        }
        public int InsertionIndex
        {
            get
            {
                return (this._insertionIndex - 1);
            }
            set
            {
                if (value == 0x7fffffff)
                {
                    throw new ArgumentOutOfRangeException("value");
                }
                this._insertionIndex = value + 1;
            }
        }
        public ScopeNodeData NodeData
        {
            get
            {
                return this._scopeNodeData;
            }
            set
            {
                this._scopeNodeData = value;
            }
        }
        public SharedDataObjectUpdate InitialSharedData
        {
            get
            {
                if (this._initialSharedData == null)
                {
                    this._initialSharedData = new SharedDataObjectUpdate();
                }
                return this._initialSharedData;
            }
        }
        public ActionsPaneRootData Actions
        {
            get
            {
                return this._actions;
            }
            set
            {
                this._actions = value;
            }
        }
        public ActionsPaneRootData HelpActions
        {
            get
            {
                return this._helpActions;
            }
            set
            {
                this._helpActions = value;
            }
        }
    }
}

