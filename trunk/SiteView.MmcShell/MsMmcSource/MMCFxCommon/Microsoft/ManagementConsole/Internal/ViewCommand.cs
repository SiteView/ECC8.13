namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ViewCommand : Command
    {
        private int _viewInstanceId;

        protected ViewCommand()
        {
        }

        public int ViewInstanceId
        {
            get
            {
                return this._viewInstanceId;
            }
            set
            {
                this._viewInstanceId = value;
            }
        }
    }
}

