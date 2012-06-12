namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateColumnsCommand : ViewCommand
    {
        private ColumnCollectionChangeType _changeType;
        private ColumnData[] _data;
        private int _index = -1;

        public ColumnData[] GetData()
        {
            return this._data;
        }

        public void SetData(ColumnData[] data)
        {
            this._data = data;
        }

        public ColumnCollectionChangeType ChangeType
        {
            get
            {
                return this._changeType;
            }
            set
            {
                this._changeType = value;
            }
        }

        public int Index
        {
            get
            {
                return this._index;
            }
            set
            {
                this._index = value;
            }
        }
    }
}

