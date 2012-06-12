namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.Globalization;
    using System.Resources;
    using System.Reflection;

    internal static class Utility
    {
        private static ResourceManager _resources = new ResourceManager("Strings", Assembly.GetExecutingAssembly());

        internal static bool CheckStringNullOrEmpty(string stringToCheck, string name, bool throwException)
        {
            bool flag = ((stringToCheck == null) || (stringToCheck.Length == 0)) || (stringToCheck[0] == '\0');
            if (!flag || !throwException)
            {
                return flag;
            }
            if (stringToCheck == null)
            {
                throw new ArgumentNullException(name);
            }
            throw new ArgumentException(string.Format(CultureInfo.CurrentUICulture, LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullOrEmptyString), new object[] { name }));
        }

        public static bool CompareSelectionObjects(object selectionObjectA, object selectionObjectB)
        {
            bool flag = false;
            if (selectionObjectA is IComparable)
            {
                if (((IComparable) selectionObjectA).CompareTo(selectionObjectB) == 0)
                {
                    flag = true;
                }
                return flag;
            }
            if (selectionObjectB is IComparable)
            {
                if (((IComparable) selectionObjectB).CompareTo(selectionObjectA) == 0)
                {
                    flag = true;
                }
                return flag;
            }
            if (selectionObjectA == selectionObjectB)
            {
                flag = true;
            }
            return flag;
        }

        internal static ArgumentException CreateArgumentException(string name, string resourceName, params object[] parms)
        {
            if ((parms == null) || (parms.Length == 0))
            {
                parms = new object[] { name };
            }
            return new ArgumentException(FormatResourceString(resourceName, parms), name);
        }

        internal static ArgumentOutOfRangeException CreateArgumentOutOfRangeException(string name, object actualValue, object minValue)
        {
            return new ArgumentOutOfRangeException(name, actualValue, FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionArgumentOutOfRangeMin, new object[] { name, minValue }));
        }

        internal static ArgumentOutOfRangeException CreateArgumentOutOfRangeException(string name, object actualValue, object minValue, object maxValue)
        {
            return new ArgumentOutOfRangeException(name, actualValue, FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionArgumentOutOfRangeMinMax, new object[] { name, minValue, maxValue }));
        }

        internal static InvalidOperationException CreateClassNotInitializedException(string className, string operation)
        {
            return new InvalidOperationException(FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionClassNotInitialized, new object[] { className, operation }));
        }

        internal static InvalidOperationException CreateClassShutdownException(string className, string operation)
        {
            return new InvalidOperationException(FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionClassShutdown, new object[] { className, operation }));
        }

        internal static string FormatResourceString(string resourceName, params object[] parms)
        {
            string format = LoadResourceString(resourceName);
            if ((parms != null) && (parms.Length > 0))
            {
                format = string.Format(CultureInfo.CurrentUICulture, format, parms);
            }
            return format;
        }

        internal static string LoadResourceString(string resourceName)
        {
            string str = Resources.GetString(resourceName);
            if (str == null)
            {
                str = Resources.GetString(Microsoft.ManagementConsole.Internal.Strings.InvalidResourceName);
            }
            return str;
        }

        public static ResourceManager Resources
        {
            get
            {
                return _resources;
            }
        }
    }
}

