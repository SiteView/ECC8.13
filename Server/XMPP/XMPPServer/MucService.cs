using System;
using System.Collections.Generic;
using System.Text;

namespace Logistics
{
    namespace SubServer
    {
        public class User
        {
            public string Nick;
            public agsXMPP.Jid JID;
            public agsXMPP.protocol.x.muc.Role Role;
            public agsXMPP.protocol.x.muc.Affiliation Affiliation;
        }

        public class ChatRoom
        {
            public string Name;
            public string Subject;
            public string Category;
            public string Type;
            public agsXMPP.Jid JID;

            private List<string> features;

            private User owner;
            private List<User> admins;
            private List<User> members;
            private List<User> outcasts;
            private List<User> nones;

            private List<User> onlines;

            public List<string> GetFeatures()
            {
                return features;
            }

            public void AddFeature(string strFeature)
            {
                if (features == null)
                {
                    features = new List<string>();
                }

                features.Add(strFeature);
            }

            public void RemoveFeature(string strFeature)
            {
                if (features != null)
                {
                    if (features.Contains(strFeature))
                    {
                        features.Remove(strFeature);
                    }

                }

            }

            public User Owner
            {
                get
                {
                    return owner;
                }
                set
                {
                    if (value.Affiliation == agsXMPP.protocol.x.muc.Affiliation.owner)
                    {
                        owner = value;
                    }
                }
            }

            public List<User> GetAdmin()
            {
                return admins;
            }

            public bool AddAdmin(User admin)
            {
                if (admin.Affiliation != agsXMPP.protocol.x.muc.Affiliation.admin)
                {
                    return false;
                }

                foreach (User user in admins)
                {
                    if (user.JID.Bare.ToLower() == admin.JID.Bare.ToLower())
                    {
                        return false;
                    }
                }

                if (admins == null)
                {
                    admins = new List<User>();
                }

                admins.Add(admin);

                return true;
            }

            public bool RemoveAdmin(User admin)
            {
                if (admin.Affiliation != agsXMPP.protocol.x.muc.Affiliation.admin)
                {
                    return false;
                }

                foreach (User user in admins)
                {
                    if (user.JID.Bare.ToLower() == admin.JID.Bare.ToLower())
                    {
                        admins.Remove(user);
                        return true;
                    }
                }

                return false;
            }

            public List<User> GetMember()
            {
                return members;
            }

            public bool AddMember(User member)
            {
                if (member.Affiliation != agsXMPP.protocol.x.muc.Affiliation.member)
                {
                    return false;
                }

                foreach (User user in members)
                {
                    if (user.JID.Bare.ToLower() == member.JID.Bare.ToLower())
                    {
                        return false;
                    }
                }

                if (members == null)
                {
                    members = new List<User>();
                }

                members.Add(member);

                return true;

            }

            public bool RemoveMember(User member)
            {
                if (member.Affiliation != agsXMPP.protocol.x.muc.Affiliation.member)
                {
                    return false;
                }

                foreach (User user in members)
                {
                    if (user.JID.Bare.ToLower() == member.JID.Bare.ToLower())
                    {
                        members.Remove(user);
                        return true;
                    }
                }

                return false;

            }

            public bool Exit(User logoff)
            {
                foreach (User user in onlines)
                {
                    if (user.JID.ToString().ToLower() == logoff.JID.ToString().ToLower())
                    {
                        onlines.Remove(user);
                        return true;
                    }
                }

                return false;

            }

            public bool Enter(User login)
            {
                if (this.onlines == null)
                {
                    this.onlines = new List<User>();
                }

                foreach (User user in onlines)
                {
                    if (user.JID.Bare.ToLower() == login.JID.Bare.ToLower())
                    {
                        return false;
                    }
                }

                this.onlines.Add(login);

                return true;
            }

            public List<User> GetOnlines()
            {
                return this.onlines;
            }

            public User FindOnline(string strJID)
            {
                foreach (User user in this.onlines)
                {
                    if (user.JID.Bare.ToLower() == strJID.ToLower())
                    {
                        return user;
                    }
                }

                return null;
            }

        }

        public class MucService : BaseService
        {
            private Dictionary<string, ChatRoom> roomList = null;

            public MucService()
            {
                this.ServiceType = ServiceType.GroupChat;

                this.roomList = new Dictionary<string, ChatRoom>();

                ChatRoom chatroom = new ChatRoom();

                chatroom.Name = "Conference";
                chatroom.Subject = "Site View Logistics Chat Room";
                chatroom.Category = ServiceType.GroupChat.ToString();
                chatroom.Type = "text";

                chatroom.JID = new agsXMPP.Jid("Conference@Muc.SiteView.com");

                User owner = new User();
                owner.Nick = "Administrator";
                owner.Role = agsXMPP.protocol.x.muc.Role.none;
                owner.Affiliation = agsXMPP.protocol.x.muc.Affiliation.owner;
                owner.JID = new agsXMPP.Jid("admin@" + ConfigManager.Server);

                chatroom.Owner = owner;

                //<feature var='http://jabber.org/protocol/muc'/>
                //<feature var='muc_passwordprotected'/>
                //<feature var='muc_hidden'/>
                //<feature var='muc_temporary'/>
                //<feature var='muc_open'/>
                //<feature var='muc_unmoderated'/>
                //<feature var='muc_nonanonymous'/>

                chatroom.AddFeature(agsXMPP.Uri.MUC);

                this.roomList.Add(chatroom.Name, chatroom);

            }

            public Dictionary<string, ChatRoom> GetRooms()
            {
                return this.roomList;
            }

            public ChatRoom RegisterRoom(string strJID)
            {
                return null;
            }

            public bool DestroyChatRoom(string strJID)
            {
                return true;
            }

            public ChatRoom FindChatRoom(string strJID)
            {
                if (roomList.ContainsKey(strJID))
                {
                    return roomList[strJID];
                }

                return null;
            }
        }
    }
}
