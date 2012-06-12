namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SortListViewCommand : ViewCommand
    {
        private int _columnIndex = -1;
        private bool _descending;
        private bool _hideSortIcon;
        private int[] _ids = new int[0];

        public int[] GetIds()
        {
            return this._ids;
        }

        public void SetIds(int[] ids)
        {
            this._ids = ids;
        }

        public int ColumnIndex
        {
            get
            {
                return this._columnIndex;
            }
            set
            {
                this._columnIndex = value;
            }
        }

        public bool Descending
        {
            get
            {
                return this._descending;
            }
            set
            {
                this._descending = value;
            }
        }

        public bool HideSortIcon
        {
            get
            {
                return this._hideSortIcon;
            }
            set
            {
                this._hideSortIcon = value;
            }
        }
    }
}

