namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class Request : MarshalByRefObject
    {
        private Microsoft.ManagementConsole.Internal.RequestInfo _requestInfo;
        private IRequestStatus _requestStatus;

        public Request(Microsoft.ManagementConsole.Internal.RequestInfo requestInfo, IRequestStatus requestStatus)
        {
            this._requestInfo = requestInfo;
            this._requestStatus = requestStatus;
        }

        public Microsoft.ManagementConsole.Internal.RequestInfo RequestInfo
        {
            get
            {
                return this._requestInfo;
            }
        }

        public IRequestStatus RequestStatus
        {
            get
            {
                return this._requestStatus;
            }
        }
    }
}

