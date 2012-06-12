namespace Microsoft.ManagementConsole.Internal
{
    using System;

    internal class TestSnapInPlatform : ISnapInPlatform
    {
        private Delegate _processCommandCallback;

        public TestSnapInPlatform(Delegate processCommandCallback)
        {
            if (processCommandCallback == null)
            {
                throw new ArgumentNullException("processCommandCallback");
            }
            this._processCommandCallback = processCommandCallback;
        }

        public CommandResult ProcessCommand(Command command)
        {
            return (CommandResult) this._processCommandCallback.DynamicInvoke(new object[] { command });
        }
    }
}

