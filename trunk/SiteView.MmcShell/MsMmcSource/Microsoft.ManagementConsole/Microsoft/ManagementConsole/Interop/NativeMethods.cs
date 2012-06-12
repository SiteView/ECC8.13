namespace Microsoft.ManagementConsole.Interop
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.InteropServices;
    using System.Security;

    [SuppressUnmanagedCodeSecurity]
    internal static class NativeMethods
    {
        [DllImport("user32.dll", EntryPoint="DispatchMessageW", CharSet=CharSet.Unicode)]
        public static extern IntPtr DispatchMessage(ref WindowsMessage msg);
        [DllImport("kernel32.dll", CharSet=CharSet.Auto, ExactSpelling=true)]
        internal static extern int GetCurrentThreadId();
        [DllImport("user32.dll", CharSet=CharSet.Auto, ExactSpelling=true)]
        public static extern IntPtr GetDesktopWindow();
        [DllImport("user32.dll", EntryPoint="GetMessageW", CharSet=CharSet.Unicode)]
        public static extern int GetMessage(ref WindowsMessage msg, IntPtr hWnd, uint wMsgFilterMin, uint wMsgFilterMax);
        [DllImport("user32.dll", ExactSpelling=true)]
        public static extern bool MessageBeep(int type);
        [DllImport("user32.dll")]
        public static extern void PostQuitMessage(int exitCode);
        [DllImport("user32.dll")]
        public static extern IntPtr SendMessage(IntPtr windowHandle, uint msgId, IntPtr wParam, IntPtr lParam);
        [DllImport("user32.dll", CharSet=CharSet.Auto, ExactSpelling=true)]
        public static extern int TranslateMessage(ref WindowsMessage msg);
    }
}

