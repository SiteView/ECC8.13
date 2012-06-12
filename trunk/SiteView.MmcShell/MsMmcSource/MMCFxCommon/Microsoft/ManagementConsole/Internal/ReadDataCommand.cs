namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ReadDataCommand : DataCommand
    {
        private string _clipboardFormatId;
        private TimeSpan _readTimeout = new TimeSpan(0, 0, 30);

        public string ClipboardFormatId
        {
            get
            {
                return this._clipboardFormatId;
            }
            set
            {
                CommonValidation.ValidateClipboardFormatId(value);
                this._clipboardFormatId = value;
            }
        }

        public TimeSpan ReadTimeout
        {
            get
            {
                return this._readTimeout;
            }
        }
    }
}

