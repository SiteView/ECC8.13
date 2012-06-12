namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole.Internal;
    using Microsoft.ManagementConsole.Interop;
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    public class WaitDialog : Component
    {
        private bool _canCancel;
        private WaitDialogCancelCallback _cancelCallback;
        private bool _completed;
        private IWaitDialog _coreWaitDialog;
        private static int _defaultDisplayDelayMSecs = 0x1388;
        private static int _defaultMinimumDisplayTimeMSecs = 0x7d0;
        private int _displayDelayMSecs = _defaultDisplayDelayMSecs;
        private bool _isDisposed;
        private int _minimumDisplayTimeMSecs = _defaultMinimumDisplayTimeMSecs;
        private string _name = string.Empty;
        private string _statusText = string.Empty;
        private object _syncRoot = new object();
        private string _title = string.Empty;
        private int _totalWork;
        private static Guid _waitDialogClsid = new Guid("2D11CF10-4FE0-45b2-88DF-6FFBF92BE9AB");
        private NativeWindow _waitDialogWindow = new NativeWindow();
        private int _workProcessed;

        public event EventHandler Cancel
        {
            add
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._cancelCallback.Cancel += value;
                }
            }
            remove
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._cancelCallback.Cancel -= value;
                }
            }
        }

        public WaitDialog()
        {
            this._cancelCallback = new WaitDialogCancelCallback(this, this._syncRoot);
        }

        public void CompleteDialog()
        {
            lock (this._syncRoot)
            {
                if (this._isDisposed)
                {
                    throw new ObjectDisposedException(this.Name);
                }
                this._completed = true;
                if (this._coreWaitDialog != null)
                {
                    this._coreWaitDialog.CompleteRequest();
                }
            }
        }

        protected override void Dispose(bool disposing)
        {
            lock (this._syncRoot)
            {
                if (!this._isDisposed)
                {
                    this._isDisposed = true;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.CompleteRequest();
                        Marshal.ReleaseComObject(this._coreWaitDialog);
                        this._coreWaitDialog = null;
                    }
                }
            }
        }

        private int GetMSecsFromTimeSpan(TimeSpan ts)
        {
            double totalMilliseconds = ts.TotalMilliseconds;
            if (totalMilliseconds > 2147483647)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("ts", ts, "int.MaxValue");
            }
            return (int) totalMilliseconds;
        }

        public void ShowDialog()
        {
            this.ShowDialog(null);
        }

        public void ShowDialog(IWin32Window owner)
        {
            bool flag = false;
            HandleRef ref2 = new HandleRef(owner, (owner != null) ? owner.Handle : Microsoft.ManagementConsole.Interop.NativeMethods.GetDesktopWindow());
            lock (this._syncRoot)
            {
                if (this._coreWaitDialog != null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedWaitDialogShowDialogTwiceNotAllowed));
                }
                if (this._isDisposed)
                {
                    throw new ObjectDisposedException(this.Name);
                }
                System.Type typeFromCLSID = System.Type.GetTypeFromCLSID(_waitDialogClsid);
                this._coreWaitDialog = (IWaitDialog) Activator.CreateInstance(typeFromCLSID);
                flag = this._completed;
                if (!flag)
                {
                    this._coreWaitDialog.UpdateTitle(this._title);
                    this._coreWaitDialog.SetCancelable(this._canCancel);
                    this._coreWaitDialog.UpdateProgress(this._workProcessed, this._totalWork, this._statusText);
                }
            }
            try
            {
                if (!flag)
                {
                    this._coreWaitDialog.RunModal(ref2.Handle, (uint) this._displayDelayMSecs, (uint) this._minimumDisplayTimeMSecs, this._cancelCallback);
                }
            }
            finally
            {
                lock (this._syncRoot)
                {
                    this._completed = false;
                    if (this._coreWaitDialog != null)
                    {
                        Marshal.ReleaseComObject(this._coreWaitDialog);
                        this._coreWaitDialog = null;
                    }
                }
            }
        }

        public void UpdateProgress(int workProcessed, int totalWork, string statusText)
        {
            lock (this._syncRoot)
            {
                if (this._isDisposed)
                {
                    throw new ObjectDisposedException(this.Name);
                }
                this._workProcessed = workProcessed;
                this._totalWork = totalWork;
                this._statusText = statusText;
                if (this._coreWaitDialog != null)
                {
                    this._coreWaitDialog.UpdateProgress(this._workProcessed, this._totalWork, this._statusText);
                }
            }
        }

        public bool CanCancel
        {
            get
            {
                return this._canCancel;
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._canCancel = value;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.SetCancelable(value);
                    }
                }
            }
        }

        public TimeSpan DisplayDelay
        {
            get
            {
                return new TimeSpan(0, 0, 0, 0, this._displayDelayMSecs);
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    if (this._coreWaitDialog != null)
                    {
                        throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedWaitDialogInvalidSet, new object[] { "DisplayDelay" }));
                    }
                    this._displayDelayMSecs = this.GetMSecsFromTimeSpan(value);
                }
            }
        }

        public TimeSpan MinimumDisplayTime
        {
            get
            {
                return new TimeSpan(0, 0, 0, 0, this._minimumDisplayTimeMSecs);
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    if (this._coreWaitDialog != null)
                    {
                        throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedWaitDialogInvalidSet, new object[] { "MinimumDisplayTime" }));
                    }
                    this._minimumDisplayTimeMSecs = this.GetMSecsFromTimeSpan(value);
                }
            }
        }

        public string Name
        {
            get
            {
                return this._name;
            }
            set
            {
                this._name = value;
            }
        }

        public string StatusText
        {
            get
            {
                return this._statusText;
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._statusText = value;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.UpdateProgress(this._workProcessed, this._totalWork, this._statusText);
                    }
                }
            }
        }

        public string Title
        {
            get
            {
                return this._title;
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._title = value;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.UpdateTitle(value);
                    }
                }
            }
        }

        public int TotalWork
        {
            get
            {
                return this._totalWork;
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._totalWork = value;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.UpdateProgress(this._workProcessed, this._totalWork, this._statusText);
                    }
                }
            }
        }

        internal NativeWindow WaitDialogWindow
        {
            get
            {
                return this._waitDialogWindow;
            }
        }

        public int WorkProcessed
        {
            get
            {
                return this._workProcessed;
            }
            set
            {
                lock (this._syncRoot)
                {
                    if (this._isDisposed)
                    {
                        throw new ObjectDisposedException(this.Name);
                    }
                    this._workProcessed = value;
                    if (this._coreWaitDialog != null)
                    {
                        this._coreWaitDialog.UpdateProgress(this._workProcessed, this._totalWork, this._statusText);
                    }
                }
            }
        }

        private class WaitDialogCancelCallback : IWaitDialogCancelCallback
        {
            private EventHandler _cancel;
            private WaitDialog _owner;
            private object _syncRoot;

            public event EventHandler Cancel
            {
                add
                {
                    lock (this._syncRoot)
                    {
                        this._cancel = (EventHandler) Delegate.Combine(this._cancel, value);
                    }
                }
                remove
                {
                    lock (this._syncRoot)
                    {
                        this._cancel = (EventHandler) Delegate.Remove(this._cancel, value);
                    }
                }
            }

            public WaitDialogCancelCallback(WaitDialog owner, object syncRoot)
            {
                this._owner = owner;
                this._syncRoot = syncRoot;
            }

            void IWaitDialogCancelCallback.Cancel(IntPtr waitDialogWindowHandle)
            {
                EventHandler handler = null;
                lock (this._syncRoot)
                {
                    handler = this._cancel;
                }
                if (handler != null)
                {
                    try
                    {
                        this._owner.WaitDialogWindow.AssignHandle(waitDialogWindowHandle);
                        handler(this._owner, new EventArgs());
                    }
                    finally
                    {
                        this._owner.WaitDialogWindow.ReleaseHandle();
                    }
                }
            }
        }
    }
}

