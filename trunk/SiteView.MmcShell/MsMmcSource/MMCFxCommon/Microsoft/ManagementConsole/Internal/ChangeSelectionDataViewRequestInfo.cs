namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ChangeSelectionDataViewRequestInfo : ViewRequestInfo
    {
        private int[] _resultNodeIds = new int[0];
        private int[] _scopeNodeIds = new int[0];

        public int[] GetResultNodeIds()
        {
            return this._resultNodeIds;
        }

        public int[] GetScopeNodeIds()
        {
            return this._scopeNodeIds;
        }

        public void SetResultNodeIds(int[] resultNodeIds)
        {
            this._resultNodeIds = resultNodeIds;
        }

        public void SetScopeNodeIds(int[] scopeNodeIds)
        {
            this._scopeNodeIds = scopeNodeIds;
        }
    }
}

