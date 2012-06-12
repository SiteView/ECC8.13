namespace Microsoft.ManagementConsole
{
    using System;

    [Flags]
    public enum MmcListViewOptions
    {
        All = 0xff,
        AllowPasteOnResultNodes = 0x20,
        AllowUserInitiatedModeChanges = 0x80,
        DisableUserInitiatedSort = 8,
        ExcludeScopeNodes = 4,
        HideSelection = 2,
        None = 0,
        SingleSelect = 1,
        UseCustomSorting = 0x10,
        UseFontLinking = 0x40
    }
}

