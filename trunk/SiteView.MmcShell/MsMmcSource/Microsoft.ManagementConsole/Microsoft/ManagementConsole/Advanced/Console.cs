namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Windows.Forms;

    public sealed class Console
    {
        private ConsoleDialogHost _dialogHost = new ConsoleDialogHost(-1);

        internal Console()
        {
        }

        internal void Initialize(ISnapInPlatform platform)
        {
            if (platform == null)
            {
                throw new ArgumentNullException("platform");
            }
            this._dialogHost.Initialize(platform);
        }

        public void Show(Form form)
        {
            this._dialogHost.Show(form);
        }

        public DialogResult ShowDialog(MessageBoxParameters parameters)
        {
            return this._dialogHost.ShowDialog(parameters);
        }

        public DialogResult ShowDialog(CommonDialog commonDialog)
        {
            return this._dialogHost.ShowDialog(commonDialog);
        }

        public DialogResult ShowDialog(Form form)
        {
            return this._dialogHost.ShowDialog(form);
        }

        public DialogResult ShowDialog(Form form, WaitCursor waitCursor)
        {
            return this._dialogHost.ShowDialog(form, waitCursor);
        }
    }
}

