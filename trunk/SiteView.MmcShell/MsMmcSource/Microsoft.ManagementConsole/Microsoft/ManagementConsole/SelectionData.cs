namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Diagnostics;
    using System.Threading;

    public sealed class SelectionData
    {
        private ActionsPaneItemCollection _actionsPaneHelpItems;
        private ActionsPaneItemCollection _actionsPaneItems;
        private bool _batchUpdates;
        private string _description;
        private string _displayName;
        private Microsoft.ManagementConsole.StandardVerbs _enabledVerbs;
        private string _helpTopic;
        private int _id;
        private static int _nextSelectionId = -1;
        private PasteTargetInfo _pasteTargetInfo;
        private object _selectionObject;
        private WritableSharedData _sharedData;
        private Microsoft.ManagementConsole.Internal.SelectionCardinality _type;
        private Guid[] _uniqueNodeTypes;
        private View _view;

        private SelectionData()
        {
            this._id = -1;
            this._uniqueNodeTypes = new Guid[0];
            this._sharedData = new WritableSharedData();
            this._description = string.Empty;
            this._actionsPaneItems = new ActionsPaneItemCollection();
            this._actionsPaneHelpItems = new ActionsPaneItemCollection();
            this._pasteTargetInfo = new PasteTargetInfo();
        }

        internal SelectionData(View view)
        {
            this._id = -1;
            this._uniqueNodeTypes = new Guid[0];
            this._sharedData = new WritableSharedData();
            this._description = string.Empty;
            this._actionsPaneItems = new ActionsPaneItemCollection();
            this._actionsPaneHelpItems = new ActionsPaneItemCollection();
            this._pasteTargetInfo = new PasteTargetInfo();
            if (view == null)
            {
                throw new ArgumentNullException("view");
            }
            this._view = view;
            this._sharedData.Changed += new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
            this._actionsPaneItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnActionsPaneItemsChanged);
            this._actionsPaneHelpItems.Changed += new ActionsPaneItemCollection.ActionsPaneItemCollectionEventHandler(this.OnActionsPaneHelpItemsChanged);
        }

        public void BeginUpdates()
        {
            this.ThrowIfViewShutdown("BeginUpdates");
            if (!this._batchUpdates)
            {
                this._batchUpdates = true;
                if (this._view.Initialized)
                {
                    this._view.BatchSelectionDataUpdates(true);
                }
            }
        }

        private void ChangeSelection(object selectionObject, Microsoft.ManagementConsole.Internal.SelectionCardinality type, Guid[] uniqueNodeTypes, WritableSharedData sharedData)
        {
            switch (type)
            {
                case Microsoft.ManagementConsole.Internal.SelectionCardinality.None:
                    if (uniqueNodeTypes.Length > 0)
                    {
                        throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("uniqueNodeTypes.Length", uniqueNodeTypes.Length, 0, 0);
                    }
                    break;

                case Microsoft.ManagementConsole.Internal.SelectionCardinality.Single:
                    if (uniqueNodeTypes.Length > 1)
                    {
                        throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("uniqueNodeTypes.Length", uniqueNodeTypes.Length, 0, 1);
                    }
                    break;
            }
            this._id = this.GetSelectionId(type, selectionObject);
            if (sharedData == null)
            {
                sharedData = new WritableSharedData();
            }
            this._type = type;
            this._uniqueNodeTypes = uniqueNodeTypes;
            this.ReplaceSharedData(sharedData);
            this._selectionObject = selectionObject;
            this.ValidateVerbs();
            if (this._view.Initialized)
            {
                this._view.OnSelectionContextChanged(this._id, this._type, this._uniqueNodeTypes, this._sharedData.GetItems());
            }
            ScopeNode scopeNode = this._view.ScopeNode;
            if (scopeNode != null)
            {
                scopeNode.CurrentSelectionDatas[this._view] = new AuxiliarySelectionData(this);
            }
        }

        public void Clear()
        {
            this.ThrowIfViewShutdown("Clear");
            MmcListView view = this._view as MmcListView;
            if (view != null)
            {
                if (!view.SnapInProcessingSelectionChange)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataClearInvalidFromList));
                }
                if (view.SelectedNodes.Count > 0)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataClearInvalidClear));
                }
            }
            this.ChangeSelection(null, Microsoft.ManagementConsole.Internal.SelectionCardinality.None, new Guid[0], new WritableSharedData());
        }

        public void EndUpdates()
        {
            this.ThrowIfViewShutdown("EndUpdates");
            if (this._batchUpdates)
            {
                this._batchUpdates = false;
                if (this._view.Initialized)
                {
                    this._view.BatchSelectionDataUpdates(false);
                }
            }
            else
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "SelectionData.EndUpdates called without a matching SelectionData.BeginUpdates.");
            }
        }

        public string[] GetAllowedClipboardFormatIdsForPaste()
        {
            return this._pasteTargetInfo.GetAllowedClipboardFormats();
        }

        private int GetSelectionId(Microsoft.ManagementConsole.Internal.SelectionCardinality type, object selectionObject)
        {
            int selectionId = -1;
            bool flag = true;
            if (selectionObject != null)
            {
                flag = !this._view.SnapIn.RunningTaskSelectionDatas.FindMatchingSelectionId(selectionObject, out selectionId);
                if (flag)
                {
                    ScopeNode scopeNode = this._view.ScopeNode;
                    flag = (scopeNode == null) || !scopeNode.CurrentSelectionDatas.FindMatchingSelectionId(selectionObject, out selectionId);
                }
            }
            if (!flag)
            {
                return selectionId;
            }
            if (_nextSelectionId == 0x7fffffff)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "The max value for selection identifiers has been reached.");
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionMMCOutOfResources));
            }
            Interlocked.Increment(ref _nextSelectionId);
            return _nextSelectionId;
        }

        public Guid[] GetUniqueNodeTypes()
        {
            return this._uniqueNodeTypes;
        }

        private void OnActionsPaneHelpItemsChanged(object sender, ActionsPaneItemCollectionEventArgs e)
        {
            this.ThrowIfViewShutdown("OnActionsPaneHelpItemsChanged");
            if (this._view.Initialized)
            {
                this._view.OnSelectionHelpActionsChanged(this._actionsPaneHelpItems.Data);
            }
        }

        private void OnActionsPaneItemsChanged(object sender, ActionsPaneItemCollectionEventArgs e)
        {
            this.ThrowIfViewShutdown("OnActionsPaneItemsChanged");
            if (this._view.Initialized)
            {
                this._view.OnSelectionActionsChanged(this._actionsPaneItems.Data);
            }
        }

        private void OnSharedDataChanged(object source, WritableSharedDataChangedEventArgs e)
        {
            if (this._view.Shutdown)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Ignoring published data changes since view has been shutdown.");
            }
            else
            {
                WritableSharedDataItem[] itemArray = new WritableSharedDataItem[0];
                WritableSharedDataItem[] addedItems = itemArray;
                WritableSharedDataItem[] modifiedItems = itemArray;
                WritableSharedDataItem[] removedItems = itemArray;
                switch (e.ChangeType)
                {
                    case WritableSharedDataChangeType.Add:
                        addedItems = new WritableSharedDataItem[] { e.SharedDataItem };
                        break;

                    case WritableSharedDataChangeType.Remove:
                        removedItems = new WritableSharedDataItem[] { e.SharedDataItem };
                        break;

                    case WritableSharedDataChangeType.Modify:
                        modifiedItems = new WritableSharedDataItem[] { e.SharedDataItem };
                        break;
                }
                if (this._view.Initialized)
                {
                    this._view.OnSharedDataChanged(addedItems, modifiedItems, removedItems);
                }
            }
        }

        internal void PerformInitialSynchronization()
        {
            if (this._batchUpdates)
            {
                this._view.BatchSelectionDataUpdates(true);
            }
            if (this._id != -1)
            {
                this._view.OnSelectionContextChanged(this._id, this._type, this._uniqueNodeTypes, this._sharedData.GetItems());
            }
            if (this._displayName != null)
            {
                this._view.OnSelectionDisplayNameChanged(this._displayName);
            }
            if (this._description != string.Empty)
            {
                this._view.OnSelectionDescriptionChanged(this._description);
            }
            if (this._helpTopic != null)
            {
                this._view.OnSelectionHelpTopicChanged(this._helpTopic);
            }
            if (this._actionsPaneItems.Count > 0)
            {
                this._view.OnSelectionActionsChanged(this._actionsPaneItems.Data);
            }
            if (this._actionsPaneHelpItems.Count > 0)
            {
                this._view.OnSelectionHelpActionsChanged(this._actionsPaneHelpItems.Data);
            }
            if (this._enabledVerbs != Microsoft.ManagementConsole.StandardVerbs.None)
            {
                this._view.OnVerbsChanged(this._enabledVerbs);
            }
            if ((this._pasteTargetInfo.DefaultDragAndDropVerb != Microsoft.ManagementConsole.Internal.DragAndDropVerb.CopyHere) || (this._pasteTargetInfo.GetAllowedClipboardFormats() != null))
            {
                this._view.OnPasteTargetInfoChanged(this._pasteTargetInfo);
            }
        }

        private WritableSharedData ReplaceSharedData(WritableSharedData newSharedData)
        {
            WritableSharedData data = this._sharedData;
            data.Changed -= new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
            this._sharedData = newSharedData;
            this._sharedData.Changed += new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
            return data;
        }

        public void SetAllowedClipboardFormatIdsForPaste(string[] clipboardFormats)
        {
            this.ThrowIfViewShutdown("SetAllowedClipboardFormatIdsForPaste");
            this._pasteTargetInfo.SetAllowedClipboardFormats(clipboardFormats);
            if (this._view.Initialized)
            {
                this._view.OnPasteTargetInfoChanged(this._pasteTargetInfo);
            }
        }

        public bool ShowPropertySheet(string title)
        {
            return this.ShowPropertySheet(title, false);
        }

        public bool ShowPropertySheet(string title, bool hideApplyButton)
        {
            this.ThrowIfViewShutdown("ShowPropertySheet");
            if (!this._view.Initialized || !this._view.Visible)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Ignoring property sheet request since view hasn't been initialized or is hidden.");
                return true;
            }
            if (title == null)
            {
                throw new ArgumentNullException("title");
            }
            if (this._selectionObject == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataObjectNull));
            }
            int num = SnapInBase.SnapInInstance.SheetManager.FindPropertySheet(this._selectionObject);
            if (num != -1)
            {
                FindPropertySheetForViewCommand command = new FindPropertySheetForViewCommand();
                command.SelectionId = num;
                FindPropertySheetCommandResult result = (FindPropertySheetCommandResult) SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
                if ((result != null) && result.SheetExists)
                {
                    return false;
                }
            }
            PropertyPageCollection propertyPageCollection = new PropertyPageCollection();
            this._view.OnAddPropertyPages(propertyPageCollection);
            CreatePropertySheetForViewCommand command2 = new CreatePropertySheetForViewCommand();
            command2.Title = title;
            command2.HideApplyButton = hideApplyButton;
            command2.ViewId = this._view.ViewInstanceId;
            command2.PropertyPagesData = propertyPageCollection.ToPropertyPageInfoArray();
            CreatePropertySheetCommandResult result2 = (CreatePropertySheetCommandResult) SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command2);
            if ((result2 != null) && (result2.SheetId != -1))
            {
                SnapInBase.SnapInInstance.SheetManager.CreatePropertySheet(result2.SheetId, propertyPageCollection, new AuxiliarySelectionData(this));
            }
            return true;
        }

        private void ThrowIfViewShutdown(string viewOperation)
        {
            if (this._view.Shutdown)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassShutdownException("View", viewOperation);
            }
        }

        public void Update(object selectionObject, bool multiSelection, Guid[] uniqueNodeTypes, WritableSharedData sharedData)
        {
            this.ThrowIfViewShutdown("Update");
            MmcListView view = this._view as MmcListView;
            if (view != null)
            {
                if (!view.SnapInProcessingSelectionChange)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataUpdateInvalidFromList));
                }
                if ((multiSelection && (view.SelectedNodes.Count < 2)) || (!multiSelection && (view.SelectedNodes.Count != 1)))
                {
                    throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataUpdateInvalidUpdate), "multiSelection");
                }
            }
            if ((uniqueNodeTypes == null) || (uniqueNodeTypes.Length == 0))
            {
                uniqueNodeTypes = new Guid[] { Guid.Empty };
            }
            this.ChangeSelection(selectionObject, multiSelection ? Microsoft.ManagementConsole.Internal.SelectionCardinality.Multiple : Microsoft.ManagementConsole.Internal.SelectionCardinality.Single, uniqueNodeTypes, sharedData);
        }

        private void ValidateVerbs()
        {
            if ((this._type == Microsoft.ManagementConsole.Internal.SelectionCardinality.Multiple) && (((this._enabledVerbs & Microsoft.ManagementConsole.StandardVerbs.Rename) != Microsoft.ManagementConsole.StandardVerbs.None) || ((this._enabledVerbs & Microsoft.ManagementConsole.StandardVerbs.Paste) != Microsoft.ManagementConsole.StandardVerbs.None)))
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Paste and Rename verbs will not be enabled in the UI for multiselection.");
            }
            if (!(this._view is MmcListView) && ((this._enabledVerbs & Microsoft.ManagementConsole.StandardVerbs.Rename) != Microsoft.ManagementConsole.StandardVerbs.None))
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SelectionDataStandardVerbsRenameVerbInvalidUpdate));
            }
        }

        public ActionsPaneItemCollection ActionsPaneHelpItems
        {
            get
            {
                return this._actionsPaneHelpItems;
            }
        }

        public ActionsPaneItemCollection ActionsPaneItems
        {
            get
            {
                return this._actionsPaneItems;
            }
        }

        public Microsoft.ManagementConsole.DragAndDropVerb DefaultDragAndDropVerb
        {
            get
            {
                return (Microsoft.ManagementConsole.DragAndDropVerb) this._pasteTargetInfo.DefaultDragAndDropVerb;
            }
            set
            {
                this.ThrowIfViewShutdown("set_DefaultDragAndDropVerb");
                if (this._pasteTargetInfo.DefaultDragAndDropVerb != ((Microsoft.ManagementConsole.Internal.DragAndDropVerb) ((int) value)))
                {
                    this._pasteTargetInfo.DefaultDragAndDropVerb = (Microsoft.ManagementConsole.Internal.DragAndDropVerb) value;
                    if (this._view.Initialized)
                    {
                        this._view.OnPasteTargetInfoChanged(this._pasteTargetInfo);
                    }
                }
            }
        }

        public string Description
        {
            get
            {
                return this._description;
            }
            set
            {
                this.ThrowIfViewShutdown("set_Description");
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (this._description != value)
                {
                    this._description = value;
                    if (this._view.Initialized)
                    {
                        this._view.OnSelectionDescriptionChanged(this._description);
                    }
                }
            }
        }

        public string DisplayName
        {
            get
            {
                if (this._displayName != null)
                {
                    return this._displayName;
                }
                return string.Empty;
            }
            set
            {
                this.ThrowIfViewShutdown("set_DisplayName");
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (this._displayName != value)
                {
                    this._displayName = value;
                    if (this._view.Initialized)
                    {
                        this._view.OnSelectionDisplayNameChanged(this._displayName);
                    }
                }
            }
        }

        public Microsoft.ManagementConsole.StandardVerbs EnabledStandardVerbs
        {
            get
            {
                return this._enabledVerbs;
            }
            set
            {
                this.ThrowIfViewShutdown("set_EnabledStandardVerbs");
                if (this._enabledVerbs != value)
                {
                    this._enabledVerbs = value;
                    this.ValidateVerbs();
                    if (this._view.Initialized)
                    {
                        this._view.OnVerbsChanged(this._enabledVerbs);
                    }
                }
            }
        }

        public string HelpTopic
        {
            get
            {
                if (this._helpTopic != null)
                {
                    return this._helpTopic;
                }
                return string.Empty;
            }
            set
            {
                if (value != this._helpTopic)
                {
                    this._helpTopic = value;
                    if (this._view.Initialized)
                    {
                        this._view.OnSelectionHelpTopicChanged(this._helpTopic);
                    }
                }
            }
        }

        internal int Id
        {
            get
            {
                return this._id;
            }
        }

        internal Microsoft.ManagementConsole.Internal.SelectionCardinality SelectionCardinality
        {
            get
            {
                return this._type;
            }
        }

        public object SelectionObject
        {
            get
            {
                return this._selectionObject;
            }
        }

        public WritableSharedData SharedData
        {
            get
            {
                return this._sharedData;
            }
            set
            {
                this.ThrowIfViewShutdown("get_SharedData");
                if (value == null)
                {
                    value = new WritableSharedData();
                }
                WritableSharedData data = this.ReplaceSharedData(value);
                if (this._view.Initialized)
                {
                    this._view.OnSharedDataChanged(this._sharedData.GetItems(), new WritableSharedDataItem[0], data.GetItems());
                }
            }
        }
    }
}

