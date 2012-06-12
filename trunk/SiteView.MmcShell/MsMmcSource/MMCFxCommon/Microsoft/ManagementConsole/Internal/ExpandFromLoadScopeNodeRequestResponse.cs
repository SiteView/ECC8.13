namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ExpandFromLoadScopeNodeRequestResponse : RequestResponse
    {
        private bool _handled;

        public bool Handled
        {
            get
            {
                return this._handled;
            }
            set
            {
                this._handled = value;
            }
        }
    }
}

