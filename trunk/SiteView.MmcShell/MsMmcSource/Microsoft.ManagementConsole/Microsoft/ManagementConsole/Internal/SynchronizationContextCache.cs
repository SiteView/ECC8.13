namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.Threading;

    internal static class SynchronizationContextCache
    {
        private static LocalDataStoreSlot _syncContextSlot = Thread.AllocateDataSlot();

        public static void RestoreOriginalContext()
        {
            SynchronizationContext.SetSynchronizationContext(OriginalContext);
        }

        public static SynchronizationContext OriginalContext
        {
            get
            {
                return (SynchronizationContext) Thread.GetData(_syncContextSlot);
            }
            set
            {
                Thread.SetData(_syncContextSlot, value);
            }
        }
    }
}

