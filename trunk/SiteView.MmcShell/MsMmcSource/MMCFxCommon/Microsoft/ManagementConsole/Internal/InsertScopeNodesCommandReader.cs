namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.IO;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class InsertScopeNodesCommandReader : IDisposable
    {
        private int _Actions_Description_Offset;
        private int _Actions_DisplayName_Offset;
        private int _Actions_ExecuteSync_Offset;
        private int _Actions_Id_Offset;
        private int _Actions_ImageIndex_Offset;
        private int _Actions_InsertionLocation_Offset;
        private int _Actions_ItemsCount_Offset;
        private int _Actions_ItemType_Offset;
        private int _Actions_LanguageIndependentName_Offset;
        private int _Actions_MnemonicDisplayName_Offset;
        private int _Actions_RenderAsRegion_Offset;
        private int _Actions_State_Offset;
        private int _currentIndex;
        private bool _disposed;
        private int _HelpActions_Description_Offset;
        private int _HelpActions_DisplayName_Offset;
        private int _HelpActions_ExecuteSync_Offset;
        private int _HelpActions_Id_Offset;
        private int _HelpActions_ImageIndex_Offset;
        private int _HelpActions_InsertionLocation_Offset;
        private int _HelpActions_ItemsCount_Offset;
        private int _HelpActions_ItemType_Offset;
        private int _HelpActions_LanguageIndependentName_Offset;
        private int _HelpActions_MnemonicDisplayName_Offset;
        private int _HelpActions_RenderAsRegion_Offset;
        private int _HelpActions_State_Offset;
        private int _InitialSharedData_AddedFormats_Offset;
        private int _InitialSharedData_ChangedFormats_Offset;
        private int _InitialSharedData_RemovedClipboardFormatIds_Offset;
        private int _InitialSharedData_UpdatedData_Offset;
        private int _InitialSharedData_UpdatedData_Value_Offset;
        private int _NodeData_PasteTargetInfo_AllowedClipboardFormats_Offset;
        private int _NodeData_SubItems_Offset;
        private InsertScopeNodesCommand _source;
        private BinaryReader _strings;

        public InsertScopeNodesCommandReader(InsertScopeNodesCommand source)
        {
            this._source = source;
            this._strings = new BinaryReader(new MemoryStream(this._source.Get_strings()));
        }

        public void Dispose()
        {
            if (!this._disposed)
            {
                this._disposed = true;
                this._strings.Close();
            }
        }

        private ActionsPaneRootData ReadNextActions()
        {
            ActionsPaneRootData data = new ActionsPaneRootData();
            int length = this._source.Get_Actions_Id_Count()[this._currentIndex];
            int[] destinationArray = null;
            if (length >= 0)
            {
                destinationArray = new int[length];
                Array.Copy(this._source.Get_Actions_Id(), this._Actions_Id_Offset, destinationArray, 0, length);
                this._Actions_Id_Offset += length;
            }
            data.SetId(destinationArray);
            int num2 = this._source.Get_Actions_ItemType_Count()[this._currentIndex];
            ActionsPaneRootItemType[] typeArray = null;
            if (num2 >= 0)
            {
                typeArray = new ActionsPaneRootItemType[num2];
            }
            int index = 0;
            for (index = 0; index < num2; index++)
            {
                typeArray[index] = (ActionsPaneRootItemType) this._source.Get_Actions_ItemType()[this._Actions_ItemType_Offset];
                this._Actions_ItemType_Offset++;
            }
            data.SetItemType(typeArray);
            int num4 = this._source.Get_Actions_InsertionLocation_Count()[this._currentIndex];
            ActionsInsertionLocation[] locationArray = null;
            if (num4 >= 0)
            {
                locationArray = new ActionsInsertionLocation[num4];
            }
            int num5 = 0;
            for (num5 = 0; num5 < num4; num5++)
            {
                locationArray[num5] = (ActionsInsertionLocation) this._source.Get_Actions_InsertionLocation()[this._Actions_InsertionLocation_Offset];
                this._Actions_InsertionLocation_Offset++;
            }
            data.SetInsertionLocation(locationArray);
            int num6 = this._source.Get_Actions_DisplayName_Count()[this._currentIndex];
            string[] strArray = null;
            if (num6 >= 0)
            {
                strArray = new string[num6];
            }
            int num7 = 0;
            for (num7 = 0; num7 < num6; num7++)
            {
                strArray[num7] = this._strings.ReadString();
                this._Actions_DisplayName_Offset++;
            }
            data.SetDisplayName(strArray);
            int num8 = this._source.Get_Actions_MnemonicDisplayName_Count()[this._currentIndex];
            string[] strArray2 = null;
            if (num8 >= 0)
            {
                strArray2 = new string[num8];
            }
            int num9 = 0;
            for (num9 = 0; num9 < num8; num9++)
            {
                strArray2[num9] = this._strings.ReadString();
                this._Actions_MnemonicDisplayName_Offset++;
            }
            data.SetMnemonicDisplayName(strArray2);
            int num10 = this._source.Get_Actions_Description_Count()[this._currentIndex];
            string[] strArray3 = null;
            if (num10 >= 0)
            {
                strArray3 = new string[num10];
            }
            int num11 = 0;
            for (num11 = 0; num11 < num10; num11++)
            {
                strArray3[num11] = this._strings.ReadString();
                this._Actions_Description_Offset++;
            }
            data.SetDescription(strArray3);
            int num12 = this._source.Get_Actions_LanguageIndependentName_Count()[this._currentIndex];
            string[] strArray4 = null;
            if (num12 >= 0)
            {
                strArray4 = new string[num12];
            }
            int num13 = 0;
            for (num13 = 0; num13 < num12; num13++)
            {
                strArray4[num13] = this._strings.ReadString();
                this._Actions_LanguageIndependentName_Offset++;
            }
            data.SetLanguageIndependentName(strArray4);
            int num14 = this._source.Get_Actions_ImageIndex_Count()[this._currentIndex];
            int[] numArray2 = null;
            if (num14 >= 0)
            {
                numArray2 = new int[num14];
                Array.Copy(this._source.Get_Actions_ImageIndex(), this._Actions_ImageIndex_Offset, numArray2, 0, num14);
                this._Actions_ImageIndex_Offset += num14;
            }
            data.SetImageIndex(numArray2);
            int num15 = this._source.Get_Actions_State_Count()[this._currentIndex];
            ActionStates[] statesArray = null;
            if (num15 >= 0)
            {
                statesArray = new ActionStates[num15];
            }
            int num16 = 0;
            for (num16 = 0; num16 < num15; num16++)
            {
                statesArray[num16] = (ActionStates) this._source.Get_Actions_State()[this._Actions_State_Offset];
                this._Actions_State_Offset++;
            }
            data.SetState(statesArray);
            int num17 = this._source.Get_Actions_ExecuteSync_Count()[this._currentIndex];
            bool[] flagArray = null;
            if (num17 >= 0)
            {
                flagArray = new bool[num17];
                Array.Copy(this._source.Get_Actions_ExecuteSync(), this._Actions_ExecuteSync_Offset, flagArray, 0, num17);
                this._Actions_ExecuteSync_Offset += num17;
            }
            data.SetExecuteSync(flagArray);
            int num18 = this._source.Get_Actions_RenderAsRegion_Count()[this._currentIndex];
            bool[] flagArray2 = null;
            if (num18 >= 0)
            {
                flagArray2 = new bool[num18];
                Array.Copy(this._source.Get_Actions_RenderAsRegion(), this._Actions_RenderAsRegion_Offset, flagArray2, 0, num18);
                this._Actions_RenderAsRegion_Offset += num18;
            }
            data.SetRenderAsRegion(flagArray2);
            int num19 = this._source.Get_Actions_ItemsCount_Count()[this._currentIndex];
            int[] numArray3 = null;
            if (num19 >= 0)
            {
                numArray3 = new int[num19];
                Array.Copy(this._source.Get_Actions_ItemsCount(), this._Actions_ItemsCount_Offset, numArray3, 0, num19);
                this._Actions_ItemsCount_Offset += num19;
            }
            data.SetItemsCount(numArray3);
            return data;
        }

        private DataFormatConfiguration ReadNextAddedFormats()
        {
            DataFormatConfiguration configuration = new DataFormatConfiguration();
            configuration.ClipboardFormatId = this._strings.ReadString();
            configuration.RequiresQuery = this._source.Get_InitialSharedData_AddedFormats_RequiresQuery()[this._InitialSharedData_AddedFormats_Offset];
            return configuration;
        }

        private DataFormatConfiguration ReadNextChangedFormats()
        {
            DataFormatConfiguration configuration = new DataFormatConfiguration();
            configuration.ClipboardFormatId = this._strings.ReadString();
            configuration.RequiresQuery = this._source.Get_InitialSharedData_ChangedFormats_RequiresQuery()[this._InitialSharedData_ChangedFormats_Offset];
            return configuration;
        }

        private ActionsPaneRootData ReadNextHelpActions()
        {
            ActionsPaneRootData data = new ActionsPaneRootData();
            int length = this._source.Get_HelpActions_Id_Count()[this._currentIndex];
            int[] destinationArray = null;
            if (length >= 0)
            {
                destinationArray = new int[length];
                Array.Copy(this._source.Get_HelpActions_Id(), this._HelpActions_Id_Offset, destinationArray, 0, length);
                this._HelpActions_Id_Offset += length;
            }
            data.SetId(destinationArray);
            int num2 = this._source.Get_HelpActions_ItemType_Count()[this._currentIndex];
            ActionsPaneRootItemType[] typeArray = null;
            if (num2 >= 0)
            {
                typeArray = new ActionsPaneRootItemType[num2];
            }
            int index = 0;
            for (index = 0; index < num2; index++)
            {
                typeArray[index] = (ActionsPaneRootItemType) this._source.Get_HelpActions_ItemType()[this._HelpActions_ItemType_Offset];
                this._HelpActions_ItemType_Offset++;
            }
            data.SetItemType(typeArray);
            int num4 = this._source.Get_HelpActions_InsertionLocation_Count()[this._currentIndex];
            ActionsInsertionLocation[] locationArray = null;
            if (num4 >= 0)
            {
                locationArray = new ActionsInsertionLocation[num4];
            }
            int num5 = 0;
            for (num5 = 0; num5 < num4; num5++)
            {
                locationArray[num5] = (ActionsInsertionLocation) this._source.Get_HelpActions_InsertionLocation()[this._HelpActions_InsertionLocation_Offset];
                this._HelpActions_InsertionLocation_Offset++;
            }
            data.SetInsertionLocation(locationArray);
            int num6 = this._source.Get_HelpActions_DisplayName_Count()[this._currentIndex];
            string[] strArray = null;
            if (num6 >= 0)
            {
                strArray = new string[num6];
            }
            int num7 = 0;
            for (num7 = 0; num7 < num6; num7++)
            {
                strArray[num7] = this._strings.ReadString();
                this._HelpActions_DisplayName_Offset++;
            }
            data.SetDisplayName(strArray);
            int num8 = this._source.Get_HelpActions_MnemonicDisplayName_Count()[this._currentIndex];
            string[] strArray2 = null;
            if (num8 >= 0)
            {
                strArray2 = new string[num8];
            }
            int num9 = 0;
            for (num9 = 0; num9 < num8; num9++)
            {
                strArray2[num9] = this._strings.ReadString();
                this._HelpActions_MnemonicDisplayName_Offset++;
            }
            data.SetMnemonicDisplayName(strArray2);
            int num10 = this._source.Get_HelpActions_Description_Count()[this._currentIndex];
            string[] strArray3 = null;
            if (num10 >= 0)
            {
                strArray3 = new string[num10];
            }
            int num11 = 0;
            for (num11 = 0; num11 < num10; num11++)
            {
                strArray3[num11] = this._strings.ReadString();
                this._HelpActions_Description_Offset++;
            }
            data.SetDescription(strArray3);
            int num12 = this._source.Get_HelpActions_LanguageIndependentName_Count()[this._currentIndex];
            string[] strArray4 = null;
            if (num12 >= 0)
            {
                strArray4 = new string[num12];
            }
            int num13 = 0;
            for (num13 = 0; num13 < num12; num13++)
            {
                strArray4[num13] = this._strings.ReadString();
                this._HelpActions_LanguageIndependentName_Offset++;
            }
            data.SetLanguageIndependentName(strArray4);
            int num14 = this._source.Get_HelpActions_ImageIndex_Count()[this._currentIndex];
            int[] numArray2 = null;
            if (num14 >= 0)
            {
                numArray2 = new int[num14];
                Array.Copy(this._source.Get_HelpActions_ImageIndex(), this._HelpActions_ImageIndex_Offset, numArray2, 0, num14);
                this._HelpActions_ImageIndex_Offset += num14;
            }
            data.SetImageIndex(numArray2);
            int num15 = this._source.Get_HelpActions_State_Count()[this._currentIndex];
            ActionStates[] statesArray = null;
            if (num15 >= 0)
            {
                statesArray = new ActionStates[num15];
            }
            int num16 = 0;
            for (num16 = 0; num16 < num15; num16++)
            {
                statesArray[num16] = (ActionStates) this._source.Get_HelpActions_State()[this._HelpActions_State_Offset];
                this._HelpActions_State_Offset++;
            }
            data.SetState(statesArray);
            int num17 = this._source.Get_HelpActions_ExecuteSync_Count()[this._currentIndex];
            bool[] flagArray = null;
            if (num17 >= 0)
            {
                flagArray = new bool[num17];
                Array.Copy(this._source.Get_HelpActions_ExecuteSync(), this._HelpActions_ExecuteSync_Offset, flagArray, 0, num17);
                this._HelpActions_ExecuteSync_Offset += num17;
            }
            data.SetExecuteSync(flagArray);
            int num18 = this._source.Get_HelpActions_RenderAsRegion_Count()[this._currentIndex];
            bool[] flagArray2 = null;
            if (num18 >= 0)
            {
                flagArray2 = new bool[num18];
                Array.Copy(this._source.Get_HelpActions_RenderAsRegion(), this._HelpActions_RenderAsRegion_Offset, flagArray2, 0, num18);
                this._HelpActions_RenderAsRegion_Offset += num18;
            }
            data.SetRenderAsRegion(flagArray2);
            int num19 = this._source.Get_HelpActions_ItemsCount_Count()[this._currentIndex];
            int[] numArray3 = null;
            if (num19 >= 0)
            {
                numArray3 = new int[num19];
                Array.Copy(this._source.Get_HelpActions_ItemsCount(), this._HelpActions_ItemsCount_Offset, numArray3, 0, num19);
                this._HelpActions_ItemsCount_Offset += num19;
            }
            data.SetItemsCount(numArray3);
            return data;
        }

        private void ReadNextInitialSharedData(SharedDataObjectUpdate obj)
        {
            int num = this._source.Get_InitialSharedData_AddedFormats_Count()[this._currentIndex];
            DataFormatConfiguration[] addedFormats = null;
            if (num >= 0)
            {
                addedFormats = new DataFormatConfiguration[num];
            }
            int index = 0;
            for (index = 0; index < num; index++)
            {
                addedFormats[index] = this.ReadNextAddedFormats();
                this._InitialSharedData_AddedFormats_Offset++;
            }
            obj.SetAddedFormats(addedFormats);
            int num3 = this._source.Get_InitialSharedData_ChangedFormats_Count()[this._currentIndex];
            DataFormatConfiguration[] changedFormats = null;
            if (num3 >= 0)
            {
                changedFormats = new DataFormatConfiguration[num3];
            }
            int num4 = 0;
            for (num4 = 0; num4 < num3; num4++)
            {
                changedFormats[num4] = this.ReadNextChangedFormats();
                this._InitialSharedData_ChangedFormats_Offset++;
            }
            obj.SetChangedFormats(changedFormats);
            int num5 = this._source.Get_InitialSharedData_UpdatedData_Count()[this._currentIndex];
            ClipboardData[] updatedData = null;
            if (num5 >= 0)
            {
                updatedData = new ClipboardData[num5];
            }
            int num6 = 0;
            for (num6 = 0; num6 < num5; num6++)
            {
                updatedData[num6] = this.ReadNextUpdatedData();
                this._InitialSharedData_UpdatedData_Offset++;
            }
            obj.SetUpdatedData(updatedData);
            int num7 = this._source.Get_InitialSharedData_RemovedClipboardFormatIds_Count()[this._currentIndex];
            string[] removedClipboardFormatIds = null;
            if (num7 >= 0)
            {
                removedClipboardFormatIds = new string[num7];
            }
            int num8 = 0;
            for (num8 = 0; num8 < num7; num8++)
            {
                removedClipboardFormatIds[num8] = this._strings.ReadString();
                this._InitialSharedData_RemovedClipboardFormatIds_Offset++;
            }
            obj.SetRemovedClipboardFormatIds(removedClipboardFormatIds);
        }

        private ScopeNodeData ReadNextNodeData()
        {
            ScopeNodeData data = new ScopeNodeData();
            data.NodeType = this._source.Get_NodeData_NodeType()[this._source.Get_NodeData_NodeType_Id()[this._currentIndex]];
            data.SelectedImageIndex = this._source.Get_NodeData_SelectedImageIndex()[this._currentIndex];
            data.HideExpandIcon = this._source.Get_NodeData_HideExpandIcon()[this._currentIndex];
            data.SendActivation = this._source.Get_NodeData_SendActivation()[this._currentIndex];
            data.SendDeactivation = this._source.Get_NodeData_SendDeactivation()[this._currentIndex];
            data.ViewSetId = this._source.Get_NodeData_ViewSetId()[this._currentIndex];
            data.EnabledVerbs = (StandardVerbs) this._source.Get_NodeData_EnabledVerbs()[this._currentIndex];
            data.LanguageIndependentName = this._strings.ReadString();
            data.HelpTopic = this._strings.ReadString();
            this.ReadNextPasteTargetInfo(data.PasteTargetInfo);
            data.Id = this._source.Get_NodeData_Id()[this._currentIndex];
            data.ImageIndex = this._source.Get_NodeData_ImageIndex()[this._currentIndex];
            data.DisplayName = this._strings.ReadString();
            int num = this._source.Get_NodeData_SubItems_Count()[this._currentIndex];
            NodeSubItemData[] subItems = null;
            if (num >= 0)
            {
                subItems = new NodeSubItemData[num];
            }
            int index = 0;
            for (index = 0; index < num; index++)
            {
                subItems[index] = this.ReadNextSubItems();
                this._NodeData_SubItems_Offset++;
            }
            data.SetSubItems(subItems);
            return data;
        }

        private void ReadNextPasteTargetInfo(PasteTargetInfo obj)
        {
            obj.DefaultDragAndDropVerb = (DragAndDropVerb) this._source.Get_NodeData_PasteTargetInfo_DefaultDragAndDropVerb()[this._currentIndex];
            int num = this._source.Get_NodeData_PasteTargetInfo_AllowedClipboardFormats_Count()[this._currentIndex];
            string[] allowedClipboardFormats = null;
            if (num >= 0)
            {
                allowedClipboardFormats = new string[num];
            }
            int index = 0;
            for (index = 0; index < num; index++)
            {
                allowedClipboardFormats[index] = this._strings.ReadString();
                this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Offset++;
            }
            obj.SetAllowedClipboardFormats(allowedClipboardFormats);
        }

        private NodeSubItemData ReadNextSubItems()
        {
            NodeSubItemData data = new NodeSubItemData();
            data.DisplayName = this._strings.ReadString();
            return data;
        }

        private ClipboardData ReadNextUpdatedData()
        {
            ClipboardData data = new ClipboardData();
            data.ClipboardFormatId = this._strings.ReadString();
            int length = this._source.Get_InitialSharedData_UpdatedData_Value_Count()[this._InitialSharedData_UpdatedData_Offset];
            byte[] destinationArray = null;
            if (length >= 0)
            {
                destinationArray = new byte[length];
                Array.Copy(this._source.Get_InitialSharedData_UpdatedData_Value(), this._InitialSharedData_UpdatedData_Value_Offset, destinationArray, 0, length);
                this._InitialSharedData_UpdatedData_Value_Offset += length;
            }
            data.SetValue(destinationArray);
            return data;
        }

        public ScopeNodeInsert ReadScopeNodeInsert()
        {
            if (this._currentIndex >= this.Count)
            {
                throw new EndOfStreamException();
            }
            ScopeNodeInsert insert = new ScopeNodeInsert();
            insert.ParentScopeNodeId = this._source.Get_ParentScopeNodeId()[this._currentIndex];
            insert.InsertionIndex = this._source.Get_InsertionIndex()[this._currentIndex];
            insert.NodeData = this.ReadNextNodeData();
            this.ReadNextInitialSharedData(insert.InitialSharedData);
            insert.Actions = this.ReadNextActions();
            insert.HelpActions = this.ReadNextHelpActions();
            this._currentIndex++;
            return insert;
        }

        public int Count
        {
            get
            {
                return this._source.Count;
            }
        }
    }
}

