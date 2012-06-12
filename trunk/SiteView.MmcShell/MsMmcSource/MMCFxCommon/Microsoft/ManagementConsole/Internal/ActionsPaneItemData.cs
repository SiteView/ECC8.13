namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ActionsPaneItemData
    {
        private int _id;
        private ActionsInsertionLocation _insertionLocation;

        protected ActionsPaneItemData()
        {
        }

        public virtual void Validate()
        {
        }

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

        public ActionsInsertionLocation InsertionLocation
        {
            get
            {
                return this._insertionLocation;
            }
            set
            {
                this._insertionLocation = value;
            }
        }
    }
}

