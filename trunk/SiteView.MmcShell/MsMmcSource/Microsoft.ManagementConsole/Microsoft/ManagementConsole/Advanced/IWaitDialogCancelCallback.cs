namespace Microsoft.ManagementConsole.Advanced
{
    using System;
    using System.Runtime.InteropServices;
    using System.Security;

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("BFD57CCB-78F2-4ab8-9173-41540F51A39D"), SuppressUnmanagedCodeSecurity]
    internal interface IWaitDialogCancelCallback
    {
        void Cancel(IntPtr waitDialogWindowHandle);
    }
}

