namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public enum SnapInType
    {
        ActionsPane = 2,
        Namespace = 1,
        PropertySheet = 3,
        StandAlone = 0,
        Unknown = -1
    }
}

