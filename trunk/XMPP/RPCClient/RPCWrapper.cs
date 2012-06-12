using System;
using System.Collections.Generic;
using System.Text;

using RPCLibrary;
using System.Xml;
using agsXMPP;
using agsXMPP.Collections;
using agsXMPP.protocol.client;
using System.Threading;

namespace RPCClient
{
    public class RPCWrapper
    {
        private static XmppClientConnection con = null;
        private static Jid server = new Jid("server@yxd");
        private static Jid client = null;

        private static bool bWait = false;

        private static string method = null;
        private static Response response = null;

        private static AutoResetEvent autoEvent = new AutoResetEvent(false);

        public static void InitInstance(Jid client, string password)
        {
            RPCWrapper.con = new XmppClientConnection();
            RPCWrapper.client = client;

            RPCWrapper.con.Password = password;
            RPCWrapper.con.Username = client.User;
            RPCWrapper.con.Server = client.Server;
            RPCWrapper.con.AutoAgents = false;
            RPCWrapper.con.AutoPresence = true;
            RPCWrapper.con.AutoRoster = true;
            RPCWrapper.con.AutoResolveConnectServer = true;

            try
            {
                RPCWrapper.con.OnRosterStart += new ObjectHandler(RPCWrapper.OnRosterStart);
                RPCWrapper.con.OnRosterItem += new XmppClientConnection.RosterHandler(RPCWrapper.OnRosterItem);
                RPCWrapper.con.OnRosterEnd += new ObjectHandler(RPCWrapper.OnRosterEnd);
                RPCWrapper.con.OnPresence += new PresenceHandler(RPCWrapper.OnPresence);
                RPCWrapper.con.OnMessage += new MessageHandler(RPCWrapper.OnMessage);
                RPCWrapper.con.OnLogin += new ObjectHandler(RPCWrapper.OnLogin);

                RPCWrapper.con.Open();

            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            Wait();

        }

        public static void ExitInstance()
        {
            RPCWrapper.con.Close();
            RPCWrapper.con = null;
            RPCWrapper.client = null;
        }

        public static void SendMethodRequest(Request request)
        {
            Message msg = new Message();

            msg.Type = MessageType.chat;
            msg.To = server;
            msg.Body = request.ToString();

            RPCWrapper.con.Send(msg);

            method = request.Name;
            response = null;

            autoEvent.Reset();

        }

        public static Response ReceiveMethodResponse()
        {

            autoEvent.WaitOne();

            return response;

        }

        private static void Wait()
        {
            int i = 0;
            bWait = true;

            while (bWait)
            {
                i++;
                if (i == 60)
                    bWait = false;

                Thread.Sleep(500);
            }
        }

        static void OnLogin(object sender)
        {

        }

        static void OnRosterEnd(object sender)
        {
            bWait = false;
        }

        static void OnRosterItem(object sender, agsXMPP.protocol.iq.roster.RosterItem item)
        {
        }

        static void OnRosterStart(object sender)
        {

        }

        static void OnPresence(object sender, Presence pres)
        {

        }

        static void OnMessage(object sender, Message msg)
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

            if (name == Const.METHOD)
            {

                if (!root.HasAttribute("Type"))
                {
                    return;
                }

                string type = root.GetAttribute("Type");

                if (type != Const.REPONSE)
                {
                    return;
                }

                response = Response.Parse(root);

                if (response == null)
                {
                    return;
                }

                if (response.Name != method)
                {
                    return;
                }

                autoEvent.Set();

            }
            else if (name == Const.INFORM)
            {

            }
            else
            {

            }
        }

    }
}
