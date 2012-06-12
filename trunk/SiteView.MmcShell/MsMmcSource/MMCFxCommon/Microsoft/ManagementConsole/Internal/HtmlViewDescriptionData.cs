namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class HtmlViewDescriptionData : ViewDescriptionData
    {
        private Uri _url;

        public HtmlViewDescriptionData()
        {
        }

        public HtmlViewDescriptionData(Uri url)
        {
            this.Url = url;
        }

        public override void Validate()
        {
            base.Validate();
            ValidateUrl(this._url);
        }

        public static void ValidateUrl(Uri url)
        {
            if (url == null)
            {
                throw new ArgumentNullException("url");
            }
        }

        public Uri Url
        {
            get
            {
                return this._url;
            }
            set
            {
                ValidateUrl(value);
                this._url = value;
            }
        }
    }
}

