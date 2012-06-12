namespace Microsoft.ManagementConsole
{
    using System;

    internal sealed class ScopeNodeCollectionEventArgs : EventArgs
    {
        private ScopeNodeCollectionChangeType _changeType;
        private int _index;
        private ScopeNode[] _items;

        public ScopeNodeCollectionEventArgs(int index, ScopeNode[] items, ScopeNodeCollectionChangeType changeType)
        {
            this._index = index;
            this._items = items;
            this._changeType = changeType;
        }

        public ScopeNode[] GetItems()
        {
            return this._items;
        }

        public ScopeNodeCollectionChangeType ChangeType
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

