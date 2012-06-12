namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Windows.Forms;

    public sealed class FormViewDescription : ViewDescription
    {
        private System.Type _controlType;

        public FormViewDescription() : base(typeof(FormView), new FormViewDescriptionData())
        {
        }

        public FormViewDescription(System.Type controlType) : this()
        {
            this.ControlType = controlType;
        }

        public System.Type ControlType
        {
            get
            {
                return this._controlType;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (!value.Equals(typeof(Control)) && !value.IsSubclassOf(typeof(Control)))
                {
                    throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.FormViewControlTypeInvalidType));
                }
                this._controlType = value;
            }
        }
    }
}

