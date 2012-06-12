using System;
using System.Collections.Generic;
using System.Text;

using RPCLibrary;

namespace RPCServer
{
    public class MethodWrapper
    {
        public static Response GetTreeData(Request request)
        {
            string name = request.FindParameter("name").Value as string;
            int number = (int)request.FindParameter("number").Value;
            string description = request.FindParameter("description").Value as string;

            Response response = new Response("GetTreeData");

            List<string> result = new List<string>();

            for(int i = 0 ; i < number; i ++)
            {
                result.Add(i.ToString().PadLeft(20, '0'));
            }

            ListDAO data = new ListDAO(BasicType.String.ToString(), result);
            response.AddParameter(new Parameter(Direction.Return, "return", data));

            return response;

        }
    }
}
