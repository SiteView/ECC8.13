namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Collections.Generic;
    using System.Reflection;
    using System.Runtime.InteropServices;

    internal class AuxiliarySelectionDataCollection
    {
        private Dictionary<object, AuxiliarySelectionData> _selections = new Dictionary<object, AuxiliarySelectionData>();

        public bool FindMatchingSelectionId(object selectionObject, out int selectionId)
        {
            selectionId = -1;
            if (selectionObject == null)
            {
                throw new ArgumentNullException("selectionObject");
            }
            foreach (AuxiliarySelectionData data in this._selections.Values)
            {
                object selectionObjectB = data.SelectionObject;
                if ((selectionObjectB != null) && Microsoft.ManagementConsole.Internal.Utility.CompareSelectionObjects(selectionObject, selectionObjectB))
                {
                    selectionId = data.Id;
                    return true;
                }
            }
            return false;
        }

        public void Remove(object key)
        {
            AuxiliarySelectionData data;
            if (this._selections.TryGetValue(key, out data))
            {
                this._selections.Remove(key);
            }
        }

        public AuxiliarySelectionData this[object key]
        {
            get
            {
                AuxiliarySelectionData data;
                if (!this._selections.TryGetValue(key, out data))
                {
                    data = null;
                }
                return data;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                this._selections[key] = value;
            }
        }
    }
}

