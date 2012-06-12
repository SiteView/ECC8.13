using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace RPCLibrary
{
    public class Response:Method
    {
        public Response(string name)
            : base(name, Const.REPONSE)
        {
        }

        public Response(string name, Parameter[] parameters)
            : base(name, Const.REPONSE, parameters)
        {
        }

        public static Response Parse(XmlElement response)
        {
            if (response == null)
            {
                return null;
            }

            if (response.HasAttribute("Type"))
            {
                string type = response.GetAttribute("Type");
                if (type != Const.REPONSE)
                {
                    throw new Exception("method type error!");
                }
            }
            else
            {
                throw new Exception("method format error!");
            }

            Response result = null;

            if (response.HasAttribute("Name"))
            {
                string name = response.GetAttribute("Name");
                result = new Response(name);
            }
            else
            {
                throw new Exception("method format error!");
            }

            if (response.HasAttribute("Sequence"))
            {
                string sequence = response.GetAttribute("Sequence");
                result.Sequence = (sequence.ToLower() == "true" ? true : false);
            }
            else
            {
                throw new Exception("method format error!");
            }

            XmlNode parameterRoot = response.SelectSingleNode("Parameter");
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
