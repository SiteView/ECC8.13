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

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package COM.dragonflow.Page:
// portalPreferencePage, portalServerPage, portalPage

public class portalViewPage extends COM.dragonflow.Page.portalPreferencePage
{

    public portalViewPage()
    {
    }

    java.lang.String getTitle()
    {
        return "Views";
    }

    java.lang.String getPageName()
    {
        return "portalView";
    }

    java.lang.String getHelpPage()
    {
        return "ViewPrefs.htm";
    }

    java.lang.String getConfigFilePath()
    {
        return COM.dragonflow.SiteView.Platform.getRoot() + "/groups/views.config";
    }

    void printLayout(jgl.HashMap ahashmap[][], java.lang.String s)
        throws java.io.IOException
    {
        outputStream.println("<INPUT TYPE=HIDDEN NAME=layout." + s + ".height VALUE=" + ahashmap.length + ">");
        outputStream.println("<INPUT TYPE=HIDDEN NAME=layout." + s + ".width VALUE=" + ahashmap[0].length + ">");
        outputStream.println("<TABLE BORDER=1>");
        for(int i = 0; i < ahashmap.length; i++)
        {
            for(int j = 0; j < ahashmap[i].length; j++)
            {
                if(j == 0)
                {
                    outputStream.println("<TR>");
                }
                jgl.HashMap hashmap = ahashmap[i][j];
                if(hashmap != null)
                {
                    int k = 1 + (COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "yEnd")) - COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "yStart")));
                    int l = 1 + (COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "xEnd")) - COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "xStart")));
                    java.lang.String s1 = "";
                    java.lang.String s2 = "";
                    if(k > 1)
                    {
                        s1 = " ROWSPAN=" + k;
                    }
                    if(l > 1)
                    {
                        s2 = " COLSPAN=" + l;
                    }
                    outputStream.println("<TD" + s1 + s2 + ">");
                    printCell(hashmap, i, j, s);
                    outputStream.println("</TD>");
                }
                if(j == ahashmap[i].length - 1)
                {
                    outputStream.println("</TR>");
                }
            }

        }

        outputStream.println("</TABLE>");
    }

    void printCell(jgl.HashMap hashmap, int i, int j, java.lang.String s)
        throws java.io.IOException
    {
        java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "view");
        java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "query");
        java.lang.String s3 = "/\\.(html|htm|xsl|gif|jpg)$/";
        jgl.Array array = COM.dragonflow.SiteView.Portal.getEditableViewContentsArray(s3, true);
        jgl.Array array1 = COM.dragonflow.SiteView.Portal.getEditableQueryArray();
        jgl.Array array2 = new Array();
        array2.add("");
        array2.add("all");
        array2.add("serverDepth=true");
        array2.add("servers only");
        array2.add("groupDepth=true");
        array2.add("groups only");
        java.lang.String s4 = "cell." + s + "." + i + "." + j + ".";
        outputStream.println("<TABLE BORDER=0><INPUT TYPE=HIDDEN NAME=" + s4 + "xStart VALUE=" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "xStart") + ">" + "<INPUT TYPE=HIDDEN NAME=" + s4 + "xEnd VALUE=" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "xEnd") + ">" + "<INPUT TYPE=HIDDEN NAME=" + s4 + "yStart VALUE=" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "yStart") + ">" + "<INPUT TYPE=HIDDEN NAME=" + s4 + "yEnd VALUE=" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "yEnd") + ">" + "<TR><TD>Cell contents:</TD><TD><select name=" + s4 + "view>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array, s1) + "</select></TD><tr></tr><TD colspan=2><font size=\"-1\">Select a HTML or XSL template (required)</font></TD></TR>" + "<TR><TD>Data query:</TD><TD><select name=" + s4 + "query>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array1, s2) + "</select></TD><tr></tr><TD colspan=2><font size=\"-1\">Named Query for XML/XSL (optional)</font></TD></TR>" + "<TR><TD>Focus:</TD><TD><input type=text name=" + s4 + "focus " + "value=\"" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "focus") + "\"></TD>" + "<tr></tr><TD colspan=2><font size=\"-1\">Optional data focus variable</font></TD></TR>" + "<TR><TD>Level(s):</TD><TD><select name=" + s4 + "hint>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array2, COM.dragonflow.Utils.TextUtils.getValue(hashmap, "hint")) + "</select></TD><tr></tr><TD colspan=2><font size=\"-1\">Optional XML data trimming </font></TD></TR>" + "</TABLE>");
    }

    boolean matchLayout(jgl.HashMap ahashmap[][], jgl.HashMap ahashmap1[][])
    {
        if(ahashmap.length != ahashmap1.length)
        {
            return false;
        }
        if(ahashmap[0].length != ahashmap1[0].length)
        {
            return false;
        }
        for(int i = 0; i < ahashmap.length; i++)
        {
            for(int j = 0; j < ahashmap[i].length; j++)
            {
                if(ahashmap[i][j] == null && ahashmap1[i][j] != null || ahashmap[i][j] != null && ahashmap1[i][j] == null)
                {
                    return false;
                }
            }

        }

        return true;
    }

    private java.lang.String getSelectHTML(jgl.HashMap hashmap)
    {
        jgl.Array array = COM.dragonflow.SiteView.Portal.getEditableViewArray();
        jgl.Array array1 = new Array(array);
        array1.pushFront("Top-Level");
        array1.pushFront("");
        return "<select size=\"1\" name=\"parentViewID\"\n>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array1, COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_parentID")) + "</SELECT>";
    }

    void printBasicProperties(jgl.HashMap hashmap, jgl.HashMap hashmap1)
        throws java.io.IOException
    {
        if(request.getValue("operation").equalsIgnoreCase("AddFrame"))
        {
            outputStream.println("<TABLE>");
            jgl.Array array = COM.dragonflow.SiteView.Portal.getEditableViewContentsArray("/^Frame.*htm[l]*$/", true);
            outputStream.println("<table><tr><td>View Name</td><td>");
            outputStream.println("<TD ALIGN=LEFT><input type=text name=title size=50 value=\"" + COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_title") + "\">");
            outputStream.println("<table><tr><td>Enter a name to use for this view definition</td></tr></table></td><td>");
            outputStream.println(getSelectHTML(hashmap));
            outputStream.println("<table><tr><td>Select a parent view</td></tr></table></td></tr></table></table>");
            outputStream.println("<TABLE><TR><TD ALIGN=RIGHT>Frame Set</TD><TD><TABLE><TR><TD ALIGN=LEFT><select name=framesHTML size=1>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array, COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_framesHTML")) + "</select></TD></TR>" + "<TR><TD><FONT SIZE=-1>select an HTML frame template to use for this view</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR></TABLE>");
        } else
        {
            outputStream.println("<table><tr><td>View Name</td><td>");
            outputStream.println("<TD ALIGN=LEFT><input type=text name=title size=50 value=\"" + COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_title") + "\">");
            outputStream.println("<table><tr><td>Enter a name to use for this view definition</td></tr></table></td><td>");
            outputStream.println(getSelectHTML(hashmap));
            outputStream.println("<table><tr><td>Select a parent view</td></tr></table></td></tr></table>");
            jgl.Array array1 = COM.dragonflow.SiteView.Portal.getEditableViewContentsArray("Frame", true);
            if(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_framesHTML").length() > 0)
            {
                outputStream.println("<TABLE><TR><TD ALIGN=RIGHT>Frame Set</TD><TD><TABLE><TR><TD ALIGN=LEFT><select name=framesHTML size=1>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array1, COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_framesHTML")) + "</select></TD></TR>" + "<TR><TD><FONT SIZE=-1>select an HTML frame template to use for this view</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR></TABLE>");
            } else
            {
                jgl.Array array2 = COM.dragonflow.Properties.FrameFile.readFromFile(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/layouts.config");
                jgl.Array array3 = new Array();
                if(hashmap.size() > 0)
                {
                    array3.add(hashmap);
                }
                for(int i = 1; i < array2.size(); i++)
                {
                    array3.add(array2.at(i));
                }

                jgl.HashMap ahashmap[][] = (jgl.HashMap[][])null;
                for(int j = 0; j < array3.size(); j++)
                {
                    jgl.HashMap hashmap2 = (jgl.HashMap)array3.at(j);
                    java.lang.String s = j != 0 ? "" : "CHECKED";
                    COM.dragonflow.Page.portalPage.convertViewCells(hashmap2);
                    int ai[] = COM.dragonflow.Page.portalPage.getTableDimensions(hashmap2.values("_cell"));
                    int k = ai[0];
                    int l = ai[1];
                    jgl.HashMap ahashmap1[][] = COM.dragonflow.Page.portalPage.getLayout(hashmap2.values("_cell"), k, l);
                    if(j == 0)
                    {
                        ahashmap = ahashmap1;
                    } else
                    if(matchLayout(ahashmap, ahashmap1))
                    {
                        continue;
                    }
                    outputStream.println("<TABLE BORDER=0><TR><TH><FONT SIZE=-1>Select layout</FONT></TH><TD><INPUT TYPE=RADIO " + s + " NAME=layout value=" + j + "></TD>" + "<TD>");
                    printLayout(ahashmap1, "" + j);
                    outputStream.println("</TD></TR></TABLE><P>");
                }

                outputStream.println("</TD></TR></TABLE><P> Select a layout to use for this view. The <b>Cell contents</b> template for each layout cell can be either an HTML segment or an XSL stylesheet. ");
                outputStream.println("A named <b>Data query</b> (optional) is applicable to layout cells that use XSL stylesheets to format the portal XML output. The <b>Level(s)</b> option allows you to further trim the portal XML data to show only servers and monitor groups or only the SiteView server names.");
            }
        }
    }

    boolean hasAdvancedOptions()
    {
        return true;
    }

    void printAdvancedProperties(jgl.HashMap hashmap, jgl.HashMap hashmap1)
        throws java.io.IOException
    {
        outputStream.println("<TABLE>");
        jgl.Array array = COM.dragonflow.SiteView.Portal.getEditableViewContentsArray("Header", true);
        outputStream.println("<TR><TD ALIGN=RIGHT>Header</TD><TD><TABLE><TR><TD ALIGN=LEFT><select name=header size=1>" + COM.dragonflow.Page.portalViewPage.getOptionsHTML(array, COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_header")) + "</select></TD></TR>" + "<TR><TD><FONT SIZE=-1>select an optional HTML header template to use for this view</FONT></TD></TR>" + "</TABLE></TD><TD><I></I></TD></TR>");
        outputStream.println("</TABLE>");
    }

    jgl.HashMap fillInResultFrame(jgl.HashMap hashmap)
    {
        java.lang.String s = request.getValue("layout");
        jgl.HashMap hashmap1 = new HashMap();
        jgl.HashMap hashmap2;
        java.lang.String s2;
        for(java.util.Enumeration enumeration = hashmap.values("_cell"); enumeration.hasMoreElements(); hashmap1.put(s2, hashmap2))
        {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            hashmap2 = COM.dragonflow.Utils.TextUtils.stringToHashMap(s1);
            s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "xStart") + "," + COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "yStart") + "," + COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "xEnd") + "," + COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "yEnd");
        }

        hashmap.remove("_cell");
        int i = COM.dragonflow.Utils.TextUtils.toInt(request.getValue("layout." + s + ".width"));
        int j = COM.dragonflow.Utils.TextUtils.toInt(request.getValue("layout." + s + ".height"));
        jgl.HashMap ahashmap[][] = new jgl.HashMap[j][i];
        for(int k = 0; k < j; k++)
        {
            for(int l = 0; l < i; l++)
            {
                java.lang.String s3 = "cell." + s + "." + k + "." + l + ".";
                java.lang.String s4 = request.getValue(s3 + "xStart");
                if(s4.length() > 0)
                {
                    java.lang.String s5 = request.getValue(s3 + "xEnd");
                    java.lang.String s6 = request.getValue(s3 + "yStart");
                    java.lang.String s7 = request.getValue(s3 + "yEnd");
                    java.lang.String s8 = s4 + "," + s6 + "," + s5 + "," + s7;
                    jgl.HashMap hashmap3 = (jgl.HashMap)hashmap1.get(s8);
                    if(hashmap3 == null)
                    {
                        hashmap3 = new HashMap();
                    }
                    hashmap3.put("xStart", s4);
                    hashmap3.put("xEnd", s5);
                    hashmap3.put("yStart", s6);
                    hashmap3.put("yEnd", s7);
                    hashmap3.put("view", request.getValue(s3 + "view"));
                    hashmap3.put("query", request.getValue(s3 + "query"));
                    hashmap3.put("focus", java.net.URLEncoder.encode(request.getValue(s3 + "focus")));
                    hashmap3.put("hint", request.getValue(s3 + "hint"));
                    java.lang.String s9 = COM.dragonflow.Utils.TextUtils.hashMapToString(hashmap3);
                    hashmap.add("_cell", s9);
                } else
                {
                    ahashmap[k][l] = null;
                }
            }

        }

        hashmap.put("_title", request.getValue("title"));
        hashmap.put("_id", request.getValue("id"));
        hashmap.put("_header", request.getValue("header"));
        hashmap.put("_parentID", request.getValue("parentViewID"));
        hashmap.put("_framesHTML", request.getValue("framesHTML"));
        return hashmap;
    }

    private void toggleView()
    {
        jgl.HashMap hashmap = getMasterConfig();
        java.lang.String s = COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_showPortalSubViews");
        if(s.length() > 0)
        {
            hashmap.put("_showPortalSubViews", "");
        } else
        {
            hashmap.put("_showPortalSubViews", "checked");
        }
        try
        {
            saveMasterConfig(hashmap);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        if(s.length() == 0)
        {
            s = "List";
        }
        if(s.equals("List"))
        {
            printListForm(s);
        } else
        if(s.equals("Add"))
        {
            printAddForm(s);
        } else
        if(s.equals("AddFrame"))
        {
            printAddForm(s);
        } else
        if(s.equals("Delete"))
        {
            printDeleteForm(s);
        } else
        if(s.equals("Edit"))
        {
            printAddForm(s);
        } else
        {
            printOtherForm(s);
        }
    }

    void printListHeader()
    {
        java.lang.String s = request.getValue("toggleview");
        if(s.equalsIgnoreCase("true"))
        {
            toggleView();
        }
        outputStream.println("<TH>Name</TH><TH WIDTH=10%>Edit</TH><TH WIDTH=3%>Del</TH>");
    }

    void printListItem(jgl.HashMap hashmap)
    {
        jgl.HashMap hashmap1 = getMasterConfig();
        java.lang.String s = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_id");
        java.lang.String s1 = COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_title");
        java.lang.String s2 = COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_parentID");
        java.lang.String s3 = "/SiteView/cgi/go.exe/SiteView?page=" + getPageName() + "&id=" + s + "&account=" + request.getAccount();
        java.lang.String s4 = "<A href=/SiteView/cgi/go.exe/SiteView?page=portal&account=" + request.getAccount() + "&view=" + s + " target=\"_top\">";
        java.lang.String s5 = "<A href=" + s3 + "&operation=Delete>X</a>";
        java.lang.String s6 = "<A href=" + s3 + "&operation=Edit>Edit</a>";
        if(!s1.equals(""))
        {
            if(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_package").length() > 0)
            {
                s5 = "&nbsp;";
                s6 = "&nbsp;";
                s1 = s1 + " (in <B>" + COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_package") + "</B> package)";
            }
            if(COM.dragonflow.Page.portalViewPage.getValue(hashmap1, "_showPortalSubViews").length() > 0)
            {
                outputStream.println("<TR><TD align=left>" + s4 + s1 + "</A>" + hasParent(s2) + "</TD>" + "<TD" + ">" + s6 + "</TD>" + "<TD" + ">" + s5 + "</TD>" + "</TR>\n");
            } else
            if(s2.length() == 0)
            {
                outputStream.println("<TR><TD align=left>" + s4 + s1 + "</A></TD>" + "<TD" + ">" + s6 + "</TD>" + "<TD" + ">" + s5 + "</TD>" + "</TR>\n");
            }
        }
    }

    void printListForm(java.lang.String s)
        throws java.io.IOException
    {
        java.lang.String s1 = request.getAccount();
        java.lang.String s2 = request.user.getProperty("_preference");
        if(!s1.equals("administrator") && !s2.equals("true"))
        {
            outputStream.println("<hr>Access Permission Error.<hr>");
            return;
        }
        java.lang.String s3 = getTitle();
        printBodyHeader(s3);
        printButtonBar(getHelpPage(), "");
        outputStream.println("<p><H2>" + s3 + " List</H2><TABLE WIDTH=100% BORDER=2>");
        printListHeader();
        jgl.Array array = readListFrames();
        if(array.size() < 2)
        {
            outputStream.println("<TR><TD>no " + s3 + "s</TD></TR>");
        } else
        {
            for(int i = 1; i < array.size(); i++)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                printListItem(hashmap);
            }

        }
        outputStream.println();
        outputStream.println("</TABLE><BR>");
        printListFooter();
        outputStream.println("<A HREF=" + getPageLink(getPageName(), "Add") + ">Add</A> " + getTitle() + "\n");
        outputStream.println("<br><A HREF=" + getPageLink(getPageName(), "AddFrame") + ">Add</A> Frame View\n");
        printFooter(outputStream);
    }

    jgl.Array readListFrames()
    {
        jgl.Array array = super.readListFrames();
        try
        {
            COM.dragonflow.SiteView.Portal.readExtraItems("views.config", array);
        }
        catch(java.io.IOException ioexception)
        {
            COM.dragonflow.Log.LogManager.log("Error", "could not read extra view file : " + ioexception.getMessage());
        }
        return array;
    }

    void printListFooter()
    {
        try
        {
            java.lang.String s = null;
            jgl.HashMap hashmap = getMasterConfig();
            s = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_showPortalSubViews");
            java.lang.String s1 = "/SiteView/cgi/go.exe/SiteView?page=portalView&account=administrator&toggleview=true";
            outputStream.println("<SCRIPT LANGUAGE=\"javascript\">");
            outputStream.println("<!--");
            outputStream.println("function ShowSubGroups_onclick() {");
            outputStream.println("document.location = \"" + s1 + "\";");
            outputStream.println(" }\n //-->\n </SCRIPT>");
            outputStream.println("<FORM name=\"showSubView\" action=\"javascript:ShowSubGroups_onclick()\">");
            outputStream.println("<INPUT type=\"checkbox\" " + s + " value=\"ON\" name=\"ShowSubGroups\" LANGUAGE=\"javascript\" onclick=\"return ShowSubGroups_onclick()\">Show Subviews </INPUT>");
            outputStream.println("</FORM>");
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
        }
    }

    private java.lang.String hasParent(java.lang.String s)
    {
        java.lang.String s1 = "";
        if(s != null && !s.equalsIgnoreCase(""))
        {
            jgl.Array array = null;
            try
            {
                array = COM.dragonflow.Properties.FrameFile.readFromFile(getConfigFilePath());
            }
            catch(java.io.IOException ioexception)
            {
                COM.dragonflow.Log.LogManager.log("Error", "could not read configuration file " + getConfigFilePath() + ": " + ioexception.getMessage());
                array = new Array();
            }
            if(array.size() >= 2)
            {
                for(int i = 1; i < array.size(); i++)
                {
                    jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                    if(COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_id").equalsIgnoreCase(s))
                    {
                        s1 = " (parent: " + COM.dragonflow.Page.portalViewPage.getValue(hashmap, "_title") + ")";
                    }
                }

            }
        }
        return s1;
    }

    void printAddForm(java.lang.String s)
        throws java.lang.Exception
    {
        java.lang.String s1 = request.getAccount();
        java.lang.String s2 = request.user.getProperty("_preference");
        if(!s1.equals("administrator") && !s2.equals("true"))
        {
            outputStream.println("<hr>Access Permission Error.<hr>");
            return;
        }
        jgl.Array array = new Array();
        array.add(new HashMapOrdered(true));
        try
        {
            java.lang.String s3 = getConfigFilePath();
            if((new File(s3)).exists())
            {
                array = COM.dragonflow.Properties.FrameFile.readFromFile(s3);
            }
            if(array.size() == 0)
            {
                array.add(new HashMapOrdered(true));
            }
        }
        catch(java.io.IOException ioexception)
        {
            COM.dragonflow.Log.LogManager.log("Error", "problem reading config file " + getConfigFilePath() + ": " + ioexception.getMessage());
        }
        if(request.isPost())
        {
            jgl.HashMap hashmap = null;
            if(s.equals("Add") || s.equals("AddFrame"))
            {
                hashmap = getResultFrame();
                array.add(hashmap);
                jgl.HashMap hashmap1 = (jgl.HashMap)array.at(0);
                setUniqueID(hashmap1, hashmap);
                postProcessAdd(hashmap);
            } else
            {
                java.lang.String s4 = request.getValue("id");
                hashmap = COM.dragonflow.Page.portalViewPage.findFrameByID(array, s4);
                if(hashmap != null)
                {
                    fillInResultFrame(hashmap);
                } else
                {
                    throw new Exception(getTitle() + " id (" + s4 + ") could not be found");
                }
            }
            jgl.HashMap hashmap2 = new HashMap();
            verify(hashmap, hashmap2);
            if(hashmap2.size() == 0)
            {
                COM.dragonflow.Properties.FrameFile.writeToFile(getConfigFilePath(), array);
                COM.dragonflow.SiteView.Portal.signalReload();
                printRefreshPage("/SiteView/cgi/go.exe/SiteView?page=" + getPageName() + "&operation=List&account=" + request.getAccount(), 0);
            } else
            {
                printEditForm(s, hashmap, hashmap2);
            }
        } else
        {
            printEditForm(s, array, new HashMap());
        }
    }

    public static void main(java.lang.String args[])
    {
        (new portalServerPage()).handleRequest();
    }
}
