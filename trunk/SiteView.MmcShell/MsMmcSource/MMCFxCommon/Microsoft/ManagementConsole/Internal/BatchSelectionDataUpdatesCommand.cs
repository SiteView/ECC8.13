namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class BatchSelectionDataUpdatesCommand : ViewCommand
    {
        private bool _begin;

        public bool Begin
        {
            get
            {
                return this._begin;
            }
            set
            {
                this._begin = value;
            }
        }
    }
}

