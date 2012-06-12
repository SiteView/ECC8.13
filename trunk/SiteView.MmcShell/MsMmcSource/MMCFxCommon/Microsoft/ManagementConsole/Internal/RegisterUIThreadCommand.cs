namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, CLSCompliant(false), EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class RegisterUIThreadCommand : Command
    {
        private bool _register;
        private uint _unmanagedThreadId;

        public bool Register
        {
            get
            {
                return this._register;
            }
            set
            {
                this._register = value;
            }
        }

        public uint UnmanagedThreadId
        {
            get
            {
                return this._unmanagedThreadId;
            }
            set
            {
                this._unmanagedThreadId = value;
            }
        }
    }
}

