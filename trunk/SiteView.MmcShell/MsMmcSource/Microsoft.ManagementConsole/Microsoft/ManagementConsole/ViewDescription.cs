namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Runtime.CompilerServices;

    public abstract class ViewDescription
    {
        private Type _baseViewType;
        private object _tag;
        private Microsoft.ManagementConsole.Internal.ViewDescriptionData _viewDescriptionData;
        private Type _viewType;

        internal event EventHandler Changed;

        private ViewDescription()
        {
        }

        internal ViewDescription(Type baseViewType, Microsoft.ManagementConsole.Internal.ViewDescriptionData viewDescriptionData)
        {
            if (baseViewType == null)
            {
                throw new ArgumentNullException("baseViewType");
            }
            if (!baseViewType.IsSubclassOf(typeof(View)))
            {
                throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.ViewDescriptionInvalidType), "baseViewType");
            }
            this._baseViewType = this._viewType = baseViewType;
            if (viewDescriptionData == null)
            {
                throw new ArgumentNullException("viewDescriptionData");
            }
            this._viewDescriptionData = viewDescriptionData;
        }

        internal IMessageClient CreateView(ScopeNode scopeNode, int componentId, int viewInstanceId)
        {
            if (scopeNode == null)
            {
                throw new ArgumentNullException("scopeNode");
            }
            View view = (View) Activator.CreateInstance(this._viewType);
            view.Initialize(scopeNode, componentId, viewInstanceId, this);
            return view.MessageClient;
        }

        internal void Notify()
        {
            if (this.Changed != null)
            {
                this.Changed(this, null);
            }
        }

        public string DisplayName
        {
            get
            {
                return this._viewDescriptionData.DisplayName;
            }
            set
            {
                this._viewDescriptionData.DisplayName = value;
                this.Notify();
            }
        }

        internal int Id
        {
            get
            {
                return this._viewDescriptionData.Id;
            }
        }

        public string LanguageIndependentName
        {
            get
            {
                return this._viewDescriptionData.LanguageIndependentName;
            }
            set
            {
                this._viewDescriptionData.LanguageIndependentName = value;
                this.Notify();
            }
        }

        public object Tag
        {
            get
            {
                return this._tag;
            }
            set
            {
                this._tag = value;
            }
        }

        internal Microsoft.ManagementConsole.Internal.ViewDescriptionData ViewDescriptionData
        {
            get
            {
                return this._viewDescriptionData;
            }
        }

        public Type ViewType
        {
            get
            {
                return this._viewType;
            }
            set
            {
                if (value == null)
                {
                    throw new ArgumentNullException("value");
                }
                if (!value.Equals(this._baseViewType) && !value.IsSubclassOf(this._baseViewType))
                {
                    throw new ArgumentException(Microsoft.ManagementConsole.Internal.Utility.FormatResourceString(Microsoft.ManagementConsole.Internal.Strings.ExceptionCommonTypeUnexpected, new object[] { this._baseViewType.FullName }), "ViewType");
                }
                this._viewType = value;
            }
        }
    }
}

