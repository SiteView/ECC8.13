namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;

    public sealed class MmcListViewDescription : ViewDescription
    {
        public MmcListViewDescription() : base(typeof(MmcListView), new ListViewDescriptionData())
        {
        }

        public MmcListViewDescription(MmcListViewOptions options) : base(typeof(MmcListView), new ListViewDescriptionData((ListViewOptions) options))
        {
        }

        public MmcListViewOptions Options
        {
            get
            {
                return (MmcListViewOptions) ((ListViewDescriptionData) base.ViewDescriptionData).Options;
            }
            set
            {
                ((ListViewDescriptionData) base.ViewDescriptionData).Options = (ListViewOptions) value;
                base.Notify();
            }
        }
    }
}

