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
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.StandardMonitor.ADReplicationMonitor;
import COM.dragonflow.StandardMonitor.Exchange2k3MailboxMonitor;

// Referenced classes of package COM.dragonflow.Page:
// CGI, SSrtn, monitorSetTemplate, monitorSetFilter,
// vMachinePage

public class monitorSetPage extends COM.dragonflow.Page.CGI
{

    public static final java.lang.String TEMPLATES_DIR;
    public static final java.lang.String SOLUTIONS_DIR;
    protected java.lang.String thisPageName;
    public java.lang.StringBuffer HTMLPage;
    protected java.lang.String helpPage;
    protected static final java.lang.String SOLUTION = "solution";
    protected static final java.lang.String OPERATION = "operation";
    protected static final java.lang.String PICK_SOLUTION = "PickSolution";
    protected static final java.lang.String ADD_SET = "AddSet";
    protected static final java.lang.String MSET_PROPERTIES = "monitorSetProps";
    protected static final java.lang.String MSET_CREATE_PREP = "monitorSetCreatePrep";
    protected static final java.lang.String MSET_CREATE = "monitorSetCreate";
    protected static final java.lang.String TEMPLATE_FILE = "templatefile";
    protected static final java.lang.String GROUP = "group";
    protected char positionDelimiter;
    private static final java.lang.String HELP_FILE = "_helpFile";
    protected static final java.lang.String DISPLAY_FILTER = "_propertyDisplayFilter";
    protected static final java.lang.String REPLACE_FILTER = "_propertyReplace";
    protected static final java.lang.String SERVERLABEL = "Server";
    private static final java.lang.String DEPLOY_CONTROL_SETTING = "_deployControlVar";
    public static final java.util.regex.Pattern FOREACH_VARNAME_PATTERN = java.util.regex.Pattern.compile("^@([a-zA-Z_0-9 ]+)@:.+");
    public static final java.lang.String NAME_IDX = "name";
    public static final java.lang.String VALUE_IDX = "value";

    public monitorSetPage()
    {
        thisPageName = "monitorSet";
        HTMLPage = new StringBuffer();
        helpPage = "../docs/MonitorSet.htm";
        positionDelimiter = '#';
    }

    public monitorSetPage(COM.dragonflow.HTTP.HTTPRequest httprequest)
    {
        thisPageName = "monitorSet";
        HTMLPage = new StringBuffer();
        helpPage = "../docs/MonitorSet.htm";
        request = httprequest;
    }

    public COM.dragonflow.Page.CGI.menus getNavItems(COM.dragonflow.HTTP.HTTPRequest httprequest)
    {
        COM.dragonflow.Page.CGI.menus menus1 = new CGI.menus();
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Browse", "browse", "", "page", "Browse Monitors"));
        }
        if(httprequest.actionAllowed("_preference"))
        {
            menus1.add(new CGI.menuItems("Remote UNIX", "machine", "", "page", "Add/Edit Remote UNIX/Linux profiles"));
            menus1.add(new CGI.menuItems("Remote NT", "ntmachine", "", "page", "Add/Edit Remote Win NT/2000 profiles"));
        }
        if(httprequest.actionAllowed("_tools"))
        {
            menus1.add(new CGI.menuItems("Tools", "monitor", "Tools", "operation", "Use monitor diagnostic tools"));
        }
        if(httprequest.actionAllowed("_progress"))
        {
            menus1.add(new CGI.menuItems("Progress", "Progress", "", "url", "View current monitoring progress"));
        }
        if(httprequest.actionAllowed("_browse"))
        {
            menus1.add(new CGI.menuItems("Summary", "monitorSummary", "", "page", "View current monitor settings"));
        }
        return menus1;
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = request.getValue("operation");
        boolean flag = request.getValue("solution").length() > 0;
        java.lang.String s1 = "";
        COM.dragonflow.Page.SSrtn ssrtn;
        if(s.equals("PickSolution"))
        {
            s1 = "Choose Solution";
            ssrtn = pickSolution();
        } else
        if(s.equals("AddSet"))
        {
            s1 = "Add " + (flag ? "Solution" : "Monitor Set");
            ssrtn = pickMonitorSet();
        } else
        if(s.equals("monitorSetProps"))
        {
            s1 = (flag ? "Solution Template  " : "Monitor Set ") + "Properties";
            ssrtn = enterSetProperties();
        } else
        if(s.equals("monitorSetCreatePrep"))
        {
            s1 = flag ? "Verify Solution Template" : "Monitor Set Verify";
            ssrtn = checkSetParams();
        } else
        if(s.equals("monitorSetCreate"))
        {
            s1 = flag ? "Create Solution" : "Monitor Set Create";
            ssrtn = createSet();
        } else
        {
            s1 = "";
            ssrtn = new SSrtn(COM.dragonflow.Page.SSrtn.ERR_InvalidOpr);
        }
        if(ssrtn.isError())
        {
            printError(ssrtn.message(), ssrtn.errormsg(), "");
            return;
        }
        COM.dragonflow.Page.CGI.menus menus1 = getNavItems(request);
        if(request.getValue("refreshURL").length() > 0)
        {
            java.lang.String s2 = "/SiteView/cgi/go.exe/SiteView?page=" + request.getValue("refreshURL") + "&account=" + request.getAccount();
            COM.dragonflow.Page.monitorSetPage.printRefreshHeader(outputStream, COM.dragonflow.SiteView.Platform.productName + " " + s1, s2, 8);
            printButtonBar(helpPage, "", menus1);
        } else
        {
            printBodyHeader(COM.dragonflow.SiteView.Platform.productName + " " + s1);
            printButtonBar(helpPage, "", menus1);
        }
        outputStream.println(HTMLPage);
        printFooter(outputStream);
        outputStream.println("\n</body>\n</html>");
    }

    private COM.dragonflow.Page.SSrtn pickSolution()
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s = COM.dragonflow.HTTP.HTTPRequest.encodeString(request.getValue("group"));
        helpPage = "../docs/Solutions.htm";
        HTMLPage.append("<H2>Add a Monitoring Solution to group : <A HREF=" + COM.dragonflow.Page.CGI.getGroupDetailURL(request, COM.dragonflow.Utils.I18N.toDefaultEncoding(s)) + ">" + COM.dragonflow.Page.CGI.getGroupName(COM.dragonflow.Utils.I18N.toDefaultEncoding(s)) + "</a></H2>\n");
        HTMLPage.append("<h3>Available Monitoring Solutions:</h3><p>");
        HTMLPage.append("<br>");
        HTMLPage.append("<hr>");
        HTMLPage.append("<br clear=all>");
        HTMLPage.append("</p>");
        HTMLPage.append("<TABLE BORDER=1 CELLPADDING=5 CELLSPACING=0 WIDTH=100%>");
        HTMLPage.append("<TR >");
        HTMLPage.append("<th align=center>Solution Name</th>");
        HTMLPage.append("<th align=center>Description</th>");
        HTMLPage.append("<th align=center>More Information</th>");
        HTMLPage.append("</tr>");
        java.lang.String as[] = getAvailableTemplates(SOLUTIONS_DIR, COM.dragonflow.Page.monitorSetTemplate.fileSuffix);
        if(as == null || as.length == 0)
        {
            HTMLPage.append("<tr><td>A seperate License is required to enable Solutions Sets for Exchange and Active Diretory.</td></tr>");
            return ssrtn;
        }
        java.lang.String as1[] = getTemplateNames(as, SOLUTIONS_DIR);
        java.lang.String as2[] = getTemplateDescriptions(as, SOLUTIONS_DIR);
        java.lang.String as3[] = getTemplateMoreInfo(as, SOLUTIONS_DIR);
        java.lang.String as4[] = getTemplateSolutionPages(as, SOLUTIONS_DIR);
        for(int i = 0; i < as.length; i++)
        {
            boolean flag = false;
            java.lang.String s1 = as1[i];
            java.lang.String s2 = as2[i];
            java.lang.String s3 = as3[i];
            if(s1.toUpperCase().indexOf("EXCHANGE") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense(new Exchange2k3MailboxMonitor()))
                {
                    flag = true;
                }
            } else
            if(s1.toUpperCase().indexOf("ACTIVE") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense(new ADReplicationMonitor()))
                {
                    flag = true;
                }
            } else
            if(s1.toUpperCase().indexOf("WEBSPHERE") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense("WebSphereSolution"))
                {
                    flag = true;
                }
            } else
            if(s1.toUpperCase().indexOf("WEBLOGIC") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense("WebLogicSolution"))
                {
                    flag = true;
                }
            } else
            if(s1.toUpperCase().indexOf("ORACLE") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense("OracleSolution"))
                {
                    flag = true;
                }
            } else
            if(s1.toUpperCase().indexOf("SIEBEL") >= 0)
            {
                if(COM.dragonflow.Utils.LUtils.isValidSSforXLicense("SiebelSolution"))
                {
                    flag = true;
                }
            } else
            {
                flag = true;
            }
            if(flag)
            {
                HTMLPage.append("<tr><td><A HREF=/SiteView/cgi/go.exe/SiteView?page=" + as4[i] + "&operation=monitorSetProps&group=" + s + "&account=" + request.getAccount() + "&templatefile=" + as[i] + "&" + "solution" + "=true" + ">" + s1 + "</A> </td><td>" + s2 + "</td><td>" + s3 + "</td></tr>");
            } else
            {
                HTMLPage.append("<tr><td>" + s1 + "</td><td>" + s2 + "<br>(additional licensing required)</td><td><a href=../../docs/Solutions.htm>Solutions Overview</a></td></tr>");
            }
        }

        HTMLPage.append("</TABLE><p><br clear=all><hr><br></p>");
        return ssrtn;
    }

    public boolean createMonitorSet(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap)
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s2 = COM.dragonflow.Utils.I18N.toDefaultEncoding(s);
        java.lang.String s3 = TEMPLATES_DIR + java.io.File.separator + s1;
        COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s3);
        java.lang.String as[] = monitorsettemplate.getVariables();
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s4 = (java.lang.String)hashmap.get(as[i]);
            if(s4 != null)
            {
                monitorsettemplate.replaceVariable(as[i], s4);
            } else
            {
                java.lang.System.out.print("monitor set variable mismatch in: " + s1);
            }
        }

        int j = monitorsettemplate.getMonitorCount();
        for(int k = 0; k < j; k++)
        {
            jgl.HashMap hashmap1 = monitorsettemplate.getNthMonitor(k);
            try
            {
                ssrtn = createMonitor(s2, hashmap1);
            }
            catch(java.lang.Exception exception)
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_Exception, "Exception: " + exception);
            }
            if(ssrtn.isError())
            {
                return false;
            }
            HTMLPage.append("Successfully created monitor. Check group page for status.<br></p>\n");
        }

        COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s2);
        return true;
    }

    COM.dragonflow.Page.SSrtn pickMonitorSet()
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s = request.getValue("group");
        HTMLPage.append("<H2>Add Monitor Set to group : <A HREF=" + COM.dragonflow.Page.CGI.getGroupDetailURL(request, COM.dragonflow.Utils.I18N.toDefaultEncoding(s)) + ">" + COM.dragonflow.Page.CGI.getGroupName(COM.dragonflow.Utils.I18N.toDefaultEncoding(s)) + "</a></H2>\n");
        HTMLPage.append("<h3>Current Monitor Set Templates:</h3>");
        java.lang.String as[] = getAvailableTemplates();
        if(as == null || as.length == 0)
        {
            ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_NoTemplatesFound, "Please verify that the SiteView/templates.sets directory exists, and that it contains template files");
            return ssrtn;
        }
        HTMLPage.append("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n<input type=hidden name=page value=" + getNextPage(request.getValue("operation")) + ">\n" + "<input type=hidden name=operation value=" + "monitorSetProps" + ">\n" + "<input type=hidden name=account value= \"" + request.getAccount() + "\">\n" + "<input type=hidden name=group value= \"" + s + "\">\n");
        HTMLPage.append("<TABLE BORDER=1 CELLSPACING=0 WIDTH=100%>\n<TR><th>Name</th><th>Description</th><th>Filename</th></tr>");
        java.lang.String as1[] = getTemplateNames(as);
        java.lang.String as2[] = getTemplateDescriptions(as);
        for(int i = 0; i < as.length; i++)
        {
            HTMLPage.append("<tr><td><input type=radio name=templatefile value=\"" + as[i] + "\">  " + as1[i] + "</td><td>" + as2[i] + "</td><td>" + as[i] + "</td></tr>\n");
        }

        HTMLPage.append("</TABLE>");
        HTMLPage.append("<BR><input type=submit value=Configure> Monitor Set\n<P>\n");
        HTMLPage.append("\n</FORM>");
        HTMLPage.append("<HR><P>Use Monitor Sets to quickly replicate a set of monitors across multiple servers or locations. ");
        HTMLPage.append("Select a Monitor Set Template and click Configure to enter settings for this set of  monitors. Click <a href=\"../../docs/MonitorSet.htm\">Help</a> for instructions on creating new Monitor Set Templates.\n<P>\n");
        return ssrtn;
    }

    COM.dragonflow.Page.SSrtn enterSetProperties()
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s = request.getValue("templatefile");
        java.lang.String s1 = request.getValue("group");
        boolean flag = request.getValue("solution").length() > 0;
        if(s.length() == 0)
        {
            ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_NoTemplateFile, "Please select a monitor set template");
            return ssrtn;
        } else
        {
            java.lang.String s2 = getTemplateFilePath(s);
            COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s2);
            setHelpLink(monitorsettemplate);
            printJavaScript();
            verifyTemplate(monitorsettemplate, ssrtn);
            printNameAndDescription(monitorsettemplate, flag, s);
            java.lang.String s3 = getFormName();
            openVariablesForm(s1, s, s3, thisPageName);
            openVariablesTable(flag);
            java.lang.String s4 = getRemotesHTML();
            printVariablesForm(monitorsettemplate, flag, s4);
            closeVariableTable();
            printVariablesFormSubmit(flag);
            closeVariablesForm();
            return ssrtn;
        }
    }

    protected void printJavaScript()
    {
    }

    protected java.lang.String getFormName()
    {
        return null;
    }

    protected void printVariablesFormSubmit(boolean flag)
    {
        HTMLPage.append("<p>Enter the values to be used by the monitors in this " + (flag ? "Solution Template" : "Monitor Set") + ".<P>\n");
        HTMLPage.append("<BR><input type=submit value=Submit>&nbsp;these values<P>\n");
    }

    protected void printNameAndDescription(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate, boolean flag, java.lang.String s)
    {
        java.lang.String s1 = monitorsettemplate.getName();
        HTMLPage.append("<P><h3>" + (flag ? "Solution Properties for " : "Monitor Set Properties for template: ") + s1 + "</h3>\n");
        HTMLPage.append("<P><h3>Description for " + s1 + ": </h3>\n");
        java.lang.String as[] = getTemplateDescriptions(s, flag ? SOLUTIONS_DIR : TEMPLATES_DIR);
        HTMLPage.append("<P>" + as[0] + "\n");
    }

    protected void verifyTemplate(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate, COM.dragonflow.Page.SSrtn ssrtn)
    {
        for(int i = 0; i < monitorsettemplate.getMonitorCount(); i++)
        {
            java.lang.String s = monitorsettemplate.verifyNthMonitor(i);
            if(s.length() != 0)
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_badTemplateData, s);
            }
        }

    }

    protected void openVariablesForm(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        HTMLPage.append("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST ");
        if(s2 != null && s2.length() > 0)
        {
            HTMLPage.append(" NAME=").append(s2);
        }
        HTMLPage.append(">\n<input type=hidden name=page value=" + s3 + ">\n" + "<input type=hidden name=operation value=" + "monitorSetCreatePrep" + ">\n" + "<input type=hidden name=account value= \"" + request.getAccount() + "\">\n" + "<input type=hidden name=group value= \"" + s + "\">\n" + "<input type=hidden name=" + "solution" + " value= \"" + request.getValue("solution") + "\">\n" + "<input type=hidden name=templatefile value= \"" + s1 + "\">\n");
    }

    protected void closeVariablesForm()
    {
        HTMLPage.append("\n</FORM>");
    }

    protected void openVariablesTable(boolean flag)
    {
        if(flag)
        {
            HTMLPage.append("<TABLE BORDER=0 CELLSPACING=0 WIDTH=\"100%\">\n");
        } else
        {
            HTMLPage.append("<TABLE BORDER=1 CELLSPACING=0 WIDTH=\"100%\">\n");
            HTMLPage.append("<TR><TH>Variable Name</TH><TH>Description</TH><TH>Enter Value</TH><TH>Monitor Type</TH></TR>\n");
        }
    }

    protected void closeVariableTable()
    {
        HTMLPage.append("\n</TABLE><P>\n");
    }

    private java.lang.String getRemotesHTML()
    {
        jgl.HashMap hashmap = COM.dragonflow.SiteView.Machine.getMachineTable();
        java.lang.String s = "";
        java.util.Enumeration enumeration = hashmap.keys();
        java.util.Vector vector = new Vector();
        for(; enumeration.hasMoreElements(); vector.addElement(enumeration.nextElement())) { }
        vector.addElement("other");
        for(int i = 0; i < vector.size(); i++)
        {
            java.lang.String s1 = (java.lang.String)vector.elementAt(i);
            boolean flag = s1.equals("other");
            java.lang.String s2 = "";
            if(!flag)
            {
                COM.dragonflow.SiteView.Machine machine = (COM.dragonflow.SiteView.Machine)hashmap.get(s1);
                s2 = machine.getProperty("_name");
            } else
            {
                s2 = "other";
            }
            s = s + COM.dragonflow.Page.vMachinePage.getListOptionHTML(s1, s2, flag);
        }

        return s;
    }

    protected void printVariablesForm(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate)
    {
        printVariablesForm(monitorsettemplate, true, "");
    }

    protected void printVariablesForm(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate, boolean flag, java.lang.String s)
    {
        java.lang.String as[] = monitorsettemplate.getVariables();
        as = sortVars(as);
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = as[i];
            jgl.HashMap hashmap = monitorsettemplate.getVariableInfo(s1);
            java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_description");
            java.lang.String s3 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_value");
            boolean flag1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_scalar").length() > 0;
            boolean flag2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_server").length() > 0;
            boolean flag3 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_checkbox").length() > 0;
            java.lang.String s4 = getDisplayVariable(s1);
            java.lang.String as1[] = monitorsettemplate.getWhereUsed(s1);
            if(flag)
            {
                if(flag2)
                {
                    java.lang.String s5 = monitorsettemplate.getSetting("_platform");
                    java.lang.String s9 = "";
                    java.lang.String s11 = "";
                    java.lang.String s12 = s5.toLowerCase().equals("windows") ? "true" : "";
                    java.lang.String s14 = s5.toLowerCase().equals("unix") ? "true" : "";
                    java.lang.String s16 = "";
                    java.lang.String s17 = "\\\\servername";
                    java.lang.String s18 = request.getValue("server");
                    java.lang.String s19 = s17;
                    if(s18.length() > 0)
                    {
                        if(s18.toUpperCase().equals("other"))
                        {
                            s17 = request.getValue("otherServer");
                        } else
                        {
                            s17 = s18;
                        }
                        int l = s17.indexOf("\\\\");
                        if(l >= 0)
                        {
                            s19 = s17 = s17.substring(2);
                        } else
                        if(s17.startsWith("remote:"))
                        {
                            s19 = COM.dragonflow.SiteView.Machine.getMachineName(s17);
                        }
                    }
                    HTMLPage.append("<TR><TD ALIGN=\"RIGHT\" VALIGN=\"TOP\">Server</TD><TD><TABLE><TR><TD ALIGN=\"left\" VALIGN=\"top\"><TABLE border=1 cellspacing=0><TR><TD>" + s19 + "</TD></TR></TABLE></TD><TD>" + "<input type=hidden name=\"" + s1 + "\" value=\"" + s17 + "\">" + "<a href=" + getPageLink("server", "") + "&server=" + java.net.URLEncoder.encode(s9) + s11 + "&returnURL=" + java.net.URLEncoder.encode(request.rawURL) + "&noremote=" + s12 + "&noNTRemote=" + s14 + ">choose server</a>" + "</TD></TR><TR><TD ALIGN=\"left\" VALIGN=\"top\"><FONT SIZE=-1>" + s2 + "</FONT></TD></TR>" + "</TABLE></TD><TD><I>" + s16 + "</I></TD></TR>");
                } else
                if(flag3)
                {
                    HTMLPage.append("<TR><TD align=\"right\" valign=\"top\">" + s4 + " </TD>");
                    HTMLPage.append("<TD><TABLE><TR><TD ALIGN=\"left\" VALIGN=\"top\"><INPUT TYPE=\"checkbox\" NAME=\"" + s1 + "\"" + (s3.length() <= 0 ? "" : " CHECKED") + "></TD></TR>");
                    HTMLPage.append("<tr><TD ALIGN=\"left\" VALIGN=\"top\">" + s2 + "</td></tr></TD></TABLE>\n");
                    HTMLPage.append("</TD>");
                    HTMLPage.append("</TR>\n");
                } else
                if(flag1)
                {
                    java.lang.String s6 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_scalarValues");
                    java.lang.String as2[] = s6.split(",");
                    if(s6 != null)
                    {
                        HTMLPage.append("<TR><TD align=\"right\" valign=\"top\">" + s4 + " </TD>");
                        HTMLPage.append("<TD><TABLE><TR><TD ALIGN=\"left\" VALIGN=\"top\"><SELECT NAME=\"" + s1 + "\" SIZE=1 >");
                        for(int j = 1; j < as2.length; j += 2)
                        {
                            java.lang.String s13 = as2[j - 1];
                            java.lang.String s15 = as2[j];
                            HTMLPage.append("<option value=\"" + s15 + "\">" + s13 + " </option> \n");
                        }

                        HTMLPage.append("</INPUT></TD></TR>");
                        HTMLPage.append("<tr><TD ALIGN=\"left\" VALIGN=\"top\">" + s2 + "</td></tr></TD></TABLE>\n");
                        HTMLPage.append("</TD>");
                        HTMLPage.append("</TR>\n");
                    }
                } else
                {
                    HTMLPage.append("<TR><TD align=\"right\" valign=\"top\">" + s4 + " </TD>");
                    java.lang.String s7 = "TEXT";
                    if(s1.toUpperCase().indexOf("ASSWORD") >= 0)
                    {
                        s7 = "PASSWORD";
                    }
                    HTMLPage.append("<TD><TABLE><TR><TD ALIGN=\"left\" VALIGN=\"top\"><INPUT TYPE=\"").append(s7).append("\" NAME=\"" + s1 + "\" VALUE=\"" + s3 + "\" SIZE=50></TD></TR>");
                    HTMLPage.append("<tr><TD ALIGN=\"left\" VALIGN=\"top\">" + s2 + "</td></tr></TD></TABLE>\n");
                    HTMLPage.append("</TD>");
                    HTMLPage.append("</TR>\n");
                }
                HTMLPage.append("<INPUT TYPE=hidden name=\"" + s1 + "remotes\" value=\"other\">");
                continue;
            }
            HTMLPage.append("<TR>");
            HTMLPage.append("<TD>" + s1 + "</TD>");
            HTMLPage.append("<TD>" + s2 + "</TD>");
            java.lang.String s8 = "TEXT";
            if(s1.toUpperCase().indexOf("ASSWORD") >= 0)
            {
                s8 = "PASSWORD";
            }
            HTMLPage.append("<TD><INPUT TYPE=\"").append(s8).append("\" NAME=\"" + s1 + "\" VALUE=\"" + s3 + "\" SIZE=50>");
            HTMLPage.append("or <select size=1 name=" + s1 + "remotes>" + s + "</select>");
            HTMLPage.append("</TD>\n");
            HTMLPage.append("<TD>");
            java.lang.String s10 = "";
            if(as1 != null)
            {
                for(int k = 0; k < as1.length; k++)
                {
                    HTMLPage.append(s10 + as1[k]);
                    s10 = ",";
                }

            }
            HTMLPage.append("</TD>");
            HTMLPage.append("</TR>\n");
        }

    }

    protected java.lang.String getDisplayVariable(java.lang.String s)
    {
        int i = s.indexOf('$') + 1;
        if(i < 0)
        {
            return s;
        }
        java.lang.String s1 = s.substring(i, s.length() - 1);
        int j = s1.indexOf(positionDelimiter);
        if(j > 0)
        {
            return s1.substring(0, j);
        } else
        {
            return s1;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param as
     * @return
     */
    protected java.lang.String[] sortVars(java.lang.String as[])
    {
        java.lang.String[] as1 = new java.lang.String[as.length];
        
        int j;
        for (int i = 0; i < as.length; i ++)
        {
            String s = as[i];
            j = s.indexOf(positionDelimiter);
            if(j > 0)
            {
                try
                {
                    int k = java.lang.Integer.parseInt(s.substring(j + 1, s.length() - 1));
                    if(k < 0 || k > as.length - 1 || as1[k] != null)
                    {
                        return as;
                    }
                    as1[k] = s;
                }
                catch(java.lang.Exception exception)
                {
                    return as;
                }
            }
            else {
                return as;
            }
        }
        
        return as1;
    }

    protected void setHelpLink(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate)
    {
        java.lang.String s = monitorsettemplate.getSetting("_helpFile");
        if(s.length() > 0)
        {
            helpPage = s;
        }
    }

    protected java.lang.String getTemplateFilePath(java.lang.String s)
    {
        java.lang.String s1;
        if(request.getValue("solution").length() > 0)
        {
            s1 = SOLUTIONS_DIR + java.io.File.separator + s;
        } else
        {
            s1 = TEMPLATES_DIR + java.io.File.separator + s;
        }
        return s1;
    }

    COM.dragonflow.Page.SSrtn checkSetParams()
        throws java.lang.Exception
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s = request.getValue("templatefile");
        java.lang.String s1 = request.getValue("group");
        boolean flag = request.getValue("solution").length() > 0;
        java.lang.String s2 = getTemplateFilePath(s);
        COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s2);
        setHelpLink(monitorsettemplate);
        java.lang.String s3 = monitorsettemplate.getName();
        java.lang.String s4 = monitorsettemplate.getSetting("_propertyDisplayFilter");
        boolean flag1 = s4.length() > 0;
        java.lang.String as[] = new java.lang.String[0];
        if(flag1)
        {
            as = s4.split(",");
        }
        java.lang.String s5 = monitorsettemplate.getSetting("_propertyReplace");
        boolean flag2 = s5.length() > 0;
        java.lang.String as1[][] = new java.lang.String[0][0];
        if(flag2)
        {
            java.lang.String as2[] = s5.split(",");
            as1 = new java.lang.String[as2.length][];
            for(int i = 0; i < as2.length; i++)
            {
                java.lang.String s6 = as2[i];
                java.lang.String as3[] = s6.split("=");
                if(as3.length == 2)
                {
                    as1[i] = as3;
                }
            }

        }
        HTMLPage.append("<p><h3>Property and Syntax Check for " + (flag ? "Solution:" : "Template: ") + s3 + "</h3>\n");
        jgl.HashMap hashmap = populateRegularVariables(monitorsettemplate, true);
        jgl.HashMap hashmap1 = populateForeachVariables();
        monitorsettemplate.replaceAllVariables(hashmap, hashmap1);
        int j = monitorsettemplate.getMonitorCount();
        boolean flag3 = false;
        if(flag)
        {
            for(int k = 0; k < j; k++)
            {
                jgl.HashMap hashmap2 = monitorsettemplate.getNthMonitor(k);
                ssrtn = checkMonitorParams(s1, hashmap2);
                if(ssrtn.isErrorList())
                {
                    flag3 = true;
                }
            }

            if(flag3)
            {
                HTMLPage.append("<P><b>Errors were found with this Solution set. The errors should be corrected before creating these monitors otherwise invalid monitors may be created.</b>\n");
            } else
            {
                HTMLPage.append("<p>No errors detected in " + (flag ? "Solution Template" : "Monitor Set") + " syntax. Click 'Create' button at bottom of page to create the monitors with these settings. <P>\n");
            }
            HTMLPage.append("<hr>");
        }
        for(int l = 0; l < j; l++)
        {
            jgl.HashMap hashmap3 = monitorsettemplate.getNthMonitor(l);
            java.lang.String s8 = COM.dragonflow.Utils.TextUtils.getValue(hashmap3, "_class");
            java.lang.String s10 = COM.dragonflow.Utils.TextUtils.getValue(hashmap3, "_name");
            java.lang.String s11 = COM.dragonflow.Utils.TextUtils.getValue(hashmap3, "_monitorDescription");
            if(doNotDeployMonitor(hashmap3))
            {
                continue;
            }
            HTMLPage.append("<P><font size=\"+1\">Monitor Type:<b> " + s8 + "</b>  &nbsp;&nbsp;&nbsp;  Monitor Name:<b> " + s10 + "</b></font></p>\n");
            if(s11.length() > 0)
            {
                HTMLPage.append("<p>Monitor Description: <b> " + s11 + "</b></p>");
            }
            HTMLPage.append("<TABLE BORDER=1 CELLSPACING=0 WIDTH=\"100%\">\n");
            HTMLPage.append("<TR><TH width=\"20%\">Property</TH><TH width=\"30%\">Value</TH><TH width=\"50%\"> Property or Syntax Errors</TH></TR>\n");
            java.util.Enumeration enumeration2 = hashmap3.keys();
            do
            {
                if(!enumeration2.hasMoreElements())
                {
                    break;
                }
                java.lang.String s12 = (java.lang.String)enumeration2.nextElement();
                if(s12.equals("_class") || s12.equals("_id") || s12.equals("_group"))
                {
                    continue;
                }
                if(flag1)
                {
                    boolean flag4 = true;
                    for(int i1 = 0; i1 < as.length; i1++)
                    {
                        java.lang.String s13 = as[i1];
                        if(s12.indexOf(s13) >= 0)
                        {
                            flag4 = false;
                        }
                    }

                    if(!flag4)
                    {
                        continue;
                    }
                }
                jgl.Array array = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap3, s12);
                java.lang.StringBuffer stringbuffer = new StringBuffer();
                for(int j1 = 0; j1 < array.size(); j1++)
                {
                    if(j1 > 0)
                    {
                        stringbuffer.append("<br>");
                    }
                    stringbuffer.append((java.lang.String)array.at(j1));
                }

                java.lang.String s14 = "BGCOLOR=\"#DDDDDD\"";
                if(monitorsettemplate.didReplacement(l, s12))
                {
                    if(flag)
                    {
                        s14 = "BGCOLOR=\"#557755\"";
                    } else
                    {
                        s14 = "BGCOLOR=\"#007700\"";
                    }
                }
                java.lang.String s16 = stringbuffer.toString();
                if(stringbuffer.toString().matches("remote:\\d+"))
                {
                    s16 = COM.dragonflow.SiteView.Machine.getMachineName(stringbuffer.toString());
                }
                if(flag2)
                {
                    for(int k1 = 0; k1 < as1.length; k1++)
                    {
                        java.lang.String as4[] = as1[k1];
                        if(as4.length == 2 && s12.indexOf(as4[0]) >= 0)
                        {
                            s12 = s12.replaceAll(as4[0], as4[1]);
                        }
                    }

                }
                if(flag)
                {
                    s12 = s12.replaceAll("_", " ");
                }
                HTMLPage.append("<TR><TD>" + s12 + "</TD><TD " + s14 + ">" + s16 + "</TD><TD>&nbsp;</TR>\n");
            } while(true);
            HTMLPage.append("<P>\n");
            ssrtn = checkMonitorParams(s1, hashmap3);
            if(ssrtn.isErrorList())
            {
                jgl.HashMap hashmap5 = ssrtn.getErrorList();
                for(java.util.Enumeration enumeration3 = hashmap5.keys(); enumeration3.hasMoreElements();)
                {
                    java.lang.Object obj = enumeration3.nextElement();
                    java.lang.String s15 = (java.lang.String)hashmap5.get(obj);
                    java.lang.String s17;
                    if(obj instanceof COM.dragonflow.Properties.StringProperty)
                    {
                        s17 = ((COM.dragonflow.Properties.StringProperty)obj).getName();
                    } else
                    {
                        s17 = (java.lang.String)obj;
                    }
                    HTMLPage.append("<TR><TD>" + s17 + "</TD><TD>&nbsp;</TD>" + "<TD BGCOLOR=\"#DD0000\">" + s15 + "</TD></TR>\n");
                    flag3 = true;
                }

            }
            HTMLPage.append("</TABLE>\n");
            if(ssrtn.isError())
            {
                HTMLPage.append("<P><B>Errors found with this monitor:<br>\n");
                HTMLPage.append(ssrtn.errormsg() + ": " + ssrtn.message() + "<br>\n");
                flag3 = true;
            }
        }

        if(!flag)
        {
            if(flag3)
            {
                HTMLPage.append("<P><b>Errors were found with this monitor set. The errors should be corrected before creating these monitors otherwise invalid monitors may be created.</b>\n");
            } else
            {
                HTMLPage.append("<p>No errors detected in Monitor Set syntax. Click 'Create' button to create the monitors with these settings. <P>\n");
            }
        }
        HTMLPage.append("<FORM ACTION=/SiteView/cgi/go.exe/SiteView method=POST>\n<input type=hidden name=page value=\"" + getNextPage(request.getValue("operation")) + "\">\n" + "<input type=hidden name=operation value=" + "monitorSetCreate" + " >\n" + "<input type=hidden name=account value= \"" + request.getAccount() + "\">\n" + "<input type=hidden name=group value= \"" + s1 + "\">\n" + "<input type=hidden name=" + "solution" + " value= \"" + request.getValue("solution") + "\">\n" + "<input type=hidden name=templatefile value= \"" + s + "\">\n");
        java.lang.String s7;
        java.lang.String s9;
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); HTMLPage.append("<input type=hidden name=\"" + s7 + "\" value=\"" + s9 + "\">\n"))
        {
            s7 = (java.lang.String)enumeration.nextElement();
            s9 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s7);
        }

        jgl.HashMap hashmap4;
        for(java.util.Enumeration enumeration1 = hashmap1.elements(); enumeration1.hasMoreElements(); HTMLPage.append("<input type=hidden name=\"" + (java.lang.String)hashmap4.get("name") + "\" value=\"" + (java.lang.String)hashmap4.get("value") + "\">\n"))
        {
            hashmap4 = (jgl.HashMap)enumeration1.nextElement();
        }

        HTMLPage.append("<BR><input type=submit value=Create>" + (flag ? " Solution" : " Monitor Set") + "\n<P>\n");
        HTMLPage.append("\n</FORM>");
        return ssrtn;
    }

    protected java.lang.String getNextPage(java.lang.String s)
    {
        return thisPageName;
    }

    protected jgl.HashMap populateForeachVariables()
    {
        jgl.HashMap hashmap = new HashMap(true);
        java.util.Enumeration enumeration = request.variables.keys();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            java.util.regex.Matcher matcher = FOREACH_VARNAME_PATTERN.matcher(s);
            if(matcher.matches())
            {
                jgl.HashMap hashmap1 = new HashMap();
                java.lang.String s1 = matcher.group(1).replaceAll(" ", "");
                java.lang.String s2 = request.getValue(s);
                hashmap1.put("name", s);
                hashmap1.put("value", s2);
                hashmap.add(s1, hashmap1);
            }
        } while(true);
        return hashmap;
    }

    protected boolean doNotDeployMonitor(jgl.HashMap hashmap)
    {
        if(hashmap.get("_deployControlVar") != null)
        {
            if(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_deployControlVar").length() == 0)
            {
                return true;
            }
            hashmap.remove("_deployControlVar");
        }
        return false;
    }

    COM.dragonflow.Page.SSrtn createSet()
        throws java.lang.Exception
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s = COM.dragonflow.Utils.I18N.toDefaultEncoding(request.getValue("group"));
        java.lang.String s1 = request.getValue("templatefile");
        java.lang.String s2 = request.getValue("debug");
        boolean flag = s2.length() > 0;
        boolean flag1 = request.getValue("solution").length() > 0;
        java.lang.String s3 = getTemplateFilePath(s1);
        COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s3);
        setHelpLink(monitorsettemplate);
        java.lang.String s4 = monitorsettemplate.getName();
        HTMLPage.append("<p><h3>Create " + (flag1 ? "Solution Set for " : "Monitor Set for template: ") + s4 + (flag1 ? "..." : "") + "</h3>");
        jgl.HashMap hashmap = populateRegularVariables(monitorsettemplate, false);
        jgl.HashMap hashmap1 = populateForeachVariables();
        monitorsettemplate.replaceAllVariables(hashmap, hashmap1);
        if(!flag1)
        {
            HTMLPage.append("</p><p>Creating Monitor Configurations...<p>");
        }
        int i = monitorsettemplate.getMonitorCount();
        for(int j = 0; j < i; j++)
        {
            jgl.HashMap hashmap2 = monitorsettemplate.getNthMonitor(j);
            if(doNotDeployMonitor(hashmap2))
            {
                continue;
            }
            hashmap2.remove("_internalId");
            java.lang.String s6 = COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "_class");
            java.lang.String s7 = COM.dragonflow.Utils.TextUtils.getValue(hashmap2, "_name");
            HTMLPage.append("<p>Creating Monitor: " + s6 + ": " + s7 + " ... ");
            if(flag)
            {
                java.util.Enumeration enumeration = hashmap2.keys();
                do
                {
                    if(!enumeration.hasMoreElements())
                    {
                        break;
                    }
                    java.lang.String s8 = (java.lang.String)enumeration.nextElement();
                    if(!s8.equals("_class") && !s8.equals("_id") && !s8.equals("_group"))
                    {
                        jgl.Array array = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap2, s8);
                        java.lang.StringBuffer stringbuffer = new StringBuffer();
                        for(int k = 0; k < array.size(); k++)
                        {
                            if(k > 0)
                            {
                                stringbuffer.append("<br>");
                            }
                            stringbuffer.append((java.lang.String)array.at(k));
                        }

                        HTMLPage.append(s8 + ": " + stringbuffer + "<br>\n");
                    }
                } while(true);
                HTMLPage.append("<P>\n");
            }
            try
            {
                ssrtn = createMonitor(s, hashmap2);
            }
            catch(java.lang.Exception exception)
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_Exception, "Exception: " + exception);
            }
            if(ssrtn.isError())
            {
                return ssrtn;
            }
            HTMLPage.append("Successfully created monitor. Check group page for status.<br></p>\n");
        }

        COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s);
        java.lang.String s5 = "";
        if(request.getValue("refreshURL").length() > 0)
        {
            s5 = "/SiteView/cgi/go.exe/SiteView?page=" + request.getValue("refreshURL") + "&account=" + request.getAccount();
            s = "Previous";
        } else
        {
            s5 = COM.dragonflow.Page.CGI.getGroupDetailURL(request, s);
        }
        HTMLPage.append("<HR><A HREF=" + s5 + ">Return to " + s + "</A><P>");
        return ssrtn;
    }

    protected java.lang.String replaceBoolean(java.lang.String s, COM.dragonflow.Page.monitorSetTemplate monitorsettemplate)
    {
        java.lang.String s1 = request.getValue(s);
        jgl.HashMap hashmap = monitorsettemplate.getVariableInfo(s);
        if(hashmap.get("_boolean") != null)
        {
            java.lang.String s2 = "";
            if(s1.length() > 0)
            {
                s2 = (java.lang.String)hashmap.get("_onTrue");
            } else
            {
                s2 = (java.lang.String)hashmap.get("_onFalse");
            }
            monitorsettemplate.replaceVariable("BOOLEAN[" + s + "]", s2);
        }
        return s1;
    }

    public java.lang.String[] getAvailableTemplates(java.lang.String s, java.lang.String s1)
    {
        java.io.File file = new File(s);
        java.lang.String as[];
        if(file.exists())
        {
            COM.dragonflow.Page.monitorSetFilter monitorsetfilter = new monitorSetFilter(s1);
            as = file.list(monitorsetfilter);
        } else
        {
            as = null;
        }
        return as;
    }

    public java.lang.String[] getAvailableTemplates()
    {
        return getAvailableTemplates(TEMPLATES_DIR, COM.dragonflow.Page.monitorSetTemplate.fileSuffix);
    }

    public java.lang.String[] getTemplateNames(java.lang.String as[])
    {
        return getTemplateNames(as, TEMPLATES_DIR);
    }

    public java.lang.String[] getTemplateNames(java.lang.String as[], java.lang.String s)
    {
        java.lang.String as1[] = new java.lang.String[as.length];
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = s + java.io.File.separator + as[i];
            COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s1);
            as1[i] = monitorsettemplate.getName();
        }

        return as1;
    }

    public java.lang.String[] getTemplateDescriptions(java.lang.String as[], java.lang.String s)
    {
        java.lang.String as1[] = new java.lang.String[as.length];
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = s + java.io.File.separator + as[i];
            COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s1);
            as1[i] = monitorsettemplate.getSetDescriptor();
        }

        return as1;
    }

    public java.lang.String[] getTemplateMoreInfo(java.lang.String as[], java.lang.String s)
    {
        java.lang.String as1[] = new java.lang.String[as.length];
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = s + java.io.File.separator + as[i];
            COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s1);
            as1[i] = monitorsettemplate.getSetting("_monitorTemplateMoreInfo");
        }

        return as1;
    }

    public java.lang.String[] getTemplateSolutionPages(java.lang.String as[], java.lang.String s)
    {
        java.lang.String as1[] = new java.lang.String[as.length];
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s1 = s + java.io.File.separator + as[i];
            COM.dragonflow.Page.monitorSetTemplate monitorsettemplate = new monitorSetTemplate(s1);
            as1[i] = monitorsettemplate.getSetting("_solutionSetPage");
            if(as1[i].length() == 0)
            {
                as1[i] = thisPageName;
            }
        }

        return as1;
    }

    public java.lang.String[] getTemplateDescriptions(java.lang.String as[])
    {
        return getTemplateDescriptions(as, TEMPLATES_DIR);
    }

    public java.lang.String[] getTemplateDescriptions(java.lang.String s, java.lang.String s1)
    {
        return getTemplateDescriptions(new java.lang.String[] {
            s
        }, s1);
    }

    boolean checkPermissions(java.lang.String s, jgl.HashMap hashmap, COM.dragonflow.SiteView.AtomicMonitor atomicmonitor, COM.dragonflow.Page.SSrtn ssrtn)
        throws java.lang.Exception
    {
        java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
        java.lang.String s2 = request.getPermission("_monitorType", s1);
        if(s2.equals("optional"))
        {
            ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonNotAvailable, "This monitor cannot be part of this monitor set");
            return false;
        }
        COM.dragonflow.SiteView.SiteViewObject siteviewobject = COM.dragonflow.SiteView.Portal.getSiteViewForID(s);
        COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor)siteviewobject.getElement(s);
        if(COM.dragonflow.Utils.TextUtils.toInt(s2) > 0)
        {
            int i = monitor.countMonitorsOfClass(s1);
            if(i >= COM.dragonflow.Utils.TextUtils.toInt(s2))
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonTooManyClass, "This monitor cannot be part of this monitor set");
                return false;
            }
        }
        int j = request.getPermissionAsInteger("_maximumMonitors");
        if(j > 0)
        {
            int k = monitor.countMonitors();
            if(k >= j)
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonTooManyGroup, "This monitor cannot be part of this monitor set");
                return false;
            }
        }
        if(COM.dragonflow.Utils.LUtils.wouldExceedLimit(atomicmonitor))
        {
            ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonTooManyLicense, "This monitor cannot be part of this monitor set");
            return false;
        }
        if(!COM.dragonflow.Utils.LUtils.isMonitorTypeAllowed(atomicmonitor))
        {
            ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonTooManyClass, "This monitor cannot be part of this monitor set");
            return false;
        }
        java.lang.String s3 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_getImages");
        java.lang.String s4 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_getFrames");
        if((s3.equals("on") || s4.equals("on")) && s1.startsWith("URLRemote") && request.isSiteSeerAccount())
        {
            int l = request.getPermissionAsInteger("_maximumFAndIMonitors");
            if(COM.dragonflow.SiteView.monitorUtils.countFrameAndImageMonitors(s) > l)
            {
                ssrtn.setError(COM.dragonflow.Page.SSrtn.ERR_MonTooManyFAndI, "This monitor cannot be part of this monitor set");
                return false;
            }
        }
        return true;
    }

    COM.dragonflow.Page.SSrtn createMonitor(java.lang.String s, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
        jgl.HashMap hashmap1 = new HashMap();
        if(s1.indexOf("SubGroup") == -1)
        {
            COM.dragonflow.SiteView.AtomicMonitor atomicmonitor = COM.dragonflow.SiteView.AtomicMonitor.MonitorCreate(s1);
            if(!checkPermissions(s, hashmap, atomicmonitor, ssrtn))
            {
                return ssrtn;
            }
            int i = request.getPermissionAsInteger("_minimumFrequency");
            long l = atomicmonitor.getPropertyAsLong(COM.dragonflow.SiteView.AtomicMonitor.pFrequency);
            java.lang.Object obj = atomicmonitor.getClassProperty("defaultFrequency");
            if(obj instanceof java.lang.String)
            {
                long l1 = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)obj);
                if(l1 > 0L)
                {
                    l = l1;
                }
            }
            if(i > 0 && l < (long)i)
            {
                l = i;
            }
            atomicmonitor.setProperty(COM.dragonflow.SiteView.AtomicMonitor.pFrequency, l);
            java.lang.String s6 = atomicmonitor.defaultTitle();
            jgl.HashMap hashmap4 = new HashMap();
            if(request.hasValue(COM.dragonflow.SiteView.ServerMonitor.pMachineName.getName()))
            {
                atomicmonitor.setProperty(COM.dragonflow.SiteView.ServerMonitor.pMachineName, request.getValue(COM.dragonflow.SiteView.ServerMonitor.pMachineName.getName()));
            }
            jgl.Array array2 = atomicmonitor.getProperties();
            array2 = COM.dragonflow.Properties.StringProperty.sortByOrder(array2);
            for(java.util.Enumeration enumeration = array2.elements(); enumeration.hasMoreElements();)
            {
                COM.dragonflow.Properties.StringProperty stringproperty = (COM.dragonflow.Properties.StringProperty)enumeration.nextElement();
                java.lang.String s7 = stringproperty.getName();
                if(stringproperty.isMultiLine)
                {
                    jgl.Array array3 = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, stringproperty.getName());
                    atomicmonitor.unsetProperty(stringproperty);
                    int k = 0;
                    while(k < array3.size()) 
                    {
                        java.lang.String s11 = (java.lang.String)array3.at(k);
                        s11 = atomicmonitor.verify(stringproperty, s11, request, hashmap4);
                        atomicmonitor.addProperty(stringproperty, s11);
                        k++;
                    }
                } else
                {
                    java.lang.String s9 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s7);
                    if(i > 0 && (stringproperty instanceof COM.dragonflow.Properties.FrequencyProperty))
                    {
                        int i1 = COM.dragonflow.Utils.TextUtils.toInt(s9);
                        if(i1 != 0 && i1 < i)
                        {
                            hashmap4.put(stringproperty, "For this account, monitors must run at intervals of " + COM.dragonflow.Utils.TextUtils.secondsToString(i) + " or more.");
                        }
                    }
                    if((stringproperty instanceof COM.dragonflow.Properties.ScalarProperty) && ((COM.dragonflow.Properties.ScalarProperty)stringproperty).multiple)
                    {
                        jgl.Array array4 = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, stringproperty.getName());
                        atomicmonitor.unsetProperty(stringproperty);
                        int j1 = 0;
                        while(j1 < array4.size()) 
                        {
                            java.lang.String s13 = (java.lang.String)array4.at(j1);
                            s13 = atomicmonitor.verify(stringproperty, s13, request, hashmap4);
                            atomicmonitor.addProperty(stringproperty, s13);
                            j1++;
                        }
                    } else
                    {
                        if(stringproperty == COM.dragonflow.SiteView.AtomicMonitor.pName)
                        {
                            if(s9.equals(s6))
                            {
                                atomicmonitor.setProperty(stringproperty, "");
                            } else
                            {
                                atomicmonitor.setProperty(stringproperty, s9);
                            }
                        }
                        atomicmonitor.setProperty(stringproperty, s9);
                    }
                }
            }

            jgl.HashMap hashmap5 = getMasterConfig();
            java.util.Enumeration enumeration1 = hashmap5.values("_monitorEditCustom");
            do
            {
                if(!enumeration1.hasMoreElements())
                {
                    break;
                }
                java.lang.String s8 = (java.lang.String)enumeration1.nextElement();
                java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s8, "|");
                java.lang.String s10 = as[0];
                if(s10.length() > 0)
                {
                    if(!s10.startsWith("_"))
                    {
                        s10 = "_" + s10;
                    }
                    java.lang.String s12 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s10);
                    s12 = s12.replace('\r', ' ');
                    s12 = s12.replace('\n', ' ');
                    atomicmonitor.setProperty(s10, s12);
                }
            } while(true);
            COM.dragonflow.SiteView.AtomicMonitor.saveThresholds(atomicmonitor, hashmap, hashmap4);
            COM.dragonflow.SiteView.AtomicMonitor.saveClassifier(atomicmonitor, hashmap, hashmap4);
            COM.dragonflow.SiteView.AtomicMonitor.saveCustomProperties(getMasterConfig(), atomicmonitor, request);
            if(atomicmonitor.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pName).length() == 0)
            {
                atomicmonitor.setProperty(COM.dragonflow.SiteView.AtomicMonitor.pName, atomicmonitor.defaultTitle());
            }
            hashmap1 = atomicmonitor.getValuesTable();
        } else
        {
            java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_name");
            java.lang.String s3 = "";
            if(s2.indexOf(' ') != -1)
            {
                s3 = COM.dragonflow.Utils.TextUtils.replaceChar(s2, ' ', "_");
            } else
            {
                s3 = s2;
            }
            hashmap1.put("_class", s1);
            hashmap1.put("_group", s3);
            hashmap1.put("_name", s2);
            hashmap1.put("_id", "");
            jgl.Array array1 = new Array();
            jgl.HashMap hashmap2 = new HashMap();
            hashmap2.put("_name", s2);
            hashmap2.put("_parent", s);
            hashmap2.put("_dependsCondition", "good");
            hashmap2.put("_nextID", "1");
            array1.add(hashmap2);
            try
            {
                COM.dragonflow.Properties.FrameFile.writeToFile(COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "groups" + java.io.File.separator + COM.dragonflow.Utils.TextUtils.getValue(hashmap1, "_group") + ".mg", array1);
            }
            catch(java.lang.Exception exception)
            {
                java.lang.System.out.println(exception + "An error occurred when trying to write the file: " + COM.dragonflow.Utils.TextUtils.getValue(hashmap1, "_group"));
            }
        }
        jgl.Array array = ReadGroupFrames(s);
        java.lang.String s4 = "";
        int j = array.size();
        jgl.HashMap hashmap3 = (jgl.HashMap)array.at(0);
        s4 = COM.dragonflow.Utils.TextUtils.getValue(hashmap3, "_nextID");
        if(s4.length() == 0)
        {
            s4 = "1";
        }
        hashmap1.remove(COM.dragonflow.SiteView.Monitor.pID);
        hashmap1.remove("_id");
        hashmap1.put("_id", s4);
        array.insert(j++, hashmap1);
        java.lang.String s5 = COM.dragonflow.Utils.TextUtils.increment(s4);
        hashmap3.put("_nextID", s5);
        WriteGroupFrames(s, array);
        return ssrtn;
    }

    COM.dragonflow.Page.SSrtn checkMonitorParams(java.lang.String s, jgl.HashMap hashmap)
        throws java.lang.Exception
    {
        COM.dragonflow.Page.SSrtn ssrtn = new SSrtn();
        java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_class");
        java.lang.String s2;
        if(s1.indexOf("SubGroup") == -1)
        {
            COM.dragonflow.SiteView.AtomicMonitor atomicmonitor = COM.dragonflow.SiteView.AtomicMonitor.MonitorCreate(s1);
            if(!checkPermissions(s, hashmap, atomicmonitor, ssrtn))
            {
                return ssrtn;
            }
            int i = request.getPermissionAsInteger("_minimumFrequency");
            long l = atomicmonitor.getPropertyAsLong(COM.dragonflow.SiteView.AtomicMonitor.pFrequency);
            java.lang.Object obj = atomicmonitor.getClassProperty("defaultFrequency");
            if(obj instanceof java.lang.String)
            {
                long l1 = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)obj);
                if(l1 > 0L)
                {
                    l = l1;
                }
            }
            if(i > 0 && l < (long)i)
            {
                l = i;
            }
            atomicmonitor.setProperty(COM.dragonflow.SiteView.AtomicMonitor.pFrequency, l);
            jgl.HashMap hashmap1 = new HashMap();
            ssrtn.setErrorList(hashmap1);
            if(request.hasValue(COM.dragonflow.SiteView.ServerMonitor.pMachineName.getName()))
            {
                atomicmonitor.setProperty(COM.dragonflow.SiteView.ServerMonitor.pMachineName, request.getValue(COM.dragonflow.SiteView.ServerMonitor.pMachineName.getName()));
            }
            jgl.Array array = atomicmonitor.getProperties();
            array = COM.dragonflow.Properties.StringProperty.sortByOrder(array);
            java.util.Enumeration enumeration = array.elements();
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                COM.dragonflow.Properties.StringProperty stringproperty = (COM.dragonflow.Properties.StringProperty)enumeration.nextElement();
                if(stringproperty.isMultiLine)
                {
                    jgl.Array array1 = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, stringproperty.getName());
                    int j = 0;
                    while(j < array1.size()) 
                    {
                        java.lang.String s5 = (java.lang.String)array1.at(j);
                        s5 = atomicmonitor.verify(stringproperty, s5, request, hashmap1);
                        atomicmonitor.addProperty(stringproperty, s5);
                        j++;
                    }
                } else
                {
                    java.lang.String s3 = stringproperty.getName();
                    java.lang.String s4 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s3);
                    if((stringproperty instanceof COM.dragonflow.Properties.ScalarProperty) && ((COM.dragonflow.Properties.ScalarProperty)stringproperty).multiple)
                    {
                        jgl.Array array2 = COM.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, stringproperty.getName());
                        for(int i1 = 0; i1 < array2.size(); i1++)
                        {
                            java.lang.String s6 = (java.lang.String)array2.at(i1);
                            s6 = atomicmonitor.verify(stringproperty, s6, request, hashmap1);
                            atomicmonitor.addProperty(stringproperty, s6);
                        }

                    } else
                    {
                        s4 = atomicmonitor.verify(stringproperty, s4, request, hashmap1);
                        atomicmonitor.addProperty(stringproperty, s4);
                    }
                    if(i > 0 && (stringproperty instanceof COM.dragonflow.Properties.FrequencyProperty))
                    {
                        int k = COM.dragonflow.Utils.TextUtils.toInt(s4);
                        if(k != 0 && k < i)
                        {
                            hashmap1.put(stringproperty, "For this account, monitors must run at intervals of " + COM.dragonflow.Utils.TextUtils.secondsToString(i) + " or more.");
                        }
                    }
                }
            } while(true);
            COM.dragonflow.SiteView.AtomicMonitor.checkThresholds(hashmap, hashmap1);
        } else
        {
            s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_group");
        }
        return ssrtn;
    }

    protected jgl.HashMap populateRegularVariables(COM.dragonflow.Page.monitorSetTemplate monitorsettemplate, boolean flag)
    {
        java.lang.String as[] = monitorsettemplate.getVariables();
        jgl.HashMap hashmap = new HashMap();
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s = request.getValue(as[i]);
            if(flag && s.length() <= 0 && !request.getValue(as[i] + "remotes").equals("other"))
            {
                java.lang.String s1 = request.getValue(as[i] + "remotes");
                s = "remote:" + s1;
            }
            hashmap.add(as[i], s);
        }

        return hashmap;
    }

    static 
    {
        TEMPLATES_DIR = COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.sets";
        SOLUTIONS_DIR = COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.solutions";
    }
}
