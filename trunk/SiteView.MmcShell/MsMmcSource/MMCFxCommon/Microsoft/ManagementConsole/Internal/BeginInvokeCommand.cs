﻿namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class BeginInvokeCommand : Command
    {
        private int _id = -1;

        public int Id
        {
            get
            {
                return this._id;
            }
            set
            {
                this._id = value;
            }
        }
    }
}

