namespace Microsoft.ManagementConsole
{
    using Microsoft.ManagementConsole.Internal;
    using System;
    using System.Reflection;

    public sealed class PropertyPageCollection : BaseCollection
    {
        public PropertyPageCollection() : base(typeof(PropertyPage))
        {
        }

        public int Add(PropertyPage propertyPage)
        {
            ValidatePropertyPage(propertyPage);
            return base.List.Add(propertyPage);
        }

        public bool Contains(PropertyPage propertyPage)
        {
            return base.List.Contains(propertyPage);
        }

        public void CopyTo(PropertyPage[] array, int index)
        {
            this.CopyTo(array, index);
        }

        public int IndexOf(PropertyPage propertyPage)
        {
            return base.List.IndexOf(propertyPage);
        }

        public void Insert(int index, PropertyPage propertyPage)
        {
            ValidatePropertyPage(propertyPage);
            base.Insert(index, propertyPage);
        }

        public void Remove(PropertyPage propertyPage)
        {
            base.List.Remove(propertyPage);
        }

        internal PropertyPageInfo[] ToPropertyPageInfoArray()
        {
            PropertyPageInfo[] infoArray = new PropertyPageInfo[base.Count];
            int index = 0;
            foreach (PropertyPage page in this)
            {
                infoArray[index] = new PropertyPageInfo();
                infoArray[index].Width = page.Control.Width;
                infoArray[index].Height = page.Control.Height;
                infoArray[index].Title = page.Title;
                infoArray[index].HelpTopic = page.HelpTopic;
                index++;
            }
            return infoArray;
        }

        private static void ValidatePropertyPage(PropertyPage propertyPage)
        {
            if (propertyPage == null)
            {
                throw new ArgumentNullException("propertyPage");
            }
            if (propertyPage.Initialized)
            {
                throw new InvalidOperationException(Microsoft.ManagementConsole.Internal.Utility.LoadResourceString(Microsoft.ManagementConsole.Internal.Strings.PropertyPageAddAlreadyAdded));
            }
            if (propertyPage.Control == null)
            {
                throw Microsoft.ManagementConsole.Internal.Utility.CreateArgumentException("propertyPage.Control", Microsoft.ManagementConsole.Internal.Strings.ArgumentExceptionNullValue, new object[0]);
            }
            Microsoft.ManagementConsole.Internal.Utility.CheckStringNullOrEmpty(propertyPage.Title, "Title", true);
        }

        public PropertyPage this[int index]
        {
            get
            {
                return (PropertyPage) base.List[index];
            }
            set
            {
                base.List[index] = value;
            }
        }
    }
}

