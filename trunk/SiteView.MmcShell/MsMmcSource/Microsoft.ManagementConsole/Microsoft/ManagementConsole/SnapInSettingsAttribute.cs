namespace Microsoft.ManagementConsole
{
    using System;

    [AttributeUsage(AttributeTargets.Class)]
    public sealed class SnapInSettingsAttribute : Attribute
    {
        private string _about = System.Guid.Empty.ToString("B");
        private string _configurationFile = string.Empty;
        private string _description = string.Empty;
        private string _displayName = string.Empty;
        private string _dynamicBase = string.Empty;
        private System.Guid _guid;
        private string _licenseFile = string.Empty;
        private string _privateBinPath = string.Empty;
        private string _privateBinPathProbe = string.Empty;
        private string _vendor = string.Empty;

        public SnapInSettingsAttribute(string guid)
        {
            this._guid = new System.Guid(guid);
        }

        internal string About
        {
            get
            {
                return this._about;
            }
            set
            {
                this._about = value;
            }
        }

        public string ConfigurationFile
        {
            get
            {
                return this._configurationFile;
            }
            set
            {
                this._configurationFile = value;
            }
        }

        public string Description
        {
            get
            {
                return this._description;
            }
            set
            {
                this._description = value;
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
                this._displayName = value;
            }
        }

        public string DynamicBase
        {
            get
            {
                return this._dynamicBase;
            }
            set
            {
                this._dynamicBase = value;
            }
        }

        public System.Guid Guid
        {
            get
            {
                return this._guid;
            }
        }

        public string LicenseFile
        {
            get
            {
                return this._licenseFile;
            }
            set
            {
                this._licenseFile = value;
            }
        }

        public string PrivateBinPath
        {
            get
            {
                return this._privateBinPath;
            }
            set
            {
                this._privateBinPath = value;
            }
        }

        public string PrivateBinPathProbe
        {
            get
            {
                return this._privateBinPathProbe;
            }
            set
            {
                this._privateBinPathProbe = value;
            }
        }

        public string Vendor
        {
            get
            {
                return this._vendor;
            }
            set
            {
                this._vendor = value;
            }
        }
    }
}

