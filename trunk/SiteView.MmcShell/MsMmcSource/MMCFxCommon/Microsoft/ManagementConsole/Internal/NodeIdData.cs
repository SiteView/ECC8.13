namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class NodeIdData
    {
        private byte[] _customId;
        private string _nameId;
        private NodeIdType _type;

        public byte[] GetCustomId()
        {
            return this._customId;
        }

        public void SetCustomId(byte[] customId)
        {
            this._customId = customId;
        }

        public string NameId
        {
            get
            {
                return this._nameId;
            }
            set
            {
                this._nameId = value;
            }
        }

        public NodeIdType Type
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
    }
}

