namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.IO;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class InsertScopeNodesCommandWriter : IDisposable
    {
        private int[] _Actions_Description_Count;
        private int[] _Actions_DisplayName_Count;
        private BooleanList _Actions_ExecuteSync = new BooleanList();
        private int[] _Actions_ExecuteSync_Count;
        private Int32List _Actions_Id = new Int32List();
        private int[] _Actions_Id_Count;
        private Int32List _Actions_ImageIndex = new Int32List();
        private int[] _Actions_ImageIndex_Count;
        private Int32List _Actions_InsertionLocation = new Int32List();
        private int[] _Actions_InsertionLocation_Count;
        private Int32List _Actions_ItemsCount = new Int32List();
        private int[] _Actions_ItemsCount_Count;
        private Int32List _Actions_ItemType = new Int32List();
        private int[] _Actions_ItemType_Count;
        private int[] _Actions_LanguageIndependentName_Count;
        private int[] _Actions_MnemonicDisplayName_Count;
        private BooleanList _Actions_RenderAsRegion = new BooleanList();
        private int[] _Actions_RenderAsRegion_Count;
        private Int32List _Actions_State = new Int32List();
        private int[] _Actions_State_Count;
        private int _currentIndex;
        private bool _disposed;
        private int[] _HelpActions_Description_Count;
        private int[] _HelpActions_DisplayName_Count;
        private BooleanList _HelpActions_ExecuteSync = new BooleanList();
        private int[] _HelpActions_ExecuteSync_Count;
        private Int32List _HelpActions_Id = new Int32List();
        private int[] _HelpActions_Id_Count;
        private Int32List _HelpActions_ImageIndex = new Int32List();
        private int[] _HelpActions_ImageIndex_Count;
        private Int32List _HelpActions_InsertionLocation = new Int32List();
        private int[] _HelpActions_InsertionLocation_Count;
        private Int32List _HelpActions_ItemsCount = new Int32List();
        private int[] _HelpActions_ItemsCount_Count;
        private Int32List _HelpActions_ItemType = new Int32List();
        private int[] _HelpActions_ItemType_Count;
        private int[] _HelpActions_LanguageIndependentName_Count;
        private int[] _HelpActions_MnemonicDisplayName_Count;
        private BooleanList _HelpActions_RenderAsRegion = new BooleanList();
        private int[] _HelpActions_RenderAsRegion_Count;
        private Int32List _HelpActions_State = new Int32List();
        private int[] _HelpActions_State_Count;
        private int[] _InitialSharedData_AddedFormats_Count;
        private BooleanList _InitialSharedData_AddedFormats_RequiresQuery = new BooleanList();
        private int[] _InitialSharedData_ChangedFormats_Count;
        private BooleanList _InitialSharedData_ChangedFormats_RequiresQuery = new BooleanList();
        private int[] _InitialSharedData_RemovedClipboardFormatIds_Count;
        private int[] _InitialSharedData_UpdatedData_Count;
        private ByteList _InitialSharedData_UpdatedData_Value = new ByteList();
        private Int32List _InitialSharedData_UpdatedData_Value_Count = new Int32List();
        private int[] _InsertionIndex;
        private int[] _NodeData_EnabledVerbs;
        private bool[] _NodeData_HideExpandIcon;
        private int[] _NodeData_Id;
        private int[] _NodeData_ImageIndex;
        private GuidList _NodeData_NodeType = new GuidList();
        private int[] _NodeData_NodeType_Id;
        private int[] _NodeData_PasteTargetInfo_AllowedClipboardFormats_Count;
        private int[] _NodeData_PasteTargetInfo_DefaultDragAndDropVerb;
        private int[] _NodeData_SelectedImageIndex;
        private bool[] _NodeData_SendActivation;
        private bool[] _NodeData_SendDeactivation;
        private int[] _NodeData_SubItems_Count;
        private int[] _NodeData_ViewSetId;
        private int[] _ParentScopeNodeId;
        private MemoryStream _stream_strings;
        private BinaryWriter _strings;
        private InsertScopeNodesCommand _target = new InsertScopeNodesCommand();

        public InsertScopeNodesCommandWriter(int capacity)
        {
            this._target.Count = capacity;
            this._ParentScopeNodeId = new int[capacity];
            this._InsertionIndex = new int[capacity];
            this._NodeData_NodeType_Id = new int[capacity];
            this._NodeData_SelectedImageIndex = new int[capacity];
            this._NodeData_HideExpandIcon = new bool[capacity];
            this._NodeData_SendActivation = new bool[capacity];
            this._NodeData_SendDeactivation = new bool[capacity];
            this._NodeData_ViewSetId = new int[capacity];
            this._NodeData_EnabledVerbs = new int[capacity];
            this._stream_strings = new MemoryStream();
            this._strings = new BinaryWriter(this._stream_strings);
            this._NodeData_PasteTargetInfo_DefaultDragAndDropVerb = new int[capacity];
            this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Count = new int[capacity];
            this._NodeData_Id = new int[capacity];
            this._NodeData_ImageIndex = new int[capacity];
            this._NodeData_SubItems_Count = new int[capacity];
            this._InitialSharedData_AddedFormats_Count = new int[capacity];
            this._InitialSharedData_ChangedFormats_Count = new int[capacity];
            this._InitialSharedData_UpdatedData_Count = new int[capacity];
            this._InitialSharedData_RemovedClipboardFormatIds_Count = new int[capacity];
            this._Actions_Id_Count = new int[capacity];
            this._Actions_ItemType_Count = new int[capacity];
            this._Actions_InsertionLocation_Count = new int[capacity];
            this._Actions_DisplayName_Count = new int[capacity];
            this._Actions_MnemonicDisplayName_Count = new int[capacity];
            this._Actions_Description_Count = new int[capacity];
            this._Actions_LanguageIndependentName_Count = new int[capacity];
            this._Actions_ImageIndex_Count = new int[capacity];
            this._Actions_State_Count = new int[capacity];
            this._Actions_ExecuteSync_Count = new int[capacity];
            this._Actions_RenderAsRegion_Count = new int[capacity];
            this._Actions_ItemsCount_Count = new int[capacity];
            this._HelpActions_Id_Count = new int[capacity];
            this._HelpActions_ItemType_Count = new int[capacity];
            this._HelpActions_InsertionLocation_Count = new int[capacity];
            this._HelpActions_DisplayName_Count = new int[capacity];
            this._HelpActions_MnemonicDisplayName_Count = new int[capacity];
            this._HelpActions_Description_Count = new int[capacity];
            this._HelpActions_LanguageIndependentName_Count = new int[capacity];
            this._HelpActions_ImageIndex_Count = new int[capacity];
            this._HelpActions_State_Count = new int[capacity];
            this._HelpActions_ExecuteSync_Count = new int[capacity];
            this._HelpActions_RenderAsRegion_Count = new int[capacity];
            this._HelpActions_ItemsCount_Count = new int[capacity];
        }

        public void Dispose()
        {
            if (!this._disposed)
            {
                this._disposed = true;
                this._strings.Close();
                this._stream_strings.Close();
            }
        }

        public InsertScopeNodesCommand Flush()
        {
            this._target.Set_ParentScopeNodeId(this._ParentScopeNodeId);
            this._target.Set_InsertionIndex(this._InsertionIndex);
            this._target.Set_NodeData_NodeType(this._NodeData_NodeType.ToArray());
            this._target.Set_NodeData_NodeType_Id(this._NodeData_NodeType_Id);
            this._target.Set_NodeData_SelectedImageIndex(this._NodeData_SelectedImageIndex);
            this._target.Set_NodeData_HideExpandIcon(this._NodeData_HideExpandIcon);
            this._target.Set_NodeData_SendActivation(this._NodeData_SendActivation);
            this._target.Set_NodeData_SendDeactivation(this._NodeData_SendDeactivation);
            this._target.Set_NodeData_ViewSetId(this._NodeData_ViewSetId);
            this._target.Set_NodeData_EnabledVerbs(this._NodeData_EnabledVerbs);
            this._target.Set_strings(this._stream_strings.GetBuffer());
            this._target.Set_NodeData_PasteTargetInfo_DefaultDragAndDropVerb(this._NodeData_PasteTargetInfo_DefaultDragAndDropVerb);
            this._target.Set_NodeData_PasteTargetInfo_AllowedClipboardFormats_Count(this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Count);
            this._target.Set_NodeData_Id(this._NodeData_Id);
            this._target.Set_NodeData_ImageIndex(this._NodeData_ImageIndex);
            this._target.Set_NodeData_SubItems_Count(this._NodeData_SubItems_Count);
            this._target.Set_InitialSharedData_AddedFormats_Count(this._InitialSharedData_AddedFormats_Count);
            this._target.Set_InitialSharedData_AddedFormats_RequiresQuery(this._InitialSharedData_AddedFormats_RequiresQuery.ToArray());
            this._target.Set_InitialSharedData_ChangedFormats_Count(this._InitialSharedData_ChangedFormats_Count);
            this._target.Set_InitialSharedData_ChangedFormats_RequiresQuery(this._InitialSharedData_ChangedFormats_RequiresQuery.ToArray());
            this._target.Set_InitialSharedData_UpdatedData_Count(this._InitialSharedData_UpdatedData_Count);
            this._target.Set_InitialSharedData_UpdatedData_Value(this._InitialSharedData_UpdatedData_Value.ToArray());
            this._target.Set_InitialSharedData_UpdatedData_Value_Count(this._InitialSharedData_UpdatedData_Value_Count.ToArray());
            this._target.Set_InitialSharedData_RemovedClipboardFormatIds_Count(this._InitialSharedData_RemovedClipboardFormatIds_Count);
            this._target.Set_Actions_Id(this._Actions_Id.ToArray());
            this._target.Set_Actions_Id_Count(this._Actions_Id_Count);
            this._target.Set_Actions_ItemType_Count(this._Actions_ItemType_Count);
            this._target.Set_Actions_ItemType(this._Actions_ItemType.ToArray());
            this._target.Set_Actions_InsertionLocation_Count(this._Actions_InsertionLocation_Count);
            this._target.Set_Actions_InsertionLocation(this._Actions_InsertionLocation.ToArray());
            this._target.Set_Actions_DisplayName_Count(this._Actions_DisplayName_Count);
            this._target.Set_Actions_MnemonicDisplayName_Count(this._Actions_MnemonicDisplayName_Count);
            this._target.Set_Actions_Description_Count(this._Actions_Description_Count);
            this._target.Set_Actions_LanguageIndependentName_Count(this._Actions_LanguageIndependentName_Count);
            this._target.Set_Actions_ImageIndex(this._Actions_ImageIndex.ToArray());
            this._target.Set_Actions_ImageIndex_Count(this._Actions_ImageIndex_Count);
            this._target.Set_Actions_State_Count(this._Actions_State_Count);
            this._target.Set_Actions_State(this._Actions_State.ToArray());
            this._target.Set_Actions_ExecuteSync(this._Actions_ExecuteSync.ToArray());
            this._target.Set_Actions_ExecuteSync_Count(this._Actions_ExecuteSync_Count);
            this._target.Set_Actions_RenderAsRegion(this._Actions_RenderAsRegion.ToArray());
            this._target.Set_Actions_RenderAsRegion_Count(this._Actions_RenderAsRegion_Count);
            this._target.Set_Actions_ItemsCount(this._Actions_ItemsCount.ToArray());
            this._target.Set_Actions_ItemsCount_Count(this._Actions_ItemsCount_Count);
            this._target.Set_HelpActions_Id(this._HelpActions_Id.ToArray());
            this._target.Set_HelpActions_Id_Count(this._HelpActions_Id_Count);
            this._target.Set_HelpActions_ItemType_Count(this._HelpActions_ItemType_Count);
            this._target.Set_HelpActions_ItemType(this._HelpActions_ItemType.ToArray());
            this._target.Set_HelpActions_InsertionLocation_Count(this._HelpActions_InsertionLocation_Count);
            this._target.Set_HelpActions_InsertionLocation(this._HelpActions_InsertionLocation.ToArray());
            this._target.Set_HelpActions_DisplayName_Count(this._HelpActions_DisplayName_Count);
            this._target.Set_HelpActions_MnemonicDisplayName_Count(this._HelpActions_MnemonicDisplayName_Count);
            this._target.Set_HelpActions_Description_Count(this._HelpActions_Description_Count);
            this._target.Set_HelpActions_LanguageIndependentName_Count(this._HelpActions_LanguageIndependentName_Count);
            this._target.Set_HelpActions_ImageIndex(this._HelpActions_ImageIndex.ToArray());
            this._target.Set_HelpActions_ImageIndex_Count(this._HelpActions_ImageIndex_Count);
            this._target.Set_HelpActions_State_Count(this._HelpActions_State_Count);
            this._target.Set_HelpActions_State(this._HelpActions_State.ToArray());
            this._target.Set_HelpActions_ExecuteSync(this._HelpActions_ExecuteSync.ToArray());
            this._target.Set_HelpActions_ExecuteSync_Count(this._HelpActions_ExecuteSync_Count);
            this._target.Set_HelpActions_RenderAsRegion(this._HelpActions_RenderAsRegion.ToArray());
            this._target.Set_HelpActions_RenderAsRegion_Count(this._HelpActions_RenderAsRegion_Count);
            this._target.Set_HelpActions_ItemsCount(this._HelpActions_ItemsCount.ToArray());
            this._target.Set_HelpActions_ItemsCount_Count(this._HelpActions_ItemsCount_Count);
            return this._target;
        }

        private void WriteNextActions(ActionsPaneRootData obj)
        {
            int[] id = obj.GetId();
            int length = -1;
            if (id != null)
            {
                this._Actions_Id.AddRange(id);
                length = id.Length;
            }
            this._Actions_Id_Count[this._currentIndex] = length;
            ActionsPaneRootItemType[] itemType = obj.GetItemType();
            int num2 = -1;
            if (itemType != null)
            {
                num2 = itemType.Length;
                int index = 0;
                for (index = 0; index < num2; index++)
                {
                    this._Actions_ItemType.Add((int) itemType[index]);
                }
            }
            this._Actions_ItemType_Count[this._currentIndex] = num2;
            ActionsInsertionLocation[] insertionLocation = obj.GetInsertionLocation();
            int num4 = -1;
            if (insertionLocation != null)
            {
                num4 = insertionLocation.Length;
                int num5 = 0;
                for (num5 = 0; num5 < num4; num5++)
                {
                    this._Actions_InsertionLocation.Add((int) insertionLocation[num5]);
                }
            }
            this._Actions_InsertionLocation_Count[this._currentIndex] = num4;
            string[] displayName = obj.GetDisplayName();
            int num6 = -1;
            if (displayName != null)
            {
                num6 = displayName.Length;
                int num7 = 0;
                for (num7 = 0; num7 < num6; num7++)
                {
                    this.WriteString(displayName[num7]);
                }
            }
            this._Actions_DisplayName_Count[this._currentIndex] = num6;
            string[] mnemonicDisplayName = obj.GetMnemonicDisplayName();
            int num8 = -1;
            if (mnemonicDisplayName != null)
            {
                num8 = mnemonicDisplayName.Length;
                int num9 = 0;
                for (num9 = 0; num9 < num8; num9++)
                {
                    this.WriteString(mnemonicDisplayName[num9]);
                }
            }
            this._Actions_MnemonicDisplayName_Count[this._currentIndex] = num8;
            string[] description = obj.GetDescription();
            int num10 = -1;
            if (description != null)
            {
                num10 = description.Length;
                int num11 = 0;
                for (num11 = 0; num11 < num10; num11++)
                {
                    this.WriteString(description[num11]);
                }
            }
            this._Actions_Description_Count[this._currentIndex] = num10;
            string[] languageIndependentName = obj.GetLanguageIndependentName();
            int num12 = -1;
            if (languageIndependentName != null)
            {
                num12 = languageIndependentName.Length;
                int num13 = 0;
                for (num13 = 0; num13 < num12; num13++)
                {
                    this.WriteString(languageIndependentName[num13]);
                }
            }
            this._Actions_LanguageIndependentName_Count[this._currentIndex] = num12;
            int[] imageIndex = obj.GetImageIndex();
            int num14 = -1;
            if (imageIndex != null)
            {
                this._Actions_ImageIndex.AddRange(imageIndex);
                num14 = imageIndex.Length;
            }
            this._Actions_ImageIndex_Count[this._currentIndex] = num14;
            ActionStates[] state = obj.GetState();
            int num15 = -1;
            if (state != null)
            {
                num15 = state.Length;
                int num16 = 0;
                for (num16 = 0; num16 < num15; num16++)
                {
                    this._Actions_State.Add((int) state[num16]);
                }
            }
            this._Actions_State_Count[this._currentIndex] = num15;
            bool[] executeSync = obj.GetExecuteSync();
            int num17 = -1;
            if (executeSync != null)
            {
                this._Actions_ExecuteSync.AddRange(executeSync);
                num17 = executeSync.Length;
            }
            this._Actions_ExecuteSync_Count[this._currentIndex] = num17;
            bool[] renderAsRegion = obj.GetRenderAsRegion();
            int num18 = -1;
            if (renderAsRegion != null)
            {
                this._Actions_RenderAsRegion.AddRange(renderAsRegion);
                num18 = renderAsRegion.Length;
            }
            this._Actions_RenderAsRegion_Count[this._currentIndex] = num18;
            int[] itemsCount = obj.GetItemsCount();
            int num19 = -1;
            if (itemsCount != null)
            {
                this._Actions_ItemsCount.AddRange(itemsCount);
                num19 = itemsCount.Length;
            }
            this._Actions_ItemsCount_Count[this._currentIndex] = num19;
        }

        private void WriteNextAddedFormats(DataFormatConfiguration obj)
        {
            this.WriteString(obj.ClipboardFormatId);
            this._InitialSharedData_AddedFormats_RequiresQuery.Add(obj.RequiresQuery);
        }

        private void WriteNextChangedFormats(DataFormatConfiguration obj)
        {
            this.WriteString(obj.ClipboardFormatId);
            this._InitialSharedData_ChangedFormats_RequiresQuery.Add(obj.RequiresQuery);
        }

        private void WriteNextHelpActions(ActionsPaneRootData obj)
        {
            int[] id = obj.GetId();
            int length = -1;
            if (id != null)
            {
                this._HelpActions_Id.AddRange(id);
                length = id.Length;
            }
            this._HelpActions_Id_Count[this._currentIndex] = length;
            ActionsPaneRootItemType[] itemType = obj.GetItemType();
            int num2 = -1;
            if (itemType != null)
            {
                num2 = itemType.Length;
                int index = 0;
                for (index = 0; index < num2; index++)
                {
                    this._HelpActions_ItemType.Add((int) itemType[index]);
                }
            }
            this._HelpActions_ItemType_Count[this._currentIndex] = num2;
            ActionsInsertionLocation[] insertionLocation = obj.GetInsertionLocation();
            int num4 = -1;
            if (insertionLocation != null)
            {
                num4 = insertionLocation.Length;
                int num5 = 0;
                for (num5 = 0; num5 < num4; num5++)
                {
                    this._HelpActions_InsertionLocation.Add((int) insertionLocation[num5]);
                }
            }
            this._HelpActions_InsertionLocation_Count[this._currentIndex] = num4;
            string[] displayName = obj.GetDisplayName();
            int num6 = -1;
            if (displayName != null)
            {
                num6 = displayName.Length;
                int num7 = 0;
                for (num7 = 0; num7 < num6; num7++)
                {
                    this.WriteString(displayName[num7]);
                }
            }
            this._HelpActions_DisplayName_Count[this._currentIndex] = num6;
            string[] mnemonicDisplayName = obj.GetMnemonicDisplayName();
            int num8 = -1;
            if (mnemonicDisplayName != null)
            {
                num8 = mnemonicDisplayName.Length;
                int num9 = 0;
                for (num9 = 0; num9 < num8; num9++)
                {
                    this.WriteString(mnemonicDisplayName[num9]);
                }
            }
            this._HelpActions_MnemonicDisplayName_Count[this._currentIndex] = num8;
            string[] description = obj.GetDescription();
            int num10 = -1;
            if (description != null)
            {
                num10 = description.Length;
                int num11 = 0;
                for (num11 = 0; num11 < num10; num11++)
                {
                    this.WriteString(description[num11]);
                }
            }
            this._HelpActions_Description_Count[this._currentIndex] = num10;
            string[] languageIndependentName = obj.GetLanguageIndependentName();
            int num12 = -1;
            if (languageIndependentName != null)
            {
                num12 = languageIndependentName.Length;
                int num13 = 0;
                for (num13 = 0; num13 < num12; num13++)
                {
                    this.WriteString(languageIndependentName[num13]);
                }
            }
            this._HelpActions_LanguageIndependentName_Count[this._currentIndex] = num12;
            int[] imageIndex = obj.GetImageIndex();
            int num14 = -1;
            if (imageIndex != null)
            {
                this._HelpActions_ImageIndex.AddRange(imageIndex);
                num14 = imageIndex.Length;
            }
            this._HelpActions_ImageIndex_Count[this._currentIndex] = num14;
            ActionStates[] state = obj.GetState();
            int num15 = -1;
            if (state != null)
            {
                num15 = state.Length;
                int num16 = 0;
                for (num16 = 0; num16 < num15; num16++)
                {
                    this._HelpActions_State.Add((int) state[num16]);
                }
            }
            this._HelpActions_State_Count[this._currentIndex] = num15;
            bool[] executeSync = obj.GetExecuteSync();
            int num17 = -1;
            if (executeSync != null)
            {
                this._HelpActions_ExecuteSync.AddRange(executeSync);
                num17 = executeSync.Length;
            }
            this._HelpActions_ExecuteSync_Count[this._currentIndex] = num17;
            bool[] renderAsRegion = obj.GetRenderAsRegion();
            int num18 = -1;
            if (renderAsRegion != null)
            {
                this._HelpActions_RenderAsRegion.AddRange(renderAsRegion);
                num18 = renderAsRegion.Length;
            }
            this._HelpActions_RenderAsRegion_Count[this._currentIndex] = num18;
            int[] itemsCount = obj.GetItemsCount();
            int num19 = -1;
            if (itemsCount != null)
            {
                this._HelpActions_ItemsCount.AddRange(itemsCount);
                num19 = itemsCount.Length;
            }
            this._HelpActions_ItemsCount_Count[this._currentIndex] = num19;
        }

        private void WriteNextInitialSharedData(SharedDataObjectUpdate obj)
        {
            DataFormatConfiguration[] addedFormats = obj.GetAddedFormats();
            int length = -1;
            if (addedFormats != null)
            {
                length = addedFormats.Length;
                int index = 0;
                for (index = 0; index < length; index++)
                {
                    this.WriteNextAddedFormats(addedFormats[index]);
                }
            }
            this._InitialSharedData_AddedFormats_Count[this._currentIndex] = length;
            DataFormatConfiguration[] changedFormats = obj.GetChangedFormats();
            int num3 = -1;
            if (changedFormats != null)
            {
                num3 = changedFormats.Length;
                int num4 = 0;
                for (num4 = 0; num4 < num3; num4++)
                {
                    this.WriteNextChangedFormats(changedFormats[num4]);
                }
            }
            this._InitialSharedData_ChangedFormats_Count[this._currentIndex] = num3;
            ClipboardData[] updatedData = obj.GetUpdatedData();
            int num5 = -1;
            if (updatedData != null)
            {
                num5 = updatedData.Length;
                int num6 = 0;
                for (num6 = 0; num6 < num5; num6++)
                {
                    this.WriteNextUpdatedData(updatedData[num6]);
                }
            }
            this._InitialSharedData_UpdatedData_Count[this._currentIndex] = num5;
            string[] removedClipboardFormatIds = obj.GetRemovedClipboardFormatIds();
            int num7 = -1;
            if (removedClipboardFormatIds != null)
            {
                num7 = removedClipboardFormatIds.Length;
                int num8 = 0;
                for (num8 = 0; num8 < num7; num8++)
                {
                    this.WriteString(removedClipboardFormatIds[num8]);
                }
            }
            this._InitialSharedData_RemovedClipboardFormatIds_Count[this._currentIndex] = num7;
        }

        private void WriteNextNodeData(ScopeNodeData obj)
        {
            Guid nodeType = obj.NodeType;
            int index = this._NodeData_NodeType.IndexOf(nodeType);
            if (index < 0)
            {
                index = this._NodeData_NodeType.Count;
                this._NodeData_NodeType.Add(nodeType);
            }
            this._NodeData_NodeType_Id[this._currentIndex] = index;
            this._NodeData_SelectedImageIndex[this._currentIndex] = obj.SelectedImageIndex;
            this._NodeData_HideExpandIcon[this._currentIndex] = obj.HideExpandIcon;
            this._NodeData_SendActivation[this._currentIndex] = obj.SendActivation;
            this._NodeData_SendDeactivation[this._currentIndex] = obj.SendDeactivation;
            this._NodeData_ViewSetId[this._currentIndex] = obj.ViewSetId;
            this._NodeData_EnabledVerbs[this._currentIndex] = (int) obj.EnabledVerbs;
            this.WriteString(obj.LanguageIndependentName);
            this.WriteString(obj.HelpTopic);
            this.WriteNextPasteTargetInfo(obj.PasteTargetInfo);
            this._NodeData_Id[this._currentIndex] = obj.Id;
            this._NodeData_ImageIndex[this._currentIndex] = obj.ImageIndex;
            this.WriteString(obj.DisplayName);
            NodeSubItemData[] subItems = obj.GetSubItems();
            int length = -1;
            if (subItems != null)
            {
                length = subItems.Length;
                int num3 = 0;
                for (num3 = 0; num3 < length; num3++)
                {
                    this.WriteNextSubItems(subItems[num3]);
                }
            }
            this._NodeData_SubItems_Count[this._currentIndex] = length;
        }

        private void WriteNextPasteTargetInfo(PasteTargetInfo obj)
        {
            this._NodeData_PasteTargetInfo_DefaultDragAndDropVerb[this._currentIndex] = (int) obj.DefaultDragAndDropVerb;
            string[] allowedClipboardFormats = obj.GetAllowedClipboardFormats();
            int length = -1;
            if (allowedClipboardFormats != null)
            {
                length = allowedClipboardFormats.Length;
                int index = 0;
                for (index = 0; index < length; index++)
                {
                    this.WriteString(allowedClipboardFormats[index]);
                }
            }
            this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Count[this._currentIndex] = length;
        }

        private void WriteNextSubItems(NodeSubItemData obj)
        {
            this.WriteString(obj.DisplayName);
        }

        private void WriteNextUpdatedData(ClipboardData obj)
        {
            this.WriteString(obj.ClipboardFormatId);
            byte[] items = obj.GetValue();
            int item = -1;
            if (items != null)
            {
                this._InitialSharedData_UpdatedData_Value.AddRange(items);
                item = items.Length;
            }
            this._InitialSharedData_UpdatedData_Value_Count.Add(item);
        }

        public void WriteScopeNodeInsert(ScopeNodeInsert obj)
        {
            if (this._currentIndex >= this._target.Count)
            {
                throw new EndOfStreamException();
            }
            this._ParentScopeNodeId[this._currentIndex] = obj.ParentScopeNodeId;
            this._InsertionIndex[this._currentIndex] = obj.InsertionIndex;
            this.WriteNextNodeData(obj.NodeData);
            this.WriteNextInitialSharedData(obj.InitialSharedData);
            this.WriteNextActions(obj.Actions);
            this.WriteNextHelpActions(obj.HelpActions);
            this._currentIndex++;
        }

        private void WriteString(string value)
        {
            if (value == null)
            {
                value = string.Empty;
            }
            this._strings.Write(value);
        }
    }
}

