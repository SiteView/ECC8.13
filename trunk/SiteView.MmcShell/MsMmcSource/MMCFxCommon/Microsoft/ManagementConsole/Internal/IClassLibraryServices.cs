namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface IClassLibraryServices
    {
        ISnapInMessagePumpProxy CreateMessagePumpProxy();
        ISnapInClient CreateSnapIn(string assemblyName, string typeName);
    }
}

