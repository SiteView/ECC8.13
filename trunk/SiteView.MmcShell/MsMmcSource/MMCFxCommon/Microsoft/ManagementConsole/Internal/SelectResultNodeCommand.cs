namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SelectResultNodeCommand : ViewCommand
    {
        private int _index;
        private bool _scheduled;
        private bool _selectionState;

        public int Index
        {
            get
            {
                return this._index;
            }
            set
            {
                this._index = value;
            }
        }

        public bool Scheduled
        {
            get
            {
                return this._scheduled;
            }
            set
            {
                this._scheduled = value;
            }
        }

        public bool SelectionState
        {
            get
            {
                return this._selectionState;
            }
            set
            {
                this._selectionState = value;
            }
        }
    }
}

