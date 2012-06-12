namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class MouseActivateCommand : ViewCommand
    {
        private int _hitTestResult;
        private IntPtr _topLevelWindow;

        public int HitTestResult
        {
            get
            {
                return this._hitTestResult;
            }
            set
            {
                this._hitTestResult = value;
            }
        }

        public IntPtr TopLevelWindow
        {
            get
            {
                return this._topLevelWindow;
            }
            set
            {
                this._topLevelWindow = value;
            }
        }
    }
}

