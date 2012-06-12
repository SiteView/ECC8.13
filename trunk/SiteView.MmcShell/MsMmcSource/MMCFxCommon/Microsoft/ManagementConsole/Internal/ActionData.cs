namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ActionData : ActionsPaneExtendedItemData
    {
        private bool _executeSync;
        private ActionStates _state = ActionStates.Enabled;

        public bool ExecuteSync
        {
            get
            {
                return this._executeSync;
            }
            set
            {
                this._executeSync = value;
            }
        }

        public ActionStates State
        {
            get
            {
                return this._state;
            }
            set
            {
                this._state = value;
            }
        }
    }
}

