namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateResultNodesCommand : ViewCommand
    {
        private ResultNodeCollectionChangeType _changeType;
        private NodeData[] _data;
        private int _index = -1;

        public NodeData[] GetData()
        {
            return this._data;
        }

        public void SetData(NodeData[] data)
        {
            this._data = data;
        }

        public ResultNodeCollectionChangeType ChangeType
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

