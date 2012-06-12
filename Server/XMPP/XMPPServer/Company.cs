using System;
using System.Collections.Generic;
using System.Text;

namespace Logistics
{
    namespace SubServer
    {
        public class Company//:agsXMPP.Xml.Dom.Element
        {
            private string strID;
            private string strName;
            private string strAddress;
            private string strTelephone;
            private string strFax;
            private string strEmail;
            private string strScale;
            private string strCategory;

            public Company()
            {
                this.strID = null;
                this.strName = null;
                this.strAddress = null;
                this.strTelephone = null;
                this.strFax = null;
                this.strEmail = null;
                this.strScale = null;
                this.strCategory = null;

            }

            //<Company>
            //    <ID>SiteView</ID>
            //    <Name>SiteView</Name>
            //</Company>
            public Company(System.Xml.XmlNode company):this()
            {
                if (company == null)
                {
                    return;
                }

                this.strID = company.SelectSingleNode("ID").InnerText;
                this.strName = company.SelectSingleNode("Name").InnerText;
            }

            public override bool Equals(object obj)
            {
                if (obj != null && obj is Company)
                {
                    return this.strID == ((Company)obj).strID;
                }
                else
                {
                    return false;
                }

            }

            public override int GetHashCode()
            {
                return this.strID.GetHashCode();
            }

            public override string ToString()
            {
                StringBuilder sb = new StringBuilder();

                sb.Append("<Company>");

                sb.Append("<ID>");
                sb.Append(this.strID);
                sb.Append("</ID>");

                sb.Append("<Name>");
                sb.Append(this.strName);
                sb.Append("</Name>");

                //sb.Append("<Address>");
                //sb.Append(this.strAddress);
                //sb.Append("</Address>");

                sb.Append("</Company>");

                return sb.ToString();
            }

            public string ID
            {
                get
                {
                    return this.strID;
                }
                set
                {
                    this.strID = value;
                }
            }

            public string Name
            {
                get
                {
                    return this.strName;
                }
                set
                {
                    this.strName = value;
                }
            }

            public string Address
            {
                get
                {
                    return this.strAddress;
                }
                set
                {
                    this.strAddress = value;
                }
            }

            public string Telephone
            {
                get
                {
                    return this.strTelephone;
                }
                set
                {
                    this.strTelephone = value;
                }
            }

            public string Fax
            {
                get
                {
                    return this.strFax;
                }
                set
                {
                    this.strFax = value;
                }
            }

            public string Email
            {
                get
                {
                    return this.strEmail;
                }
                set
                {
                    this.strEmail = value;
                }
            }

            public string Scale
            {
                get
                {
                    return this.strScale;
                }
                set
                {
                    this.strScale = value;
                }
            }

            public string Category
            {
                get
                {
                    return this.strCategory;
                }
                set
                {
                    this.strCategory = value;
                }
            }
        }
    }
}
