namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ConsoleDialogCommand : Command
    {
        private int _ownerId = -1;
        public const int ConsoleWindowOwnerId = -1;

        protected ConsoleDialogCommand()
        {
        }

        public int OwnerId
        {
            get
            {
                return this._ownerId;
            }
            set
            {
                this._ownerId = value;
            }
        }
    }
}

