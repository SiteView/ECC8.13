namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Drawing;
    using System.Reflection;
    using System.Runtime.CompilerServices;
    using System.Windows.Forms;

    public sealed class SnapInImageList : ICollection, IEnumerable
    {
        private System.Windows.Forms.ImageList _innerList = new System.Windows.Forms.ImageList();

        internal event EventHandler Changed;

        public void Add(Icon value)
        {
            this._innerList.Images.Add(value);
            this.Notify();
        }

        public void Add(Image value)
        {
            this._innerList.Images.Add(value);
            this.Notify();
        }

        public int Add(Image value, Color transparentColor)
        {
            int num = this._innerList.Images.Add(value, transparentColor);
            this.Notify();
            return num;
        }

        public int AddStrip(Image value)
        {
            int num = this._innerList.Images.AddStrip(value);
            this.Notify();
            return num;
        }

        public void Clear()
        {
            this._innerList.Images.Clear();
            this.Notify();
        }

        public void CopyTo(SnapInImageList imageList, int index)
        {
            if (imageList == null)
            {
                throw new ArgumentNullException("imageList");
            }
            if ((index >= imageList.Count) || (this.ImageList.Images.Count > (imageList.Count - index)))
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("index", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionCopyTo, new object[0]);
            }
            for (int i = 0; i < this.ImageList.Images.Count; i++)
            {
                imageList[index++] = this.ImageList.Images[i];
            }
        }

        public void CopyTo(Array array, int index)
        {
            ((ICollection) this._innerList.Images).CopyTo(array, index);
        }

        public IEnumerator GetEnumerator()
        {
            return this._innerList.Images.GetEnumerator();
        }

        private void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, null);
            }
        }

        public void RemoveAt(int index)
        {
            this._innerList.Images.RemoveAt(index);
            this.Notify();
        }

        public int Count
        {
            get
            {
                return this._innerList.Images.Count;
            }
        }

        public bool Empty
        {
            get
            {
                return this._innerList.Images.Empty;
            }
        }

        internal System.Windows.Forms.ImageList ImageList
        {
            get
            {
                return this._innerList;
            }
        }

        public bool IsSynchronized
        {
            get
            {
                return ((ICollection) this._innerList.Images).IsSynchronized;
            }
        }

        public Image this[int index]
        {
            get
            {
                return this._innerList.Images[index];
            }
            set
            {
                this._innerList.Images[index] = value;
                this.Notify();
            }
        }

        public object SyncRoot
        {
            get
            {
                return ((ICollection) this._innerList.Images).SyncRoot;
            }
        }

        public Color TransparentColor
        {
            get
            {
                return this._innerList.TransparentColor;
            }
            set
            {
                this._innerList.TransparentColor = value;
                this.Notify();
            }
        }
    }
}

