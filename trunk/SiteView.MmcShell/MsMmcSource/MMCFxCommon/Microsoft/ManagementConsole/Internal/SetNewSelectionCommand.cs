namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SetNewSelectionCommand : ViewCommand
    {
        private int _id = -1;
        private Microsoft.ManagementConsole.Internal.SelectionCardinality _type;
        private Guid[] _uniqueNodeTypes;
        private SharedDataObjectUpdate _updatedDataObject;

        public int Id
        {
            get
            {
                return this._id;
            }
            set
            {
                this._id = value;
            }
        }

        public Microsoft.ManagementConsole.Internal.SelectionCardinality SelectionCardinality
        {
            get
            {
                return this._type;
            }
            set
            {
                this._type = value;
            }
        }

        public Guid[] UniqueNodeTypes
        {
            get
            {
                return this._uniqueNodeTypes;
            }
            set
            {
                this._uniqueNodeTypes = value;
            }
        }

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

