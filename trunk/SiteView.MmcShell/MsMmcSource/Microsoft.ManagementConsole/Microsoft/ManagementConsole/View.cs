namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Diagnostics;
    using System.Globalization;

    public abstract class View
    {
        private ActionsPaneItemCollection _actionsPaneItems;
        private AuxiliarySelectionDataCollection _clipboardSelectionDatas;
        private int _componentId = -1;
        private string _descriptionBarText = string.Empty;
        private bool _initialized;
        private bool _isModified;
        private ViewMessageClient _messageClient;
        private ActionsPaneItemCollection _modeActionsPaneItems;
        private Microsoft.ManagementConsole.ScopeNode _scopeNode;
        private Microsoft.ManagementConsole.SelectionData _selectionData;
        private bool _shutdown;
        private NamespaceSnapInBase _snapIn = (SnapInBase.SnapInInstance as NamespaceSnapInBase);
        private Microsoft.ManagementConsole.ViewDescription _viewDescription;
        private int _viewInstanceId = -1;
        private bool _visible;

        internal View()
        {
            if (this._snapIn == null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonWrongThread, new object[] { "View" }));
            }
            this._messageClient = new ViewMessageClient(this);
        }

        internal void BatchSelectionDataUpdates(bool begin)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "BatchSelectionDataUpdates");
            }
            BatchSelectionDataUpdatesCommand command = new BatchSelectionDataUpdatesCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.Begin = begin;
            snapInPlatform.ProcessCommand(command);
        }

        private void ComparePropertySheetSelectionObjects(int currentSelectionId, int selectionIdToCompare, IRequestStatus requestStatus)
        {
            CompareSelectionObjectsResponse response = new CompareSelectionObjectsResponse();
            response.Result = false;
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus");
            }
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                if (((this.SelectionData.SelectionCardinality != SelectionCardinality.None) && (currentSelectionId == this.SelectionData.Id)) && (this.SelectionData.SelectionObject != null))
                {
                    response.Result = SnapInBase.SnapInInstance.SheetManager.ComparePropertySheetSelectionObjects(this.SelectionData.SelectionObject, selectionIdToCompare);
                }
                requestStatus.ProcessResponse(response);
            }
            finally
            {
                status.Close();
            }
        }

        private SharedDataObjectUpdate CreateSharedDataObjectUpdate(WritableSharedDataItem[] addedItems, WritableSharedDataItem[] modifiedItems, WritableSharedDataItem[] removedItems)
        {
            SharedDataObjectUpdate update = new SharedDataObjectUpdate();
            ArrayList dataUpdate = new ArrayList();
            ArrayList formats = new ArrayList();
            ArrayList list3 = new ArrayList();
            this.ParseSharedDataItems(addedItems, formats, dataUpdate);
            update.SetAddedFormats((DataFormatConfiguration[]) formats.ToArray(typeof(DataFormatConfiguration)));
            this.ParseSharedDataItems(modifiedItems, list3, dataUpdate);
            update.SetChangedFormats((DataFormatConfiguration[]) list3.ToArray(typeof(DataFormatConfiguration)));
            update.SetUpdatedData((ClipboardData[]) dataUpdate.ToArray(typeof(ClipboardData)));
            ArrayList list4 = new ArrayList();
            foreach (WritableSharedDataItem item in removedItems)
            {
                list4.Add(item.ClipboardFormatId);
            }
            update.SetRemovedClipboardFormatIds((string[]) list4.ToArray(typeof(string)));
            return update;
        }

        private void DoAction(int actionId, bool selectionDependent, int selectionId, IRequestStatus requestStatus)
        {
            ActionsPaneItem itemById = null;
            bool flag = false;
            if (selectionDependent)
            {
                itemById = this.SelectionData.ActionsPaneItems.GetItemById(actionId);
                if (itemById == null)
                {
                    itemById = this.SelectionData.ActionsPaneHelpItems.GetItemById(actionId);
                }
            }
            else
            {
                itemById = this.ActionsPaneItems.GetItemById(actionId);
                if (itemById == null)
                {
                    itemById = this.ModeActionsPaneItems.GetItemById(actionId);
                    flag = true;
                }
            }
            ActionBase base2 = itemById as ActionBase;
            if (base2 == null)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "The request action with id {0} does not exist for view {1}.", new object[] { actionId.ToString(CultureInfo.CurrentUICulture), this._viewInstanceId });
            }
            else if (selectionDependent && ((this.SelectionData.SelectionCardinality == SelectionCardinality.None) || (selectionId != this.SelectionData.Id)))
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Action {0} in view {1} selection id {2} ignored since selection has changed.", new object[] { actionId, this._viewInstanceId, selectionId });
            }
            else
            {
                SyncAction action = base2 as SyncAction;
                if (action != null)
                {
                    SyncStatus status = new SyncStatus(requestStatus);
                    action.RaiseTriggeredEvent(this, status);
                    if (selectionDependent)
                    {
                        this.OnSyncSelectionAction(action, status);
                    }
                    else if (flag)
                    {
                        this.OnSyncModeAction(action, status);
                    }
                    else
                    {
                        this.OnSyncAction(action, status);
                    }
                }
                else
                {
                    Action action2 = (Action) base2;
                    AsyncStatus status2 = new AsyncStatus(requestStatus);
                    action2.RaiseTriggeredEvent(this, status2);
                    if (selectionDependent)
                    {
                        this.OnSelectionAction(action2, status2);
                    }
                    else if (flag)
                    {
                        this.OnModeAction(action2, status2);
                    }
                    else
                    {
                        this.OnAction(action2, status2);
                    }
                }
            }
        }

        private void DoVerb(RequestInfo requestInfo, IRequestStatus requestStatus)
        {
            if (requestInfo is CutOrMoveViewSelectionRequestInfo)
            {
                CutOrMoveViewSelectionRequestInfo info = (CutOrMoveViewSelectionRequestInfo) requestInfo;
                AuxiliarySelectionData data = this.ClipboardSelectionDatas[info.SelectionId];
                if (data != null)
                {
                    this.OnCut(data.SelectionObject, new AsyncStatus(requestStatus));
                }
                else
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request CutOrMove in view {0} ignore since selection id {1} could not be found.", new object[] { this._viewInstanceId, info.SelectionId });
                }
            }
            else
            {
                int selectionId = ((ViewSelectionRequestInfo) requestInfo).SelectionId;
                if ((this.SelectionData.SelectionCardinality == SelectionCardinality.None) || (selectionId != this.SelectionData.Id))
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request {0} in view {1} selection id {2} ignored since selection has changed.", new object[] { requestInfo.GetType().FullName, this._viewInstanceId, selectionId });
                }
                else if (requestInfo is DeleteViewSelectionRequestInfo)
                {
                    this.OnDelete(new SyncStatus(requestStatus));
                }
                else if (requestInfo is RefreshViewSelectionRequestInfo)
                {
                    this.OnRefresh(new AsyncStatus(requestStatus));
                }
                else if (requestInfo is PrintViewSelectionRequestInfo)
                {
                    this.OnPrint(new SyncStatus(requestStatus));
                }
                else if (requestInfo is RenameViewSelectionRequestInfo)
                {
                    this.OnRename(((RenameViewSelectionRequestInfo) requestInfo).NewDisplayName, new SyncStatus(requestStatus));
                }
                else if (requestInfo is PasteViewSelectionRequestInfo)
                {
                    PasteViewSelectionRequestInfo info2 = (PasteViewSelectionRequestInfo) requestInfo;
                    SharedData sharedData = new SharedData(info2.DataObjectId);
                    this.ScopeNode.SnapIn.AddSharedData(sharedData);
                    sharedData.SetSnapInPlatform(this.ScopeNode.SnapIn.SnapInClient.SnapInPlatform);
                    PasteResponse response = new PasteResponse();
                    try
                    {
                        response.AcceptPaste = this.OnPaste(sharedData, (Microsoft.ManagementConsole.DragAndDropVerb) info2.PasteType, new SyncStatus(requestStatus));
                        requestStatus.ProcessResponse(response);
                    }
                    finally
                    {
                        this.ScopeNode.SnapIn.RemoveSharedData(sharedData);
                    }
                }
            }
        }

        internal void GetPropertyPages(int sheetId, long selectionId, IRequestStatus requestStatus)
        {
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus");
            }
            PropertyPageCollection propertyPageCollection = new PropertyPageCollection();
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                if ((this.SelectionData.SelectionCardinality == SelectionCardinality.None) || (selectionId != this.SelectionData.Id))
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request for pages for sheet {0} in view {1} selection id {2} ignored since selection has changed.", new object[] { sheetId, this._viewInstanceId, selectionId });
                    requestStatus.ProcessResponse(new PropertyPagesResponse());
                    return;
                }
                this.OnAddPropertyPages(propertyPageCollection);
                PropertyPagesResponse response = new PropertyPagesResponse();
                response.SetPropertyPages(propertyPageCollection.ToPropertyPageInfoArray());
                requestStatus.ProcessResponse(response);
            }
            finally
            {
                status.Close();
            }
            SnapInBase.SnapInInstance.SheetManager.CreatePropertySheet(sheetId, propertyPageCollection, new AuxiliarySelectionData(this.SelectionData));
        }

        internal void GetSharedData(string clipboardFormatId, int selectionId, IRequestStatus requestStatus)
        {
            WritableSharedData sharedData = null;
            object selectionObject = null;
            if ((this.SelectionData.SelectionCardinality == SelectionCardinality.None) || (selectionId != this.SelectionData.Id))
            {
                AuxiliarySelectionData data2 = this.ClipboardSelectionDatas[selectionId];
                if (data2 == null)
                {
                    data2 = this.SnapIn.SheetManager.ActiveViewPropertySheetSelectionDatas[selectionId];
                }
                if (data2 == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request for getting data format {0} in view {1} selection id {2} could not be handled.", new object[] { clipboardFormatId, this._viewInstanceId, selectionId });
                    return;
                }
                sharedData = data2.SharedData;
                selectionObject = data2.SelectionObject;
            }
            else
            {
                sharedData = this.SelectionData.SharedData;
                selectionObject = this.SelectionData.SelectionObject;
            }
            WritableSharedDataItem item = sharedData.GetItem(clipboardFormatId);
            if (item == null)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "The requested data format {0} is no longer available on the current selection in view {1}.", new object[] { clipboardFormatId, this._viewInstanceId });
            }
            else
            {
                SyncStatus status = new SyncStatus(requestStatus);
                byte[] buffer = this.OnGetSharedData(selectionObject, item, status);
                ClipboardData data3 = new ClipboardData();
                data3.ClipboardFormatId = item.ClipboardFormatId;
                data3.SetValue(buffer);
                ReadSharedDataResponse response = new ReadSharedDataResponse();
                response.RequestedClipboardData = data3;
                requestStatus.ProcessResponse(response);
            }
        }

        private void HandleHideNotification()
        {
            this._visible = false;
            this.OnHide();
        }

        private void HandleInitializationRequest(IRequestStatus requestStatus)
        {
            this._initialized = true;
            if (this._descriptionBarText != string.Empty)
            {
                this.SynchronizeDescriptionBarText();
            }
            if ((this._actionsPaneItems != null) && (this._actionsPaneItems.Count > 0))
            {
                this.SynchronizeGlobalActions();
            }
            if ((this._modeActionsPaneItems != null) && (this._modeActionsPaneItems.Count > 0))
            {
                this.SynchronizeModeActions();
            }
            if (this._selectionData != null)
            {
                this._selectionData.PerformInitialSynchronization();
            }
            if (this._isModified)
            {
                this.SynchronizeModifiedState();
            }
            this.InternalInitialize();
            this.OnInitialize(new AsyncStatus(requestStatus));
        }

        private void HandleKeepAliveRequest(int selectionId, bool keepAlive, KeepAlivePurpose purpose, IRequestStatus requestStatus)
        {
            AuxiliarySelectionDataCollection clipboardSelectionDatas = null;
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                if (purpose == KeepAlivePurpose.Clipboard)
                {
                    clipboardSelectionDatas = this.ClipboardSelectionDatas;
                }
                else if (purpose == KeepAlivePurpose.RunningTask)
                {
                    clipboardSelectionDatas = this._snapIn.RunningTaskSelectionDatas;
                }
                if (clipboardSelectionDatas != null)
                {
                    if (keepAlive)
                    {
                        if (this.SelectionData.Id == selectionId)
                        {
                            clipboardSelectionDatas[selectionId] = new AuxiliarySelectionData(this.SelectionData);
                        }
                        else
                        {
                            TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request Keep Alive {0} in view {1} selection id {2} ignored since selection has changed.", new object[] { keepAlive, this._viewInstanceId, selectionId });
                        }
                    }
                    else
                    {
                        clipboardSelectionDatas.Remove(selectionId);
                    }
                }
            }
            finally
            {
                status.Close();
            }
        }

        internal void HandleLoadViewDataRequest(IRequestStatus requestStatus, byte[] dataBlob)
        {
            if (dataBlob != null)
            {
                this.OnLoadCustomData(new AsyncStatus(requestStatus), dataBlob);
            }
        }

        internal void HandleSaveViewDataRequest(IRequestStatus requestStatus, bool clearModified)
        {
            byte[] data = null;
            if (this.IsModified)
            {
                data = this.OnSaveCustomData(new SyncStatus(requestStatus));
                if (data == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 12, "Snap-in view failed to return a non-null byte[] of serialized data.");
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonPersistenceNotSerializable));
                }
            }
            SaveViewDataResponse response = new SaveViewDataResponse();
            response.SetDataBlob(data);
            requestStatus.ProcessResponse(response);
            if (clearModified)
            {
                this.IsModified = false;
            }
        }

        private void HandleShowNotification()
        {
            this._visible = true;
            this.OnShow();
        }

        private void HandleShutdownRequest(IRequestStatus requestStatus)
        {
            this.OnShutdown(new SyncStatus(requestStatus));
            this.InternalShutdown();
            this._shutdown = true;
            this._scopeNode.CurrentSelectionDatas.Remove(this);
        }

        internal void Initialize(Microsoft.ManagementConsole.ScopeNode scopeNode, int componentId, int viewInstanceId, Microsoft.ManagementConsole.ViewDescription viewDescription)
        {
            if (scopeNode == null)
            {
                throw new ArgumentNullException("scopeNode");
            }
            if (viewDescription == null)
            {
                throw new ArgumentNullException("viewDescription");
            }
            this._componentId = componentId;
            this._scopeNode = scopeNode;
            this._viewInstanceId = viewInstanceId;
            this._viewDescription = viewDescription;
        }

        internal virtual void InternalInitialize()
        {
        }

        internal virtual void InternalShutdown()
        {
        }

        protected virtual void OnAction(Action action, AsyncStatus status)
        {
        }

        protected internal virtual void OnAddPropertyPages(PropertyPageCollection propertyPageCollection)
        {
        }

        protected virtual void OnCut(object selectionObject, AsyncStatus status)
        {
        }

        protected virtual void OnDelete(SyncStatus status)
        {
        }

        protected virtual byte[] OnGetSharedData(object selectionObject, WritableSharedDataItem item, SyncStatus status)
        {
            return null;
        }

        private void OnGlobalActionsChanged(object source, ActionsPaneItemCollectionEventArgs e)
        {
            this.ThrowIfShutdown("OnGlobalActionsChanged");
            if (this.Initialized)
            {
                this.SynchronizeGlobalActions();
            }
        }

        protected virtual void OnHide()
        {
        }

        protected virtual void OnInitialize(AsyncStatus status)
        {
        }

        protected virtual void OnLoadCustomData(AsyncStatus status, byte[] customData)
        {
        }

        protected virtual void OnModeAction(Action action, AsyncStatus status)
        {
        }

        private void OnModeActionsChanged(object source, ActionsPaneItemCollectionEventArgs e)
        {
            this.ThrowIfShutdown("OnModeActionsChanged");
            if (this.Initialized)
            {
                this.SynchronizeModeActions();
            }
        }

        protected virtual bool OnPaste(SharedData data, Microsoft.ManagementConsole.DragAndDropVerb pasteType, SyncStatus status)
        {
            return false;
        }

        internal void OnPasteTargetInfoChanged(PasteTargetInfo selectionPasteInfo)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnPasteTargetInfoChanged");
            }
            UpdateViewPasteTargetInfoCommand command = new UpdateViewPasteTargetInfoCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.PasteTargetInfo = selectionPasteInfo;
            snapInPlatform.ProcessCommand(command);
        }

        protected virtual void OnPrint(SyncStatus status)
        {
        }

        protected virtual void OnRefresh(AsyncStatus status)
        {
        }

        protected virtual void OnRename(string newText, SyncStatus status)
        {
        }

        protected virtual byte[] OnSaveCustomData(SyncStatus status)
        {
            return null;
        }

        protected virtual void OnSelectionAction(Action action, AsyncStatus status)
        {
        }

        internal void OnSelectionActionsChanged(ActionsPaneItemCollectionData actionsData)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionActionsChanged");
            }
            UpdateViewActionsCommand command = new UpdateViewActionsCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.ActionType = ViewActionType.Selection;
            command.Data = actionsData;
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSelectionContextChanged(int id, SelectionCardinality type, Guid[] uniqueNodeTypes, WritableSharedDataItem[] sharedDataItems)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionContextChanged");
            }
            SetNewSelectionCommand command = new SetNewSelectionCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.Id = id;
            command.SelectionCardinality = type;
            command.UniqueNodeTypes = uniqueNodeTypes;
            command.UpdatedSharedData = this.CreateSharedDataObjectUpdate(sharedDataItems, new WritableSharedDataItem[0], new WritableSharedDataItem[0]);
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSelectionDescriptionChanged(string description)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionDescriptionChanged");
            }
            UpdateViewSelectionDescriptionCommand command = new UpdateViewSelectionDescriptionCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.Description = description;
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSelectionDisplayNameChanged(string displayName)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionDisplayNameChanged");
            }
            UpdateViewSelectionDisplayNameCommand command = new UpdateViewSelectionDisplayNameCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.DisplayName = displayName;
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSelectionHelpActionsChanged(ActionsPaneItemCollectionData actionsData)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionActionsChanged");
            }
            foreach (ActionsPaneItemData data in actionsData.GetItems())
            {
                data.InsertionLocation = ActionsInsertionLocation.Help;
            }
            actionsData.InsertionLocation = ActionsInsertionLocation.Help;
            UpdateViewActionsCommand command = new UpdateViewActionsCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.ActionType = ViewActionType.Help;
            command.Data = actionsData;
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSelectionHelpTopicChanged(string helpTopic)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSelectionHelpTopicChanged");
            }
            UpdateViewSelectionHelpTopicCommand command = new UpdateViewSelectionHelpTopicCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.HelpTopic = helpTopic;
            snapInPlatform.ProcessCommand(command);
        }

        internal void OnSharedDataChanged(WritableSharedDataItem[] addedItems, WritableSharedDataItem[] modifiedItems, WritableSharedDataItem[] removedItems)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnSharedDataChanged");
            }
            UpdateViewSharedDataCommand command = new UpdateViewSharedDataCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.UpdatedSharedData = this.CreateSharedDataObjectUpdate(addedItems, modifiedItems, removedItems);
            snapInPlatform.ProcessCommand(command);
        }

        protected virtual void OnSharedDataChangeRequested(object selectionObject, WritableSharedDataItem item, byte[] newValue, AsyncStatus status)
        {
        }

        protected virtual void OnShow()
        {
        }

        protected virtual void OnShutdown(SyncStatus status)
        {
        }

        protected virtual void OnSyncAction(SyncAction action, SyncStatus status)
        {
        }

        protected virtual void OnSyncModeAction(SyncAction action, SyncStatus status)
        {
        }

        protected virtual void OnSyncSelectionAction(SyncAction action, SyncStatus status)
        {
        }

        internal void OnVerbsChanged(Microsoft.ManagementConsole.StandardVerbs enabledVerbs)
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "OnVerbsChanged");
            }
            UpdateViewStandardVerbsCommand command = new UpdateViewStandardVerbsCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.EnabledVerbs = (Microsoft.ManagementConsole.Internal.StandardVerbs) enabledVerbs;
            snapInPlatform.ProcessCommand(command);
        }

        private void ParseSharedDataItems(WritableSharedDataItem[] items, ArrayList formats, ArrayList dataUpdate)
        {
            foreach (WritableSharedDataItem item in items)
            {
                DataFormatConfiguration configuration = new DataFormatConfiguration();
                configuration.ClipboardFormatId = item.ClipboardFormatId;
                configuration.RequiresQuery = item.RequiresCallback;
                formats.Add(configuration);
                if (!item.RequiresCallback)
                {
                    ClipboardData data = new ClipboardData();
                    data.SetValue(item.GetData());
                    data.ClipboardFormatId = item.ClipboardFormatId;
                    dataUpdate.Add(data);
                }
            }
        }

        internal virtual void ProcessNotification(Notification notification)
        {
            if (notification is HideViewNotification)
            {
                this.HandleHideNotification();
            }
            else if (notification is ShowViewNotification)
            {
                this.HandleShowNotification();
            }
            else
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "The Notification of type {0} is not handled by view {1}.", new object[] { notification.GetType().FullName, this._viewInstanceId });
            }
        }

        internal virtual void ProcessRequest(Request request)
        {
            RequestInfo requestInfo = request.RequestInfo;
            if (requestInfo is ActionViewRequestInfo)
            {
                ActionViewRequestInfo info2 = (ActionViewRequestInfo) requestInfo;
                this.DoAction(info2.ActionId, info2.SelectionDependent, info2.SelectionId, request.RequestStatus);
            }
            else if (requestInfo is ReadSharedDataViewRequestInfo)
            {
                ReadSharedDataViewRequestInfo info3 = (ReadSharedDataViewRequestInfo) requestInfo;
                this.GetSharedData(info3.RequestedClipboardFormatId, info3.SelectionId, request.RequestStatus);
            }
            else if (requestInfo is UpdateSharedDataViewRequestInfo)
            {
                UpdateSharedDataViewRequestInfo info4 = (UpdateSharedDataViewRequestInfo) requestInfo;
                this.RequestSharedDataUpdate(info4.RequestedValue, info4.SelectionId, request.RequestStatus);
            }
            else if (requestInfo is PagesForViewRequestInfo)
            {
                PagesForViewRequestInfo info5 = (PagesForViewRequestInfo) requestInfo;
                this.GetPropertyPages(info5.SheetId, (long) info5.SelectionId, request.RequestStatus);
            }
            else if ((((requestInfo is DeleteViewSelectionRequestInfo) || (requestInfo is RefreshViewSelectionRequestInfo)) || ((requestInfo is PrintViewSelectionRequestInfo) || (requestInfo is RenameViewSelectionRequestInfo))) || ((requestInfo is PasteViewSelectionRequestInfo) || (requestInfo is CutOrMoveViewSelectionRequestInfo)))
            {
                this.DoVerb(requestInfo, request.RequestStatus);
            }
            else if (requestInfo is InitializeViewRequestInfo)
            {
                this.HandleInitializationRequest(request.RequestStatus);
            }
            else if (requestInfo is ShutdownViewRequestInfo)
            {
                this.HandleShutdownRequest(request.RequestStatus);
            }
            else if (requestInfo is LoadViewDataRequestInfo)
            {
                this.HandleLoadViewDataRequest(request.RequestStatus, (requestInfo as LoadViewDataRequestInfo).GetDataBlob());
            }
            else if (requestInfo is SaveViewDataRequestInfo)
            {
                SaveViewDataRequestInfo info7 = requestInfo as SaveViewDataRequestInfo;
                this.HandleSaveViewDataRequest(request.RequestStatus, info7.ClearModified);
            }
            else if (requestInfo is KeepAliveViewSelectionRequestInfo)
            {
                KeepAliveViewSelectionRequestInfo info8 = requestInfo as KeepAliveViewSelectionRequestInfo;
                this.HandleKeepAliveRequest(info8.SelectionId, info8.KeepAlive, info8.Purpose, request.RequestStatus);
            }
            else if (requestInfo is CompareViewSelectionsRequestInfo)
            {
                CompareViewSelectionsRequestInfo info9 = requestInfo as CompareViewSelectionsRequestInfo;
                this.ComparePropertySheetSelectionObjects(info9.SelectionId, info9.SelectionIdToCompare, request.RequestStatus);
            }
            else
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "The request of type {0} is not handled by view {1}.", new object[] { requestInfo.GetType().FullName, this._viewInstanceId });
            }
        }

        internal void RequestSharedDataUpdate(ClipboardData requestedValue, int selectionId, IRequestStatus requestStatus)
        {
            object selectionObject = null;
            WritableSharedData sharedData = null;
            if ((this.SelectionData.SelectionCardinality == SelectionCardinality.None) || (selectionId != this.SelectionData.Id))
            {
                AuxiliarySelectionData data2 = this.ClipboardSelectionDatas[selectionId];
                if (data2 == null)
                {
                    data2 = this.SnapIn.SheetManager.ActiveViewPropertySheetSelectionDatas[selectionId];
                }
                if (data2 == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Request for updating data format {0} in view {1} selection id {2} could not be handled.", new object[] { requestedValue.ClipboardFormatId, this._viewInstanceId, selectionId });
                    return;
                }
                sharedData = data2.SharedData;
                selectionObject = data2.SelectionObject;
            }
            else
            {
                sharedData = this.SelectionData.SharedData;
                selectionObject = this.SelectionData.SelectionObject;
            }
            WritableSharedDataItem item = sharedData.GetItem(requestedValue.ClipboardFormatId);
            if (item == null)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "The requested data format {0} is no longer available on the current selection in view {1}.", new object[] { requestedValue.ClipboardFormatId, this._viewInstanceId });
            }
            else
            {
                this.OnSharedDataChangeRequested(selectionObject, item, requestedValue.GetValue(), new AsyncStatus(requestStatus));
            }
        }

        public void SelectScopeNode(Microsoft.ManagementConsole.ScopeNode scopeNode)
        {
            this.SelectScopeNode(scopeNode, new NodeId[0]);
        }

        public void SelectScopeNode(Microsoft.ManagementConsole.ScopeNode startNode, NodeId[] relativePath)
        {
            this.ThrowIfShutdown("SelectScopeNode");
            if (startNode == null)
            {
                throw new ArgumentNullException("startNode");
            }
            if (relativePath == null)
            {
                throw new ArgumentNullException("relativePath");
            }
            if (!this.Initialized || !this.Visible)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Ignoring select scope node request since view hasn't been initialized or is hidden.");
            }
            else
            {
                ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
                if (snapInPlatform == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
                }
                NodeIdData[] dataArray = new NodeIdData[relativePath.Length];
                int num = 0;
                foreach (NodeId id in relativePath)
                {
                    NodeIdData data = new NodeIdData();
                    if (id is DisplayNameNodeId)
                    {
                        data.NameId = ((DisplayNameNodeId) id).DisplayName;
                        data.Type = NodeIdType.Display;
                    }
                    else if (id is LanguageIndependentNameNodeId)
                    {
                        data.NameId = ((LanguageIndependentNameNodeId) id).LanguageIndependentName;
                        data.Type = NodeIdType.LanguageIndependent;
                    }
                    else
                    {
                        if (!(id is CustomNodeId))
                        {
                            throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ViewSelectScopeNodeNullOrUnrecognizedNodeId, new object[] { num }), "relativePath");
                        }
                        data.SetCustomId(((CustomNodeId) id).GetCustomId());
                        data.Type = NodeIdType.Custom;
                    }
                    dataArray[num++] = data;
                }
                SelectScopeNodeCommand command = new SelectScopeNodeCommand();
                command.ViewInstanceId = this.ViewInstanceId;
                command.ScopeNodeId = startNode.Id;
                command.SetRelativePath(dataArray);
                snapInPlatform.ProcessCommand(command);
            }
        }

        private void SynchronizeDescriptionBarText()
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "SyncronizeDescriptionBarText");
            }
            UpdateViewDescriptionBarTextCommand command = new UpdateViewDescriptionBarTextCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.DescriptionBarText = this._descriptionBarText;
            snapInPlatform.ProcessCommand(command);
        }

        private void SynchronizeGlobalActions()
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "SynchronizeGlobalActions");
            }
            UpdateViewActionsCommand command = new UpdateViewActionsCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.ActionType = ViewActionType.Global;
            command.Data = this.ActionsPaneItems.Data;
            snapInPlatform.ProcessCommand(command);
        }

        private void SynchronizeModeActions()
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "SynchronizeModeActions");
            }
            foreach (ActionsPaneItemData data in this.ModeActionsPaneItems.Data.GetItems())
            {
                data.InsertionLocation = ActionsInsertionLocation.View;
            }
            UpdateViewActionsCommand command = new UpdateViewActionsCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.ActionType = ViewActionType.Mode;
            command.Data = this.ModeActionsPaneItems.Data;
            snapInPlatform.ProcessCommand(command);
        }

        private void SynchronizeModifiedState()
        {
            ISnapInPlatform snapInPlatform = this.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("SnapIn", "SynchronizeModifiedState");
            }
            UpdateViewModifiedStateCommand command = new UpdateViewModifiedStateCommand();
            command.ViewInstanceId = this.ViewInstanceId;
            command.IsModified = this._isModified;
            snapInPlatform.ProcessCommand(command);
        }

        internal void ThrowIfShutdown(string viewOperation)
        {
            if (this._shutdown)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassShutdownException("View", viewOperation);
            }
        }

        public ActionsPaneItemCollection ActionsPaneItems
        {
            get
            {
                if (this._actionsPaneItems == null)
                {
                    this._actionsPaneItems = new ActionsPaneItemCollection();
                    this._actionsPaneItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnGlobalActionsChanged);
                }
                return this._actionsPaneItems;
            }
        }

        private AuxiliarySelectionDataCollection ClipboardSelectionDatas
        {
            get
            {
                if (this._clipboardSelectionDatas == null)
                {
                    this._clipboardSelectionDatas = new AuxiliarySelectionDataCollection();
                }
                return this._clipboardSelectionDatas;
            }
        }

        public string DescriptionBarText
        {
            get
            {
                return this._descriptionBarText;
            }
            set
            {
                this.ThrowIfShutdown("DescriptionBarText");
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (this._descriptionBarText != value)
                {
                    this._descriptionBarText = value;
                    if (this.Initialized)
                    {
                        this.SynchronizeDescriptionBarText();
                    }
                }
            }
        }

        internal bool Initialized
        {
            get
            {
                return this._initialized;
            }
        }

        public bool IsModified
        {
            get
            {
                return this._isModified;
            }
            set
            {
                this.ThrowIfShutdown("IsModified");
                if (this._isModified != value)
                {
                    this._isModified = value;
                    if (this.Initialized)
                    {
                        this.SynchronizeModifiedState();
                    }
                }
            }
        }

        internal IMessageClient MessageClient
        {
            get
            {
                return this._messageClient;
            }
        }

        public ActionsPaneItemCollection ModeActionsPaneItems
        {
            get
            {
                if (this._modeActionsPaneItems == null)
                {
                    this._modeActionsPaneItems = new ActionsPaneItemCollection();
                    this._modeActionsPaneItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnModeActionsChanged);
                }
                return this._modeActionsPaneItems;
            }
        }

        public Microsoft.ManagementConsole.ScopeNode ScopeNode
        {
            get
            {
                return this._scopeNode;
            }
        }

        public Microsoft.ManagementConsole.SelectionData SelectionData
        {
            get
            {
                if (this._selectionData == null)
                {
                    this._selectionData = new Microsoft.ManagementConsole.SelectionData(this);
                }
                return this._selectionData;
            }
        }

        public object SharedTag
        {
            get
            {
                if (!this.Initialized)
                {
                    return null;
                }
                return this._snapIn.GetMdiSharedData(this._componentId);
            }
            set
            {
                if (this._viewInstanceId == -1)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionViewsViewNotInitialized));
                }
                this.ThrowIfShutdown("SharedTag");
                this._snapIn.SetMdiSharedData(this._componentId, value);
            }
        }

        internal bool Shutdown
        {
            get
            {
                return this._shutdown;
            }
        }

        public NamespaceSnapInBase SnapIn
        {
            get
            {
                return this._snapIn;
            }
        }

        internal Microsoft.ManagementConsole.ViewDescription ViewDescription
        {
            get
            {
                return this._viewDescription;
            }
        }

        public object ViewDescriptionTag
        {
            get
            {
                if (this._viewDescription != null)
                {
                    return this._viewDescription.Tag;
                }
                return null;
            }
        }

        internal int ViewInstanceId
        {
            get
            {
                return this._viewInstanceId;
            }
        }

        internal bool Visible
        {
            get
            {
                return this._visible;
            }
        }
    }
}

