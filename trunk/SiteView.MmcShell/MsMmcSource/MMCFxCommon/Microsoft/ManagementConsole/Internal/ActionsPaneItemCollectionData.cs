namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ActionsPaneItemCollectionData : ActionsPaneExtendedItemData
    {
        private ActionsPaneItemData[] _items;
        private bool _renderAsRegion;

        public ActionsPaneItemData[] GetItems()
        {
            return this._items;
        }

        public void SetItems(ActionsPaneItemData[] items)
        {
            this._items = items;
        }

        public bool RenderAsRegion
        {
            get
            {
                return this._renderAsRegion;
            }
            set
            {
                this._renderAsRegion = value;
            }
        }
    }
}

