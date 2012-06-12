namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateSnapInConfigCommand : Command
    {
        private TimeSpan _waitDialogDelay;

        public TimeSpan WaitDialogDelay
        {
            get
            {
                return this._waitDialogDelay;
            }
            set
            {
                this._waitDialogDelay = value;
            }
        }
    }
}

