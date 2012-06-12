namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SetViewSetDataCommand : Command
    {
        private ViewSetData _viewSet;

        public ViewSetData ViewSet
        {
            get
            {
                return this._viewSet;
            }
            set
            {
                this._viewSet = value;
            }
        }
    }
}

