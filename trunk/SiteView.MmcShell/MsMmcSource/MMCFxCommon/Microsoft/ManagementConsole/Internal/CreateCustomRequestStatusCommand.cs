namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class CreateCustomRequestStatusCommand : Command
    {
        private int _scopeNodeId = -1;

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

