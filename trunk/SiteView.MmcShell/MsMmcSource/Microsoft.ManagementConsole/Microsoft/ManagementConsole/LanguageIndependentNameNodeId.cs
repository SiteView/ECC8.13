namespace Microsoft.ManagementConsole
{
    using System;

    public class LanguageIndependentNameNodeId : NodeId
    {
        private string _languageIndependentName;

        public LanguageIndependentNameNodeId()
        {
        }

        public LanguageIndependentNameNodeId(string languageIndependentName)
        {
            this.LanguageIndependentName = languageIndependentName;
        }

        public string LanguageIndependentName
        {
            get
            {
                return this._languageIndependentName;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._languageIndependentName = value;
            }
        }
    }
}

