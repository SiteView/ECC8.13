namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ActionViewRequestInfo : ViewSelectionRequestInfo
    {
        private int _actionId;
        private bool _selectionDependent;

        public int ActionId
        {
            get
            {
                return this._actionId;
            }
            set
            {
                this._actionId = value;
            }
        }

        public bool SelectionDependent
        {
            get
            {
                return this._selectionDependent;
            }
            set
            {
                this._selectionDependent = value;
            }
        }
    }
}

