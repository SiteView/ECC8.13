namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Diagnostics;
    using System.Reflection;
    using System.Runtime.CompilerServices;
    using System.Threading;

    public sealed class ViewDescriptionCollection : BaseCollection
    {
        private ViewSetData _data;
        private static int _idCounter;
        private Hashtable _idToViewDescription;
        private bool _initialized;

        internal event ViewDescriptionCollectionEventHandler ItemsChanged;

        public ViewDescriptionCollection() : base(typeof(ViewDescription))
        {
            this._idToViewDescription = new Hashtable();
            this._data = new ViewSetData();
            this._data.ViewSetId = Interlocked.Increment(ref _idCounter);
        }

        public int Add(ViewDescription item)
        {
            return base.List.Add(item);
        }

        public void AddRange(ViewDescription[] items)
        {
            base.AddRange(items);
        }

        public bool Contains(ViewDescription item)
        {
            return base.List.Contains(item);
        }

        public void CopyTo(ViewDescription[] array, int index)
        {
            this.CopyTo(array, index);
        }

        internal IMessageClient CreateView(int id, ScopeNode node, int componentId, int viewInstanceId)
        {
            ViewDescription viewDescriptionById = this.GetViewDescriptionById(id);
            if (viewDescriptionById == null)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Information, 12, "ViewDescription id:{0} not found. Cannot create view.", new object[] { id });
                return null;
            }
            return viewDescriptionById.CreateView(node, componentId, viewInstanceId);
        }

        internal ViewDescription GetViewDescriptionById(int id)
        {
            if (!this._idToViewDescription.Contains(id))
            {
                return null;
            }
            return (ViewDescription) this._idToViewDescription[id];
        }

        public int IndexOf(ViewDescription item)
        {
            return base.List.IndexOf(item);
        }

        internal void Initialize()
        {
            if (!this._initialized && (SnapInBase.SnapInInstance.SnapInPlatform != null))
            {
                this._initialized = true;
                this.Synchronize();
            }
        }

        public void Insert(int index, ViewDescription item)
        {
            base.Insert(index, item);
        }

        public void InsertRange(int index, ViewDescription[] items)
        {
            base.InsertRange(index, items);
        }

        private void ItemChanged(object sender, EventArgs e)
        {
            int index = base.List.IndexOf(sender);
            this.Notify(index, new ViewDescription[] { (ViewDescription) sender }, ViewDescriptionCollectionChangeType.Modify);
        }

        private void Notify(int index, ViewDescription[] items, ViewDescriptionCollectionChangeType action)
        {
            if ((this._data.DefaultIndex < 0) || (this._data.DefaultIndex >= base.Count))
            {
                this._data.DefaultIndex = base.Count - 1;
            }
            this.Synchronize();
            if (this.ItemsChanged != null)
            {
                this.ItemsChanged(this, new ViewDescriptionCollectionEventArgs(index, items, action));
            }
        }

        protected override void OnItemsAdded(int index, object[] items)
        {
            foreach (ViewDescription description in items)
            {
                this._idToViewDescription.Add(description.Id, description);
                description.Changed += new EventHandler(this.ItemChanged);
            }
            ViewDescription[] destinationArray = new ViewDescription[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ViewDescriptionCollectionChangeType.Add);
        }

        protected override void OnItemsRemoved(int index, object[] items)
        {
            foreach (ViewDescription description in items)
            {
                this._idToViewDescription.Remove(description.Id);
                description.Changed -= new EventHandler(this.ItemChanged);
            }
            ViewDescription[] destinationArray = new ViewDescription[items.Length];
            Array.Copy(items, destinationArray, items.Length);
            this.Notify(index, destinationArray, ViewDescriptionCollectionChangeType.Remove);
        }

        internal override void OnValidate(object objectToValidate, bool testForDuplicate)
        {
            base.OnValidate(objectToValidate, testForDuplicate);
            ViewDescription description = objectToValidate as ViewDescription;
            if (description != null)
            {
                ViewDescriptionData.ValidateDisplayName(description.DisplayName);
            }
        }

        public void Remove(ViewDescription item)
        {
            base.List.Remove(item);
        }

        internal void Synchronize()
        {
            NamespaceSnapInBase snapInInstance = SnapInBase.SnapInInstance as NamespaceSnapInBase;
            if ((snapInInstance != null) && (snapInInstance.SnapInPlatform != null))
            {
                ViewDescriptionData[] viewDescriptionData = new ViewDescriptionData[base.Count];
                for (int i = 0; i < base.Count; i++)
                {
                    viewDescriptionData[i] = this[i].ViewDescriptionData;
                }
                this._data.SetViewDescriptions(viewDescriptionData);
                SetViewSetDataCommand command = new SetViewSetDataCommand();
                command.ViewSet = this._data;
                snapInInstance.SnapInPlatform.ProcessCommand(command);
            }
        }

        public ViewDescription[] ToArray()
        {
            return (ViewDescription[]) base.InnerList.ToArray(typeof(ViewDescription));
        }

        public int DefaultIndex
        {
            get
            {
                return this._data.DefaultIndex;
            }
            set
            {
                if ((value < 0) || (value >= base.Count))
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("DefaultIndex", value, 0, "ViewDescriptionCollection.Count - 1");
                }
                this._data.DefaultIndex = value;
                this.Synchronize();
            }
        }

        public int Id
        {
            get
            {
                return this._data.ViewSetId;
            }
        }

        public ViewDescription this[int index]
        {
            get
            {
                return (ViewDescription) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }

        internal delegate void ViewDescriptionCollectionEventHandler(object sender, ViewDescriptionCollectionEventArgs e);
    }
}

