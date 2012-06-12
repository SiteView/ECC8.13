namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class CreatePropertySheetCommand : Command
    {
        private bool _hideApplyButton;
        private PropertyPageInfo[] _propertyPagesData;
        private string _title;

        protected CreatePropertySheetCommand()
        {
        }

        public bool HideApplyButton
        {
            get
            {
                return this._hideApplyButton;
            }
            set
            {
                this._hideApplyButton = value;
            }
        }

        public PropertyPageInfo[] PropertyPagesData
        {
            get
            {
                return this._propertyPagesData;
            }
            set
            {
                this._propertyPagesData = value;
            }
        }

        public string Title
        {
            get
            {
                return this._title;
            }
            set
            {
                this._title = value;
            }
        }
    }
}

