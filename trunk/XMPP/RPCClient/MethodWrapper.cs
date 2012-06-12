using System;
using System.Collections.Generic;
using System.Text;

using RPCLibrary;

namespace RPCClient
{
    public class MethodWrapper
    {
        public static List<string> GetTreeData(string name, int number, string description)
        {
            Request request = new Request("GetTreeData");
            request.AddParameter(new Parameter("name", name));
            request.AddParameter(new Parameter("number", number));
            request.AddParameter(new Parameter("description", description));

            RPCWrapper.SendMethodRequest(request);

            Response response = RPCWrapper.ReceiveMethodResponse();

            Parameter p = null;

            foreach (Parameter item in response.Parameters)
            {
                if (item.Direction == Direction.Return)
                {
                    p = item;
                    break;
                }
            }

            List<string> result = p.Value as List<string>;

            return result;

        }
    }
}
