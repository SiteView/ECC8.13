namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole.Advanced;
    using System;
    using System.Runtime.CompilerServices;
    using System.Windows.Forms;

    internal class ConsoleDialogHost
    {
        private int _ownerId;
        private ISnapInPlatform _platform;

        internal ConsoleDialogHost(int ownerId)
        {
            this._ownerId = ownerId;
        }

        internal void Initialize(ISnapInPlatform platform)
        {
            if (platform == null)
            {
                throw new ArgumentNullException("platform");
            }
            this._platform = platform;
        }

        public void Show(Form form)
        {
            if (form == null)
            {
                throw new ArgumentNullException("form");
            }
            if (this._platform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionInternalConsoleDialogHostOwnerNotInitialized));
            }
            GetPopupParentWindowCommand command = new GetPopupParentWindowCommand();
            command.OwnerId = this._ownerId;
            GetPopupParentWindowCommandResult result = (GetPopupParentWindowCommandResult) this._platform.ProcessCommand(command);
            form.Show(result.ParentWindow);
        }

        public DialogResult ShowDialog(MessageBoxParameters parameters)
        {
            if (parameters == null)
            {
                throw new ArgumentNullException("parameters");
            }
            return this.ShowDialog(null, new ShowDialogCallback(parameters.ShowDialog));
        }

        public DialogResult ShowDialog(CommonDialog commonDialog)
        {
            if (commonDialog == null)
            {
                throw new ArgumentNullException("commonDialog");
            }
            return this.ShowDialog(null, new ShowDialogCallback(commonDialog.ShowDialog));
        }

        public DialogResult ShowDialog(Form form)
        {
            return this.ShowDialog(form, null);
        }

        private DialogResult ShowDialog(WaitCursor waitCursor, ShowDialogCallback callback)
        {
            DialogResult result;
            IWin32Window owner = null;
            if (this._platform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionInternalConsoleDialogHostOwnerNotInitialized));
            }
            try
            {
                BeginModalLoopConsoleDialogCommand command = new BeginModalLoopConsoleDialogCommand();
                command.OwnerId = this._ownerId;
                BeginModalLoopConsoleDialogCommandResult result2 = (BeginModalLoopConsoleDialogCommandResult) this._platform.ProcessCommand(command);
                owner = result2.Window;
                if ((waitCursor != null) && waitCursor.Run())
                {
                    return waitCursor.DialogResult;
                }
                result = callback(owner);
            }
            finally
            {
                EndModalLoopConsoleDialogCommand command2 = new EndModalLoopConsoleDialogCommand();
                command2.OwnerId = this._ownerId;
                this._platform.ProcessCommand(command2);
            }
            return result;
        }

        public DialogResult ShowDialog(Form form, WaitCursor waitCursor)
        {
            if (form == null)
            {
                throw new ArgumentNullException("form");
            }
            return this.ShowDialog(waitCursor, new ShowDialogCallback(form.ShowDialog));
        }

        internal bool Initialized
        {
            get
            {
                return (this._platform != null);
            }
        }

        private delegate DialogResult ShowDialogCallback(IWin32Window owner);
    }
}

