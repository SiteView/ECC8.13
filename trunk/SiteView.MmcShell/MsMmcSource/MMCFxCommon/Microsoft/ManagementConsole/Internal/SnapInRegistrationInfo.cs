namespace Microsoft.ManagementConsole.Internal
{
    using Microsoft.ManagementConsole;
    using Microsoft.Win32;
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Globalization;
    using System.Runtime.InteropServices;

    [EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class SnapInRegistrationInfo
    {
        private const string _actionsKeyName = "Actions";
        private readonly DWordProperty[] _dWordProperties = new DWordProperty[] { new DWordProperty("FolderBitmapsColorMask") };
        private List<Guid> _extendsNodeTypes = new List<Guid>();
        private const string _extensionKeyName = "Extension";
        private const string _extensionsKeyName = "Extensions";
        private string _id;
        private const string _mmcNodeTypesKeyPath = @"SOFTWARE\Microsoft\MMC\NodeTypes\";
        private const string _mmcSnapInsKeyPath = @"SOFTWARE\Microsoft\MMC\SnapIns\";
        private const string _namespaceKeyName = "Namespace";
        private List<NodeType> _nodeTypes = new List<NodeType>();
        private const string _nodeTypesKeyName = "NodeTypes";
        private const string _nodeTypeValueName = "NodeType";
        private const string _propertyPagesKeyName = "PropertySheet";
        private Microsoft.ManagementConsole.Internal.SnapInType _snapInType = Microsoft.ManagementConsole.Internal.SnapInType.Unknown;
        private static readonly StringToSnapInType[] _snapInTypeToStringTable = new StringToSnapInType[] { new StringToSnapInType("Namespace", Microsoft.ManagementConsole.Internal.SnapInType.Namespace), new StringToSnapInType("ActionsPane", Microsoft.ManagementConsole.Internal.SnapInType.Namespace), new StringToSnapInType("PropertySheet", Microsoft.ManagementConsole.Internal.SnapInType.PropertySheet) };
        private const string _standAloneKeyName = "Standalone";
        private readonly StringProperty[] _stringProperties = new StringProperty[] { 
            new StringProperty("Type"), new StringProperty("ApplicationBase", false), new StringProperty("ConfigurationFile"), new StringProperty("DynamicBase"), new StringProperty("LicenseFile"), new StringProperty("PrivateBinPath"), new StringProperty("PrivateBinPathProbe"), new StringProperty("ResourceModule"), new StringProperty("RootNodeType"), new StringProperty("NameString"), new StringProperty("Description"), new StringProperty("Provider"), new StringProperty("ModuleName"), new StringProperty("AssemblyName"), new StringProperty("RuntimeVersion"), new StringProperty("FxVersion"), 
            new StringProperty("About"), new StringProperty("NameStringIndirect"), new StringProperty("DescriptionStringIndirect"), new StringProperty("ProviderStringIndirect"), new StringProperty("VersionStringIndirect"), new StringProperty("IconIndirect"), new StringProperty("LargeFolderBitmapIndirect"), new StringProperty("SmallFolderBitmapIndirect"), new StringProperty("SmallSelectedFolderBitmapIndirect"), new StringProperty("HelpTopic"), new StringProperty("LinkedHelpTopics")
         };

        public int GetDWordProperty(DWordValueKey key)
        {
            if ((key < DWordValueKey.FolderBitmapsColorMask) || ((int)key >= this._dWordProperties.Length))
            {
                throw new ArgumentOutOfRangeException("key");
            }
            return this._dWordProperties[(int) key].GetValue();
        }

        internal static Microsoft.ManagementConsole.Internal.SnapInType GetExtensionTypeFromString(string snapInType)
        {
            Microsoft.ManagementConsole.Internal.SnapInType unknown = Microsoft.ManagementConsole.Internal.SnapInType.Unknown;
            foreach (StringToSnapInType type2 in _snapInTypeToStringTable)
            {
                if (string.Compare(type2.Description, snapInType, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    unknown = type2.Type;
                    break;
                }
            }
            if (unknown == Microsoft.ManagementConsole.Internal.SnapInType.Unknown)
            {
                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 10, "Extension is not registered properly.  Extension of type {0} is not recognized", new object[] { snapInType });
            }
            return unknown;
        }

        private static int GetRegistryDWordValue(RegistryKey key, string value)
        {
            return (int) key.GetValue(value, 0);
        }

        internal static Microsoft.ManagementConsole.Internal.SnapInType GetRegistrySnapInType(RegistryKey snapInKey)
        {
            Microsoft.ManagementConsole.Internal.SnapInType unknown = Microsoft.ManagementConsole.Internal.SnapInType.Unknown;
            using (RegistryKey key = snapInKey.OpenSubKey("Standalone"))
            {
                if (key != null)
                {
                    return Microsoft.ManagementConsole.Internal.SnapInType.StandAlone;
                }
                using (RegistryKey key2 = snapInKey.OpenSubKey("Extension"))
                {
                    if (key2 != null)
                    {
                        return GetExtensionTypeFromString(GetRegistryStringValue(key2, null));
                    }
                    TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Error, 10, "Snap-in is neither a stand-alone snap-in or extension");
                    return unknown;
                }
            }
        }

        private static string GetRegistryStringValue(RegistryKey key, string value)
        {
            return (key.GetValue(value) as string);
        }

        public string GetStringProperty(StringValueKey key)
        {
            if ((key < StringValueKey.Type) || ((int)key >= this._stringProperties.Length))
            {
                throw new ArgumentOutOfRangeException("key");
            }
            return this._stringProperties[(int) key].Value;
        }

        public static SnapInRegistrationInfo LoadFromStore(string id)
        {
            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\MMC\SnapIns\" + id))
            {
                if (key == null)
                {
                    return null;
                }
                SnapInRegistrationInfo info = new SnapInRegistrationInfo();
                info._id = id;
                for (int i = 0; i < info._dWordProperties.Length; i++)
                {
                    info._dWordProperties[i].SetValue(GetRegistryDWordValue(key, info._dWordProperties[i].Name));
                }
                for (int j = 0; j < info._stringProperties.Length; j++)
                {
                    info._stringProperties[j].Value = GetRegistryStringValue(key, info._stringProperties[j].Name);
                }
                info._snapInType = GetRegistrySnapInType(key);
                if (info._snapInType == Microsoft.ManagementConsole.Internal.SnapInType.Unknown)
                {
                    return null;
                }
                using (RegistryKey key2 = key.OpenSubKey("NodeTypes"))
                {
                    if (key2 != null)
                    {
                        foreach (string str in key2.GetSubKeyNames())
                        {
                            NodeType item = new NodeType();
                            try
                            {
                                item.Guid = new Guid(str);
                            }
                            catch (FormatException)
                            {
                                TraceSources.ExecutiveSource.TraceEvent(TraceEventType.Warning, 10, "Snap-in guid string is an invalid format");
                                goto Label_015D;
                            }
                            using (RegistryKey key3 = key2.OpenSubKey(str))
                            {
                                item.Description = GetRegistryStringValue(key3, "");
                                info.NodeTypes.Add(item);
                            }
                        Label_015D:;
                        }
                    }
                }
                return info;
            }
        }

        public void RemoveFromStore()
        {
            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\MMC\SnapIns\", true))
            {
                if (key != null)
                {
                    key.DeleteSubKeyTree(this.Id);
                }
            }
            foreach (Guid guid in this.ExtendedNodeTypes)
            {
                using (RegistryKey key2 = Registry.LocalMachine.OpenSubKey(string.Format(CultureInfo.InvariantCulture, @"{0}{1:B}\{2}\{3}", new object[] { @"SOFTWARE\Microsoft\MMC\NodeTypes\", guid, "Extensions", "Namespace" }), true))
                {
                    if (key2 != null)
                    {
                        key2.DeleteValue(this.Id);
                    }
                }
                using (RegistryKey key3 = Registry.LocalMachine.OpenSubKey(string.Format(CultureInfo.InvariantCulture, @"{0}{1:B}\Extensions", new object[] { @"SOFTWARE\Microsoft\MMC\NodeTypes\", guid }), true))
                {
                    if (key3 != null)
                    {
                        this.RemoveSubkeyIfEmpty(key3, "Namespace");
                        this.RemoveSubkeyIfEmpty(key3, "PropertySheet");
                        this.RemoveSubkeyIfEmpty(key3, "Actions");
                    }
                }
                using (RegistryKey key4 = Registry.LocalMachine.OpenSubKey(string.Format(CultureInfo.InvariantCulture, "{0}{1:B}", new object[] { @"SOFTWARE\Microsoft\MMC\NodeTypes\", guid }), true))
                {
                    if (key4 != null)
                    {
                        this.RemoveSubkeyIfEmpty(key4, "Extensions");
                    }
                }
                using (RegistryKey key5 = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\MMC\NodeTypes\", true))
                {
                    if (key5 != null)
                    {
                        this.RemoveSubkeyIfEmpty(key5, guid.ToString("B"));
                    }
                    continue;
                }
            }
        }

        private void RemoveSubkeyIfEmpty(RegistryKey key, string subKeyName)
        {
            using (RegistryKey key2 = key.OpenSubKey(subKeyName))
            {
                if (((key2 != null) && (key2.ValueCount == 0)) && ((key2.SubKeyCount == 0) && (key2.GetValue(null) == null)))
                {
                    key.DeleteSubKeyTree(subKeyName);
                }
            }
        }

        public void SetDWordProperty(DWordValueKey key, int value)
        {
            if ((key < DWordValueKey.FolderBitmapsColorMask) || ((int)key >= this._dWordProperties.Length))
            {
                throw new ArgumentOutOfRangeException("key");
            }
            this._dWordProperties[(int) key].SetValue(value);
        }

        private static void SetRegistryDWordValue(RegistryKey key, string name, int value)
        {
            key.SetValue(name, value, RegistryValueKind.DWord);
        }

        private static void SetRegistryStringValue(RegistryKey key, string name, string value, bool optional)
        {
            if ((value == null) || (value == string.Empty))
            {
                if (!optional)
                {
                    key.SetValue(name, string.Empty);
                }
            }
            else
            {
                key.SetValue(name, value);
            }
        }

        public void SetStringProperty(StringValueKey key, string value)
        {
            if ((key < StringValueKey.Type) || ((int)key >= this._stringProperties.Length))
            {
                throw new ArgumentOutOfRangeException("key");
            }
            this._stringProperties[(int) key].Value = value;
        }

        public void WriteToStore()
        {
            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\MMC\SnapIns\", true))
            {
                using (RegistryKey key2 = key.CreateSubKey(this.Id))
                {
                    RegistryKey key6;
                    foreach (DWordProperty property in this._dWordProperties)
                    {
                        if (property.IsSet())
                        {
                            SetRegistryDWordValue(key2, property.Name, property.GetValue());
                        }
                    }
                    foreach (StringProperty property2 in this._stringProperties)
                    {
                        SetRegistryStringValue(key2, property2.Name, property2.Value, property2.Optional);
                    }
                    if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.StandAlone)
                    {
                        key2.CreateSubKey("Standalone");
                    }
                    else
                    {
                        if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.Namespace)
                        {
                            using (RegistryKey key3 = key2.CreateSubKey("Extension"))
                            {
                                key3.SetValue(string.Empty, "Namespace");
                                goto Label_0175;
                            }
                        }
                        if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.ActionsPane)
                        {
                            using (RegistryKey key4 = key2.CreateSubKey("Extension"))
                            {
                                key4.SetValue(string.Empty, "ActionsPane");
                                goto Label_0175;
                            }
                        }
                        if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.PropertySheet)
                        {
                            using (RegistryKey key5 = key2.CreateSubKey("Extension"))
                            {
                                key5.SetValue(string.Empty, "PropertySheet");
                                goto Label_0175;
                            }
                        }
                        throw new Exception(Utility.LoadResourceString(Strings.SnapInRegistrationInfoUnknownSnapInType));
                    }
                Label_0175:
                    key6 = key2.CreateSubKey("NodeTypes");
                    try
                    {
                        foreach (NodeType type in this.NodeTypes)
                        {
                            using (RegistryKey key7 = key6.CreateSubKey(type.Guid.ToString("B", null)))
                            {
                                key7.SetValue(null, type.Description, RegistryValueKind.String);
                                continue;
                            }
                        }
                    }
                    finally
                    {
                        if (key6 != null)
                        {
                            ((IDisposable) key6).Dispose();
                        }
                    }
                }
            }
            if (this.ExtendedNodeTypes.Count > 0)
            {
                using (RegistryKey key8 = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\MMC\NodeTypes\", true))
                {
                    foreach (Guid guid in this.ExtendedNodeTypes)
                    {
                        if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.Namespace)
                        {
                            using (RegistryKey key9 = key8.CreateSubKey(string.Format(CultureInfo.InvariantCulture, @"{0:B}\Extensions\Namespace", new object[] { guid })))
                            {
                                key9.SetValue(this.Id, this.GetStringProperty(StringValueKey.Description));
                                continue;
                            }
                        }
                        if (this.SnapInType == Microsoft.ManagementConsole.Internal.SnapInType.PropertySheet)
                        {
                            using (RegistryKey key10 = key8.CreateSubKey(string.Format(CultureInfo.InvariantCulture, @"{0:B}\Extensions\PropertySheet", new object[] { guid })))
                            {
                                key10.SetValue(this.Id, this.GetStringProperty(StringValueKey.Description));
                                continue;
                            }
                        }
                    }
                }
            }
        }

        public List<Guid> ExtendedNodeTypes
        {
            get
            {
                return this._extendsNodeTypes;
            }
        }

        public string Id
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

        public List<NodeType> NodeTypes
        {
            get
            {
                return this._nodeTypes;
            }
        }

        public Microsoft.ManagementConsole.Internal.SnapInType SnapInType
        {
            get
            {
                return this._snapInType;
            }
            set
            {
                this._snapInType = value;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct DWordProperty
        {
            internal readonly string Name;
            private bool _isSet;
            private int _value;
            internal int GetValue()
            {
                return this._value;
            }

            internal bool IsSet()
            {
                return this._isSet;
            }

            internal void SetValue(int value)
            {
                this._value = value;
                this._isSet = true;
            }

            internal DWordProperty(string name)
            {
                this.Name = name;
                this._isSet = false;
                this._value = 0;
            }
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public enum DWordValueKey
        {
            FolderBitmapsColorMask
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct StringProperty
        {
            internal readonly string Name;
            internal string Value;
            internal readonly bool Optional;
            internal StringProperty(string name)
            {
                this.Name = name;
                this.Optional = true;
                this.Value = string.Empty;
            }

            internal StringProperty(string name, bool optional)
            {
                this.Name = name;
                this.Optional = optional;
                this.Value = string.Empty;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct StringToSnapInType
        {
            internal readonly string Description;
            internal readonly SnapInType Type;
            internal StringToSnapInType(string description, SnapInType type)
            {
                this.Description = description;
                this.Type = type;
            }
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public enum StringValueKey
        {
            Type,
            ApplicationBase,
            ConfigurationFile,
            DynamicBase,
            LicenseFile,
            PrivateBinPath,
            PrivateBinPathProbe,
            ResourceModule,
            RootNodeType,
            NameString,
            Description,
            Vendor,
            ModuleName,
            AssemblyName,
            RuntimeVersion,
            FxVersion,
            About,
            NameStringIndirect,
            DescriptionStringIndirect,
            VendorStringIndirect,
            VersionStringIndirect,
            IconIndirect,
            LargeFolderBitmapIndirect,
            SmallFolderBitmapIndirect,
            SmallSelectedFolderBitmapIndirect,
            HelpTopic,
            LinkedHelpTopics
        }
    }
}

