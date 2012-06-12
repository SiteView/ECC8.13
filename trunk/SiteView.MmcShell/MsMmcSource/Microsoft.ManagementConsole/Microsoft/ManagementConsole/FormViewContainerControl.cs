namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Interop;
    using System;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    internal class FormViewContainerControl : ContainerControl
    {
        private FormView _view;

        public FormViewContainerControl(FormView view)
        {
            if (view == null)
            {
                throw new ArgumentNullException("view");
            }
            this._view = view;
        }

        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == 0x21)
            {
                IntPtr wParam = m.WParam;
                int hitTestResult = m.LParam.ToInt32() & 0xffff;
                this._view.MouseActivate(wParam, hitTestResult);
                m.Result = (IntPtr) 1L;
            }
            else
            {
                base.DefWndProc(ref m);
            }
        }

        protected override bool ProcessDialogChar(char charCode)
        {
            bool flag = false;
            if (charCode != ' ')
            {
                if (!this.ProcessMnemonic(charCode))
                {
                    this._view.ProcessDialogKey();
                }
                flag = true;
            }
            if (!flag)
            {
                return base.ProcessDialogChar(charCode);
            }
            return true;
        }

        protected override bool ProcessDialogKey(Keys keyData)
        {
            bool flag = false;
            Keys keys = keyData & Keys.KeyCode;
            if (keys == Keys.Tab)
            {
                if ((keyData & (Keys.Alt | Keys.Control)) != Keys.None)
                {
                    return base.ProcessDialogKey(keyData);
                }
                bool forward = (keyData & Keys.Shift) == Keys.None;
                if (!this._view.LoseKeyboardFocus(forward))
                {
                    this.TakeKeyboardFocus(forward);
                }
                flag = true;
            }
            if (!flag)
            {
                flag = this._view.ProcessCmdKey();
            }
            if (!flag)
            {
                return base.ProcessDialogKey(keyData);
            }
            return true;
        }

        public void TakeKeyboardFocus(bool forward)
        {
            HandleRef ref2 = new HandleRef(this, base.Handle);
            int num = (int) Microsoft.ManagementConsole.Interop.NativeMethods.SendMessage(ref2.Handle, 0x129, IntPtr.Zero, IntPtr.Zero);
            if ((num & 1) != 0)
            {
                HandleRef ref3 = new HandleRef(this, base.Handle);
                Microsoft.ManagementConsole.Interop.NativeMethods.SendMessage(ref3.Handle, 0x127, (IntPtr) 0x10002, IntPtr.Zero);
            }
            if (base.Controls.Count != 0)
            {
                base.SelectNextControl(null, forward, true, true, true);
            }
        }
    }
}

