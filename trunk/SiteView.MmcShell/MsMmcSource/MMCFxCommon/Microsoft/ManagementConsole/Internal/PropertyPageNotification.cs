namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class PropertyPageNotification : Notification
    {
        private int _pageId = -1;
        private int _sheetId = -1;

        protected PropertyPageNotification()
        {
        }

        public int PageId
        {
            get
            {
                return this._pageId;
            }
            set
            {
                this._pageId = value;
            }
        }

        public int SheetId
        {
            get
            {
                return this._sheetId;
            }
            set
            {
                this._sheetId = value;
            }
        }
    }
}

