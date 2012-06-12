namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Diagnostics;

    public class MmcListView : View
    {
        private MmcListViewColumnCollection _columns;
        private MmcListViewMode _mode;
        private MmcListViewOptions _options;
        private SortListViewCommand _pendingSortCommand;
        private ResultNodeCollection _resultNodes;
        private SelectedNodeCollection _selectedNodes = new SelectedNodeCollection();
        private IResultNodeComparer _sorter;
        private ListViewStates _states;

        internal void ChangeResultNodeSelection(ResultNode node, bool selectionState)
        {
            base.ThrowIfShutdown("SendSelectionRequest");
            int index = this.ResultNodes.IndexOf(node);
            if (index == -1)
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ListViewChangeResultNodeSelectionNotExist));
            }
            if (!base.Initialized || !base.Visible)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Ignoring selection request since view hasn't been initialized or is hidden.");
            }
            else
            {
                ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
                if (snapInPlatform == null)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MmcListView", "ChangeResultNodeSelection");
                }
                SelectResultNodeCommand command = new SelectResultNodeCommand();
                command.ViewInstanceId = base.ViewInstanceId;
                command.SelectionState = selectionState;
                command.Index = index;
                snapInPlatform.ProcessCommand(command);
            }
        }

        private int[] DoSort(int columnIndex, bool descending)
        {
            if ((columnIndex < 0) || (columnIndex >= this.Columns.Count))
            {
                throw new ArgumentOutOfRangeException("columnIndex");
            }
            IResultNodeComparer comparer = ((this._options & MmcListViewOptions.UseCustomSorting) == MmcListViewOptions.None) ? new DefaultComparer() : this._sorter;
            if (comparer == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ListViewDoSortNoComparer));
            }
            comparer.SetColumnIndex(columnIndex);
            ResultNode[] array = this.ResultNodes.ToArray();
            this._states |= ListViewStates.SortingInProgress;
            Array.Sort(array, comparer);
            this._states &= ~ListViewStates.SortingInProgress;
            int[] numArray = new int[array.Length];
            for (int i = 0; i < array.Length; i++)
            {
                numArray[i] = array[i].Id;
            }
            if (descending)
            {
                Array.Reverse(array);
            }
            this.ResultNodes.Replace(array);
            return numArray;
        }

        private void HandleColumnVisibilityChange(int[] visibleIds, int[] hiddenIds)
        {
            foreach (int num in visibleIds)
            {
                MmcListViewColumn column = this.Columns.GetColumn(num);
                if (column == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Column id {0} in View {1} not found. May have been deleted.", new object[] { num, base.ViewInstanceId });
                }
                else
                {
                    column.Data.Visible = true;
                }
            }
            foreach (int num2 in hiddenIds)
            {
                MmcListViewColumn column2 = this.Columns.GetColumn(num2);
                if (column2 == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Column id {0} in View {1} not found. May have been deleted.", new object[] { num2, base.ViewInstanceId });
                }
                else
                {
                    column2.Data.Visible = false;
                }
            }
            this.OnColumnVisibilityChanged();
        }

        private void HandleSelectionChange(int[] scopeNodeIds, int[] resultNodeIds, IRequestStatus requestStatus)
        {
            this._selectedNodes.Clear();
            foreach (ScopeNode node in base.ScopeNode.Children)
            {
                if (Array.IndexOf<int>(scopeNodeIds, node.Id) != -1)
                {
                    this._selectedNodes.Add(node);
                }
            }
            foreach (int num in resultNodeIds)
            {
                ResultNode item = this._resultNodes.GetNode(num);
                if (item == null)
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Verbose, 12, "A selected ResultNode with id {0} in list view {1} appears to have been removed.", new object[] { num, base.ViewInstanceId });
                }
                else
                {
                    this._selectedNodes.Add(item);
                }
            }
            this._states |= ListViewStates.SnapInProcessingSelectionChange;
            SyncStatus status = new SyncStatus(requestStatus);
            this.OnSelectionChanged(status);
            this._states &= ~ListViewStates.SnapInProcessingSelectionChange;
        }

        private void HandleSortRequest(int columnIndex, bool descending, IRequestStatus requestStatus)
        {
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                int[] ids = this.DoSort(columnIndex, descending);
                SortListViewResponse response = new SortListViewResponse();
                response.SetIds(ids);
                requestStatus.ProcessResponse(response);
            }
            finally
            {
                status.Close();
            }
            this.OnSortCompleted(columnIndex, descending);
        }

        internal override void InternalInitialize()
        {
            MmcListViewDescription viewDescription = base.ViewDescription as MmcListViewDescription;
            if (viewDescription == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString("Microsoft.ManagementConsole.ViewDescription.InvalidViewDescription", new object[] { "MmcListView", "MmcListViewDescription" }));
            }
            this._options = viewDescription.Options;
            if (this._mode != MmcListViewMode.Report)
            {
                this.SynchronizeMode(this._mode);
            }
            if (this._columns != null)
            {
                this.SynchronizeColumns(new MmcListViewColumn[] { this._columns[0] }, 0, ColumnCollectionChangeType.Modify);
                int length = this._columns.Count - 1;
                if (length > 0)
                {
                    MmcListViewColumn[] sourceArray = this._columns.ToArray();
                    MmcListViewColumn[] destinationArray = new MmcListViewColumn[length];
                    Array.Copy(sourceArray, 1, destinationArray, 0, length);
                    this.SynchronizeColumns(destinationArray, 1, ColumnCollectionChangeType.Add);
                }
            }
            if ((this._resultNodes != null) && (this._resultNodes.Count > 0))
            {
                this.SynchronizeResultNodes(this.ResultNodes.ToArray(), 0, ResultNodeCollectionChangeType.Add);
            }
            if (this._pendingSortCommand != null)
            {
                bool descending = this._pendingSortCommand.Descending;
                int[] ids = new int[this.ResultNodes.Count];
                for (int i = 0; i < this.ResultNodes.Count; i++)
                {
                    int index = descending ? ((this.ResultNodes.Count - i) - 1) : i;
                    ids[index] = this.ResultNodes[i].Id;
                }
                this._pendingSortCommand.ViewInstanceId = base.ViewInstanceId;
                this._pendingSortCommand.SetIds(ids);
                base.SnapIn.SnapInPlatform.ProcessCommand(this._pendingSortCommand);
                this._pendingSortCommand = null;
            }
        }

        private void OnColumnsChanged(object sender, ColumnCollectionEventArgs e)
        {
            if (e == null)
            {
                throw new ArgumentNullException("e");
            }
            base.ThrowIfShutdown("OnColumnsChanged");
            if (base.Initialized)
            {
                this.SynchronizeColumns(e.GetItems(), e.Index, e.ChangeType);
            }
        }

        protected virtual void OnColumnVisibilityChanged()
        {
        }

        private void OnResultNodesChanged(object sender, ResultNodeCollectionEventArgs e)
        {
            if (e == null)
            {
                throw new ArgumentNullException("e");
            }
            base.ThrowIfShutdown("OnResultNodesChanged");
            if (base.Initialized)
            {
                this.SynchronizeResultNodes(e.GetItems(), e.Index, e.ChangeType);
            }
        }

        protected virtual void OnSelectionChanged(SyncStatus status)
        {
        }

        protected virtual void OnSortCompleted(int columnIndex, bool descending)
        {
        }

        internal override void ProcessNotification(Notification notification)
        {
            if (notification is ColumnVisibilityChangedNotification)
            {
                ColumnVisibilityChangedNotification notification2 = (ColumnVisibilityChangedNotification) notification;
                this.HandleColumnVisibilityChange(notification2.GetVisibleIds(), notification2.GetHiddenIds());
            }
            else
            {
                base.ProcessNotification(notification);
            }
        }

        internal override void ProcessRequest(Request request)
        {
            RequestInfo requestInfo = request.RequestInfo;
            if (requestInfo is ChangeSelectionDataViewRequestInfo)
            {
                ChangeSelectionDataViewRequestInfo info2 = (ChangeSelectionDataViewRequestInfo) requestInfo;
                this.HandleSelectionChange(info2.GetScopeNodeIds(), info2.GetResultNodeIds(), request.RequestStatus);
            }
            else if (requestInfo is SortListViewRequestInfo)
            {
                SortListViewRequestInfo info3 = (SortListViewRequestInfo) requestInfo;
                this.HandleSortRequest(info3.ColumnIndex, info3.Descending, request.RequestStatus);
            }
            else
            {
                base.ProcessRequest(request);
            }
        }

        public void Sort(int columnIndex)
        {
            this.Sort(columnIndex, false);
        }

        public void Sort(int columnIndex, bool descending)
        {
            this.Sort(columnIndex, descending, false);
        }

        public void Sort(int columnIndex, bool descending, bool hideSortIcon)
        {
            base.ThrowIfShutdown("Sort");
            int[] ids = this.DoSort(columnIndex, descending);
            SortListViewCommand command = new SortListViewCommand();
            command.ColumnIndex = columnIndex;
            command.Descending = descending;
            command.HideSortIcon = hideSortIcon;
            if (base.Initialized)
            {
                ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
                if (snapInPlatform == null)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MmcListView", "Sort");
                }
                command.ViewInstanceId = base.ViewInstanceId;
                command.SetIds(ids);
                snapInPlatform.ProcessCommand(command);
            }
            else
            {
                this._pendingSortCommand = command;
            }
            this.OnSortCompleted(columnIndex, descending);
        }

        private void SynchronizeColumns(MmcListViewColumn[] items, int index, ColumnCollectionChangeType changeType)
        {
            if (items == null)
            {
                throw new ArgumentNullException("items");
            }
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MmcListView", "SynchronizeColumns");
            }
            if (items.Length < 1)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Verbose, 12, "Empty column update for view {0}.", new object[] { base.ViewInstanceId });
            }
            else
            {
                UpdateColumnsCommand command = new UpdateColumnsCommand();
                command.ViewInstanceId = base.ViewInstanceId;
                command.ChangeType = changeType;
                command.Index = index;
                ColumnData[] data = new ColumnData[items.Length];
                for (int i = 0; i < items.Length; i++)
                {
                    data[i] = items[i].Data;
                }
                command.SetData(data);
                snapInPlatform.ProcessCommand(command);
            }
        }

        private void SynchronizeMode(MmcListViewMode mode)
        {
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MmcListView", "SynchronizeMode");
            }
            UpdateListViewModeCommand command = new UpdateListViewModeCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            command.Mode = (ListViewMode) mode;
            snapInPlatform.ProcessCommand(command);
        }

        private void SynchronizeResultNodes(ResultNode[] items, int index, ResultNodeCollectionChangeType changeType)
        {
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MmcListView", "SynchronizeResultNodes");
            }
            if (items == null)
            {
                throw new ArgumentNullException("items");
            }
            if (items.Length < 1)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Verbose, 12, "Empty result nodes update for view {0}.", new object[] { base.ViewInstanceId });
            }
            else
            {
                UpdateResultNodesCommand command = new UpdateResultNodesCommand();
                command.ViewInstanceId = base.ViewInstanceId;
                command.ChangeType = changeType;
                command.Index = index;
                NodeData[] data = new NodeData[items.Length];
                for (int i = 0; i < items.Length; i++)
                {
                    data[i] = items[i].Data;
                }
                command.SetData(data);
                snapInPlatform.ProcessCommand(command);
            }
        }

        public MmcListViewColumnCollection Columns
        {
            get
            {
                if (this._columns == null)
                {
                    this._columns = new MmcListViewColumnCollection(this);
                    this._columns.ItemsChanged += new MmcListViewColumnCollection.ColumnCollectionEventHandler(this.OnColumnsChanged);
                }
                return this._columns;
            }
        }

        public MmcListViewMode Mode
        {
            get
            {
                if ((this._options & MmcListViewOptions.AllowUserInitiatedModeChanges) != MmcListViewOptions.None)
                {
                    ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
                    if (snapInPlatform != null)
                    {
                        GetListViewModeCommand command = new GetListViewModeCommand();
                        command.ViewInstanceId = base.ViewInstanceId;
                        GetListViewModeCommandResult result = snapInPlatform.ProcessCommand(command) as GetListViewModeCommandResult;
                        this._mode = (MmcListViewMode) result.Mode;
                    }
                }
                return this._mode;
            }
            set
            {
                base.ThrowIfShutdown("Mode");
                if (((value != MmcListViewMode.Report) && (value != MmcListViewMode.List)) && ((value != MmcListViewMode.SmallIcon) && (value != MmcListViewMode.LargeIcon)))
                {
                    throw new ArgumentOutOfRangeException("value");
                }
                if (base.Initialized)
                {
                    this.SynchronizeMode(value);
                }
                this._mode = value;
            }
        }

        public MmcListViewOptions Options
        {
            get
            {
                return this._options;
            }
        }

        public ResultNodeCollection ResultNodes
        {
            get
            {
                if (this._resultNodes == null)
                {
                    this._resultNodes = new ResultNodeCollection(this);
                    this._resultNodes.ItemsChanged += new ResultNodeCollection.ResultNodeCollectionEventHandler(this.OnResultNodesChanged);
                }
                return this._resultNodes;
            }
        }

        public SelectedNodeCollection SelectedNodes
        {
            get
            {
                return this._selectedNodes;
            }
        }

        internal bool SnapInProcessingSelectionChange
        {
            get
            {
                return ((this._states & ListViewStates.SnapInProcessingSelectionChange) != ListViewStates.None);
            }
        }

        public IResultNodeComparer Sorter
        {
            get
            {
                return this._sorter;
            }
            set
            {
                base.ThrowIfShutdown("Sorter");
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._sorter = value;
            }
        }

        internal bool SortingInProgress
        {
            get
            {
                return ((this._states & ListViewStates.SortingInProgress) != ListViewStates.None);
            }
        }

        private class DefaultComparer : IResultNodeComparer, IComparer
        {
            private int _columnIndex = -1;

            public int Compare(object object1, object object2)
            {
                ResultNode node = object1 as ResultNode;
                if (node == null)
                {
                    throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ListViewCompareNullObject), "object1");
                }
                ResultNode node2 = object2 as ResultNode;
                if (node2 == null)
                {
                    throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ListViewCompareNullObject), "object2");
                }
                return string.Compare(this.GetStringToCompare(node), this.GetStringToCompare(node2));
            }

            private string GetStringToCompare(ResultNode node)
            {
                string str = string.Empty;
                if (this._columnIndex == 0)
                {
                    return node.DisplayName;
                }
                if (this._columnIndex <= node.SubItemDisplayNames.Count)
                {
                    str = node.SubItemDisplayNames[this._columnIndex - 1];
                }
                return str;
            }

            public void SetColumnIndex(int index)
            {
                this._columnIndex = index;
            }
        }

        [Flags]
        private enum ListViewStates
        {
            None,
            SnapInProcessingSelectionChange,
            SortingInProgress
        }
    }
}

