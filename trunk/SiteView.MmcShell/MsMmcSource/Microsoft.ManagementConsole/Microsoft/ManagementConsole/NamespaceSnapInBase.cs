namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Advanced;
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;
    using System.Drawing;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class NamespaceSnapInBase : SnapInBase
    {
        private Microsoft.ManagementConsole.Advanced.Console _console = new Microsoft.ManagementConsole.Advanced.Console();
        private SnapInImageList _largeImages = new SnapInImageList();
        internal NodeSyncManager _nodeSyncManager = new NodeSyncManager();
        private AuxiliarySelectionDataCollection _runningTaskSelectionDatas;
        private SnapInImageList _smallImages = new SnapInImageList();
        private SnapInData _snapInData = new SnapInData();

        internal NamespaceSnapInBase()
        {
            this._smallImages.ImageList.ImageSize = new Size(0x10, 0x10);
            this._largeImages.ImageList.ImageSize = new Size(0x20, 0x20);
            this._smallImages.Changed += new EventHandler(this.OnPropertyChanged);
            this._largeImages.Changed += new EventHandler(this.OnPropertyChanged);
            this._snapInData.SmallImages = this._smallImages.ImageList;
            this._snapInData.LargeImages = this._largeImages.ImageList;
        }

        internal override IMessageClient CreateView(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId)
        {
            return this._nodeSyncManager.CreateView(nodeId, componentId, viewDescriptionId, viewInstanceId);
        }

        internal void LoadCustomData(IRequestStatus requestStatus, byte[] dataBlob)
        {
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus", Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ScopeNodeRequestInterfaceNull));
            }
            if (dataBlob != null)
            {
                this.OnLoadCustomData(new AsyncStatus(requestStatus), dataBlob);
            }
        }

        protected virtual void OnLoadCustomData(AsyncStatus status, byte[] persistenceData)
        {
        }

        private void OnPropertyChanged(object sender, EventArgs e)
        {
            this.SynchronizeMmc();
        }

        protected virtual byte[] OnSaveCustomData(SyncStatus status)
        {
            return null;
        }

        internal override void PreInitialize()
        {
            base.PreInitialize();
            if (base.SnapInPlatform == null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.InternalNamespaceSnapInBasePreInitializeNullPlatform));
            }
            this._nodeSyncManager.Initialize(base.SnapInPlatform);
            this._console.Initialize(base.SnapInPlatform);
            this.SynchronizeMmc();
        }

        internal override void ProcessNotification(Notification notif)
        {
            DeactivateNodeNotification notification = notif as DeactivateNodeNotification;
            if (notification != null)
            {
                this._nodeSyncManager.DeactivateNode(notification.ScopeNodeId);
            }
            else
            {
                base.ProcessNotification(notif);
            }
        }

        internal override void ProcessRequest(Request request)
        {
            if (request == null)
            {
                throw new ArgumentNullException("request");
            }
            if (request.RequestInfo is NodeRequestInfo)
            {
                this._nodeSyncManager.ProcessRequest((NodeRequestInfo) request.RequestInfo, request.RequestStatus);
            }
            else if (request.RequestInfo is LoadDataRequestInfo)
            {
                this.LoadCustomData(request.RequestStatus, (request.RequestInfo as LoadDataRequestInfo).GetDataBlob());
            }
            else if (request.RequestInfo is SaveDataRequestInfo)
            {
                SaveDataRequestInfo requestInfo = request.RequestInfo as SaveDataRequestInfo;
                this.SaveCustomData(request.RequestStatus, requestInfo.ClearModified);
            }
            else
            {
                base.ProcessRequest(request);
            }
        }

        internal void SaveCustomData(IRequestStatus requestStatus, bool clearModified)
        {
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus", Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ScopeNodeRequestInterfaceNull));
            }
            byte[] data = null;
            if (this.IsModified)
            {
                data = this.OnSaveCustomData(new SyncStatus(requestStatus));
                if (data == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonPersistenceNotSerializable));
                }
            }
            PersistenceCompletedResponse response = new PersistenceCompletedResponse();
            response.SetDataBlob(data);
            requestStatus.ProcessResponse(response);
            if (clearModified)
            {
                this.IsModified = false;
            }
        }

        internal void SynchronizeMmc()
        {
            if (base.SnapInPlatform != null)
            {
                UpdateSnapInCommand command = new UpdateSnapInCommand();
                command.SnapInData = this._snapInData;
                base.SnapInPlatform.ProcessCommand(command);
            }
        }

        public Microsoft.ManagementConsole.Advanced.Console Console
        {
            get
            {
                return this._console;
            }
        }

        public bool IsModified
        {
            get
            {
                return this._snapInData.IsModified;
            }
            set
            {
                if (value != this._snapInData.IsModified)
                {
                    this._snapInData.IsModified = value;
                    this.SynchronizeMmc();
                }
            }
        }

        public SnapInImageList LargeImages
        {
            get
            {
                return this._largeImages;
            }
        }

        internal AuxiliarySelectionDataCollection RunningTaskSelectionDatas
        {
            get
            {
                if (this._runningTaskSelectionDatas == null)
                {
                    this._runningTaskSelectionDatas = new AuxiliarySelectionDataCollection();
                }
                return this._runningTaskSelectionDatas;
            }
        }

        public SnapInImageList SmallImages
        {
            get
            {
                return this._smallImages;
            }
        }
    }
}

