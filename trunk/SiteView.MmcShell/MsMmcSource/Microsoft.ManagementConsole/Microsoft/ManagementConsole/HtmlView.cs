namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public class HtmlView : View
    {
        private Uri _url;

        internal override void InternalInitialize()
        {
            HtmlViewDescription viewDescription = base.ViewDescription as HtmlViewDescription;
            if (viewDescription == null)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ViewDescriptionInvalidViewDescription, new object[] { "HtmlView", "HtmlViewDescription" }));
            }
            this._url = viewDescription.Url;
        }

        public Uri Url
        {
            get
            {
                return this._url;
            }
        }
    }
}

