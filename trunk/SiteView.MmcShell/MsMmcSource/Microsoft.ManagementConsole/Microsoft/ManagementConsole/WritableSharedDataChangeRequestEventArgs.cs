namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    internal class WritableSharedDataChangeRequestEventArgs : EventArgs
    {
        private byte[] _newValue;
        private WritableSharedDataItem _publishedDataItem;
        private IRequestStatus _requestStatus;

        internal WritableSharedDataChangeRequestEventArgs(byte[] newValue, IRequestStatus requestStatus, WritableSharedDataItem publishedDataItem)
        {
            this._newValue = newValue;
            this._requestStatus = requestStatus;
            this._publishedDataItem = publishedDataItem;
        }

        internal byte[] GetNewValue()
        {
            return this._newValue;
        }

        internal IRequestStatus RequestStatus
        {
            get
            {
                return this._requestStatus;
            }
        }

        internal WritableSharedDataItem SharedDataItem
        {
            get
            {
                return this._publishedDataItem;
            }
        }
    }
}

