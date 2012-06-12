namespace Microsoft.ManagementConsole.Advanced
{
    using Microsoft.ManagementConsole;
    using Microsoft.ManagementConsole.Internal;
    using System;

    public class PropertySheetExtension : SnapInBase
    {
        private PropertySheet _extensionPropertySheet;
        private Guid[] _nodeTypes;
        private Microsoft.ManagementConsole.SharedData _sharedData = new Microsoft.ManagementConsole.SharedData();

        protected PropertySheetExtension()
        {
            this._sharedData.Changed += new Microsoft.ManagementConsole.SharedData.SharedDataChangedEventHandler(this.SharedDataChanged);
        }

        public Guid[] GetNodeTypes()
        {
            return this._nodeTypes;
        }

        internal override void Initialize()
        {
            base.Initialize();
            this._sharedData.SetSnapInPlatform(base.SnapInClient.SnapInPlatform);
        }

        protected virtual void OnAddPropertyPages(PropertyPageCollection propertyPageCollection)
        {
        }

        protected virtual void OnSharedDataChanged(SharedDataItem item)
        {
        }

        internal override void ProcessNotification(Notification notification)
        {
            if (notification is PropertySheetExtensionInitNotification)
            {
                this._nodeTypes = (notification as PropertySheetExtensionInitNotification).GetPrimaryNodeTypes();
                base.AddSharedData(this._sharedData);
            }
            else
            {
                base.ProcessNotification(notification);
            }
        }

        internal override void ProcessRequest(Request request)
        {
            if (request.RequestInfo is ExtensionPagesRequestInfo)
            {
                ExtensionPagesRequestInfo requestInfo = request.RequestInfo as ExtensionPagesRequestInfo;
                PropertyPageCollection propertyPageCollection = new PropertyPageCollection();
                IRequestStatus requestStatus = request.RequestStatus;
                SyncStatus status2 = new SyncStatus(requestStatus);
                try
                {
                    this.OnAddPropertyPages(propertyPageCollection);
                    PropertyPagesResponse response = new PropertyPagesResponse();
                    response.SetPropertyPages(propertyPageCollection.ToPropertyPageInfoArray());
                    requestStatus.ProcessResponse(response);
                }
                finally
                {
                    status2.Close();
                }
                this._extensionPropertySheet = SnapInBase.SnapInInstance.SheetManager.CreatePropertySheet(requestInfo.SheetId, propertyPageCollection, null);
            }
            else
            {
                base.ProcessRequest(request);
            }
        }

        private void SharedDataChanged(object sender, SharedDataChangedEventArgs e)
        {
            this.OnSharedDataChanged(e.SharedDataItem);
        }

        public PropertySheet ExtensionPropertySheet
        {
            get
            {
                return this._extensionPropertySheet;
            }
        }

        public Microsoft.ManagementConsole.SharedData SharedData
        {
            get
            {
                return this._sharedData;
            }
        }
    }
}

