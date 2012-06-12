namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class CreatePropertySheetForViewCommand : CreatePropertySheetCommand
    {
        private int _viewId = -1;

        public int ViewId
        {
            get
            {
                return this._viewId;
            }
            set
            {
                this._viewId = value;
            }
        }
    }
}

