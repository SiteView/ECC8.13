 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */


// Referenced classes of package com.dragonflow.Utils:
// RawXmlWriter, StringPropertyUtil

public class HtmlUtil
{

    public HtmlUtil()
    {
    }

    public static java.lang.String createHiddenInputs(java.util.HashMap hashmap)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.util.Set set = hashmap.entrySet();
        java.util.Map.Entry entry;
        for(java.util.Iterator iterator = set.iterator(); iterator.hasNext(); stringbuffer.append("<INPUT type=hidden name='" + com.dragonflow.Utils.RawXmlWriter.enCodeElement((java.lang.String)entry.getKey()) + "' id='" + com.dragonflow.Utils.RawXmlWriter.enCodeElement((java.lang.String)entry.getKey()) + "' value='" + com.dragonflow.Utils.RawXmlWriter.enCodeElement((java.lang.String)entry.getValue()) + "'>\n"))
        {
            entry = (java.util.Map.Entry)iterator.next();
        }

        return stringbuffer.toString();
    }

    public static java.lang.String createHiddenInputs(com.dragonflow.Properties.StringProperty astringproperty[], java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("<INPUT type=hidden id='" + s + s3 + "' value='" + astringproperty.length + "'>\n");
        for(int i = 0; i < astringproperty.length; i++)
        {
            java.lang.String s4 = com.dragonflow.Utils.RawXmlWriter.enCodeElement(astringproperty[i].getLabel());
            stringbuffer.append("<INPUT type=hidden id='" + s + s1 + i + "' value='" + s4 + "'>\n");
            java.lang.String s5 = com.dragonflow.Utils.RawXmlWriter.enCodeElement(astringproperty[i].getDescription());
            stringbuffer.append("<INPUT type=hidden id='" + s + s2 + i + "' value='" + s5 + "'>\n");
        }

        return stringbuffer.toString();
    }

    public static java.lang.String createCheckboxList(com.dragonflow.Properties.StringProperty astringproperty[], java.lang.String s)
    {
        com.dragonflow.Properties.StringProperty astringproperty1[] = (com.dragonflow.Properties.StringProperty[])astringproperty.clone();
        com.dragonflow.Utils.StringPropertyUtil.sortPropsArray(astringproperty1);
        java.lang.StringBuffer stringbuffer = new StringBuffer("<SCRIPT LANGUAGE='Javascript' SRC='/SiteView/htdocs/js/utils.js'></SCRIPT>\n<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>\n   <TR>\n       <TD width=100%><DIV style='width:100%; height:88px; OVERFLOW: auto'>\n           <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>\n");
        for(int i = 0; i < astringproperty1.length; i++)
        {
            stringbuffer.append("               <TR>\n                   <TD>\n                       <INPUT type='checkbox' id='" + s + i + "' value=\"" + com.dragonflow.Utils.RawXmlWriter.enCodeElement(astringproperty1[i].getLabel()) + "\" title=\"" + com.dragonflow.Utils.RawXmlWriter.enCodeElement(astringproperty1[i].getDescription()) + "\">" + com.dragonflow.Utils.RawXmlWriter.enCodeElement(astringproperty1[i].getLabel()) + "</INPUT>\n" + "                   </TD>\n" + "               </TR>\n");
        }

        stringbuffer.append("           </TABLE>\n       </DIV></TD>\n       <TD vAlign=top>\n           <TABLE width=1 cellSpacing=0 cellPadding=0 border=0 align=top>\n               <TR><TD>\n                   <INPUT type=button title='Select all counters' value='Select All' onclick=\"checkCheckboxes('" + s + "', true)\">\n" + "               </TD></TR>\n" + "               <TR><TD>\n" + "                   <INPUT type=button value='Clear All' title='Clear all counter selections' onclick=\"checkCheckboxes('" + s + "', false)\" style='WIDTH: 100%'>\n" + "               </TD></TR>\n" + "           </TABLE>\n" + "       </TD>\n" + "   </TR>\n" + "</TABLE>\n");
        return stringbuffer.toString();
    }
}
