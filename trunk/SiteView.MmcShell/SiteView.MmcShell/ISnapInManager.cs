using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.ManagementConsole.Internal;

namespace SiteView.MmcShell
{
    interface ISnapInManager
    {
        void Init(ISnapInPlatform snapInPlatform);
    }
}
