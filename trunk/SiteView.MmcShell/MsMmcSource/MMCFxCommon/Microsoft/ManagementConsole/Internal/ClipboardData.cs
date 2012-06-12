namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    [Serializable, StructLayout(LayoutKind.Sequential), EditorBrowsable(EditorBrowsableState.Never)]
    public struct ClipboardData
    {
        private string _clipboardFormatId;
        private byte[] _value;
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
        public byte[] GetValue()
        {
            return this._value;
        }

        public void SetValue(byte[] value)
        {
            this._value = value;
        }

        public override bool Equals(object obj)
        {
            bool flag = false;
            if (obj is DataFormatConfiguration)
            {
                flag = ((ClipboardData) obj) == this;
            }
            return flag;
        }

        public override int GetHashCode()
        {
            return this.ClipboardFormatId.GetHashCode();
        }

        public static bool operator ==(ClipboardData a, ClipboardData b)
        {
            return (a.ClipboardFormatId == b.ClipboardFormatId);
        }

        public static bool operator !=(ClipboardData a, ClipboardData b)
        {
            return (a != b);
        }
    }
}

