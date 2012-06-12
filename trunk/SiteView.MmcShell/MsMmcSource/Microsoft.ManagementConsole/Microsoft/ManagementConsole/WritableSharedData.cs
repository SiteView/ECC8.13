namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.Runtime.CompilerServices;

    public sealed class WritableSharedData
    {
        internal Dictionary<string, WritableSharedDataItem> _dataItems = new Dictionary<string, WritableSharedDataItem>();

        internal event WritableSharedDataItem.SharedDataChangedEventHandler Changed;

        internal event WritableSharedDataItem.SharedDataChangeRequestEventHandler PropertyChangeRequested;

        public void Add(WritableSharedDataItem item)
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
            this._dataItems.Add(key, item);
            item.Changed += new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
            item.PropertyChangeRequested += new WritableSharedDataItem.SharedDataChangeRequestEventHandler(this.OnPropertyChangeRequested);
            if (this.Changed != null)
            {
                this.Changed(this, new WritableSharedDataChangedEventArgs(WritableSharedDataChangeType.Add, item));
            }
        }

        public WritableSharedDataItem GetItem(string clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            string key = clipboardFormatId.ToUpper(CultureInfo.InvariantCulture);
            if (this._dataItems.ContainsKey(key))
            {
                return this._dataItems[key];
            }
            return null;
        }

        internal WritableSharedDataItem[] GetItems()
        {
            WritableSharedDataItem[] array = new WritableSharedDataItem[this._dataItems.Values.Count];
            this._dataItems.Values.CopyTo(array, 0);
            return array;
        }

        private void OnPropertyChangeRequested(object sender, WritableSharedDataChangeRequestEventArgs e)
        {
            if (this.PropertyChangeRequested != null)
            {
                this.PropertyChangeRequested(this, e);
            }
        }

        private void OnSharedDataChanged(object sender, WritableSharedDataChangedEventArgs e)
        {
            if (this.Changed != null)
            {
                this.Changed(this, e);
            }
        }

        public void Remove(string clipboardFormatId)
        {
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(clipboardFormatId, "clipboardFormatId", true);
            string key = clipboardFormatId.ToUpper(CultureInfo.InvariantCulture);
            if (this._dataItems.ContainsKey(key))
            {
                WritableSharedDataItem publishedDataItem = this._dataItems[key];
                this._dataItems.Remove(key);
                publishedDataItem.Changed -= new WritableSharedDataItem.SharedDataChangedEventHandler(this.OnSharedDataChanged);
                publishedDataItem.PropertyChangeRequested -= new WritableSharedDataItem.SharedDataChangeRequestEventHandler(this.OnPropertyChangeRequested);
                if (this.Changed != null)
                {
                    this.Changed(this, new WritableSharedDataChangedEventArgs(WritableSharedDataChangeType.Remove, publishedDataItem));
                }
            }
        }
    }
}

