namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole;
    using Microsoft.ManagementConsole.Internal;
    using System;

    public abstract class NamespaceExtension : NamespaceSnapInBase
    {
        private PrimaryScopeNode _primaryNode = new PrimaryScopeNode();

        protected NamespaceExtension()
        {
            this._primaryNode.SharedData.Changed += new SharedData.SharedDataChangedEventHandler(this.SharedDataChanged);
        }

        internal override void Initialize()
        {
            base.Initialize();
            this._primaryNode.SharedData.SetSnapInPlatform(base.SnapInClient.SnapInPlatform);
        }

        protected virtual string OnRetrievePersistenceKey()
        {
            return null;
        }

        protected virtual void OnSharedDataChanged(SharedDataItem item)
        {
        }

        internal override void PostInitialize()
        {
        }

        internal override void ProcessNotification(Notification notification)
        {
            if (notification is NamespaceExtensionInitNotification)
            {
                NamespaceExtensionInitNotification notification2 = notification as NamespaceExtensionInitNotification;
                this._primaryNode.Initialize(base._nodeSyncManager, notification2.PrimaryNodeType);
                base.AddSharedData(this._primaryNode.SharedData);
                this.OnInitialize();
            }
            else
            {
                base.ProcessNotification(notification);
            }
        }

        internal override void ProcessRequest(Request request)
        {
            if (request == null)
            {
                throw new ArgumentNullException("request");
            }
            if (request.RequestInfo is PersistenceKeyRequestInfo)
            {
                PersistenceKeyRetrievalCompletedResponse response = new PersistenceKeyRetrievalCompletedResponse();
                IRequestStatus requestStatus = request.RequestStatus;
                SyncStatus status2 = new SyncStatus(requestStatus);
                try
                {
                    string str = this.OnRetrievePersistenceKey();
                    response.PersistenceKey = str;
                    requestStatus.ProcessResponse(response);
                }
                finally
                {
                    status2.Close();
                }
            }
            else
            {
                base.ProcessRequest(request);
            }
        }

        private void SharedDataChanged(object sender, SharedDataChangedEventArgs e)
        {
            this.OnSharedDataChanged(e.SharedDataItem);
        }

        public PrimaryScopeNode PrimaryNode
        {
            get
            {
                return this._primaryNode;
            }
        }
    }
}

