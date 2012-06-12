namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface IMessageClient
    {
        void ProcessNotification(Notification notification);
        void ProcessRequest(Request request);
    }
}

