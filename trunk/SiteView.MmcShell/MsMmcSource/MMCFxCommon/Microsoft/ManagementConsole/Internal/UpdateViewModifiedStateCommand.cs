namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewModifiedStateCommand : ViewCommand
    {
        private bool _isModified;

        public bool IsModified
        {
            get
            {
                return this._isModified;
            }
            set
            {
                this._isModified = value;
            }
        }
    }
}

