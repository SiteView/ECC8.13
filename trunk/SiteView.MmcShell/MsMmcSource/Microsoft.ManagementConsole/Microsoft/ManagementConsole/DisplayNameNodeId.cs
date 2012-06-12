namespace Microsoft.ManagementConsole
{
    using System;

    public class DisplayNameNodeId : NodeId
    {
        private string _displayName;

        public DisplayNameNodeId()
        {
        }

        public DisplayNameNodeId(string displayName)
        {
            this.DisplayName = displayName;
        }

        public string DisplayName
        {
            get
            {
                return this._displayName;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._displayName = value;
            }
        }
    }
}

