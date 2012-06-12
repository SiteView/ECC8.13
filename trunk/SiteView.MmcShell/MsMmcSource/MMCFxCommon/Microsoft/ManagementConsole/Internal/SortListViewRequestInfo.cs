namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SortListViewRequestInfo : RequestInfo
    {
        private int _columnIndex = -1;
        private bool _descending;

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
    }
}

