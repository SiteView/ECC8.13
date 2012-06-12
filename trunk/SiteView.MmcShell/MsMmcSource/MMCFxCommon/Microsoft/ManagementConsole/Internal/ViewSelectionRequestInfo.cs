namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ViewSelectionRequestInfo : ViewRequestInfo
    {
        private int _selectionId;

        protected ViewSelectionRequestInfo()
        {
        }

        public int SelectionId
        {
            get
            {
                return this._selectionId;
            }
            set
            {
                this._selectionId = value;
            }
        }
    }
}

