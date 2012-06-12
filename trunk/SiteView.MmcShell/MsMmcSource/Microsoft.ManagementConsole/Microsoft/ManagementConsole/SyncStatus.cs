namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class SyncStatus : Status
    {
        internal SyncStatus(IRequestStatus requestStatus) : base(requestStatus)
        {
        }

        public bool CanCancel
        {
            get
            {
                return base.RequestStatus.CanCancel;
            }
            set
            {
                base.RequestStatus.CanCancel = value;
            }
        }

        public bool IsCancelSignaled
        {
            get
            {
                return base.RequestStatus.IsCancelSignaled;
            }
        }
    }
}

