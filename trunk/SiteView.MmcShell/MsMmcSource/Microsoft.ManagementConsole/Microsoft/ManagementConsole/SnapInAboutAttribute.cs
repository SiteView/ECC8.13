namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    [AttributeUsage(AttributeTargets.Class)]
    public sealed class SnapInAboutAttribute : Attribute
    {
        private bool _applicationBaseRelative = true;
        private int _descriptionId = -1;
        private int _displayNameId = -1;
        private int _folderBitmapsColorMask;
        private bool _folderBitmapsColorMaskSet;
        private int _iconId = -1;
        private int _largeFolderBitmapId = -1;
        private string _resourceModule = string.Empty;
        private int _smallFolderBitmapId = -1;
        private int _smallFolderSelectedBitmapId = -1;
        private int _vendorId = -1;
        private int _versionId = -1;

        public SnapInAboutAttribute(string resourceModule)
        {
            this._resourceModule = resourceModule;
        }

        internal bool IsFolderBitmapsColorMaskSet()
        {
            return this._folderBitmapsColorMaskSet;
        }

        public bool ApplicationBaseRelative
        {
            get
            {
                return this._applicationBaseRelative;
            }
            set
            {
                this._applicationBaseRelative = value;
            }
        }

        public int DescriptionId
        {
            get
            {
                return this._descriptionId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._descriptionId = value;
            }
        }

        public int DisplayNameId
        {
            get
            {
                return this._displayNameId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._displayNameId = value;
            }
        }

        public int FolderBitmapsColorMask
        {
            get
            {
                return this._folderBitmapsColorMask;
            }
            set
            {
                if ((value < 0) || (value > 0xffffff))
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0, 0xffffff);
                }
                this._folderBitmapsColorMask = value;
                this._folderBitmapsColorMaskSet = true;
            }
        }

        public int IconId
        {
            get
            {
                return this._iconId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._iconId = value;
            }
        }

        public int LargeFolderBitmapId
        {
            get
            {
                return this._largeFolderBitmapId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._largeFolderBitmapId = value;
            }
        }

        public string ResourceModule
        {
            get
            {
                return this._resourceModule;
            }
        }

        public int SmallFolderBitmapId
        {
            get
            {
                return this._smallFolderBitmapId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._smallFolderBitmapId = value;
            }
        }

        public int SmallFolderSelectedBitmapId
        {
            get
            {
                return this._smallFolderSelectedBitmapId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._smallFolderSelectedBitmapId = value;
            }
        }

        public int VendorId
        {
            get
            {
                return this._vendorId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._vendorId = value;
            }
        }

        public int VersionId
        {
            get
            {
                return this._versionId;
            }
            set
            {
                if (value < 0)
                {
                    throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentOutOfRangeException("value", value, 0);
                }
                this._versionId = value;
            }
        }
    }
}

