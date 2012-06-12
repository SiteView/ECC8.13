namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PropertySheetExtensionInitNotification : Notification
    {
        private Guid[] _primaryNodeTypes;

        public Guid[] GetPrimaryNodeTypes()
        {
            return this._primaryNodeTypes;
        }

        public void SetPrimaryNodeTypes(Guid[] primaryNodeTypes)
        {
            this._primaryNodeTypes = primaryNodeTypes;
        }
    }
}

