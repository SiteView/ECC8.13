namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ActionsPaneExtendedItemData : ActionsPaneItemData
    {
        private string _description = string.Empty;
        private string _displayName = string.Empty;
        private int _imageIndex = -1;
        private string _languageIndependentName = string.Empty;
        private string _mnemonicDisplayName = string.Empty;

        protected ActionsPaneExtendedItemData()
        {
        }

        public override void Validate()
        {
            base.Validate();
            ValidateDisplayName(this._displayName);
            ValidateMnemonicDisplayName(this._mnemonicDisplayName, "MnemonicDisplayName");
            ValidateLanguageIndependentName(this._languageIndependentName);
            ValidateDescription(this._description);
        }

        public static void ValidateDescription(string description)
        {
            if (description == null)
            {
                throw new ArgumentNullException("description");
            }
        }

        public static void ValidateDisplayName(string displayName)
        {
            if (displayName == null)
            {
                throw new ArgumentNullException("displayName");
            }
            displayName = displayName.Trim();
            Utility.CheckStringNullOrEmpty(displayName, "DisplayName", true);
        }

        public static void ValidateLanguageIndependentName(string languageIndependentName)
        {
            if (languageIndependentName == null)
            {
                throw new ArgumentNullException("languageIndependentName");
            }
        }

        public static void ValidateMnemonicDisplayName(string displayName, string propertyName)
        {
            if (displayName == null)
            {
                throw new ArgumentNullException(propertyName);
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
                ValidateDescription(value);
                this._description = value;
            }
        }

        public string DisplayName
        {
            get
            {
                return this._displayName;
            }
            set
            {
                ValidateDisplayName(value);
                this._displayName = value;
            }
        }

        public int ImageIndex
        {
            get
            {
                return this._imageIndex;
            }
            set
            {
                this._imageIndex = value;
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                if (Utility.CheckStringNullOrEmpty(this._languageIndependentName, string.Empty, false))
                {
                    return this._displayName;
                }
                return this._languageIndependentName;
            }
            set
            {
                ValidateLanguageIndependentName(value);
                this._languageIndependentName = value;
            }
        }

        public string MnemonicDisplayName
        {
            get
            {
                return this._mnemonicDisplayName;
            }
            set
            {
                ValidateMnemonicDisplayName(value, "value");
                this._mnemonicDisplayName = value;
            }
        }
    }
}

