namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public class NodeData
    {
        private string _displayName = string.Empty;
        private int _id;
        private int _imageIndex;
        private NodeSubItemData[] _subItems = new NodeSubItemData[0];

        public NodeSubItemData[] GetSubItems()
        {
            return this._subItems;
        }

        public void SetSubItems(NodeSubItemData[] subItems)
        {
            this._subItems = subItems;
        }

        public string DisplayName
        {
            get
            {
                return this._displayName;
            }
            set
            {
                this._displayName = value;
            }
        }

        public int Id
        {
            get
            {
                return this._id;
            }
            set
            {
                this._id = value;
            }
        }

        public int ImageIndex
        {
            get
            {
                return this._imageIndex;
            }
            set
            {
                this._imageIndex = value;
            }
        }
    }
}

