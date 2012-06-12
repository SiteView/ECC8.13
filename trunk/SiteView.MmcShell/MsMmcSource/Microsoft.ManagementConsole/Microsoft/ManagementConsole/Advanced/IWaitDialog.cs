namespace Microsoft.ManagementConsole.Advanced
{
    using System;
    using System.Runtime.InteropServices;
    using System.Security;

    [ComImport, Guid("92B4FF02-08E4-40e5-A5A6-624F8970C116"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), SuppressUnmanagedCodeSecurity]
    internal interface IWaitDialog
    {
        void RunModal(IntPtr ownerHWnd, uint displayDelayMSecs, uint minimumDisplayMSecs, IWaitDialogCancelCallback cancelCallback);
        void UpdateProgress(int workProcessed, int totalWork, [MarshalAs(UnmanagedType.BStr)] string statusText);
        void UpdateTitle([MarshalAs(UnmanagedType.BStr)] string title);
        void CompleteRequest();
        void SetCancelable([MarshalAs(UnmanagedType.Bool)] bool fCancelable);
    }
}

