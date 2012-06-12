namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Drawing;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ShowContextMenuCommand : ViewCommand
    {
        private bool _onResultItem;
        private System.Drawing.Point _point;

        public bool OnResultItem
        {
            get
            {
                return this._onResultItem;
            }
            set
            {
                this._onResultItem = value;
            }
        }

        public System.Drawing.Point Point
        {
            get
            {
                return this._point;
            }
            set
            {
                this._point = value;
            }
        }
    }
}

