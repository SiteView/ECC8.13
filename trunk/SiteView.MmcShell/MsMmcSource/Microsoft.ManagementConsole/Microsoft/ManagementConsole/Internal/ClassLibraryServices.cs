namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.Reflection;
    using System.Security.Permissions;

    internal class ClassLibraryServices : MarshalByRefObject, IClassLibraryServices
    {
        internal ClassLibraryServices()
        {
            AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(ClassLibraryServices.OnAssemblyResolve);
        }

        [SecurityPermission(SecurityAction.LinkDemand, Flags=SecurityPermissionFlag.Infrastructure)]
        public override object InitializeLifetimeService()
        {
            return null;
        }

        ISnapInMessagePumpProxy IClassLibraryServices.CreateMessagePumpProxy()
        {
            return new SnapInMessagePumpProxy();
        }

        ISnapInClient IClassLibraryServices.CreateSnapIn(string assemblyName, string typeName)
        {
            SnapInClient client = new SnapInClient();
            client.CreateSnapIn(assemblyName, typeName);
            return client;
        }

        private static Assembly OnAssemblyResolve(object sender, ResolveEventArgs e)
        {
            Assembly assembly = null;
            Assembly executingAssembly = Assembly.GetExecutingAssembly();
            if (e.Name == executingAssembly.FullName)
            {
                return executingAssembly;
            }
            Assembly assembly3 = typeof(IClassLibraryServices).Assembly;
            if (e.Name == assembly3.FullName)
            {
                assembly = assembly3;
            }
            return assembly;
        }
    }
}

