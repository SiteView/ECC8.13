namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewStandardVerbsCommand : ViewCommand
    {
        private StandardVerbs _enabledVerbs;

        public StandardVerbs EnabledVerbs
        {
            get
            {
                return this._enabledVerbs;
            }
            set
            {
                this._enabledVerbs = value;
            }
        }
    }
}

