namespace Microsoft.ManagementConsole
{
    using System;
    using System.Reflection;
    using System.Runtime.CompilerServices;

    public sealed class NodeSubItemDisplayNameCollection : BaseCollection
    {
        internal event NodeSubItemDisplayNameCollectionEventHandler Changed;

        internal NodeSubItemDisplayNameCollection() : base(typeof(string), true)
        {
        }

        public int Add(string displayName)
        {
            return base.List.Add(displayName);
        }

        public void AddRange(string[] displayNames)
        {
            base.AddRange(displayNames);
        }

        public bool Contains(string displayName)
        {
            return base.List.Contains(displayName);
        }

        public void CopyTo(string[] array, int index)
        {
            this.CopyTo(array, index);
        }

        public int IndexOf(string displayName)
        {
            return base.List.IndexOf(displayName);
        }

        public void Insert(int index, string displayName)
        {
            base.Insert(index, displayName);
        }

        public void InsertRange(int index, string[] displayNames)
        {
            base.InsertRange(index, displayNames);
        }

        private void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this);
            }
        }

        protected override void OnItemsAdded(int index, object[] displayNames)
        {
            this.Notify();
        }

        protected override void OnItemsRemoved(int index, object[] displayNames)
        {
            this.Notify();
        }

        public void Remove(string displayName)
        {
            base.List.Remove(displayName);
        }

        public string[] ToArray()
        {
            return (string[]) base.InnerList.ToArray(typeof(string));
        }

        public string this[int index]
        {
            get
            {
                return (string) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void NodeSubItemDisplayNameCollectionEventHandler(object sender);
    }
}

