using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace RPCLibrary
{
    public enum Operation
    {
        Add,
        Delete,
        Modify
    }

    public class Inform:Load
    {
        private Operation operation;

        public Inform(Operation operation, string name, DAO value):base(name, value)
        {
            this.operation = operation;
        }

        public Inform(Operation operation, string name, string type, object value):base(name, type, value)
        {
            this.operation = operation;
        }

        public Operation Operation
        {
            get
            {
                return this.operation;
            }
            set
            {
                this.operation = value;
            }
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<");
            sb.Append(Const.INFORM);
            sb.Append(" Operation=\"" + this.operation.ToString() + "\"");
            sb.Append(">");

            sb.Append(base.ToString());

            sb.Append("</" + Const.INFORM + ">");

            return sb.ToString();

        }

        public static new Inform Parse(XmlElement inform)
        {
            if (inform == null)
            {
                throw new Exception("parameter can't be null!");
            }

            string type = string.Empty;
            string operation = string.Empty;

            if (inform.HasAttribute("Type"))
            {
                type = inform.GetAttribute("Type");
            }
            else
            {
                throw new Exception("load hasn't type attribute!");
            }

            if (inform.HasAttribute("Operation"))
            {
                operation = inform.GetAttribute("Operation");
            }
            else
            {
                throw new Exception("parameter hasn't Operation attribute!");
            }

            Operation enumOperation = (Operation)Enum.Parse(typeof(Operation), operation);

            Inform result = new Inform(enumOperation, inform.Name, type, inform.InnerText);

            return result;

        }
    }
}
