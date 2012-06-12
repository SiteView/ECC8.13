namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SetFormViewControlCommand : ViewCommand
    {
        private IntPtr _handle = IntPtr.Zero;

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
    }
}

