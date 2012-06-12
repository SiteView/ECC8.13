namespace Microsoft.ManagementConsole
{
    using System;

    internal sealed class ActionsPaneItemCollectionEventArgs : EventArgs
    {
        private ActionsPaneItemCollectionChangeType _changeType;
        private int _index;
        private ActionsPaneItem[] _items;

        internal ActionsPaneItemCollectionEventArgs(int index, ActionsPaneItem[] items, ActionsPaneItemCollectionChangeType changeType)
        {
            this._index = index;
            this._items = items;
            this._changeType = changeType;
        }

        public ActionsPaneItem[] GetItems()
        {
            return this._items;
        }

        public ActionsPaneItemCollectionChangeType ChangeType
        {
            get
            {
                return this._changeType;
            }
        }
    }
}

