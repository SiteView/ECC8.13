namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never), Flags]
    public enum StandardVerbs
    {
        Copy = 2,
        Cut = 1,
        Delete = 8,
        None = 0,
        Paste = 4,
        Print = 0x80,
        Properties = 0x10,
        Refresh = 0x40,
        Rename = 0x20
    }
}

