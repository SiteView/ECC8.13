namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Threading;

    internal class AsyncDelegateQueue
    {
        private int _managedThreadId = Thread.CurrentThread.ManagedThreadId;
        private int _nextInvokeId;
        private Dictionary<int, AsyncDelegate> _pendingDelegates = new Dictionary<int, AsyncDelegate>();
        private ISnapInPlatform _snapInPlatform;

        public IAsyncResult BeginInvoke(Delegate method, object[] args)
        {
            AsyncDelegate delegate2 = new AsyncDelegate(method, args);
            if (!this.InvokeRequired)
            {
                delegate2.Execute(true);
                return delegate2;
            }
            BeginInvokeCommand command = null;
            lock (this.SyncRoot)
            {
                int key = this._nextInvokeId++;
                this._pendingDelegates.Add(key, delegate2);
                if (this._snapInPlatform != null)
                {
                    command = new BeginInvokeCommand();
                    command.Id = key;
                }
            }
            if (command != null)
            {
                this._snapInPlatform.ProcessCommand(command);
            }
            return delegate2;
        }

        public object EndInvoke(IAsyncResult result)
        {
            AsyncDelegate delegate2 = result as AsyncDelegate;
            if (delegate2 == null)
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.AsyncDelegateQueueEndInvokeInvokeMismatch), "result");
            }
            if (!delegate2.IsCompleted)
            {
                delegate2.AsyncWaitHandle.WaitOne();
            }
            return delegate2.DelegateResult;
        }

        public void Initialize(ISnapInPlatform snapInPlatform)
        {
            if (snapInPlatform == null)
            {
                throw new ArgumentNullException("snapInPlatform");
            }
            AsyncDelegate[] array = null;
            lock (this.SyncRoot)
            {
                this._snapInPlatform = snapInPlatform;
                array = new AsyncDelegate[this._pendingDelegates.Values.Count];
                this._pendingDelegates.Values.CopyTo(array, 0);
                this._pendingDelegates.Clear();
            }
            if (array != null)
            {
                foreach (AsyncDelegate delegate2 in array)
                {
                    delegate2.Execute(false);
                }
            }
        }

        public object Invoke(Delegate method, object[] args)
        {
            return this.EndInvoke(this.BeginInvoke(method, args));
        }

        public void Notify(BeginInvokeNotification notification)
        {
            if (notification == null)
            {
                throw new ArgumentNullException("notification");
            }
            AsyncDelegate delegate2 = null;
            lock (this.SyncRoot)
            {
                if (this._pendingDelegates.TryGetValue(notification.Id, out delegate2))
                {
                    this._pendingDelegates.Remove(notification.Id);
                }
                else
                {
                    delegate2 = null;
                }
            }
            if (delegate2 != null)
            {
                delegate2.Execute(false);
            }
        }

        public bool InvokeRequired
        {
            get
            {
                return (Thread.CurrentThread.ManagedThreadId != this._managedThreadId);
            }
        }

        private object SyncRoot
        {
            get
            {
                return this._pendingDelegates;
            }
        }
    }
}

