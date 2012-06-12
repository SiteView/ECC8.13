namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Flags, EditorBrowsable(EditorBrowsableState.Never)]
    public enum ActionStates
    {
        Bulleted = 4,
        Checked = 2,
        Enabled = 1
    }
}

