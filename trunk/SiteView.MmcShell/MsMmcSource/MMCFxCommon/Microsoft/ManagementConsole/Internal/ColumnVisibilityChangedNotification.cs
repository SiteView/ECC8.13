namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ColumnVisibilityChangedNotification : Notification
    {
        private int[] _hiddenIds = new int[0];
        private int[] _visibleIds = new int[0];

        public int[] GetHiddenIds()
        {
            return this._hiddenIds;
        }

        public int[] GetVisibleIds()
        {
            return this._visibleIds;
        }

        public void SetHiddenIds(int[] hiddenIds)
        {
            this._hiddenIds = hiddenIds;
        }

        public void SetVisibleIds(int[] visibleIds)
        {
            this._visibleIds = visibleIds;
        }
    }
}

