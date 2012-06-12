namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class BeginModalLoopConsoleDialogCommandResult : CommandResult
    {
        private IWin32Window _window;

        public IWin32Window Window
        {
            get
            {
                return this._window;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._window = value;
            }
        }
    }
}

