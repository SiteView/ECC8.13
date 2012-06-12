namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ComponentAbandonedNotification : Notification
    {
        private int _id;

        public ComponentAbandonedNotification(int componentId)
        {
            this._id = componentId;
        }

        public int Id
        {
            get
            {
                return this._id;
            }
        }
    }
}

