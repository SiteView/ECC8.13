namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PropertyPageMessageResponse : RequestResponse
    {
        private bool _allowRequestedOperation;
        private int _newActivePageId = -1;

        public bool AllowRequestedOperation
        {
            get
            {
                return this._allowRequestedOperation;
            }
            set
            {
                this._allowRequestedOperation = value;
            }
        }

        public int NewActivePageId
        {
            get
            {
                return this._newActivePageId;
            }
            set
            {
                this._newActivePageId = value;
            }
        }
    }
}

