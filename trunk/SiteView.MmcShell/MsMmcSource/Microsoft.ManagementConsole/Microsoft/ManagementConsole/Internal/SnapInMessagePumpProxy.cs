namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.Reflection;
    using System.Threading;
    using System.Windows.Forms;

    internal class SnapInMessagePumpProxy : MarshalByRefObject, ISnapInMessagePumpProxy, IMessageFilter
    {
        private WindowsMessage _lastKeyboardMessage;

        public override object InitializeLifetimeService()
        {
            return null;
        }

        void ISnapInMessagePumpProxy.ExitThread()
        {
            Application.RemoveMessageFilter(this);
            Application.ExitThread();
        }

        void ISnapInMessagePumpProxy.Run()
        {
            Application.ThreadException += new ThreadExceptionEventHandler(this.OnThreadException);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            WindowsFormsSynchronizationContext.AutoInstall = false;
            SynchronizationContext syncContext = new WindowsFormsSynchronizationContext();
            SynchronizationContextCache.OriginalContext = syncContext;
            SynchronizationContext.SetSynchronizationContext(syncContext);
            Application.AddMessageFilter(this);
            Application.Run();
        }

        private void OnThreadException(object sender, ThreadExceptionEventArgs e)
        {
            throw new TargetInvocationException(e.Exception);
        }

        bool IMessageFilter.PreFilterMessage(ref Message m)
        {
            if ((m.Msg >= 0x100) && (m.Msg <= 0x109))
            {
                this._lastKeyboardMessage = new WindowsMessage(m);
            }
            return false;
        }

        WindowsMessage ISnapInMessagePumpProxy.LastKeyboardMessage
        {
            get
            {
                return this._lastKeyboardMessage;
            }
        }
    }
}

