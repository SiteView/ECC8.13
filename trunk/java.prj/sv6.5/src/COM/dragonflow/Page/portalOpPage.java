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

import COM.dragonflow.SiteView.PortalSync;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class portalOpPage extends COM.dragonflow.Page.CGI
{

    public portalOpPage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        if(s.equals("Sync"))
        {
            doSync();
        } else
        {
            printError("The link was incorrect", "unknown operation", "/SiteView/" + request.getAccountDirectory() + "/SiteView.html");
        }
    }

    public void doSync()
    {
        outputStream.println("<PRE>");
        COM.dragonflow.SiteView.PortalSync portalsync = new PortalSync(outputStream);
        portalsync.sync();
        java.lang.String s = request.getValue("rview");
        outputStream.println("</PRE>");
        outputStream.println("<P><A HREF=/SiteView/cgi/go.exe/SiteView?page=portal&view=" + s + "&account=" + request.getAccount() + ">\n" + "Return to Portal</A>");
    }

    public static void main(java.lang.String args[])
    {
        (new portalOpPage()).handleRequest();
    }
}
