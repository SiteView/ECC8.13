namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.ComponentModel;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class BaseCollection : CollectionBase
    {
        private bool _allowDuplicates;
        private object[] _itemsBeingCleared;
        private Type _type;

        internal BaseCollection(Type type)
        {
            this._type = type;
        }

        internal BaseCollection(Type type, bool allowDuplicates) : this(type)
        {
            this._allowDuplicates = allowDuplicates;
        }

        protected void AddRange(object[] items)
        {
            if (items == null)
            {
                throw new ArgumentNullException("items");
            }
            if (items.Length != 0)
            {
                foreach (object obj2 in items)
                {
                    this.OnValidate(obj2, true);
                }
                int count = base.InnerList.Count;
                base.InnerList.AddRange(items);
                try
                {
                    this.OnItemsAdded(count, items);
                }
                catch
                {
                    base.InnerList.RemoveRange(count, items.Length);
                    throw;
                }
            }
        }

        public bool Contains(object item)
        {
            return base.List.Contains(item);
        }

        protected void Insert(int index, object item)
        {
            this.OnValidate(item, true);
            base.InnerList.Insert(index, item);
            try
            {
                this.OnItemsAdded(index, new object[] { item });
            }
            catch
            {
                base.InnerList.Remove(item);
                throw;
            }
        }

        protected void InsertRange(int index, object[] items)
        {
            if (items == null)
            {
                throw new ArgumentNullException("items");
            }
            if (items.Length != 0)
            {
                foreach (object obj2 in items)
                {
                    this.OnValidate(obj2, true);
                }
                base.InnerList.InsertRange(index, items);
                try
                {
                    this.OnItemsAdded(index, items);
                }
                catch
                {
                    base.InnerList.RemoveRange(index, items.Length);
                    throw;
                }
            }
        }

        protected override void OnClear()
        {
            object[] objArray1 = this._itemsBeingCleared;
            this._itemsBeingCleared = base.InnerList.ToArray();
            base.OnClear();
        }

        protected override void OnClearComplete()
        {
            base.OnClearComplete();
            this.OnItemsRemoved(0, this._itemsBeingCleared);
            this._itemsBeingCleared = null;
        }

        protected override void OnInsert(int index, object value)
        {
            this.OnValidate(value, true);
            base.OnInsert(index, value);
        }

        protected override void OnInsertComplete(int index, object value)
        {
            base.OnInsertComplete(index, value);
            this.OnItemsAdded(index, new object[] { value });
        }

        protected virtual void OnItemsAdded(int index, object[] items)
        {
        }

        protected virtual void OnItemsRemoved(int index, object[] items)
        {
        }

        protected override void OnRemove(int index, object value)
        {
            this.OnValidate(value, false);
            base.OnRemove(index, value);
        }

        protected override void OnRemoveComplete(int index, object value)
        {
            base.OnRemoveComplete(index, value);
            this.OnItemsRemoved(index, new object[] { value });
        }

        protected override void OnSet(int index, object oldValue, object newValue)
        {
            if (oldValue != newValue)
            {
                this.OnValidate(oldValue, false);
                this.OnValidate(newValue, true);
                base.OnSet(index, oldValue, newValue);
            }
        }

        protected override void OnSetComplete(int index, object oldValue, object newValue)
        {
            base.OnSetComplete(index, oldValue, newValue);
            this.OnItemsRemoved(index, new object[] { oldValue });
            this.OnItemsAdded(index, new object[] { newValue });
        }

        protected override void OnValidate(object objectToValidate)
        {
            this.OnValidate(objectToValidate, false);
        }

        internal virtual void OnValidate(object objectToValidate, bool testForDuplicate)
        {
            if (objectToValidate == null)
            {
                throw new ArgumentNullException("objectToValidate");
            }
            if (!this._type.IsInstanceOfType(objectToValidate))
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.MmcCollectionBaseOnValidateInvalidType), "objectToValidate");
            }
            if (testForDuplicate && !this._allowDuplicates)
            {
                this.ThrowArgumentExceptionIfDuplicate(objectToValidate);
            }
        }

        internal void ThrowArgumentExceptionIfDuplicate(object value)
        {
            if (base.List.Contains(value))
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionItemInCollection));
            }
        }

        public object SyncRoot
        {
            get
            {
                return base.List.SyncRoot;
            }
        }
    }
}

