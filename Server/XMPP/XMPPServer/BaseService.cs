using System;
using System.Collections.Generic;
using System.Text;

namespace Logistics
{
    namespace SubServer
    {
        public enum ServiceType
        {
            FileTransfer,
            ContactSearch,
            GroupChat
        }

        public class BaseService
        {
            private ServiceType serviceType;

            private string strName = null;
            private string strJId = null;

            public ServiceType ServiceType
            {
                get
                {
                    return this.serviceType;
                }
                set
                {
                    this.serviceType = value;
                }
            }

            public string Name
            {
                get
                {
                    return this.strName;
                }
                set
                {
                    this.strName = value;
                }
            }

            public agsXMPP.Jid JID
            {
                get
                {
                    return new agsXMPP.Jid(this.strJId);
                }
                set
                {
                    this.strJId = value.ToString();
                }
            }

        }
    }
}
