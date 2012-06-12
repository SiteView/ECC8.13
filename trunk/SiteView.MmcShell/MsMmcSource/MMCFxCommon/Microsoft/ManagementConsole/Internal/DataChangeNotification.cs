namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class DataChangeNotification : Notification
    {
        private string[] _changedClipboardFormatIds;
        private int _dataObjectId;
        private string[] _removedClipboardFormatIds;

        public string[] GetChangedClipboardFormatIds()
        {
            return this._changedClipboardFormatIds;
        }

        public string[] GetRemovedClipboardFormatIds()
        {
            return this._removedClipboardFormatIds;
        }

        public void SetChangedClipboardFormatIds(string[] changedClipboardFormatIds)
        {
            this._changedClipboardFormatIds = changedClipboardFormatIds;
        }

        public void SetRemovedClipboardFormatIds(string[] removedClipboardFormatIds)
        {
            this._removedClipboardFormatIds = removedClipboardFormatIds;
        }

        public int DataObjectId
        {
            get
            {
                return this._dataObjectId;
            }
            set
            {
                this._dataObjectId = value;
            }
        }
    }
}

