namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateDataChangeNodeRequestInfo : NodeRequestInfo
    {
        private ClipboardData _requestedValue;

        public ClipboardData RequestedValue
        {
            get
            {
                return this._requestedValue;
            }
            set
            {
                this._requestedValue = value;
            }
        }
    }
}

