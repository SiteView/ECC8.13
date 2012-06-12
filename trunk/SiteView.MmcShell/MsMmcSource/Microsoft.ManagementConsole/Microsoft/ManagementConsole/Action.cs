namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public sealed class Action : ActionBase
    {
        public event ActionEventHandler Triggered;

        public Action() : base(string.Empty, string.Empty, -1, null, false)
        {
        }

        public Action(string displayName, string description) : this(displayName, description, -1)
        {
        }

        public Action(string displayName, string description, int imageIndex) : this(displayName, description, imageIndex, null)
        {
        }

        public Action(string displayName, string description, int imageIndex, object tag) : base(displayName, description, imageIndex, tag, false)
        {
            if (description == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("description", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullValue, new object[0]);
            }
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(displayName, "displayName", true);
        }

        internal void RaiseTriggeredEvent(object sender, AsyncStatus status)
        {
            if (this.Triggered != null)
            {
                this.Triggered(sender, new ActionEventArgs(this, status));
            }
        }

        public delegate void ActionEventHandler(object sender, ActionEventArgs e);
    }
}

