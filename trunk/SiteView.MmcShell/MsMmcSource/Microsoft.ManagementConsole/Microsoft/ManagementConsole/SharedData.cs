namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.Runtime.CompilerServices;

    public sealed class SharedData
    {
        internal Dictionary<string, SharedDataItem> _dataItems;
        private int _dataObjectId;
        private ISnapInPlatform _snapInPlatform;

        internal event SharedDataChangedEventHandler Changed;

        internal SharedData() : this(0)
        {
        }

        internal SharedData(int dataObjectId)
        {
            this._dataItems = new Dictionary<string, SharedDataItem>();
            this._dataObjectId = dataObjectId;
        }

        public void Add(SharedDataItem item)
        {
            if (item == null)
            {
                throw new ArgumentNullException("item");
            }
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(item.ClipboardFormatId, "ClipboardFormatId", true);
            string key = item.ClipboardFormatId.ToUpper(CultureInfo.InvariantCulture);
            if (this._dataItems.ContainsKey(key))
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.AdvancedSharedDataAddFormatError));
            }
            item.SetSnapInPlatform(this._snapInPlatform, this._dataObjectId);
            this._dataItems.Add(key, item);
            item.Changed += new SharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
            if (this.Changed != null)
            {
                this.NotifyChanged(new SharedDataChangedEventArgs(SharedDataChangeType.Add, item));
            }
        }

        public SharedDataItem GetItem(string clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            string key = clipboardFormatId.ToUpper(CultureInfo.InvariantCulture);
            if (this._dataItems.ContainsKey(key))
            {
                return this._dataItems[key];
            }
            return null;
        }

        private void NotifyChanged(SharedDataChangedEventArgs args)
        {
            if ((this._snapInPlatform != null) && (this.Changed != null))
            {
                this.Changed(this, args);
            }
        }

        private void OnSharedDataChanged(object sender, SharedDataChangedEventArgs e)
        {
            if (this.Changed != null)
            {
                this.Changed(this, e);
            }
        }

        internal void ProcessChangeNotification(DataChangeNotification notification)
        {
            string[] removedClipboardFormatIds = notification.GetRemovedClipboardFormatIds();
            string[] changedClipboardFormatIds = notification.GetChangedClipboardFormatIds();
            if ((removedClipboardFormatIds != null) && (removedClipboardFormatIds.Length > 0))
            {
                foreach (string str in removedClipboardFormatIds)
                {
                    this._dataItems.Remove(str);
                }
            }
            if ((changedClipboardFormatIds != null) && (changedClipboardFormatIds.Length > 0))
            {
                foreach (string str2 in changedClipboardFormatIds)
                {
                    if (this._dataItems.ContainsKey(str2))
                    {
                        this._dataItems[str2].Notify();
                    }
                }
            }
        }

        public void Remove(string clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            string key = clipboardFormatId.ToUpper(CultureInfo.InvariantCulture);
            if (this._dataItems.ContainsKey(key))
            {
                SharedDataItem publishedDataItem = this._dataItems[key];
                this._dataItems.Remove(key);
                publishedDataItem.Changed -= new SharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
                this.NotifyChanged(new SharedDataChangedEventArgs(SharedDataChangeType.Remove, publishedDataItem));
            }
        }

        internal void SetSnapInPlatform(ISnapInPlatform snapInPlatform)
        {
            this._snapInPlatform = snapInPlatform;
            Dictionary<string, SharedDataItem>.ValueCollection.Enumerator enumerator = this._dataItems.Values.GetEnumerator();
            try
            {
                while (enumerator.MoveNext())
                {
                    enumerator.Current.SetSnapInPlatform(this._snapInPlatform, this._dataObjectId);
                }
            }
            finally
            {
                enumerator.Dispose();
            }
        }

        internal int DataObjectId
        {
            get
            {
                return this._dataObjectId;
            }
        }

        internal delegate void SharedDataChangedEventHandler(object sender, SharedDataChangedEventArgs e);
    }
}

