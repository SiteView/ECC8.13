namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface ISnapInMessagePumpProxy
    {
        void ExitThread();
        void Run();

        WindowsMessage LastKeyboardMessage { get; }
    }
}

