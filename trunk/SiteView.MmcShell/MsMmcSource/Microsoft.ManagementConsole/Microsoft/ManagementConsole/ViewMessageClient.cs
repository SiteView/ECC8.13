namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.Remoting.Lifetime;
    using System.Security.Permissions;

    internal class ViewMessageClient : MarshalByRefObject, IMessageClient
    {
        private View _view;

        public ViewMessageClient(View view)
        {
            if (view == null)
            {
                throw new ArgumentNullException("view");
            }
            this._view = view;
        }

        [SecurityPermission(SecurityAction.LinkDemand, Flags=SecurityPermissionFlag.Infrastructure)]
        public override object InitializeLifetimeService()
        {
            ILease lease = (ILease) base.InitializeLifetimeService();
            if (lease.CurrentState == LeaseState.Initial)
            {
                lease.InitialLeaseTime = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectLeaseTime;
                lease.SponsorshipTimeout = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectSponsorshipTimeout;
                lease.RenewOnCallTime = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectRenewOnCallTime;
            }
            return lease;
        }

        public void ProcessNotification(Notification notification)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            this._view.ProcessNotification(notification);
        }

        public void ProcessRequest(Request request)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            this._view.ProcessRequest(request);
        }
    }
}

