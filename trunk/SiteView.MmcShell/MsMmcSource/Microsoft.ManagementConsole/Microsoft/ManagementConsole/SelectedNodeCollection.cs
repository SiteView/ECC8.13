namespace Microsoft.ManagementConsole
{
    using System;
    using System.Collections;
    using System.Reflection;

    public sealed class SelectedNodeCollection : ICollection, IEnumerable
    {
        private ArrayList _list = new ArrayList();

        internal SelectedNodeCollection()
        {
        }

        internal void Add(Node item)
        {
            this._list.Add(item);
        }

        internal void Clear()
        {
            this._list.Clear();
        }

        public bool Contains(Node node)
        {
            return this._list.Contains(node);
        }

        public void CopyTo(Node[] array, int index)
        {
            this._list.CopyTo(array, index);
        }

        public int IndexOf(Node node)
        {
            return this._list.IndexOf(node);
        }

        void ICollection.CopyTo(Array array, int index)
        {
            this._list.CopyTo(array, index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this._list.GetEnumerator();
        }

        public Node[] ToArray()
        {
            return (Node[]) this._list.ToArray(typeof(Node));
        }

        public int Count
        {
            get
            {
                return this._list.Count;
            }
        }

        public Node this[int index]
        {
            get
            {
                return (Node) this._list[index];
            }
        }

        bool ICollection.IsSynchronized
        {
            get
            {
                return this._list.IsSynchronized;
            }
        }

        object ICollection.SyncRoot
        {
            get
            {
                return this._list.SyncRoot;
            }
        }
    }
}

