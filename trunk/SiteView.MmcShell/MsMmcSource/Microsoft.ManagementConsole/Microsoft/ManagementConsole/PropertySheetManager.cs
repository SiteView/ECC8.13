namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;

    internal sealed class PropertySheetManager
    {
        private AuxiliarySelectionDataCollection _activeViewPropertySheetSelectionDatas;
        private Dictionary<int, PropertySheet> _sheets = new Dictionary<int, PropertySheet>();

        private void AddPropertySheet(PropertySheet sheet)
        {
            if (sheet == null)
            {
                throw new ArgumentNullException("sheet");
            }
            this._sheets.Add(sheet.Id, sheet);
            AuxiliarySelectionData auxiliarySelectionData = sheet.AuxiliarySelectionData;
            if (auxiliarySelectionData != null)
            {
                this.ActiveViewPropertySheetSelectionDatas[auxiliarySelectionData.Id] = auxiliarySelectionData;
            }
        }

        internal bool ComparePropertySheetSelectionObjects(object selectionObject, int selectionId)
        {
            bool flag = false;
            if (selectionObject == null)
            {
                throw new ArgumentNullException("selectionObject");
            }
            AuxiliarySelectionData data = this.ActiveViewPropertySheetSelectionDatas[selectionId];
            if (data != null)
            {
                flag = Microsoft.ManagementConsole.Internal.Utility.CompareSelectionObjects(selectionObject, data.SelectionObject);
            }
            return flag;
        }

        internal PropertySheet CreatePropertySheet(int sheetId, PropertyPageCollection pageCollection, AuxiliarySelectionData auxiliarySelectionData)
        {
            if (pageCollection == null)
            {
                throw new ArgumentNullException("pageCollection");
            }
            PropertySheet sheet = new PropertySheet(this, sheetId, auxiliarySelectionData);
            sheet.AddPropertyPages(pageCollection);
            this.AddPropertySheet(sheet);
            return sheet;
        }

        internal int FindPropertySheet(object selectionObject)
        {
            int num;
            this.ActiveViewPropertySheetSelectionDatas.FindMatchingSelectionId(selectionObject, out num);
            return num;
        }

        internal PropertySheet GetPropertySheet(int id)
        {
            PropertySheet sheet;
            try
            {
                sheet = this._sheets[id];
            }
            catch (KeyNotFoundException)
            {
                throw new ArgumentOutOfRangeException("id", Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertySheetUnknownPage));
            }
            return sheet;
        }

        internal void ProcessNotificationMessage(PropertyPageNotification pageNotif)
        {
            this.GetPropertySheet(pageNotif.SheetId).ProcessNotificationMessage(pageNotif);
        }

        internal void ProcessRequestMessage(PropertyPageMessageRequestInfo requestInfo, IRequestStatus requestStatus)
        {
            PropertySheet propertySheet = this.GetPropertySheet(requestInfo.SheetId);
            SyncStatus status = new SyncStatus(requestStatus);
            try
            {
                requestStatus.ProcessResponse(propertySheet.ProcessRequestMessage(requestInfo));
            }
            finally
            {
                status.Close();
            }
        }

        public void RemovePropertySheet(PropertySheet sheet)
        {
            if (sheet == null)
            {
                throw new ArgumentNullException("sheet");
            }
            this._sheets.Remove(sheet.Id);
            AuxiliarySelectionData auxiliarySelectionData = sheet.AuxiliarySelectionData;
            if (auxiliarySelectionData != null)
            {
                this.ActiveViewPropertySheetSelectionDatas.Remove(auxiliarySelectionData.Id);
            }
        }

        internal AuxiliarySelectionDataCollection ActiveViewPropertySheetSelectionDatas
        {
            get
            {
                if (this._activeViewPropertySheetSelectionDatas == null)
                {
                    this._activeViewPropertySheetSelectionDatas = new AuxiliarySelectionDataCollection();
                }
                return this._activeViewPropertySheetSelectionDatas;
            }
        }
    }
}

