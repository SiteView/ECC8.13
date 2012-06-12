namespace Microsoft.ManagementConsole.Interop
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    internal static class ModalLoop
    {
        public static void Exit()
        {
            NativeMethods.PostQuitMessage(0);
        }

        public static void Run()
        {
            Run(false);
        }

        public static void Run(bool filterInput)
        {
            WindowsMessage msg = new WindowsMessage();
            while (NativeMethods.GetMessage(ref msg, IntPtr.Zero, 0, 0) > 0)
            {
                if ((!filterInput || (((msg.Message < 0x100) || (msg.Message > 0x109)) && ((msg.Message < 0x200) || (msg.Message > 0x20d)))) && ((msg.Message < 160) || (msg.Message > 0xad)))
                {
                    NativeMethods.TranslateMessage(ref msg);
                    NativeMethods.DispatchMessage(ref msg);
                }
            }
        }
    }
}

