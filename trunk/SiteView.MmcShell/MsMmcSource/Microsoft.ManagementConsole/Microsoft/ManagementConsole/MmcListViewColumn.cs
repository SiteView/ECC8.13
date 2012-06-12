namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public class MmcListViewColumn
    {
        private ColumnData _data;
        private MmcListView _listView;

        internal event ColumnChangedEventHandler Changed;

        public MmcListViewColumn()
        {
            this._data = new ColumnData();
        }

        public MmcListViewColumn(string title) : this()
        {
            this._data.Title = title;
        }

        public MmcListViewColumn(string title, int width) : this(title)
        {
            this._data.Width = width;
        }

        public MmcListViewColumn(string title, int width, MmcListViewColumnFormat format) : this(title, width)
        {
            this._data.Format = (ListViewColumnFormat) format;
        }

        public MmcListViewColumn(string title, int width, MmcListViewColumnFormat format, bool visible) : this(title, width, format)
        {
            this._data.Visible = visible;
        }

        private void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, new EventArgs());
            }
        }

        public void SetWidth(int width)
        {
            this._data.Width = width;
            this.Notify();
        }

        internal ColumnData Data
        {
            get
            {
                return this._data;
            }
        }

        public MmcListViewColumnFormat Format
        {
            get
            {
                return (MmcListViewColumnFormat) this._data.Format;
            }
            set
            {
                if (this._listView != null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnFormatInvalidChange));
                }
                ListViewColumnFormat format = this._data.Format;
                this._data.Format = (ListViewColumnFormat) value;
                if (format != this._data.Format)
                {
                    this.Notify();
                }
            }
        }

        internal int Id
        {
            get
            {
                return this._data.Id;
            }
        }

        internal MmcListView ListView
        {
            get
            {
                return this._listView;
            }
            set
            {
                this._listView = value;
            }
        }

        public string Title
        {
            get
            {
                return this._data.Title;
            }
            set
            {
                string title = this._data.Title;
                this._data.Title = value;
                if (title != this._data.Title)
                {
                    this.Notify();
                }
            }
        }

        public bool Visible
        {
            get
            {
                return this._data.Visible;
            }
            set
            {
                if (this._listView != null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ColumnVisibleInvalidChange));
                }
                bool visible = this._data.Visible;
                this._data.Visible = value;
                if (visible != this._data.Visible)
                {
                    this.Notify();
                }
            }
        }

        internal delegate void ColumnChangedEventHandler(object sender, EventArgs e);
    }
}

