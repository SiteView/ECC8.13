namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class ShowHelpTopicCommand : Command
    {
        private string _helpTopic;

        public string HelpTopic
        {
            get
            {
                return this._helpTopic;
            }
            set
            {
                this._helpTopic = value;
            }
        }
    }
}

