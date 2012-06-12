namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class InsertScopeNodesCommand : Command
    {
        private int[] _Actions_Description_Count;
        private int[] _Actions_DisplayName_Count;
        private bool[] _Actions_ExecuteSync;
        private int[] _Actions_ExecuteSync_Count;
        private int[] _Actions_Id;
        private int[] _Actions_Id_Count;
        private int[] _Actions_ImageIndex;
        private int[] _Actions_ImageIndex_Count;
        private int[] _Actions_InsertionLocation;
        private int[] _Actions_InsertionLocation_Count;
        private int[] _Actions_ItemsCount;
        private int[] _Actions_ItemsCount_Count;
        private int[] _Actions_ItemType;
        private int[] _Actions_ItemType_Count;
        private int[] _Actions_LanguageIndependentName_Count;
        private int[] _Actions_MnemonicDisplayName_Count;
        private bool[] _Actions_RenderAsRegion;
        private int[] _Actions_RenderAsRegion_Count;
        private int[] _Actions_State;
        private int[] _Actions_State_Count;
        private int _count;
        private int[] _HelpActions_Description_Count;
        private int[] _HelpActions_DisplayName_Count;
        private bool[] _HelpActions_ExecuteSync;
        private int[] _HelpActions_ExecuteSync_Count;
        private int[] _HelpActions_Id;
        private int[] _HelpActions_Id_Count;
        private int[] _HelpActions_ImageIndex;
        private int[] _HelpActions_ImageIndex_Count;
        private int[] _HelpActions_InsertionLocation;
        private int[] _HelpActions_InsertionLocation_Count;
        private int[] _HelpActions_ItemsCount;
        private int[] _HelpActions_ItemsCount_Count;
        private int[] _HelpActions_ItemType;
        private int[] _HelpActions_ItemType_Count;
        private int[] _HelpActions_LanguageIndependentName_Count;
        private int[] _HelpActions_MnemonicDisplayName_Count;
        private bool[] _HelpActions_RenderAsRegion;
        private int[] _HelpActions_RenderAsRegion_Count;
        private int[] _HelpActions_State;
        private int[] _HelpActions_State_Count;
        private int[] _InitialSharedData_AddedFormats_Count;
        private bool[] _InitialSharedData_AddedFormats_RequiresQuery;
        private int[] _InitialSharedData_ChangedFormats_Count;
        private bool[] _InitialSharedData_ChangedFormats_RequiresQuery;
        private int[] _InitialSharedData_RemovedClipboardFormatIds_Count;
        private int[] _InitialSharedData_UpdatedData_Count;
        private byte[] _InitialSharedData_UpdatedData_Value;
        private int[] _InitialSharedData_UpdatedData_Value_Count;
        private int[] _InsertionIndex;
        private int[] _NodeData_EnabledVerbs;
        private bool[] _NodeData_HideExpandIcon;
        private int[] _NodeData_Id;
        private int[] _NodeData_ImageIndex;
        private Guid[] _NodeData_NodeType;
        private int[] _NodeData_NodeType_Id;
        private int[] _NodeData_PasteTargetInfo_AllowedClipboardFormats_Count;
        private int[] _NodeData_PasteTargetInfo_DefaultDragAndDropVerb;
        private int[] _NodeData_SelectedImageIndex;
        private bool[] _NodeData_SendActivation;
        private bool[] _NodeData_SendDeactivation;
        private int[] _NodeData_SubItems_Count;
        private int[] _NodeData_ViewSetId;
        private int[] _ParentScopeNodeId;
        private byte[] _strings;

        internal int[] Get_Actions_Description_Count()
        {
            return this._Actions_Description_Count;
        }

        internal int[] Get_Actions_DisplayName_Count()
        {
            return this._Actions_DisplayName_Count;
        }

        internal bool[] Get_Actions_ExecuteSync()
        {
            return this._Actions_ExecuteSync;
        }

        internal int[] Get_Actions_ExecuteSync_Count()
        {
            return this._Actions_ExecuteSync_Count;
        }

        internal int[] Get_Actions_Id()
        {
            return this._Actions_Id;
        }

        internal int[] Get_Actions_Id_Count()
        {
            return this._Actions_Id_Count;
        }

        internal int[] Get_Actions_ImageIndex()
        {
            return this._Actions_ImageIndex;
        }

        internal int[] Get_Actions_ImageIndex_Count()
        {
            return this._Actions_ImageIndex_Count;
        }

        internal int[] Get_Actions_InsertionLocation()
        {
            return this._Actions_InsertionLocation;
        }

        internal int[] Get_Actions_InsertionLocation_Count()
        {
            return this._Actions_InsertionLocation_Count;
        }

        internal int[] Get_Actions_ItemsCount()
        {
            return this._Actions_ItemsCount;
        }

        internal int[] Get_Actions_ItemsCount_Count()
        {
            return this._Actions_ItemsCount_Count;
        }

        internal int[] Get_Actions_ItemType()
        {
            return this._Actions_ItemType;
        }

        internal int[] Get_Actions_ItemType_Count()
        {
            return this._Actions_ItemType_Count;
        }

        internal int[] Get_Actions_LanguageIndependentName_Count()
        {
            return this._Actions_LanguageIndependentName_Count;
        }

        internal int[] Get_Actions_MnemonicDisplayName_Count()
        {
            return this._Actions_MnemonicDisplayName_Count;
        }

        internal bool[] Get_Actions_RenderAsRegion()
        {
            return this._Actions_RenderAsRegion;
        }

        internal int[] Get_Actions_RenderAsRegion_Count()
        {
            return this._Actions_RenderAsRegion_Count;
        }

        internal int[] Get_Actions_State()
        {
            return this._Actions_State;
        }

        internal int[] Get_Actions_State_Count()
        {
            return this._Actions_State_Count;
        }

        internal int[] Get_HelpActions_Description_Count()
        {
            return this._HelpActions_Description_Count;
        }

        internal int[] Get_HelpActions_DisplayName_Count()
        {
            return this._HelpActions_DisplayName_Count;
        }

        internal bool[] Get_HelpActions_ExecuteSync()
        {
            return this._HelpActions_ExecuteSync;
        }

        internal int[] Get_HelpActions_ExecuteSync_Count()
        {
            return this._HelpActions_ExecuteSync_Count;
        }

        internal int[] Get_HelpActions_Id()
        {
            return this._HelpActions_Id;
        }

        internal int[] Get_HelpActions_Id_Count()
        {
            return this._HelpActions_Id_Count;
        }

        internal int[] Get_HelpActions_ImageIndex()
        {
            return this._HelpActions_ImageIndex;
        }

        internal int[] Get_HelpActions_ImageIndex_Count()
        {
            return this._HelpActions_ImageIndex_Count;
        }

        internal int[] Get_HelpActions_InsertionLocation()
        {
            return this._HelpActions_InsertionLocation;
        }

        internal int[] Get_HelpActions_InsertionLocation_Count()
        {
            return this._HelpActions_InsertionLocation_Count;
        }

        internal int[] Get_HelpActions_ItemsCount()
        {
            return this._HelpActions_ItemsCount;
        }

        internal int[] Get_HelpActions_ItemsCount_Count()
        {
            return this._HelpActions_ItemsCount_Count;
        }

        internal int[] Get_HelpActions_ItemType()
        {
            return this._HelpActions_ItemType;
        }

        internal int[] Get_HelpActions_ItemType_Count()
        {
            return this._HelpActions_ItemType_Count;
        }

        internal int[] Get_HelpActions_LanguageIndependentName_Count()
        {
            return this._HelpActions_LanguageIndependentName_Count;
        }

        internal int[] Get_HelpActions_MnemonicDisplayName_Count()
        {
            return this._HelpActions_MnemonicDisplayName_Count;
        }

        internal bool[] Get_HelpActions_RenderAsRegion()
        {
            return this._HelpActions_RenderAsRegion;
        }

        internal int[] Get_HelpActions_RenderAsRegion_Count()
        {
            return this._HelpActions_RenderAsRegion_Count;
        }

        internal int[] Get_HelpActions_State()
        {
            return this._HelpActions_State;
        }

        internal int[] Get_HelpActions_State_Count()
        {
            return this._HelpActions_State_Count;
        }

        internal int[] Get_InitialSharedData_AddedFormats_Count()
        {
            return this._InitialSharedData_AddedFormats_Count;
        }

        internal bool[] Get_InitialSharedData_AddedFormats_RequiresQuery()
        {
            return this._InitialSharedData_AddedFormats_RequiresQuery;
        }

        internal int[] Get_InitialSharedData_ChangedFormats_Count()
        {
            return this._InitialSharedData_ChangedFormats_Count;
        }

        internal bool[] Get_InitialSharedData_ChangedFormats_RequiresQuery()
        {
            return this._InitialSharedData_ChangedFormats_RequiresQuery;
        }

        internal int[] Get_InitialSharedData_RemovedClipboardFormatIds_Count()
        {
            return this._InitialSharedData_RemovedClipboardFormatIds_Count;
        }

        internal int[] Get_InitialSharedData_UpdatedData_Count()
        {
            return this._InitialSharedData_UpdatedData_Count;
        }

        internal byte[] Get_InitialSharedData_UpdatedData_Value()
        {
            return this._InitialSharedData_UpdatedData_Value;
        }

        internal int[] Get_InitialSharedData_UpdatedData_Value_Count()
        {
            return this._InitialSharedData_UpdatedData_Value_Count;
        }

        internal int[] Get_InsertionIndex()
        {
            return this._InsertionIndex;
        }

        internal int[] Get_NodeData_EnabledVerbs()
        {
            return this._NodeData_EnabledVerbs;
        }

        internal bool[] Get_NodeData_HideExpandIcon()
        {
            return this._NodeData_HideExpandIcon;
        }

        internal int[] Get_NodeData_Id()
        {
            return this._NodeData_Id;
        }

        internal int[] Get_NodeData_ImageIndex()
        {
            return this._NodeData_ImageIndex;
        }

        internal Guid[] Get_NodeData_NodeType()
        {
            return this._NodeData_NodeType;
        }

        internal int[] Get_NodeData_NodeType_Id()
        {
            return this._NodeData_NodeType_Id;
        }

        internal int[] Get_NodeData_PasteTargetInfo_AllowedClipboardFormats_Count()
        {
            return this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Count;
        }

        internal int[] Get_NodeData_PasteTargetInfo_DefaultDragAndDropVerb()
        {
            return this._NodeData_PasteTargetInfo_DefaultDragAndDropVerb;
        }

        internal int[] Get_NodeData_SelectedImageIndex()
        {
            return this._NodeData_SelectedImageIndex;
        }

        internal bool[] Get_NodeData_SendActivation()
        {
            return this._NodeData_SendActivation;
        }

        internal bool[] Get_NodeData_SendDeactivation()
        {
            return this._NodeData_SendDeactivation;
        }

        internal int[] Get_NodeData_SubItems_Count()
        {
            return this._NodeData_SubItems_Count;
        }

        internal int[] Get_NodeData_ViewSetId()
        {
            return this._NodeData_ViewSetId;
        }

        internal int[] Get_ParentScopeNodeId()
        {
            return this._ParentScopeNodeId;
        }

        internal byte[] Get_strings()
        {
            return this._strings;
        }

        internal void Set_Actions_Description_Count(int[] Description_Count)
        {
            this._Actions_Description_Count = Description_Count;
        }

        internal void Set_Actions_DisplayName_Count(int[] DisplayName_Count)
        {
            this._Actions_DisplayName_Count = DisplayName_Count;
        }

        internal void Set_Actions_ExecuteSync(bool[] ExecuteSync)
        {
            this._Actions_ExecuteSync = ExecuteSync;
        }

        internal void Set_Actions_ExecuteSync_Count(int[] ExecuteSync_Count)
        {
            this._Actions_ExecuteSync_Count = ExecuteSync_Count;
        }

        internal void Set_Actions_Id(int[] Id)
        {
            this._Actions_Id = Id;
        }

        internal void Set_Actions_Id_Count(int[] Id_Count)
        {
            this._Actions_Id_Count = Id_Count;
        }

        internal void Set_Actions_ImageIndex(int[] ImageIndex)
        {
            this._Actions_ImageIndex = ImageIndex;
        }

        internal void Set_Actions_ImageIndex_Count(int[] ImageIndex_Count)
        {
            this._Actions_ImageIndex_Count = ImageIndex_Count;
        }

        internal void Set_Actions_InsertionLocation(int[] InsertionLocation)
        {
            this._Actions_InsertionLocation = InsertionLocation;
        }

        internal void Set_Actions_InsertionLocation_Count(int[] InsertionLocation_Count)
        {
            this._Actions_InsertionLocation_Count = InsertionLocation_Count;
        }

        internal void Set_Actions_ItemsCount(int[] ItemsCount)
        {
            this._Actions_ItemsCount = ItemsCount;
        }

        internal void Set_Actions_ItemsCount_Count(int[] ItemsCount_Count)
        {
            this._Actions_ItemsCount_Count = ItemsCount_Count;
        }

        internal void Set_Actions_ItemType(int[] ItemType)
        {
            this._Actions_ItemType = ItemType;
        }

        internal void Set_Actions_ItemType_Count(int[] ItemType_Count)
        {
            this._Actions_ItemType_Count = ItemType_Count;
        }

        internal void Set_Actions_LanguageIndependentName_Count(int[] LanguageIndependentName_Count)
        {
            this._Actions_LanguageIndependentName_Count = LanguageIndependentName_Count;
        }

        internal void Set_Actions_MnemonicDisplayName_Count(int[] MnemonicDisplayName_Count)
        {
            this._Actions_MnemonicDisplayName_Count = MnemonicDisplayName_Count;
        }

        internal void Set_Actions_RenderAsRegion(bool[] RenderAsRegion)
        {
            this._Actions_RenderAsRegion = RenderAsRegion;
        }

        internal void Set_Actions_RenderAsRegion_Count(int[] RenderAsRegion_Count)
        {
            this._Actions_RenderAsRegion_Count = RenderAsRegion_Count;
        }

        internal void Set_Actions_State(int[] State)
        {
            this._Actions_State = State;
        }

        internal void Set_Actions_State_Count(int[] State_Count)
        {
            this._Actions_State_Count = State_Count;
        }

        internal void Set_HelpActions_Description_Count(int[] Description_Count)
        {
            this._HelpActions_Description_Count = Description_Count;
        }

        internal void Set_HelpActions_DisplayName_Count(int[] DisplayName_Count)
        {
            this._HelpActions_DisplayName_Count = DisplayName_Count;
        }

        internal void Set_HelpActions_ExecuteSync(bool[] ExecuteSync)
        {
            this._HelpActions_ExecuteSync = ExecuteSync;
        }

        internal void Set_HelpActions_ExecuteSync_Count(int[] ExecuteSync_Count)
        {
            this._HelpActions_ExecuteSync_Count = ExecuteSync_Count;
        }

        internal void Set_HelpActions_Id(int[] Id)
        {
            this._HelpActions_Id = Id;
        }

        internal void Set_HelpActions_Id_Count(int[] Id_Count)
        {
            this._HelpActions_Id_Count = Id_Count;
        }

        internal void Set_HelpActions_ImageIndex(int[] ImageIndex)
        {
            this._HelpActions_ImageIndex = ImageIndex;
        }

        internal void Set_HelpActions_ImageIndex_Count(int[] ImageIndex_Count)
        {
            this._HelpActions_ImageIndex_Count = ImageIndex_Count;
        }

        internal void Set_HelpActions_InsertionLocation(int[] InsertionLocation)
        {
            this._HelpActions_InsertionLocation = InsertionLocation;
        }

        internal void Set_HelpActions_InsertionLocation_Count(int[] InsertionLocation_Count)
        {
            this._HelpActions_InsertionLocation_Count = InsertionLocation_Count;
        }

        internal void Set_HelpActions_ItemsCount(int[] ItemsCount)
        {
            this._HelpActions_ItemsCount = ItemsCount;
        }

        internal void Set_HelpActions_ItemsCount_Count(int[] ItemsCount_Count)
        {
            this._HelpActions_ItemsCount_Count = ItemsCount_Count;
        }

        internal void Set_HelpActions_ItemType(int[] ItemType)
        {
            this._HelpActions_ItemType = ItemType;
        }

        internal void Set_HelpActions_ItemType_Count(int[] ItemType_Count)
        {
            this._HelpActions_ItemType_Count = ItemType_Count;
        }

        internal void Set_HelpActions_LanguageIndependentName_Count(int[] LanguageIndependentName_Count)
        {
            this._HelpActions_LanguageIndependentName_Count = LanguageIndependentName_Count;
        }

        internal void Set_HelpActions_MnemonicDisplayName_Count(int[] MnemonicDisplayName_Count)
        {
            this._HelpActions_MnemonicDisplayName_Count = MnemonicDisplayName_Count;
        }

        internal void Set_HelpActions_RenderAsRegion(bool[] RenderAsRegion)
        {
            this._HelpActions_RenderAsRegion = RenderAsRegion;
        }

        internal void Set_HelpActions_RenderAsRegion_Count(int[] RenderAsRegion_Count)
        {
            this._HelpActions_RenderAsRegion_Count = RenderAsRegion_Count;
        }

        internal void Set_HelpActions_State(int[] State)
        {
            this._HelpActions_State = State;
        }

        internal void Set_HelpActions_State_Count(int[] State_Count)
        {
            this._HelpActions_State_Count = State_Count;
        }

        internal void Set_InitialSharedData_AddedFormats_Count(int[] AddedFormats_Count)
        {
            this._InitialSharedData_AddedFormats_Count = AddedFormats_Count;
        }

        internal void Set_InitialSharedData_AddedFormats_RequiresQuery(bool[] RequiresQuery)
        {
            this._InitialSharedData_AddedFormats_RequiresQuery = RequiresQuery;
        }

        internal void Set_InitialSharedData_ChangedFormats_Count(int[] ChangedFormats_Count)
        {
            this._InitialSharedData_ChangedFormats_Count = ChangedFormats_Count;
        }

        internal void Set_InitialSharedData_ChangedFormats_RequiresQuery(bool[] RequiresQuery)
        {
            this._InitialSharedData_ChangedFormats_RequiresQuery = RequiresQuery;
        }

        internal void Set_InitialSharedData_RemovedClipboardFormatIds_Count(int[] RemovedClipboardFormatIds_Count)
        {
            this._InitialSharedData_RemovedClipboardFormatIds_Count = RemovedClipboardFormatIds_Count;
        }

        internal void Set_InitialSharedData_UpdatedData_Count(int[] UpdatedData_Count)
        {
            this._InitialSharedData_UpdatedData_Count = UpdatedData_Count;
        }

        internal void Set_InitialSharedData_UpdatedData_Value(byte[] Value)
        {
            this._InitialSharedData_UpdatedData_Value = Value;
        }

        internal void Set_InitialSharedData_UpdatedData_Value_Count(int[] Value_Count)
        {
            this._InitialSharedData_UpdatedData_Value_Count = Value_Count;
        }

        internal void Set_InsertionIndex(int[] InsertionIndex)
        {
            this._InsertionIndex = InsertionIndex;
        }

        internal void Set_NodeData_EnabledVerbs(int[] EnabledVerbs)
        {
            this._NodeData_EnabledVerbs = EnabledVerbs;
        }

        internal void Set_NodeData_HideExpandIcon(bool[] HideExpandIcon)
        {
            this._NodeData_HideExpandIcon = HideExpandIcon;
        }

        internal void Set_NodeData_Id(int[] Id)
        {
            this._NodeData_Id = Id;
        }

        internal void Set_NodeData_ImageIndex(int[] ImageIndex)
        {
            this._NodeData_ImageIndex = ImageIndex;
        }

        internal void Set_NodeData_NodeType(Guid[] NodeType)
        {
            this._NodeData_NodeType = NodeType;
        }

        internal void Set_NodeData_NodeType_Id(int[] NodeType_Id)
        {
            this._NodeData_NodeType_Id = NodeType_Id;
        }

        internal void Set_NodeData_PasteTargetInfo_AllowedClipboardFormats_Count(int[] AllowedClipboardFormats_Count)
        {
            this._NodeData_PasteTargetInfo_AllowedClipboardFormats_Count = AllowedClipboardFormats_Count;
        }

        internal void Set_NodeData_PasteTargetInfo_DefaultDragAndDropVerb(int[] DefaultDragAndDropVerb)
        {
            this._NodeData_PasteTargetInfo_DefaultDragAndDropVerb = DefaultDragAndDropVerb;
        }

        internal void Set_NodeData_SelectedImageIndex(int[] SelectedImageIndex)
        {
            this._NodeData_SelectedImageIndex = SelectedImageIndex;
        }

        internal void Set_NodeData_SendActivation(bool[] SendActivation)
        {
            this._NodeData_SendActivation = SendActivation;
        }

        internal void Set_NodeData_SendDeactivation(bool[] SendDeactivation)
        {
            this._NodeData_SendDeactivation = SendDeactivation;
        }

        internal void Set_NodeData_SubItems_Count(int[] SubItems_Count)
        {
            this._NodeData_SubItems_Count = SubItems_Count;
        }

        internal void Set_NodeData_ViewSetId(int[] ViewSetId)
        {
            this._NodeData_ViewSetId = ViewSetId;
        }

        internal void Set_ParentScopeNodeId(int[] ParentScopeNodeId)
        {
            this._ParentScopeNodeId = ParentScopeNodeId;
        }

        internal void Set_strings(byte[] strings)
        {
            this._strings = strings;
        }

        internal int Count
        {
            get
            {
                return this._count;
            }
            set
            {
                this._count = value;
            }
        }
    }
}

