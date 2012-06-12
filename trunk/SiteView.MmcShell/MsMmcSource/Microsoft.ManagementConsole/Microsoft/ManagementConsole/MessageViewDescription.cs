namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class MessageViewDescription : ViewDescription
    {
        public MessageViewDescription() : base(typeof(MessageView), new MessageViewDescriptionData())
        {
        }

        public MessageViewDescription(string title, string bodyText, Microsoft.ManagementConsole.MessageViewIcon iconId) : base(typeof(MessageView), new MessageViewDescriptionData(title, bodyText, (Microsoft.ManagementConsole.Internal.MessageViewIcon) iconId))
        {
        }

        public string BodyText
        {
            get
            {
                return ((MessageViewDescriptionData) base.ViewDescriptionData).BodyText;
            }
            set
            {
                ((MessageViewDescriptionData) base.ViewDescriptionData).BodyText = value;
                base.Notify();
            }
        }

        public Microsoft.ManagementConsole.MessageViewIcon IconId
        {
            get
            {
                return (Microsoft.ManagementConsole.MessageViewIcon) ((MessageViewDescriptionData) base.ViewDescriptionData).IconId;
            }
            set
            {
                ((MessageViewDescriptionData) base.ViewDescriptionData).IconId = (Microsoft.ManagementConsole.Internal.MessageViewIcon) value;
                base.Notify();
            }
        }

        public string Title
        {
            get
            {
                return ((MessageViewDescriptionData) base.ViewDescriptionData).Title;
            }
            set
            {
                ((MessageViewDescriptionData) base.ViewDescriptionData).Title = value;
                base.Notify();
            }
        }
    }
}

