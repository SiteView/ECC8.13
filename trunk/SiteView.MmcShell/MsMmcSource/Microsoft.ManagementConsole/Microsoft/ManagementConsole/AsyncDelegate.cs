namespace Microsoft.ManagementConsole
{
    using System;
    using System.Threading;

    internal class AsyncDelegate : IAsyncResult
    {
        private object[] _args;
        private Delegate _asyncDelegate;
        private ManualResetEvent _completedEvent = new ManualResetEvent(false);
        private bool _completedSync;
        private object _delegateResult;
        private bool _isCompleted;

        public AsyncDelegate(Delegate asyncDelegate, object[] args)
        {
            if (asyncDelegate == null)
            {
                throw new ArgumentNullException("asyncDelegate");
            }
            this._asyncDelegate = asyncDelegate;
            this._args = args;
        }

        public void Execute(bool completeSync)
        {
            try
            {
                this._delegateResult = this._asyncDelegate.DynamicInvoke(this._args);
            }
            finally
            {
                this._isCompleted = true;
                this._completedSync = completeSync;
                this._completedEvent.Set();
            }
        }

        public object AsyncState
        {
            get
            {
                return null;
            }
        }

        public WaitHandle AsyncWaitHandle
        {
            get
            {
                return this._completedEvent;
            }
        }

        public bool CompletedSynchronously
        {
            get
            {
                return this._completedSync;
            }
        }

        public object DelegateResult
        {
            get
            {
                return this._delegateResult;
            }
        }

        public bool IsCompleted
        {
            get
            {
                return this._isCompleted;
            }
        }
    }
}

