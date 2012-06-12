namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole.Internal;
    using Microsoft.ManagementConsole.Interop;
    using System;
    using System.Runtime.CompilerServices;
    using System.Windows.Forms;

    public class WaitCursor
    {
        private System.Windows.Forms.DialogResult _dialogResult = System.Windows.Forms.DialogResult.OK;
        private bool _insideModalLoop;
        private bool _quitMessagePosted;
        private bool _timedOut;
        private TimeSpan _timeout = BeginModalLoopConsoleDialogCommand.DefaultTimeout;

        public event EventHandler Start;

        public void Exit()
        {
            this.OnExit(false);
        }

        private void InnerStart()
        {
            this.OnStart();
            if (this.Start != null)
            {
                this.Start(this, new EventArgs());
            }
        }

        private void OnExit(bool timedOut)
        {
            if (this._insideModalLoop && !this._quitMessagePosted)
            {
                this._quitMessagePosted = true;
                this._timedOut = timedOut;
                ModalLoop.Exit();
            }
        }

        protected virtual void OnStart()
        {
        }

        private void OnTimer(object sender, EventArgs e)
        {
            this.OnExit(true);
        }

        internal bool Run()
        {
            bool flag;
            if (this._insideModalLoop)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionInternalConsoleDialogHostAlreadyInsideModalLoop));
            }
            Timer timer = new Timer();
            try
            {
                Application.UseWaitCursor = true;
                this._insideModalLoop = true;
                timer.Tick += new EventHandler(this.OnTimer);
                timer.Interval = (int) this.Timeout.TotalMilliseconds;
                timer.Start();
                this.InnerStart();
                ModalLoop.Run();
                flag = !this._timedOut;
            }
            finally
            {
                timer.Dispose();
                this._timedOut = false;
                this._quitMessagePosted = false;
                this._insideModalLoop = false;
                Application.UseWaitCursor = false;
            }
            return flag;
        }

        public System.Windows.Forms.DialogResult DialogResult
        {
            get
            {
                return this._dialogResult;
            }
            set
            {
                this._dialogResult = value;
            }
        }

        public TimeSpan Timeout
        {
            get
            {
                return this._timeout;
            }
            set
            {
                if (value > BeginModalLoopConsoleDialogCommand.MaxTimeout)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, new TimeSpan(), BeginModalLoopConsoleDialogCommand.MaxTimeout);
                }
                this._timeout = value;
            }
        }
    }
}

