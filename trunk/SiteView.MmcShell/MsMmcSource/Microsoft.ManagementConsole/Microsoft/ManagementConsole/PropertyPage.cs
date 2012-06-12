namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using Microsoft.ManagementConsole.Interop;
    using System;
    using System.Windows.Forms;

    public class PropertyPage
    {
        private PropertyPageContainerControl _containerControl;
        private System.Windows.Forms.Control _control;
        private bool _destroyed;
        private bool _dirty;
        private bool _firstSetActiveNotification = true;
        private string _helpTopic;
        private int _id = -1;
        private bool _initialized;
        private PropertySheet _sheet;
        private string _title;

        internal void ClearDirtyFlag()
        {
            this._dirty = false;
        }

        internal void InternalDestroy()
        {
            this._destroyed = true;
            this.OnDestroy();
            if (this._control != null)
            {
                this._control.Dispose();
            }
            if (this._containerControl != null)
            {
                this._containerControl.Dispose();
            }
            this._control = null;
            this._containerControl = null;
        }

        internal void InternalInitialize()
        {
            this._containerControl = new PropertyPageContainerControl(this);
            if (this._containerControl == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertyPageInternalInitializeNullContainer));
            }
            this._containerControl.Dock = DockStyle.Fill;
            this._containerControl.HandleCreated += new EventHandler(this.OnHandleCreated);
            this._containerControl.Controls.Add(this.Control);
            this._containerControl.CreateControl();
            this._initialized = true;
            this.OnInitialize();
        }

        internal void InternalSetActive()
        {
            if (this._firstSetActiveNotification)
            {
                this._containerControl.Focus();
                this._containerControl.SelectNextControl(this._control, true, true, true, true);
                this._firstSetActiveNotification = false;
            }
            this.OnSetActive();
        }

        protected internal virtual bool OnApply()
        {
            return true;
        }

        protected internal virtual void OnCancel()
        {
        }

        protected internal virtual void OnDestroy()
        {
        }

        private void OnHandleCreated(object control, EventArgs args)
        {
            this.Synchronize();
        }

        protected internal virtual void OnInitialize()
        {
        }

        protected internal virtual bool OnKillActive()
        {
            return true;
        }

        protected internal virtual bool OnOK()
        {
            return true;
        }

        protected internal virtual void OnSetActive()
        {
        }

        internal bool ProcessMnemonic(char charCode)
        {
            this._containerControl.Focus();
            bool flag = this._containerControl.ProcessHotKey(charCode);
            if (!flag)
            {
                Microsoft.ManagementConsole.Interop.NativeMethods.MessageBeep(0);
            }
            return flag;
        }

        protected internal virtual bool QueryCancel()
        {
            return true;
        }

        internal void SetPageIdAndParentSheet(int id, PropertySheet sheet)
        {
            if (sheet == null)
            {
                throw new ArgumentNullException("sheet");
            }
            this._sheet = sheet;
            this._id = id;
        }

        private void Synchronize()
        {
            if (this._containerControl != null)
            {
                this._sheet.SetPropertyPageControl(this._id, this._containerControl, this._containerControl.Handle);
            }
        }

        private void ThrowIfPageIsAdded()
        {
            if (this._id != -1)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertyPageInvalidPropertyModify));
            }
        }

        private void ValidateRequest()
        {
            if (!this._initialized)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertyPageNotInitialized));
            }
            if (this._destroyed)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertyPageDestroyed));
            }
        }

        public System.Windows.Forms.Control Control
        {
            get
            {
                return this._control;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this.ThrowIfPageIsAdded();
                this._control = value;
            }
        }

        public bool Destroyed
        {
            get
            {
                return this._destroyed;
            }
        }

        public bool Dirty
        {
            get
            {
                return this._dirty;
            }
            set
            {
                this.ValidateRequest();
                if (value != this._dirty)
                {
                    this._dirty = value;
                    this._sheet.ModifyDirtyFlagForPage(this._id, this._dirty);
                }
            }
        }

        public string HelpTopic
        {
            get
            {
                return this._helpTopic;
            }
            set
            {
                Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(value, "HelpTopic", true);
                this.ThrowIfPageIsAdded();
                this._helpTopic = value;
            }
        }

        internal int Id
        {
            get
            {
                return this._id;
            }
        }

        public bool Initialized
        {
            get
            {
                return this._initialized;
            }
        }

        public PropertySheet ParentSheet
        {
            get
            {
                this.ValidateRequest();
                return this._sheet;
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
                Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(value, "Title", true);
                this.ThrowIfPageIsAdded();
                this._title = value;
            }
        }
    }
}

