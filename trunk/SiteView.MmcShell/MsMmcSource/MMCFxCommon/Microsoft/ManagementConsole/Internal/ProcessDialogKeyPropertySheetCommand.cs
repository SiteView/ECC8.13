namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ProcessDialogKeyPropertySheetCommand : PropertySheetCommand
    {
        private Keys _keyData;

        public Keys KeyData
        {
            get
            {
                return this._keyData;
            }
            set
            {
                this._keyData = value;
            }
        }
    }
}

