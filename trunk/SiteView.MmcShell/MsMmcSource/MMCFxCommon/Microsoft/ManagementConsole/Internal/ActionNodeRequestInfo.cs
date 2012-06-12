namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ActionNodeRequestInfo : NodeRequestInfo
    {
        private int _actionId;

        public int ActionId
        {
            get
            {
                return this._actionId;
            }
            set
            {
                this._actionId = value;
            }
        }
    }
}

