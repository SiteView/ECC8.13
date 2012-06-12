namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SetPropertyPageControlCommand : Microsoft.ManagementConsole.Internal.Command
    {
        private System.Windows.Forms.Control _control;
        private IntPtr _handle = IntPtr.Zero;
        private int _pageId = -1;
        private int _sheetId = -1;

        public System.Windows.Forms.Control Control
        {
            get
            {
                return this._control;
            }
            set
            {
                this._control = value;
            }
        }

        public IntPtr Handle
        {
            get
            {
                return this._handle;
            }
            set
            {
                this._handle = value;
            }
        }

        public int PageId
        {
            get
            {
                return this._pageId;
            }
            set
            {
                this._pageId = value;
            }
        }

        public int SheetId
        {
            get
            {
                return this._sheetId;
            }
            set
            {
                this._sheetId = value;
            }
        }
    }
}

