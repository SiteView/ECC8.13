namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ViewSetData
    {
        private int _defaultIndex;
        private ViewDescriptionData[] _viewDescriptionDatas;
        private int _viewDescriptionsId;

        public ViewSetData()
        {
            this._defaultIndex = -1;
            this._viewDescriptionDatas = new ViewDescriptionData[0];
        }

        public ViewSetData(ViewDescriptionData[] viewDescriptionData)
        {
            this._defaultIndex = -1;
            this._viewDescriptionDatas = viewDescriptionData;
        }

        public ViewDescriptionData[] GetViewDescriptions()
        {
            return this._viewDescriptionDatas;
        }

        public void SetViewDescriptions(ViewDescriptionData[] viewDescriptionData)
        {
            this._viewDescriptionDatas = viewDescriptionData;
        }

        public int DefaultIndex
        {
            get
            {
                return this._defaultIndex;
            }
            set
            {
                this._defaultIndex = value;
            }
        }

        public int ViewSetId
        {
            get
            {
                return this._viewDescriptionsId;
            }
            set
            {
                this._viewDescriptionsId = value;
            }
        }
    }
}

