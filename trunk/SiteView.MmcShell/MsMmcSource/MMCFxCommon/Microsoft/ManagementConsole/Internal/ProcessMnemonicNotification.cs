namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ProcessMnemonicNotification : PropertyPageNotification
    {
        private char _charCode;

        public char CharCode
        {
            get
            {
                return this._charCode;
            }
            set
            {
                this._charCode = value;
            }
        }
    }
}

