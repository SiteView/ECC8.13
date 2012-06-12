namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Globalization;
    using System.Reflection;
    using System.Runtime.CompilerServices;

    public sealed class MmcListViewColumnCollection : BaseCollection
    {
        private Hashtable _itemsById;
        private MmcListView _listView;

        internal event ColumnCollectionEventHandler ItemsChanged;

        internal MmcListViewColumnCollection(MmcListView listView) : base(typeof(MmcListViewColumn))
        {
            this._itemsById = new Hashtable();
            if (listView == null)
            {
                throw new ArgumentNullException("listView");
            }
            this._listView = listView;
            MmcListViewColumn column = new MmcListViewColumn(Microsoft.ManagementConsole.Internal.Utility.Resources.GetString(Microsoft.ManagementConsole.Internal.Strings.MicrosoftManagementConsoleFxColumnDefaultTitle, CultureInfo.CurrentUICulture), -1, MmcListViewColumnFormat.Left, true);
            column.ListView = this._listView;
            column.Changed += new MmcListViewColumn.ColumnChangedEventHandler(this.ItemChanged);
            this._itemsById[column.Id] = column;
            base.InnerList.Add(column);
        }

        public void Add(MmcListViewColumn column)
        {
            base.List.Add(column);
        }

        public void AddRange(MmcListViewColumn[] columns)
        {
            base.AddRange(columns);
        }

        public void Clear()
        {
            if (base.Count > 1)
            {
                MmcListViewColumn[] items = new MmcListViewColumn[base.Count - 1];
                for (int i = 1; i < base.Count; i++)
                {
                    items[i - 1] = this[i];
                }
                base.InnerList.RemoveRange(1, base.Count - 1);
                try
                {
                    this.OnItemsRemoved(1, items);
                }
                catch
                {
                    foreach (MmcListViewColumn column in items)
                    {
                        base.InnerList.Add(column);
                    }
                    throw;
                }
            }
        }

        public bool Contains(MmcListViewColumn column)
        {
            return base.List.Contains(column);
        }

        public void CopyTo(MmcListViewColumn[] array, int index)
        {
            this.CopyTo(array, index);
        }

        internal MmcListViewColumn GetColumn(int id)
        {
            return (this._itemsById[id] as MmcListViewColumn);
        }

        public int IndexOf(MmcListViewColumn column)
        {
            return base.List.IndexOf(column);
        }

        public void Insert(int index, MmcListViewColumn column)
        {
            base.Insert(index, column);
        }

        public void InsertRange(int index, MmcListViewColumn[] columns)
        {
            base.InsertRange(index, columns);
        }

        private void ItemChanged(object sender, EventArgs e)
        {
            int index = base.List.IndexOf(sender);
            this.Notify(index, new MmcListViewColumn[] { (MmcListViewColumn) sender }, ColumnCollectionChangeType.Modify);
        }

        private void Notify(int index, MmcListViewColumn[] columns, ColumnCollectionChangeType action)
        {
            if (this.ItemsChanged != null)
            {
                this.ItemsChanged(this, new ColumnCollectionEventArgs(index, columns, action));
            }
        }

        protected override void OnItemsAdded(int index, object[] items)
        {
            if (index == 0)
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnCollectionOnItemsAddedIndexError), "index");
            }
            if ((this._listView != null) && (this._listView.ResultNodes.Count != 0))
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnCollectionOnItemsAddedInvalidOperationResultNode));
            }
            foreach (MmcListViewColumn column in items)
            {
                if (column == null)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("items[x]", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullValue, new object[0]);
                }
                if (column.ListView != null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnCollectionOnItemsAddedInvalidOperationInsertTwice));
                }
            }
            foreach (MmcListViewColumn column2 in items)
            {
                column2.Changed += new MmcListViewColumn.ColumnChangedEventHandler(this.ItemChanged);
                column2.ListView = this._listView;
                this._itemsById[column2.Id] = column2;
            }
            MmcListViewColumn[] destinationArray = new MmcListViewColumn[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ColumnCollectionChangeType.Add);
        }

        protected override void OnItemsRemoved(int index, object[] items)
        {
            if (index == 0)
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnCollectionOnItemsRemovedFirstColumn), "index");
            }
            if ((this._listView != null) && (this._listView.ResultNodes.Count != 0))
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnCollectionOnItemsRemovedResultNode));
            }
            foreach (MmcListViewColumn column in items)
            {
                column.Changed -= new MmcListViewColumn.ColumnChangedEventHandler(this.ItemChanged);
                column.ListView = null;
                this._itemsById.Remove(column.Id);
            }
            MmcListViewColumn[] destinationArray = new MmcListViewColumn[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ColumnCollectionChangeType.Remove);
        }

        internal override void OnValidate(object objectToValidate, bool testForDuplicate)
        {
            base.OnValidate(objectToValidate, testForDuplicate);
            MmcListViewColumn column = objectToValidate as MmcListViewColumn;
            if (column != null)
            {
                ColumnData.ValidateTitle(column.Title);
            }
        }

        public void Remove(MmcListViewColumn column)
        {
            base.List.Remove(column);
        }

        public MmcListViewColumn[] ToArray()
        {
            return (MmcListViewColumn[]) base.InnerList.ToArray(typeof(MmcListViewColumn));
        }

        public MmcListViewColumn this[int index]
        {
            get
            {
                return (MmcListViewColumn) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void ColumnCollectionEventHandler(object sender, ColumnCollectionEventArgs e);
    }
}

