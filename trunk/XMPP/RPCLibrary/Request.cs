using System;
using System.Collections.Generic;
using System.Text;

using System.Xml;

namespace RPCLibrary
{
    public class Request:Method
    {
        public Request(string name)
            : base(name, Const.REQUEST)
        {
        }

        public Request(string name, Parameter[] parameters)
            : base(name, Const.REQUEST, parameters)
        {
        }

        public static Request Parse(XmlElement request)
        {
            if (request == null)
            {
                return null;
            }

            if (request.HasAttribute("Type"))
            {
                string type = request.GetAttribute("Type");
                if (type != Const.REQUEST)
                {
                    throw new Exception("method type error!");
                }
            }
            else
            {
                throw new Exception("method format error!");
            }

            Request result = null;

            if (request.HasAttribute("Name"))
            {
                string name = request.GetAttribute("Name");
                result = new Request(name);
            }
            else
            {
                throw new Exception("method format error!");
            }

            if (request.HasAttribute("Sequence"))
            {
                string sequence = request.GetAttribute("Sequence");
                result.Sequence = (sequence.ToLower() == "true" ? true : false);
            }
            else
            {
                throw new Exception("method format error!");
            }

            XmlNode parameterRoot = request.SelectSingleNode("Parameter");
            if (parameterRoot != null)
            {
                XmlNodeList parameters = parameterRoot.ChildNodes;
                foreach (XmlNode parameter in parameters)
                {
                    Parameter p = Parameter.Parse(parameter as XmlElement);
                    result.AddParameter(p);
                }
            }

            return result;

        }
        
    }

}
