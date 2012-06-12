namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole.Interop;
    using System;
    using System.Collections.Generic;

    internal class SnapInUIThreadTable
    {
        private List<ulong> _registeredThreadIds = new List<ulong>();
        private ISnapInPlatform _snapInPlatform;

        public void Initialize(ISnapInPlatform snapInPlatform)
        {
            lock (this.SyncRoot)
            {
                this._snapInPlatform = snapInPlatform;
                foreach (uint num in this._registeredThreadIds)
                {
                    this.RegisterThreadWithExecutive(num, true);
                }
                this._registeredThreadIds.Clear();
            }
        }

        public void RegisterCurrentThread(bool register)
        {
            uint currentThreadId = (uint) NativeMethods.GetCurrentThreadId();
            lock (this.SyncRoot)
            {
                if (this._snapInPlatform != null)
                {
                    this.RegisterThreadWithExecutive(currentThreadId, register);
                }
                else if (register)
                {
                    if (!this._registeredThreadIds.Contains((ulong) currentThreadId))
                    {
                        this._registeredThreadIds.Add((ulong) currentThreadId);
                    }
                }
                else if (this._registeredThreadIds.Contains((ulong) currentThreadId))
                {
                    this._registeredThreadIds.Remove((ulong) currentThreadId);
                }
            }
        }

        private void RegisterThreadWithExecutive(uint threadId, bool register)
        {
            RegisterUIThreadCommand command = new RegisterUIThreadCommand();
            command.UnmanagedThreadId = threadId;
            command.Register = register;
            this._snapInPlatform.ProcessCommand(command);
        }

        private object SyncRoot
        {
            get
            {
                return this._registeredThreadIds;
            }
        }
    }
}

