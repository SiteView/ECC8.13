namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class DataCommand : Command
    {
        private int _dataObjectId;
        public const int PrimaryDataObjectId = 0;

        protected DataCommand()
        {
        }

        public int DataObjectId
        {
            get
            {
                return this._dataObjectId;
            }
            set
            {
                this._dataObjectId = value;
            }
        }
    }
}

