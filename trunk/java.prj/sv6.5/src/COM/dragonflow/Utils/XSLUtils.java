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

import java.io.FileOutputStream;
import java.io.StringReader;
import java.io.StringWriter;

import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import jgl.Array;
import COM.datachannel.xml.om.Document;

// Referenced classes of package COM.dragonflow.Utils:
// SoapRpc, TextUtils, FileUtils

public class XSLUtils
{

    public static final boolean SHOW_FOOTER = true;
    public static final boolean NO_FOOTER = false;

    public XSLUtils()
    {
    }

    public static int matchXML(java.lang.String s, java.lang.String s1, jgl.Array array, java.lang.StringBuffer stringbuffer)
    {
        int i = COM.dragonflow.SiteView.Monitor.kURLContentMatchError;
        try
        {
            jgl.Array array1 = COM.dragonflow.SiteView.Platform.split(',', s1);
            COM.datachannel.xml.om.Document document = new Document();
            int j = 0;
            java.lang.String s2 = (java.lang.String)array1.at(j);
            java.lang.String s4 = "<?xml";
            java.lang.String s5 = null;
            java.lang.String s6 = "xml.endtag=";
            if(s2.startsWith("xml.endtag="))
            {
                j++;
                s5 = s2.substring(s6.length());
            }
            int k = s.indexOf(s4);
            if(k == -1)
            {
                i = COM.dragonflow.SiteView.Monitor.kXMLFormatError;
            } else
            {
                s = s.substring(k);
            }
            if(s5 != null)
            {
                int l = s.indexOf(s5);
                if(l == -1)
                {
                    i = COM.dragonflow.SiteView.Monitor.kXMLFormatError;
                } else
                {
                    s = s.substring(0, l + s5.length());
                }
            }
            if(i != COM.dragonflow.SiteView.Monitor.kXMLFormatError)
            {
                s = COM.dragonflow.Utils.SoapRpc.stripEncoding(s);
                document.loadXML(s);
                if(s1.length() != 0)
                {
                    do
                    {
                        if(j >= array1.size())
                        {
                            break;
                        }
                        java.lang.String s3 = (java.lang.String)array1.at(j++);
                        s3 = s3.trim();
                        s3 = s3.substring(4);
                        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
                        i = COM.dragonflow.Utils.XSLUtils.findMatches(document, s3, stringbuffer1, stringbuffer);
                        array.add(stringbuffer1.toString());
                    } while(i == COM.dragonflow.SiteView.Monitor.kURLok);
                }
            }
        }
        catch(java.lang.Exception exception)
        {
            COM.dragonflow.Log.LogManager.log("RunMonitor", "XML format error, " + exception);
            stringbuffer.append(exception.getMessage());
            i = COM.dragonflow.SiteView.Monitor.kXMLFormatError;
        }
        return i;
    }

    public static void findElements(org.w3c.dom.Node node, java.lang.String s, jgl.Array array)
    {
        java.lang.String s1 = s;
        java.lang.String s2 = "";
        int i = s.indexOf('.');
        if(i != -1)
        {
            s1 = s.substring(0, i);
            s2 = s.substring(i + 1);
        }
        java.lang.String s3 = node.getNodeName();
        if(s3 != null)
        {
            if(!s1.equals(s3.toString()))
            {
                return;
            }
            if(s2.length() == 0)
            {
                array.add(node);
            } else
            {
                org.w3c.dom.NodeList nodelist = node.getChildNodes();
                for(int j = 0; j < nodelist.getLength(); j++)
                {
                    org.w3c.dom.Node node1 = nodelist.item(j);
                    COM.dragonflow.Utils.XSLUtils.findElements(node1, s2, array);
                }

            }
        }
    }

    static int findMatches(COM.datachannel.xml.om.Document document, java.lang.String s, java.lang.StringBuffer stringbuffer, java.lang.StringBuffer stringbuffer1)
    {
        s = s.trim();
        int i = COM.dragonflow.SiteView.Monitor.kURLok;
        java.lang.String s1 = s;
        java.lang.String s2 = null;
        int j = s1.indexOf('=');
        if(j != -1)
        {
            s2 = s1.substring(j + 1);
            s1 = s1.substring(0, j);
        }
        int k = s1.indexOf(".[");
        java.lang.String s3 = null;
        if(k != -1)
        {
            s3 = s1.substring(k + 2, s1.length() - 1);
            s1 = s1.substring(0, k);
        }
        int l = s1.lastIndexOf("]");
        int i1 = 0;
        java.lang.String s4 = "";
        java.lang.String s6 = "";
        if(l != -1)
        {
            java.lang.String s8 = s1.substring(0, l);
            int j1 = s8.indexOf("[");
            if(j1 < l)
            {
                java.lang.String s9 = s1.substring(j1 + 1, l);
                int l1 = s9.indexOf("->");
                if(l1 >= 0)
                {
                    java.lang.String s10 = s8.substring(0, j1);
                    jgl.Array array1 = new Array();
                    java.lang.String s5 = s9.substring(0, l1);
                    java.lang.String s7 = s9.substring(l1 + 2);
                    COM.dragonflow.Utils.XSLUtils.findElements(document.getDocumentElement(), s10, array1);
                    java.util.Enumeration enumeration1 = array1.elements();
                    i1 = 1;
//                    while (enumeration.hasMoreElements()) {
//                        COM.datachannel.xml.om.Element element1 = (COM.datachannel.xml.om.Element)enumeration1.nextElement();
//                        if(element1.getAttribute(s5).equals(s7))
//                        {
//                            break;
//                        }
//                        i1++;
//                    } 
                } else
                {
                    i1 = COM.dragonflow.Utils.TextUtils.toInt(s9);
                }
                s8 = s8.substring(0, j1);
                java.lang.String s11 = s1.substring(l + 1);
                s1 = s8 + s11;
            }
        }
        jgl.Array array = new Array();
        COM.dragonflow.Utils.XSLUtils.findElements(document.getDocumentElement(), s1, array);
        java.util.Enumeration enumeration = array.elements();
        int k1 = 0;
        int i2 = 1;
        while (enumeration.hasMoreElements()) {
            java.lang.String s12 = "";
            COM.datachannel.xml.om.Element element = (COM.datachannel.xml.om.Element)enumeration.nextElement();
            if(i1 > 0)
            {
                if(i2++ != i1)
                {
                    continue;
                }
                s12 = s3 != null ? element.getAttribute(s3) : element.getText();
            } else
            {
                s12 = s3 != null ? element.getAttribute(s3) : element.getText();
            }
            if(stringbuffer.length() != 0)
            {
                stringbuffer.append(", ");
            }
            stringbuffer.append(s12);
            if(s2 != null && s2.equals(s12))
            {
                k1++;
            }
        } 
        
        java.lang.String s13 = "";
        if(array.size() == 0)
        {
            s13 = "missing " + s;
            i = COM.dragonflow.SiteView.Monitor.kXMLElementNotFoundError;
        } else
        if(s2 != null)
        {
            if(k1 == 0)
            {
                i = COM.dragonflow.SiteView.Monitor.kXMLElementMatchError;
                s13 = "expected " + s + ", found " + stringbuffer;
            }
        } else
        {
            s13 = "matched " + stringbuffer;
        }
        if(stringbuffer1.length() != 0)
        {
            stringbuffer1.append(", ");
        }
        stringbuffer1.append(s13);
        return i;
    }

    public static void convert(java.lang.String s, java.lang.String s1, java.lang.String s2)
        throws java.io.IOException
    {
        java.lang.String s3 = COM.dragonflow.Utils.FileUtils.readFile(s).toString();
        java.lang.String s4 = COM.dragonflow.Utils.FileUtils.readFile(s1).toString();
        java.io.FileOutputStream fileoutputstream = new FileOutputStream(s2);
        java.io.PrintWriter printwriter = COM.dragonflow.Utils.FileUtils.MakeOutputWriter(fileoutputstream);
        COM.dragonflow.Utils.XSLUtils.convert(s3, s4, printwriter, null, false);
        printwriter.close();
        fileoutputstream.close();
    }

    public static void convert(java.lang.String s, java.lang.String s1, java.io.PrintWriter printwriter)
    {
        COM.dragonflow.Utils.XSLUtils.convert(s, s1, printwriter, null, false);
    }

    private static java.lang.String addLineNumbers(java.lang.String s)
    {
        java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s, "\n");
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        for(int i = 0; i < as.length; i++)
        {
            COM.dragonflow.Utils.TextUtils.appendStringRightJustify(stringbuffer, "" + (i + 1), 5);
            stringbuffer.append("  ");
            stringbuffer.append(as[i]);
            stringbuffer.append("\n");
        }

        return stringbuffer.toString();
    }

    private static java.lang.String convertDataChannel(java.lang.String s, java.lang.String s1, java.lang.StringBuffer stringbuffer, java.lang.StringBuffer stringbuffer1, java.lang.StringBuffer stringbuffer2)
    {
        COM.datachannel.xml.om.Document document = new Document();
        try
        {
            document = new Document();
            document.loadXML(s);
        }
        catch(java.lang.Exception exception)
        {
            stringbuffer.append("Error Reading XML");
            stringbuffer1.append(exception.getMessage());
            stringbuffer2.append(COM.dragonflow.Utils.XSLUtils.addLineNumbers(s));
        }
        COM.datachannel.xml.om.Document document1 = new Document();
        try
        {
            document1 = new Document();
            document1.loadXML(s1);
        }
        catch(java.lang.Exception exception1)
        {
            stringbuffer.append("Error Reading XSL Template");
            stringbuffer1.append(exception1.getMessage());
            stringbuffer2.append(COM.dragonflow.Utils.XSLUtils.addLineNumbers(s));
        }
        java.lang.String s2 = "";
        if(stringbuffer1.length() == 0)
        {
            try
            {
                s2 = document.transformNode((COM.datachannel.xml.om.IXMLDOMNode)document1.getDocumentElement());
            }
            catch(java.lang.Exception exception2)
            {
                stringbuffer.append("Error Reading transforming XML");
                stringbuffer1.append(exception2.getMessage());
                if(stringbuffer1.length() == 0)
                {
                    stringbuffer1.append("" + exception2);
                }
            }
        }
        return s2;
    }

    private static java.lang.String convertSun(java.lang.String s, java.lang.String s1, java.lang.StringBuffer stringbuffer, java.lang.StringBuffer stringbuffer1, java.lang.StringBuffer stringbuffer2)
    {
        javax.xml.transform.Transformer transformer = null;
        try
        {
            javax.xml.transform.TransformerFactory transformerfactory = javax.xml.transform.TransformerFactory.newInstance();
            transformer = transformerfactory.newTransformer(new StreamSource(new StringReader(s1)));
        }
        catch(java.lang.Exception exception)
        {
            stringbuffer.append("Error Reading XSL Template");
            stringbuffer1.append(exception.getMessage());
            stringbuffer2.append(COM.dragonflow.Utils.XSLUtils.addLineNumbers(s));
        }
        java.lang.String s2 = "";
        if(stringbuffer1.length() == 0)
        {
            try
            {
                java.io.StringWriter stringwriter = new StringWriter();
                transformer.transform(new StreamSource(new StringReader(s)), new StreamResult(stringwriter));
                s2 = stringwriter.toString();
            }
            catch(java.lang.Exception exception1)
            {
                stringbuffer.append("Error Reading transforming XML");
                stringbuffer1.append(exception1.getMessage());
                if(stringbuffer1.length() == 0)
                {
                    stringbuffer1.append("" + exception1);
                }
            }
        }
        return s2;
    }

    public static java.lang.String getAttrValue(org.w3c.dom.Node node, java.lang.String s, java.lang.String s1, java.lang.StringBuffer stringbuffer)
    {
        jgl.Array array = new Array();
        java.lang.String s2 = null;
        try
        {
            if(s.length() > 0)
            {
                COM.dragonflow.Utils.XSLUtils.findElements(node, s, array);
                java.util.Enumeration enumeration = array.elements();
                org.w3c.dom.Node node1 = (org.w3c.dom.Node)enumeration.nextElement();
                s2 = ((COM.datachannel.xml.om.Element)node1).getAttribute(s1);
            } else
            {
                s2 = ((COM.datachannel.xml.om.Element)node).getAttribute(s1);
            }
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            stringbuffer.append(" Error getting the attribute. Check wsdl file ");
            stringbuffer.append(exception.toString() + " " + s);
        }
        return s2;
    }

    public static void convert(java.lang.String s, java.lang.String s1, java.io.PrintWriter printwriter, COM.dragonflow.HTTP.HTTPRequest httprequest, boolean flag)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        java.lang.StringBuffer stringbuffer2 = new StringBuffer();
        java.lang.String s2;
        if(s1.indexOf("xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\"") != -1)
        {
            s2 = COM.dragonflow.Utils.XSLUtils.convertSun(s, s1, stringbuffer, stringbuffer1, stringbuffer2);
        } else
        {
            s2 = COM.dragonflow.Utils.XSLUtils.convertDataChannel(s, s1, stringbuffer, stringbuffer1, stringbuffer2);
        }
        java.lang.String s3 = stringbuffer.toString();
        java.lang.String s4 = stringbuffer1.toString();
        java.lang.String s5 = stringbuffer2.toString();
        if(s4.length() > 0)
        {
            s2 = "<HTML><HEAD>" + COM.dragonflow.Page.CGI.nocacheHeader + COM.dragonflow.SiteView.Platform.charSetTag + "<TITLE>Error Generating Document</TITLE></HEAD>\n" + "<BODY BGCOLOR=#FFFFFF><H2>" + s3 + "</H2><P>\n" + s4 + "<HR>\n" + "<PRE>\n" + COM.dragonflow.Utils.TextUtils.escapeHTML(s5) + "</PRE>\n" + "</BODY></HTML>\n";
        }
        java.lang.String s6 = "";
        if(flag)
        {
            int i = s2.lastIndexOf("</BODY>");
            if(i == -1)
            {
                i = s2.lastIndexOf("</body>");
            }
            if(i >= 0)
            {
                s2 = s2.substring(0, i);
                s6 = s2.substring(i);
            }
        }
        if(httprequest != null)
        {
            s2 = COM.dragonflow.Utils.TextUtils.replaceString(s2, "account=administrator", "account=" + httprequest.getAccount());
            s2 = COM.dragonflow.Utils.TextUtils.replaceString(s2, "name=\"account\" value=\"administrator\"", "name=\"account\" value=\"" + httprequest.getAccount() + "\"");
        }
        printwriter.print(s2);
        if(flag)
        {
            COM.dragonflow.Page.CGI.printFooter(printwriter, httprequest);
        }
        printwriter.print(s6);
        printwriter.flush();
    }

    public static void main(java.lang.String args[])
    {
        if(args.length == 1)
        {
            COM.datachannel.xml.om.Document document = new Document();
            try
            {
                java.lang.String s = COM.dragonflow.Utils.FileUtils.readFile(args[0]).toString();
                COM.datachannel.xml.om.Document document1 = new Document();
                document1.loadXML(s);
            }
            catch(java.lang.Exception exception1)
            {
                java.lang.System.out.println("Exception: " + exception1.getMessage());
            }
        } else
        if(args.length != 3)
        {
            java.lang.System.out.println("Usage: XSLUtils xmlFile xslURL outputURL");
            java.lang.System.exit(0);
        } else
        {
            try
            {
                COM.dragonflow.Utils.XSLUtils.convert(args[0], args[1], args[2]);
            }
            catch(java.lang.Exception exception)
            {
                java.lang.System.out.println("Exception: " + exception);
                exception.printStackTrace();
            }
        }
    }
}
