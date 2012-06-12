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

import com.dragonflow.SiteView.PQVPrintMainHTML;

// Referenced classes of package com.dragonflow.Page:
// portalChooserPage

public class portalMainPage extends com.dragonflow.Page.portalChooserPage
{

    public static boolean debug = true;

    public portalMainPage()
    {
        bodyHeader = "CentraScope Manager";
        helpFileName = "NoDoc.htm";
        serversSelectable = true;
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.portalMainPage portalmainpage = new portalMainPage();
        if(args.length > 0)
        {
            portalmainpage.args = args;
        }
        portalmainpage.handleRequest();
    }

    public void printBody()
        throws Exception
    {
        request.unsetValue(com.dragonflow.HTTP.HTTPRequest.PORTAL_SERVER_NAME);
        super.printBody();
    }

    protected com.dragonflow.SiteView.PortalQueryVisitor createPQVToPrint(jgl.HashMap hashmap, jgl.HashMap hashmap1)
    {
        return new PQVPrintMainHTML(this, hashmap, hashmap1);
    }

    protected void printButtons(java.io.PrintWriter printwriter)
    {
    }

    boolean defaultLoadState()
    {
        return true;
    }

}
