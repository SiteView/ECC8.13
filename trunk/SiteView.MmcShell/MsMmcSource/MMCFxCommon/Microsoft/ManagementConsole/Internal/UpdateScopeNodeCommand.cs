namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateScopeNodeCommand : Command
    {
        private ActionsPaneRootData _actions;
        private ActionsPaneRootData _helpActions;
        private ScopeNodeData _nodeData;
        private SharedDataObjectUpdate _updatedSharedData;

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

        public ScopeNodeData NodeData
        {
            get
            {
                return this._nodeData;
            }
            set
            {
                this._nodeData = value;
            }
        }

        public SharedDataObjectUpdate UpdatedSharedData
        {
            get
            {
                return this._updatedSharedData;
            }
            set
            {
                this._updatedSharedData = value;
            }
        }
    }
}

