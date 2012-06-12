namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ShowInitializationWizardResponse : RequestResponse
    {
        private bool _addSnapInToConsole;

        public bool AddSnapInToConsole
        {
            get
            {
                return this._addSnapInToConsole;
            }
            set
            {
                this._addSnapInToConsole = value;
            }
        }
    }
}

