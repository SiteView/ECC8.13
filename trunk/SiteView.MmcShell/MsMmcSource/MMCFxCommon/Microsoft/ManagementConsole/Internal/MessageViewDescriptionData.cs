namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class MessageViewDescriptionData : ViewDescriptionData
    {
        private string _bodyText;
        private MessageViewIcon _iconId;
        private string _title;

        public MessageViewDescriptionData()
        {
            this._title = string.Empty;
            this._bodyText = string.Empty;
        }

        public MessageViewDescriptionData(string title, string bodyText, MessageViewIcon iconId)
        {
            this._title = string.Empty;
            this._bodyText = string.Empty;
            this.Title = title;
            this.BodyText = bodyText;
            this.IconId = iconId;
        }

        public override void Validate()
        {
            base.Validate();
            ValidateTitle(this._title);
            ValidateText(this._bodyText);
            ValidateIconId(this._iconId);
        }

        public static void ValidateIconId(MessageViewIcon iconId)
        {
            if ((((iconId != MessageViewIcon.None) && (iconId != MessageViewIcon.Error)) && ((iconId != MessageViewIcon.Question) && (iconId != MessageViewIcon.Warning))) && (iconId != MessageViewIcon.Information))
            {
                throw new ArgumentOutOfRangeException("iconId");
            }
        }

        public static void ValidateText(string bodyText)
        {
            if (bodyText == null)
            {
                throw new ArgumentNullException("bodyText");
            }
        }

        public static void ValidateTitle(string title)
        {
            if (title == null)
            {
                throw new ArgumentNullException("title");
            }
        }

        public string BodyText
        {
            get
            {
                return this._bodyText;
            }
            set
            {
                ValidateText(value);
                this._bodyText = value;
            }
        }

        public MessageViewIcon IconId
        {
            get
            {
                return this._iconId;
            }
            set
            {
                ValidateIconId(value);
                this._iconId = value;
            }
        }

        public string Title
        {
            get
            {
                return this._title;
            }
            set
            {
                ValidateTitle(value);
                this._title = value;
            }
        }
    }
}

