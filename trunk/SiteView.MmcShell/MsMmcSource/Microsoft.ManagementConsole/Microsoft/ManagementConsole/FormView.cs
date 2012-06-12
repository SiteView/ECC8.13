namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Windows.Forms;

    public class FormView : Microsoft.ManagementConsole.View
    {
        private FormViewContainerControl _containerControl;
        private System.Windows.Forms.Control _control;
        private System.Type _controlType;

        internal override void InternalInitialize()
        {
            FormViewDescription viewDescription = base.ViewDescription as FormViewDescription;
            if (viewDescription == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString("Microsoft.ManagementConsole.ViewDescription.InvalidViewDescription", new object[] { "FormView", "FormViewDescription" }));
            }
            this._controlType = viewDescription.ControlType;
            if (this._controlType != null)
            {
                this._containerControl = new FormViewContainerControl(this);
                if (this._containerControl == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.FormViewControlTypeContainerCreateFailed));
                }
                this._containerControl.Dock = DockStyle.Fill;
                this._containerControl.HandleCreated += new EventHandler(this.OnHandleCreated);
                this._control = Activator.CreateInstance(this._controlType) as System.Windows.Forms.Control;
                IFormViewControl control = this._control as IFormViewControl;
                if (control != null)
                {
                    control.Initialize(this);
                }
                this._containerControl.CreateControl();
                this._containerControl.Controls.Add(this._control);
            }
        }

        internal override void InternalShutdown()
        {
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
            this._controlType = null;
        }

        internal bool LoseKeyboardFocus(bool forward)
        {
            LoseKeyboardFocusCommand command = new LoseKeyboardFocusCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            command.Forward = forward;
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
            }
            LoseKeyboardFocusCommandResult result = snapInPlatform.ProcessCommand(command) as LoseKeyboardFocusCommandResult;
            if (result != null)
            {
                return result.FocusChanged;
            }
            return false;
        }

        internal void MouseActivate(IntPtr topLevelWindow, int hitTestResult)
        {
            MouseActivateCommand command = new MouseActivateCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            command.TopLevelWindow = topLevelWindow;
            command.HitTestResult = hitTestResult;
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
            }
            snapInPlatform.ProcessCommand(command);
        }

        private void OnHandleCreated(object control, EventArgs args)
        {
            this.Synchronize();
        }

        internal bool ProcessCmdKey()
        {
            ProcessViewCmdKeyCommand command = new ProcessViewCmdKeyCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
            }
            ProcessViewCmdKeyCommandResult result = snapInPlatform.ProcessCommand(command) as ProcessViewCmdKeyCommandResult;
            if (result == null)
            {
                return false;
            }
            return result.Handled;
        }

        internal void ProcessDialogKey()
        {
            ProcessViewDialogKeyCommand command = new ProcessViewDialogKeyCommand();
            command.ViewInstanceId = base.ViewInstanceId;
            ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
            if (snapInPlatform == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
            }
            snapInPlatform.ProcessCommand(command);
        }

        internal override void ProcessNotification(Notification notification)
        {
            if (notification is ViewKeyboardFocusNotification)
            {
                ViewKeyboardFocusNotification notification2 = (ViewKeyboardFocusNotification) notification;
                this.TakeKeyboardFocus(notification2.Forward);
            }
            else
            {
                base.ProcessNotification(notification);
            }
        }

        public void ShowContextMenu(Point point, bool onResultItem)
        {
            base.ThrowIfShutdown("ShowContextMenu");
            if (!base.Initialized || !base.Visible)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 12, "Ignoring context menu request since view hasn't been initialized or is hidden.");
            }
            else
            {
                if (onResultItem && (base.SelectionData.SelectionCardinality == SelectionCardinality.None))
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.FormViewShowContextMenuNoSelection));
                }
                ShowContextMenuCommand command = new ShowContextMenuCommand();
                command.ViewInstanceId = base.ViewInstanceId;
                command.Point = point;
                command.OnResultItem = onResultItem;
                ISnapInPlatform snapInPlatform = base.SnapIn.SnapInPlatform;
                if (snapInPlatform == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
                }
                snapInPlatform.ProcessCommand(command);
            }
        }

        private void Synchronize()
        {
            if (this._containerControl != null)
            {
                ISnapInPlatform snapInPlatform = SnapInBase.SnapInInstance.SnapInPlatform;
                if (snapInPlatform == null)
                {
                    throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonSnapInPlatformIsNull));
                }
                SetFormViewControlCommand command = new SetFormViewControlCommand();
                command.ViewInstanceId = base.ViewInstanceId;
                command.Handle = this._containerControl.Handle;
                snapInPlatform.ProcessCommand(command);
            }
        }

        private void TakeKeyboardFocus(bool forward)
        {
            if (this._containerControl != null)
            {
                this._containerControl.TakeKeyboardFocus(forward);
            }
        }

        public System.Windows.Forms.Control Control
        {
            get
            {
                return this._control;
            }
        }

        public System.Type ControlType
        {
            get
            {
                return this._controlType;
            }
        }
    }
}

