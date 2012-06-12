namespace Microsoft.ManagementConsole
{
    using System;

    [AttributeUsage(AttributeTargets.Class, AllowMultiple=true)]
    public sealed class SnapInLinkedHelpTopicAttribute : Attribute
    {
        private bool _applicationBaseRelative = true;
        private string _topic;

        public SnapInLinkedHelpTopicAttribute(string topic)
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

