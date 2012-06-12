namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PersistenceKeyRetrievalCompletedResponse : RequestResponse
    {
        private string _persistenceKey;

        public string PersistenceKey
        {
            get
            {
                return this._persistenceKey;
            }
            set
            {
                this._persistenceKey = value;
            }
        }
    }
}

