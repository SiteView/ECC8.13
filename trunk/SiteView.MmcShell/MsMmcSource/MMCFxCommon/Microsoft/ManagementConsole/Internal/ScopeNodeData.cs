namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ScopeNodeData : NodeData
    {
        private StandardVerbs _enabledVerbs;
        private string _helpTopic;
        private bool _hideExpandIcon;
        private string _languageIndependentName = string.Empty;
        private Guid _nodeType;
        private Microsoft.ManagementConsole.Internal.PasteTargetInfo _pasteTargetInfo;
        private int _selectedImageIndex;
        private bool _sendActivation;
        private bool _sendDeactivation;
        private int _viewSetId = -1;

        public StandardVerbs EnabledVerbs
        {
            get
            {
                return this._enabledVerbs;
            }
            set
            {
                this._enabledVerbs = value;
            }
        }

        public string HelpTopic
        {
            get
            {
                return this._helpTopic;
            }
            set
            {
                this._helpTopic = value;
            }
        }

        public bool HideExpandIcon
        {
            get
            {
                return this._hideExpandIcon;
            }
            set
            {
                this._hideExpandIcon = value;
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                if (Utility.CheckStringNullOrEmpty(this._languageIndependentName, string.Empty, false))
                {
                    return base.DisplayName;
                }
                return this._languageIndependentName;
            }
            set
            {
                this._languageIndependentName = value;
            }
        }

        public Guid NodeType
        {
            get
            {
                return this._nodeType;
            }
            set
            {
                this._nodeType = value;
            }
        }

        public Microsoft.ManagementConsole.Internal.PasteTargetInfo PasteTargetInfo
        {
            get
            {
                if (this._pasteTargetInfo == null)
                {
                    this._pasteTargetInfo = new Microsoft.ManagementConsole.Internal.PasteTargetInfo();
                }
                return this._pasteTargetInfo;
            }
        }

        public int SelectedImageIndex
        {
            get
            {
                return this._selectedImageIndex;
            }
            set
            {
                this._selectedImageIndex = value;
            }
        }

        public bool SendActivation
        {
            get
            {
                return this._sendActivation;
            }
            set
            {
                this._sendActivation = value;
            }
        }

        public bool SendDeactivation
        {
            get
            {
                return this._sendDeactivation;
            }
            set
            {
                this._sendDeactivation = value;
            }
        }

        public int ViewSetId
        {
            get
            {
                return this._viewSetId;
            }
            set
            {
                this._viewSetId = value;
            }
        }
    }
}

