namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class FindPropertySheetForViewCommand : FindPropertySheetCommand
    {
        private int _selectionId = -1;

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

