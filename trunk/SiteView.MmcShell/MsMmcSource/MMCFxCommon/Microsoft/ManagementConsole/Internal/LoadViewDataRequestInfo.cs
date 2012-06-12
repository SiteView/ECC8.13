namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class LoadViewDataRequestInfo : ViewRequestInfo
    {
        private byte[] _dataBlob;

        public byte[] GetDataBlob()
        {
            return this._dataBlob;
        }

        public void SetDataBlob(byte[] dataBlob)
        {
            if (this._dataBlob != dataBlob)
            {
                this._dataBlob = dataBlob;
            }
        }
    }
}

