 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

import java.io.FileOutputStream;
import java.util.Hashtable;
import java.util.Vector;

import jgl.Array;

// Referenced classes of package com.dragonflow.Utils:
// URLInfo, HTMLTagParser, TextUtils, SocketSession,
// FileUtils

public class LinkFinder
{

    public java.util.Hashtable ht;
    public int totalBroken;
    public int totalLeft;
    public int totalPages;
    public int totalGraphics;
    public long totalTime;
    public java.lang.String brokenSummary;
    public java.lang.String brokenLinks;
    java.lang.String reportPath;
    int maxLinks;
    com.dragonflow.StandardMonitor.LinkMonitor monitor;
    java.lang.String urlString;
    com.dragonflow.Utils.URLInfo start;
    boolean verifyExternalLinks;
    java.lang.String proxy;
    java.lang.String userName;
    java.lang.String password;
    java.lang.String proxyUserName;
    java.lang.String proxyPassword;
    jgl.Array postData;
    int timeout;
    int pause;
    com.dragonflow.Utils.SocketSession session;
    int maxSearchDepth;
    int currentDepth;
    long contentMax;
    long summaryMax;
    int debugLinkFinder;
    public java.util.Vector remaining;
    java.io.PrintWriter report;
    static final java.lang.String TARGET_TAGS[] = {
        "A", "IMG", "INPUT", "BODY", "BASE", "META", "FRAME", "IFRAME", "AREA"
    };

    public static void main(java.lang.String args[])
    {
        java.util.Hashtable hashtable = null;
        try
        {
            com.dragonflow.Utils.LinkFinder linkfinder = new LinkFinder(args[0], "", "", "", null, "", "", 60000, 250, 1000, 100, null, null);
            linkfinder.search(false);
            hashtable = linkfinder.ht;
        }
        catch(java.lang.Exception exception)
        {
            java.lang.System.out.println("Exception: " + exception);
        }
        java.lang.System.out.println("\nBroken Links-----------------------\n");
        java.util.Enumeration enumeration = hashtable.keys();
        while (enumeration.hasMoreElements())
            {
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            com.dragonflow.Utils.URLInfo urlinfo = (com.dragonflow.Utils.URLInfo)hashtable.get(s);
            if(urlinfo.status != 200)
            {
                java.lang.System.out.print("" + urlinfo.status + "    ");
                java.lang.System.out.println(urlinfo.url);
            }
        } 
        java.lang.System.out.println("\nGood Links-------------------------\n");
        enumeration = hashtable.keys();
        while (enumeration.hasMoreElements())
            {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            com.dragonflow.Utils.URLInfo urlinfo1 = (com.dragonflow.Utils.URLInfo)hashtable.get(s1);
            if(urlinfo1.status == 200)
            {
                java.lang.System.out.print("OK     ");
                java.lang.System.out.println(urlinfo1.url);
            }
        } 
    }

    public LinkFinder(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array, java.lang.String s4, java.lang.String s5, 
            int i, int j, int k, int l, java.lang.String s6, com.dragonflow.StandardMonitor.LinkMonitor linkmonitor)
    {
        ht = new Hashtable();
        totalBroken = 0;
        totalLeft = 0;
        totalPages = 0;
        totalGraphics = 0;
        totalTime = 0L;
        brokenSummary = "";
        brokenLinks = "";
        reportPath = null;
        maxLinks = 1000;
        monitor = null;
        urlString = "";
        start = null;
        verifyExternalLinks = true;
        proxy = "";
        userName = "";
        password = "";
        proxyUserName = "";
        proxyPassword = "";
        postData = null;
        timeout = com.dragonflow.StandardMonitor.URLMonitor.DEFAULT_TIMEOUT;
        pause = 250;
        maxSearchDepth = 100;
        currentDepth = 0;
        contentMax = 50000L;
        summaryMax = 500L;
        debugLinkFinder = 0;
        remaining = new Vector();
        report = null;
        urlString = s;
        proxy = s1;
        proxyUserName = s2;
        proxyPassword = s3;
        userName = s4;
        password = s5;
        postData = array;
        monitor = linkmonitor;
        timeout = i;
        reportPath = s6;
        maxLinks = k;
        maxSearchDepth = l;
        if(l < 1)
        {
            maxSearchDepth = 100;
        }
        if(j > pause)
        {
            pause = j;
        }
        if(linkmonitor != null)
        {
            contentMax = linkmonitor.getSettingAsLong("_urlContentMatchMax", (int)contentMax);
            summaryMax = linkmonitor.getSettingAsLong("_linkSummaryMax", (int)summaryMax);
        }
        java.lang.String s7 = java.lang.System.getProperty("LinkFinder.debug");
        if(s7 != null)
        {
            debugLinkFinder = com.dragonflow.Utils.TextUtils.toInt(s7);
            java.lang.System.out.println("debugLinkFinder=" + debugLinkFinder);
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param flag
     */
    public void search(boolean flag)
    {
        try {
            boolean flag1;
            java.util.Date date;
            session = com.dragonflow.Utils.SocketSession.getSession(monitor);
            if(reportPath != null)
            {
                report = com.dragonflow.Utils.FileUtils.MakeOutputWriter(new FileOutputStream(reportPath));
            }
            flag1 = monitor != null && monitor.getSetting("_linkMonitorJdbcEnabled").length() > 0 && com.dragonflow.Log.JdbcLogger.logger != null;
            date = com.dragonflow.SiteView.Platform.makeDate();
            report.println(com.dragonflow.Utils.TextUtils.dateToString());
            start = new URLInfo(urlString, true);
            start.source = "-";
            remaining.addElement(start);
            ht.put(urlString, start);
            
            java.util.Enumeration enumeration;
            while(remaining.size() > 0 && currentDepth <= maxSearchDepth)
            {
                currentDepth++;
                enumeration = remaining.elements();
                while (enumeration.hasMoreElements())
                {
                    if(monitor != null && !monitor.stillActive())
                    {
                        return;
                    }
                    if(totalPages < maxLinks)
                    {
                        com.dragonflow.Utils.URLInfo urlinfo = (com.dragonflow.Utils.URLInfo)enumeration.nextElement();
                        urlinfo.url = com.dragonflow.Utils.TextUtils.unescapeHTML(urlinfo.url);
                        findLinks(urlinfo, flag);
                        if(report != null)
                        {
                            urlinfo.print(report);
                            report.flush();
                        }
                        if(flag1)
                        {
                            java.lang.String as[] = {
                                    urlinfo.url, "" + urlinfo.status, urlinfo.contentType, "" + urlinfo.count, "" + urlinfo.externalLink, "" + urlinfo.duration, "" + urlinfo.size, urlinfo.source
                            };
                            com.dragonflow.Log.JdbcLogger.logger.logLink(date, monitor, as);
                        }
                    }
                }
                
                if(totalPages < maxLinks)
                {
                    remaining = findNewLinks();
                }
            }
            
        }
        catch (java.io.IOException ioexception) {
            com.dragonflow.Log.LogManager.log("Error", "Error writing link report: " + reportPath + ", " + ioexception.getMessage());
        }
        finally {
            session.close();
            monitor = null;
            if(report != null)
            {
                report.println("DONE");
                report.close();
            }
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    java.util.Vector findNewLinks()
    {
        java.util.Enumeration enumeration = ht.keys();
        java.util.Vector vector = new Vector();
        while (enumeration.hasMoreElements())
            {
            java.lang.String s = (java.lang.String)enumeration.nextElement();
            com.dragonflow.Utils.URLInfo urlinfo = (com.dragonflow.Utils.URLInfo)ht.get(s);
            if(!urlinfo.visited)
            {
                urlinfo.visited = true;
                if(!urlinfo.getHost().equalsIgnoreCase(start.getHost()))
                {
                    urlinfo.externalLink = true;
                }
                vector.addElement(urlinfo);
                totalLeft++;
            }
        } 
        return vector;
    }

    java.lang.String getContentType(java.lang.String s)
    {
        java.lang.String s1 = null;
        java.lang.String s2 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPHeaders(s);
        java.lang.String s3 = "Content-type: ";
        int i = s2.indexOf(s3);
        if(i == -1)
        {
            i = s2.indexOf("Content-Type: ");
        }
        if(i != -1)
        {
            int j = s2.indexOf('\n', i);
            if(j == -1)
            {
                s1 = s2.substring(i + s3.length());
            } else
            {
                s1 = s2.substring(i + s3.length(), j);
            }
        }
        return s1;
    }

    long[] checkOne(com.dragonflow.Utils.SocketSession socketsession, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, jgl.Array array, java.lang.String s4, 
            java.lang.String s5, java.lang.StringBuffer stringbuffer, long l, int i, java.lang.StringBuffer stringbuffer1)
    {
        java.lang.String s6 = "";
        stringbuffer1.setLength(0);
        stringbuffer.setLength(0);
        long al[] = com.dragonflow.StandardMonitor.URLMonitor.checkURL(socketsession, s, "", "", s1, s2, s3, array, s4, s5, s6, stringbuffer, l, "", 0, i, stringbuffer1);
        if(al[0] == 401L && s4.length() > 0)
        {
            stringbuffer1.setLength(0);
            stringbuffer.setLength(0);
            al = com.dragonflow.StandardMonitor.URLMonitor.checkURL(socketsession, s, "", "", s1, s2, s3, array, "", "", s6, stringbuffer, l, "", 0, i, stringbuffer1);
        }
        return al;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param urlinfo
     * @param flag
     */
    void findLinks(com.dragonflow.Utils.URLInfo urlinfo, boolean flag)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        long al[] = new long[3];
        al[0] = 0L;
        al[1] = 0L;
        al[2] = 0L;
        com.dragonflow.Utils.URLInfo urlinfo1 = urlinfo;
        long l = com.dragonflow.SiteView.Platform.timeMillis();
        if(monitor != null)
        {
            monitor.UpdateProperties(urlinfo.url, totalBroken, totalPages, totalGraphics, totalTime, totalLeft, brokenSummary, brokenLinks);
            com.dragonflow.StandardMonitor.LinkMonitor _tmp = monitor;
            com.dragonflow.Log.LogManager.log("RunMonitor", monitor.getProperty(com.dragonflow.StandardMonitor.LinkMonitor.pName) + ",  checking " + urlinfo.url);
        }
        boolean flag1 = false;
        if(urlinfo.url.endsWith(".map") || urlinfo.url.endsWith(".bin") || urlinfo.url.endsWith(".gz") || urlinfo.url.endsWith(".tar") || urlinfo.url.endsWith(".exe") || urlinfo.url.endsWith(".mov") || urlinfo.url.endsWith(".zip") || urlinfo.url.endsWith(".wav") || urlinfo.url.endsWith(".hqx"))
        {
            flag1 = true;
        }
        java.lang.String s = urlinfo.getProtocol().toLowerCase();
        if(!s.equals("http") && !s.equals("https"))
        {
            al[0] = -1L;
        } else
        {
            java.lang.StringBuffer stringbuffer1 = new StringBuffer();
            if(flag1)
            {
                jgl.Array array;
                if(postData == null)
                {
                    array = new Array();
                } else
                {
                    array = new Array(postData);
                }
                array.add("Method: HEAD");
                al = checkOne(session, urlinfo.url, proxy, proxyUserName, proxyPassword, array, userName, password, stringbuffer, contentMax, timeout, stringbuffer1);
                java.lang.String s3 = getContentType(stringbuffer.toString());
                if(s3 != null)
                {
                    s3 = s3.toLowerCase();
                    if(s3.indexOf("text") != -1)
                    {
                        flag1 = false;
                        al = checkOne(session, urlinfo.url, proxy, proxyUserName, proxyPassword, postData, userName, password, stringbuffer, contentMax, timeout, stringbuffer1);
                    }
                }
            } else
            {
                al = checkOne(session, urlinfo.url, proxy, proxyUserName, proxyPassword, postData, userName, password, stringbuffer, contentMax, timeout, stringbuffer1);
            }
            if(stringbuffer1.length() != 0)
            {
                urlinfo1 = new URLInfo(stringbuffer1.toString());
            }
            com.dragonflow.SiteView.Platform.sleep(pause);
        }
        postData = null;
        urlinfo.status = (int)al[0];
        if(urlinfo.status == 204)
        {
            urlinfo.status = 200;
        }
        if(flag1)
        {
            urlinfo.duration = -1L;
        } else
        {
            urlinfo.duration = al[1];
            if(urlinfo.duration == 0L)
            {
                urlinfo.duration = com.dragonflow.SiteView.Platform.timeMillis() - l;
            }
        }
        urlinfo.size = al[2];
        java.lang.String s1 = stringbuffer.toString();
        java.lang.String s2 = getContentType(s1);
        if(s2 != null)
        {
            urlinfo.setContentType(s2);
        }
        session.updateCookies(s1, urlinfo.url);
        if(urlinfo.contentType.startsWith("image/"))
        {
            totalGraphics++;
        }
        totalPages++;
        totalLeft--;
        if(urlinfo.status != 200 && urlinfo.status != -1)
        {
            totalBroken++;
            if(brokenLinks.length() != 0)
            {
                brokenLinks = ", ";
            }
            brokenLinks += urlinfo.url;
            if(!brokenSummary.endsWith("..."))
            {
                if(brokenSummary.length() == 0)
                {
                    brokenSummary = urlinfo.url;
                } else
                if((long)brokenSummary.length() > summaryMax)
                {
                    brokenSummary = brokenSummary + "...";
                } else
                {
                    brokenSummary = brokenSummary + ", " + urlinfo.url;
                }
            }
        } else
        {
            totalTime += urlinfo.duration;
        }
        if(monitor != null)
        {
            com.dragonflow.Log.LogManager.log("RunMonitor", urlinfo.url + ", " + urlinfo.status + ", " + urlinfo.duration + ", " + urlinfo.size + ", " + urlinfo.contentType);
        }
        if(urlinfo.status == 200 && urlinfo.contentType.equals("text/html") && (!urlinfo.externalLink || flag))
        {
            java.lang.String s4 = com.dragonflow.StandardMonitor.URLMonitor.getHTTPContent(s1);
            if(debugLinkFinder > 0)
            {
                java.lang.System.out.println("LinkFinder FINDING LINKS ON THIS URL: " + urlinfo.url);
            }
            if(debugLinkFinder > 0)
            {
                java.lang.System.out.println("LinkFinder FINDING LINKS ON THIS PAGE: " + s4);
            }
            com.dragonflow.Utils.HTMLTagParser htmltagparser = new HTMLTagParser(s4, TARGET_TAGS);
            htmltagparser.process();
            java.lang.String s6 = "";
            java.util.Enumeration enumeration = htmltagparser.findTags("base");
            if(enumeration.hasMoreElements())
            {
                jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                s6 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "href");
            }
            if(debugLinkFinder > 0)
            {
                java.lang.System.out.println("LinkFinder base URL: " + s6);
            }
            enumeration = htmltagparser.findTags("body");
            if(enumeration.hasMoreElements())
            {
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s7 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "background");
                if(s7.length() > 0)
                {
                    addURL(urlinfo1, s7, s6, true);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder body tag image URL: " + s7);
                    }
                }
            }
            enumeration = htmltagparser.findTags("meta");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap2 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s8 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "http-equiv").toLowerCase();
                if(s8.equals("refresh"))
                {
                    java.lang.String s15 = com.dragonflow.Utils.TextUtils.getValue(hashmap2, "content");
                    java.lang.String s5 = com.dragonflow.Utils.TextUtils.removeChars(s15, "\"");
                    java.lang.String s16 = s15.toLowerCase();
                    int i = s16.indexOf("url=");
                    java.lang.String s17 = "";
                    if(i != -1)
                    {
                        java.lang.String s18 = s15.substring(i + 4);
                        addURL(urlinfo1, s18, s6);
                        if(debugLinkFinder > 0)
                        {
                            java.lang.System.out.println("LinkFinder meta tag URL: " + s18);
                        }
                    }
                }
            } 
            enumeration = htmltagparser.findTags("img");
            while(enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap3 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s9 = com.dragonflow.Utils.TextUtils.getValue(hashmap3, "src");
                if(s9.length() > 0)
                {
                    addURL(urlinfo1, s9, s6, true);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder img tag src URL: " + s9);
                    }
                }
            } 
            enumeration = htmltagparser.findTags("input");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap4 = (jgl.HashMap)enumeration.nextElement();
                if(com.dragonflow.Utils.TextUtils.getValue(hashmap4, "type").equals("image"))
                {
                    java.lang.String s10 = com.dragonflow.Utils.TextUtils.getValue(hashmap4, "src");
                    if(s10.length() > 0)
                    {
                        addURL(urlinfo1, s10, s6, true);
                        if(debugLinkFinder > 0)
                        {
                            java.lang.System.out.println("LinkFinder input tag image src URL: " + s10);
                        }
                    }
                }
            }
            enumeration = htmltagparser.findTags("a");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap5 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s11 = com.dragonflow.Utils.TextUtils.getValue(hashmap5, "href");
                if(s11.length() > 0)
                {
                    addURL(urlinfo1, s11, s6);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder A tag href link URL: " + s11);
                    }
                }
            } 
            enumeration = htmltagparser.findTags("frame");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap6 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s12 = com.dragonflow.Utils.TextUtils.getValue(hashmap6, "src");
                if(s12.length() > 0)
                {
                    addURL(urlinfo1, s12, s6);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder frame tag src link URL: " + s12);
                    }
                }
            } 
            enumeration = htmltagparser.findTags("iframe");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap7 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s13 = com.dragonflow.Utils.TextUtils.getValue(hashmap7, "src");
                if(s13.length() > 0)
                {
                    addURL(urlinfo1, s13, s6);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder iframe tag src link URL: " + s13);
                    }
                }
            } 
            enumeration = htmltagparser.findTags("area");
            while (enumeration.hasMoreElements())
                {
                jgl.HashMap hashmap8 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s14 = com.dragonflow.Utils.TextUtils.getValue(hashmap8, "href");
                if(s14.length() > 0)
                {
                    addURL(urlinfo1, s14, s6);
                    if(debugLinkFinder > 0)
                    {
                        java.lang.System.out.println("LinkFinder area tag href link URL: " + s14);
                    }
                }
            } 
        }
    }

    void addURL(com.dragonflow.Utils.URLInfo urlinfo, java.lang.String s, java.lang.String s1)
    {
        addURL(urlinfo, s, s1, false);
    }

    void addURL(com.dragonflow.Utils.URLInfo urlinfo, java.lang.String s, java.lang.String s1, boolean flag)
    {
        if(s.startsWith("\""))
        {
            s = s.substring(1, s.length() - 1);
        }
        s = s.trim();
        java.lang.String s2 = s.toLowerCase();
        if(s2.startsWith("#"))
        {
            return;
        }
        if(!s2.startsWith("javascript:") && !s2.startsWith("mailto:") && !s2.startsWith("news:") && !s2.startsWith("ftp://"))
        {
            s = com.dragonflow.StandardMonitor.URLMonitor.resolveURL(s, urlinfo, s1);
            int i = s.lastIndexOf("#");
            if(i >= 0)
            {
                s = s.substring(0, i);
            }
        }
        com.dragonflow.Utils.URLInfo urlinfo1 = (com.dragonflow.Utils.URLInfo)ht.get(s);
        if(urlinfo1 == null)
        {
            urlinfo1 = new URLInfo(s, urlinfo.url);
            urlinfo.addChild(urlinfo1);
        }
        urlinfo1.count++;
        ht.put(urlinfo1.url, urlinfo1);
    }

}
