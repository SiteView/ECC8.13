namespace Microsoft.ManagementConsole.Advanced
{
    using System;
    using System.Windows.Forms;

    public sealed class MessageBoxParameters
    {
        private MessageBoxButtons _buttons;
        private string _caption = string.Empty;
        private MessageBoxDefaultButton _defaultButton;
        private string _helpFilePath;
        private object _helpTopicId;
        private MessageBoxIcon _icon;
        private HelpNavigator _navigator;
        private MessageBoxOptions _options;
        private bool _showHelp;
        private string _text = string.Empty;

        internal DialogResult ShowDialog(IWin32Window parent)
        {
            if (this._showHelp)
            {
                return MessageBox.Show(parent, this._text, this._caption, this._buttons, this._icon, this._defaultButton, this._options, this._helpFilePath, this._navigator, this._helpTopicId);
            }
            return MessageBox.Show(parent, this._text, this._caption, this._buttons, this._icon, this._defaultButton, this._options);
        }

        public MessageBoxButtons Buttons
        {
            get
            {
                return this._buttons;
            }
            set
            {
                this._buttons = value;
            }
        }

        public string Caption
        {
            get
            {
                return this._caption;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._caption = value;
            }
        }

        public MessageBoxDefaultButton DefaultButton
        {
            get
            {
                return this._defaultButton;
            }
            set
            {
                this._defaultButton = value;
            }
        }

        public string HelpFilePath
        {
            get
            {
                return this._helpFilePath;
            }
            set
            {
                this._helpFilePath = value;
            }
        }

        public object HelpTopicId
        {
            get
            {
                return this._helpTopicId;
            }
            set
            {
                this._helpTopicId = value;
            }
        }

        public MessageBoxIcon Icon
        {
            get
            {
                return this._icon;
            }
            set
            {
                this._icon = value;
            }
        }

        public HelpNavigator Navigator
        {
            get
            {
                return this._navigator;
            }
            set
            {
                this._navigator = value;
            }
        }

        public MessageBoxOptions Options
        {
            get
            {
                return this._options;
            }
            set
            {
                this._options = value;
            }
        }

        public bool ShowHelp
        {
            get
            {
                return this._showHelp;
            }
            set
            {
                this._showHelp = value;
            }
        }

        public string Text
        {
            get
            {
                return this._text;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._text = value;
            }
        }
    }
}

