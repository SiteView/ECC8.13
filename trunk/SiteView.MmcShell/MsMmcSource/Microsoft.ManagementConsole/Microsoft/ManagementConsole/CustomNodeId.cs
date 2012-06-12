namespace Microsoft.ManagementConsole
{
    using System;

    public class CustomNodeId : NodeId
    {
        private byte[] _customId;

        public CustomNodeId()
        {
            this._customId = new byte[0];
        }

        public CustomNodeId(byte[] customId)
        {
            this._customId = new byte[0];
            this.SetCustomId(customId);
        }

        public byte[] GetCustomId()
        {
            return this._customId;
        }

        public void SetCustomId(byte[] customId)
        {
            if (customId == null)
            {
                throw new ArgumentNullException("customId");
            }
            this._customId = customId;
        }
    }
}

