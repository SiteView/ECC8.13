namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections;
    using System.Configuration.Install;
    using System.Reflection;

    public class SnapInInstaller : Installer
    {
        public override void Install(IDictionary stateSaver)
        {
            SnapInRegistrationInfo[] infoArray = this.ReflectSnapIn();
            if (infoArray.Length != 0)
            {
                foreach (SnapInRegistrationInfo info in infoArray)
                {
                    info.WriteToStore();
                }
            }
            base.Install(stateSaver);
        }

        private SnapInRegistrationInfo[] ReflectSnapIn()
        {
            ArrayList list = new ArrayList();
            foreach (Type type in Assembly.GetAssembly(base.GetType()).GetTypes())
            {
                if ((type.GetCustomAttributes(typeof(SnapInSettingsAttribute), false).Length > 0) && (SnapInRegistration.LoadFromType(type) != null))
                {
                    list.Add(SnapInRegistration.LoadFromType(type));
                }
            }
            return (SnapInRegistrationInfo[]) list.ToArray(typeof(SnapInRegistrationInfo));
        }

        private void RemoveAssemblySnapInsFromRegistry()
        {
            foreach (SnapInRegistrationInfo info in this.ReflectSnapIn())
            {
                info.RemoveFromStore();
            }
        }

        public override void Rollback(IDictionary savedState)
        {
            base.Rollback(savedState);
            this.RemoveAssemblySnapInsFromRegistry();
        }

        public override void Uninstall(IDictionary savedState)
        {
            base.Uninstall(savedState);
            this.RemoveAssemblySnapInsFromRegistry();
        }
    }
}

