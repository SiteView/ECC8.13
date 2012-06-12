namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewActionsCommand : ViewCommand
    {
        private ViewActionType _actiontype;
        private ActionsPaneItemCollectionData _data;

        public ViewActionType ActionType
        {
            get
            {
                return this._actiontype;
            }
            set
            {
                this._actiontype = value;
            }
        }

        public ActionsPaneItemCollectionData Data
        {
            get
            {
                return this._data;
            }
            set
            {
                this._data = value;
            }
        }
    }
}

