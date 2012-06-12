namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SnapInData
    {
        private bool _isModified;
        private SerializableImageListWrapper _largeImages = new SerializableImageListWrapper();
        private SerializableImageListWrapper _smallImages = new SerializableImageListWrapper();

        public bool IsModified
        {
            get
            {
                return this._isModified;
            }
            set
            {
                this._isModified = value;
            }
        }

        public ImageList LargeImages
        {
            get
            {
                return this._largeImages.ImageList;
            }
            set
            {
                this._largeImages.ImageList = value;
            }
        }

        public ImageList SmallImages
        {
            get
            {
                return this._smallImages.ImageList;
            }
            set
            {
                this._smallImages.ImageList = value;
            }
        }
    }
}

