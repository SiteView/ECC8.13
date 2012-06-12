namespace Microsoft.ManagementConsole
{
    using System;

    internal class NodeChangedEventArgs : EventArgs
    {
        private Node _source;

        public NodeChangedEventArgs(Node source)
        {
            this.Source = source;
        }

        public Node Source
        {
            get
            {
                return this._source;
            }
            set
            {
                this._source = value;
            }
        }
    }
}

