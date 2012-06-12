namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class AsyncStatus : Status
    {
        internal AsyncStatus(IRequestStatus requestStatus) : base(requestStatus)
        {
        }

        public void EnableManualCompletion()
        {
            base.RequestStatus.RequestState = RequestState.Pending;
        }
    }
}

