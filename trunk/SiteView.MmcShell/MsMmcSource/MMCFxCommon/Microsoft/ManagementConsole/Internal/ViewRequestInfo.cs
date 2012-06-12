﻿namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ViewRequestInfo : RequestInfo
    {
        protected ViewRequestInfo()
        {
        }
    }
}

