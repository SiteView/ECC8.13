namespace Microsoft.ManagementConsole
{
    using System;

    [AttributeUsage(AttributeTargets.Class, AllowMultiple=true)]
    public sealed class PublishesNodeTypeAttribute : Attribute
    {
        private string _description = string.Empty;
        private System.Guid _guid;

        public PublishesNodeTypeAttribute(string guid)
        {
            this._guid = new System.Guid(guid);
        }

        public string Description
        {
            get
            {
                return this._description;
            }
            set
            {
                this._description = value;
            }
        }

        public System.Guid Guid
        {
            get
            {
                return this._guid;
            }
        }
    }
}

