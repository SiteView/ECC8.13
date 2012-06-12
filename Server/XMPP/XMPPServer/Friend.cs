using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using agsXMPP.protocol.iq.roster;

namespace Logistics
{
    namespace SubServer
    {

        //<Friend>
        //  <JID>test1@192.168.6.26:SiteView</JID>
        //  <Nick>test1</Nick>
        //  <Group>
        //    <Item>SiteView</Item>
        //  </Group>
        //  <Subscribe>
        //    <type>both</type>
        //    <status>1</status>
        //  </Subscribe>
        //</Friend>

        public class Friend
        {
            private string strJID;
            private string strNick;
            private agsXMPP.protocol.iq.roster.SubscriptionType enuSubscriptionType;
            private int nStatus;
            private List<string> listGroup;

            private XmlNode friend = null;

            public Friend()
            {
                this.strJID = null;
                this.strNick = null;
                this.enuSubscriptionType = agsXMPP.protocol.iq.roster.SubscriptionType.none;
                this.nStatus = 0;
                this.listGroup = new List<string>();
            }

            public Friend(XmlNode friend):this()
            {
                this.friend = friend;

                ParseNode(friend);

            }

            public void Save()
            {
                if (this.friend == null)
                {
                    return;
                }

                XmlNode jid = friend.SelectSingleNode("JID");
                if (jid == null)
                {
                    jid = this.friend.OwnerDocument.CreateElement("JID");
                    this.friend.AppendChild(jid);
                }

                jid.InnerText = this.strJID;


                XmlNode nick = friend.SelectSingleNode("Nick");
                if (nick == null)
                {
                    nick = this.friend.OwnerDocument.CreateElement("Nick");
                    this.friend.AppendChild(nick);
                }

                nick.InnerText = this.strNick;

                friend.SelectSingleNode("Group").RemoveAll();
                foreach (string strGroup in this.listGroup)
                {
                    XmlNode groupItem = this.friend.OwnerDocument.CreateElement("Item");
                    friend.SelectSingleNode("Group").AppendChild(groupItem);
                    groupItem.InnerText = strGroup;
                }

                XmlNode subscribe = friend.SelectSingleNode("Subscribe");
                if (subscribe == null)
                {
                    subscribe = this.friend.OwnerDocument.CreateElement("Subscribe");
                    this.friend.AppendChild(subscribe);
                }

                XmlNode subscribeType = subscribe.SelectSingleNode("Type");
                if (subscribeType == null)
                {
                    subscribeType = this.friend.OwnerDocument.CreateElement("Type");
                    subscribe.AppendChild(subscribeType);
                }

                subscribeType.InnerText = this.enuSubscriptionType.ToString();

                XmlNode subscribeStatus = subscribe.SelectSingleNode("Status");
                if (subscribeStatus == null)
                {
                    subscribeStatus = this.friend.OwnerDocument.CreateElement("Status");
                    subscribe.AppendChild(subscribeStatus);
                }

                subscribeStatus.InnerText = this.nStatus.ToString();

            }

            private bool ParseNode(XmlNode friend)
            {
                if (friend == null)
                {
                    return false; 
                }

                if (this.listGroup == null)
                {
                    this.listGroup = new List<string>();
                }
                else
                {
                    this.listGroup.Clear();
                }

                foreach (XmlNode groupItem in friend.SelectSingleNode("Group").ChildNodes)
                {
                    this.listGroup.Add(groupItem.InnerText);
                }

                XmlNode nickName = friend.SelectSingleNode("Nick");
                if (nickName != null)
                {
                    this.strNick = nickName.InnerText;
                }
                
                XmlNode jid = friend.SelectSingleNode("JID");
                if(jid != null)
                {
                    this.strJID = jid.InnerText;
                }
                
                XmlNode subscribe = friend.SelectSingleNode("Subscribe");
                if (subscribe != null)
                {
                    XmlNode subscribeType = subscribe.SelectSingleNode("Type");
                    if (subscribeType != null)
                    {
                        this.enuSubscriptionType = (SubscriptionType)Enum.Parse(typeof(SubscriptionType), subscribeType.InnerText);
                    }

                    XmlNode subscribeStatus = subscribe.SelectSingleNode("Status");
                    if (subscribeStatus != null)
                    {
                        this.nStatus = int.Parse(subscribeStatus.InnerText);
                    }
                }

                return true;

            }

            public XmlNode XNode
            {
                get
                {
                    return this.friend;
                }
                set
                {
                    this.friend = value;
                    ParseNode(friend);
                }
            }

            public agsXMPP.Jid JID
            {
                get
                {
                    return new agsXMPP.Jid(this.strJID);
                }
                set
                {
                    this.strJID = value.ToString();
                }
            }

            public List<string> Groups
            {
                get
                {
                    return this.listGroup;
                }
                set
                {
                    this.listGroup = value;
                }
            }

            public void AddGroup(string strGroup)
            {
                if (!this.listGroup.Contains(strGroup))
                {
                    this.listGroup.Add(strGroup);
                    
                    ///****************************
                    /// XML
                    ///****************************
                    XmlNode groupItem = this.friend.OwnerDocument.CreateElement("Item");
                    groupItem.InnerText = strGroup;
                    this.friend.SelectSingleNode("Group").AppendChild(groupItem);
                    
                }

            }

            public void RemoveGroup(string strGroup)
            {
                if (this.listGroup.Contains(strGroup))
                {
                    this.listGroup.Remove(strGroup);

                    ///****************************
                    /// XML
                    ///****************************
                    string strPath = string.Format("Group/Item[text()='{0}']", strGroup);
                    XmlNode groupItem = this.friend.SelectSingleNode(strPath);
                    if (groupItem != null)
                    {
                        this.friend.SelectSingleNode("Group").RemoveChild(groupItem);
                    }

                }
            }
            

            public string Nick
            {
                get
                {
                    return this.strNick;
                }
                set
                {
                    this.strNick = value;
                }
            }

            public agsXMPP.protocol.iq.roster.SubscriptionType SubscriptionType
            {
                get
                {
                    return this.enuSubscriptionType;
                }
                set
                {
                    this.enuSubscriptionType = value;
                }
            }

            public int SubscriptionStatus
            {
                get
                {
                    return this.nStatus;
                }
                set
                {
                    this.nStatus = value;
                }
            }

        }
    }
}
