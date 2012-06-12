namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewSharedDataCommand : ViewCommand
    {
        private SharedDataObjectUpdate _updatedDataObject;

        public SharedDataObjectUpdate UpdatedSharedData
        {
            get
            {
                return this._updatedDataObject;
            }
            set
            {
                this._updatedDataObject = value;
            }
        }
    }
}

