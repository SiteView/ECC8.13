namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class NamespaceExtensionInitNotification : Notification
    {
        private Guid _primaryNodeType = Guid.Empty;

        public Guid PrimaryNodeType
        {
            get
            {
                return this._primaryNodeType;
            }
            set
            {
                this._primaryNodeType = value;
            }
        }
    }
}

