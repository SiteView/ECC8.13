namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ActionsPaneExtendedItem : ActionsPaneItem
    {
        internal ActionsPaneExtendedItem()
        {
        }

        internal void Initialize(ActionsPaneItemData data, string displayName, string description, int imageIndex, object tag)
        {
            base.Data = data;
            if (!string.IsNullOrEmpty(displayName))
            {
                this.DisplayName = displayName;
            }
            if (!string.IsNullOrEmpty(description))
            {
                this.Description = description;
            }
            if (imageIndex != -1)
            {
                this.ImageIndex = imageIndex;
            }
            if (tag != null)
            {
                base.Tag = tag;
            }
        }

        public string Description
        {
            get
            {
                return ((ActionsPaneExtendedItemData) base.Data).Description;
            }
            set
            {
                ActionsPaneExtendedItemData.ValidateDescription(value);
                if (((ActionsPaneExtendedItemData) base.Data).Description != value)
                {
                    ((ActionsPaneExtendedItemData) base.Data).Description = value;
                    base.Notify();
                }
            }
        }

        public string DisplayName
        {
            get
            {
                return ((ActionsPaneExtendedItemData) base.Data).DisplayName;
            }
            set
            {
                ActionsPaneExtendedItemData.ValidateDisplayName(value);
                if (((ActionsPaneExtendedItemData) base.Data).DisplayName != value)
                {
                    ((ActionsPaneExtendedItemData) base.Data).DisplayName = value;
                    base.Notify();
                }
            }
        }

        public int ImageIndex
        {
            get
            {
                return ((ActionsPaneExtendedItemData) base.Data).ImageIndex;
            }
            set
            {
                ((ActionsPaneExtendedItemData) base.Data).ImageIndex = value;
                base.Notify();
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                return ((ActionsPaneExtendedItemData) base.Data).LanguageIndependentName;
            }
            set
            {
                ActionsPaneExtendedItemData.ValidateLanguageIndependentName(value);
                if (((ActionsPaneExtendedItemData) base.Data).LanguageIndependentName != value)
                {
                    ((ActionsPaneExtendedItemData) base.Data).LanguageIndependentName = value;
                    base.Notify();
                }
            }
        }

        public string MnemonicDisplayName
        {
            get
            {
                return ((ActionsPaneExtendedItemData) base.Data).MnemonicDisplayName;
            }
            set
            {
                ActionsPaneExtendedItemData.ValidateMnemonicDisplayName(value, "value");
                if (((ActionsPaneExtendedItemData) base.Data).MnemonicDisplayName != value)
                {
                    ((ActionsPaneExtendedItemData) base.Data).MnemonicDisplayName = value;
                    base.Notify();
                }
            }
        }
    }
}

