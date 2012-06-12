namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public class MessageView : View
    {
        private MessageViewDescriptionData _data = new MessageViewDescriptionData();
        private PreInitializedFields _preInitializedFields;

        internal override void InternalInitialize()
        {
            MessageViewDescription viewDescription = base.ViewDescription as MessageViewDescription;
            if (viewDescription == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString("Microsoft.ManagementConsole.ViewDescription.InvalidViewDescription", new object[] { "MessageView", "MessageViewDescription" }));
            }
            if ((this._preInitializedFields & PreInitializedFields.Title) == PreInitializedFields.None)
            {
                this._data.Title = viewDescription.Title;
            }
            if ((this._preInitializedFields & PreInitializedFields.BodyText) == PreInitializedFields.None)
            {
                this._data.BodyText = viewDescription.BodyText;
            }
            if ((this._preInitializedFields & PreInitializedFields.IconId) == PreInitializedFields.None)
            {
                this._data.IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) viewDescription.IconId;
            }
            if (this._preInitializedFields != PreInitializedFields.None)
            {
                this.Synchronize();
            }
        }

        private void Synchronize()
        {
            if (base.SnapIn.SnapInPlatform == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateClassNotInitializedException("MessageView", "Synchronize");
            }
            UpdateMessageViewCommand command = new UpdateMessageViewCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            command.Data = this._data;
            base.SnapIn.SnapInPlatform.ProcessCommand(command);
        }

        public void Update(string title, string bodyText, Microsoft.ManagementConsole.MessageViewIcon iconId)
        {
            base.ThrowIfShutdown("Update");
            if (!base.Initialized)
            {
                this._preInitializedFields |= PreInitializedFields.Title;
                this._preInitializedFields |= PreInitializedFields.BodyText;
                this._preInitializedFields |= PreInitializedFields.IconId;
                this._data.Title = title;
                this._data.BodyText = bodyText;
                this._data.IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) iconId;
            }
            else
            {
                bool flag = false;
                if (this._data.Title != title)
                {
                    this._data.Title = title;
                    flag = true;
                }
                if (this._data.BodyText != bodyText)
                {
                    this._data.BodyText = bodyText;
                    flag = true;
                }
                if (this._data.IconId != ((Microsoft.ManagementConsole.Internal.MessageViewIcon) ((int) iconId)))
                {
                    this._data.IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) iconId;
                    flag = true;
                }
                if (flag)
                {
                    this.Synchronize();
                }
            }
        }

        public string BodyText
        {
            get
            {
                return this._data.BodyText;
            }
            set
            {
                base.ThrowIfShutdown("BodyText");
                if (!base.Initialized)
                {
                    this._preInitializedFields |= PreInitializedFields.BodyText;
                    this._data.BodyText = value;
                }
                else if (this._data.BodyText != value)
                {
                    this._data.BodyText = value;
                    this.Synchronize();
                }
            }
        }

        public Microsoft.ManagementConsole.MessageViewIcon IconId
        {
            get
            {
                return (Microsoft.ManagementConsole.MessageViewIcon) this._data.IconId;
            }
            set
            {
                base.ThrowIfShutdown("IconId");
                if (!base.Initialized)
                {
                    this._preInitializedFields |= PreInitializedFields.IconId;
                    this._data.IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) value;
                }
                else if (this._data.IconId != ((Microsoft.ManagementConsole.Internal.MessageViewIcon) ((int) value)))
                {
                    this._data.IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) value;
                    this.Synchronize();
                }
            }
        }

        public string Title
        {
            get
            {
                return this._data.Title;
            }
            set
            {
                base.ThrowIfShutdown("Title");
                if (!base.Initialized)
                {
                    this._preInitializedFields |= PreInitializedFields.Title;
                    this._data.Title = value;
                }
                else if (this._data.Title != value)
                {
                    this._data.Title = value;
                    this.Synchronize();
                }
            }
        }

        [Flags]
        private enum PreInitializedFields
        {
            BodyText = 2,
            IconId = 4,
            None = 0,
            Title = 1
        }
    }
}

