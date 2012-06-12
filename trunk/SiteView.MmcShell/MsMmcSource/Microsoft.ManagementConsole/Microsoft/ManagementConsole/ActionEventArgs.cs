namespace Microsoft.ManagementConsole
{
    using System;

    public sealed class ActionEventArgs : EventArgs
    {
        private Microsoft.ManagementConsole.Action _action;
        private AsyncStatus _status;

        public ActionEventArgs(Microsoft.ManagementConsole.Action action, AsyncStatus status)
        {
            this._action = action;
            this._status = status;
        }

        public Microsoft.ManagementConsole.Action Action
        {
            get
            {
                return this._action;
            }
        }

        public AsyncStatus Status
        {
            get
            {
                return this._status;
            }
        }
    }
}

