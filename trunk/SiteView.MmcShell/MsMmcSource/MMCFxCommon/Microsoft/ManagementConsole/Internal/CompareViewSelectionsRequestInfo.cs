namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class CompareViewSelectionsRequestInfo : ViewSelectionRequestInfo
    {
        private int _selectionIdToCompare = -1;

        public int SelectionIdToCompare
        {
            get
            {
                return this._selectionIdToCompare;
            }
            set
            {
                this._selectionIdToCompare = value;
            }
        }
    }
}

