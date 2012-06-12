namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ReadSharedDataViewRequestInfo : ViewSelectionRequestInfo
    {
        private string _requestedClipboardFormatId;

        public string RequestedClipboardFormatId
        {
            get
            {
                return this._requestedClipboardFormatId;
            }
            set
            {
                CommonValidation.ValidateClipboardFormatId(value);
                this._requestedClipboardFormatId = value;
            }
        }
    }
}

