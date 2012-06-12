namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ListViewDescriptionData : ViewDescriptionData
    {
        private ListViewOptions _options;

        public ListViewDescriptionData()
        {
        }

        public ListViewDescriptionData(ListViewOptions options)
        {
            this.Options = options;
        }

        public override void Validate()
        {
            base.Validate();
            this.ValidateOptions(this._options);
        }

        private void ValidateOptions(ListViewOptions options)
        {
            if (options > ListViewOptions.All)
            {
                throw new ArgumentOutOfRangeException("options");
            }
        }

        public ListViewOptions Options
        {
            get
            {
                return this._options;
            }
            set
            {
                this.ValidateOptions(value);
                this._options = value;
            }
        }
    }
}

