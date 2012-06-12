namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class FindPropertySheetCommandResult : CommandResult
    {
        private bool _sheetExists;

        public bool SheetExists
        {
            get
            {
                return this._sheetExists;
            }
            set
            {
                this._sheetExists = value;
            }
        }
    }
}

