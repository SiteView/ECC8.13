using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace Logistics
{
    namespace SubServer
    {
        public enum AccountType
        {
            User,
            Service,
            Administrator
        }

        public class AccountComparer : IEqualityComparer<Account>
        {

            #region IEqualityComparer<Account> 成员

            public bool Equals(Account x, Account y)
            {
                if (x.Company != null && y.Company != null)
                {
                    if (x.Company.ToLower().Equals(y.Company.ToLower()) && (x.UserID.ToLower() == y.UserID.ToLower()))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (x.Company == null && y.Company == null)
                {
                    return x.UserID.ToLower() == y.UserID.ToLower();
                }
                else
                {
                    return false;
                }

            }

            public int GetHashCode(Account obj)
            {
                return obj.ToString().ToLower().GetHashCode();
            }

            #endregion
        }

        //<User>
        //  <ID>test</ID>
        //  <Name>test</Name>
        //  <Password>test</Password>
        //  <Role>0</Role>
        //  <Privacy></Privacy>
        //  <Privilege>0</Privilege>
        //  <Roster>
        //    <Friend>
        //      <Company>SiteView</Company>
        //      <ID>test1</ID>
        //      <Nick>test1</Nick>
        //       <Group>
        //        <Item>SiteView</Item>
        //      </Group>
        //     <Subscribe>
        //        <type>both</type>
        //        <status>1</status>
        //      </Subscribe>
        //    </Friend>
        //    <Friend>
        //      <Company>SiteView</Company>
        //      <ID>test2</ID>
        //      <Nick>test2</Nick>
        //      <Group>
        //        <Item>SiteView</Item>
        //      </Group>
        //      <Subscribe>
        //        <type>both</type>
        //        <status>1</status>
        //      </Subscribe>
        //    </Friend>
        //    <Friend>
        //      <Company>SiteView</Company>
        //      <ID>test3</ID>
        //      <Nick>test3</Nick>
        //      <Group>
        //        <Item>SiteView</Item>
        //      </Group>
        //      <Subscribe>
        //        <type>both</type>
        //        <status>1</status>
        //      </Subscribe>
        //    </Friend>
        //  </Roster>
        //</User>

        public class Account
        {
            private string strCompany;
            private string strUserID;
            private string strUserName;
            private string strPassword;
            
            //private string strRole;
            //private string strPrivacy;
            //private string strPrivilege;

            private agsXMPP.Jid objJid;
            private List<Friend> listFriend;

            private XmlNode xNode;

            private AccountType accountType;

            public Account()
            {

                //this.objCompany = ConfigManager.Company;
                //this.objCompany.ID = ConfigManager.Company.ID;
                //this.objCompany.Name = ConfigManager.Company.Name;
                if (ConfigManager.Company != null)
                {
                    this.strCompany = ConfigManager.Company.ID;
                }
                else
                {
                    this.strCompany = null;
                }

                this.accountType = AccountType.User;

                this.strUserID = null;
                this.strUserName = null;
                this.strPassword = null;

                //this.strRole = null;
                //this.strPrivacy = null;
                //this.strPrivilege = null;

                this.objJid = null;
                this.listFriend = new List<Friend>();

                this.xNode = null;
            }

            public Account(XmlNode account):this()
            {
                this.xNode = account;

                ParseNode(account);
            }

            public void Save()
            {

                if (this.xNode == null)
                {
                    return;
                }

                XmlNode userID = this.xNode.SelectSingleNode("ID");
                if (userID == null)
                {
                    userID = this.xNode.OwnerDocument.CreateElement("ID");
                    this.xNode.AppendChild(userID);
                }
                userID.InnerText = this.strUserID;

                XmlNode userName = this.xNode.SelectSingleNode("Name");
                if (userName != null)
                {
                    userName = this.xNode.OwnerDocument.CreateElement("Name");
                    this.xNode.AppendChild(userName);
                }
                userName.InnerText = this.strUserName;

                XmlNode password = this.xNode.SelectSingleNode("Password");
                if (password == null)
                {
                    password = this.xNode.OwnerDocument.CreateElement("Password");
                    this.xNode.AppendChild(password);
                }
                password.InnerText = this.strPassword;

                XmlNode role = this.xNode.SelectSingleNode("Role");
                if (role == null)
                {
                }

                XmlNode privacy = this.xNode.SelectSingleNode("Privacy");
                if (privacy == null)
                {
                }

                XmlNode privilege = this.xNode.SelectSingleNode("Privilege");
                if (privilege == null)
                {
                }

                foreach (Friend friend in this.listFriend)
                {
                    friend.Save();
                }

            }

            private bool ParseNode(XmlNode account)
            {
                if (account == null)
                {
                    return false;
                }

                XmlNode userID = account.SelectSingleNode("ID");
                if (userID != null)
                {
                    this.strUserID = userID.InnerText;
                }

                XmlNode userName = account.SelectSingleNode("Name");
                if (userName != null)
                {
                    this.strUserName = userName.InnerText;
                }

                XmlNode password = account.SelectSingleNode("Password");
                if (password != null)
                {
                    this.strPassword = password.InnerText;
                }

                XmlNode role = account.SelectSingleNode("Role");
                if (role != null)
                {
                    //this.strRole = role.InnerText;
                }

                XmlNode privacy = account.SelectSingleNode("Privacy");
                if (privacy != null)
                {
                    //this.strPrivacy = privacy.InnerText;
                }

                XmlNode privilege = account.SelectSingleNode("Privilege");
                if (privilege != null)
                {
                    //this.strPrivilege = privilege.InnerText;
                }

                XmlNode roster = account.SelectSingleNode("Roster");
                if (roster != null)
                {
                    foreach (XmlNode friend in roster.ChildNodes)
                    {
                        this.listFriend.Add(new Friend(friend));
                    }
                }

                return true;

            }

            public override string ToString()
            {
                string strTemp = null;

                StringBuilder sb = new StringBuilder();

                sb.Append("<User>");

                sb.Append("<Company>");
                //if (this.strCompany == null)
                //{
                //    strTemp = string.Empty;
                //}
                //else
                //{
                //    strTemp = this.strCompany.ToLower();
                //}
                //sb.Append(strTemp);
                sb.Append(this.strCompany);
                sb.Append("</Company>");

                sb.Append("<ID>");
                //strTemp = this.strUserID.ToLower();
                //sb.Append(strTemp);
                sb.Append(this.strUserID);
                sb.Append("</ID>");

                //*************************************************
                // 未完待续(Role, Privacy, Privilege, Friends.....)
                // 为了提高查找效率，精简项目便于取得HashCode
                //*************************************************

                //sb.Append("<Name>");
                //sb.Append(this.strUserName);
                //sb.Append("</Name>");

                //sb.Append("<Password>");
                //sb.Append(this.strPassword);
                //sb.Append("</Password>");

                //sb.Append("<Password>");
                //sb.Append(this.strPassword);
                //sb.Append("</Password>");

                sb.Append("</User>");

                return sb.ToString();
            }

            public XmlNode XNode
            {
                get
                {
                    return this.xNode;
                }
                set
                {
                    this.xNode = value;
                    ParseNode(value);
                 }
            }

            public AccountType Type
            {
                get
                {
                    return this.accountType;
                }
                set
                {
                    this.accountType = value;
                }
            }

            public string Company
            {
                get
                {
                    return this.strCompany;
                }
                set
                {
                    this.strCompany = value;
                }
            }

            public string UserID
            {
                get
                {
                    return this.strUserID;
                }
                set
                {
                    this.strUserID = value;
                }
            }

            public string UserName
            {
                get
                {
                    return this.strUserName;
                }
                set
                {
                    this.strUserName = value;
                }
            }

            public string Password
            {
                get
                {
                    return this.strPassword;
                }
                set
                {
                    this.strPassword = value;
                }
            }

            //public string Role
            //{
            //    get
            //    {
            //        return this.strRole;
            //    }
            //    set
            //    {
            //        this.strRole = value;
            //    }
            //}


            //public string Privacy
            //{
            //    get
            //    {
            //        return this.strPrivacy;
            //    }
            //    set
            //    {
            //        this.strPrivacy = value;
            //    }
            //}

            //public string Privilege
            //{
            //    get
            //    {
            //        return this.strPrivilege;
            //    }
            //    set
            //    {
            //        this.strPrivilege = value;
            //    }
            //}

            public agsXMPP.Jid JID
            {
                get
                {
                    if (this.accountType == AccountType.Service)
                    {
                        return new agsXMPP.Jid(this.strUserID);
                    }
                    else
                    {
                        //return new agsXMPP.Jid(this.strUserID, ConfigManager.Server, null, this.strCompany);//gt
                          return new agsXMPP.Jid(this.strUserID, ConfigManager.Server, null);
                    }
                }
                //set
                //{
                //    this.objJid = value;
                //}
            }

            public Friend FindFriend(string strJID)
            {
                if (this.listFriend == null)
                {
                    return null;
                }

                agsXMPP.Jid objJID = new agsXMPP.Jid(strJID);

                foreach (Friend friend in this.listFriend)
                {
                    if (friend.JID.Bare.ToLower() == objJID.Bare.ToLower())
                    {
                        return friend;
                    }
                }

                return null;

            }

            public Friend AddFriend()
            {

                //<Friend>
                //  <Company>SiteView</Company>
                //  <Group>
                //      <Item>SiteView</Item>
                //  </Group>
                //  <NickName>test</NickName>
                //  <JID>test@im.merchandiseflow.com</JID>
                //  <Subscribe>
                //    <type>both</type>
                //    <status>true</status>
                //  </Subscribe>
                //</Friend>

                XmlNode friend = this.xNode.OwnerDocument.CreateElement("Friend");

                this.xNode.SelectSingleNode("Roster").AppendChild(friend);

                XmlNode id = this.xNode.OwnerDocument.CreateElement("JID");
                friend.AppendChild(id);

                XmlNode nickName = this.xNode.OwnerDocument.CreateElement("Nick");
                friend.AppendChild(nickName);

                XmlNode group = this.xNode.OwnerDocument.CreateElement("Group");
                friend.AppendChild(group);

                XmlNode subscribe = this.xNode.OwnerDocument.CreateElement("Subscribe");

                XmlNode subscribeType = this.xNode.OwnerDocument.CreateElement("Type");
                subscribe.AppendChild(subscribeType);

                XmlNode subscribeStatus = this.xNode.OwnerDocument.CreateElement("Status");
                subscribe.AppendChild(subscribeStatus);

                Friend newFriend = new Friend(friend);
                this.listFriend.Add(newFriend);

                return newFriend;

            }

            public void RemoveFriend(Friend friend)
            {
                if (friend == null)
                {
                    return;
                }

                if (this.listFriend.Contains(friend))
                {
                    this.listFriend.Remove(friend);
                }

                friend.XNode.ParentNode.RemoveChild(friend.XNode);

            }

            public List<Friend> Friends
            {
                get
                {
                    return this.listFriend;
                }
                set
                {
                    this.listFriend = value;
                }
            }

        }
    }
}
