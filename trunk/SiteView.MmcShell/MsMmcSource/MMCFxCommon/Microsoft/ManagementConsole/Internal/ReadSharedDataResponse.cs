namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ReadSharedDataResponse : RequestResponse
    {
        private ClipboardData _requestedClipboardData;

        public ClipboardData RequestedClipboardData
        {
            get
            {
                return this._requestedClipboardData;
            }
            set
            {
                this._requestedClipboardData = value;
            }
        }
    }
}

