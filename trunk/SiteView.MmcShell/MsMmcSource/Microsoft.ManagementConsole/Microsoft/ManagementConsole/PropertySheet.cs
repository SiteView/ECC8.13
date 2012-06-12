namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Advanced;
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Windows.Forms;

    public sealed class PropertySheet
    {
        private Microsoft.ManagementConsole.AuxiliarySelectionData _auxiliarySelectionData;
        private ConsoleDialogHost _dialogHost;
        private int _id = -1;
        private int _initPageCount;
        private bool _inRequestOperation;
        private PropertySheetManager _manager;
        private int _newActivePageId = -1;
        private Dictionary<int, PropertyPage> _pages = new Dictionary<int, PropertyPage>();

        internal PropertySheet(PropertySheetManager manager, int sheetId, Microsoft.ManagementConsole.AuxiliarySelectionData auxiliarySelectionData)
        {
            if (manager == null)
            {
                throw new ArgumentNullException("manager");
            }
            this._manager = manager;
            this._id = sheetId;
            this._auxiliarySelectionData = auxiliarySelectionData;
            this._dialogHost = new ConsoleDialogHost(this._id);
        }

        private void AddPropertyPage(PropertyPage propertyPage)
        {
            if (propertyPage == null)
            {
                throw new ArgumentNullException("propertyPage");
            }
            this._pages.Add(propertyPage.Id, propertyPage);
        }

        internal void AddPropertyPages(PropertyPageCollection pageCollection)
        {
            if (pageCollection == null)
            {
                throw new ArgumentNullException("pageCollection");
            }
            for (int i = 0; i < pageCollection.Count; i++)
            {
                PropertyPage propertyPage = pageCollection[i];
                propertyPage.SetPageIdAndParentSheet(i, this);
                this.AddPropertyPage(propertyPage);
            }
        }

        public void CancelToClose()
        {
            CancelToClosePropertySheetCommand command = new CancelToClosePropertySheetCommand();
            command.SheetId = this.Id;
            command.PageId = 0;
            SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
        }

        public PropertyPage GetPropertyPage(int index)
        {
            PropertyPage page;
            try
            {
                page = this._pages[index];
            }
            catch (KeyNotFoundException)
            {
                throw new ArgumentOutOfRangeException("index", Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetUnknownPage));
            }
            return page;
        }

        private void InitializeConsoleDialogHost()
        {
            if (!this._dialogHost.Initialized)
            {
                SnapInBase snapInInstance = SnapInBase.SnapInInstance;
                if (snapInInstance == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetWrongThread));
                }
                this._dialogHost.Initialize(snapInInstance.SnapInPlatform);
            }
        }

        internal void ModifyDirtyFlagForPage(int pageId, bool isDirty)
        {
            PropertySheetCommand command;
            if (isDirty)
            {
                command = new SetDirtyFlagPropertySheetCommand();
            }
            else
            {
                command = new ClearDirtyFlagPropertySheetCommand();
            }
            command.SheetId = this.Id;
            command.PageId = pageId;
            SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
        }

        internal void ProcessDialogKey(int pageId, Keys keyData)
        {
            ProcessDialogKeyPropertySheetCommand command = new ProcessDialogKeyPropertySheetCommand();
            command.SheetId = this.Id;
            command.PageId = pageId;
            command.KeyData = keyData;
            SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
        }

        internal void ProcessNotificationMessage(PropertyPageNotification pageNotif)
        {
            PropertyPage propertyPage = this.GetPropertyPage(pageNotif.PageId);
            if (pageNotif is InitializePropertyPageNotification)
            {
                this._initPageCount++;
                propertyPage.InternalInitialize();
            }
            else if (pageNotif is DestroyPropertyPageNotification)
            {
                this._initPageCount--;
                propertyPage.InternalDestroy();
                this.RemovePropertyPage(propertyPage);
            }
            else if (pageNotif is SetActivePropertyPageNotification)
            {
                propertyPage.InternalSetActive();
            }
            else if (pageNotif is ResetPropertyPageNotification)
            {
                propertyPage.OnCancel();
            }
            else
            {
                if (!(pageNotif is ProcessMnemonicNotification))
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetUnknownMessage));
                }
                propertyPage.ProcessMnemonic(((ProcessMnemonicNotification) pageNotif).CharCode);
            }
        }

        internal PropertyPageMessageResponse ProcessRequestMessage(PropertyPageMessageRequestInfo requestInfo)
        {
            PropertyPage propertyPage = this.GetPropertyPage(requestInfo.PageId);
            this._inRequestOperation = true;
            PropertyPageMessageResponse response = new PropertyPageMessageResponse();
            response.AllowRequestedOperation = false;
            if (requestInfo is ApplyPropertyPageMessageRequestInfo)
            {
                if (propertyPage.OnApply())
                {
                    propertyPage.ClearDirtyFlag();
                    response.AllowRequestedOperation = true;
                }
            }
            else if (requestInfo is OkPropertyPageMessageRequestInfo)
            {
                if (propertyPage.OnOK())
                {
                    propertyPage.ClearDirtyFlag();
                    response.AllowRequestedOperation = true;
                }
            }
            else if (requestInfo is KillActivePropertyPageMessageRequestInfo)
            {
                response.AllowRequestedOperation = propertyPage.OnKillActive();
            }
            else
            {
                if (!(requestInfo is QueryCancelPropertyPageMessageRequestInfo))
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetUnknownMessage));
                }
                response.AllowRequestedOperation = propertyPage.QueryCancel();
            }
            response.NewActivePageId = this._newActivePageId;
            this._inRequestOperation = false;
            this._newActivePageId = -1;
            return response;
        }

        private void RemovePropertyPage(PropertyPage propertyPage)
        {
            if (propertyPage == null)
            {
                throw new ArgumentNullException("propertyPage");
            }
            this._pages.Remove(propertyPage.Id);
            if (this._initPageCount == 0)
            {
                this._pages.Clear();
                this._manager.RemovePropertySheet(this);
            }
        }

        public void SetActivePage(int index)
        {
            this.GetPropertyPage(index);
            if (this._inRequestOperation)
            {
                this._newActivePageId = index;
            }
            else
            {
                SetActivePagePropertySheetCommand command = new SetActivePagePropertySheetCommand();
                command.SheetId = this.Id;
                command.PageId = 0;
                command.NewActivePageId = index;
                SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
            }
        }

        internal void SetPropertyPageControl(int pageId, Control control, IntPtr handle)
        {
            if (handle == IntPtr.Zero)
            {
                throw new ArgumentNullException("handle");
            }
            SetPropertyPageControlCommand command = new SetPropertyPageControlCommand();
            command.SheetId = this.Id;
            command.PageId = pageId;
            command.Handle = handle;
            command.Control = control;
            SnapInBase.SnapInInstance.SnapInPlatform.ProcessCommand(command);
        }

        public void Show(Form form)
        {
            this.InitializeConsoleDialogHost();
            this._dialogHost.Show(form);
        }

        public DialogResult ShowDialog(MessageBoxParameters parameters)
        {
            this.InitializeConsoleDialogHost();
            return this._dialogHost.ShowDialog(parameters);
        }

        public DialogResult ShowDialog(CommonDialog commonDialog)
        {
            this.InitializeConsoleDialogHost();
            return this._dialogHost.ShowDialog(commonDialog);
        }

        public DialogResult ShowDialog(Form form)
        {
            this.InitializeConsoleDialogHost();
            return this._dialogHost.ShowDialog(form);
        }

        public DialogResult ShowDialog(Form form, WaitCursor waitCursor)
        {
            this.InitializeConsoleDialogHost();
            return this._dialogHost.ShowDialog(form, waitCursor);
        }

        internal Microsoft.ManagementConsole.AuxiliarySelectionData AuxiliarySelectionData
        {
            get
            {
                return this._auxiliarySelectionData;
            }
        }

        internal int Id
        {
            get
            {
                return this._id;
            }
        }

        public int PageCount
        {
            get
            {
                return this._pages.Count;
            }
        }

        public object SelectionObject
        {
            get
            {
                if (this._auxiliarySelectionData == null)
                {
                    return null;
                }
                return this._auxiliarySelectionData.SelectionObject;
            }
        }

        public SnapInBase SnapIn
        {
            get
            {
                return SnapInBase.SnapInInstance;
            }
        }
    }
}

