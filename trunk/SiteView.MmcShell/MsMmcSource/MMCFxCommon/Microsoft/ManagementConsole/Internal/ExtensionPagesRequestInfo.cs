﻿namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ExtensionPagesRequestInfo : RequestInfo
    {
        private int _sheetId = -1;

        public int SheetId
        {
            get
            {
                return this._sheetId;
            }
            set
            {
                this._sheetId = value;
            }
        }
    }
}
