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

// Referenced classes of package com.dragonflow.Page:
// CGI

public class restartPage extends com.dragonflow.Page.CGI {
    class ExitSiteView extends Thread {

        public void run() {
            try {
                Thread.currentThread();
                Thread.sleep(1000L);
            } catch (InterruptedException interruptedexception) {
            }
            System.exit(0);
        }

        ExitSiteView() {
            super();
        }
    }

    public restartPage() {
    }

    public void printBody() throws Exception {
        com.dragonflow.HTTP.HTTPRequestThread.licenseExpired = false;
        com.dragonflow.Page.CGI.printRefreshHeader(outputStream, "",
                "/SiteView/htdocs/SiteView.html", 0);
        outputStream.flush();
        (new ExitSiteView()).start();
    }
}
