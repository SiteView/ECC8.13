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

import java.util.Enumeration;

import com.siteview.svecc.service.Config;


// Referenced classes of package com.dragonflow.Page:
// CGI

public class haLicensePage extends com.dragonflow.Page.CGI
{

    public haLicensePage()
    {
    }

    public void printBody()
    {
        if(request.isPost())
        {
            //jgl.HashMap hashmap = getMasterConfig();
            jgl.HashMap hashmap = new jgl.HashMap();
            String s1 = request.getValue("halicense");
            com.dragonflow.Utils.LUtils.setLicenseKey(s1,hashmap,hashmap);
            try
            {
                //saveMasterConfig(hashmap);
            	Config.configPut(hashmap);
            }
            catch(Exception exception) { }
            String s2 = "/SiteView/cgi/go.exe/SiteView?page=mirrorPrefs&account=administrator&operation=initSetup";
            printRefreshPage(s2, 0);
        } else
        {
            String s = "SiteView Fail-Over";
            printBodyHeader("Starting " + s + " for the First Time");
            outputStream.println("<CENTER><H2>Starting " + s + " the First Time</H2></CENTER><P>" + "<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>" + "<p>Please start by entering your " + s + " license key in the field below " + "<CENTER>" + "<p>" + "<input type=txt name=halicense value=\"\">\n\n" + "<input type=hidden name=page value=\"haLicense\">" + "<input type=hidden name=account value=\"administrator\">\n" + "<input type=submit value=\"Start\"> using " + s + "</CENTER>");
            outputStream.println("</FORM>");
            printFooter(outputStream);
        }
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        (new haLicensePage()).handleRequest();
    }
}
