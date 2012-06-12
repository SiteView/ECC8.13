using System;
using System.Collections.Generic;
using System.Text;

using RPCLibrary;
using System.Xml;
using agsXMPP;
using agsXMPP.Collections;
using agsXMPP.protocol.client;
using System.Threading;

namespace RPCServer
{
    public class RPCMessageHandler
    {
        private static XmppClientConnection con = null;

        public static void InitInstance(XmppClientConnection con)
        {
            RPCMessageHandler.con = con;
        }

        public static void ExitInstance()
        {
            RPCMessageHandler.con = null;
        }

        public static void ProcessMessage(Message msg)
        {
            if (msg.Body == null)
            {
                return;
            }

            if (msg.FirstChild == null)
            {
                return;
            }

            XmlDocument doc = new XmlDocument();
            doc.LoadXml(msg.FirstChild.InnerXml);

            XmlElement root = doc.DocumentElement;

            string name = root.Name;

            if (name != Const.METHOD)
            {
                return;
            }

            if (!root.HasAttribute("Type"))
            {
                return;
            }

            string type = root.GetAttribute("Type");

            if (type != Const.REQUEST)
            {
                return;
            }

            Request request = Request.Parse(root);

            msg.SwitchDirection();

            Response response = HandleRequest(request);

            msg.Body = response.ToString();

            RPCMessageHandler.con.Send(msg);

        }


        private static Response HandleRequest(Request request)
        {

            Response response = null;

            switch (request.Name)
            {
                case "GetTreeData":
                    response = MethodWrapper.GetTreeData(request);
                    break;
                default:
                    break;
            }

            return response;

        }

    }
}
