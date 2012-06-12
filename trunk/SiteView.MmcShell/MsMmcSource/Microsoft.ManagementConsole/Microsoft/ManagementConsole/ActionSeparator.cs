namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class ActionSeparator : ActionsPaneItem
    {
        private ActionSeparatorItemData _data = new ActionSeparatorItemData();

        public ActionSeparator()
        {
            base.Data = this._data;
        }
    }
}

