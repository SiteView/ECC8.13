namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SaveViewDataRequestInfo : ViewRequestInfo
    {
        private bool _clearModified;

        public bool ClearModified
        {
            get
            {
                return this._clearModified;
            }
            set
            {
                this._clearModified = value;
            }
        }
    }
}

