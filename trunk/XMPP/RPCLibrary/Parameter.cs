using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Text.RegularExpressions;

namespace RPCLibrary
{
    public enum Direction
    {
        In,
        Out,
        Both,
        Return
    }

    public class Parameter:Load
    {
        private Direction direction;
       
        public Direction Direction
        {
            get
            {
                return this.direction;
            }
            set
            {
                this.direction = value;
            }
        }

        public Parameter(string name, object value)
            : this(Direction.In, name, value)
        {

        }

        public Parameter(Direction direction, string name, object value)
            : this(direction, name, value.GetType().Name, value)
        {

        }

        public Parameter(string name, string type, object value)
            : this(Direction.In, name, type, value)
        {

        }

        public Parameter(string name, DAO data)
            : this(Direction.In, name, data)
        {
        }

        public Parameter(Direction direction, string name, DAO data):base(name, data)
        {
            this.direction = direction;
        }

        public Parameter(string name, ExtensionType extensionType, BasicType basicType, object value)
            : this(Direction.In, name, extensionType, basicType, value)
        {

        }

        public Parameter(Direction direction, string name, ExtensionType extensionType, BasicType basicType, object value):base(name, extensionType, basicType, value)
        {
            this.direction = direction;
        }

        public Parameter(Direction direction, string name, string type, object value):base(name, type, value)
        {
            this.direction = direction;
        }

        public override string ToString()
        {
            string temp = " Direction=\"" + this.direction.ToString() + "\"";
           
            int index = this.name.Length + 1;

            string result = base.ToString();

            result = result.Insert(index, temp);

            return result;
        }

        public static new Parameter Parse(XmlElement parameter)
        {
            if (parameter == null)
            {
                throw new Exception("parameter can't be null!");
            }

            string type = string.Empty; 
            string direction = string.Empty;

            if (parameter.HasAttribute("Type"))
            {
                type = parameter.GetAttribute("Type");
            }
            else
            {
                throw new Exception("load hasn't type attribute!");
            }

            if (parameter.HasAttribute("Direction"))
            {
                direction = parameter.GetAttribute("Direction");
            }
            else
            {
                throw new Exception("parameter hasn't direction attribute!");
            }

            Direction enumDirection = (Direction)Enum.Parse(typeof(Direction), direction);

            Parameter result = new Parameter(enumDirection, parameter.Name, type, parameter.InnerText);

            return result;

        }

    }

}
