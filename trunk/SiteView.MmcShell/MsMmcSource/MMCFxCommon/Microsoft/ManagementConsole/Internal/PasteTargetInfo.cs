namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PasteTargetInfo
    {
        private string[] _allowedClipboardFormats;
        private DragAndDropVerb _defaultDragAndDropVerb;

        public string[] GetAllowedClipboardFormats()
        {
            return this._allowedClipboardFormats;
        }

        public void SetAllowedClipboardFormats(string[] allowedClipboardFormats)
        {
            this._allowedClipboardFormats = (allowedClipboardFormats != null) ? ((string[]) allowedClipboardFormats.Clone()) : null;
        }

        public DragAndDropVerb DefaultDragAndDropVerb
        {
            get
            {
                return this._defaultDragAndDropVerb;
            }
            set
            {
                this._defaultDragAndDropVerb = value;
            }
        }
    }
}

