namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public abstract class SnapIn : NamespaceSnapInBase
    {
        private ScopeNode _rootNode;

        protected SnapIn()
        {
        }

        internal override void Initialize()
        {
            base.Initialize();
            if (this._rootNode != null)
            {
                base._nodeSyncManager.AddNodes(new ScopeNode[] { this._rootNode }, 0);
            }
        }

        protected virtual bool OnShowInitializationWizard()
        {
            return true;
        }

        internal override void ProcessRequest(Request request)
        {
            if (request.RequestInfo is ShowInitializationWizardRequestInfo)
            {
                ShowInitializationWizardResponse response = new ShowInitializationWizardResponse();
                IRequestStatus requestStatus = request.RequestStatus;
                SyncStatus status2 = new SyncStatus(requestStatus);
                try
                {
                    response.AddSnapInToConsole = this.OnShowInitializationWizard();
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

        public ScopeNode RootNode
        {
            get
            {
                return this._rootNode;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (base.IsInitialized)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SnapInRootNodeInvalidSet));
                }
                if (value != this._rootNode)
                {
                    if (base.SnapInPlatform != null)
                    {
                        if (this._rootNode != null)
                        {
                            base._nodeSyncManager.RemoveNodes(new ScopeNode[] { this._rootNode });
                        }
                        this._rootNode = value;
                        base._nodeSyncManager.AddNodes(new ScopeNode[] { this._rootNode }, 0);
                    }
                    else
                    {
                        this._rootNode = value;
                    }
                }
            }
        }
    }
}

