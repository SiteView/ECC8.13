namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ViewKeyboardFocusNotification : Notification
    {
        private bool _forward;

        public bool Forward
        {
            get
            {
                return this._forward;
            }
            set
            {
                this._forward = value;
            }
        }
    }
}

