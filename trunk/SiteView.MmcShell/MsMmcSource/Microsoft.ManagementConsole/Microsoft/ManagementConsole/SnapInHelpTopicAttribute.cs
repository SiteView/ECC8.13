namespace Microsoft.ManagementConsole
{
    using System;

    [AttributeUsage(AttributeTargets.Class, AllowMultiple=false)]
    public sealed class SnapInHelpTopicAttribute : Attribute
    {
        private bool _applicationBaseRelative = true;
        private string _topic;

        public SnapInHelpTopicAttribute(string topic)
        {
            this._topic = topic;
        }

        public bool ApplicationBaseRelative
        {
            get
            {
                return this._applicationBaseRelative;
            }
            set
            {
                this._applicationBaseRelative = value;
            }
        }

        public string Topic
        {
            get
            {
                return this._topic;
            }
        }
    }
}

