namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Globalization;
    using System.Threading;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ColumnData
    {
        private ListViewColumnFormat _format;
        private int _id = -1;
        private static int _identifierSeed;
        private string _title = string.Empty;
        private bool _visible = true;
        private int _width = -1;
        private const int MaxPath = 0xff;

        public ColumnData()
        {
            if (_identifierSeed == 0x7fffffff)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "The max value for Column identifiers has been reached; no new columns can be created.");
                throw new Exception(Utility.LoadResourceString(Strings.ExceptionMMCOutOfResources));
            }
            this._id = Interlocked.Increment(ref _identifierSeed);
        }

        public void Validate()
        {
            ValidateTitle(this._title);
            ValidateWidth(this._width);
            ValidateFormat(this._format);
        }

        public static void ValidateFormat(ListViewColumnFormat format)
        {
            if (((format != ListViewColumnFormat.Left) && (format != ListViewColumnFormat.Center)) && (format != ListViewColumnFormat.Right))
            {
                throw Utility.CreateArgumentOutOfRangeException("format", (int) format, ListViewColumnFormat.Left.ToString(), ListViewColumnFormat.Right.ToString());
            }
        }

        public static void ValidateTitle(string title)
        {
            Utility.CheckStringNullOrEmpty(title, "title", true);
            if (title.Length > 0xff)
            {
                object[] args = new object[] { 0xff.ToString(CultureInfo.CurrentUICulture) };
                throw new ArgumentOutOfRangeException("title", string.Format(CultureInfo.CurrentUICulture, Utility.LoadResourceString(Strings.ExceptionArgumentOutOfRangeMaxColumnLength), args));
            }
        }

        public static void ValidateWidth(int width)
        {
            if (width < -1)
            {
                throw Utility.CreateArgumentOutOfRangeException("width", width, -1);
            }
        }

        public ListViewColumnFormat Format
        {
            get
            {
                return this._format;
            }
            set
            {
                ValidateFormat(value);
                this._format = value;
            }
        }

        public int Id
        {
            get
            {
                return this._id;
            }
        }

        public string Title
        {
            get
            {
                return this._title;
            }
            set
            {
                ValidateTitle(value);
                this._title = value;
            }
        }

        public bool Visible
        {
            get
            {
                return this._visible;
            }
            set
            {
                this._visible = value;
            }
        }

        public int Width
        {
            get
            {
                return this._width;
            }
            set
            {
                ValidateWidth(value);
                this._width = value;
            }
        }
    }
}

