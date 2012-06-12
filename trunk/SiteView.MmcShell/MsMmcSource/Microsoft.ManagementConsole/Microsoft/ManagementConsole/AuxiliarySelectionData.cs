namespace Microsoft.ManagementConsole
{
    using System;

    internal class AuxiliarySelectionData
    {
        private int _id;
        private object _selectionObject;
        private WritableSharedData _sharedData;

        public AuxiliarySelectionData(SelectionData selectionData)
        {
            if (selectionData == null)
            {
                throw new ArgumentNullException("selectionData");
            }
            this._sharedData = selectionData.SharedData;
            this._selectionObject = selectionData.SelectionObject;
            this._id = selectionData.Id;
        }

        public int Id
        {
            get
            {
                return this._id;
            }
        }

        public object SelectionObject
        {
            get
            {
                return this._selectionObject;
            }
        }

        public WritableSharedData SharedData
        {
            get
            {
                return this._sharedData;
            }
        }
    }
}

