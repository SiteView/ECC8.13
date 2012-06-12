namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class LoseKeyboardFocusCommandResult : CommandResult
    {
        private bool _focusChanged;

        public bool FocusChanged
        {
            get
            {
                return this._focusChanged;
            }
            set
            {
                this._focusChanged = value;
            }
        }
    }
}

