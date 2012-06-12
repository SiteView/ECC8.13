using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Windows.Forms;

namespace Logistics
{
    namespace SubServer
    {

        class AccountManager
        {
            private string strAccountFile = null;
            private XmlDocument doc = null;

            private List<Account> accounts = null;

            public AccountManager()
            {
                doc = new XmlDocument();
                this.strAccountFile = Application.StartupPath + "\\AccountDB.xml";
                doc.Load(this.strAccountFile);

                this.accounts = new List<Account>();
                XmlNodeList users = doc.DocumentElement.SelectNodes("//User");
                foreach (XmlNode user in users)
                {
                    Account account = new Account(user);
                    accounts.Add(account);
                }

            }

            public bool Load(string strAccountFile)
            {
                if (!System.IO.File.Exists(strAccountFile))
                {
                    return false;
                }

                this.strAccountFile = strAccountFile;

                doc = new XmlDocument();
                doc.Load(strAccountFile);

                if (this.accounts != null)
                {
                    this.accounts.Clear();
                }

                this.accounts = new List<Account>();
                XmlNodeList users = doc.DocumentElement.SelectNodes("//User");
                foreach (XmlNode user in users)
                {
                    Account account = new Account(user);
                    accounts.Add(account);
                }

                return true;

            }

            public void Save()
            {
                if (doc != null)
                {
                    doc.Save(this.strAccountFile);
                }
            }

            public void SaveAs(string strFilePath)
            {
                if (doc != null)
                {
                    doc.Save(strFilePath);
                }
            }

            //<User>
            //  <UserID>test</UserID>
            //  <UserName>test</UserName>
            //  <Password>test</Password>
            //  <Role>0</Role>
            //  <Group>SiteView</Group>
            //  <Privacy></Privacy>
            //  <Privilege>0</Privilege>
            //  <Roster>
            //    <Friend>
            //      <Company>SiteView</Company>
            //      <Group>SiteView</Group>
            //      <NickName>test1</NickName>
            //      <JID>test1@im.merchandiseflow.com</JID>
            //      <Subscribe>
            //        <type>both</type>
            //        <status>0</status>
            //      </Subscribe>
            //    </Friend>
            //    <Friend>
            //      <Company>SiteView</Company>
            //      <Group>SiteView</Group>
            //      <NickName>test2</NickName>
            //      <JID>test2@im.merchandiseflow.com</JID>
            //      <Subscribe>
            //        <type>both</type>
            //        <status>0</status>
            //      </Subscribe>
            //    </Friend>
            //    <Friend>
            //      <Company>SiteView</Company>
            //      <Group>SiteView</Group>
            //      <NickName>test3</NickName>
            //      <JID>test3@im.merchandiseflow.com</JID>
            //      <Subscribe>
            //        <type>both</type>
            //        <status>0</status>
            //      </Subscribe>
            //    </Friend>
            //  </Roster>
            //</User>

            public Account FindAccount(string strJID)
            {
                agsXMPP.Jid objJID = new agsXMPP.Jid(strJID);
                foreach (Account account in this.accounts)
                {
                    if (account.JID.Bare.ToLower() == objJID.Bare.ToLower())
                    {
                        return account;
                    }
                }

                return null;
            }
            public Account AddAccount()
            {
                XmlNode user = doc.CreateElement("User");
                this.doc.DocumentElement.AppendChild(user);

                XmlNode userID = doc.CreateElement("UserID");
                user.AppendChild(userID);

                XmlNode userName = doc.CreateElement("UserName");
                user.AppendChild(userName);

                XmlNode password = doc.CreateElement("Password");
                user.AppendChild(password);

                XmlNode role = doc.CreateElement("Role");
                user.AppendChild(role);

                XmlNode group = doc.CreateElement("Group");
                user.AppendChild(group);

                XmlNode privacy = doc.CreateElement("Privacy");
                user.AppendChild(privacy);

                XmlNode privilege = doc.CreateElement("Privilege");
                user.AppendChild(privilege);

                XmlNode roster = doc.CreateElement("Roster");
                user.AppendChild(roster);

                Account account = new Account(user);
                this.accounts.Add(account);
                
                return account;
            }

            public void RemoveAccount(Account account)
            {
                if (account.XNode != null)
                {
                    account.XNode.ParentNode.RemoveChild(account.XNode);
                }

                if (this.accounts.Contains(account))
                {
                    this.accounts.Remove(account);
                }

            }

            public List<Account> Accounts
            {
                get
                {
                    return this.accounts;
                }
                set
                {
                    if (this.accounts != null)
                    {
                        this.accounts.Clear();
                    }

                    this.accounts = value;
                }
            }

        }
    }
}
