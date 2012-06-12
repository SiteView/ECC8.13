namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class NodeRequestInfo : RequestInfo
    {
        private int _scopeNodeId;

        protected NodeRequestInfo()
        {
        }

        public int ScopeNodeId
        {
            get
            {
                return this._scopeNodeId;
            }
            set
            {
                this._scopeNodeId = value;
            }
        }
    }
}

