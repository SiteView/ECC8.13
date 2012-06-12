namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    [Serializable, StructLayout(LayoutKind.Sequential), EditorBrowsable(EditorBrowsableState.Never)]
    public struct ActionsPaneRootData
    {
        private int[] _id;
        private ActionsPaneRootItemType[] _type;
        private ActionsInsertionLocation[] _insertionLocation;
        private string[] _displayName;
        private string[] _description;
        private string[] _mnemonicDisplayName;
        private string[] _languageIndependentName;
        private int[] _imageIndex;
        private ActionStates[] _state;
        private bool[] _executeSync;
        private bool[] _renderAsRegion;
        private int[] _itemsCount;
        public void Write(ActionsPaneItemCollectionData data)
        {
            if (data == null)
            {
                throw new ArgumentNullException("data");
            }
            int sepCount = 0;
            int actionCount = 0;
            int colCount = 0;
            this.CountItems(data, ref sepCount, ref actionCount, ref colCount);
            int num4 = (sepCount + actionCount) + colCount;
            int num5 = actionCount + colCount;
            this._id = new int[num4];
            this._type = new ActionsPaneRootItemType[num4];
            this._insertionLocation = new ActionsInsertionLocation[num4];
            this._displayName = new string[num5];
            this._description = new string[num5];
            this._mnemonicDisplayName = new string[num5];
            this._languageIndependentName = new string[num5];
            this._imageIndex = new int[num5];
            this._state = new ActionStates[actionCount];
            this._executeSync = new bool[actionCount];
            this._renderAsRegion = new bool[colCount];
            this._itemsCount = new int[colCount];
            int index = 0;
            int exItemIndex = 0;
            int actionIndex = 0;
            int colIndex = 0;
            this.Write(data, ref index, ref exItemIndex, ref actionIndex, ref colIndex);
        }

        private void Write(ActionsPaneItemData data, ref int index, ref int exItemIndex, ref int actionIndex, ref int colIndex)
        {
            this._id[index] = data.Id;
            this._insertionLocation[index] = data.InsertionLocation;
            this._type[index] = ActionsPaneRootItemType.Separator;
            index++;
            ActionsPaneExtendedItemData data2 = data as ActionsPaneExtendedItemData;
            if (data2 != null)
            {
                this._displayName[exItemIndex] = data2.DisplayName;
                this._description[exItemIndex] = data2.Description;
                this._mnemonicDisplayName[exItemIndex] = data2.MnemonicDisplayName;
                this._languageIndependentName[exItemIndex] = data2.LanguageIndependentName;
                this._imageIndex[exItemIndex] = data2.ImageIndex;
                exItemIndex++;
                ActionData data3 = data2 as ActionData;
                if (data3 != null)
                {
                    this._state[actionIndex] = data3.State;
                    this._executeSync[actionIndex] = data3.ExecuteSync;
                    this._type[index - 1] = ActionsPaneRootItemType.Action;
                    actionIndex++;
                }
                else
                {
                    ActionsPaneItemCollectionData data4 = (ActionsPaneItemCollectionData) data2;
                    this._type[index - 1] = ActionsPaneRootItemType.Collection;
                    this._renderAsRegion[colIndex] = data4.RenderAsRegion;
                    int length = 0;
                    ActionsPaneItemData[] items = data4.GetItems();
                    if (items != null)
                    {
                        length = items.Length;
                    }
                    this._itemsCount[colIndex] = length;
                    colIndex++;
                    for (int i = 0; i < length; i++)
                    {
                        this.Write(items[i], ref index, ref exItemIndex, ref actionIndex, ref colIndex);
                    }
                }
            }
        }

        public ActionsPaneItemCollectionData Read()
        {
            int index = 0;
            int exItemIndex = 0;
            int actionIndex = 0;
            int colIndex = 0;
            ActionsPaneItemData data = null;
            if (this._id == null)
            {
                return null;
            }
            if (this._id.Length > 0)
            {
                data = this.Read(ref index, ref exItemIndex, ref actionIndex, ref colIndex);
            }
            ActionsPaneItemCollectionData data2 = data as ActionsPaneItemCollectionData;
            if (data2 == null)
            {
                data2 = new ActionsPaneItemCollectionData();
                if (data != null)
                {
                    data2.SetItems(new ActionsPaneItemData[] { data });
                }
            }
            return data2;
        }

        private ActionsPaneItemData Read(ref int index, ref int exItemIndex, ref int actionIndex, ref int colIndex)
        {
            ActionsPaneItemData data = null;
            switch (this._type[index])
            {
                case ActionsPaneRootItemType.Separator:
                    data = new ActionSeparatorItemData();
                    break;

                case ActionsPaneRootItemType.Action:
                    data = new ActionData();
                    break;

                case ActionsPaneRootItemType.Collection:
                    data = new ActionsPaneItemCollectionData();
                    break;
            }
            this.ReadActionsPaneItem(data, ref index);
            ActionsPaneExtendedItemData data2 = data as ActionsPaneExtendedItemData;
            if (data2 != null)
            {
                this.ReadExtendedActionsPaneItem(data2, ref exItemIndex);
                ActionData data3 = data2 as ActionData;
                if (data3 != null)
                {
                    this.ReadAction(data3, ref actionIndex);
                    return data;
                }
                this.ReadCollection((ActionsPaneItemCollectionData) data2, ref index, ref exItemIndex, ref actionIndex, ref colIndex);
            }
            return data;
        }

        private void ReadActionsPaneItem(ActionsPaneItemData data, ref int index)
        {
            data.Id = this._id[index];
            data.InsertionLocation = this._insertionLocation[index];
            index++;
        }

        private void ReadExtendedActionsPaneItem(ActionsPaneExtendedItemData data, ref int exItemIndex)
        {
            string str = this._displayName[exItemIndex];
            if (!string.IsNullOrEmpty(str))
            {
                data.DisplayName = str;
            }
            string str2 = this._mnemonicDisplayName[exItemIndex];
            if (!string.IsNullOrEmpty(str2))
            {
                data.MnemonicDisplayName = str2;
            }
            string str3 = this._description[exItemIndex];
            if (!string.IsNullOrEmpty(str3))
            {
                data.Description = str3;
            }
            string str4 = this._languageIndependentName[exItemIndex];
            if (!string.IsNullOrEmpty(str4))
            {
                data.LanguageIndependentName = str4;
            }
            data.ImageIndex = this._imageIndex[exItemIndex];
            exItemIndex++;
        }

        private void ReadAction(ActionData data, ref int actionIndex)
        {
            data.ExecuteSync = this._executeSync[actionIndex];
            data.State = this._state[actionIndex];
            actionIndex++;
        }

        private void ReadCollection(ActionsPaneItemCollectionData data, ref int index, ref int exItemIndex, ref int actionIndex, ref int colIndex)
        {
            data.RenderAsRegion = this._renderAsRegion[colIndex];
            int num = this._itemsCount[colIndex];
            colIndex++;
            ActionsPaneItemData[] items = new ActionsPaneItemData[num];
            for (int i = 0; i < num; i++)
            {
                items[i] = this.Read(ref index, ref exItemIndex, ref actionIndex, ref colIndex);
            }
            data.SetItems(items);
        }

        private void CountItems(ActionsPaneItemData data, ref int sepCount, ref int actionCount, ref int colCount)
        {
            ActionsPaneItemCollectionData data2 = data as ActionsPaneItemCollectionData;
            if (data2 != null)
            {
                colCount++;
                ActionsPaneItemData[] items = data2.GetItems();
                if (items != null)
                {
                    for (int i = 0; i < items.Length; i++)
                    {
                        this.CountItems(items[i], ref sepCount, ref actionCount, ref colCount);
                    }
                }
            }
            else if (data is ActionData)
            {
                actionCount++;
            }
            else
            {
                sepCount++;
            }
        }

        public int[] GetId()
        {
            return this._id;
        }

        public void SetId(int[] value)
        {
            this._id = value;
        }

        public ActionsPaneRootItemType[] GetItemType()
        {
            return this._type;
        }

        public void SetItemType(ActionsPaneRootItemType[] value)
        {
            this._type = value;
        }

        public ActionsInsertionLocation[] GetInsertionLocation()
        {
            return this._insertionLocation;
        }

        public void SetInsertionLocation(ActionsInsertionLocation[] value)
        {
            this._insertionLocation = value;
        }

        public string[] GetDisplayName()
        {
            return this._displayName;
        }

        public void SetDisplayName(string[] value)
        {
            this._displayName = value;
        }

        public string[] GetMnemonicDisplayName()
        {
            return this._mnemonicDisplayName;
        }

        public void SetMnemonicDisplayName(string[] value)
        {
            this._mnemonicDisplayName = value;
        }

        public string[] GetDescription()
        {
            return this._description;
        }

        public void SetDescription(string[] value)
        {
            this._description = value;
        }

        public string[] GetLanguageIndependentName()
        {
            return this._languageIndependentName;
        }

        public void SetLanguageIndependentName(string[] value)
        {
            this._languageIndependentName = value;
        }

        public int[] GetImageIndex()
        {
            return this._imageIndex;
        }

        public void SetImageIndex(int[] value)
        {
            this._imageIndex = value;
        }

        public ActionStates[] GetState()
        {
            return this._state;
        }

        public void SetState(ActionStates[] value)
        {
            this._state = value;
        }

        public bool[] GetExecuteSync()
        {
            return this._executeSync;
        }

        public void SetExecuteSync(bool[] value)
        {
            this._executeSync = value;
        }

        public bool[] GetRenderAsRegion()
        {
            return this._renderAsRegion;
        }

        public void SetRenderAsRegion(bool[] value)
        {
            this._renderAsRegion = value;
        }

        public int[] GetItemsCount()
        {
            return this._itemsCount;
        }

        public void SetItemsCount(int[] value)
        {
            this._itemsCount = value;
        }
    }
}

