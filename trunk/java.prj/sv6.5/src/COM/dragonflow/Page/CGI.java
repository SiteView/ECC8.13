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

import java.io.IOException;
import java.util.Date;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import jgl.LessString;
import COM.dragonflow.HTTP.HTTPRequest;
import COM.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package COM.dragonflow.Page:
// treeControl

public abstract class CGI {
    public static class menuItems {

        private java.lang.String menuLabel;

        private java.lang.String menuLink;

        private java.lang.String opLink;

        private java.lang.String linkClass;

        private java.lang.String toolTip;

        public menuItems(java.lang.String s, java.lang.String s1,
                java.lang.String s2, java.lang.String s3, java.lang.String s4) {
            menuLabel = "";
            menuLink = "";
            opLink = "";
            linkClass = "";
            toolTip = "";
            menuLabel = s;
            menuLink = s1;
            opLink = s2;
            linkClass = s3;
            toolTip = s4;
        }
    }

    public static class menus extends jgl.Array {

        public menus() {
            add(new menuItems("Multi-view", "overview", "", "script",
                    "Open the SiteView Multi-view Window"));
            add(new menuItems("Manage Monitors/Groups", "manage", "", "page",
                    "Manage Monitors and Groups"));
        }
    }

    java.lang.String args[];

    public COM.dragonflow.HTTP.HTTPRequest request;

    public java.io.PrintWriter outputStream;

    protected boolean autoFollowPortalRefresh;

    public static java.lang.String nocacheHeader = "<meta http-equiv=\"Expires\" content=\"0\">\n<meta http-equiv=\"Pragma\" content=\"no-cache\">\n";

    public static java.lang.String CONTENT_REGEX = "/<!--CONTENTSTART-->(.*)<!--CONTENTEND-->/s";

    private jgl.HashMap privateConfigCache;

    private jgl.HashMap privateLocalConfigCache;

    private jgl.Array settingsArray;

    public static final int SHOW_MONITORS = 1;

    public static final int SHOW_GROUPS = 2;

    public static final int ADD_NONE_OPTION = 4;

    public static final int HIDE_GROUP_PREFIX = 8;

    public static final int ADD_TOP_LEVEL_OPTION = 16;

    public static final int REVERSE_MONITOR_SPEC = 32;

    public static final int SHOW_ALL_GROUPS = 64;

    public static final int SELECTED_FIRST = 128;

    public static final int SHOW_GROUPS_AND_MONITORS = 3;

    public static final boolean ALL_GROUPS = false;

    public static final boolean TOP_LEVEL_GROUPS = true;

    public CGI() {
        args = null;
        request = null;
        outputStream = null;
        autoFollowPortalRefresh = true;
        privateConfigCache = null;
        privateLocalConfigCache = null;
        settingsArray = null;
    }

    public abstract void printBody() throws java.lang.Exception;

    public void initialize(COM.dragonflow.HTTP.HTTPRequest httprequest,
            java.io.PrintWriter printwriter) {
        request = httprequest;
        outputStream = printwriter;
		
		/*��ʼ����request����*/
		System.out.println(request.queryString);
		
		java.util.Enumeration enum1=request.getVariables();
		while(enum1.hasMoreElements())
		{
			String key1=enum1.nextElement().toString();
			
			java.util.Enumeration enum2=request.getValues(key1);
			while(enum2.hasMoreElements())
			{
				System.out.println(key1+"="+enum2.nextElement());
			}
		}

		/*��������request����*/
    }

    public void printBody(java.io.PrintWriter printwriter)
            throws java.lang.Exception {
        outputStream = printwriter;
        printBody();
    }

    public void printFooter(java.io.PrintWriter printwriter) {
        COM.dragonflow.Page.CGI.printFooter(printwriter, request);
    }

    public static void printFooter(java.io.PrintWriter printwriter,
            java.lang.String s) {
        COM.dragonflow.Page.CGI.printFooter(printwriter, s, false);
    }

    public static void printFooter(java.io.PrintWriter printwriter,
            java.lang.String s, boolean flag) {
        COM.dragonflow.Page.CGI.printFooter(printwriter, s, flag, true);
    }

    public static void printFooter(java.io.PrintWriter printwriter,
            java.lang.String s, boolean flag, boolean flag1) {
        if (!COM.dragonflow.SiteView.Platform.isSiteSeerAccount(s)) {
            java.lang.String s1 = "";
            java.lang.String s3 = "SiteViewlogo.gif";
            if (COM.dragonflow.SiteView.Platform.isPortal()) {
                s3 = "SiteReliancelogo.gif";
            }
            java.lang.String s5 = "";
            if (flag) {
                s5 = s5 = "<p align=center><font size=-2>"
                        + COM.dragonflow.Utils.LocaleUtils.createLink(
                                COM.dragonflow.Utils.LocaleUtils
                                        .getResourceBundle().getString(
                                                "TermsAndConditions"), 1,
                                "/SiteView/license.html") + "</font>";
            }
            java.lang.String s7 = "";
            if (flag1) {
                s7 = "<center>" + COM.dragonflow.SiteView.Platform.companyLogo
                        + "</center>";
            }
            java.lang.String s8 = COM.dragonflow.SiteView.Platform.getVersion();
            printwriter
                    .println("<table class=fine border=0 cellspacing=0 width=500 align=center><tr><td><p class=fine align=center>"
                            + s7
                            + "<br>\n"
                            + "<small>"
                            + COM.dragonflow.SiteView.Platform.productName
                            + " "
                            + s8
                            + ", "
                            + "<p>"
                            + COM.dragonflow.SiteView.Platform.copyright
                            + s1
                            + "</small>"
                            + s5
                            + "</p></td></tr></table></BODY></HTML>");
        } else {
            java.lang.String s2 = "";
            if (flag1) {
                s2 = "<img src=http://www.dragonflow.com/images/common/dragonflow_logo.gif  width=\"184\" height=\"69\" border=\"\" alt=\""
                        + COM.dragonflow.SiteView.Platform.companyName
                        + "\"></a>\n";
            }
            java.lang.String s4 = "";
            if (flag) {
                s4 = s4 = "<p align=center><font size=-2>"
                        + COM.dragonflow.Utils.LocaleUtils.createLink(
                                COM.dragonflow.Utils.LocaleUtils
                                        .getResourceBundle().getString(
                                                "TermsAndConditions"), 1,
                                "/SiteView/license.html") + "</font>";
            }
            java.lang.String s6 = COM.dragonflow.SiteView.Platform.getVersion();
            printwriter
                    .println("<table class=fine border=0 cellspacing=0 width=\"100%\" align=center><tr><td><p class=fine align=center><a href="
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + ">"
                            + s2
                            + "<br><small>"
                            + COM.dragonflow.SiteView.Platform.productName
                            + " "
                            + s6
                            + "<br>"
                            + "<a href=\""
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + "\">dragonflow.com</a> | \n"
                            + "<a href=\"http://support.dragonflow.com\">Customer Support</a> | \n"
                            + "<a href=\""
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + "/company/contact_us/\">Contact Us</a> | \n"
                            + COM.dragonflow.SiteView.Platform.copyright
                            + "</small>"
                            + s4
                            + "</p>\n</center>\n</td></tr></table></BODY></HTML>");
        }
    }

    public static void printFooter(java.io.PrintWriter printwriter,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        COM.dragonflow.Page.CGI.printFooter(printwriter, httprequest, false);
    }

    jgl.Array _getUsedMonitorClasses() {
        jgl.Array array = new Array();
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        java.util.Enumeration enumeration = siteviewgroup.getGroupIDs()
                .elements();
        jgl.HashMap hashmap = new HashMap();
        while (enumeration.hasMoreElements()) {
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = COM.dragonflow.SiteView.SiteViewGroup
                    .currentSiteView().getGroup(
                            COM.dragonflow.Utils.I18N
                                    .toDefaultEncoding(enumeration
                                            .nextElement().toString()));
            java.util.Enumeration enumeration1 = monitorgroup.getMonitors();
            while (enumeration1.hasMoreElements()) {
                COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor) enumeration1
                        .nextElement();
                java.lang.String s = monitor.getClass().getName();
                s = s.substring(s.lastIndexOf(".") + 1);
                hashmap.put(s, "");
            }
        }
        array = COM.dragonflow.Utils.TextUtils.enumToArray(hashmap.keys());
        return array;
    }

    public static void printFooter(java.io.PrintWriter printwriter,
            COM.dragonflow.HTTP.HTTPRequest httprequest, boolean flag) {
        if (httprequest == null
                || !COM.dragonflow.SiteView.Platform
                        .isSiteSeerAccount(httprequest.getAccount())) {
            java.lang.String s = "";
            java.lang.String s2 = "SiteViewlogo.gif";
            if (COM.dragonflow.SiteView.Platform.isPortal()) {
                s2 = "SiteReliancelogo.gif";
            }
            if (httprequest != null) {
                java.lang.String s4 = httprequest.getPermission("_partner");
                if (s4.length() > 0) {
                    COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                            .currentSiteView();
                    COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup
                            .getElement(s4);
                    if (monitorgroup != null) {
                        s = monitorgroup.getProperty("_partnerCopyrightHTML");
                    }
                }
            }
            java.lang.String s5 = "";
            if (flag) {
                s5 = s5 = "<p class=fine align=center><font size=-2>"
                        + COM.dragonflow.Utils.LocaleUtils.createLink(
                                COM.dragonflow.Utils.LocaleUtils
                                        .getResourceBundle().getString(
                                                "TermsAndConditions"), 1,
                                "/SiteView/license.html") + "</font>";
            }
            java.lang.String s6 = COM.dragonflow.SiteView.Platform.getVersion();
            printwriter
                    .println("<table class=fine border=0 cellspacing=0 width=500 align=center><tr><td><p class=fine align=center>"
                            + COM.dragonflow.SiteView.Platform.companyLogo
                            + "<p>\n"
                            + "<p class=fine align=center><small>"
                            + COM.dragonflow.SiteView.Platform.productName
                            + " "
                            + s6
                            + ", "
                            + COM.dragonflow.SiteView.Platform.copyright
                            + s
                            + "</small>"
                            + s5
                            + "</p>\n</center>\n</td></tr></table></BODY></HTML>");
        } else {
            java.lang.String s1 = "http://www.dragonflow.com/images/common/dragonflow_logo.gif";
            java.lang.String s3 = COM.dragonflow.SiteView.Platform.getVersion();
            printwriter
                    .println("<table class=fine border=0 cellspacing=0 width=\"100%\" align=center><tr><td><p class=fine align=center><a href="
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + ">"
                            + COM.dragonflow.SiteView.Platform.companyLogo
                            + COM.dragonflow.SiteView.Platform.companyName
                            + "\"></a>\n"
                            + "<br><small>"
                            + COM.dragonflow.SiteView.Platform.productName
                            + " "
                            + s3
                            + "<br>"
                            + "<a href=\""
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + "\">dragonflow.com</a> | \n"
                            + "<a href=\"http://support.dragonflow.com\">Customer Support</a> | \n"
                            + "<a href=\""
                            + COM.dragonflow.SiteView.Platform.homeURLPrefix
                            + "/company/contact_us/\">Contact Us</a> | \n"
                            + COM.dragonflow.SiteView.Platform.copyright
                            + "</small>"
                            + "</p>\n</center>\n</td></tr></table></BODY></HTML>");
        }
    }

    public void printButtonBar(java.lang.String s, java.lang.String s1,
            menus menus1) {
        COM.dragonflow.Page.CGI.printButtonBar(outputStream, s, s1, request,
                getLocalMasterConfig(), menus1, false);
    }

    public void printButtonBar(java.lang.String s, java.lang.String s1) {
        COM.dragonflow.Page.CGI.printButtonBar(outputStream, s, s1, request,
                getLocalMasterConfig());
    }

    public static java.lang.String getSubmitName(java.lang.String s) {
        if (s.equals("Edit")) {
            return "Update";
        } else {
            return s;
        }
    }

    public static java.lang.String reportURL(
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        if (httprequest.getAccount().equals("user")) {
            return COM.dragonflow.SiteView.Platform.getURLPath("userhtml",
                    httprequest.getAccount())
                    + "/Reports.html";
        } else {
            return "/SiteView/cgi/go.exe/SiteView?page=report&operation=List&view=Report&account="
                    + httprequest.getAccount();
        }
    }

    public static void printCurrentSiteView(java.io.PrintWriter printwriter,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        if (COM.dragonflow.Page.CGI.isPortalServerRequest(httprequest)) {
            COM.dragonflow.SiteView.PortalSiteView portalsiteview = (COM.dragonflow.SiteView.PortalSiteView) COM.dragonflow.SiteView.Portal
                    .getSiteViewForID(httprequest.getPortalServer());
            if (portalsiteview != null) {
                printwriter.println("<HR><B><FONT SIZE=+2>"
                        + portalsiteview.getProperty("_title")
                        + "</FONT></B> - information is for the "
                        + portalsiteview.getProperty("_title")
                        + " SiteView<HR>");
            }
        }
    }

    private static void printSecondNavBar(java.io.PrintWriter printwriter,
            COM.dragonflow.HTTP.HTTPRequest httprequest, menus menus1, int i,
            boolean flag) {
        if (menus1.size() < 3) {
            if (httprequest.actionAllowed("_browse")) {
                menus1.add(new menuItems("Browse", "browse", "", "page",
                        "Browse Monitors"));
            }
            if (httprequest.actionAllowed("_preference")) {
                menus1.add(new menuItems("Remote UNIX", "machine", "", "page",
                        "Add/Edit Remote UNIX/Linux profiles"));
                menus1.add(new menuItems("Remote NT", "ntmachine", "", "page",
                        "Add/Edit Remote Win NT/2000 profiles"));
            }
            if (httprequest.actionAllowed("_tools")) {
                menus1.add(new menuItems("Tools", "monitor", "Tools",
                        "operation", "Use monitor diagnostic tools"));
            }
            if (httprequest.actionAllowed("_progress")) {
                menus1.add(new menuItems("Progress", "Progress", "", "url",
                        "View current monitoring progress"));
            }
            if (httprequest.actionAllowed("_browse")) {
                menus1.add(new menuItems("Summary", "monitorSummary", "",
                        "page", "View current monitor settings"));
            }
        }
        if (COM.dragonflow.SiteView.Platform.isSiteSeerAccount(httprequest
                .getAccount())) {
            return;
        }
        printwriter
                .print("<TABLE class=\"subnav\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"4\"><TR class=\"subnav\"><TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>");
        if (menus1.size() != 0) {
            for (int j = 0; j < menus1.size(); j++) {
                menuItems menuitems = (menuItems) menus1.at(j);
                if (menuitems.linkClass.equals("url")) {
                    printwriter
                            .print("<TD><p class=navbar align=center> <font size=-1 face=Arial, sans-serif><b><a href=\"/SiteView/"
                                    + httprequest.getAccountDirectory()
                                    + "/"
                                    + menuitems.menuLink
                                    + ".html\" title=\""
                                    + menuitems.toolTip
                                    + "\">"
                                    + menuitems.menuLabel
                                    + "</a></b></font></p>");
                } else if (menuitems.linkClass.equals("script")) {
                    if (httprequest.isStandardAccount()) {
                        printwriter
                                .print("<TD><p class=navbar align=center> <font size=-1 face=Arial, sans-serif><b><a href=\"javascript:OpenOverview()\" title=\""
                                        + menuitems.toolTip
                                        + "\">"
                                        + menuitems.menuLabel
                                        + "</a></b></font></p>");
                    }
                } else if (menuitems.linkClass.equals("operation")) {
                    printwriter
                            .print("<TD><p class=navbar align=center> <font size=-1 face=Arial, sans-serif><b><a href=\"/SiteView/cgi/go.exe/SiteView?page="
                                    + menuitems.menuLink
                                    + "&operation="
                                    + menuitems.opLink
                                    + "&account="
                                    + httprequest.getAccount()
                                    + "\" title=\""
                                    + menuitems.toolTip
                                    + "\">"
                                    + menuitems.menuLabel
                                    + "</a></b></font></p>");
                } else {
                    printwriter
                            .print("<TD><p class=navbar align=center> <font size=-1 face=Arial, sans-serif><b><a href=\"/SiteView/cgi/go.exe/SiteView?page="
                                    + menuitems.menuLink
                                    + "&account="
                                    + httprequest.getAccount()
                                    + "\"  title=\""
                                    + menuitems.toolTip
                                    + "\">"
                                    + menuitems.menuLabel
                                    + "</a></b></font></p>");
                }
                printwriter
                        .print("<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>");
            }

            printwriter.print("</TR></table>\n");
        }
    }

    private static void printSecondNavBar(java.io.PrintWriter printwriter,
            COM.dragonflow.HTTP.HTTPRequest httprequest, int i, boolean flag) {
        if (COM.dragonflow.SiteView.Platform.isSiteSeerAccount(httprequest
                .getAccount())) {
            return;
        }
        java.lang.String s = "<TD>&nbsp;</td>";
        if (httprequest.actionAllowed("_preference")) {
            java.lang.String s1 = "general";
            s = "<TD><p class=navbar align=center> <font size=-1 face=Arial, sans-serif><b><a href=/SiteView/cgi/go.exe/SiteView?page="
                    + s1
                    + "Prefs&account="
                    + httprequest.getAccount()
                    + ">"
                    + COM.dragonflow.Utils.LocaleUtils.getResourceBundle()
                            .getString("Preferences")
                    + "</a></b></font></p></TD>\n";
        }
        java.lang.String s2 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>";
        if (httprequest.actionAllowed("_browse")) {
            s2 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td><TD><p class=navbar align=center><font size=-1 face=Arial, sans-serif><b><A HREF=/SiteView/cgi/go.exe/SiteView?page=browse&account="
                    + httprequest.getAccount()
                    + ">"
                    + COM.dragonflow.Utils.LocaleUtils.getResourceBundle()
                            .getString("BrowseMonitors")
                    + "</A></b></font></p></TD>\n";
        }
        java.lang.String s3 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>";
        if ((httprequest.actionAllowed("_groupEdit")
                || httprequest.actionAllowed("_groupDisable") || httprequest
                .actionAllowed("_groupRefresh"))
                && !httprequest.getPermission("_link", "deleteGroup").equals(
                        "hidden")) {
            s3 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td><TD><p class=navbar align=center><font size=-1 face=Arial, sans-serif><b><A HREF=/SiteView/cgi/go.exe/SiteView?page=manage&account="
                    + httprequest.getAccount()
                    + ">"
                    + COM.dragonflow.Utils.LocaleUtils.getResourceBundle()
                            .getString("Manage") + "</A></b></font></p></TD>\n";
        }
        java.lang.String s4 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>";
        if (httprequest.actionAllowed("_tools")) {
            s4 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td><TD><p class=navbar align=center><font size=-1 face=Arial, sans-serif><b><A HREF=/SiteView/cgi/go.exe/SiteView?page=monitor&operation=Tools&account="
                    + httprequest.getAccount()
                    + ">"
                    + COM.dragonflow.Utils.LocaleUtils.getResourceBundle()
                            .getString("DiagnosticTools")
                    + "</A></b></font></p></TD>\n";
        }
        java.lang.String s5 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td>";
        if (httprequest.actionAllowed("_support")) {
            s5 = "<TD><img src=/SiteView/htdocs/artwork/empty1111.gif width=10 height=10 border=0></td><TD><p class=navbar align=center><font size=-1 face=Arial, sans-serif><b><a href=\"http://support.dragonflow.com/\" target=\"Help\">"
                    + COM.dragonflow.Utils.LocaleUtils.getResourceBundle()
                            .getString("SupportRequest")
                    + "</a></b></font></p></td>\n";
        }
        printwriter
                .println("<img src=/SiteView/htdocs/artwork/empty6010.gif height=5 width=10><br>\n");
        if (flag) {
            printwriter
                    .print("<TABLE border=0 align=center cellpadding=0 width="
                            + i + "><TR>" + s + s2 + s3 + s4 + s5
                            + "</TR></TABLE>\n");
        } else {
            printwriter.print("<center><TABLE border=0 cellpadding=0 width="
                    + i + "><TR>" + s + s2 + s3 + s4 + s5
                    + "</TR></table></center>\n");
        }
    }

    public static void printButtonBar(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1,
            COM.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap) {
        COM.dragonflow.Page.CGI.printButtonBar(printwriter, s, s1, httprequest,
                hashmap, false);
    }

    public static void printButtonBar(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1,
            COM.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap,
            boolean flag) {
        menus menus1 = new menus();
        COM.dragonflow.Page.CGI.printButtonBar(printwriter, s, s1, httprequest,
                hashmap, menus1, flag);
    }

    public static void printButtonBar(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1,
            COM.dragonflow.HTTP.HTTPRequest httprequest, jgl.HashMap hashmap,
            menus menus1, boolean flag) {
        if (COM.dragonflow.SiteView.Platform.isPortal()) {
            if (httprequest.getValue("toolbar").equals("off")) {
                return;
            }
            COM.dragonflow.SiteView.User user = httprequest.getUser();
            java.lang.String s3 = user.getProperty("_buttonBar");
            if (s3.length() == 0) {
                s3 = "Toolbar.htm";
            }
            java.lang.String s5 = COM.dragonflow.SiteView.Portal
                    .getViewContent(s3, httprequest);
            s5 = COM.dragonflow.Utils.TextUtils.replaceString(s5,
                    "CentraScopeTOC.htm", s);
            printwriter.println(s5);
            COM.dragonflow.Page.CGI.printCurrentSiteView(printwriter,
                    httprequest);
            return;
        }
        java.lang.String s2 = "/SiteView/" + httprequest.getAccountDirectory()
                + "/SiteView.html";
        java.lang.String s4 = COM.dragonflow.Page.CGI.reportURL(httprequest);
        java.lang.String s6 = "";
        if (httprequest.actionAllowed("_alertList")) {
            s6 = "/SiteView/cgi/go.exe/SiteView?page=alert&operation=List&view=Alert&account="
                    + httprequest.getAccount();
        } else {
            s6 = s2;
        }
        java.lang.String s7 = "/SiteView/cgi/go.exe/SiteView?page=overview&account="
                + httprequest.getAccount();
        java.lang.String s8 = "";
        if (httprequest.actionAllowed("_healthView")
                || httprequest.actionAllowed("_healthEdit")) {
            s8 = "/SiteView/cgi/go.exe/SiteView?page=health&operation=List&account="
                    + httprequest.getAccount();
        } else {
            s8 = s2;
        }
        java.lang.String s9 = "/SiteView/cgi/go.exe/SiteView?page=generalPrefs&account="
                + httprequest.getAccount();
        java.lang.String s10 = "preferences";
        if (httprequest.actionAllowed("_preference")
                || httprequest.actionAllowed("_detachFromMA")) {
            s9 = "/SiteView/cgi/go.exe/SiteView?page=generalPrefs&account="
                    + httprequest.getAccount();
            s10 = "preferences";
        } else {
            s9 = s2;
        }
        java.lang.String s11 = "siteview";
        java.lang.String s12 = "alerts";
        java.lang.String s13 = "reports";
        java.lang.String s14 = "overview";
        java.lang.String s15 = COM.dragonflow.SiteView.Health.getHealthState();
        if (s15.equals("nodata")) {
            s15 = "disable";
        }
        java.lang.String s16 = "Health" + s15.toLowerCase();
        if (httprequest.isSiteSeerAccount()) {
            s11 = "siteseer";
        }
        if (s1.equals("SiteView")) {
            s11 = "H" + s11;
        } else if (s1.equals("Alerts")) {
            s12 = "H" + s12;
        } else if (s1.equals("Reports")) {
            s13 = "H" + s13;
        } else if (s1.equals("Health")) {
            s16 = "H" + s16;
        } else if (s1.equals("Preference")) {
            s10 = "H" + s10;
        } else if (s1.length() != 0) {
            s12 = "alerts";
        }
        if (httprequest.isStandardAccount()) {
            printwriter.println("<SCRIPT LANGUAGE = \"JavaScript\">\n");
            printwriter
                    .println("<!--\nfunction OpenOverview()\n{\noverviewWindow=window.open(\""
                            + s7
                            + "\",\"SiteView\",\""
                            + COM.dragonflow.Utils.TextUtils.getValue(hashmap,
                                    "_overviewOptions")
                            + "\");\n"
                            + "location.reload();\n"
                            + "}\n"
                            + "if (location.search == '?openMultiView') { OpenOverview();}\n"
                            + "//-->\n");
            printwriter.println("</SCRIPT>\n");
        }
        if (!s1.equals("SiteView")) {
            java.lang.String s17 = "";
            java.lang.String s18 = httprequest.getPermission("_partner");
            if (s18.length() > 0) {
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                        .currentSiteView();
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup
                        .getElement(s18);
                if (monitorgroup != null) {
                    s17 = monitorgroup.getProperty("_partnerHeaderHTML");
                }
            }
            if (s17.length() == 0) {
                s17 = COM.dragonflow.Page.CGI.getValue(hashmap, "_headerHTML");
            }
            printwriter.print(s17);
            printwriter.println(COM.dragonflow.SiteView.Platform.licenseHeader(
                    hashmap, true, httprequest.getAccount()));
        }
        printwriter
                .print("<table border=\"0\" align=\"center\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\"><TR class=\"navbox\"><TD>\n");
        printwriter
                .print("<table class=\"topnav\" border=\"0\" align=\"center\" cellspacing=\"0\" cellpadding=\"0\"><TR class=\"topnav\">\n<TD><IMG SRC=/SiteView/htdocs/artwork/left.gif width=35 height=44 alt=\"\" border=0></td>");
        byte byte0 = 106;
        java.lang.String s19 = COM.dragonflow.SiteView.Platform.productName;
        printwriter
                .println("<TD><a href="
                        + s2
                        + "><IMG SRC=/SiteView/htdocs/artwork/"
                        + s11
                        + ".gif ALT=\"SiteView Main View\""
                        + " width="
                        + byte0
                        + " height=44\n"
                        + "border=0></a></td><TD><a href="
                        + s6
                        + ">"
                        + "<IMG SRC=/SiteView/htdocs/artwork/"
                        + s12
                        + ".gif ALT=\"View/add/edit automated alerts\" width=82 height=44 border=0></a></td>\n");
        printwriter
                .println("<TD><a href="
                        + s4
                        + ">"
                        + "<IMG SRC=/SiteView/htdocs/artwork/"
                        + s13
                        + ".gif ALT=\"View/create/edit automated and adhoc reports\" width=82 height=44 border=0></a></td>\n");
        if (!COM.dragonflow.SiteView.Platform.isSiteSeerAccount(httprequest
                .getAccount())) {
            printwriter
                    .println("<TD><a href="
                            + s8
                            + "><IMG SRC=/SiteView/htdocs/artwork/"
                            + s16
                            + ".gif ALT=\"View current health of SiteView processes and files\" width=82 height=44 border=0></a></td>\n");
            printwriter
                    .println("<TD><a href="
                            + s9
                            + "><IMG SRC=/SiteView/htdocs/artwork/"
                            + s10
                            + ".gif ALT=\"View/edit SiteView configuration settings and options\" height=44 border=0></a></td>\n");
        }
        java.lang.String s20 = "<a href=/SiteView/docs/" + s + " TARGET=Help>";
        printwriter
                .println("<TD>"
                        + s20
                        + "<IMG SRC=/SiteView/htdocs/artwork/help.gif ALT=\"View the online SiteView User's Guide\" width=82 height=44\n"
                        + "border=0></a></td><TD><IMG SRC=/SiteView/htdocs/artwork/right.gif width=35 height=44 ALT=\"\" border=0>"
                        + "</td></TR></TABLE>\n");
        printwriter.println("</td></TR><TR class=\"navbox\"><TD>");
        COM.dragonflow.Page.CGI.printSecondNavBar(printwriter, httprequest,
                menus1, 600, flag);
        printwriter.println("</td></TR><TR class=\"navbox\"><TD>");
        COM.dragonflow.Page.CGI.printNavBarMessages(printwriter);
        printwriter.print("</TD></TR></TABLE>\n");
    }

    void printErrorHeader() {
        outputStream
                .println("<HR><CENTER><FONT SIZE=+2> Error </FONT><BR>There was an error in the entered information - the error message is displayed in italics to the right of the field that is in error.</CENTER><HR>");
    }

    void printError(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        COM.dragonflow.Page.CGI.printError(outputStream, s, s1, s2);
    }

    static void printError(java.io.PrintWriter printwriter, java.lang.String s,
            java.lang.String s1, java.lang.String s2) {
        COM.dragonflow.Page.CGI.printRefreshHeader(printwriter, "", s2, 1);
        printwriter.print(s + "<HR>" + s1 + "<HR>");
        COM.dragonflow.HTTP.HTTPRequest httprequest = null;
        COM.dragonflow.Page.CGI.printFooter(printwriter, httprequest);
        printwriter.println("</BODY>");
    }

    public static void printHeadTag(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1) {
        COM.dragonflow.Page.CGI.printHeadTag(printwriter, s, s1,
                COM.dragonflow.SiteView.Platform.charSetTag);
    }

    public static void printHeadTag(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1, java.lang.String s2) {
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        COM.dragonflow.SiteView.SiteViewGroup _tmp = siteviewgroup;
        java.lang.String s3 = COM.dragonflow.SiteView.SiteViewGroup
                .getServerID();
        printwriter.println("<HEAD>\n" + nocacheHeader + s2 + s1 + "\n<TITLE>"
                + s3 + " : " + s + "</TITLE>\n");
        printwriter
                .println("<link rel=\"stylesheet\" type=\"text/css\" href=\"/SiteView/htdocs/artwork/siteviewUI.css\">\n<link rel=\"stylesheet\" type=\"text/css\" href=\"/SiteView/htdocs/artwork/user.css\">\n </HEAD>\n");
    }

    public void printHeadTagAWRequest(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1, java.lang.String s2) {
        printwriter.println("<HEAD>\n" + nocacheHeader + s2 + s1);
        if (request.getValue("AWRequest").equals("yes")) {
            printwriter
                    .println("<style type=\"text/css\">.darkrow {COLOR: black; BACKGROUND-COLOR: #cccc99; FONT-FAMILY: Verdana; FONT-SIZE: 7.5pt }.lightrow { COLOR: black; BACKGROUND-COLOR: #efefdf; FONT-FAMILY: Verdana; FONT-SIZE: 7.5pt }.titlerow { BACKGROUND-COLOR: #330066; COLOR: white; FONT-FAMILY: Verdana; FONT-SIZE: 8pt } .VerBl8 { COLOR: black; FONT-FAMILY: Verdana; FONT-SIZE: 8pt }.VerdanaDB10 { COLOR: #330066; FONT-FAMILY: Verdana; FONT-SIZE: 10pt }</style>\n");
        }
        printwriter
                .println("<TITLE>"
                        + s
                        + "</TITLE>"
                        + "\n<link rel=\"stylesheet\" type=\"text/css\" href=\"/SiteView/htdocs/artwork/siteviewUI.css\">\n"
                        + "</HEAD>\n");
    }

    public static void printBodyHeader(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1) {
        COM.dragonflow.Page.CGI.printBodyHeader(printwriter, s, s1, "");
    }

    public static void printBodyHeader(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1, java.lang.String s2) {
        java.lang.String s3 = "";
        if (s2.length() > 0) {
            s3 = "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html;CHARSET="
                    + s2 + "\">\n";
        } else {
            s3 = COM.dragonflow.SiteView.Platform.charSetTag;
        }
        COM.dragonflow.Page.CGI.printHeadTag(printwriter, s, s1, s3);
        java.lang.String s4 = "";
        if (s.toLowerCase().indexOf("overview") != -1) {
            s4 = " onload=\"window.focus()\"";
        }
        printwriter
                .println("<BODY BGCOLOR=\"#ffffff\" link=#1155bb alink=#1155bb vlink=#1155bb"
                        + s4 + ">\n");
    }

    public void printBodyHeader(java.lang.String s) {
        if (!request.getValue("AWRequest").equals("yes")) {
            COM.dragonflow.Page.CGI.printBodyHeader(outputStream, s, "");
        } else {
            printBodyHeaderAWRequest(outputStream, s, "", "");
        }
    }

    public static java.lang.String getGroupDetailURL(
            COM.dragonflow.HTTP.HTTPRequest httprequest, java.lang.String s) {
        java.lang.String s1 = httprequest.getValue("_health").length() <= 0 ? ""
                : "?_health=true";
        return "/SiteView/" + httprequest.getAccountDirectory() + "/Detail"
                + COM.dragonflow.HTTP.HTTPRequest.encodeString(s) + ".html" + s1;
    }

    public void printBodyHeaderAWRequest(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1, java.lang.String s2) {
        java.lang.String s3 = "";
        if (s2.length() > 0) {
            s3 = "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html;CHARSET="
                    + s2 + "\">\n";
        }
        printHeadTagAWRequest(printwriter, s, s1, s3);
        printwriter.println("<BODY BGCOLOR=\"#ffffff\" class=\"VerBl8\">\n");
    }

    public static void printRefreshHeader(java.io.PrintWriter printwriter,
            java.lang.String s, java.lang.String s1, int i) {
        COM.dragonflow.Page.CGI.printBodyHeader(printwriter, s,
                "<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"" + i + "; URL=" + s1
                        + "\">\n");
        printwriter.flush();
    }

    public java.lang.String getWhereURL(java.lang.String s) {
        if (isPortalServerRequest() && autoFollowPortalRefresh) {
            if (request.getValue("rview").length() > 0) {
                s = getPageLink("portal", "") + "&view="
                        + request.getValue("rview");
                if (request.getValue("detail").length() > 0) {
                    java.lang.String s1 = request.getValue("detail");
                    if (s1.indexOf('=') > 0) {
                        s1 = s1.substring(0, s1.indexOf('=')) + "%3D"
                                + s1.substring(s1.indexOf('=') + 1);
                    }
                    if (s1.indexOf('&') > 0) {
                        s1 = s1.substring(0, s1.indexOf('&')) + "%26"
                                + s1.substring(s1.indexOf('&') + 1);
                    }
                    s = s + "&detail=" + s1;
                }
            } else {
                s = getPageLink("portalMain", "");
            }
        }
        return s;
    }

    public java.lang.String getWhereLabel(java.lang.String s) {
        if (isPortalServerRequest()) {
            s = "Return";
        }
        return s;
    }

    public void printRefreshHeader(java.lang.String s, java.lang.String s1,
            int i) {
        s1 = getWhereURL(s1);
        COM.dragonflow.Page.CGI.printRefreshHeader(outputStream, s, s1, i);
    }

    public void printRefreshPage(java.lang.String s, int i) {
        printRefreshHeader("", s, i);
        outputStream
                .println("<!--<br><br><br><br><hr><br><h3 align=center>SiteView is running</h3><br> <p align=center>If your browser doesn't refresh in 5 seconds, click on <A HREF="
                        + s
                        + ">this link</A> to continue.</p>"
                        + "<br><hr>\n"
                        + "<p class=fine align=center>"
                        + COM.dragonflow.SiteView.Platform.companyLogo
                        + "</body></html>");
    }

    public void printReturnRefresh(java.lang.String s, int i) {
        printRefreshPage(s, i);
    }

    public void printCGIHeader() {
        request.printHeader(outputStream);
        outputStream.println("<HTML>");
    }

    public void printCGIFooter() {
        outputStream.println("</HTML>");
        outputStream.flush();
    }

    public void printLicenseExceeded(COM.dragonflow.SiteView.Monitor monitor,
            java.lang.String s, int i, java.lang.String s1) {
        java.lang.String s2 = (java.lang.String) monitor
                .getClassProperty("title");
        printButtonBar((java.lang.String) monitor.getClassProperty("help"), s);
        outputStream.print("<HR>");
        if (s1.equals("license")) {
            java.lang.String s3 = COM.dragonflow.Utils.LUtils
                    .getLicenseExceededHTML();
            outputStream.println(s3);
        } else {
            java.lang.String s4 = "";
            if (s1.equals("class")) {
                s4 = " " + s2;
            }
            outputStream.print("You have reached your limit of " + i + s4
                    + " monitors for this account.");
        }
        outputStream.print("<HR><P><A HREF="
                + COM.dragonflow.Page.CGI.getGroupDetailURL(request, s)
                + ">Return to Group</A>\n");
        printFooter(outputStream);
    }

    public void printTooManyFAndIMonitors(java.lang.String s, int i) {
        outputStream.print("<HR>");
        outputStream.print("You have reached your limit of " + i
                + " frames and images for this account.");
        outputStream.print("<HR><P><A HREF="
                + COM.dragonflow.Page.CGI.getGroupDetailURL(request, s)
                + ">Return to Group</A>\n");
        printFooter(outputStream);
    }

    public void printContentStartComment() {
        outputStream.println("\n<!--CONTENTSTART-->");
    }

    public void printContentEndComment() {
        outputStream.println("\n<!--CONTENTEND-->");
    }

    public void handleRequest() {
        outputStream.println("Content-type: text/html\n\n<HTML>");
        try {
            java.io.BufferedReader bufferedreader = COM.dragonflow.Utils.FileUtils
                    .MakeInputReader(java.lang.System.in);
            if (args != null) {
                request = new HTTPRequest(args);
                request.setUser(request.getAccount());
            } else {
                request = new HTTPRequest(bufferedreader);
            }
            printBody();
        } catch (java.lang.Exception exception) {
            printError("There was a unexpected problem.", exception.toString(),
                    "/SiteView/" + request.getAccountDirectory()
                            + "/SiteView.html");
        }
        printCGIFooter();
    }

    boolean isGroup(jgl.HashMap hashmap) {
        return hashmap.get("_id") == null;
    }

    jgl.Array getAllowedGroupIDs() {
        return COM.dragonflow.Page.CGI.getAllowedGroupIDsForAccount(request);
    }

    public static boolean isRelated(java.lang.String s, java.lang.String s1) {
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        Object obj = null;
        while (s.length() != 0) {
            if (s.equals(s1)) {
                return true;
            }
            COM.dragonflow.SiteView.Monitor monitor;
            if (COM.dragonflow.Page.treeControl.useTree()) {
                java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s,
                        "/");
                if (as[0].equals(s1)) {
                    return true;
                }
                monitor = (COM.dragonflow.SiteView.Monitor) siteviewgroup
                        .getElement(as[0]);
            } else {
                monitor = (COM.dragonflow.SiteView.Monitor) siteviewgroup
                        .getElement(s);
            }
            if (monitor == null) {
                break;
            }
            s = COM.dragonflow.Utils.I18N.toDefaultEncoding(monitor
                    .getProperty("_parent"));
        } 
        return false;
    }

    public static jgl.Array getAllowedGroupIDsForAccount(
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        if (COM.dragonflow.Page.CGI.isPortalServerRequest(httprequest)) {
            jgl.Array array = COM.dragonflow.SiteView.Portal.findObjects(
                    "item=" + httprequest.getPortalServer(), 2, httprequest);
            jgl.Array array2 = new Array();
            for (int i = 0; i < array.size(); i++) {
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) array
                        .at(i);
                array2
                        .add(COM.dragonflow.Utils.I18N
                                .toDefaultEncoding(monitorgroup
                                        .getProperty(COM.dragonflow.SiteView.MonitorGroup.pID)));
            }

            return array2;
        } else {
            jgl.Array array1 = COM.dragonflow.Utils.I18N
                    .toDefaultArray(COM.dragonflow.SiteView.SiteViewGroup
                            .currentSiteView().getGroupIDs());
            return COM.dragonflow.Page.CGI.filterGroupsForAccount(array1,
                    httprequest);
        }
    }

    public static jgl.Array getGroupFilterForAccount(
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        jgl.Array array = new Array();
        java.lang.String s = httprequest.getAccount();
        java.lang.String s1 = httprequest.getValue("groupFilter");
        if (COM.dragonflow.SiteView.Platform.isStandardAccount(s)) {
            java.util.Enumeration enumeration = httprequest.getUser()
                    .getMultipleValues("_group");
            if (enumeration.hasMoreElements()) {
                while (enumeration.hasMoreElements()) {
                    java.lang.String s2 = COM.dragonflow.Utils.I18N
                            .toDefaultEncoding((java.lang.String) enumeration
                                    .nextElement());
                    if (s1.length() == 0
                            || COM.dragonflow.Page.CGI.isRelated(s2, s1)) {
                        array.add(s2);
                    }
                } 
            } else if (s1.length() > 0) {
                array.add(COM.dragonflow.Utils.I18N.toDefaultEncoding(s1));
            }
        } else {
            if (s1 == null || s1.length() == 0) {
                array.add(s);
            } else {
                array.add(COM.dragonflow.Utils.I18N.toDefaultEncoding(s1));
            }
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                    .currentSiteView();
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup
                    .getElement(s);
            if (monitorgroup != null
                    && s.equals(monitorgroup.getProperty("_partnerFilter"))) {
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup1 = COM.dragonflow.SiteView.SiteViewGroup
                        .currentSiteView();
                jgl.Array array1 = siteviewgroup1.getGroupIDs();
                java.util.Enumeration enumeration1 = array1.elements();
                while (enumeration1.hasMoreElements()) {
                    java.lang.String s3 = COM.dragonflow.Utils.I18N
                            .toDefaultEncoding((java.lang.String) enumeration1
                                    .nextElement());
                    COM.dragonflow.SiteView.MonitorGroup monitorgroup1 = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup1
                            .getElement(s3);
                    if (monitorgroup1 != null
                            && monitorgroup1.getProperty("_partner").equals(s)) {
                        array.add(s3);
                    }
                }
            }
        }
        return array;
    }

    public static boolean allowedByGroupFilter(java.lang.String s,
            jgl.Array array) {
        for (java.util.Enumeration enumeration = array.elements(); enumeration
                .hasMoreElements();) {
            java.lang.String s1 = (java.lang.String) enumeration.nextElement();
            if (COM.dragonflow.Page.CGI.isRelated(s, s1)) {
                return true;
            }
        }

        return false;
    }

    public static boolean isGroupAllowedForAccount(java.lang.String s,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        return COM.dragonflow.Page.CGI.isGroupAllowedForAccount(s,
                COM.dragonflow.Page.CGI.getGroupFilterForAccount(httprequest));
    }

    public static boolean isGroupAllowedForAccount(java.lang.String s,
            jgl.Array array) {
        if (array != null && array.size() != 0) {
            return COM.dragonflow.Page.CGI.allowedByGroupFilter(s, array);
        } else {
            return true;
        }
    }

    public static jgl.Array filterGroupsForAccount(jgl.Array array,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        jgl.Array array1 = COM.dragonflow.Page.CGI
                .getGroupFilterForAccount(httprequest);
        if (array1 != null && array1.size() != 0) {
            java.util.Enumeration enumeration = array.elements();
            array = new Array();
            while (enumeration.hasMoreElements()) {
                java.lang.String s = (java.lang.String) enumeration
                        .nextElement();
                if (COM.dragonflow.Page.CGI.allowedByGroupFilter(s, array1)) {
                    array.add(s);
                }
            } 
        }
        return array;
    }

    public static java.lang.String getGroupFullLinks(
            COM.dragonflow.SiteView.Monitor monitor) {
        return COM.dragonflow.Page.CGI.getGroupFullLinks(monitor, null);
    }

    public static java.lang.String getGroupFullLinks(
            COM.dragonflow.SiteView.Monitor monitor,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        java.lang.String s = COM.dragonflow.Utils.I18N.toDefaultEncoding(monitor
                .getProperty(COM.dragonflow.SiteView.Monitor.pID));
        return COM.dragonflow.Page.CGI.getGroupPath(monitor, s, true,
                httprequest);
    }

    public static java.lang.String getGroupFullName(java.lang.String s) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        COM.dragonflow.SiteView.SiteViewObject siteviewobject = COM.dragonflow.SiteView.Portal
                .getSiteViewForID(s);
        COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor) siteviewobject
                .getElementByID(COM.dragonflow.Page.CGI.getGroupIDRelative(s));
        return COM.dragonflow.Page.CGI.getGroupPath(monitor, s, false);
    }

    public static java.lang.String getGroupPath(
            COM.dragonflow.SiteView.Monitor monitor, java.lang.String s,
            boolean flag) {
        return COM.dragonflow.Page.CGI.getGroupPath(monitor, s, flag, null);
    }

    public static java.lang.String getGroupPath(
            COM.dragonflow.SiteView.Monitor monitor, java.lang.String s,
            boolean flag, COM.dragonflow.HTTP.HTTPRequest httprequest) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        COM.dragonflow.SiteView.SiteViewObject siteviewobject = COM.dragonflow.SiteView.Portal
                .getSiteViewForID(s);
        java.lang.String s1 = httprequest == null
                || httprequest.getValue("_health").length() <= 0 ? ""
                : "?_health=true";
        java.lang.String s2 = "";
        while (true) {
            if (s2.length() != 0) {
                s2 = ": " + s2;
            }
            java.lang.String s3 = COM.dragonflow.Page.CGI.getGroupName(monitor,
                    s);
            s = COM.dragonflow.HTTP.HTTPRequest.encodeString(s);
            if (flag && s2.length() != 0) {
                s2 = "<A HREF=Detail" + s + ".html" + s1 + ">" + s3 + "</a>"
                        + s2;
            } else {
                s2 = s3 + s2;
            }
            if (monitor == null) {
                break;
            }
            s = COM.dragonflow.Utils.I18N.toDefaultEncoding(monitor
                    .getProperty("_parent"));
            if (s == null || s.length() == 0) {
                break;
            }
            monitor = (COM.dragonflow.SiteView.Monitor) siteviewobject
                    .getElement(s);
        } 
        return s2;
    }

    public static java.lang.String getGroupName(
            COM.dragonflow.SiteView.Monitor monitor, java.lang.String s) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        java.lang.String s1;
        if (monitor == null) {
            s1 = COM.dragonflow.Utils.I18N.toNullEncoding(s);
            s1 = "MISSING GROUP (" + s1 + ")";
        } else {
            s1 = COM.dragonflow.Page.CGI.getGroupName(s);
        }
        return s1;
    }

    public static java.lang.String getGroupName(java.lang.String s) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        jgl.HashMap hashmap = null;
        try {
            jgl.Array array = COM.dragonflow.Page.CGI.ReadGroupFrames(s, null);
            java.util.Enumeration enumeration = array.elements();
            if (enumeration.hasMoreElements()) {
                hashmap = (jgl.HashMap) enumeration.nextElement();
            } else {
                hashmap = new HashMap();
            }
        } catch (java.io.IOException ioexception) {
            java.lang.System.out.println("***id: " + s + ", error: "
                    + ioexception);
        }
        return COM.dragonflow.Page.CGI.getGroupName(hashmap, s);
    }

    public static java.lang.String getGroupName(jgl.Array array,
            java.lang.String s) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        if (array.size() > 0) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(0);
            return COM.dragonflow.Page.CGI.getGroupName(hashmap, s);
        } else {
            java.lang.System.out.println("GROUP : " + s + " IS EMPTY.");
            return "";
        }
    }

    public static java.lang.String getGroupName(jgl.HashMap hashmap,
            java.lang.String s) {
        java.lang.String s1 = null;
        COM.dragonflow.Utils.I18N.test(s, 0);
        if (COM.dragonflow.SiteView.Portal.isPortalID(s)) {
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) COM.dragonflow.SiteView.Portal
                    .getPortal().getElement(s);
            if (monitorgroup != null) {
                COM.dragonflow.SiteView.PortalSiteView portalsiteview = (COM.dragonflow.SiteView.PortalSiteView) monitorgroup
                        .getOwner();
                if (portalsiteview != null) {
                    s1 = monitorgroup
                            .getProperty(COM.dragonflow.SiteView.MonitorGroup.pName)
                            + " on "
                            + portalsiteview
                                    .getProperty(COM.dragonflow.SiteView.PortalSiteView.pTitle);
                }
            }
            if (s1 == null) {
                s1 = "UNKNOWN NAME: " + s;
            }
        } else {
            if (hashmap != null) {
                s1 = (java.lang.String) hashmap.get("_name");
            }
            if (s1 == null || s1.equals("config") || s1.length() == 0) {
                s1 = COM.dragonflow.Utils.I18N.toNullEncoding(s);
            }
        }
        return s1;
    }

    public static java.lang.String getGroupIDFull(java.lang.String s,
            java.lang.String s1) {
        if (s1.length() > 0 && COM.dragonflow.SiteView.Portal.isPortalID(s1)) {
            s = COM.dragonflow.SiteView.Portal.makePortalID(
                    COM.dragonflow.SiteView.Portal.getServerID(s1), s, "");
        }
        return s;
    }

    public static java.lang.String getGroupIDFull(java.lang.String s,
            COM.dragonflow.SiteView.SiteViewObject siteviewobject) {
        if (siteviewobject instanceof COM.dragonflow.SiteView.PortalSiteView) {
            s = COM.dragonflow.SiteView.Portal.makePortalID(siteviewobject
                    .getProperty(COM.dragonflow.SiteView.PortalSiteView.pID),
                    s, "");
        }
        return s;
    }

    public java.lang.String getGroupIDFull(java.lang.String s) {
        return COM.dragonflow.Page.CGI.getGroupIDFull(s, request
                .getPortalServer());
    }

    public static java.lang.String getGroupIDRelative(java.lang.String s) {
        if (COM.dragonflow.SiteView.Portal.isPortalID(s)) {
            s = COM.dragonflow.SiteView.Portal.getGroupID(s);
        }
        return s;
    }

    public COM.dragonflow.SiteView.SiteViewObject getSiteView() {
        return COM.dragonflow.SiteView.Portal.getSiteViewForID(request
                .getPortalServer());
    }

    public java.lang.String computeGroupName(java.lang.String s) {
        return COM.dragonflow.Page.CGI.computeGroupName(s, request);
    }

    public static java.lang.String computeGroupName(java.lang.String s,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        java.lang.String s1 = s;
        s = COM.dragonflow.Page.CGI.getGroupIDRelative(s);
        s = s.replace(' ', '_');
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        jgl.Array array = siteviewgroup.getGroupFileIDs();
        java.lang.String s2 = s.toUpperCase() + ".";
        int i = -1;
        java.util.Enumeration enumeration = array.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s3 = (java.lang.String) enumeration.nextElement();
            s3 = s3.toUpperCase() + '.';
            if (s3.startsWith(s2)) {
                int j = COM.dragonflow.Utils.TextUtils.readInteger(s3, s2
                        .length());
                if (j < 0) {
                    j = 0;
                }
                if (j > i) {
                    i = j;
                }
            }
        } 
        
        if (i++ >= 0) {
            s = s + "." + i;
        }
        return COM.dragonflow.Page.CGI.getGroupIDFull(s, s1);
    }

    public static java.lang.String getGroupFilePath(java.lang.String s,
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        return COM.dragonflow.Page.CGI.getGroupFilePath(s, httprequest, ".mg");
    }

    public static java.lang.String getGroupFilePath(java.lang.String s,
            COM.dragonflow.HTTP.HTTPRequest httprequest, java.lang.String s1) {
        java.lang.String s2 = "";
        if (httprequest != null) {
            s2 = COM.dragonflow.SiteView.Portal.cleanPortalServerID(httprequest
                    .getPortalServer());
        }
        if (COM.dragonflow.SiteView.Portal.isPortalID(s)) {
            java.lang.String as[] = COM.dragonflow.SiteView.Portal
                    .getIDComponents(s);
            s2 = as[0];
            s = as[1];
        }
        java.lang.String s3;
        if (s.equals("_master")) {
            s3 = "/groups/master.config";
        } else if (s.equals("_users")) {
            s3 = "/groups/users.config";
        } else {
            s3 = "/groups/" + s + s1;
        }
        java.lang.String s4 = "";
        if (s2.length() > 0) {
            s4 = COM.dragonflow.SiteView.Portal.getPortalSiteViewRootPath(s2)
                    + s3;
        } else {
            s4 = COM.dragonflow.SiteView.Platform.getRoot() + s3;
        }
        return s4;
    }

    public jgl.Array ReadGroupFrames(java.lang.String s)
            throws java.io.IOException {
        return COM.dragonflow.Page.CGI.ReadGroupFrames(s, request);
    }

    public static jgl.Array ReadGroupFrames(java.lang.String s,
            COM.dragonflow.HTTP.HTTPRequest httprequest)
            throws java.io.IOException {
        if (httprequest != null
                && !COM.dragonflow.Page.CGI.isGroupAllowedForAccount(s,
                        httprequest)) {
            throw new IOException("login " + httprequest.getUser()
                    + " cannot access " + s);
        }
        java.lang.String s1 = COM.dragonflow.Page.CGI.getGroupFilePath(s,
                httprequest);
        jgl.Array array = COM.dragonflow.Properties.FrameFile.readFromFile(s1);
        if (array.size() == 0) {
            array.add(new HashMap());
        }
        return array;
    }

    public void WriteGroupFrames(java.lang.String s, jgl.Array array)
            throws java.io.IOException {
        COM.dragonflow.Page.CGI.WriteGroupFrames(s, array, request);
    }

    public static void WriteGroupFrames(java.lang.String s, jgl.Array array,
            COM.dragonflow.HTTP.HTTPRequest httprequest)
            throws java.io.IOException {
        java.lang.String s1 = COM.dragonflow.Page.CGI.getGroupFilePath(s,
                httprequest);
        for (int i = 0; i < array.size(); i++) {
            jgl.HashMap hashmap = (jgl.HashMap) array.at(i);
            if (COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_encoding")
                    .length() == 0) {
                hashmap.put("_encoding", COM.dragonflow.Utils.I18N
                        .nullEncoding());
            }
        }

        COM.dragonflow.Properties.FrameFile.writeToFile(s1, array, "_", true);
    }

    public static java.util.Enumeration getMonitors(jgl.Array array) {
        jgl.Array array1 = new Array();
        java.util.Enumeration enumeration = array.elements();
        if (enumeration.hasMoreElements()) {
            array1.add(enumeration.nextElement());
        }
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap = (jgl.HashMap) enumeration.nextElement();
            if (COM.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap)) {
                array1.add(hashmap);
            }
        } 
        
        return array1.elements();
    }

    public static int findMonitorIndex(jgl.Array array, java.lang.String s)
            throws java.lang.Exception {
        if (s.equals("_config")) {
            return 0;
        }
        java.util.Enumeration enumeration = array.elements();
        int i = 0;
        enumeration.nextElement();
        i++;
        int j = -1;
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap = (jgl.HashMap) enumeration.nextElement();
            if (COM.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap)
                    && hashmap.get("_id").equals(s)) {
                j = i;
                break;
            }
            i++;
        }
        
        if (j == -1) {
            throw new Exception("monitor id (" + s + ") could not be found");
        } else {
            return j;
        }
    }

    public static int findSubGroupIndex(jgl.Array array, java.lang.String s)
            throws java.lang.Exception {
        java.util.Enumeration enumeration = array.elements();
        int i = 0;
        s = COM.dragonflow.Page.CGI.getGroupIDRelative(s);
        enumeration.nextElement();
        i++;
        int j = -1;
        for (; enumeration.hasMoreElements(); i++) {
            jgl.HashMap hashmap = (jgl.HashMap) enumeration.nextElement();
            if (!COM.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap)) {
                continue;
            }
            java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(
                    hashmap, "_group");
            if (s1.length() == 0 || !s1.equals(s)) {
                continue;
            }
            j = i;
            break;
        }

        if (j == -1) {
            throw new Exception("subgroup id (" + s + ") could not be found");
        } else {
            return j;
        }
    }

    public static java.lang.String getValue(jgl.HashMap hashmap,
            java.lang.String s) {
        java.lang.String s1 = (java.lang.String) hashmap.get(s);
        if (s1 == null) {
            return "";
        } else {
            return s1;
        }
    }

    public static java.util.Enumeration getValues(jgl.HashMap hashmap,
            java.lang.String s) {
        return hashmap.values(s);
    }

    public jgl.HashMap getMasterConfig() {
        if (privateConfigCache == null) {
            privateConfigCache = loadMasterConfig();
        }
        return privateConfigCache;
    }

    public jgl.HashMap getLocalMasterConfig() {
        if (privateLocalConfigCache == null) {
            privateLocalConfigCache = COM.dragonflow.Page.CGI
                    .loadMasterConfig(null);
        }
        return privateLocalConfigCache;
    }

    public jgl.HashMap loadMasterConfig() {
        return COM.dragonflow.Page.CGI.loadMasterConfig(request);
    }

    public static jgl.HashMap loadMasterConfig(
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        java.lang.Object obj = new HashMapOrdered(true);
        try {
            java.lang.String s = COM.dragonflow.Page.CGI.getGroupFilePath(
                    "_master", httprequest);
            jgl.Array array = COM.dragonflow.Properties.FrameFile
                    .readFromFile(s);
            obj = (jgl.HashMap) array.front();
        } catch (java.lang.Exception exception) {
        }
        return ((jgl.HashMap) (obj));
    }

    public void saveMasterConfig(jgl.HashMap hashmap)
            throws java.io.IOException {
        COM.dragonflow.Page.CGI.saveMasterConfig(hashmap, request);
    }

    public static void saveMasterConfig(jgl.HashMap hashmap,
            COM.dragonflow.HTTP.HTTPRequest httprequest)
            throws java.io.IOException {
        jgl.Array array = new Array();
        array.add(hashmap);
        java.lang.String s = COM.dragonflow.Page.CGI.getGroupFilePath("_master",
                httprequest);
        COM.dragonflow.Properties.FrameFile.writeToFile(s, array, true);
        COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages(httprequest);
    }

    public static jgl.HashMap findMonitor(jgl.Array array, java.lang.String s)
            throws java.lang.Exception {
        int i = COM.dragonflow.Page.CGI.findMonitorIndex(array, s);
        return (jgl.HashMap) array.at(i);
    }

    public jgl.HashMap getSettings() {
        java.lang.Object obj = new HashMapOrdered(true);
        if (request.isStandardAccount()) {
            obj = getMasterConfig();
        } else {
            try {
                settingsArray = ReadGroupFrames(request.getAccount());
                obj = (jgl.HashMap) settingsArray.at(0);
            } catch (java.lang.Exception exception) {
            }
        }
        return ((jgl.HashMap) (obj));
    }

    void saveSettings(jgl.HashMap hashmap) throws java.io.IOException {
        if (request.isStandardAccount()) {
            saveMasterConfig(hashmap);
        } else {
            settingsArray.put(0, hashmap);
            WriteGroupFrames(request.getAccount(), settingsArray);
            COM.dragonflow.SiteView.SiteViewGroup.updateStaticPages(request
                    .getAccount());
        }
    }

    java.lang.String getMonitorOptionsHTML(java.lang.String s,
            java.lang.String s1, int i) throws java.lang.Exception {
        jgl.Array array = new Array();
        array.add(s);
        jgl.Array array1 = new Array();
        array1.add(s1);
        return getMonitorOptionsHTML(array, array1, null, i);
    }

    java.lang.String getMonitorOptionsHTML(jgl.Array array, jgl.Array array1,
            jgl.Array array2, int i) throws java.lang.Exception {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        java.lang.StringBuffer stringbuffer2 = new StringBuffer();
        java.lang.StringBuffer stringbuffer3 = new StringBuffer();
        java.lang.StringBuffer stringbuffer4 = new StringBuffer();
        if ((i & 4) != 0) {
            stringbuffer2.append("<option value=\"\">none");
        }
        if ((i & 0x10) != 0) {
            stringbuffer2.append("<option value=\"\">-- SiteView Panel --");
        }
        jgl.HashMap hashmap = new HashMap();
        if (array != null) {
            for (int j = 0; j < array.size(); j++) {
                hashmap.put(array.at(j), "true");
            }

        }
        jgl.HashMap hashmap1 = new HashMap();
        if (array1 != null) {
            for (int k = 0; k < array1.size(); k++) {
                hashmap1.put(array1.at(k), "true");
            }

        }
        jgl.HashMap hashmap2 = null;
        if (array2 != null) {
            hashmap2 = new HashMap();
            for (int l = 0; l < array2.size(); l++) {
                hashmap2.put(array2.at(l), "true");
            }

        }
        if ((i & 0x40) != 0) {
            java.lang.String s = "";
            if (hashmap.get("_master") != null) {
                s = "selected";
            }
            java.lang.StringBuffer stringbuffer5 = stringbuffer2;
            if (s.length() > 0 && (i & 0x80) != 0) {
                stringbuffer5 = stringbuffer3;
            }
            stringbuffer5.append("\n<option " + s
                    + " value=\"_master\">All Groups");
        }
        COM.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(
                true);
        jgl.Array array3 = getGroupNameList(hashmapordered, hashmap1, hashmap2,
                false);
        for (java.util.Enumeration enumeration = array3.elements(); enumeration
                .hasMoreElements();) {
            java.lang.String s1 = (java.lang.String) enumeration.nextElement();
            java.util.Enumeration enumeration1 = hashmapordered.values(s1);
            while (enumeration1.hasMoreElements()) {
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) enumeration1
                        .nextElement();
                java.lang.String s2 = monitorgroup
                        .getProperty(COM.dragonflow.SiteView.Monitor.pID);
                java.util.Enumeration enumeration2 = monitorgroup.getMonitors();
                if ((i & 2) != 0) {
                    java.lang.String s3 = "";
                    if (hashmap.get(s2) != null) {
                        s3 = "selected";
                    }
                    java.lang.StringBuffer stringbuffer6 = stringbuffer1;
                    if (s3.length() > 0 && (i & 0x80) != 0) {
                        stringbuffer6 = stringbuffer3;
                    }
                    stringbuffer6.append("\n<option ");
                    stringbuffer6.append(s3);
                    stringbuffer6.append(" value=\"");
                    stringbuffer6.append(s2);
                    stringbuffer6.append("\">");
                    if (monitorgroup.getTreeSetting("_truncateGroupName")
                            .length() > 0) {
                        java.lang.String s5 = monitorgroup
                                .getTreeSetting("_truncateGroupName");
                        int i1 = (new Integer(s5)).intValue();
                        java.lang.String s8 = s1.length() <= i1 ? s1 : s1
                                .substring(i1);
                        stringbuffer6.append(s8);
                    } else {
                        stringbuffer6.append(s1);
                    }
                }
                while (enumeration2.hasMoreElements()) {
                    COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor) enumeration2
                            .nextElement();
                    if (!(monitor instanceof COM.dragonflow.SiteView.SubGroup)
                            && (i & 1) != 0) {
                        java.lang.String s4 = "";
                        java.lang.String s6 = monitor
                                .getProperty(COM.dragonflow.SiteView.Monitor.pID);
                        java.lang.String s7;
                        if ((i & 0x20) != 0) {
                            s7 = s6 + " " + s2;
                        } else {
                            s7 = s2 + " " + s6;
                        }
                        if (hashmap.get(s7) != null) {
                            s4 = "selected";
                        }
                        java.lang.StringBuffer stringbuffer7 = stringbuffer;
                        if (s4.length() > 0 && (i & 0x80) != 0) {
                            stringbuffer7 = stringbuffer4;
                        }
                        stringbuffer7.append("\n<option ");
                        stringbuffer7.append(s4);
                        stringbuffer7.append(" value=\"");
                        stringbuffer7.append(s7);
                        stringbuffer7.append("\">");
                        if ((i & 8) == 0) {
                            if (monitor.getTreeSetting("_truncateGroupName")
                                    .length() > 0) {
                                java.lang.String s9 = monitor
                                        .getTreeSetting("_truncateGroupName");
                                int j1 = (new Integer(s9)).intValue();
                                java.lang.String s12 = s1.length() <= j1 ? s1
                                        : s1.substring(j1);
                                stringbuffer7.append(s12);
                            } else {
                                stringbuffer7.append(s1);
                            }
                            stringbuffer7.append(": ");
                        }
                        java.lang.String s10 = monitor
                                .getProperty(COM.dragonflow.SiteView.Monitor.pName);
                        if (monitor.getTreeSetting("_truncateMonitorName")
                                .length() > 0) {
                            java.lang.String s11 = monitor
                                    .getTreeSetting("_truncateMonitorName");
                            int k1 = (new Integer(s11)).intValue();
                            java.lang.String s13 = s10.length() <= k1 ? s10
                                    : s10.substring(k1);
                            stringbuffer7.append(s13);
                        } else {
                            stringbuffer7.append(s10);
                        }
                    }
                }
            }
        }

        return stringbuffer3.toString() + stringbuffer4.toString()
                + stringbuffer2.toString() + stringbuffer1.toString()
                + stringbuffer.toString();
    }

    public java.lang.String getSelectedOptionsHTML(jgl.Array array,
            java.lang.String s, java.lang.String s1, jgl.Array array1,
            jgl.Array array2, int i) throws java.lang.Exception {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        return stringbuffer.toString();
    }

    public jgl.Array getGroupNameList(jgl.HashMap hashmap,
            jgl.HashMap hashmap1, jgl.HashMap hashmap2, boolean flag) {
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        jgl.Array array = null;
        array = getAllowedGroupIDs();
        java.util.Enumeration enumeration = array.elements();
        jgl.Array array1 = new Array();
        java.lang.String s = "";
        java.lang.String s1 = null;
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if ((hashmap1 == null || hashmap1.get(s2) == null)
                    && (hashmap2 == null || hashmap2.get(s2) != null)) {
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup
                        .getElement(s2);
                if (monitorgroup != null
                        && (!flag || monitorgroup.getProperty(
                                COM.dragonflow.SiteView.MonitorGroup.pParent)
                                .length() <= 0)) {
                    java.lang.String s3 = COM.dragonflow.Page.CGI.getGroupPath(
                            monitorgroup, COM.dragonflow.Page.CGI
                                    .getGroupIDFull(s2, siteviewgroup), false);
                    hashmap.add(s3 + " (" + s2 + ")", monitorgroup);
                    if (!s2.equals(s)) {
                        if (s2.equals("__Health__")) {
                            s1 = s3 + " (" + s2 + ")";
                        } else {
                            array1.add(s3 + " (" + s2 + ")");
                        }
                    }
                    s = s2;
                }
            }
        } 
        
        jgl.Sorting.sort(array1, new LessString());
        if (s1 != null) {
            array1.insert(0, s1);
        }
        return array1;
    }

    void printProgressMessage(java.lang.String s) {
        if (s.length() > 0) {
            outputStream.println(s);
            outputStream.flush();
            COM.dragonflow.Log.LogManager.log("RunMonitor", "progress: " + s);
        }
    }

    public static java.lang.String getStartTimeHTML(long l) {
        java.util.Date date = COM.dragonflow.SiteView.Platform.makeDate();
        l *= 1000L;
        return COM.dragonflow.Page.CGI
                .getTimeHTML(
                        new Date(
                                (date.getTime() - (long) (COM.dragonflow.Utils.TextUtils.HOUR_SECONDS * 1000))
                                        + l), "start");
    }

    public static java.lang.String getEndTimeHTML(long l) {
        java.util.Date date = COM.dragonflow.SiteView.Platform.makeDate();
        l *= 1000L;
        return COM.dragonflow.Page.CGI.getTimeHTML(new Date(date.getTime() + l),
                "end");
    }

    public static java.lang.String getTimeHTML(java.util.Date date,
            java.lang.String s) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("<input type=text size=5 maxlength=5 name=");
        stringbuffer.append(s);
        stringbuffer.append("TimeTime value=\"");
        stringbuffer.append(COM.dragonflow.Utils.TextUtils
                .dateToMilitaryTime(date));
        stringbuffer.append("\"> ");
        stringbuffer.append("<input type=text size=10 maxlength=11 name=");
        stringbuffer.append(s);
        stringbuffer.append("TimeDate value=\"");
        stringbuffer.append(COM.dragonflow.Utils.TextUtils.prettyDateDate(date));
        stringbuffer.append("\"> ");
        return stringbuffer.toString();
    }

    public static java.lang.String getOptionsHTML(jgl.Array array,
            java.lang.String s) {
        java.util.Vector vector = new Vector();
        for (int i = 0; i < array.size(); i++) {
            vector.addElement(array.at(i));
        }

        return COM.dragonflow.Page.CGI.getOptionsHTML(vector, s);
    }

    public static java.lang.String getOptionsHTML(java.util.Vector vector,
            java.lang.String s) {
        jgl.HashMap hashmap = new HashMap();
        if (s.length() > 0) {
            hashmap.put(s, "true");
        }
        return COM.dragonflow.Page.CGI.getOptionsHTML(vector, hashmap);
    }

    public static java.lang.String getOptionsHTML(java.util.Vector vector,
            jgl.HashMap hashmap) {
        java.lang.String s = "";
        for (int i = 0; i < vector.size(); i += 2) {
            java.lang.String s1 = "";
            java.lang.String s3 = (java.lang.String) vector.elementAt(i);
            if (s3 != null
                    && (hashmap.get(s3) != null || i == 0
                            && hashmap.size() == 0)) {
                hashmap.remove(s3);
                s1 = "SELECTED ";
            }
            s = s + "<OPTION " + s1 + "value=\"" + s3 + "\">"
                    + vector.elementAt(i + 1) + "</OPTION>\n";
        }

        if (hashmap.size() > 0) {
            for (java.util.Enumeration enumeration = hashmap.keys(); enumeration
                    .hasMoreElements();) {
                java.lang.String s2 = (java.lang.String) enumeration
                        .nextElement();
                s = s + "<OPTION SELECTED value=\"" + s2 + "\">" + s2
                        + "</OPTION>\n";
            }

        }
        return s;
    }

    public static jgl.Array expandSubgroupIDs(java.lang.String s) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        return COM.dragonflow.Page.CGI.expandSubgroupIDs(s, null);
    }

    public static jgl.Array expandSubgroupIDs(java.lang.String s,
            COM.dragonflow.Page.CGI cgi) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        jgl.Array array = new Array();
        COM.dragonflow.Page.CGI.expandSubgroupIDs(s, array, cgi);
        return array;
    }

    public static void expandSubgroupIDs(java.lang.String s, jgl.Array array,
            COM.dragonflow.Page.CGI cgi) {
        COM.dragonflow.Utils.I18N.test(s, 0);
        java.lang.Object obj = COM.dragonflow.SiteView.SiteViewGroup
                .currentSiteView();
        if (cgi != null) {
            obj = cgi.getSiteView();
        }
        array.add(s);
        COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) ((COM.dragonflow.SiteView.SiteViewObject) (obj))
                .getElement(s);
        if (monitorgroup != null) {
            java.util.Enumeration enumeration = monitorgroup.getMonitors();
            while (enumeration.hasMoreElements()) {
                COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor) enumeration
                        .nextElement();
                if (monitor instanceof COM.dragonflow.SiteView.SubGroup) {
                    COM.dragonflow.Page.CGI
                            .expandSubgroupIDs(
                                    COM.dragonflow.Utils.I18N
                                            .toDefaultEncoding(monitor
                                                    .getProperty(COM.dragonflow.SiteView.SubGroup.pGroup)),
                                    array, cgi);
                }
            }
        }
    }

    public java.lang.String getPageLink(java.lang.String s, java.lang.String s1) {
        return getPageLink(s, s1, "");
    }

    public java.lang.String getPageLink(java.lang.String s,
            java.lang.String s1, java.lang.String s2) {
        java.lang.String s3 = "/SiteView/cgi/go.exe/SiteView?page=" + s
                + "&account=" + request.getAccount();
        if (s.startsWith("portal")) {
            java.lang.String s4 = request.getPortalServer();
            if (s4.length() > 0) {
                s3 = s3 + "&portalserver=" + s4;
            }
            java.lang.String s6 = request.getValue("rview");
            if (s6.length() > 0) {
                s3 = s3 + "&rview=" + s6;
            }
            if (request.getValue("detail").length() > 0) {
                java.lang.String s7 = request.getValue("detail");
                if (s7.indexOf('=') > 0) {
                    s7 = s7.substring(0, s7.indexOf('=')) + "%3D"
                            + s7.substring(s7.indexOf('=') + 1);
                }
                if (s7.indexOf('&') > 0) {
                    s7 = s7.substring(0, s7.indexOf('&')) + "%26"
                            + s7.substring(s7.indexOf('&') + 1);
                }
                s3 = s3 + "&detail=" + s7;
            }
        }
        java.lang.String s5 = COM.dragonflow.Utils.I18N
                .toDefaultEncoding(request.getValue("groupFilter"));
        if (s5.length() > 0) {
            s3 = s3 + "&groupFilter="
                    + COM.dragonflow.HTTP.HTTPRequest.encodeString(s5);
        }
        if (s1.length() > 0) {
            s3 = s3 + "&operation="
                    + COM.dragonflow.HTTP.HTTPRequest.encodeString(s1);
        }
        if (request.getValue("_health").length() > 0) {
            s3 = s3 + "&_health=true";
        }
        if (s2.length() > 0) {
            s3 = s3 + "&view="
                    + COM.dragonflow.HTTP.HTTPRequest.encodeString(s2);
        }
        return s3;
    }

    public java.lang.String getPagePOST(java.lang.String s, java.lang.String s1) {
        return getPagePOST(s, s1, "");
    }

    public java.lang.String getPagePOST(java.lang.String s,
            java.lang.String s1, java.lang.String s2) {
        return getPageForm(s, s1, "POST", s2);
    }

    public java.lang.String getPageGET(java.lang.String s, java.lang.String s1) {
        return getPageGET(s, s1, "");
    }

    public java.lang.String getPageGET(java.lang.String s, java.lang.String s1,
            java.lang.String s2) {
        return getPageForm(s, s1, "GET", s2);
    }

    public java.lang.String getPageForm(java.lang.String s,
            java.lang.String s1, java.lang.String s2) {
        return getPageForm(s, s1, s2, "");
    }

    public java.lang.String getPageForm(java.lang.String s,
            java.lang.String s1, java.lang.String s2, java.lang.String s3) {
        java.lang.String s4 = "<FORM ACTION=/SiteView/cgi/go.exe/SiteView method="
                + s2
                + ">\n"
                + "<input type=hidden name=page value="
                + s
                + ">\n"
                + "<input type=hidden name=account value=\""
                + request.getAccount() + "\">\n";
        if (s3.length() > 0) {
            s4 = s4 + "<input type=hidden name=view value=" + s3 + ">\n";
        }
        if (request.getValue("AWRequest").equals("yes")) {
            s4 = s4 + "<input type=hidden name=AWRequest value=yes>\n";
        }
        if (!s.startsWith("portal")) {
            java.lang.String s5 = request.getPortalServer();
            if (s5.length() > 0) {
                s4 = s4 + "<input type=hidden name=portalserver value=\"" + s5
                        + "\">\n";
            }
            java.lang.String s7 = request.getValue("rview");
            if (s7.length() > 0) {
                s4 = s4 + "<input type=hidden name=rview value=\"" + s7
                        + "\">\n";
            }
            if (request.getValue("detail").length() > 0) {
                s4 = s4 + "<input type=hidden name=detail value=\""
                        + request.getValue("detail") + "\">\n";
            }
        }
        java.lang.String s6 = request.getValue("groupFilter");
        if (s6.length() > 0) {
            s4 = s4 + "<input type=hidden name=groupFilter value=\"" + s6
                    + "\">\n";
        }
        if (s1.length() > 0) {
            s4 = s4 + "<input type=hidden name=operation value=\"" + s1
                    + "\">\n";
        }
        return s4;
    }

    boolean isPortalServerRequest() {
        if (request != null) {
            return COM.dragonflow.Page.CGI.isPortalServerRequest(request);
        } else {
            return false;
        }
    }

    public static boolean isPortalServerRequest(
            COM.dragonflow.HTTP.HTTPRequest httprequest) {
        if (httprequest != null) {
            return httprequest.getPortalServer().length() > 0;
        } else {
            return false;
        }
    }

    jgl.Array readMachines(java.lang.String s) throws java.io.IOException {
        jgl.Array array = new Array();
        jgl.HashMap hashmap = getMasterConfig();
        java.lang.String s1;
        for (java.util.Enumeration enumeration = hashmap.values(s); enumeration
                .hasMoreElements(); array.add(COM.dragonflow.Utils.TextUtils
                .stringToHashMap(s1))) {
            s1 = (java.lang.String) enumeration.nextElement();
            if (s1.indexOf("_id") >= 0) {
                continue;
            }
            java.lang.String s2 = "_nextRemoteID";
            if (s.equals("_remoteNTMachine")) {
                s2 = "_nextRemoteNTID";
            }
            java.lang.String s3 = COM.dragonflow.Utils.TextUtils.getValue(
                    hashmap, s2);
            if (s3.length() == 0) {
                s3 = "10";
            }
            s1 = s1 + " _id=" + s3;
            hashmap.put(s2, COM.dragonflow.Utils.TextUtils.increment(s3));
            saveMasterConfig(hashmap);
        }

        return array;
    }

    void saveMachines(jgl.Array array, java.lang.String s)
            throws java.io.IOException {
        jgl.HashMap hashmap = getMasterConfig();
        hashmap.remove(s);
        for (int i = 0; i < array.size(); i++) {
            jgl.HashMap hashmap1 = (jgl.HashMap) array.at(i);
            hashmap.add(s, COM.dragonflow.Utils.TextUtils
                    .hashMapToString(hashmap1));
        }

        saveMasterConfig(hashmap);
    }

    jgl.HashMap findMachine(jgl.Array array, java.lang.String s) {
        java.util.Enumeration enumeration = array.elements();
        jgl.HashMap hashmap = new HashMap();
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap1 = (jgl.HashMap) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.TextUtils.getValue(hashmap1,
                    "_id"))) {
            hashmap = hashmap1;
            break;
            }
        } 
        
        return hashmap;
    }

    protected static java.lang.String getListOptionHTML(java.lang.String s,
            java.lang.String s1, boolean flag) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("<option ");
        if (flag) {
            stringbuffer.append("SELECTED ");
        }
        stringbuffer.append("value=");
        stringbuffer.append(s);
        stringbuffer.append(">");
        stringbuffer.append(s1);
        stringbuffer.append("</option>\n");
        return stringbuffer.toString();
    }

    protected static java.lang.String getComboOptionHTML(java.lang.String s,
            boolean flag) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("<option ");
        if (flag) {
            stringbuffer.append("SELECTED");
        }
        stringbuffer.append(">");
        stringbuffer.append(s);
        stringbuffer.append("</option>\n");
        return stringbuffer.toString();
    }

    public int platformOS() {
        int i = COM.dragonflow.SiteView.Platform.getLocalPlatform();
        if (isPortalServerRequest()) {
            COM.dragonflow.SiteView.PortalSiteView portalsiteview = (COM.dragonflow.SiteView.PortalSiteView) COM.dragonflow.SiteView.Portal
                    .getSiteViewForServerID(COM.dragonflow.SiteView.Portal
                            .cleanPortalServerID(request.getPortalServer()));
            if (portalsiteview != null) {
                java.lang.String s = portalsiteview
                        .getProperty(COM.dragonflow.SiteView.PortalSiteView.pPlatformOS);
                i = COM.dragonflow.SiteView.Machine.stringToOS(s);
            }
        }
        return i;
    }

    private static void printNavBarMessages(java.io.PrintWriter printwriter) {
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig
                .getMasterConfig();
        if (COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_suspendMonitors")
                .equals("CHECKED")) {
            printwriter
                    .println("<TABLE class=\"subnav\" width=\"600\" bgcolor=\"#CCCCCC\" bordercolor=\"#666666\" border=\"1\" align=\"center\" cellpadding=\"2\" cellspacing=\"0\"><TR class=\"subnav\"><td><p class=\"navbar\" align=\"center\"> <font size=\"-1\" face=Arial, sans-serif><b>SiteView is in Suspended mode; no monitors are currently running.</b><br>To reactivate monitoring, clear the <b>Suspend Monitors</b> setting on the  <a href=/SiteView/docs/GenPref.htm#suspend target=\"Help\"> General Preferences</a> page.</font></p></TD></TR></TABLE>");
        }
        if (COM.dragonflow.SiteView.SiteViewGroup.currentSiteView()
                .hasCircularGroups()
                && COM.dragonflow.SiteView.SiteViewGroup.currentSiteView()
                        .checkForCircularGroups()) {
            printwriter
                    .println("<TABLE class=\"subnav\" width=\"600\" bgcolor=\"#CCCCCC\" bordercolor=\"#666666\" border=\"1\" align=\"center\" cellpadding=\"2\" cellspacing=\"0\"><TR class=\"subnav\"><td><p class=\"navbar\" align=\"center\"> <font size=\"-1\" face=Arial, sans-serif><b>A circular group hierarchy has been detected.  Check the error log for details.</b><br>It is recommended that SiteView be shut down until the problem is fixed. </font></p></TD></TR></TABLE>");
        }
    }

}
