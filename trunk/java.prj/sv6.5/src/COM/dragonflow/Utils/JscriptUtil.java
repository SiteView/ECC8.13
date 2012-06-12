 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package COM.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */


public class JscriptUtil
{

    public JscriptUtil()
    {
    }

    public static java.lang.String createFieldsAsUrlParamsFunc(java.lang.String s, java.lang.String as[])
    {
        java.lang.String s1 = "inputsNamesArray";
        java.lang.String s2 = COM.dragonflow.Utils.JscriptUtil.createArray(s1, as);
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("<SCRIPT>\n   function " + s + "(){\n" + "       " + s2 + "       var urlParams = \"\";\n" + "       isFirst = true;\n" + "       for (i=0; i<" + s1 + ".length; i++){\n" + "           var colObj = document.getElementsByName(" + s1 + "[i]);\n" + "           for (j=0; j<colObj.length; j++){\n" + "               if (colObj[j].tagName.toLowerCase() == \"input\"){\n" + "                   if (!isFirst){\n" + "                       urlParams += \"&\";\n" + "                   }else{\n" + "                       isFirst = false;\n" + "                   }\n" + "               }\n" + "               urlParams += colObj[j].name + \"=\" + colObj[j].value;\n" + "               break;\n" + "           }\n" + "       }\n" + "       return urlParams;" + "   }\n" + "</SCRIPT>\n");
        return stringbuffer.toString();
    }

    private static java.lang.String createArray(java.lang.String s, java.lang.String as[])
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("var " + s + "= new Array(");
        for(int i = 0; i < as.length; i++)
        {
            stringbuffer.append("\"" + as[i] + "\"");
            if(i < as.length - 1)
            {
                stringbuffer.append(",");
            }
        }

        stringbuffer.append(");\n");
        return stringbuffer.toString();
    }

    public static java.lang.String createArrayFromInstancePropsFunc(java.lang.String s, COM.dragonflow.Properties.StringProperty astringproperty[])
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("function " + s + "(){\n" + "   var propsArray = new Array(\n");
        for(int i = 0; i < astringproperty.length; i++)
        {
            java.lang.String s1 = astringproperty[i].getLabel();
            java.lang.String s2 = astringproperty[i].getDescription();
            stringbuffer.append("       new Array(\"" + s1 + "\",\"" + s2 + "\")");
            if(i < astringproperty.length - 1)
            {
                stringbuffer.append(",\n");
            }
        }

        stringbuffer.append(");\n");
        stringbuffer.append("   return propsArray;\n");
        stringbuffer.append("}\n");
        return stringbuffer.toString();
    }
}
