namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class DeactivateNodeNotification : Notification
    {
        private int _scopeNodeId;

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

