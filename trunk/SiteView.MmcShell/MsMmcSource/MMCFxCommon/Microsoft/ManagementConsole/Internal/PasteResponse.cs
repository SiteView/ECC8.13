namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PasteResponse : RequestResponse
    {
        private bool _acceptPaste;

        public bool AcceptPaste
        {
            get
            {
                return this._acceptPaste;
            }
            set
            {
                this._acceptPaste = value;
            }
        }
    }
}

