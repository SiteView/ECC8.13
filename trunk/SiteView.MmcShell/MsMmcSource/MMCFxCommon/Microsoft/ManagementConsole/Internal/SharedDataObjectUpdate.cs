namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SharedDataObjectUpdate
    {
        private DataFormatConfiguration[] _addedFormats;
        private DataFormatConfiguration[] _changedFormats;
        private string[] _removedClipboardFormatIds;
        private ClipboardData[] _updatedData;

        public DataFormatConfiguration[] GetAddedFormats()
        {
            return this._addedFormats;
        }

        public DataFormatConfiguration[] GetChangedFormats()
        {
            return this._changedFormats;
        }

        public string[] GetRemovedClipboardFormatIds()
        {
            return this._removedClipboardFormatIds;
        }

        public ClipboardData[] GetUpdatedData()
        {
            return this._updatedData;
        }

        public void SetAddedFormats(DataFormatConfiguration[] addedFormats)
        {
            this._addedFormats = addedFormats;
        }

        public void SetChangedFormats(DataFormatConfiguration[] changedFormats)
        {
            this._changedFormats = changedFormats;
        }

        public void SetRemovedClipboardFormatIds(string[] removedClipboardFormatIds)
        {
            this._removedClipboardFormatIds = removedClipboardFormatIds;
        }

        public void SetUpdatedData(ClipboardData[] updatedData)
        {
            this._updatedData = updatedData;
        }
    }
}

