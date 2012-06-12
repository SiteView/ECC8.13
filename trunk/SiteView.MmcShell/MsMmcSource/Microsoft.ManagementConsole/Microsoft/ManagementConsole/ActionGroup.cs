namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class ActionGroup : ActionsPaneExtendedItem
    {
        private ActionsPaneItemCollectionData _data;
        private ActionsPaneItemCollection _items;

        public ActionGroup()
        {
            this._data = new ActionsPaneItemCollectionData();
            this._items = new ActionsPaneItemCollection();
            base.Initialize(this._data, string.Empty, string.Empty, -1, null);
            this._items.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnItemsChanged);
        }

        public ActionGroup(string displayName, string description) : this(displayName, description, -1)
        {
        }

        public ActionGroup(string displayName, string description, int imageIndex) : this(displayName, description, imageIndex, null)
        {
        }

        public ActionGroup(string displayName, string description, int imageIndex, object tag)
        {
            this._data = new ActionsPaneItemCollectionData();
            this._items = new ActionsPaneItemCollection();
            if (description == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("description", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullValue, new object[0]);
            }
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(displayName, "displayName", true);
            base.Initialize(this._data, displayName, description, imageIndex, tag);
            this._items.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnItemsChanged);
        }

        private void OnItemDataChanged(object sender, EventArgs e)
        {
            base.Notify();
        }

        private void OnItemsChanged(object sender, ActionsPaneItemCollectionEventArgs e)
        {
            ActionsPaneItem[] items = e.GetItems();
            switch (e.ChangeType)
            {
                case ActionsPaneItemCollectionChangeType.Add:
                    foreach (ActionsPaneItem item in items)
                    {
                        item.Changed += new EventHandler(this.OnItemDataChanged);
                    }
                    this.RefreshChildData();
                    base.Notify();
                    return;

                case ActionsPaneItemCollectionChangeType.Remove:
                    foreach (ActionsPaneItem item2 in items)
                    {
                        item2.Changed -= new EventHandler(this.OnItemDataChanged);
                    }
                    this.RefreshChildData();
                    base.Notify();
                    return;
            }
        }

        private void RefreshChildData()
        {
            ActionsPaneItemData[] items = new ActionsPaneItemData[this.Items.Count];
            for (int i = 0; i < this.Items.Count; i++)
            {
                items[i] = this.Items[i].Data;
            }
            this._data.SetItems(items);
        }

        public ActionsPaneItemCollection Items
        {
            get
            {
                return this._items;
            }
        }

        public bool RenderAsRegion
        {
            get
            {
                return this._data.RenderAsRegion;
            }
            set
            {
                if (this._data.RenderAsRegion != value)
                {
                    this._data.RenderAsRegion = value;
                    base.Notify();
                }
            }
        }
    }
}

