namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;

    internal class NodeSyncManager
    {
        private bool _initialized;
        private Dictionary<int, ScopeNode> _nodes = new Dictionary<int, ScopeNode>();
        private ISnapInPlatform _snapInPlatform;

        internal NodeSyncManager()
        {
        }

        internal void AddNodes(ScopeNode[] items, int index)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            if (items.Length != 0)
            {
                int capacity = this.CountNodesForInsertion(items);
                InsertScopeNodesCommandWriter writer = new InsertScopeNodesCommandWriter(capacity);
                ScopeNode[] nodeList = new ScopeNode[capacity];
                int currentNodesIndex = 0;
                try
                {
                    this.AddTreeToInsertionList(writer, nodeList, ref currentNodesIndex, index, items);
                    foreach (ScopeNode node in nodeList)
                    {
                        ViewDescriptionCollection viewDescriptionsInternal = node.ViewDescriptionsInternal;
                        if (viewDescriptionsInternal != null)
                        {
                            viewDescriptionsInternal.Initialize();
                        }
                    }
                    this._snapInPlatform.ProcessCommand(writer.Flush());
                }
                catch
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "NodeSyncManager.AddNodes() failed");
                    throw;
                }
                finally
                {
                    writer.Dispose();
                }
                foreach (ScopeNode node2 in nodeList)
                {
                    node2.Children.ItemsChanged += new ScopeNodeCollection.ScopeNodeCollectionEventHandler(this.OnNodesChanged);
                    node2.Changed += new Node.NodeChangedEventHandler(this.OnNodeChanged);
                    node2.SharedDataChanged += new ScopeNode.SharedDataChangedEventHandler(this.OnNodeSharedDataChanged);
                    this._nodes.Add(node2.Id, node2);
                    node2.OnNodeSyncManagerAdd();
                }
            }
        }

        private void AddTreeToDeletionList(List<ScopeNode> nodeList, ScopeNode[] nodes)
        {
            foreach (ScopeNode node in nodes)
            {
                nodeList.Add(node);
                if (node.Children.Count > 0)
                {
                    this.AddTreeToDeletionList(nodeList, node.Children.ToArray());
                }
            }
        }

        private void AddTreeToInsertionList(InsertScopeNodesCommandWriter writer, ScopeNode[] nodeList, ref int currentNodesIndex, int index, ScopeNode[] nodes)
        {
            foreach (ScopeNode node in nodes)
            {
                if (this._nodes.ContainsKey(node.Id))
                {
                    throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerAddTreeToInsertionListNodeExistInOneLocation));
                }
                if (node == null)
                {
                    throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerInvalidNodeType));
                }
                ScopeNodeInsert insert = new ScopeNodeInsert();
                insert.NodeData = (ScopeNodeData) node.Data;
                ActionsPaneRootData data = new ActionsPaneRootData();
                data.Write(node.ActionsPaneItems.Data);
                insert.Actions = data;
                data = new ActionsPaneRootData();
                data.Write(node.ActionsPaneHelpItems.Data);
                insert.HelpActions = data;
                insert.InitialSharedData.SetAddedFormats(this.GenerateSharedDataFormatConfiguration(node));
                insert.InitialSharedData.SetUpdatedData(this.GenerateClipboardData(node));
                if (node.Parent != null)
                {
                    insert.ParentScopeNodeId = node.Parent.Id;
                }
                insert.InsertionIndex = index;
                writer.WriteScopeNodeInsert(insert);
                nodeList[currentNodesIndex++] = node;
                index++;
                if (node.Children.Count > 0)
                {
                    this.AddTreeToInsertionList(writer, nodeList, ref currentNodesIndex, 0, node.Children.ToArray());
                }
            }
        }

        private int CountNodesForInsertion(ScopeNode[] nodes)
        {
            int length = nodes.Length;
            Stack<ScopeNode> stack = new Stack<ScopeNode>();
            for (int i = 0; i < nodes.Length; i++)
            {
                ScopeNode item = nodes[i];
                if (item.Children.Count > 0)
                {
                    stack.Push(item);
                }
            }
            while (stack.Count > 0)
            {
                ScopeNode node2 = stack.Pop();
                length += node2.Children.Count;
                foreach (ScopeNode node3 in node2.Children)
                {
                    if (node3.Children.Count > 0)
                    {
                        stack.Push(node3);
                    }
                }
            }
            return length;
        }

        internal IMessageClient CreateView(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            ScopeNode node = this.GetNode(nodeId);
            if (node == null)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 12, "Node id:{0} not found. Cannot create view.", new object[] { nodeId });
                return null;
            }
            return node.ViewDescriptions.CreateView(viewDescriptionId, node, componentId, viewInstanceId);
        }

        internal void DeactivateNode(int scopeNodeId)
        {
            ScopeNode node = this.GetNode(scopeNodeId);
            if (node != null)
            {
                node.Deactivate();
            }
        }

        private ClipboardData[] GenerateClipboardData(ScopeNode node)
        {
            WritableSharedDataItem[] items = node.SharedData.GetItems();
            List<ClipboardData> list = new List<ClipboardData>();
            foreach (WritableSharedDataItem item in items)
            {
                if (!item.RequiresCallback)
                {
                    ClipboardData data = new ClipboardData();
                    data.ClipboardFormatId = item.ClipboardFormatId;
                    data.SetValue(item.GetData());
                    list.Add(data);
                }
            }
            if (list.Count > 0)
            {
                return list.ToArray();
            }
            return null;
        }

        private DataFormatConfiguration[] GenerateSharedDataFormatConfiguration(ScopeNode node)
        {
            DataFormatConfiguration[] configurationArray = null;
            WritableSharedDataItem[] items = node.SharedData.GetItems();
            if (items.Length > 0)
            {
                configurationArray = new DataFormatConfiguration[items.Length];
                for (int i = 0; i < items.Length; i++)
                {
                    configurationArray[i] = new DataFormatConfiguration();
                    configurationArray[i].RequiresQuery = items[i].RequiresCallback;
                    configurationArray[i].ClipboardFormatId = items[i].ClipboardFormatId;
                }
            }
            return configurationArray;
        }

        internal ScopeNode GetNode(int id)
        {
            ScopeNode node = null;
            if (!this._nodes.TryGetValue(id, out node))
            {
                node = null;
            }
            return node;
        }

        internal void Initialize(ISnapInPlatform snapInPlatform)
        {
            if (this._snapInPlatform != null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            if (snapInPlatform == null)
            {
                throw new ArgumentNullException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerInitializeNullPlatform));
            }
            this._snapInPlatform = snapInPlatform;
            this._initialized = true;
        }

        internal void OnNodeChanged(object sender, NodeChangedEventArgs e)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            if (!(e.Source is ScopeNode))
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerInvalidNodeType));
            }
            UpdateScopeNodeCommand command = new UpdateScopeNodeCommand();
            command.NodeData = (ScopeNodeData) e.Source.Data;
            ActionsPaneRootData data = new ActionsPaneRootData();
            data.Write(((ScopeNode) e.Source).ActionsPaneItems.Data);
            command.Actions = data;
            data = new ActionsPaneRootData();
            data.Write(((ScopeNode) e.Source).ActionsPaneHelpItems.Data);
            command.HelpActions = data;
            this._snapInPlatform.ProcessCommand(command);
        }

        internal void OnNodesChanged(object sender, ScopeNodeCollectionEventArgs e)
        {
            ScopeNode[] items = e.GetItems();
            if (items.Length != 0)
            {
                switch (e.ChangeType)
                {
                    case ScopeNodeCollectionChangeType.Add:
                        this.AddNodes(items, e.Index);
                        return;

                    case ScopeNodeCollectionChangeType.Remove:
                        this.RemoveNodes(items);
                        return;
                }
            }
        }

        internal void OnNodeSharedDataChanged(object sender, WritableSharedDataChangedEventArgs e)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            ScopeNode node = sender as ScopeNode;
            if (node == null)
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerOnNodeSharedDataChangedScopeNodeExpected), "sender");
            }
            WritableSharedDataItem sharedDataItem = e.SharedDataItem;
            if (sharedDataItem == null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerOnNodeSharedDataChangedWritableSharedDataItemExpected));
            }
            bool flag = false;
            UpdateScopeNodeCommand command = new UpdateScopeNodeCommand();
            command.NodeData = (ScopeNodeData) node.Data;
            ActionsPaneRootData data = new ActionsPaneRootData();
            data.Write(node.ActionsPaneItems.Data);
            command.Actions = data;
            data = new ActionsPaneRootData();
            data.Write(node.ActionsPaneHelpItems.Data);
            command.HelpActions = data;
            switch (e.ChangeType)
            {
                case WritableSharedDataChangeType.Add:
                case WritableSharedDataChangeType.Modify:
                {
                    DataFormatConfiguration configuration = new DataFormatConfiguration();
                    configuration.ClipboardFormatId = sharedDataItem.ClipboardFormatId;
                    configuration.RequiresQuery = sharedDataItem.RequiresCallback;
                    SharedDataObjectUpdate update = new SharedDataObjectUpdate();
                    if (!sharedDataItem.RequiresCallback)
                    {
                        ClipboardData data2 = new ClipboardData();
                        data2.ClipboardFormatId = sharedDataItem.ClipboardFormatId;
                        data2.SetValue(sharedDataItem.GetData());
                        ClipboardData[] updatedData = new ClipboardData[] { data2 };
                        update.SetUpdatedData(updatedData);
                    }
                    command.UpdatedSharedData = update;
                    if (e.ChangeType == WritableSharedDataChangeType.Add)
                    {
                        DataFormatConfiguration[] addedFormats = new DataFormatConfiguration[] { configuration };
                        command.UpdatedSharedData.SetAddedFormats(addedFormats);
                    }
                    else
                    {
                        DataFormatConfiguration[] changedFormats = new DataFormatConfiguration[] { configuration };
                        command.UpdatedSharedData.SetChangedFormats(changedFormats);
                    }
                    flag = true;
                    break;
                }
                case WritableSharedDataChangeType.Remove:
                    command.UpdatedSharedData.SetRemovedClipboardFormatIds(new string[] { sharedDataItem.ClipboardFormatId });
                    flag = true;
                    break;
            }
            if (flag)
            {
                this._snapInPlatform.ProcessCommand(command);
            }
        }

        internal void ProcessRequest(NodeRequestInfo info, IRequestStatus requestStatus)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            ScopeNode node = this.GetNode(info.ScopeNodeId);
            if (node != null)
            {
                if (info is ExpandScopeNodeRequestInfo)
                {
                    node.Expand(requestStatus);
                }
                else if (info is ActionNodeRequestInfo)
                {
                    node.DoAction(((ActionNodeRequestInfo) info).ActionId, requestStatus);
                }
                else if (info is ReadSharedDataNodeRequestInfo)
                {
                    node.GetSharedData((ReadSharedDataNodeRequestInfo) info, requestStatus);
                }
                else if (info is UpdateDataChangeNodeRequestInfo)
                {
                    node.RequestSharedDataUpdate((UpdateDataChangeNodeRequestInfo) info, requestStatus);
                }
                else if (info is PagesForNodeRequestInfo)
                {
                    node.GetPropertyPages(((PagesForNodeRequestInfo) info).SheetId, requestStatus);
                }
                else if ((((info is DeleteNodeRequestInfo) || (info is RefreshNodeRequestInfo)) || ((info is PrintNodeRequestInfo) || (info is RenameNodeRequestInfo))) || ((info is PasteNodeRequestInfo) || (info is CutOrMoveNodeRequestInfo)))
                {
                    node.DoVerb(info, requestStatus);
                }
                else if (info is ExpandFromLoadScopeNodeRequestInfo)
                {
                    ExpandFromLoadScopeNodeRequestResponse response = new ExpandFromLoadScopeNodeRequestResponse();
                    response.Handled = node.ExpandFromLoad(requestStatus);
                    requestStatus.ProcessResponse(response);
                }
                else if (info is ActivateNodeRequestInfo)
                {
                    node.Activate(requestStatus);
                }
            }
        }

        internal void RemoveNodes(ScopeNode[] items)
        {
            if (!this._initialized)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.NodeSyncManagerNotInitialized));
            }
            if (items.Length != 0)
            {
                List<ScopeNode> nodeList = new List<ScopeNode>();
                try
                {
                    int[] ids = new int[items.Length];
                    for (int i = 0; i < items.Length; i++)
                    {
                        ids[i] = items[i].Id;
                    }
                    this.AddTreeToDeletionList(nodeList, items);
                    DeleteScopeNodesCommand command = new DeleteScopeNodesCommand();
                    command.SetIds(ids);
                    this._snapInPlatform.ProcessCommand(command);
                }
                catch
                {
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "NodeSyncManager.RemoveNodes() failed");
                    throw;
                }
                foreach (ScopeNode node in nodeList)
                {
                    node.Children.ItemsChanged -= new ScopeNodeCollection.ScopeNodeCollectionEventHandler(this.OnNodesChanged);
                    node.Changed -= new Node.NodeChangedEventHandler(this.OnNodeChanged);
                    node.SharedDataChanged -= new ScopeNode.SharedDataChangedEventHandler(this.OnNodeSharedDataChanged);
                    this._nodes.Remove(node.Id);
                    node.OnNodeSyncManagerRemove();
                }
            }
        }
    }
}

