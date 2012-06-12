﻿namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public enum RequestState
    {
        Synchronous,
        Pending,
        Complete
    }
}
