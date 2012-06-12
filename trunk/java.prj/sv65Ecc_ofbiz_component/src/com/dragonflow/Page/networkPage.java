/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class networkPage extends com.dragonflow.Page.CGI
{

    public networkPage()
    {
    }

    private boolean printOutput(Process process)
        throws java.io.IOException
    {
        boolean flag = false;
        boolean flag1 = false;
        java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
        String s;
        while((s = bufferedreader.readLine()) != null) 
        {
            if(s.length() > 0)
            {
                flag1 = true;
                outputStream.println(com.dragonflow.Utils.TextUtils.escapeHTML(s));
                outputStream.flush();
                flag = false;
            } else
            if(flag)
            {
                flag1 = true;
                outputStream.println();
                flag = false;
            } else
            {
                flag = true;
            }
        }
        bufferedreader.close();
        return flag1;
    }

    public void printBody()
        throws Exception
    {
        if(!request.actionAllowed("_tools"))
        {
            throw new HTTPRequestException(557);
        }
        printBodyHeader("Network");
        printButtonBar("Network.htm", "");
        outputStream.print("<P><CENTER><H2>Network</H2></CENTER><P><P>" + getPagePOST("network", "") + "Network is a tool that uses the <I>netstat</I> command to " + "determine your network interface statistics and number " + "of active connections.&nbsp; " + "When there is a problem, network can tell you if your " + "interface is saturated or in error.&nbsp; " + "Network also shows the number of connections, which can " + "keep climbing in a runaway situation.&nbsp; " + "This form will run netstat first to show the statistics " + "and again to show the active connections." + "<P>" + "<INPUT TYPE=SUBMIT VALUE=\"Run Network\">" + "</FORM>");
        if(!isPortalServerRequest())
        {
            printContentStartComment();
            outputStream.print("<PRE><HR>");
            String s = com.dragonflow.SiteView.Platform.netEthernetStatsCommand();
            String s1 = com.dragonflow.SiteView.Platform.netConnectionStatsCommand();
            boolean flag = false;
            try
            {
                Process process = com.dragonflow.Utils.CommandLine.execSync(s);
                flag = printOutput(process);
            }
            catch(java.io.IOException ioexception)
            {
                if(!flag)
                {
                    outputStream.println("Could not perform network command: " + s);
                }
            }
            outputStream.print("<HR>");
            try
            {
                Process process1 = com.dragonflow.Utils.CommandLine.execSync(s1);
                flag = printOutput(process1);
            }
            catch(java.io.IOException ioexception1)
            {
                if(!flag)
                {
                    outputStream.println("Could not perform network command: " + s1);
                }
            }
            outputStream.println("</PRE>");
            printContentEndComment();
        } else
        {
            com.dragonflow.SiteView.PortalSiteView portalsiteview = (com.dragonflow.SiteView.PortalSiteView)getSiteView();
            if(portalsiteview != null)
            {
                String s2 = portalsiteview.getURLContentsFromRemoteSiteView(request, "_centrascopeToolMatch");
                outputStream.println(s2);
            }
        }
        printFooter(outputStream);
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.networkPage networkpage = new networkPage();
        if(args.length > 0)
        {
            networkpage.args = args;
        }
        networkpage.handleRequest();
    }
}
