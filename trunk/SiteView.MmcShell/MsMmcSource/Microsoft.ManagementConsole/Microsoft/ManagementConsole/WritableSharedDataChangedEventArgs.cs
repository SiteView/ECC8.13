namespace Microsoft.ManagementConsole
{
    using System;

    internal class WritableSharedDataChangedEventArgs : EventArgs
    {
        private WritableSharedDataChangeType _changeType;
        private WritableSharedDataItem _publishedDataItem;

        internal WritableSharedDataChangedEventArgs(WritableSharedDataChangeType changeType, WritableSharedDataItem publishedDataItem)
        {
            this._changeType = changeType;
            this._publishedDataItem = publishedDataItem;
        }

        internal WritableSharedDataChangeType ChangeType
        {
            get
            {
                return this._changeType;
            }
        }

        internal WritableSharedDataItem SharedDataItem
        {
            get
            {
                return this._publishedDataItem;
            }
        }
    }
}

