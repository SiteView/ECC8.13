namespace Microsoft.ManagementConsole
{
    using System;

    internal class SharedDataChangedEventArgs : EventArgs
    {
        private SharedDataChangeType _changeType;
        private Microsoft.ManagementConsole.SharedDataItem _publishedDataItem;

        internal SharedDataChangedEventArgs(SharedDataChangeType changeType, Microsoft.ManagementConsole.SharedDataItem publishedDataItem)
        {
            this._changeType = changeType;
            this._publishedDataItem = publishedDataItem;
        }

        internal SharedDataChangeType ChangeType
        {
            get
            {
                return this._changeType;
            }
        }

        internal Microsoft.ManagementConsole.SharedDataItem SharedDataItem
        {
            get
            {
                return this._publishedDataItem;
            }
        }
    }
}

