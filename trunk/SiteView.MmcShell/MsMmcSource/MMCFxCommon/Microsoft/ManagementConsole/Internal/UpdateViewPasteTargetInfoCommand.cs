namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewPasteTargetInfoCommand : ViewCommand
    {
        private Microsoft.ManagementConsole.Internal.PasteTargetInfo _pasteTargetInfo;

        public Microsoft.ManagementConsole.Internal.PasteTargetInfo PasteTargetInfo
        {
            get
            {
                return this._pasteTargetInfo;
            }
            set
            {
                this._pasteTargetInfo = value;
            }
        }
    }
}

