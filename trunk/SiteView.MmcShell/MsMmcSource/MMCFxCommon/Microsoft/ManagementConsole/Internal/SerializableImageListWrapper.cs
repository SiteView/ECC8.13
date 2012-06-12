namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Runtime.Serialization;
    using System.Security.Permissions;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SerializableImageListWrapper : ISerializable
    {
        private System.Windows.Forms.ImageList _imageList;

        public SerializableImageListWrapper()
        {
            this._imageList = new System.Windows.Forms.ImageList();
        }

        private SerializableImageListWrapper(SerializationInfo info, StreamingContext context)
        {
            this._imageList = new System.Windows.Forms.ImageList();
            this._imageList.ColorDepth = (ColorDepth) info.GetValue("ColorDepth", typeof(ColorDepth));
            this._imageList.ImageSize = (Size) info.GetValue("ImageSize", typeof(Size));
            this._imageList.TransparentColor = (Color) info.GetValue("TransparentColor", typeof(Color));
            this._imageList.ImageStream = (ImageListStreamer) info.GetValue("ImageStream", typeof(ImageListStreamer));
        }

        [SecurityPermission(SecurityAction.Demand, SerializationFormatter=true)]
        void ISerializable.GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("ColorDepth", this._imageList.ColorDepth);
            info.AddValue("ImageSize", this._imageList.ImageSize);
            info.AddValue("TransparentColor", this._imageList.TransparentColor);
            info.AddValue("ImageStream", this._imageList.ImageStream);
        }

        public System.Windows.Forms.ImageList ImageList
        {
            get
            {
                return this._imageList;
            }
            set
            {
                this._imageList = value;
            }
        }
    }
}

