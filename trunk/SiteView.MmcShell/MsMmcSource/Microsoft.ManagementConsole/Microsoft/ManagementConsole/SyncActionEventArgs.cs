namespace Microsoft.ManagementConsole
{
    using System;

    public sealed class SyncActionEventArgs : EventArgs
    {
        private SyncAction _action;
        private SyncStatus _status;

        public SyncActionEventArgs(SyncAction action, SyncStatus status)
        {
            this._action = action;
            this._status = status;
        }

        public SyncAction Action
        {
            get
            {
                return this._action;
            }
        }

        public SyncStatus Status
        {
            get
            {
                return this._status;
            }
        }
    }
}

