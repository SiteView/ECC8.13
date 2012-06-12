namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateSnapInCommand : Command
    {
        private Microsoft.ManagementConsole.Internal.SnapInData _snapInData;

        public Microsoft.ManagementConsole.Internal.SnapInData SnapInData
        {
            get
            {
                return this._snapInData;
            }
            set
            {
                this._snapInData = value;
            }
        }
    }
}

