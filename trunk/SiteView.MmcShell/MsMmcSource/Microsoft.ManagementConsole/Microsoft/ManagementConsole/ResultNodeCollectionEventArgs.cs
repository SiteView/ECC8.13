namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    internal sealed class ResultNodeCollectionEventArgs : EventArgs
    {
        private ResultNodeCollectionChangeType _changeType;
        private int _index;
        private ResultNode[] _items;

        public ResultNodeCollectionEventArgs(int index, ResultNode[] items, ResultNodeCollectionChangeType changeType)
        {
            this._index = index;
            this._items = items;
            this._changeType = changeType;
        }

        public ResultNode[] GetItems()
        {
            return this._items;
        }

        public ResultNodeCollectionChangeType ChangeType
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

