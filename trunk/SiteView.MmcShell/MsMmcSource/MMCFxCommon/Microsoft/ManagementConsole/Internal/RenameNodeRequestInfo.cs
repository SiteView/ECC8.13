namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class RenameNodeRequestInfo : NodeRequestInfo
    {
        private string _newDisplayName = string.Empty;

        public string NewDisplayName
        {
            get
            {
                return this._newDisplayName;
            }
            set
            {
                this._newDisplayName = value;
            }
        }
    }
}

