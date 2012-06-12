namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PropertyPagesResponse : RequestResponse
    {
        private PropertyPageInfo[] _propertyPagesData;

        public PropertyPageInfo[] GetPropertyPages()
        {
            return this._propertyPagesData;
        }

        public void SetPropertyPages(PropertyPageInfo[] propertyPagesData)
        {
            this._propertyPagesData = propertyPagesData;
        }
    }
}

