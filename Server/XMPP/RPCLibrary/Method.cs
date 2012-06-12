using System;
using System.Collections.Generic;
using System.Text;

namespace RPCLibrary
{
    public abstract class Method
    {
        private string type;
        private string name;
        private bool sequence = false;
        private IList<Parameter> parameters;

        public string Name
        {
            get
            {
                return this.name;
            }
            set
            {
                this.name = value;
            }
        }

        public string Type
        {
            get
            {
                return this.type;
            }
            set
            {
                this.type = value;
            }
        }

        public bool Sequence
        {
            get
            {
                return this.sequence;
            }
            set
            {
                this.sequence = value;
            }
        }

        public Method(string name, string type)
        {
            this.name = name;
            this.type = type;

            this.parameters = new List<Parameter>();
        }

        public Method(string name, string type, Parameter[] parameters)
            : this(name, type)
        {
            foreach (Parameter parameter in parameters)
            {
                this.parameters.Add(parameter);
            }
        }

        public IList<Parameter> Parameters
        {
            get
            {
                return this.parameters;
            }
        }

        public void AddParameter(Parameter parameter)
        {
            foreach (Parameter p in this.parameters)
            {
                if (p.Name == parameter.Name)
                {
                    return;
                }
            }

            this.parameters.Add(parameter);
        }

        public void DeleParameter(string name)
        {
            foreach (Parameter parameter in this.parameters)
            {
                if (parameter.Name == name)
                {
                    this.parameters.Remove(parameter);
                }
            }
        }

        public Parameter FindParameter(string name)
        {
            foreach (Parameter parameter in this.parameters)
            {
                if (parameter.Name == name)
                {
                    return parameter;
                }
            }

            return null;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<");
            sb.Append(Const.METHOD);
            sb.Append(" Name=\"" + this.name + "\"");
            sb.Append(" Type=\"" + this.type + "\"");
            sb.Append(" Sequence=\"" + this.sequence.ToString() + "\"");
            sb.Append(">");

            sb.Append("<Parameter>");
            
            foreach (Parameter parameter in this.parameters)
            {
                sb.Append(parameter.ToString());
            }

            sb.Append("</Parameter>");

            sb.Append("</" + Const.METHOD + ">");
            return sb.ToString();
        }
    }
}
