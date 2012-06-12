namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PasteNodeRequestInfo : NodeRequestInfo
    {
        private int _dataObjectId;
        private DragAndDropVerb _pasteType;

        public int DataObjectId
        {
            get
            {
                return this._dataObjectId;
            }
            set
            {
                this._dataObjectId = value;
            }
        }

        public DragAndDropVerb PasteType
        {
            get
            {
                return this._pasteType;
            }
            set
            {
                this._pasteType = value;
            }
        }
    }
}

