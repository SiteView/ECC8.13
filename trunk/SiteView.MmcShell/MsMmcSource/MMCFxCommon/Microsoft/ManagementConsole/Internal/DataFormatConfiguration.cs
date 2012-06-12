namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    [Serializable, StructLayout(LayoutKind.Sequential), EditorBrowsable(EditorBrowsableState.Never)]
    public struct DataFormatConfiguration
    {
        private string _clipboardFormatId;
        private bool _requiresQuery;
        public string ClipboardFormatId
        {
            get
            {
                return this._clipboardFormatId;
            }
            set
            {
                CommonValidation.ValidateClipboardFormatId(value);
                this._clipboardFormatId = value;
            }
        }
        public bool RequiresQuery
        {
            get
            {
                return this._requiresQuery;
            }
            set
            {
                this._requiresQuery = value;
            }
        }
        public static bool operator ==(DataFormatConfiguration a, DataFormatConfiguration b)
        {
            return (a.ClipboardFormatId == b.ClipboardFormatId);
        }

        public static bool operator !=(DataFormatConfiguration a, DataFormatConfiguration b)
        {
            return (a != b);
        }

        public override bool Equals(object obj)
        {
            bool flag = false;
            if (obj is DataFormatConfiguration)
            {
                flag = ((DataFormatConfiguration) obj) == this;
            }
            return flag;
        }

        public override int GetHashCode()
        {
            return this.ClipboardFormatId.GetHashCode();
        }
    }
}

