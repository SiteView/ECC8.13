namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public class ResultNode : Node
    {
        private NodeData _data = new NodeData();
        private MmcListView _listView;

        public ResultNode()
        {
            base.Initialize(this._data);
        }

        public void SendSelectionRequest(bool selected)
        {
            if (this._listView == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ResultNodeSendSelectionRequestMustBeAddedToListView));
            }
            this._listView.ChangeResultNodeSelection(this, selected);
        }

        internal MmcListView ListView
        {
            get
            {
                return this._listView;
            }
            set
            {
                this._listView = value;
            }
        }
    }
}

