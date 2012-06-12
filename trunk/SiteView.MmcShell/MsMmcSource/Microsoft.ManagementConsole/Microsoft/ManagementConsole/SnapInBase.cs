namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Security.Permissions;
    using System.Threading;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class SnapInBase : ISynchronizeInvoke
    {
        private AsyncDelegateQueue _delegateQueue = new AsyncDelegateQueue();
        private Dictionary<int, SharedData> _externalDataObjects = new Dictionary<int, SharedData>();
        private bool _isInitialized;
        private Hashtable _mdiSharedData;
        private PropertySheetManager _sheetManager = new PropertySheetManager();
        private Microsoft.ManagementConsole.Internal.SnapInClient _snapInClient;
        private int _snapInId = -1;
        private object _tag;
        private SnapInUIThreadTable _uiThreadTable = new SnapInUIThreadTable();
        internal const string SnapInReference = "SnapInReference";

        internal SnapInBase()
        {
            this._snapInId = AppDomain.CurrentDomain.Id;
            LocalDataStoreSlot namedDataSlot = Thread.GetNamedDataSlot("SnapInReference");
            if (Thread.GetData(namedDataSlot) != null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SnapInBaseSingleInstance));
            }
            Thread.SetData(namedDataSlot, this);
        }

        internal void AddSharedData(SharedData sharedData)
        {
            this._externalDataObjects.Add(sharedData.DataObjectId, sharedData);
            ChangeNotificationSubscriptionCommand command = new ChangeNotificationSubscriptionCommand();
            command.DataObjectId = sharedData.DataObjectId;
            command.IsActive = true;
            this.SnapInClient.SnapInPlatform.ProcessCommand(command);
        }

        public IAsyncResult BeginInvoke(Delegate method)
        {
            return this._delegateQueue.BeginInvoke(method, new object[0]);
        }

        [HostProtection(SecurityAction.LinkDemand, Synchronization=true, ExternalThreading=true)]
        public IAsyncResult BeginInvoke(Delegate method, object[] args)
        {
            return this._delegateQueue.BeginInvoke(method, args);
        }

        internal virtual IMessageClient CreateView(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId)
        {
            return null;
        }

        public object EndInvoke(IAsyncResult result)
        {
            return this._delegateQueue.EndInvoke(result);
        }

        internal object GetMdiSharedData(int componentId)
        {
            if ((this._mdiSharedData != null) && this._mdiSharedData.ContainsKey(componentId))
            {
                return this._mdiSharedData[componentId];
            }
            return null;
        }

        internal virtual void Initialize()
        {
        }

        private void Initialized()
        {
            UpdateSnapInConfigCommand command = new UpdateSnapInConfigCommand();
            command.WaitDialogDelay = GlobalConfiguration.SnapInHostingOptions.WaitDialogDelay;
            this.SnapInPlatform.ProcessCommand(command);
            this._uiThreadTable.Initialize(this.SnapInPlatform);
            this.PreInitialize();
            this.Initialize();
            this.PostInitialize();
            this._delegateQueue.Initialize(this.SnapInPlatform);
            this._isInitialized = true;
        }

        public object Invoke(Delegate method)
        {
            return this._delegateQueue.Invoke(method, new object[0]);
        }

        public object Invoke(Delegate method, object[] args)
        {
            return this._delegateQueue.Invoke(method, args);
        }

        protected virtual void OnInitialize()
        {
        }

        protected virtual void OnShutdown(AsyncStatus status)
        {
        }

        internal virtual void PostInitialize()
        {
            this.OnInitialize();
        }

        internal virtual void PreInitialize()
        {
        }

        internal virtual void ProcessNotification(Notification notification)
        {
            if (notification is BeginInvokeNotification)
            {
                BeginInvokeNotification notification2 = notification as BeginInvokeNotification;
                this._delegateQueue.Notify(notification2);
            }
            else if (notification is PropertyPageNotification)
            {
                this._sheetManager.ProcessNotificationMessage((PropertyPageNotification) notification);
            }
            else if (notification is DataChangeNotification)
            {
                DataChangeNotification notification3 = notification as DataChangeNotification;
                SharedData data = null;
                if (this._externalDataObjects.TryGetValue(notification3.DataObjectId, out data))
                {
                    data.ProcessChangeNotification(notification3);
                }
            }
            else
            {
                if (!(notification is ComponentAbandonedNotification))
                {
                    throw new NotImplementedException();
                }
                ComponentAbandonedNotification notification4 = notification as ComponentAbandonedNotification;
                this.RemoveMdiSharedData(notification4.Id);
            }
        }

        internal virtual void ProcessRequest(Request request)
        {
            if (request.RequestInfo is ShutdownRequestInfo)
            {
                AsyncStatus status = new AsyncStatus(request.RequestStatus);
                this.OnShutdown(status);
            }
            else
            {
                if (!(request.RequestInfo is PropertyPageMessageRequestInfo))
                {
                    throw new NotImplementedException();
                }
                this._sheetManager.ProcessRequestMessage((PropertyPageMessageRequestInfo) request.RequestInfo, request.RequestStatus);
            }
        }

        public void RegisterCurrentThreadForUI()
        {
            this._uiThreadTable.RegisterCurrentThread(true);
        }

        internal void RemoveMdiSharedData(int componentId)
        {
            if (this._mdiSharedData != null)
            {
                this._mdiSharedData.Remove(componentId);
            }
        }

        internal void RemoveSharedData(SharedData sharedData)
        {
            this._externalDataObjects.Remove(sharedData.DataObjectId);
            ChangeNotificationSubscriptionCommand command = new ChangeNotificationSubscriptionCommand();
            command.DataObjectId = sharedData.DataObjectId;
            command.IsActive = false;
            this.SnapInClient.SnapInPlatform.ProcessCommand(command);
        }

        internal void SetMdiSharedData(int componentId, object value)
        {
            if (this._mdiSharedData == null)
            {
                this._mdiSharedData = new Hashtable();
            }
            this._mdiSharedData[componentId] = value;
        }

        public void ShowHelpTopic(string helpTopic)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(helpTopic, "helpTopic", true);
            ISnapInPlatform snapInPlatform = this.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
            }
            ShowHelpTopicCommand command = new ShowHelpTopicCommand();
            command.HelpTopic = helpTopic;
            snapInPlatform.ProcessCommand(command);
        }

        public void UnregisterCurrentThreadForUI()
        {
            this._uiThreadTable.RegisterCurrentThread(false);
        }

        protected internal int Id
        {
            get
            {
                return this._snapInId;
            }
        }

        public bool InvokeRequired
        {
            get
            {
                return this._delegateQueue.InvokeRequired;
            }
        }

        internal bool IsInitialized
        {
            get
            {
                return this._isInitialized;
            }
        }

        internal PropertySheetManager SheetManager
        {
            get
            {
                if (this._sheetManager == null)
                {
                    return null;
                }
                return this._sheetManager;
            }
        }

        internal Microsoft.ManagementConsole.Internal.SnapInClient SnapInClient
        {
            get
            {
                return this._snapInClient;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._snapInClient = value;
                this._snapInClient.OnProcessNotification = new Microsoft.ManagementConsole.Internal.SnapInClient.ProcessNotificationHandler(this.ProcessNotification);
                this._snapInClient.OnProcessRequest = new Microsoft.ManagementConsole.Internal.SnapInClient.ProcessRequestHandler(this.ProcessRequest);
                this._snapInClient.OnInitialized = new Microsoft.ManagementConsole.Internal.SnapInClient.InitializedHandler(this.Initialized);
                this._snapInClient.OnCreateView = new Microsoft.ManagementConsole.Internal.SnapInClient.CreateViewHandler(this.CreateView);
            }
        }

        internal static SnapInBase SnapInInstance
        {
            get
            {
                SnapInBase data = null;
                LocalDataStoreSlot namedDataSlot = Thread.GetNamedDataSlot("SnapInReference");
                if (namedDataSlot != null)
                {
                    data = Thread.GetData(namedDataSlot) as SnapInBase;
                }
                return data;
            }
        }

        internal ISnapInPlatform SnapInPlatform
        {
            get
            {
                if (this._snapInClient == null)
                {
                    return null;
                }
                return this._snapInClient.SnapInPlatform;
            }
        }

        public object Tag
        {
            get
            {
                return this._tag;
            }
            set
            {
                this._tag = value;
            }
        }
    }
}

