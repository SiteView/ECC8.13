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
import com.dragonflow.SiteView.PQVPrintChooserHTML;
import com.dragonflow.SiteView.PortalFilter;
import com.dragonflow.SiteView.PortalQuery;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class portalChooserPage extends com.dragonflow.Page.CGI
{

    public static boolean debug = false;
    private static String OPEN_VARIABLE = "open";
    private static String CLOSE_VARIABLE = "close";
    private static String NEXT_PAGE_VARIABLE = "nextPage";
    private static String CUSTOM_QUERY_STRING = "Custom";
    private static String NO_QUERY_STRING = "None";
    private static String NO_QUERY_VALUE = "";
    protected String bodyHeader;
    protected String helpFileName;
    protected boolean serversSelectable;
    private static String STRIP_STRING = "&item";

    public static String getQueryString(com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        return com.dragonflow.Page.portalChooserPage.getQueryString(httprequest.getValues("item"));
    }

    public static void printQueryChooseList(java.io.PrintWriter printwriter, com.dragonflow.HTTP.HTTPRequest httprequest, String s, String s1)
    {
        com.dragonflow.Page.portalChooserPage.printQueryChooser(printwriter, httprequest, s, s1, "", true);
    }

    public static void printQueryChooseList(java.io.PrintWriter printwriter, com.dragonflow.HTTP.HTTPRequest httprequest, String s, String s1, String s2)
    {
        com.dragonflow.Page.portalChooserPage.printQueryChooser(printwriter, httprequest, s, s1, s2, true);
    }

    public static void printQueryDefine(java.io.PrintWriter printwriter, com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        com.dragonflow.Page.portalChooserPage.printQueryDefine(printwriter, httprequest, "");
    }

    public static void printQueryDefine(java.io.PrintWriter printwriter, com.dragonflow.HTTP.HTTPRequest httprequest, String s)
    {
        com.dragonflow.Page.portalChooserPage.printQueryChooser(printwriter, httprequest, "Selection Set", "set of objects that define this selection set", s, false);
    }

    public static String getQueryChooseListSelectedItem(com.dragonflow.HTTP.HTTPRequest httprequest)
    {
        java.util.Enumeration enumeration = httprequest.getValues("item");
        String s;
        if(enumeration.hasMoreElements())
        {
            s = com.dragonflow.Page.portalChooserPage.getQueryString(enumeration);
        } else
        {
            s = httprequest.getValue("query");
        }
        return s;
    }

    public portalChooserPage(String s, String s1, boolean flag)
    {
        serversSelectable = true;
        bodyHeader = s;
        helpFileName = s1;
        serversSelectable = flag;
    }

    public portalChooserPage()
    {
        serversSelectable = true;
        bodyHeader = "Choose Monitors and Groups";
        helpFileName = "ChooseMon.htm";
        serversSelectable = true;
    }

    public void printBody()
        throws Exception
    {
        String s = request.getValue("chooserOperation");
        if(s.length() == 0)
        {
            printForm();
        } else
        {
            handleButton(s);
        }
    }

    protected static String getQueryString(java.util.Enumeration enumeration)
    {
        StringBuffer stringbuffer = new StringBuffer();
        if(enumeration.hasMoreElements())
        {
            stringbuffer.append("item=");
            do
            {
                stringbuffer.append((String)enumeration.nextElement());
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                stringbuffer.append("&item=");
            } while(true);
        }
        return stringbuffer.toString();
    }

    protected void printButton(java.io.PrintWriter printwriter, String s, String s1, String s2)
    {
        printwriter.println("<P><DT><TABLE WIDTH=300 BORDER=0><TR><TD><input type=submit name=chooserOperation value=\"" + s + "\"> Selected Items" + "<TD ALIGN=RIGHT><A HREF=/SiteView/docs/" + helpFileName + s1 + " TARGET=Help>Help</A></TR></TABLE>" + "<DD>" + s2);
    }

    protected void printPostFormHeader(java.io.PrintWriter printwriter)
    {
        printwriter.println("<FORM METHOD=POST ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=page VALUE=" + request.getValue("page") + "><INPUT TYPE=HIDDEN NAME=account VALUE=" + request.getAccount() + ">");
    }

    protected void printPostFormItem(java.io.PrintWriter printwriter, Object obj)
    {
        printwriter.println("<INPUT TYPE=HIDDEN NAME=item VALUE=" + (String)obj);
    }

    protected void printPostFormItems(java.io.PrintWriter printwriter, java.util.Enumeration enumeration)
    {
        for(; enumeration.hasMoreElements(); printwriter.println("<INPUT TYPE=HIDDEN NAME=item VALUE=" + (String)enumeration.nextElement())) { }
    }

    protected void printPostFormFooter(java.io.PrintWriter printwriter)
    {
        printwriter.println("</FORM>");
    }

    protected jgl.Array getItemList(java.util.Enumeration enumeration)
    {
        jgl.Array array = new Array();
        if(com.dragonflow.SiteView.Platform.isPortal())
        {
            com.dragonflow.SiteView.Portal portal = com.dragonflow.SiteView.Portal.getPortal();
            String s;
            for(; enumeration.hasMoreElements(); array.add(portal.getElement(s)))
            {
                s = (String)enumeration.nextElement();
            }

        } else
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            String s1;
            for(; enumeration.hasMoreElements(); array.add(siteviewgroup.getElementByID(s1)))
            {
                s1 = (String)enumeration.nextElement();
            }

        }
        return array;
    }

    public static void main(String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.portalChooserPage portalchooserpage = new portalChooserPage();
        if(args.length > 0)
        {
            portalchooserpage.args = args;
        }
        portalchooserpage.handleRequest();
    }

    protected void printButtons(java.io.PrintWriter printwriter)
    {
        printButton(printwriter, "Choose", "#Chooser", "Choose the selected groups and monitors");
    }

    protected void performOperation(String s, java.util.Enumeration enumeration)
        throws Exception
    {
        if(s.startsWith("Choose"))
        {
            String s1 = com.dragonflow.Page.portalChooserPage.getQueryString(enumeration);
            String s2 = "Item";
            if(s1.indexOf('&') >= 0)
            {
                s2 = s2 + "s";
            }
            String s3 = s + " " + s2;
            printBodyHeader(s3);
            String as[] = com.dragonflow.Utils.TextUtils.split(s);
            String s4 = as[0].toLowerCase();
            printButtonBar("ChooseMon.htm#" + s4, "");
            outputStream.println("<FONT SIZE=+1><B>" + s + " the " + s2 + ":</B></FONT><BR>");
            outputStream.println(s1);
            printFooter(outputStream);
        }
    }

    protected void handlePost(String s, java.util.Enumeration enumeration)
        throws Exception
    {
        jgl.Array array = getItemList(enumeration);
        jgl.Array array1 = new Array();
        jgl.Array array2 = new Array();
        jgl.Array array3 = new Array();
        for(enumeration = array.elements(); enumeration.hasMoreElements();)
        {
            com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)enumeration.nextElement();
            if(siteviewobject instanceof com.dragonflow.SiteView.PortalSiteView)
            {
                array3.add(siteviewobject);
            } else
            if(siteviewobject instanceof com.dragonflow.SiteView.MonitorGroup)
            {
                array2.add(siteviewobject);
            } else
            {
                array1.add(siteviewobject);
            }
        }

        handlePost(s, array3, array2, array1);
    }

    protected void handlePost(String s, jgl.Array array, jgl.Array array1, jgl.Array array2)
        throws Exception
    {
    }

    protected void performRedirect(StringBuffer stringbuffer, java.util.Enumeration enumeration)
        throws Exception
    {
        stringbuffer.append("&");
        String s = com.dragonflow.Page.portalChooserPage.getQueryString(enumeration);
        stringbuffer.append(s);
        String s1 = stringbuffer.toString();
        com.dragonflow.Page.portalChooserPage.printRefreshHeader(outputStream, "", s1, 0);
        outputStream.println("<!--If your browser doesn't refresh, click on <A HREF=" + s1 + ">this link</A> to continue.-->" + "</BODY>\n");
    }

    private static void printQueryChooser(java.io.PrintWriter printwriter, com.dragonflow.HTTP.HTTPRequest httprequest, String s, String s1, String s2, boolean flag)
    {
        if(s2 == null)
        {
            s2 = com.dragonflow.Page.portalChooserPage.getQueryString(httprequest);
        }
        if(s.length() > 0)
        {
            printwriter.println("<TR><TD ALIGN=RIGHT>" + s + ":</TD><TD>");
        }
        printwriter.println("<TABLE><TR><TD ALIGN=LEFT>");
        String s3 = "";
        String s4 = "";
        if(flag)
        {
            jgl.Array array = com.dragonflow.SiteView.Portal.getEditableQueryArray();
            array.pushFront(NO_QUERY_STRING);
            array.pushFront(NO_QUERY_VALUE);
            if(s2.length() > 0 && !com.dragonflow.SiteView.Portal.isQueryID(s2))
            {
                array.add(s2);
                array.add(CUSTOM_QUERY_STRING);
            }
            s3 = com.dragonflow.Page.CGI.getOptionsHTML(array, s2);
        }
        if(!flag || !com.dragonflow.SiteView.Portal.isQueryID(s2))
        {
            com.dragonflow.SiteView.PortalFilter portalfilter = new PortalFilter(s2);
            s4 = portalfilter.getDescription();
        }
        if(s3.length() > 0)
        {
            printwriter.println("<select name=query>" + s3 + "</select>");
        }
        if(s4.length() > 0)
        {
            printwriter.println("<TABLE BORDER=1 cellspacing=0><TR><TD>" + s4 + "</TD></TR></TABLE>");
        }
        printwriter.print("</TD><TD>\n<A HREF=\"/SiteView/cgi/go.exe/SiteView?page=portalChooser&account=" + httprequest.getAccount());
        if(s2.length() > 0)
        {
            printwriter.print("&" + s2);
        }
        printwriter.println("&returnURL=" + java.net.URLEncoder.encode(com.dragonflow.Page.portalChooserPage.stripItems(httprequest.rawURL)) + "\">choose items</A>" + "</TD></TR>" + "</TD></TR>" + "<TR><TD COLSPAN=4><FONT SIZE=-1>" + s1 + "</FONT></TD></TR>" + "</TD></TR></TABLE>");
        if(s.length() > 0)
        {
            printwriter.println("</TD><TD></TD></TR>");
        }
    }

    private static String stripItems(String s)
    {
        int i = s.indexOf(STRIP_STRING);
        if(i == -1)
        {
            return s;
        }
        int j = s.lastIndexOf(STRIP_STRING);
        j = s.indexOf("&", j + 1);
        if(j == -1)
        {
            j = s.length();
        }
        StringBuffer stringbuffer = new StringBuffer(s.substring(0, i));
        stringbuffer.append(s.substring(j, s.length()));
        return stringbuffer.toString();
    }

    private void handleButton(String s)
        throws Exception
    {
        if(request.isPost())
        {
            handlePost(s, request.getValues("item"));
        } else
        {
            java.util.Enumeration enumeration = request.getValues("item");
            if(enumeration.hasMoreElements())
            {
                String s1 = request.getValue(NEXT_PAGE_VARIABLE);
                if(s1.length() > 0)
                {
                    StringBuffer stringbuffer = new StringBuffer("/SiteView/cgi/go.exe/SiteView?page=");
                    stringbuffer.append(s1);
                    stringbuffer.append("&account=");
                    stringbuffer.append(request.getAccount());
                    String s3 = request.getValue("operation");
                    if(s3.length() > 0)
                    {
                        stringbuffer.append("&operation=");
                        stringbuffer.append(s3);
                    }
                    performRedirect(stringbuffer, enumeration);
                } else
                {
                    String s2 = request.getValue("returnURL");
                    if(s2.length() > 0)
                    {
                        performRedirect(new StringBuffer(s2), enumeration);
                    } else
                    {
                        performOperation(s, enumeration);
                    }
                }
            } else
            {
                printForm();
            }
        }
    }

    boolean defaultLoadState()
    {
        return false;
    }

    private void printForm()
        throws Exception
    {
        String s = request.getAccount();
        String s1 = com.dragonflow.SiteView.Platform.getDirectoryPath("groups", s);
        String s2 = s1 + java.io.File.separator + "chooser.dyn";
        String s3 = request.getValue(NEXT_PAGE_VARIABLE);
        String s4 = request.getValue("operation");
        String s5 = request.getValue("returnURL");
        printBodyHeader(bodyHeader);
        printButtonBar(helpFileName, "");
        jgl.Array array = null;
        try
        {
            array = com.dragonflow.Properties.FrameFile.readFromFile(s2);
        }
        catch(Exception exception)
        {
            array = new Array();
        }
        jgl.HashMap hashmap = null;
        boolean flag = false;
        boolean flag1 = defaultLoadState();
        java.util.Enumeration enumeration = request.getVariables();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            String s6 = (String)enumeration.nextElement();
            if(s6.startsWith(OPEN_VARIABLE))
            {
                flag1 = true;
                break;
            }
            if(!s6.startsWith(CLOSE_VARIABLE))
            {
                continue;
            }
            flag1 = true;
            break;
        } while(true);
        for(int i = 0; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            if(!com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_user").equals(s))
            {
                continue;
            }
            hashmap = hashmap1;
            if(!flag1)
            {
                hashmap.clear();
                hashmap.put("_user", s);
                flag = true;
            }
        }

        if(hashmap == null)
        {
            hashmap = new HashMap();
            array.add(hashmap);
            hashmap.put("_user", s);
        }
        java.util.Enumeration enumeration2 = request.getValues("item");
        if(flag1)
        {
            java.util.Enumeration enumeration1 = request.getVariables();
            do
            {
                if(!enumeration1.hasMoreElements())
                {
                    break;
                }
                String s7 = (String)enumeration1.nextElement();
                if(s7.startsWith(OPEN_VARIABLE))
                {
                    String s10 = s7.substring(OPEN_VARIABLE.length(), s7.length() - 2);
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint("OPEN " + s10);
                    }
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s10).equals("open"))
                    {
                        hashmap.put(s10, "open");
                        flag = true;
                    }
                } else
                if(s7.startsWith(CLOSE_VARIABLE))
                {
                    String s11 = s7.substring(CLOSE_VARIABLE.length(), s7.length() - 2);
                    if(debug)
                    {
                        com.dragonflow.Utils.TextUtils.debugPrint("CLOSE " + s11);
                    }
                    if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s11).equals("close"))
                    {
                        hashmap.remove(s11);
                        flag = true;
                    }
                }
            } while(true);
        } else
        if(enumeration2.hasMoreElements())
        {
            flag = true;
            Object obj;
            if(com.dragonflow.SiteView.Platform.isPortal())
            {
                obj = com.dragonflow.SiteView.Portal.getPortal();
            } else
            {
                obj = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            }
            do
            {
                String s8 = (String)enumeration2.nextElement();
                com.dragonflow.SiteView.SiteViewObject siteviewobject = ((com.dragonflow.SiteView.SiteViewObject) (obj)).getElement(s8);
                if(siteviewobject != null)
                {
                    com.dragonflow.SiteView.SiteViewObject siteviewobject2 = siteviewobject.getOwner();
                    if(siteviewobject2 instanceof com.dragonflow.SiteView.MonitorGroup)
                    {
                        com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewobject2;
                        do
                        {
                            String s9 = monitorgroup.getFullID();
                            hashmap.put(s9, "open");
                            com.dragonflow.SiteView.SiteViewObject siteviewobject1 = monitorgroup.getParent();
                            if(siteviewobject1 == null)
                            {
                                break;
                            }
                            monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewobject1;
                        } while(true);
                    }
                }
            } while(enumeration2.hasMoreElements());
            enumeration2 = request.getValues("item");
        }
        jgl.HashMap hashmap2 = new HashMap();
        for(; enumeration2.hasMoreElements(); hashmap2.put(enumeration2.nextElement(), "checked")) { }
        outputStream.println("<H2>" + bodyHeader + "</H2><P>Select one or more groups and monitors and then choose the action you wish to perform." + "<p><FORM METHOD=GET ACTION=/SiteView/cgi/go.exe/SiteView>" + "<INPUT TYPE=HIDDEN NAME=page VALUE=" + request.getValue("page") + "><INPUT TYPE=HIDDEN NAME=account VALUE=" + s + ">");
        if(s3.length() > 0)
        {
            outputStream.println("<INPUT TYPE=HIDDEN NAME=" + NEXT_PAGE_VARIABLE + " VALUE=" + s3 + ">");
            if(s4.length() > 0)
            {
                outputStream.println("<INPUT TYPE=HIDDEN NAME=operation VALUE=" + s4 + ">");
            }
        }
        if(s5.length() > 0)
        {
            outputStream.println("<INPUT TYPE=HIDDEN NAME=returnURL VALUE=" + s5 + ">");
        }
        outputStream.println("<HR>(Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand a group, and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a group).<P><TABLE BORDER=0>");
        com.dragonflow.SiteView.PortalQueryVisitor portalqueryvisitor = createPQVToPrint(hashmap, hashmap2);
        com.dragonflow.SiteView.PortalQuery portalquery = new PortalQuery(com.dragonflow.SiteView.PortalFilter.queryStringToMap(""), portalqueryvisitor, request);
        portalquery.runQuery();
        outputStream.println("</TABLE>");
        outputStream.println("<HR><BLOCKQUOTE><DL>");
        printButtons(outputStream);
        outputStream.println("</DL></BLOCKQUOTE>");
        outputStream.println("</FORM>");
        printFooter(outputStream);
        if(flag)
        {
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("SAVING CHOOSER STATE");
            }
            com.dragonflow.Properties.FrameFile.writeToFile(s2, array);
        }
    }

    protected com.dragonflow.SiteView.PortalQueryVisitor createPQVToPrint(jgl.HashMap hashmap, jgl.HashMap hashmap1)
    {
        return new PQVPrintChooserHTML(this, hashmap, hashmap1);
    }

}
