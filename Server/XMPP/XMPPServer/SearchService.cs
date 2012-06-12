using System;
using System.Collections.Generic;
using System.Text;

namespace Logistics
{
    namespace SubServer
    {
        public class SearchService : BaseService
        {
            public SearchService()
            {
                this.ServiceType = ServiceType.ContactSearch;
            }

        }
    }
}
