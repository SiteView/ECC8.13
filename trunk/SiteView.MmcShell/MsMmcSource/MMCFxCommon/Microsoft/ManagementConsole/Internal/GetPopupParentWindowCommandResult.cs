namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class GetPopupParentWindowCommandResult : CommandResult
    {
        private IWin32Window _parentWindow;

        public IWin32Window ParentWindow
        {
            get
            {
                return this._parentWindow;
            }
            set
            {
                this._parentWindow = value;
            }
        }
    }
}

