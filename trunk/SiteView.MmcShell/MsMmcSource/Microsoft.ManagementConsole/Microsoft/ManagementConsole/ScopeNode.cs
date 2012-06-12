namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Runtime.CompilerServices;

    public class ScopeNode : Node
    {
        private EventHandler _actionsActivated;
        private EventHandler _actionsDeactivated;
        private ActionsPaneItemCollection _actionsPaneHelpItems;
        private ActionsPaneItemCollection _actionsPaneItems;
        private ScopeNodeCollection _children;
        private AuxiliarySelectionDataCollection _currentSelectionDatas;
        private List<CustomStatus> _customStatusList;
        private ScopeNodeData _data;
        private static EventArgs _eventArgs = new EventArgs();
        private bool _fSubscribedToViewDescriptionEvents;
        private ScopeNode _parent;
        private WritableSharedData _sharedData;
        private ViewDescriptionCollection _viewDescriptions;

        [EditorBrowsable(EditorBrowsableState.Advanced)]
        public event EventHandler ActionsActivated
        {
            add
            {
                this._actionsActivated = (EventHandler) Delegate.Combine(this._actionsActivated, value);
                this.NotifySendActivation();
            }
            remove
            {
                this._actionsActivated = (EventHandler) Delegate.Remove(this._actionsActivated, value);
                this.NotifySendActivation();
            }
        }

        [EditorBrowsable(EditorBrowsableState.Advanced)]
        public event EventHandler ActionsDeactivated
        {
            add
            {
                this._actionsDeactivated = (EventHandler) Delegate.Combine(this._actionsDeactivated, value);
                this.NotifySendDeactivation();
            }
            remove
            {
                this._actionsDeactivated = (EventHandler) Delegate.Remove(this._actionsDeactivated, value);
                this.NotifySendDeactivation();
            }
        }

        internal event SharedDataChangedEventHandler SharedDataChanged;

        public ScopeNode()
        {
            this._data = new ScopeNodeData();
            this._customStatusList = new List<CustomStatus>();
            base.Initialize(this._data);
            object[] customAttributes = base.GetType().GetCustomAttributes(typeof(NodeTypeAttribute), true);
            if (customAttributes.Length == 1)
            {
                this._data.NodeType = ((NodeTypeAttribute) customAttributes[0]).Guid;
            }
        }

        public ScopeNode(bool hideExpandIcon) : this()
        {
            this._data.HideExpandIcon = hideExpandIcon;
        }

        public ScopeNode(Guid nodeType) : this()
        {
            this._data.NodeType = nodeType;
        }

        public ScopeNode(Guid nodeType, bool hideExpandIcon) : this(nodeType)
        {
            this._data.HideExpandIcon = hideExpandIcon;
        }

        internal void Activate(IRequestStatus requestStatus)
        {
            if (this._actionsActivated != null)
            {
                SyncStatus status = new SyncStatus(requestStatus);
                try
                {
                    this._actionsActivated(this, _eventArgs);
                }
                finally
                {
                    status.Close();
                }
            }
        }

        internal void AddCustomStatus(CustomStatus status)
        {
            this._customStatusList.Add(status);
        }

        internal void Deactivate()
        {
            if (this._actionsDeactivated != null)
            {
                this._actionsDeactivated(this, _eventArgs);
            }
        }

        internal void DoAction(int actionId, IRequestStatus requestStatus)
        {
            ActionsPaneItem itemById = this.ActionsPaneItems.GetItemById(actionId);
            if (itemById == null)
            {
                itemById = this.ActionsPaneHelpItems.GetItemById(actionId);
            }
            Action action = itemById as Action;
            if (action != null)
            {
                AsyncStatus status = new AsyncStatus(requestStatus);
                action.RaiseTriggeredEvent(this, status);
                this.OnAction(action, status);
            }
            else
            {
                SyncAction action2 = itemById as SyncAction;
                if (action2 != null)
                {
                    SyncStatus status2 = new SyncStatus(requestStatus);
                    action2.RaiseTriggeredEvent(this, status2);
                    this.OnSyncAction(action2, status2);
                }
                else
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "action with Id {0} no longer exists on node with Id {1}", new object[] { actionId, base.Id });
                }
            }
        }

        internal void DoVerb(NodeRequestInfo info, IRequestStatus requestStatus)
        {
            if (info is DeleteNodeRequestInfo)
            {
                this.OnDelete(new SyncStatus(requestStatus));
            }
            else if (info is RefreshNodeRequestInfo)
            {
                this.OnRefresh(new AsyncStatus(requestStatus));
            }
            else if (info is PrintNodeRequestInfo)
            {
                this.OnPrint(new SyncStatus(requestStatus));
            }
            else if (info is RenameNodeRequestInfo)
            {
                this.OnRename(((RenameNodeRequestInfo) info).NewDisplayName, new SyncStatus(requestStatus));
            }
            else if (info is PasteNodeRequestInfo)
            {
                PasteNodeRequestInfo info2 = (PasteNodeRequestInfo) info;
                Microsoft.ManagementConsole.SharedData sharedData = new Microsoft.ManagementConsole.SharedData(info2.DataObjectId);
                base.SnapIn.AddSharedData(sharedData);
                sharedData.SetSnapInPlatform(base.SnapIn.SnapInClient.SnapInPlatform);
                PasteResponse response = new PasteResponse();
                try
                {
                    response.AcceptPaste = this.OnPaste(sharedData, (Microsoft.ManagementConsole.DragAndDropVerb) info2.PasteType, new SyncStatus(requestStatus));
                    requestStatus.ProcessResponse(response);
                }
                finally
                {
                    base.SnapIn.RemoveSharedData(sharedData);
                }
            }
            else if (info is CutOrMoveNodeRequestInfo)
            {
                this.OnCut(new AsyncStatus(requestStatus));
            }
        }

        internal void Expand(IRequestStatus requestStatus)
        {
            AsyncStatus status = new AsyncStatus(requestStatus);
            this.OnExpand(status);
        }

        internal bool ExpandFromLoad(IRequestStatus requestStatus)
        {
            SyncStatus status = new SyncStatus(requestStatus);
            return this.OnExpandFromLoad(status);
        }

        public string[] GetAllowedClipboardFormatIdsForPaste()
        {
            return this._data.PasteTargetInfo.GetAllowedClipboardFormats();
        }

        internal void GetPropertyPages(int sheetId, IRequestStatus requestStatus)
        {
            if (requestStatus == null)
            {
                throw new ArgumentNullException("requestStatus", Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ScopeNodeRequestInterfaceNull));
            }
            PropertyPageCollection propertyPageCollection = new PropertyPageCollection();
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                this.OnAddPropertyPages(propertyPageCollection);
                PropertyPagesResponse response = new PropertyPagesResponse();
                response.SetPropertyPages(propertyPageCollection.ToPropertyPageInfoArray());
                requestStatus.ProcessResponse(response);
            }
            finally
            {
                status.Close();
            }
            SnapInBase.SnapInInstance.SheetManager.CreatePropertySheet(sheetId, propertyPageCollection, null);
        }

        internal void GetSharedData(ReadSharedDataNodeRequestInfo requestInfo, IRequestStatus requestStatus)
        {
            WritableSharedDataItem item = this.SharedData.GetItem(requestInfo.RequestedClipboardFormatId);
            if (item != null)
            {
                SyncStatus status = new SyncStatus(requestStatus);
                byte[] buffer = this.OnGetSharedData(item, status);
                ClipboardData data = new ClipboardData();
                data.ClipboardFormatId = item.ClipboardFormatId;
                data.SetValue(buffer);
                ReadSharedDataResponse response = new ReadSharedDataResponse();
                response.RequestedClipboardData = data;
                requestStatus.ProcessResponse(response);
            }
        }

        private void NotifySendActivation()
        {
            bool flag = this._actionsActivated != null;
            if (flag != this._data.SendActivation)
            {
                this._data.SendActivation = flag;
                base.Notify();
            }
        }

        private void NotifySendDeactivation()
        {
            bool flag = this._actionsDeactivated != null;
            if (flag != this._data.SendDeactivation)
            {
                this._data.SendDeactivation = flag;
                base.Notify();
            }
        }

        protected virtual void OnAction(Action action, AsyncStatus status)
        {
        }

        private void OnActionsPaneHelpItemsChanged(object sender, ActionsPaneItemCollectionEventArgs e)
        {
            base.Notify();
        }

        private void OnActionsPaneItemsChanged(object sender, ActionsPaneItemCollectionEventArgs e)
        {
            base.Notify();
        }

        protected virtual void OnAddPropertyPages(PropertyPageCollection propertyPageCollection)
        {
        }

        protected virtual void OnCut(AsyncStatus status)
        {
        }

        protected virtual void OnDelete(SyncStatus status)
        {
        }

        protected virtual void OnExpand(AsyncStatus status)
        {
        }

        protected virtual bool OnExpandFromLoad(SyncStatus status)
        {
            return false;
        }

        protected virtual byte[] OnGetSharedData(WritableSharedDataItem item, SyncStatus status)
        {
            return null;
        }

        internal void OnNodeSyncManagerAdd()
        {
            foreach (CustomStatus status in this._customStatusList)
            {
                status.AttachRequestStatus();
            }
            this.UpdateViewDescriptionSubscription(true);
        }

        internal void OnNodeSyncManagerRemove()
        {
            foreach (CustomStatus status in this._customStatusList)
            {
                status.DetachRequestStatus();
            }
            this.UpdateViewDescriptionSubscription(false);
        }

        protected virtual bool OnPaste(Microsoft.ManagementConsole.SharedData data, Microsoft.ManagementConsole.DragAndDropVerb pasteType, SyncStatus status)
        {
            return false;
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

        private void OnSharedDataChanged(object source, WritableSharedDataChangedEventArgs e)
        {
            if (this.SharedDataChanged != null)
            {
                this.SharedDataChanged(this, e);
            }
        }

        protected virtual void OnSharedDataChangeRequested(WritableSharedDataItem item, byte[] newValue, AsyncStatus status)
        {
        }

        private void OnSharedDataPropertyChangeRequested(object source, WritableSharedDataChangeRequestEventArgs e)
        {
            AsyncStatus status = new AsyncStatus(e.RequestStatus);
            this.OnSharedDataChangeRequested(e.SharedDataItem, e.GetNewValue(), status);
        }

        protected virtual void OnSyncAction(SyncAction action, SyncStatus status)
        {
        }

        private void OnVerbsChanged(object sender, EventArgs e)
        {
            base.Notify();
        }

        internal void OnViewDescriptionsChanged(object sender, ViewDescriptionCollectionEventArgs e)
        {
            base.Notify();
        }

        internal void RemoveCustomStatus(CustomStatus status)
        {
            this._customStatusList.Remove(status);
        }

        internal void RequestSharedDataUpdate(UpdateDataChangeNodeRequestInfo requestInfo, IRequestStatus requestStatus)
        {
            WritableSharedDataItem item = this.SharedData.GetItem(requestInfo.RequestedValue.ClipboardFormatId);
            if (item != null)
            {
                item.OnPropertyUpdateRequested(requestInfo.RequestedValue.GetValue(), requestStatus);
            }
        }

        public void SetAllowedClipboardFormatIdsForPaste(string[] clipboardFormats)
        {
            this._data.PasteTargetInfo.SetAllowedClipboardFormats(clipboardFormats);
            base.Notify();
        }

        internal void SetParent(ScopeNode parent)
        {
            this._parent = parent;
        }

        public bool ShowPropertySheet(string title)
        {
            return this.ShowPropertySheet(title, false);
        }

        public bool ShowPropertySheet(string title, bool hideApplyButton)
        {
            if (title == null)
            {
                throw new ArgumentNullException("title");
            }
            FindPropertySheetForScopeNodeCommand command = new FindPropertySheetForScopeNodeCommand();
            command.ScopeNodeId = base.Id;
            FindPropertySheetCommandResult result = (FindPropertySheetCommandResult) SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
            if ((result != null) && result.SheetExists)
            {
                return false;
            }
            PropertyPageCollection propertyPageCollection = new PropertyPageCollection();
            this.OnAddPropertyPages(propertyPageCollection);
            CreatePropertySheetForScopeNodeCommand command2 = new CreatePropertySheetForScopeNodeCommand();
            command2.Title = title;
            command2.ScopeNodeId = base.Id;
            command2.HideApplyButton = hideApplyButton;
            command2.PropertyPagesData = propertyPageCollection.ToPropertyPageInfoArray();
            CreatePropertySheetCommandResult result2 = (CreatePropertySheetCommandResult) SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command2);
            if ((result2 != null) && (result2.SheetId != -1))
            {
                SnapInBase.SnapInInstance.SheetManager.CreatePropertySheet(result2.SheetId, propertyPageCollection, null);
            }
            return true;
        }

        private void UpdateViewDescriptionSubscription(bool fSubscribe)
        {
            if ((fSubscribe && (this.ViewDescriptionsInternal != null)) && !this._fSubscribedToViewDescriptionEvents)
            {
                this.ViewDescriptionsInternal.ItemsChanged += new ViewDescriptionCollection.ViewDescriptionCollectionEventHandler(this.OnViewDescriptionsChanged);
            }
            else if ((!fSubscribe && (this.ViewDescriptionsInternal != null)) && this._fSubscribedToViewDescriptionEvents)
            {
                this.ViewDescriptionsInternal.ItemsChanged -= new ViewDescriptionCollection.ViewDescriptionCollectionEventHandler(this.OnViewDescriptionsChanged);
            }
            this._fSubscribedToViewDescriptionEvents = fSubscribe;
        }

        public ActionsPaneItemCollection ActionsPaneHelpItems
        {
            get
            {
                if (this._actionsPaneHelpItems == null)
                {
                    this._actionsPaneHelpItems = new ActionsPaneItemCollection();
                    this._actionsPaneHelpItems.InsertionLocation = ActionsInsertionLocation.Help;
                    this._actionsPaneHelpItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnActionsPaneHelpItemsChanged);
                }
                return this._actionsPaneHelpItems;
            }
        }

        public ActionsPaneItemCollection ActionsPaneItems
        {
            get
            {
                if (this._actionsPaneItems == null)
                {
                    this._actionsPaneItems = new ActionsPaneItemCollection();
                    this._actionsPaneItems.InsertionLocation = ActionsInsertionLocation.Top;
                    this._actionsPaneItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnActionsPaneItemsChanged);
                }
                return this._actionsPaneItems;
            }
        }

        public ScopeNodeCollection Children
        {
            get
            {
                if (this._children == null)
                {
                    this._children = new ScopeNodeCollection();
                    this._children.ContainerNode = this;
                }
                return this._children;
            }
        }

        internal AuxiliarySelectionDataCollection CurrentSelectionDatas
        {
            get
            {
                if (this._currentSelectionDatas == null)
                {
                    this._currentSelectionDatas = new AuxiliarySelectionDataCollection();
                }
                return this._currentSelectionDatas;
            }
        }

        public Microsoft.ManagementConsole.DragAndDropVerb DefaultDragAndDropVerb
        {
            get
            {
                return (Microsoft.ManagementConsole.DragAndDropVerb) this._data.PasteTargetInfo.DefaultDragAndDropVerb;
            }
            set
            {
                if (this._data.PasteTargetInfo.DefaultDragAndDropVerb != ((Microsoft.ManagementConsole.Internal.DragAndDropVerb) ((int) value)))
                {
                    this._data.PasteTargetInfo.DefaultDragAndDropVerb = (Microsoft.ManagementConsole.Internal.DragAndDropVerb) value;
                    base.Notify();
                }
            }
        }

        public Microsoft.ManagementConsole.StandardVerbs EnabledStandardVerbs
        {
            get
            {
                return (Microsoft.ManagementConsole.StandardVerbs) this._data.EnabledVerbs;
            }
            set
            {
                if (this._data.EnabledVerbs != ((Microsoft.ManagementConsole.Internal.StandardVerbs) ((int) value)))
                {
                    this._data.EnabledVerbs = (Microsoft.ManagementConsole.Internal.StandardVerbs) value;
                    base.Notify();
                }
            }
        }

        public string HelpTopic
        {
            get
            {
                if (this._data.HelpTopic != null)
                {
                    return this._data.HelpTopic;
                }
                return string.Empty;
            }
            set
            {
                if (value != this._data.HelpTopic)
                {
                    this._data.HelpTopic = value;
                    base.Notify();
                }
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                return this._data.LanguageIndependentName;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._data.LanguageIndependentName = value;
                base.Notify();
            }
        }

        public Guid NodeType
        {
            get
            {
                return this._data.NodeType;
            }
        }

        public ScopeNode Parent
        {
            get
            {
                return this._parent;
            }
        }

        public int SelectedImageIndex
        {
            get
            {
                return this._data.SelectedImageIndex;
            }
            set
            {
                if (this._data.SelectedImageIndex != value)
                {
                    this._data.SelectedImageIndex = value;
                    base.Notify();
                }
            }
        }

        public WritableSharedData SharedData
        {
            get
            {
                if (this._sharedData == null)
                {
                    this._sharedData = new WritableSharedData();
                    this._sharedData.Changed += new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
                    this._sharedData.PropertyChangeRequested += new WritableSharedDataItem.SharedDataChangeRequestEventHandler(this.OnSharedDataPropertyChangeRequested);
                }
                return this._sharedData;
            }
        }

        public ViewDescriptionCollection ViewDescriptions
        {
            get
            {
                if (this._viewDescriptions == null)
                {
                    this.ViewDescriptions = new ViewDescriptionCollection();
                }
                return this._viewDescriptions;
            }
            set
            {
                if (value != this._viewDescriptions)
                {
                    this.UpdateViewDescriptionSubscription(false);
                    this._viewDescriptions = value;
                    this.UpdateViewDescriptionSubscription(true);
                    if (this._viewDescriptions != null)
                    {
                        this._data.ViewSetId = this._viewDescriptions.Id;
                        this._viewDescriptions.Initialize();
                    }
                    else
                    {
                        this._data.ViewSetId = -1;
                    }
                    base.Notify();
                }
            }
        }

        internal ViewDescriptionCollection ViewDescriptionsInternal
        {
            get
            {
                return this._viewDescriptions;
            }
            set
            {
                this.ViewDescriptions = value;
            }
        }

        internal delegate void SharedDataChangedEventHandler(object sender, WritableSharedDataChangedEventArgs e);
    }
}

