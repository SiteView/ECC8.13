namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SetActivePagePropertySheetCommand : PropertySheetCommand
    {
        private int _newActivePageId = -1;

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

