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

import java.io.File;
import java.io.StringWriter;

import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class exchangeReportPage extends com.dragonflow.Page.CGI {

    public exchangeReportPage() {
    }

    public void printBody() throws Exception {
        if (!request.actionAllowed("_tools")) {
            throw new HTTPRequestException(557);
        } else {
            String s = request.getValue("file");
            String s1 = com.dragonflow.SiteView.Platform.getRoot()
                    + java.io.File.separator + "dat" + java.io.File.separator
                    + "monitors" + java.io.File.separator + "exchangetool.xsl";
            javax.xml.transform.Transformer transformer = null;
            javax.xml.transform.TransformerFactory transformerfactory = javax.xml.transform.TransformerFactory
                    .newInstance();
            transformer = transformerfactory.newTransformer(new StreamSource(
                    new File(s1)));
            java.io.StringWriter stringwriter = new StringWriter();
            transformer.transform(new StreamSource(new File(s)),
                    new StreamResult(stringwriter));
            outputStream.println(stringwriter.toString());
            outputStream.println("<br /><br />");
            printFooter(outputStream);
            return;
        }
    }
}
