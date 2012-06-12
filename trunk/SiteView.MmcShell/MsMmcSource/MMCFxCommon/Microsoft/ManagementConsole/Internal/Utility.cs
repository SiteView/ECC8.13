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
            throw new ArgumentException(string.Format(CultureInfo.CurrentUICulture, LoadResourceString(Strings.ArgumentExceptionNullOrEmptyString), new object[] { name }));
        }

        internal static ArgumentOutOfRangeException CreateArgumentOutOfRangeException(string name, object actualValue, object minValue)
        {
            return new ArgumentOutOfRangeException(name, actualValue, FormatResourceString(Strings.ExceptionArgumentOutOfRangeMin, new object[] { name, minValue }));
        }

        internal static ArgumentOutOfRangeException CreateArgumentOutOfRangeException(string name, object actualValue, object minValue, object maxValue)
        {
            return new ArgumentOutOfRangeException(name, actualValue, FormatResourceString(Strings.ExceptionArgumentOutOfRangeMinMax, new object[] { name, minValue, maxValue }));
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
                str = Resources.GetString(Strings.InvalidResourceName);
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

