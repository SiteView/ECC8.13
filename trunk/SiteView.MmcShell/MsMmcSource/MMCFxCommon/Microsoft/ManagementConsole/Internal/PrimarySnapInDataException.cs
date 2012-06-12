namespace Microsoft.ManagementConsole.Internal
{
    using System;
    using System.ComponentModel;
    using System.Runtime.Serialization;
    using System.Security.Permissions;

    [Serializable, EditorBrowsable(EditorBrowsableState.Never)]
    public sealed class PrimarySnapInDataException : Exception
    {
        public PrimarySnapInDataException()
        {
        }

        public PrimarySnapInDataException(string message) : base(message)
        {
        }

        public PrimarySnapInDataException(SerializationInfo information, StreamingContext context) : base(information, context)
        {
        }

        public PrimarySnapInDataException(string message, Exception innerException) : base(message, innerException)
        {
        }

        [SecurityPermission(SecurityAction.Demand, SerializationFormatter=true)]
        public override void GetObjectData(SerializationInfo information, StreamingContext context)
        {
            base.GetObjectData(information, context);
        }
    }
}

