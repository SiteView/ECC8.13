namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SelectScopeNodeCommand : ViewCommand
    {
        private NodeIdData[] _relativePath = new NodeIdData[0];
        private int _scopeNodeId = -1;

        public NodeIdData[] GetRelativePath()
        {
            return this._relativePath;
        }

        public void SetRelativePath(NodeIdData[] relativePath)
        {
            this._relativePath = relativePath;
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

