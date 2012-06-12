namespace Microsoft.ManagementConsole
{
    using System;
    using System.Diagnostics;

    public sealed class TraceSources
    {
        private static TraceSource _exSource = new TraceSource("Executive");

        private TraceSources()
        {
        }

        [Switch("Executive", typeof(TraceSwitch))]
        public static TraceSource ExecutiveSource
        {
            get
            {
                return _exSource;
            }
        }
    }
}

