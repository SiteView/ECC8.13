namespace Microsoft.ManagementConsole
{
    using System;
    using System.Collections;

    public interface IResultNodeComparer : IComparer
    {
        void SetColumnIndex(int index);
    }
}

