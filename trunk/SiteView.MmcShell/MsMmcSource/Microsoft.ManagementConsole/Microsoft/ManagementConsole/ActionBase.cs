namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ActionBase : ActionsPaneExtendedItem
    {
        private ActionData _data = new ActionData();

        internal ActionBase(string displayName, string description, int imageIndex, object tag, bool executeSync)
        {
            base.Initialize(this._data, displayName, description, imageIndex, tag);
            this._data.ExecuteSync = executeSync;
        }

        private bool IsStateSet(Microsoft.ManagementConsole.ActionStates state)
        {
            return ((this._data.State & ((Microsoft.ManagementConsole.Internal.ActionStates) ((int) state))) != 0);
        }

        private bool SetActionState(Microsoft.ManagementConsole.ActionStates state, bool value)
        {
            if (this.IsStateSet(state) == value)
            {
                return false;
            }
            if (value)
            {
                this._data.State |= (Microsoft.ManagementConsole.Internal.ActionStates) ((int) state);
            }
            else
            {
                this._data.State &= (Microsoft.ManagementConsole.Internal.ActionStates) ((int) ~state);
            }
            return true;
        }

        public bool Bulleted
        {
            get
            {
                return this.IsStateSet(Microsoft.ManagementConsole.ActionStates.Bulleted);
            }
            set
            {
                if (this.IsStateSet(Microsoft.ManagementConsole.ActionStates.Bulleted) != value)
                {
                    if (value)
                    {
                        this.SetActionState(Microsoft.ManagementConsole.ActionStates.Checked, false);
                    }
                    this.SetActionState(Microsoft.ManagementConsole.ActionStates.Bulleted, value);
                    base.Notify();
                }
            }
        }

        public bool Checked
        {
            get
            {
                return this.IsStateSet(Microsoft.ManagementConsole.ActionStates.Checked);
            }
            set
            {
                if (this.IsStateSet(Microsoft.ManagementConsole.ActionStates.Checked) != value)
                {
                    if (value)
                    {
                        this.SetActionState(Microsoft.ManagementConsole.ActionStates.Bulleted, false);
                    }
                    this.SetActionState(Microsoft.ManagementConsole.ActionStates.Checked, value);
                    base.Notify();
                }
            }
        }

        public bool Enabled
        {
            get
            {
                return this.IsStateSet(Microsoft.ManagementConsole.ActionStates.Enabled);
            }
            set
            {
                if (this.SetActionState(Microsoft.ManagementConsole.ActionStates.Enabled, value))
                {
                    base.Notify();
                }
            }
        }
    }
}

