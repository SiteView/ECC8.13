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
import java.util.Vector;

import COM.dragonflow.Utils.Snmp.SNMPSession;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class browsableSNMPToolPage extends COM.dragonflow.Page.CGI
{

    private java.lang.String help;
    private int versionNum;
    private int nRetries;
    private int timeout;
    private java.lang.String mibFileVal;
    private java.lang.String hostVal;
    private java.lang.String versionVal;
    private java.lang.String communityVal;
    private java.lang.String v3AuthTypeVal;
    private java.lang.String v3UserVal;
    private java.lang.String v3AuthPasswordVal;
    private java.lang.String v3PrivPassphraseVal;
    private java.lang.String v3ContextEngineIDVal;
    private java.lang.String v3ContextNameVal;
    private java.lang.String timeoutVal;
    private java.lang.String retriesVal;
    private java.lang.String portVal;
    private static final java.lang.String versionsNames[] = {
        "V1", "V2", "V3"
    };
    private static final java.lang.String versionsValues[] = {
        "1", "2", "3"
    };
    private static final java.lang.String authTypeNames[] = {
        "MD5", "SHA", "None"
    };
    private static final java.lang.String authTypeValues[] = {
        "MD5", "SHA", "NoAuthentication"
    };
    private static final java.lang.String isTreeWindow = "isTreeWindow";
    private static final java.lang.String treeWindowName = "BrowsableSNMPTool";
    private static final java.lang.String treeWindowOptions = "toolbar=no,width=700,height=600,directories=no,status=no,scrollbars=yes,resizable=1,menubar=no";
    private java.util.Vector mibFileNames;
    private java.util.Vector mibFileDisplayNames;

    public browsableSNMPToolPage()
    {
        help = "browsableSNMPTool.htm";
        mibFileNames = new Vector();
        mibFileDisplayNames = new Vector();
        try
        {
            COM.dragonflow.Utils.Snmp.BrowsableMIB browsablemib = COM.dragonflow.Utils.Snmp.BrowsableMIB.getInstance();
            java.lang.String as[] = browsablemib.getCompiledMIBs();
            mibFileNames.add(as[0]);
            mibFileDisplayNames.add(as[0]);
            for(int i = 1; i < as.length; i++)
            {
                mibFileNames.add(as[i]);
                mibFileDisplayNames.add((new File(as[i])).getName());
            }

        }
        catch(java.lang.Exception exception)
        {
            COM.dragonflow.Log.LogManager.log("Error", "BrowsableSNMPMonitor could not get BrowsableMIB instance: " + exception.getMessage());
            mibFileNames.add("No MIBs Available");
            mibFileDisplayNames.add("No MIBs Available");
        }
    }

    public void printBody()
    {
        hostVal = request.getValue("_server");
        mibFileVal = request.getValue("_mibfile");
        communityVal = request.getValue("_community");
        versionVal = request.getValue("_snmpversion");
        v3UserVal = request.getValue("_snmpv3username");
        v3AuthTypeVal = request.getValue("_snmpv3authtype");
        v3AuthPasswordVal = request.getValue("_snmpv3authpassword");
        v3PrivPassphraseVal = request.getValue("_snmpv3privpassword");
        v3ContextEngineIDVal = request.getValue("_contextEngineID");
        v3ContextNameVal = request.getValue("_contextName");
        timeoutVal = request.getValue("_timeout");
        retriesVal = request.getValue("_retries");
        portVal = request.getValue("_port");
        if(versionVal.length() > 0)
        {
            try
            {
                versionNum = java.lang.Integer.parseInt(versionVal);
            }
            catch(java.lang.NumberFormatException numberformatexception)
            {
                versionNum = 1;
                versionVal = "1";
            }
        }
        try
        {
            timeout = java.lang.Integer.parseInt(timeoutVal);
            nRetries = java.lang.Integer.parseInt(retriesVal);
        }
        catch(java.lang.NumberFormatException numberformatexception1)
        {
            timeout = 2;
            nRetries = 2;
        }
        timeout *= 100;
        if(nRetries > 0)
        {
            timeout /= nRetries + 1;
            if(timeout == 0)
            {
                timeout = 200;
            }
        }
        if(request.getValue("isTreeWindow").length() > 0)
        {
            try
            {
                java.lang.StringBuffer stringbuffer = new StringBuffer();
                java.lang.String s1;
                try
                {
                    int i = java.lang.Integer.parseInt(portVal);
                    s1 = hostVal + ":" + i;
                }
                catch(java.lang.NumberFormatException numberformatexception2)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "Invalid port number in SNMP by MIB Tool: " + portVal + ", using default of 161.");
                    s1 = hostVal + ":" + 161;
                }
                COM.dragonflow.Utils.Snmp.SNMPSession snmpsession;
                if(versionNum == 1 || versionNum == 2)
                {
                    snmpsession = new SNMPSession(s1, versionNum, communityVal);
                } else
                {
                    snmpsession = new SNMPSession(s1, v3AuthTypeVal, v3UserVal, v3AuthPasswordVal, v3PrivPassphraseVal, v3ContextEngineIDVal, v3ContextNameVal);
                }
                snmpsession.setTimeout(timeout);
                snmpsession.setRetries(nRetries);
                COM.dragonflow.Utils.Snmp.BrowsableMIB browsablemib = COM.dragonflow.Utils.Snmp.BrowsableMIB.getInstance();
                java.lang.String s = browsablemib.getXML(snmpsession, mibFileVal, stringbuffer);
                if(stringbuffer.length() > 0)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "Error while creating BrowsableMIB: " + stringbuffer.toString());
                    printErrorClose("There was an error while creating a browsable view of " + mibFileVal + ": <BR><B>" + stringbuffer.toString() + "</B>");
                } else
                {
                    outputStream.println("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>");
                    outputStream.println(s);
                }
            }
            catch(COM.dragonflow.Utils.Snmp.SNMPSessionException snmpsessionexception)
            {
                COM.dragonflow.Log.LogManager.log("Error", "Error while creating SNMPSession: " + snmpsessionexception.getMessage());
                printErrorClose("There was an error while attempting to connect to host " + hostVal + ": <BR><B>" + snmpsessionexception.getMessage() + "</B>");
            }
            catch(java.io.IOException ioexception)
            {
                COM.dragonflow.Log.LogManager.log("Error", "Error while creating BrowsableMIB: " + ioexception.getMessage());
                printErrorClose("There was an error while creating a browsable view of " + mibFileVal + ": <BR><B>" + ioexception.getMessage() + "</B>");
            }
            catch(COM.dragonflow.Utils.Snmp.BrowsableMIBException browsablemibexception)
            {
                COM.dragonflow.Log.LogManager.log("Error", "Error while creating BrowsableMIB: " + browsablemibexception.getMessage());
                printErrorClose("There was an error while creating a browsable view of " + mibFileVal + ":  <BR><B>" + browsablemibexception.getMessage() + "</B>");
            }
            return;
        } else
        {
            printButtonBar(help, "");
            printBodyHeader("SNMP Browser Tool Page");
            printJavaScript();
            outputStream.print("<P><CENTER><H2>SNMP Browser Tool</H2></CENTER><P>The SNMP Browser Tool will walk the MIB of the specified server and display the OIDs and their values in a tree.");
            outputStream.println("<FORM ACTION=/SiteView/cgi/go.exe/SiteView TARGET=\"BrowsableSNMPTool\" method=GET>");
            outputStream.println("<INPUT TYPE=hidden NAME=isTreeWindow VALUE=\"true\">\n");
            printConnectionProperties();
            printButtons();
            outputStream.println("</FORM>");
            printFooter(outputStream);
            outputStream.flush();
            return;
        }
    }

    private void printErrorClose(java.lang.String s)
    {
        COM.dragonflow.Page.browsableSNMPToolPage.printHeadTag(outputStream, "Error", "");
        printJavaScript();
        outputStream.println("<H2 ALIGN=center>Error</H2>");
        outputStream.println(s + "<BR> Please verify the connection properties and <A HREF=\"javascript:TryAgain()\">try again</A>.<BR>");
        printFooter(outputStream);
    }

    private void printJavaScript()
    {
        outputStream.println("<SCRIPT LANGUAGE = \"JavaScript\">\n");
        outputStream.println("<!--\nfunction OpenTreeWindow() {\ntreeWin=window.open(\"\", \"BrowsableSNMPTool\", \"toolbar=no,width=700,height=600,directories=no,status=no,scrollbars=yes,resizable=1,menubar=no\");\ntreeWin.focus();\n}\nfunction TryAgain() {\nwindow.opener.focus();\nself.close();\n}//-->\n");
        outputStream.println("</SCRIPT>\n");
    }

    private void printConnectionProperties()
    {
        outputStream.println(getPagePOST("browsableSNMPTool", ""));
        outputStream.println("<TABLE BORDER=0>");
        tableRow("Host or IP Address:", "text", "_server", hostVal, 32);
        tableRow("Port:", "text", "_port", portVal, 32);
        tableRowDropDown("MIB:", "_mibfile", mibFileDisplayNames, mibFileNames, 1);
        tableRowDropDown("Version:", "_snmpversion", versionsNames, versionsValues, 1);
        tableRow("<B>V1/V2</B> Community:", "text", "_community", communityVal, 32);
        tableRowDropDown("<B>V3</B> Authentication Type:", "_snmpv3authtype", authTypeNames, authTypeValues, 1);
        tableRow("<B>V3</B> Username:", "text", "_snmpv3username", v3UserVal, 32);
        tableRow("<B>V3</B> Authenication Password:", "password", "_snmpv3authpassword", v3AuthPasswordVal, 32);
        tableRow("<B>V3</B> Privacy Password:", "password", "_snmpv3privpassword", v3PrivPassphraseVal, 32);
        tableRow("<B>V3</B> Context Engine ID:", "text", "_contextEngineID", v3ContextEngineIDVal, 32);
        tableRow("<B>V3</B> Context Name:", "text", "_contextName", v3ContextNameVal, 32);
        outputStream.println("</TABLE>");
    }

    private void printButtons()
    {
        outputStream.println("<p>\n<INPUT TYPE=\"submit\" onClick=\"OpenTreeWindow()\" VALUE=\"Browse\">\n");
    }

    private void tableRow(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, int i)
    {
        outputStream.println("<TR><TD ALIGN=RIGHT>" + s + "</TD><TD><INPUT TYPE=\"" + s1 + "\" NAME=\"" + s2 + "\" VALUE=\"" + s3 + "\" SIZE=\"" + i + "\"></TD></TR>\n");
    }

    private void tableRowDropDown(java.lang.String s, java.lang.String s1, java.lang.String as[], java.lang.String as1[], int i)
    {
        outputStream.println("<TR><TD ALIGN=RIGHT>" + s + "</TD><TD><SELECT NAME=\"" + s1 + "\" SIZE=\"" + i + "\"/>");
        for(int j = 0; j < as.length && j < as1.length; j++)
        {
            if(j == 0)
            {
                outputStream.println("<OPTION  SELECTED=\"selected\" VALUE=\"" + as1[j] + "\">" + as[j] + "</OPTION>\n");
            } else
            {
                outputStream.println("<OPTION  VALUE=\"" + as1[j] + "\">" + as[j] + "</OPTION>\n");
            }
        }

        outputStream.println("</SELECT></TD></TR>\n");
    }

    private void tableRowDropDown(java.lang.String s, java.lang.String s1, java.util.Vector vector, java.util.Vector vector1, int i)
    {
        java.lang.String as[] = new java.lang.String[vector.size()];
        java.lang.String as1[] = new java.lang.String[vector1.size()];
        vector.toArray(as);
        vector1.toArray(as1);
        tableRowDropDown(s, s1, as, as1, i);
    }

    public void printCGIFooter()
    {
        if(request.getValue("isTreeWindow").length() == 0)
        {
            super.printCGIFooter();
        }
    }

    public void printCGIHeader()
    {
        if(request.getValue("isTreeWindow").length() == 0)
        {
            super.printCGIHeader();
        }
    }

}
