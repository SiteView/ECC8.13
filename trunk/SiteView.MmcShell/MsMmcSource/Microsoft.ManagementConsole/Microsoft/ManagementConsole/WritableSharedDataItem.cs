namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public class WritableSharedDataItem : SharedDataItemBase
    {
        private bool _requiresCallback;

        internal event SharedDataChangedEventHandler Changed;

        internal event SharedDataChangeRequestEventHandler PropertyChangeRequested;

        public WritableSharedDataItem(string clipboardFormatId, bool requiresCallback) : base(clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            this._requiresCallback = requiresCallback;
        }

        private void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, new WritableSharedDataChangedEventArgs(WritableSharedDataChangeType.Modify, this));
            }
        }

        internal void OnPropertyUpdateRequested(byte[] value, IRequestStatus status)
        {
            if (this.PropertyChangeRequested != null)
            {
                this.PropertyChangeRequested(this, new WritableSharedDataChangeRequestEventArgs(value, status, this));
            }
        }

        public void SetData(byte[] value)
        {
            if ((value == null) && !this._requiresCallback)
            {
                throw new ArgumentNullException("value");
            }
            if (value == null)
            {
                base.InternalSetData(null);
            }
            else
            {
                base.InternalSetData((byte[]) value.Clone());
            }
            this.Notify();
        }

        public bool RequiresCallback
        {
            get
            {
                return this._requiresCallback;
            }
        }

        internal delegate void SharedDataChangedEventHandler(object sender, WritableSharedDataChangedEventArgs e);

        internal delegate void SharedDataChangeRequestEventHandler(object sender, WritableSharedDataChangeRequestEventArgs e);
    }
}

