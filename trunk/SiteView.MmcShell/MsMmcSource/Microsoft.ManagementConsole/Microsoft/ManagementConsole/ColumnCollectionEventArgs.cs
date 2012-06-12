namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    internal sealed class ColumnCollectionEventArgs : EventArgs
    {
        private ColumnCollectionChangeType _changeType;
        private int _index;
        private MmcListViewColumn[] _items;

        public ColumnCollectionEventArgs(int index, MmcListViewColumn[] items, ColumnCollectionChangeType changeType)
        {
            this._index = index;
            this._items = items;
            this._changeType = changeType;
        }

        public MmcListViewColumn[] GetItems()
        {
            return this._items;
        }

        public ColumnCollectionChangeType ChangeType
        {
            get
            {
                return this._changeType;
            }
        }

        public int Index
        {
            get
            {
                return this._index;
            }
        }
    }
}

