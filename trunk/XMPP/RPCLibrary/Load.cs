using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Text.RegularExpressions;

namespace RPCLibrary
{
    public class Load
    {
        protected string name;
        protected DAO data;

        public string Name
        {
            get
            {
                return this.name;
            }
        }

        public string Type
        {
            get
            {
                return this.data.Type;
            }
        }

        public object Value
        {
            get
            {
                return this.data.Value;
            }
            set
            {
                this.data.Value = value;
            }
        }

        public Load(string name, object value)
            : this(name, value.GetType().Name, value)
        {

        }

        public Load(string name, DAO data)
        {
            this.name = name;
            this.data = data;
        }

        public Load(string name, ExtensionType extensionType, BasicType basicType, object value)
        {

            this.name = name;
            
            if (extensionType != ExtensionType.List)
            {
                throw new Exception("Not supported type");
            }

            this.data = new List(basicType.ToString(), value);

        }

        public Load(string name, string type, object value)
        {

            this.name = name;

            if (Util.IsBasicType(type))
            {
                this.data = new DAO(type, value);
            }
            else if (Util.IsExtensionType(type))
            {
                int index = type.IndexOf('[');
                string type1 = string.Empty;
                if (index > 0)
                {
                    type1 = type.Substring(0, index);
                }
                Match match=null;
                if (type1 == "List")
                {
                    match = Regex.Match(type, "^(\\w+)\\[(\\w+)\\]$");
                    string extensionType = match.Groups[1].Value;
                    if (extensionType != ExtensionType.List.ToString())
                    {
                        throw new Exception("extension type not supported!");
                    }

                    string basicType = match.Groups[2].Value;
                    if (!Util.IsBasicType(basicType))
                    {
                        throw new Exception("basic type of extendsion type error!");
                    }
                    if (match.Groups.Count != 3)
                    {
                        throw new Exception("extendsion type error!");
                    }
                    this.data = new List(basicType, value);
                }
                if (type1 == "Map")
                {
                    match = Regex.Match(type, "^(\\w+)\\[(\\w+),(\\w+)\\]$");
                    string extensionType = match.Groups[1].Value;
                    if (extensionType != ExtensionType.ListMap.ToString())
                    {
                        throw new Exception("extension type not supported!");
                    }

                    string basicType1 = match.Groups[2].Value;
                    if (!Util.IsBasicType(basicType1))
                    {
                        throw new Exception("basic type of extendsion type error!");
                    }
                    string basicType2 = match.Groups[3].Value;
                    if (!Util.IsBasicType(basicType2))
                    {
                        throw new Exception("basic type of extendsion type error!");
                    }
                    if (match.Groups.Count != 4)
                    {
                        throw new Exception("extendsion type error!");
                    }
                    this.data = new Map(basicType1, basicType2, value);
                }
                if (type1 == "ListMap")
                {
                    match = Regex.Match(type, "^(\\w+)\\[(\\w+),(\\w+)\\]$");
                    string extensionType = match.Groups[1].Value;
                    if (extensionType != ExtensionType.ListMap.ToString())
                    {
                        throw new Exception("extension type not supported!");
                    }

                    string basicType1 = match.Groups[2].Value;
                    if (!Util.IsBasicType(basicType1))
                    {
                        throw new Exception("basic type of extendsion type error!");
                    }
                    string basicType2 = match.Groups[3].Value;
                    if (!Util.IsBasicType(basicType2))
                    {
                        throw new Exception("basic type of extendsion type error!");
                    }
                    if (match.Groups.Count != 4)
                    {
                        throw new Exception("extendsion type error!");
                    }
                    this.data = new ListMap(basicType1,basicType2, value);
                    
                }
                

               
                
            }
            else
            {
                throw new Exception("not supported type!");
            }

        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.Append("<");
            sb.Append(this.name);
            sb.Append(" Type=\"" + this.data.Type + "\"");
            sb.Append(">");

            sb.Append(this.data.ToString());

            sb.Append("</" + this.name + ">");

            return sb.ToString();
        }

        public static Load Parse(XmlElement load)
        {
            if (load == null)
            {
                throw new Exception("load can't be null!");
            }

            string type = string.Empty;

            if (load.HasAttribute("Type"))
            {
                type = load.GetAttribute("Type");
            }
            else
            {
                throw new Exception("load hasn't type attribute!");
            }

            Load result = new Load(load.Name, type, load.InnerText);

            return result;

        }

    }
}
