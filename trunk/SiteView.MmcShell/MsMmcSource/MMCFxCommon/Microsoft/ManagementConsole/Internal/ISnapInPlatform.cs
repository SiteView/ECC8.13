namespace Microsoft.ManagementConsole.Internal
{
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public interface ISnapInPlatform
    {
        CommandResult ProcessCommand(Command command);
    }
}

