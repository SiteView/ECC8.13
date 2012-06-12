namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.Remoting.Lifetime;
    using System.Security.Permissions;
    using System.Windows.Forms;

    internal class PropertyPageContainerControl : ContainerControl
    {
        private PropertyPage _ownerPage;

        public PropertyPageContainerControl(PropertyPage ownerPage)
        {
            this._ownerPage = ownerPage;
        }

        [SecurityPermission(SecurityAction.LinkDemand, Flags=SecurityPermissionFlag.Infrastructure)]
        public override object InitializeLifetimeService()
        {
            ILease lease = (ILease) base.InitializeLifetimeService();
            if (lease.CurrentState == LeaseState.Initial)
            {
                lease.InitialLeaseTime = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectLeaseTime;
                lease.SponsorshipTimeout = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectSponsorshipTimeout;
                lease.RenewOnCallTime = GlobalConfiguration.SnapInHostingOptions.MarshalByRefObjectRenewOnCallTime;
            }
            return lease;
        }

        protected override bool ProcessDialogChar(char charCode)
        {
            bool flag = false;
            if (charCode != ' ')
            {
                if (!this.ProcessMnemonic(charCode))
                {
                    this._ownerPage.ParentSheet.ProcessDialogKey(this._ownerPage.Id, Keys.None);
                }
                flag = true;
            }
            if (!flag)
            {
                return base.ProcessDialogChar(charCode);
            }
            return true;
        }

        protected override bool ProcessDialogKey(Keys keyData)
        {
            Keys keys = keyData & Keys.KeyCode;
            switch (keys)
            {
                case Keys.Tab:
                case Keys.Return:
                case Keys.Escape:
                    break;

                default:
                    if (((keys != Keys.Prior) && (keys != Keys.Next)) || ((keyData & Keys.Control) == Keys.None))
                    {
                        return false;
                    }
                    break;
            }
            this._ownerPage.ParentSheet.ProcessDialogKey(this._ownerPage.Id, keyData);
            return true;
        }

        public bool ProcessHotKey(char hotKey)
        {
            return this.ProcessMnemonic(hotKey);
        }
    }
}

