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

import COM.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class DNSPage extends COM.dragonflow.Page.CGI
{

    public DNSPage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_monitorTools"))
        {
            throw new HTTPRequestException(557);
        }
        java.lang.String s = request.getValue("host");
        java.lang.String s1 = request.getValue("misc");
        if(s.length() <= 0);
        printBodyHeader("DNS Lookup");
        java.lang.String s2 = new String("");
        if(!request.getValue("AWRequest").equals("yes"))
        {
            printButtonBar("Dns.htm", "");
            outputStream.println("<center><a href=" + getPageLink("trace", "") + "&host=" + s + "&group=" + request.getValue("group") + ">TraceRoute</a></center><P>");
            s2 = COM.dragonflow.SiteView.Platform.exampleDomain;
        } else
        {
            outputStream.println("<center><a href=" + getPageLink("trace", "") + "&host=" + s + "&AWRequest=yes" + ">TraceRoute</a>" + " | " + "<a href=/SiteView/cgi/go.exe/SiteView?page=monitor&operation=Tools&account=" + request.getAccount() + "&AWRequest=yes>Diagnostic Tools</a>" + "</center><P>");
            s2 = "merc-int.com";
        }
        outputStream.println("<CENTER><H2>DNS lookup</H2></CENTER><P>\n<p>\n" + getPagePOST("DNS", "") + "Domain Name Servers are used to translates domain names into IP addresses.  For example,\n" + "a DNS server converts the name www." + s2 + " into an IP address.\n" + "<p>\n" + "This form will send a request to translate a domain name.  \n" + "Enter the IP address of a DNS server and a domain name.\n" + "If left blank then the default DNS server will be used.\n" + "<p>\n" + "Enter \"LOCAL\" in the address field to check the local DNS server" + "<p>\n" + "<TABLE BORDER=\"0\">\n" + "<TR><TD ALIGN=RIGHT>DNS address:</TD><TD><input type=text name=host value=\"" + s + "\" size=60></TD></TR>\n" + "<TR><TD ALIGN=RIGHT>Host Name:</TD><TD><input type=text name=misc value=\"" + s1 + "\" size=60></TD></TR>\n" + "</TABLE>\n" + "<p>\n" + "<input type=submit value=\"DNS Lookup\" class=\"VerBl8\">\n" + "</FORM>\n");
        if(s.length() > 0)
        {
            if(!isPortalServerRequest())
            {
                printContentStartComment();
                outputStream.println("<PRE>");
                long l = java.lang.System.currentTimeMillis();
                java.lang.String s4 = "";
                if(s.equals("LOCAL"))
                {
                    s4 = COM.dragonflow.SiteView.Platform.nslookupCommand() + " " + s1;
                } else
                {
                    s4 = COM.dragonflow.SiteView.Platform.nslookupCommand() + " " + s1 + " " + s;
                }
                boolean flag = false;
                try
                {
                    java.lang.Process process = COM.dragonflow.Utils.CommandLine.execSync(s4);
                    boolean flag1 = false;
                    java.io.BufferedReader bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getErrorStream());
                    java.lang.String s5;
                    while((s5 = bufferedreader.readLine()) != null) 
                    {
                        if(s5.length() > 0)
                        {
                            flag = true;
                            outputStream.println(s5);
                            flag1 = false;
                        } else
                        if(flag1)
                        {
                            flag = true;
                            outputStream.println();
                            flag1 = false;
                        } else
                        {
                            flag1 = true;
                        }
                    }
                    bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
                    while((s5 = bufferedreader.readLine()) != null) 
                    {
                        if(s5.length() > 0)
                        {
                            flag = true;
                            outputStream.println(s5);
                            flag1 = false;
                        } else
                        if(flag1)
                        {
                            flag = true;
                            outputStream.println();
                            flag1 = false;
                        } else
                        {
                            flag1 = true;
                        }
                    }
                    bufferedreader.close();
                }
                catch(java.io.IOException ioexception)
                {
                    if(!flag)
                    {
                        outputStream.println("Could not perform nslookup command: " + s4);
                    }
                }
                long l1 = java.lang.System.currentTimeMillis() - l;
                java.lang.String s6 = COM.dragonflow.Utils.TextUtils.floatToString((float)l1 / 1000F, 2) + " seconds";
                outputStream.print("\nTotal time: " + s6 + "\n" + "</PRE>\n");
                outputStream.println("</PRE>");
                printContentEndComment();
            } else
            {
                COM.dragonflow.SiteView.PortalSiteView portalsiteview = (COM.dragonflow.SiteView.PortalSiteView)getSiteView();
                if(portalsiteview != null)
                {
                    java.lang.String s3 = portalsiteview.getURLContentsFromRemoteSiteView(request, "_centrascopeToolMatch");
                    outputStream.println(s3);
                }
            }
        }
        if(!request.getValue("AWRequest").equals("yes"))
        {
            printFooter(outputStream);
        } else
        {
            outputStream.println("</BODY>");
        }
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        COM.dragonflow.Page.DNSPage dnspage = new DNSPage();
        if(args.length > 0)
        {
            dnspage.args = args;
        }
        dnspage.handleRequest();
    }
}
