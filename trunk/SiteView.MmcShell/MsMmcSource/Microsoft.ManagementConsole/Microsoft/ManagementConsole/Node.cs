namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Runtime.CompilerServices;
    using System.Threading;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class Node
    {
        private NodeData _data;
        private static int _idCounter;
        private NamespaceSnapInBase _snapIn;
        private NodeSubItemDisplayNameCollection _subItemDisplayNames;
        private object _tag;

        internal event NodeChangedEventHandler Changed;

        internal Node()
        {
        }

        internal void Initialize(NodeData data)
        {
            this.Data = data;
            this._snapIn = SnapInBase.SnapInInstance as NamespaceSnapInBase;
            if (this._snapIn == null)
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonWrongThread, new object[] { "Node" }));
            }
            if (_idCounter == 0x7fffffff)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "The max value for Node identifiers has been reached; no new nodes can be created.");
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionMMCOutOfResources));
            }
            this.Data.Id = Interlocked.Increment(ref _idCounter);
        }

        internal void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, new NodeChangedEventArgs(this));
            }
        }

        private void OnSubItemsChanged(object source)
        {
            NodeSubItemData[] subItems = new NodeSubItemData[this.SubItemDisplayNames.Count];
            int num = 0;
            foreach (string str in this.SubItemDisplayNames)
            {
                NodeSubItemData data = new NodeSubItemData();
                data.DisplayName = str;
                subItems[num++] = data;
            }
            this.Data.SetSubItems(subItems);
            this.Notify();
        }

        internal NodeData Data
        {
            get
            {
                return this._data;
            }
            set
            {
                this._data = value;
            }
        }

        public string DisplayName
        {
            get
            {
                return this.Data.DisplayName;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (this.Data.DisplayName != value)
                {
                    this.Data.DisplayName = value;
                    this.Notify();
                }
            }
        }

        protected internal int Id
        {
            get
            {
                return this.Data.Id;
            }
        }

        public int ImageIndex
        {
            get
            {
                return this.Data.ImageIndex;
            }
            set
            {
                if (this.Data.ImageIndex != value)
                {
                    this.Data.ImageIndex = value;
                    this.Notify();
                }
            }
        }

        public NamespaceSnapInBase SnapIn
        {
            get
            {
                return this._snapIn;
            }
        }

        public NodeSubItemDisplayNameCollection SubItemDisplayNames
        {
            get
            {
                if (this._subItemDisplayNames == null)
                {
                    this._subItemDisplayNames = new NodeSubItemDisplayNameCollection();
                    this._subItemDisplayNames.Changed += new NodeSubItemDisplayNameCollection.NodeSubItemDisplayNameCollectionEventHandler(this.OnSubItemsChanged);
                }
                return this._subItemDisplayNames;
            }
            set
            {
                if (this._subItemDisplayNames != null)
                {
                    this._subItemDisplayNames.Changed -= new NodeSubItemDisplayNameCollection.NodeSubItemDisplayNameCollectionEventHandler(this.OnSubItemsChanged);
                }
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._subItemDisplayNames = value;
                this._subItemDisplayNames.Changed += new NodeSubItemDisplayNameCollection.NodeSubItemDisplayNameCollectionEventHandler(this.OnSubItemsChanged);
                this.OnSubItemsChanged(this._subItemDisplayNames);
            }
        }

        public object Tag
        {
            get
            {
                return this._tag;
            }
            set
            {
                this._tag = value;
            }
        }

        internal delegate void NodeChangedEventHandler(object sender, NodeChangedEventArgs e);
    }
}

