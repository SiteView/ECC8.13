namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class LoseKeyboardFocusCommand : ViewCommand
    {
        private bool _forward;

        public bool Forward
        {
            get
            {
                return this._forward;
            }
            set
            {
                this._forward = value;
            }
        }
    }
}

