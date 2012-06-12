namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Globalization;

    public sealed class CustomStatus : Status
    {
        private ScopeNode _owner;

        internal void AttachRequestStatus()
        {
            if (((base.RequestStatus == null) && (this._owner.SnapIn.SnapInPlatform != null)) && (this._owner.SnapIn._nodeSyncManager.GetNode(this._owner.Id) != null))
            {
                CreateCustomRequestStatusCommand command = new CreateCustomRequestStatusCommand();
                command.ScopeNodeId = this._owner.Id;
                CreateCustomRequestStatusCommandResult result = this._owner.SnapIn.SnapInPlatform.ProcessCommand(command) as CreateCustomRequestStatusCommandResult;
                base.Initialize(result.RequestStatus);
            }
        }

        internal void DetachRequestStatus()
        {
            base.RequestStatus = null;
        }

        internal override void InternalComplete(string completionText, bool success)
        {
            if (base.RequestStatus != null)
            {
                base.InternalComplete(completionText, success);
            }
            if (this._owner != null)
            {
                this._owner.RemoveCustomStatus(this);
                this.DetachRequestStatus();
                this._owner = null;
            }
        }

        public void Start(ScopeNode owner)
        {
            if (owner == null)
            {
                throw new ArgumentNullException("owner");
            }
            if (this._owner != null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.Resources.GetString(Microsoft.ManagementConsole.Internal.Strings.MicrosoftManagementConsoleCustomStatusRequestAlreadyStarted, CultureInfo.CurrentUICulture));
            }
            NamespaceSnapInBase snapInInstance = SnapInBase.SnapInInstance as NamespaceSnapInBase;
            if ((snapInInstance == null) || (owner.SnapIn != snapInInstance))
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetWrongThread));
            }
            this._owner = owner;
            this._owner.AddCustomStatus(this);
            try
            {
                this.AttachRequestStatus();
            }
            catch
            {
                this.InternalComplete(string.Empty, false);
                throw;
            }
        }
    }
}

