namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class DeleteScopeNodesCommand : Command
    {
        private int[] _ids = new int[0];

        public int[] GetIds()
        {
            return this._ids;
        }

        public void SetIds(int[] ids)
        {
            this._ids = ids;
        }
    }
}

