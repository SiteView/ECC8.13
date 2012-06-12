namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Globalization;
    using System.Runtime.Remoting;
    using System.Runtime.Remoting.Lifetime;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class Status
    {
        private IRequestStatus _requestStatus;
        private static ClientSponsor _requestStatusSponsor = new ClientSponsor(GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectLeaseTime);
        private string _statusText;
        private string _title;
        private int _totalWork;
        private int _workProcessed;

        internal Status()
        {
            this._statusText = string.Empty;
            this._title = string.Empty;
        }

        internal Status(IRequestStatus requestStatus)
        {
            this._statusText = string.Empty;
            this._title = string.Empty;
            if (requestStatus == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.InternalStatusRequestStatusAlreadySet));
            }
            this._requestStatus = requestStatus;
            this.RegisterSponsor();
        }

        internal void Close()
        {
            try
            {
                if (this._requestStatus != null)
                {
                    ILease lifetimeService = (ILease) ((MarshalByRefObject) this._requestStatus).GetLifetimeService();
                    if (lifetimeService != null)
                    {
                        lifetimeService.Unregister(_requestStatusSponsor);
                    }
                }
            }
            catch (InvalidOperationException exception)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Verbose, 12, exception.Message);
            }
            catch (RemotingException exception2)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Verbose, 12, exception2.Message);
            }
            finally
            {
                this._requestStatus = null;
            }
        }

        public void Complete(string completionText, bool success)
        {
            this.InternalComplete(completionText, success);
        }

        ~Status()
        {
            this.Close();
        }

        internal void Initialize(IRequestStatus requestStatus)
        {
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus");
            }
            if (this._requestStatus != null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.InternalStatusRequestStatusAlreadySet));
            }
            this._requestStatus = requestStatus;
            this._requestStatus.Title = this._title;
            this._requestStatus.ReportProgress(this._workProcessed, this._totalWork, this._statusText);
            this.RegisterSponsor();
        }

        internal virtual void InternalComplete(string completionText, bool success)
        {
            if (this._requestStatus == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.Resources.GetString(Microsoft.ManagementConsole.Internal.Strings.MicrosoftManagementConsoleInternalStatusRequestNotStarted, CultureInfo.CurrentUICulture));
            }
            this._requestStatus.SetCompletionText(completionText, success);
            if (this._requestStatus.RequestState != RequestState.Synchronous)
            {
                this._requestStatus.RequestState = RequestState.Complete;
                this._requestStatus = null;
            }
        }

        private void RegisterSponsor()
        {
            ILease lifetimeService = (ILease) ((MarshalByRefObject) this._requestStatus).GetLifetimeService();
            if (lifetimeService != null)
            {
                lifetimeService.Register(_requestStatusSponsor);
            }
        }

        public void ReportProgress(int workProcessed, int totalWork, string statusText)
        {
            if (this._requestStatus != null)
            {
                this._requestStatus.ReportProgress(workProcessed, totalWork, statusText);
            }
            this._workProcessed = workProcessed;
            this._totalWork = totalWork;
            this._statusText = statusText;
        }

        internal IRequestStatus RequestStatus
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

        public string Title
        {
            get
            {
                if (this._requestStatus == null)
                {
                    return this._title;
                }
                return this._requestStatus.Title;
            }
            set
            {
                if (this._requestStatus != null)
                {
                    this._requestStatus.Title = value;
                    this._title = value;
                }
                else
                {
                    this._title = value;
                }
            }
        }
    }
}

