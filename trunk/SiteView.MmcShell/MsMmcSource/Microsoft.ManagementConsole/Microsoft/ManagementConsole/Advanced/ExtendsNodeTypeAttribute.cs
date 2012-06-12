namespace Microsoft.ManagementConsole.Advanced
{
    using System;

    [AttributeUsage(AttributeTargets.Class, AllowMultiple=true)]
    public sealed class ExtendsNodeTypeAttribute : Attribute
    {
        private Guid _nodeType;

        public ExtendsNodeTypeAttribute(string nodeType)
        {
            this._nodeType = new Guid(nodeType);
        }

        public Guid NodeType
        {
            get
            {
                return this._nodeType;
            }
        }
    }
}

