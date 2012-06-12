namespace Microsoft.ManagementConsole
{
    using System;

    internal sealed class ViewDescriptionCollectionEventArgs : EventArgs
    {
        private ViewDescriptionCollectionChangeType _changeType;
        private int _index;
        private ViewDescription[] _items;

        public ViewDescriptionCollectionEventArgs(int index, ViewDescription[] items, ViewDescriptionCollectionChangeType changeType)
        {
            this._index = index;
            this._items = items;
            this._changeType = changeType;
        }

        public ViewDescription[] GetItems()
        {
            return this._items;
        }

        public ViewDescriptionCollectionChangeType ChangeType
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

