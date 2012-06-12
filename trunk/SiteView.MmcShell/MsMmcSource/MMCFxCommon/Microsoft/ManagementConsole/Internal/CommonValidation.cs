namespace Microsoft.ManagementConsole.Internal
{
    using System;

    internal static class CommonValidation
    {
        public static void ValidateClipboardFormatId(string clipboardFormatId)
        {
            if ((clipboardFormatId == null) || (clipboardFormatId.Length == 0))
            {
                throw new ArgumentException(Utility.LoadResourceString(Strings.ExceptionSnapinDataNullClipboardId), "clipboardFormatId");
            }
        }
    }
}

