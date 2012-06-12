namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Threading;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public abstract class ViewDescriptionData
    {
        private string _displayName;
        private int _id;
        private static int _identifierSeed;
        private string _languageIndependentName;
        public static readonly int ExDefaultViewId = -1;
        public static readonly int ExErrorViewId = -2;

        protected ViewDescriptionData()
        {
            this._displayName = string.Empty;
            this._languageIndependentName = string.Empty;
            if (_identifierSeed == 0x7fffffff)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 12, "The max value for View identifiers has been reached; no new views can be created.");
                throw new Exception(Utility.LoadResourceString(Strings.ExceptionMMCOutOfResources));
            }
            this._id = Interlocked.Increment(ref _identifierSeed);
        }

        private ViewDescriptionData(ViewDescriptionData viewDescriptionData)
        {
            this._displayName = string.Empty;
            this._languageIndependentName = string.Empty;
        }

        public virtual void Validate()
        {
            ValidateDisplayName(this._displayName);
            ValidateLanguageIndependentName(this._languageIndependentName);
        }

        public static void ValidateDisplayName(string displayName)
        {
            Utility.CheckStringNullOrEmpty(displayName, "DisplayName", true);
        }

        public static void ValidateLanguageIndependentName(string languageIndependentName)
        {
            if (languageIndependentName == null)
            {
                throw new ArgumentNullException("languageIndependentName");
            }
        }

        public string DisplayName
        {
            get
            {
                return this._displayName;
            }
            set
            {
                ValidateDisplayName(value);
                this._displayName = value;
            }
        }

        public int Id
        {
            get
            {
                return this._id;
            }
            set
            {
                this._id = value;
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                if (Utility.CheckStringNullOrEmpty(this._languageIndependentName, string.Empty, false))
                {
                    return this._displayName;
                }
                return this._languageIndependentName;
            }
            set
            {
                ValidateLanguageIndependentName(value);
                this._languageIndependentName = value;
            }
        }
    }
}

