namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public class SharedDataItemBase
    {
        private string _clipboardFormatId;
        private byte[] _data;

        internal SharedDataItemBase(string clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            this._clipboardFormatId = clipboardFormatId;
        }

        public virtual byte[] GetData()
        {
            return this._data;
        }

        internal void InternalSetData(byte[] data)
        {
            this._data = data;
        }

        public string ClipboardFormatId
        {
            get
            {
                return this._clipboardFormatId;
            }
        }
    }
}

