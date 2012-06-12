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

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.Utils.SiteViewXMLQuery;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class xmlPage extends com.dragonflow.Page.CGI
{

    static jgl.HashMap excludeVariableMap;

    public xmlPage()
    {
    }

    public static jgl.HashMap buildQueryMap(com.dragonflow.HTTP.HTTPRequest httprequest)
        throws Exception
    {
        Object obj = null;
        String s = httprequest.getValue("query");
        jgl.Array array = null;
        if(s.length() == 0)
        {
            obj = new HashMapOrdered(true);
            array = com.dragonflow.Page.xmlPage.getAllowedGroupIDsForAccount(httprequest);
        } else
        {
            String s1 = com.dragonflow.SiteView.Platform.getUsedDirectoryPath("templates.view", httprequest.getAccount()) + java.io.File.separator + s;
            jgl.Array array1 = com.dragonflow.Properties.FrameFile.readFromFile(s1);
            if(array1.size() > 0)
            {
                obj = (jgl.HashMap)array1.at(0);
            }
            array = new Array();
            jgl.Array array2 = com.dragonflow.Page.xmlPage.getGroupFilterForAccount(httprequest);
            java.util.Enumeration enumeration2 = ((jgl.HashMap) (obj)).values("group");
            do
            {
                if(!enumeration2.hasMoreElements())
                {
                    break;
                }
                String s3 = (String)enumeration2.nextElement();
                if(com.dragonflow.Page.xmlPage.allowedByGroupFilter(s3, array2))
                {
                    array.add(enumeration2.nextElement());
                }
            } while(true);
        }
        for(int i = 0; i < array.size(); i++)
        {
            ((jgl.HashMap) (obj)).add("group", array.at(i));
        }

        java.util.Enumeration enumeration = httprequest.getVariables();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            String s2 = (String)enumeration.nextElement();
            if(excludeVariableMap.get(s2) == null)
            {
                if(((jgl.HashMap) (obj)).get(s2) != null)
                {
                    ((jgl.HashMap) (obj)).remove(s2);
                }
                java.util.Enumeration enumeration1 = httprequest.getValues(s2);
                while(enumeration1.hasMoreElements()) 
                {
                    ((jgl.HashMap) (obj)).add(s2, enumeration1.nextElement());
                }
            }
        } while(true);
        return ((jgl.HashMap) (obj));
    }

    public void printBody()
        throws Exception
    {
        String s = request.getValue("license");
        if(s.length() == 0)
        {
            s = com.dragonflow.Utils.LUtils.getLicenseKey();
        }
        if(!com.dragonflow.Utils.LUtils.isCentraScopeLicense(s))
        {
            outputStream.println("<siteview>\n<error>The XML interface is a feature that requires a CentraScope subscription.</error>\n</siteview>");
            return;
        } else
        {
            jgl.HashMap hashmap = com.dragonflow.Page.xmlPage.buildQueryMap(request);
            com.dragonflow.Utils.SiteViewXMLQuery siteviewxmlquery = new SiteViewXMLQuery(hashmap, outputStream, request);
            siteviewxmlquery.printXML();
            return;
        }
    }

    public void printCGIHeader()
    {
        com.dragonflow.HTTP.HTTPRequest _tmp = request;
        com.dragonflow.HTTP.HTTPRequest.printHeader(outputStream, 200, "OK", "text/xml");
    }

    public void printCGIFooter()
    {
        outputStream.flush();
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.xmlPage xmlpage = new xmlPage();
        if(args.length > 0)
        {
            xmlpage.args = args;
        }
        xmlpage.handleRequest();
    }

    static 
    {
        excludeVariableMap = new HashMap();
        excludeVariableMap.put("query", "true");
        excludeVariableMap.put("page", "true");
        excludeVariableMap.put("xsl", "true");
        excludeVariableMap.put("account", "true");
        excludeVariableMap.put("license", "true");
    }
}
