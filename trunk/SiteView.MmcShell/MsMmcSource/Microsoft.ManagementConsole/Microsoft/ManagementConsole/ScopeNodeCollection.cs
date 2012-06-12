namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Reflection;
    using System.Runtime.CompilerServices;

    public sealed class ScopeNodeCollection : BaseCollection
    {
        private ScopeNode _containerNode;

        internal event ScopeNodeCollectionEventHandler ItemsChanged;

        public ScopeNodeCollection() : base(typeof(ScopeNode))
        {
        }

        public int Add(ScopeNode item)
        {
            return base.List.Add(item);
        }

        public void AddRange(ScopeNode[] items)
        {
            base.AddRange(items);
        }

        public bool Contains(ScopeNode item)
        {
            return base.List.Contains(item);
        }

        public void CopyTo(ScopeNode[] array, int index)
        {
            this.CopyTo(array, index);
        }

        public int IndexOf(ScopeNode item)
        {
            return base.List.IndexOf(item);
        }

        public void Insert(int index, ScopeNode item)
        {
            base.Insert(index, item);
        }

        public void InsertRange(int index, ScopeNode[] items)
        {
            base.InsertRange(index, items);
        }

        private void ItemChanged(object sender, NodeChangedEventArgs e)
        {
            int index = base.List.IndexOf(sender);
            this.Notify(index, new ScopeNode[] { (ScopeNode) sender }, ScopeNodeCollectionChangeType.Modify);
        }

        private void Notify(int index, ScopeNode[] items, ScopeNodeCollectionChangeType action)
        {
            if (this.ItemsChanged != null)
            {
                this.ItemsChanged(this, new ScopeNodeCollectionEventArgs(index, items, action));
            }
        }

        protected override void OnItemsAdded(int index, object[] items)
        {
            foreach (ScopeNode node in items)
            {
                node.Changed += new Node.NodeChangedEventHandler(this.ItemChanged);
                node.SetParent(this.ContainerNode);
            }
            ScopeNode[] destinationArray = new ScopeNode[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ScopeNodeCollectionChangeType.Add);
        }

        protected override void OnItemsRemoved(int index, object[] items)
        {
            foreach (ScopeNode node in items)
            {
                node.Changed -= new Node.NodeChangedEventHandler(this.ItemChanged);
                node.SetParent(null);
            }
            ScopeNode[] destinationArray = new ScopeNode[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ScopeNodeCollectionChangeType.Remove);
        }

        internal override void OnValidate(object objectToValidate, bool testForDuplicate)
        {
            base.OnValidate(objectToValidate, testForDuplicate);
            ScopeNode node = (ScopeNode) objectToValidate;
            for (ScopeNode node2 = this.ContainerNode; node2 != null; node2 = node2.Parent)
            {
                if (node == node2)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("objectToValidate", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionCircularReference, new object[0]);
                }
            }
        }

        public void Remove(ScopeNode item)
        {
            base.List.Remove(item);
        }

        public ScopeNode[] ToArray()
        {
            return (ScopeNode[]) base.InnerList.ToArray(typeof(ScopeNode));
        }

        internal ScopeNode ContainerNode
        {
            get
            {
                return this._containerNode;
            }
            set
            {
                this._containerNode = value;
                foreach (ScopeNode node in base.InnerList)
                {
                    node.SetParent(this._containerNode);
                }
            }
        }

        public ScopeNode this[int index]
        {
            get
            {
                return (ScopeNode) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void ScopeNodeCollectionEventHandler(object sender, ScopeNodeCollectionEventArgs e);
    }
}

