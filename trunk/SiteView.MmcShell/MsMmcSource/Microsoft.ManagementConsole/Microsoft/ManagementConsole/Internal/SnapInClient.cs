namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole;
    using System;
    using System.Runtime.CompilerServices;
    using System.Security.Permissions;

    internal class SnapInClient : MarshalByRefObject, ISnapInClient, IMessageClient
    {
        private CreateViewHandler _onCreateView;
        private InitializedHandler _onInitialized;
        private ProcessNotificationHandler _onProcessNotification;
        private ProcessRequestHandler _onProcessRequest;
        private SnapInBase _snapInInstance;
        private ISnapInPlatform _snapInPlatform;

        internal SnapInClient()
        {
        }

        public void CreateSnapIn(string assemblyName, string typeName)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            this._snapInInstance = (SnapInBase) AppDomain.CurrentDomain.CreateInstanceAndUnwrap(assemblyName, typeName);
            this._snapInInstance.SnapInClient = this;
        }

        [SecurityPermission(SecurityAction.LinkDemand, Flags=SecurityPermissionFlag.Infrastructure)]
        public override object InitializeLifetimeService()
        {
            return null;
        }

        internal void InitializeTestSnapInPlatform(Delegate processCommandCallback)
        {
            this._snapInPlatform = new TestSnapInPlatform(processCommandCallback);
        }

        void IMessageClient.ProcessNotification(Notification notification)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            if (this._onProcessNotification != null)
            {
                this._onProcessNotification(notification);
            }
        }

        void IMessageClient.ProcessRequest(Request request)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            if (this._onProcessRequest != null)
            {
                this._onProcessRequest(request);
            }
        }

        IMessageClient ISnapInClient.CreateView(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            if (this._onCreateView != null)
            {
                return this._onCreateView(nodeId, componentId, viewDescriptionId, viewInstanceId);
            }
            return null;
        }

        void ISnapInClient.Initialize(ISnapInPlatform snapInPlatform)
        {
            SynchronizationContextCache.RestoreOriginalContext();
            this._snapInPlatform = snapInPlatform;
            if (this._onInitialized != null)
            {
                this._onInitialized();
            }
        }

        internal CreateViewHandler OnCreateView
        {
            set
            {
                this._onCreateView = value;
            }
        }

        internal InitializedHandler OnInitialized
        {
            set
            {
                this._onInitialized = value;
            }
        }

        internal ProcessNotificationHandler OnProcessNotification
        {
            set
            {
                this._onProcessNotification = value;
            }
        }

        internal ProcessRequestHandler OnProcessRequest
        {
            set
            {
                this._onProcessRequest = value;
            }
        }

        internal ISnapInPlatform SnapInPlatform
        {
            get
            {
                return this._snapInPlatform;
            }
        }

        internal delegate IMessageClient CreateViewHandler(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId);

        internal delegate void InitializedHandler();

        internal delegate void ProcessNotificationHandler(Notification notificition);

        internal delegate void ProcessRequestHandler(Request request);
    }
}

