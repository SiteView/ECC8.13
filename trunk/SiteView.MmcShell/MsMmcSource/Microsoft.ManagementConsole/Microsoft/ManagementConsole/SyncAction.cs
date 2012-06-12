namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public sealed class SyncAction : ActionBase
    {
        public event SyncActionEventHandler Triggered;

        public SyncAction() : base(string.Empty, string.Empty, -1, null, true)
        {
        }

        public SyncAction(string displayName, string description) : this(displayName, description, -1)
        {
        }

        public SyncAction(string displayName, string description, int imageIndex) : this(displayName, description, imageIndex, null)
        {
        }

        public SyncAction(string displayName, string description, int imageIndex, object tag) : base(displayName, description, imageIndex, tag, true)
        {
            if (description == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("description", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullValue, new object[0]);
            }
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(displayName, "displayName", true);
        }

        internal void RaiseTriggeredEvent(object sender, SyncStatus status)
        {
            if (this.Triggered != null)
            {
                this.Triggered(sender, new SyncActionEventArgs(this, status));
            }
        }

        public delegate void SyncActionEventHandler(object sender, SyncActionEventArgs e);
    }
}

