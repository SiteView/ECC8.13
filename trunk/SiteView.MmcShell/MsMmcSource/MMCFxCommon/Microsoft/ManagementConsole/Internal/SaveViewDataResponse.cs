namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SaveViewDataResponse : RequestResponse
    {
        private byte[] _dataBlob;

        public byte[] GetDataBlob()
        {
            return this._dataBlob;
        }

        public void SetDataBlob(byte[] data)
        {
            this._dataBlob = data;
        }
    }
}

