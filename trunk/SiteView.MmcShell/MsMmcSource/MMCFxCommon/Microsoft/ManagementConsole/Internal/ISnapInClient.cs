namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface ISnapInClient : IMessageClient
    {
        IMessageClient CreateView(int nodeId, int componentId, int viewDescriptionId, int viewInstanceId);
        void Initialize(ISnapInPlatform snapInPlatform);
    }
}

