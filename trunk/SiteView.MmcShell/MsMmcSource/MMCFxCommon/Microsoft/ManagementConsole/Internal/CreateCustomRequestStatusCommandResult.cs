namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class CreateCustomRequestStatusCommandResult : CommandResult
    {
        private IRequestStatus _requestStatus;

        public IRequestStatus RequestStatus
        {
            get
            {
                return this._requestStatus;
            }
            set
            {
                this._requestStatus = value;
            }
        }
    }
}

