namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Runtime.CompilerServices;
    using System.Threading;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ActionsPaneItem
    {
        private ActionsPaneItemData _data;
        private static int _idCounter;
        private object _tag;

        internal event EventHandler Changed;

        internal ActionsPaneItem()
        {
        }

        internal void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, null);
            }
        }

        internal ActionsPaneItemData Data
        {
            get
            {
                return this._data;
            }
            set
            {
                this._data = value;
                if (this._data != null)
                {
                    if (_idCounter == 0x7fffffff)
                    {
                        TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "The max value for Action identifiers has been reached; no new actions can be created.");
                        throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionMMCOutOfResources));
                    }
                    this._data.Id = Interlocked.Increment(ref _idCounter);
                }
            }
        }

        internal int Id
        {
            get
            {
                return this.Data.Id;
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
                this.Notify();
            }
        }
    }
}

