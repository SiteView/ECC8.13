/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Page;

import java.io.File;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.HTTP.HTTPRequestException;
import COM.dragonflow.Utils.WSDLParser;

// Referenced classes of package COM.dragonflow.Page:
// monitorPage, CGI

public class serviceWizardPage extends COM.dragonflow.Page.monitorPage
{

    java.lang.String addMonitor;
    java.lang.String getMethods;
    java.lang.String getArgs;
    java.lang.String updateMonitor;
    java.lang.String urlType;
    java.lang.String urlPrefix;
    java.lang.String methodType;
    private final java.lang.String methodHelp = "This is a list of available methods for this Web Service";
    private final java.lang.String inputHelp = "This is the input argument list for the chosen web service method<P>";
    private final java.lang.String inputHelp_noArg = "This method takes no arguments - leave the above text field blank<P>";
    java.lang.String methodArgs;
    int displayMax;
    int methodNameMax;
    java.lang.String stepHelp;
    java.lang.String startHelp;
    private COM.dragonflow.Utils.WSDLParser wsdlParser;
    java.lang.String WSDL_DIRECTORY;
    public static boolean debug = false;

    public serviceWizardPage()
    {
        addMonitor = "Add Monitor";
        getMethods = "Get Methods";
        getArgs = "Get Arguments";
        updateMonitor = "Update Monitor";
        urlType = "url";
        urlPrefix = "http://";
        methodType = "_methodname";
        methodArgs = "";
        displayMax = 80;
        methodNameMax = 30;
        stepHelp = "";
        startHelp = "";
        wsdlParser = null;
        WSDL_DIRECTORY = "templates.wsdl";
    }

    void printHeaders(java.lang.String s)
    {
        printBodyHeader("Web Service Wizard");
        printButtonBar("WebServiceMonitor.htm", "");
        outputStream.println("<P><H2>Add Web Service Monitor</H2></P>\n<P><FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n" + s);
    }

    void printErrorHtml(java.lang.String s)
    {
        printBodyHeader("Web Service Wizard");
        printButtonBar("WebServiceMonitor.htm", "");
        outputStream.println("<P>\n<H2>Get Method Error</H2>\n<P><br>There was an error retrieving the methods for the Web Service:<blockquote><b>" + s + "</b></blockquote>\n" + "<P><br>Press BACK on your browser to continue\n");
        printFooter(outputStream);
    }

    private void setHiddenInfo()
    {
        outputStream.print("<input type=hidden name=class value=\"" + request.getValue("class") + "\">\n" + "<input type=hidden name=page value=\"" + request.getValue("page") + "\">\n" + "<input type=hidden name=group value=\"" + request.getValue("group") + "\">\n" + "<input type=hidden name=id value=\"" + request.getValue("id") + "\">\n" + "<input type=hidden name=operation value=\"" + request.getValue("operation") + "\">\n" + "<input type=hidden name=account value=\"" + request.getAccount() + "\">\n");
    }

    public void printBody()
        throws java.lang.Exception
    {
        COM.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
        jgl.Array array2 = null;
        if(request.getValue("group").length() > 0)
        {
            array2 = ReadGroupFrames(request.getValue("group"));
        }
        if(request.getValue("operation").equals("Edit") || request.getValue("operation").equals("Tool"))
        {
            addMonitor = updateMonitor;
        }
        if(!request.getValue("operation").equals("Add") && request.getValue("group").length() > 0)
        {
            atomicmonitor = COM.dragonflow.SiteView.AtomicMonitor.MonitorCreate(array2, request.getValue("id"), request.getPortalServer());
            jgl.Array array = atomicmonitor.getProperties();
            COM.dragonflow.Properties.StringProperty stringproperty;
            java.lang.String s2;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); request.setValue(stringproperty.getName(), s2))
            {
                stringproperty = (COM.dragonflow.Properties.StringProperty)enumeration.nextElement();
                s2 = "";
                if(stringproperty.isMultiLine)
                {
                    for(java.util.Enumeration enumeration2 = atomicmonitor.getMultipleValues(stringproperty); enumeration2.hasMoreElements();)
                    {
                        s2 = s2 + enumeration2.nextElement() + "\n";
                    }

                } else
                {
                    s2 = atomicmonitor.getProperty(stringproperty);
                }
            }

        }
        if(request.getValue("operation").equals("Tool"))
        {
            if(!request.actionAllowed("_tools"))
            {
                throw new HTTPRequestException(557);
            }
            printBodyHeader("Web Service Test");
            if(!request.getValue("AWRequest").equals("yes"))
            {
                printButtonBar("WebService.htm", "");
            } else
            {
                outputStream.println("<center><a href=/SiteView/cgi/go.exe/SiteView?page=monitor&operation=Tools&account=" + request.getAccount() + "&AWRequest=yes>Diagnostic Tools</a></center><p>");
            }
            java.lang.String s = request.getValue("_wsdlurl");
            java.lang.String s3 = request.getValue("_methodname");
            java.lang.String s4 = request.getValue("_argnames");
            java.lang.String s6 = request.getValue("_contenttype");
            java.lang.String s8 = request.getValue("_schema");
            java.lang.String s9 = request.getValue("_methodns");
            java.lang.String s11 = request.getValue("_actionuri");
            java.lang.String s13 = request.getValue("_serverurl");
            java.lang.String s15 = request.getValue("_username");
            java.lang.String s16 = request.getValue("_ntlmDomain");
            java.lang.String s17 = request.getValue("_proxy");
            java.lang.String s18 = request.getValue("_proxyuser");
            java.lang.String s19 = request.getValue("_useDotNetSoap");
            java.lang.String s20 = request.getValue("_URLUserAgent");
            java.lang.StringBuffer stringbuffer3 = new StringBuffer();
            java.lang.StringBuffer stringbuffer4 = new StringBuffer();
            java.lang.StringBuffer stringbuffer5 = new StringBuffer();
            java.lang.StringBuffer stringbuffer6 = new StringBuffer();
            java.lang.String s21 = COM.dragonflow.Properties.StringProperty.getPrivate(request, "_password", "serviceSuff", stringbuffer3, stringbuffer4);
            java.lang.String s22 = COM.dragonflow.Properties.StringProperty.getPrivate(request, "_proxypassword", "pSevericeSuff", stringbuffer5, stringbuffer6);
            COM.dragonflow.Utils.TextUtils.debugPrint(" hello " + s + " methodname " + s3 + " serverurl " + s13);
            java.lang.String s23 = s19.length() <= 0 ? "" : "checked";
            java.lang.String s24 = COM.dragonflow.Utils.TextUtils.encodeArgs(s4);
            COM.dragonflow.Page.serviceWizardPage.status("NEWARGS = " + s24);
            outputStream.println("<p>\n<CENTER><H2>Web Service Test</H2></CENTER><P>\n<p>\n<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\nUse this form to test an existing Web Service for availability by sending it a true SOAP request over HTTP. In addition, you can examine the actual SOAP response message that gets returned.  The Web Service URL specifies which\nserver to contact, the method name and arguments are then used to build the request.\nEnter the URL of the Web Service endpoint, and optionally, the user name, password and/or proxy server \nto use for contacting the web service.\n If you have an existing web service monitor, you can click its Tools link to have these input fields filled in automatically. See the Tools online help for details.\n<p><TABLE BORDER=0>\n<TR><TD ALIGN=RIGHT>WSDL Path or URL:<TD><input type=text name=_wsdlurl value=\"" + s + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>Web Service URL:<TD><input type=text name=_serverurl value=\"" + s13 + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>Method Name:<TD><input type=text name=_methodname value=\"" + s3 + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>Arguments:</TD><TD ALIGN=LEFT><TEXTAREA name=_argnames rows=4 cols=80>" + s24 + "</TEXTAREA></TD></TR>" + "<TR><TD ALIGN=RIGHT>SOAP Action URI:<TD><input type=text name=_actionuri value=\"" + s11 + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>User-Agent:<TD><input type=text name=_URLUserAgent value=\"" + s20 + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>Method Namespace:<TD><input type=text name=_methodns value=\"" + s9 + "\" size=60><br>\n" + "<TR><TD ALIGN=RIGHT>User Name:<TD><input type=text name=_username value=\"" + s15 + "\" size=30><br>\n" + "<TR><TD ALIGN=RIGHT>Password:<TD>" + stringbuffer3.toString() + " size=30><br>\n" + stringbuffer4.toString() + "<TR><TD ALIGN=RIGHT>NTLM Domain:<TD><input type=text name=_ntlmDomain value=\"" + s16 + "\" size=40><br>\n" + "<TR><TD ALIGN=RIGHT>Proxy:<TD><input type=text name=_proxy value=\"" + s17 + "\" size=40><br>\n" + "<TR><TD ALIGN=RIGHT>Proxy User:<TD><input type=text name=_proxyuser value=\"" + s18 + "\" size=40><br>\n" + "<TR><TD ALIGN=RIGHT>Proxy Password:<TD>" + stringbuffer5.toString() + " size=30><br>\n" + stringbuffer6.toString() + "<TR><TD ALIGN=RIGHT><TD><input type=checkbox name=_useDotNetSoap size=50 " + s23 + ">Check if testing MS .NET web service<br>\n" + "</TABLE><p>\n");
            outputStream.println("<input type=hidden name=operation value=Tool>\n<input type=hidden name=page value=serviceWizard>\n<input type=hidden name=account value=\"" + request.getAccount() + "\">");
            if(request.getValue("AWRequest").equals("yes"))
            {
                outputStream.println("<input type=hidden name=AWRequest value=yes>");
            }
            outputStream.println("<input type=submit value=\"Web Service Request\" class=\"VerBl8\">\n</FORM>\n");
            if(s13.length() > 0 && s3.length() > 0 && s.length() > 0)
            {
                outputStream.println("Retrieving.... ");
                outputStream.flush();
                java.lang.StringBuffer stringbuffer7 = new StringBuffer();
                java.lang.StringBuffer stringbuffer8 = new StringBuffer();
                boolean flag2 = s19.length() > 0;
                java.lang.Object aobj[] = COM.dragonflow.StandardMonitor.WebServiceMonitor.rpcCall(s, s3, s4, s6, s8, s9, s11, s20, s13, stringbuffer7, stringbuffer8, s15, s21, s17, s18, s22, s16, flag2);
                int j = ((java.lang.Long)aobj[0]).intValue();
                long l2 = ((java.lang.Long)aobj[2]).longValue();
                java.lang.String s25 = COM.dragonflow.StandardMonitor.URLMonitor.lookupStatus(j);
                outputStream.print("<P>Result: <B>" + s25 + "</B><P>\n" + "Total time (msec): <B>" + l2 + "</B><BR>\n" + "<!--WEB SERVICE STATUS=" + j + " " + stringbuffer7.toString() + "-->\n");
                if(stringbuffer8 != null)
                {
                    outputStream.print("<HR><PRE>" + COM.dragonflow.Utils.TextUtils.escapeHTML(stringbuffer8.toString()) + "</PRE></HR>");
                }
            }
            if(!request.getValue("AWRequest").equals("yes"))
            {
                printFooter(outputStream);
            } else
            {
                outputStream.println("</BODY>");
            }
            return;
        }
        if(atomicmonitor == null)
        {
            atomicmonitor = COM.dragonflow.SiteView.AtomicMonitor.MonitorCreate(request.getValue("class"));
        }
        java.lang.String s1 = request.getPermission("_monitorType", (java.lang.String)atomicmonitor.getClassProperty("class"));
        if(s1.equals("optional"))
        {
            printErrorHtml("Operation not available to current user");
            return;
        }
        if(request.getValue("submit").equals(addMonitor))
        {
            postToMonitorPage();
            return;
        }
        boolean flag = false;
        if(request.getValue("_url").length() > 0 || request.getValue("_file").length() > 0)
        {
            flag = true;
        }
        if(flag && request.getValue("_methodname").length() <= 0)
        {
            java.lang.String s5 = request.getValue("_url").equals("http://") ? request.getValue("_file") : request.getValue("_url");
            if(s5.indexOf("http") < 0)
            {
                s5 = COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", request.getAccount()) + "/" + s5;
            }
            java.lang.StringBuffer stringbuffer1 = new StringBuffer();
            wsdlParser = new WSDLParser();
            wsdlParser.readWSDL(s5, stringbuffer1);
            if(stringbuffer1.length() > 0)
            {
                printErrorHtml(stringbuffer1.toString());
                return;
            }
            java.util.List list = wsdlParser.getOperationNames(stringbuffer1);
            if(stringbuffer1.length() > 0)
            {
                printErrorHtml(stringbuffer1.toString());
                return;
            }
            java.lang.String s10 = wsdlParser.getServiceEndpointURL(stringbuffer1);
            if(stringbuffer1.length() > 0)
            {
                printErrorHtml(stringbuffer1.toString());
                return;
            }
            printHeaders(stepHelp);
            outputStream.print("<TR><TD></TD><TD><b>Web Service URL:</b></TD></TR><BR>");
            outputStream.print("<TR><TD></TD><TD></TD><TD>" + COM.dragonflow.Utils.TextUtils.escapeHTML(s10) + "</TD>" + "</TR>\n");
            outputStream.println("<TABLE>");
            displayMethodList(list);
            outputStream.print("<input type=hidden name=_wsdlurl value=\"" + s5 + "\">\n" + "<input type=hidden name=_serverurl value=\"" + s10 + "\">\n");
            setHiddenInfo();
            outputStream.print("<BR>\n<BR>\n");
            outputStream.println("</TABLE>");
            outputStream.print("<BR>\n<BR>\n");
            outputStream.print("<TR><TD></TD><TD></TD><TD>");
            outputStream.print("<input type=submit name=\"submit\" value=\"" + getArgs + "\">&nbsp;&nbsp");
            outputStream.print("</TD></TR>");
            outputStream.print("<TR><TD></TD><TD></TD><TD>Choose <b>Get Arguments</b>  retrieve the arguments of the above method");
        } else
        if(request.getValue("_methodname").length() > 0)
        {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            if(wsdlParser == null)
            {
                wsdlParser = new WSDLParser();
                wsdlParser.readWSDL(request.getValue("_wsdlurl"), stringbuffer);
                if(stringbuffer.length() > 0)
                {
                    printErrorHtml(stringbuffer.toString());
                    return;
                }
            }
            java.lang.String s7 = request.getValue("_methodname");
            java.util.List list1 = wsdlParser.generateArgXMLforUI(s7, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                printErrorHtml(stringbuffer.toString());
                return;
            }
            java.lang.StringBuffer stringbuffer2 = new StringBuffer();
            java.lang.String s12 = wsdlParser.getOperationNamespace(s7, stringbuffer2, stringbuffer);
            if(stringbuffer.length() > 0)
            {
                printErrorHtml(stringbuffer.toString());
                return;
            }
            java.lang.String s14 = stringbuffer2.toString();
            printHeaders(stepHelp);
            outputStream.print("<TR><TD></TD><TD></TD><TD><b>Web Service URL:</b></TD></TR>");
            outputStream.print("<TR><DD>" + COM.dragonflow.Utils.TextUtils.escapeHTML(request.getValue("_serverurl")) + "</DD>" + "</TR><BR>\n<BR>\n<BR>\n");
            outputStream.print("<TR><TD></TD><TD></TD><TD><b>Web Service Method:</b></TD></TR>");
            outputStream.print("<TR><DD>" + COM.dragonflow.Utils.TextUtils.escapeHTML(request.getValue("_methodname")) + "</DD>" + "</TR><BR>\n<BR>\n");
            outputStream.print("<TR><TD></TD><TD></TD><TD><b>Web Service Arguments:</b></TD></TR><BR>\n<BR>\n");
            outputStream.println("<TABLE>");
            displayArgNames(list1);
            outputStream.print("<input type=hidden name=_wsdlurl value=\"" + request.getValue("_wsdlurl") + "\">\n" + "<input type=hidden name=_methodname value=\"" + request.getValue("_methodname") + "\">\n" + "<input type=hidden name=_serverurl value=\"" + request.getValue("_serverurl") + "\">\n" + "<input type=hidden name=_methodns value=\"" + s12 + "\">\n" + "<input type=hidden name=_actionuri value=\"" + s14 + "\">\n");
            setHiddenInfo();
            jgl.HashMap hashmap = new HashMap();
            boolean flag1 = false;
            jgl.Array array1 = COM.dragonflow.Properties.StringProperty.sortByOrder(atomicmonitor.getProperties());
            java.util.Enumeration enumeration1 = array1.elements();
            do
            {
                if(!enumeration1.hasMoreElements())
                {
                    break;
                }
                COM.dragonflow.Properties.StringProperty stringproperty1 = (COM.dragonflow.Properties.StringProperty)enumeration1.nextElement();
                if(!stringproperty1.isAdvanced && !stringproperty1.isVariableCountProperty() && stringproperty1.getName() != "_wsdlurl" && stringproperty1.getName() != "_methodname" && stringproperty1.getName() != "_argnames" && stringproperty1.getName() != "_serverurl" && stringproperty1.isEditable)
                {
                    printProperty(stringproperty1, outputStream, atomicmonitor, request, hashmap, flag1);
                }
            } while(true);
            if(request.getValue("group").length() > 0)
            {
                outputStream.println("</TABLE>");
                outputStream.print("<TR><TD></TD><TD></TD><TD>");
                outputStream.print("<input type=submit name=\"submit\" value=\"" + addMonitor + "\">&nbsp;&nbsp");
                outputStream.print("<TR><TD></TD><TD></TD><TD>Choose <b>" + addMonitor + "</b> to save the changes to  monitor");
                outputStream.println("<TABLE>");
            }
            outputStream.println("</TABLE>");
            outputStream.println("<P><HR><CENTER><B>Advanced Settings</B></CENTER><P>");
            outputStream.println("<TABLE>");
            enumeration1 = array1.elements();
            do
            {
                if(!enumeration1.hasMoreElements())
                {
                    break;
                }
                COM.dragonflow.Properties.StringProperty stringproperty2 = (COM.dragonflow.Properties.StringProperty)enumeration1.nextElement();
                if(stringproperty2.isAdvanced && stringproperty2.getName() != "_methodns" && stringproperty2.getName() != "_actionuri" && stringproperty2.isEditable)
                {
                    generateSubHeading(stringproperty2);
                    printProperty(stringproperty2, outputStream, atomicmonitor, request, hashmap, flag1);
                }
            } while(true);
            if(array2 != null)
            {
                printOrdering(atomicmonitor, array2);
            }
            printThresholds(atomicmonitor, hashmap);
            outputStream.println("</TABLE>");
        } else
        {
            int i = request.getPermissionAsInteger("_minimumFrequency");
            long l = atomicmonitor.getPropertyAsLong(COM.dragonflow.SiteView.AtomicMonitor.pFrequency);
            java.lang.Object obj = atomicmonitor.getClassProperty("defaultFrequency");
            if(obj instanceof java.lang.String)
            {
                long l1 = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)obj);
                if(l1 > 0L)
                {
                    l = l1;
                }
            }
            if(i > 0 && l < (long)i)
            {
                l = i;
            }
            atomicmonitor.setProperty(COM.dragonflow.SiteView.AtomicMonitor.pFrequency, l);
            request.setValue("_timeout", "60");
            printHeaders(startHelp);
            printUrlOption();
            setHiddenInfo();
            outputStream.println("</TABLE>");
            outputStream.println("<BR>\n<BR>\n");
            outputStream.println("<TABLE>");
            outputStream.print("<TR><TD></TD><TD></TD>");
            outputStream.print("<input type=submit name=\"submit\" value=\"" + getMethods + "\">&nbsp;&nbsp");
            outputStream.print("</TD></TR>");
            outputStream.print("<TR><TD></TD><TD></TD><TD>Choose <b>Get Methods</b> to retrieve the methods of the Service");
            outputStream.println("</TABLE>");
        }
        if(!request.getValue("AWRequest").equals("yes"))
        {
            printFooter(outputStream);
        } else
        {
            outputStream.println("</BODY>");
        }
    }

    private void generateSubHeading(COM.dragonflow.Properties.StringProperty stringproperty)
    {
        if(stringproperty.getName().equals("_useDotNetSoap"))
        {
            outputStream.println("</TABLE><P><B>SOAP Options</B><P><TABLE>");
        } else
        if(stringproperty.getName().equals("_ntlmDomain"))
        {
            outputStream.println("</TABLE><P><B>Authentication</B><P><TABLE>");
        } else
        if(stringproperty.getName().equals("_proxy"))
        {
            outputStream.println("</TABLE><P><B>Proxy Options</B><P><TABLE>");
        }
    }

    private void displayArgNames(java.util.List list)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String s = null;
        if(list.size() > 0)
        {
            s = "This is the input argument list for the chosen web service method<P>";
        } else
        {
            s = "This method takes no arguments - leave the above text field blank<P>";
        }
        java.util.Iterator iterator = list.iterator();
        do
        {
            if(!iterator.hasNext())
            {
                break;
            }
            java.lang.String s1 = (java.lang.String)iterator.next();
            stringbuffer.append(s1);
            if(iterator.hasNext())
            {
                stringbuffer.append(COM.dragonflow.StandardMonitor.URLMonitor.CRLF);
            }
        } while(true);
        outputStream.print("<TR><TD></TD><TD ALIGN=RIGHT><TEXTAREA name=_argnames rows=4 cols=80>" + stringbuffer.toString() + "</TEXTAREA></TD></TR>" + "<TR><TD></TD><TD><small>" + s + "</small><p></TD></TR>");
    }

    private void displayMethodList(java.util.List list)
    {
        java.lang.String s = "Web Service Methods:";
        outputStream.print("<TR><TD><b>" + s + "</b></TD></TR>" + "<TR><TD><select name=_methodname>");
        java.lang.String s1;
        for(java.util.Iterator iterator = list.iterator(); iterator.hasNext(); outputStream.print("<option value=\"" + s1 + "\">" + s1 + "</option>"))
        {
            s1 = (java.lang.String)iterator.next();
        }

        outputStream.print("</select></TD></TR>\n<TD ALIGN=RIGHT><small>This is a list of available methods for this Web Service</small></TD>");
    }

    void postToMonitorPage()
    {
        request.requestMethod = "POST";
        request.setValue("page", "monitor");
        if(!request.getValue("operation").equals("Add"))
        {
            request.setValue("operation", "Edit");
        }
        try
        {
            outputStream.println("Content-type: text/html\n\n<html>");
            java.lang.Class class1 = java.lang.Class.forName("COM.dragonflow.Page.monitorPage");
            COM.dragonflow.Page.CGI cgi = (COM.dragonflow.Page.CGI)class1.newInstance();
            cgi.request = request;
            cgi.outputStream = outputStream;
            cgi.printBody();
            outputStream.println("</HTML>");
        }
        catch(java.lang.ClassNotFoundException classnotfoundexception)
        {
            java.lang.String s = "";
            if(request != null)
            {
                s = request.getURL();
            }
            COM.dragonflow.HTTP.HTTPRequest.printErrorMessage(request, 404, s, classnotfoundexception, outputStream);
        }
        catch(java.lang.Exception exception)
        {
            java.lang.String s1 = "";
            if(request != null)
            {
                s1 = request.getURL();
            }
            COM.dragonflow.HTTP.HTTPRequest.printErrorMessage(request, 999, s1, exception, outputStream);
        }
    }

    void printUrlOption()
    {
        outputStream.print("<TR><TD></TD><TD>Start by entering the URL of the Web Service Descriptor Language for the Service\n</TD></TR><TR><TD></TD><TD>or selecting the correct WSDL file\n\n\n</TD></TR>");
        outputStream.println("<H3></H3><H3></H3>");
        outputStream.println("<TABLE>");
        outputStream.print("<TR><TD ALIGN=RIGHT>URL : </TD><TD><input type=text name=_url value=\"");
        java.lang.String s = "Example: http://demo.siteview.com";
        outputStream.print(urlPrefix + "\" size=80></TD></TR>" + "<TR><TD></TD><TD><small>" + s + "</small></TD></TR>");
        jgl.Array array = new Array();
        java.io.File file = new File(COM.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.wsdl", request.getAccount()));
        if(!file.exists())
        {
            return;
        }
        java.lang.String as[] = file.list();
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = as[i];
            if(s1.endsWith(".wsdl"))
            {
                array.add(s1);
            }
        }

        java.util.Enumeration enumeration = array.elements();
        outputStream.print("<TR><TD></TD></TR>");
        outputStream.print("<TR><TD ALIGN=RIGHT>File :</TD><TD><select name=_file>");
        if(enumeration.hasMoreElements())
        {
            java.lang.String s2;
            for(; enumeration.hasMoreElements(); outputStream.print("<option value=\"" + s2 + "\">" + s2 + "</option>"))
            {
                s2 = (java.lang.String)enumeration.nextElement();
            }

        }
        s = "";
        outputStream.print("</select></TD></TR>\n<TR><TD></TD><TD></TD><TD><small>" + s + "</small></TD></TR>");
    }

    public static void main(java.lang.String args[])
    {
        COM.dragonflow.Page.serviceWizardPage servicewizardpage = new serviceWizardPage();
        if(args.length > 0)
        {
            servicewizardpage.args = args;
        }
        servicewizardpage.handleRequest();
    }

    private static void status(java.lang.String s)
    {
        if(debug)
        {
            java.lang.System.out.println(s);
        }
    }

    static 
    {
        java.lang.String s = java.lang.System.getProperty("serviceWizardPage.debug", "false");
        if(s.equalsIgnoreCase("true"))
        {
            debug = true;
        }
    }
}
