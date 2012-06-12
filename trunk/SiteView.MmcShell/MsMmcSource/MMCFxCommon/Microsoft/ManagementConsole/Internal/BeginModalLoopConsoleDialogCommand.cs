namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class BeginModalLoopConsoleDialogCommand : ConsoleDialogCommand
    {
        public static readonly TimeSpan DefaultTimeout = new TimeSpan(0, 0, 2);
        public static readonly TimeSpan MaxTimeout = new TimeSpan(0, 0, 20);
    }
}

