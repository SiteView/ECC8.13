namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    [Serializable, StructLayout(LayoutKind.Sequential), EditorBrowsable(EditorBrowsableState.Never)]
    public struct WindowsMessage
    {
        private IntPtr hwnd;
        private uint message;
        private IntPtr wParam;
        private IntPtr lParam;
        private ulong time;
        private Microsoft.ManagementConsole.Internal.POINT pt;
        public WindowsMessage(System.Windows.Forms.Message m)
        {
            this.hwnd = m.HWnd;
            this.message = (uint) m.Msg;
            this.lParam = m.LParam;
            this.wParam = m.WParam;
            this.time = 0L;
            this.pt = new Microsoft.ManagementConsole.Internal.POINT();
        }

        public static bool operator ==(WindowsMessage a, WindowsMessage b)
        {
            if ((((a.hwnd == b.hwnd) && (a.message == b.message)) && ((a.lParam == b.lParam) && (a.wParam == b.wParam))) && ((a.time == b.time) && (a.pt.x == b.pt.x)))
            {
                return (a.pt.y == b.pt.y);
            }
            return false;
        }

        public static bool operator !=(WindowsMessage a, WindowsMessage b)
        {
            return (a != b);
        }

        public override bool Equals(object obj)
        {
            bool flag = false;
            if (obj is WindowsMessage)
            {
                flag = ((WindowsMessage) obj) == this;
            }
            return flag;
        }

        public override int GetHashCode()
        {
            return (int) this.message;
        }

        [CLSCompliant(false)]
        public uint Message
        {
            get
            {
                return this.message;
            }
        }
        public IntPtr WParam
        {
            get
            {
                return this.wParam;
            }
        }
        public IntPtr LParam
        {
            get
            {
                return this.lParam;
            }
        }
    }
}

