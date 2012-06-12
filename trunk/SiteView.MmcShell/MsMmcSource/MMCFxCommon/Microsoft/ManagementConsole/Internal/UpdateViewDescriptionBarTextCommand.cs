namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class UpdateViewDescriptionBarTextCommand : ViewCommand
    {
        private string _descriptionBarText = string.Empty;

        public string DescriptionBarText
        {
            get
            {
                return this._descriptionBarText;
            }
            set
            {
                this._descriptionBarText = value;
            }
        }
    }
}

