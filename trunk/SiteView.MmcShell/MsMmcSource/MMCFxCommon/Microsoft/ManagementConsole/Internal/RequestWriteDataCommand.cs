namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class RequestWriteDataCommand : DataCommand
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
                CommonValidation.ValidateClipboardFormatId(value.ClipboardFormatId);
                this._requestedValue = value;
            }
        }
    }
}

