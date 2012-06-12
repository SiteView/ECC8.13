namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class KeepAliveViewSelectionRequestInfo : ViewSelectionRequestInfo
    {
        private bool _keepAlive;
        private KeepAlivePurpose _purpose;

        public bool KeepAlive
        {
            get
            {
                return this._keepAlive;
            }
            set
            {
                this._keepAlive = value;
            }
        }

        public KeepAlivePurpose Purpose
        {
            get
            {
                return this._purpose;
            }
            set
            {
                this._purpose = value;
            }
        }
    }
}

