namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Advanced;
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Globalization;
    using System.IO;

    internal static class SnapInRegistration
    {
        private const string _locFormatString = "@{0},-{1}";

        private static string BuildPath(string path, Type originType, bool isApplicationBaseRelative)
        {
            if (isApplicationBaseRelative)
            {
                return Path.Combine(Path.GetDirectoryName(originType.Assembly.Location), path);
            }
            return path;
        }

        public static SnapInRegistrationInfo LoadFromType(Type type)
        {
            if (!type.IsSubclassOf(typeof(SnapInBase)))
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SnapInRegistrationLoadFromTypeWrongType));
            }
            SnapInRegistrationInfo info = new SnapInRegistrationInfo();
            if (type.IsSubclassOf(typeof(SnapIn)))
            {
                info.SnapInType = SnapInType.StandAlone;
            }
            else if (type.IsSubclassOf(typeof(NamespaceExtension)))
            {
                info.SnapInType = SnapInType.Namespace;
            }
            else if (type.IsSubclassOf(typeof(PropertySheetExtension)))
            {
                info.SnapInType = SnapInType.PropertySheet;
            }
            else
            {
                return null;
            }
            SnapInSettingsAttribute[] customAttributes = (SnapInSettingsAttribute[]) type.GetCustomAttributes(typeof(SnapInSettingsAttribute), false);
            SnapInAboutAttribute[] attributeArray2 = (SnapInAboutAttribute[]) type.GetCustomAttributes(typeof(SnapInAboutAttribute), false);
            SnapInHelpTopicAttribute[] attributeArray3 = (SnapInHelpTopicAttribute[]) type.GetCustomAttributes(typeof(SnapInHelpTopicAttribute), false);
            SnapInLinkedHelpTopicAttribute[] attributeArray4 = (SnapInLinkedHelpTopicAttribute[]) type.GetCustomAttributes(typeof(SnapInLinkedHelpTopicAttribute), false);
            if (customAttributes.Length == 0)
            {
                return null;
            }
            SnapInSettingsAttribute attribute = customAttributes[0];
            info.Id = string.Format(CultureInfo.InvariantCulture, "FX:{0}", new object[] { attribute.Guid.ToString("B") });
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.ApplicationBase, Path.GetDirectoryName(type.Assembly.Location));
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.Type, type.AssemblyQualifiedName);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.ModuleName, type.Module.Name);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.AssemblyName, type.Assembly.GetName().Name);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.RuntimeVersion, type.Assembly.ImageRuntimeVersion);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.FxVersion, typeof(SnapInSettingsAttribute).Assembly.GetName().Version.ToString());
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.NameString, attribute.DisplayName);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.Description, attribute.Description);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.Vendor, attribute.Vendor);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.ConfigurationFile, attribute.ConfigurationFile);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.DynamicBase, attribute.DynamicBase);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.LicenseFile, attribute.LicenseFile);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.PrivateBinPath, attribute.PrivateBinPath);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.PrivateBinPathProbe, attribute.PrivateBinPathProbe);
            info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.About, attribute.About);
            if (attributeArray3.Length == 1)
            {
                info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.HelpTopic, BuildPath(attributeArray3[0].Topic, type, attributeArray3[0].ApplicationBaseRelative));
            }
            if (attributeArray4.Length > 0)
            {
                string[] strArray = new string[attributeArray4.Length];
                for (int i = 0; i < attributeArray4.Length; i++)
                {
                    strArray[i] = BuildPath(attributeArray4[i].Topic, type, attributeArray4[i].ApplicationBaseRelative);
                }
                info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.LinkedHelpTopics, string.Join(";", strArray));
            }
            if (attributeArray2.Length == 1)
            {
                SnapInAboutAttribute attribute2 = attributeArray2[0];
                string str = BuildPath(attribute2.ResourceModule, type, attribute2.ApplicationBaseRelative);
                if (attribute2.DisplayNameId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.NameStringIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.DisplayNameId }));
                }
                if (attribute2.DescriptionId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.DescriptionStringIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.DescriptionId }));
                }
                if (attribute2.VendorId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.VendorStringIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.VendorId }));
                }
                if (attribute2.VersionId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.VersionStringIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.VersionId }));
                }
                if (attribute2.IconId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.IconIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.IconId }));
                }
                if (attribute2.LargeFolderBitmapId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.LargeFolderBitmapIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.LargeFolderBitmapId }));
                }
                if (attribute2.SmallFolderBitmapId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.SmallFolderBitmapIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.SmallFolderBitmapId }));
                }
                if (attribute2.SmallFolderSelectedBitmapId >= 0)
                {
                    info.SetStringProperty(SnapInRegistrationInfo.StringValueKey.SmallSelectedFolderBitmapIndirect, string.Format(CultureInfo.InvariantCulture, "@{0},-{1}", new object[] { str, attribute2.SmallFolderSelectedBitmapId }));
                }
                if (attribute2.IsFolderBitmapsColorMaskSet())
                {
                    info.SetDWordProperty(SnapInRegistrationInfo.DWordValueKey.FolderBitmapsColorMask, attribute2.FolderBitmapsColorMask);
                }
            }
            LoadNodeTypes(info, type);
            return info;
        }

        private static void LoadNodeTypes(SnapInRegistrationInfo info, Type type)
        {
            ExtendsNodeTypeAttribute[] customAttributes = (ExtendsNodeTypeAttribute[]) type.GetCustomAttributes(typeof(ExtendsNodeTypeAttribute), true);
            PublishesNodeTypeAttribute[] attributeArray2 = (PublishesNodeTypeAttribute[]) type.GetCustomAttributes(typeof(PublishesNodeTypeAttribute), true);
            if (((customAttributes.Length > 0) && !type.IsSubclassOf(typeof(NamespaceExtension))) && !type.IsSubclassOf(typeof(PropertySheetExtension)))
            {
                throw new Exception(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.SnapInRegistrationLoadNodeTypesWrongType));
            }
            foreach (PublishesNodeTypeAttribute attribute in attributeArray2)
            {
                NodeType item = new NodeType();
                item.Description = attribute.Description;
                item.Guid = attribute.Guid;
                info.NodeTypes.Add(item);
            }
            foreach (ExtendsNodeTypeAttribute attribute2 in customAttributes)
            {
                info.ExtendedNodeTypes.Add(attribute2.NodeType);
            }
        }
    }
}

