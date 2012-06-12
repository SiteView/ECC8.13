namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class HtmlViewDescription : ViewDescription
    {
        public HtmlViewDescription() : base(typeof(HtmlView), new HtmlViewDescriptionData())
        {
        }

        public HtmlViewDescription(Uri url) : base(typeof(HtmlView), new HtmlViewDescriptionData(url))
        {
        }

        public Uri Url
        {
            get
            {
                return ((HtmlViewDescriptionData) base.ViewDescriptionData).Url;
            }
            set
            {
                ((HtmlViewDescriptionData) base.ViewDescriptionData).Url = value;
                base.Notify();
            }
        }
    }
}

