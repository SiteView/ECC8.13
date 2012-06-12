namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Reflection;
    using System.Runtime.CompilerServices;

    public sealed class ResultNodeCollection : BaseCollection
    {
        private bool _ignoreChanges;
        private Hashtable _itemsById;
        private MmcListView _listView;

        internal event ResultNodeCollectionEventHandler ItemsChanged;

        internal ResultNodeCollection(MmcListView listView) : base(typeof(ResultNode))
        {
            this._itemsById = new Hashtable();
            if (listView == null)
            {
                throw new ArgumentNullException("listView");
            }
            this._listView = listView;
        }

        public void Add(ResultNode item)
        {
            base.List.Add(item);
        }

        public void AddRange(ResultNode[] items)
        {
            base.AddRange(items);
        }

        public bool Contains(ResultNode item)
        {
            return base.List.Contains(item);
        }

        public void CopyTo(ResultNode[] array, int index)
        {
            this.CopyTo(array, index);
        }

        internal ResultNode GetNode(int id)
        {
            return (this._itemsById[id] as ResultNode);
        }

        public int IndexOf(ResultNode item)
        {
            return base.List.IndexOf(item);
        }

        public void Insert(int index, ResultNode item)
        {
            base.Insert(index, item);
        }

        public void InsertRange(int index, ResultNode[] items)
        {
            base.InsertRange(index, items);
        }

        private void ItemChanged(object sender, NodeChangedEventArgs e)
        {
            int index = base.List.IndexOf(sender);
            this.Notify(index, new ResultNode[] { (ResultNode) sender }, ResultNodeCollectionChangeType.Modify);
        }

        private void Notify(int index, ResultNode[] items, ResultNodeCollectionChangeType action)
        {
            if (this.ItemsChanged != null)
            {
                this.ItemsChanged(this, new ResultNodeCollectionEventArgs(index, items, action));
            }
        }

        protected override void OnItemsAdded(int index, object[] items)
        {
            if (!this._ignoreChanges)
            {
                if (this._listView.SortingInProgress)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ResultNodeCollectionOnItemsAddedResultNodeAdd));
                }
                foreach (ResultNode node in items)
                {
                    if (node.ListView != null)
                    {
                        throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ResultNodeCollectionOnItemsAddedMultipleInstance));
                    }
                    node.ListView = this._listView;
                    node.Changed += new Node.NodeChangedEventHandler(this.ItemChanged);
                    this._itemsById[node.Id] = node;
                }
                ResultNode[] destinationArray = new ResultNode[items.Length];
                Array.Copy(items, destinationArray, items.Length);
                this.Notify(index, destinationArray, ResultNodeCollectionChangeType.Add);
            }
        }

        protected override void OnItemsRemoved(int index, object[] items)
        {
            if (!this._ignoreChanges)
            {
                if (this._listView.SortingInProgress)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ResultNodeCollectionOnItemsRemovedResultNode));
                }
                foreach (ResultNode node in items)
                {
                    node.ListView = null;
                    node.Changed -= new Node.NodeChangedEventHandler(this.ItemChanged);
                    this._itemsById.Remove(node.Id);
                }
                ResultNode[] destinationArray = new ResultNode[items.Length];
                Array.Copy(items, destinationArray, items.Length);
                this.Notify(index, destinationArray, ResultNodeCollectionChangeType.Remove);
            }
        }

        public void Remove(ResultNode item)
        {
            base.List.Remove(item);
        }

        internal void Replace(ResultNode[] nodes)
        {
            this._ignoreChanges = true;
            base.Clear();
            this.AddRange(nodes);
            this._ignoreChanges = false;
        }

        public ResultNode[] ToArray()
        {
            return (ResultNode[]) base.InnerList.ToArray(typeof(ResultNode));
        }

        public ResultNode this[int index]
        {
            get
            {
                return (ResultNode) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void ResultNodeCollectionEventHandler(object sender, ResultNodeCollectionEventArgs e);
    }
}

