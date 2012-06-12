namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Reflection;
    using System.Runtime.CompilerServices;

    public sealed class ActionsPaneItemCollection : BaseCollection
    {
        private ActionsPaneItemCollectionData _data;
        private ActionsInsertionLocation _insertionLocation;

        internal event ActionsPaneItemCollectionEventHandler Changed;

        public ActionsPaneItemCollection() : base(typeof(ActionsPaneItem))
        {
            this._data = new ActionsPaneItemCollectionData();
        }

        public int Add(ActionsPaneItem item)
        {
            return base.List.Add(item);
        }

        public void AddRange(ActionsPaneItem[] items)
        {
            base.AddRange(items);
        }

        private bool CheckForCircularReference(ActionGroup group)
        {
            if (group.Items == this)
            {
                return true;
            }
            foreach (ActionsPaneItem item in group.Items)
            {
                ActionGroup group2 = item as ActionGroup;
                if ((group2 != null) && this.CheckForCircularReference(group2))
                {
                    return true;
                }
            }
            return false;
        }

        public bool Contains(ActionsPaneItem item)
        {
            return base.List.Contains(item);
        }

        public void CopyTo(ActionsPaneItem[] array, int index)
        {
            this.CopyTo(array, index);
        }

        internal ActionsPaneItem GetItemById(int itemId)
        {
            foreach (ActionsPaneItem item in this)
            {
                if (item.Id == itemId)
                {
                    return item;
                }
                ActionGroup group = item as ActionGroup;
                if (group != null)
                {
                    ActionsPaneItem itemById = group.Items.GetItemById(itemId);
                    if (itemById != null)
                    {
                        return itemById;
                    }
                }
            }
            return null;
        }

        public int IndexOf(ActionsPaneItem item)
        {
            return base.List.IndexOf(item);
        }

        public void Insert(int index, ActionsPaneItem item)
        {
            base.Insert(index, item);
        }

        public void InsertRange(int index, ActionsPaneItem[] items)
        {
            base.InsertRange(index, items);
        }

        private void ItemChanged(object sender, EventArgs e)
        {
            int index = base.List.IndexOf(sender);
            this.SyncData();
            this.Notify(index, new ActionsPaneItem[] { (ActionsPaneItem) sender }, ActionsPaneItemCollectionChangeType.Modify);
        }

        private void Notify(int index, ActionsPaneItem[] items, ActionsPaneItemCollectionChangeType action)
        {
            if (this.Changed != null)
            {
                this.Changed(this, new ActionsPaneItemCollectionEventArgs(index, items, action));
            }
        }

        protected override void OnItemsAdded(int index, object[] items)
        {
            foreach (ActionsPaneItem item in items)
            {
                item.Data.InsertionLocation = this.InsertionLocation;
                item.Changed += new EventHandler(this.ItemChanged);
            }
            ActionsPaneItem[] destinationArray = new ActionsPaneItem[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.SyncData();
            this.Notify(index, destinationArray, ActionsPaneItemCollectionChangeType.Add);
        }

        protected override void OnItemsRemoved(int index, object[] items)
        {
            foreach (ActionsPaneItem item in items)
            {
                item.Changed -= new EventHandler(this.ItemChanged);
            }
            ActionsPaneItem[] destinationArray = new ActionsPaneItem[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.SyncData();
            this.Notify(index, destinationArray, ActionsPaneItemCollectionChangeType.Remove);
        }

        internal override void OnValidate(object objectToValidate, bool testForDuplicate)
        {
            base.OnValidate(objectToValidate, testForDuplicate);
            ActionsPaneExtendedItem item = objectToValidate as ActionsPaneExtendedItem;
            if (item != null)
            {
                ActionsPaneExtendedItemData.ValidateDisplayName(item.DisplayName);
            }
            ActionGroup group = objectToValidate as ActionGroup;
            if ((group != null) && this.CheckForCircularReference(group))
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("objectToValidate", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionCircularReference, new object[0]);
            }
        }

        public void Remove(ActionsPaneItem item)
        {
            base.List.Remove(item);
        }

        private void SyncData()
        {
            ActionsPaneItemData[] items = new ActionsPaneItemData[base.Count];
            for (int i = 0; i < base.Count; i++)
            {
                items[i] = this[i].Data;
            }
            this._data.SetItems(items);
        }

        public ActionsPaneItem[] ToArray()
        {
            return (ActionsPaneItem[]) base.InnerList.ToArray(typeof(ActionsPaneItem));
        }

        internal ActionsPaneItemCollectionData Data
        {
            get
            {
                return this._data;
            }
        }

        internal ActionsInsertionLocation InsertionLocation
        {
            get
            {
                return this._insertionLocation;
            }
            set
            {
                this._insertionLocation = value;
            }
        }

        public ActionsPaneItem this[int index]
        {
            get
            {
                return (ActionsPaneItem) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void ActionsPaneItemCollectionEventHandler(object sender, ActionsPaneItemCollectionEventArgs e);
    }
}

