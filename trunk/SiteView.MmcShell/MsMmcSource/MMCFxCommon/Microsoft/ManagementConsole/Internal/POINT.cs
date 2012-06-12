namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.Runtime.InteropServices;

    [Serializable, StructLayout(LayoutKind.Sequential)]
    internal struct POINT
    {
        public long x;
        public long y;
    }
}

