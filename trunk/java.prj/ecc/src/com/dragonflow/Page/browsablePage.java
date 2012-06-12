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
import COM.datachannel.xml.om.Document;

// Referenced classes of package com.dragonflow.Page:
// CGI, monitorPage

public class browsablePage extends com.dragonflow.Page.CGI
{

    public static final java.lang.String COUNTERS_PAGE = "countersPage";
    public static final java.lang.String YES = "yes";
    boolean debug;
    java.lang.String OPEN;
    java.lang.String CLOSE;
    java.lang.String help;
    java.lang.String operation;
    boolean fooSet;

    public browsablePage()
    {
        debug = false;
        OPEN = "open";
        CLOSE = "close";
        help = "BrowseCtrPage.htm";
        operation = "";
        fooSet = false;
    }

    private void buildNodeList(jgl.Array array, org.w3c.dom.Node node)
    {
        if(node == null || !node.hasChildNodes())
        {
            return;
        }
        org.w3c.dom.NodeList nodelist = node.getChildNodes();
        int i = nodelist.getLength();
        for(int j = 0; j < i; j++)
        {
            org.w3c.dom.Node node1 = nodelist.item(j);
            array.add(node1);
            buildNodeList(array, node1);
        }

    }

    private int getCounterSize(jgl.HashMap hashmap, jgl.HashMap hashmap1, java.lang.String s, com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        java.util.Enumeration enumeration = hashmap.keys();
        int i = hashmap1.size();
        if(enumeration.hasMoreElements())
        {
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                java.lang.String s1 = (java.lang.String)enumeration.nextElement();
                if(s1.endsWith("object"))
                {
                    java.lang.String s2 = s1.substring(0, s1.indexOf("object"));
                    COM.datachannel.xml.om.Document document = com.dragonflow.SiteView.BrowsableCache.getXml(s);
                    if(document.getDocumentElement() != null)
                    {
                        jgl.Array array = new Array();
                        org.w3c.dom.NodeList nodelist = document.getDocumentElement().getChildNodes();
                        int j = nodelist.getLength();
                        org.w3c.dom.Node node = null;
                        for(int l = 0; l < j; l++)
                        {
                            array.add(nodelist.item(l));
                            buildNodeList(array, nodelist.item(l));
                        }

                        for(int i1 = 0; i1 < array.size(); i1++)
                        {
                            org.w3c.dom.Node node1 = (org.w3c.dom.Node)array.at(i1);
                            if(node1 == null || !node1.getNodeName().equals("object"))
                            {
                                continue;
                            }
                            java.lang.String s3 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseName(com.dragonflow.Page.browsablePage.getNodeDisplayNames(node1));
                            if(!s3.equals(java.net.URLDecoder.decode(s2)))
                            {
                                continue;
                            }
                            node = node1;
                            break;
                        }

                        if(node != null)
                        {
                            org.w3c.dom.NodeList nodelist1 = node.getChildNodes();
                            int k = nodelist1.getLength();
                            array.clear();
                            for(int j1 = 0; j1 < k; j1++)
                            {
                                array.add(nodelist1.item(j1));
                                buildNodeList(array, nodelist1.item(j1));
                            }

                            int k1 = 0;
                            while(k1 < array.size()) 
                            {
                                org.w3c.dom.Node node2 = (org.w3c.dom.Node)array.at(k1);
                                if(node2.getNodeName().equals("counter"))
                                {
                                    java.lang.String s4 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseName(com.dragonflow.Page.browsablePage.getNodeDisplayNames(node2));
                                    if(hashmap.get(java.net.URLEncoder.encode(s4)) == null && hashmap1.get(s4) == null)
                                    {
                                        i++;
                                    }
                                }
                                k1++;
                            }
                        }
                    }
                } else
                if(hashmap1.get(s1) == null)
                {
                    i++;
                }
            } while(true);
        }
        return i;
    }

    public void printBody()
        throws java.lang.Exception
    {
        boolean flag = request.isPost();
        if(request.getValue("countersPage").equals("yes"))
        {
            flag = true;
        }
        if(!flag)
        {
            printBodyHeader("Choose Counters");
            printButtonBar(help, "");
        }
        com.dragonflow.SiteView.AtomicMonitor atomicmonitor = null;
        java.lang.String s = request.getValue("returnURL");
        java.lang.String s1 = getURLparm(s, "class");
        java.lang.String s2 = getURLparm(s, "group");
        Object obj = null;
        if(s1.length() == 0)
        {
            java.lang.String s3 = getURLparm(s, "id");
            jgl.Array array = ReadGroupFrames(s2);
            atomicmonitor = com.dragonflow.SiteView.AtomicMonitor.MonitorCreate(array, s3, request.getPortalServer(), request);
            s1 = (java.lang.String)atomicmonitor.getClassProperty("class");
        } else
        {
            atomicmonitor = com.dragonflow.SiteView.AtomicMonitor.MonitorCreate(s1, request);
        }
        if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
        {
            com.dragonflow.SiteView.AtomicMonitor atomicmonitor1 = atomicmonitor;
            if((atomicmonitor instanceof com.dragonflow.SiteView.IServerPropMonitor) && request.hasValue("server"))
            {
                java.lang.String s4 = request.getValue("server");
                jgl.HashMap hashmap3 = com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), false, false);
                jgl.HashMap hashmap5 = (jgl.HashMap)hashmap3.get("cParms");
                java.lang.String s5 = ((com.dragonflow.SiteView.IServerPropMonitor)atomicmonitor).getServerProperty().getName();
                hashmap5.put(s5, s4);
            }
            if(!flag)
            {
                outputStream.println("<H3>Choose Server for: " + (java.lang.String)atomicmonitor1.getClassProperty("title") + " Monitor</H3><P>\n");
            }
            if(com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), false, false) == null)
            {
                outputStream.println("<P><BR><BR><FONT SIZE=+2><B>An error has occurred, please retry.</B></FONT><BR><BR>This is most likely due to a SiteView restart or the current cache of counters timing out.<BR><BR>Click on <A HREF=/SiteView/" + request.getAccountDirectory() + "/SiteView.html" + " >this link</A> to return to the main SiteView page.");
                return;
            }
            if(flag)
            {
                operation = request.getValue("submit");
                com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), true, false);
                if(!operation.equals("Browse") && !operation.equals("Choose"))
                {
                    com.dragonflow.SiteView.BrowsableCache.mergeSelections((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1, request.getValue("uniqueID"), false, "visible", request, false);
                }
                if(operation.equals("Cancel"))
                {
                    com.dragonflow.SiteView.BrowsableCache.updateCache(request.getValue("uniqueID"));
                    printRefreshPage(request.getValue("returnURL"), 0);
                    return;
                }
                if(operation.equals("Choose"))
                {
                    int i = atomicmonitor1.getMaxCounters();
                    jgl.Array array1 = com.dragonflow.SiteView.BrowsableCache.getSelections(request.getValue("uniqueID"), true, true);
                    jgl.HashMap hashmap6 = (jgl.HashMap)array1.at(0);
                    com.dragonflow.SiteView.BrowsableCache.mergeSelections((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1, request.getValue("uniqueID"), false, "visible", request, false);
                    jgl.Array array2 = com.dragonflow.SiteView.BrowsableCache.getSelections(request.getValue("uniqueID"), true, false);
                    jgl.HashMap hashmap9 = (jgl.HashMap)array2.at(0);
                    int k = getCounterSize((jgl.HashMap)hashmap9.clone(), (jgl.HashMap)hashmap6.clone(), request.getValue("uniqueID"), atomicmonitor);
                    if(k > i)
                    {
                        outputStream.println("<H3>Error: Too many counters selected.</H3>\n<P>Your " + k + " selections " + "exceeds the allowed limit of " + i + " counters. Hint:<i>\"Clear Selections\" will remove all " + "selections so that you can start over.</i><p>");
                    } else
                    {
                        com.dragonflow.SiteView.BrowsableCache.mergeSelections((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1, request.getValue("uniqueID"), false, "visible", request, true);
                        com.dragonflow.SiteView.BrowsableCache.updateCache(request.getValue("uniqueID"));
                        java.lang.String s7 = request.getValue("returnURL");
                        s7 = com.dragonflow.HTTP.HTTPRequest.removeParameter(s7, "uniqueID");
                        s7 = s7 + "&uniqueID=" + request.getValue("uniqueID");
                        printRefreshPage(s7, 0);
                        return;
                    }
                }
                jgl.HashMap hashmap = new HashMap();
                
				if(operation.equals("Browse"))
                {
					try
					{					
	                    jgl.HashMap hashmap4 = com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), false, false);
	                    jgl.HashMap hashmap7 = (jgl.HashMap)hashmap4.get("cParms");
	                    jgl.Array array3 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1).getConnectionProperties();
	                    for(int j = 0; j < array3.size(); j++)
	                    {
	                        com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)array3.at(j);
	                        java.lang.String s8 = request.getValue(stringproperty.getName());
	                        if(!stringproperty.isPassword || !s8.equals("*********"))
	                        {
								if(j==11)
								{
									int mmmm=1;
								};	
	                            s8 = atomicmonitor1.verify(stringproperty, s8, request, hashmap);
	                            atomicmonitor1.setProperty(stringproperty, s8);
	                        } else
	                        {
	                            s8 = atomicmonitor1.getProperty(stringproperty);
	                        }
	                        hashmap7.put(stringproperty.getName(), s8);
	                    }
					}catch(Exception err)
					{
						System.out.println(err.getMessage());
					}
				

                }
                if(!hashmap.isEmpty() || operation.equals("Back"))
                {
                    printConnectionProperties(atomicmonitor1, hashmap, null);
                } else
                {
                    if(operation.equals("Clear Selections") || operation.equals("Reload Counters"))
                    {
                        com.dragonflow.SiteView.BrowsableCache.clearState(request.getValue("uniqueID"));
                        com.dragonflow.SiteView.BrowsableCache.clearSelections(request.getValue("uniqueID"));
                    }
                    java.lang.StringBuffer stringbuffer = new StringBuffer("");
                    COM.datachannel.xml.om.Document document = new Document();
                    if(operation.equals("Browse") || operation.equals("Reload Counters") || com.dragonflow.SiteView.BrowsableCache.getXml(request.getValue("uniqueID")).getReadyState() == 0)
                    {
                        jgl.HashMap hashmap8 = com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), false, false);
                        jgl.HashMap hashmap10 = (jgl.HashMap)hashmap8.get("cParms");
                        java.util.Enumeration enumeration = hashmap10.keys();
                        if(enumeration.hasMoreElements())
                        {
                            java.lang.String s9;
                            for(; enumeration.hasMoreElements(); atomicmonitor1.setProperty(s9, (java.lang.String)hashmap10.get(s9)))
                            {
                                s9 = (java.lang.String)enumeration.nextElement();
                            }

                        }
                        java.lang.String s10 = "";
                        boolean flag1 = true;
                        java.lang.String s12 = "";
                        if(atomicmonitor instanceof com.dragonflow.SiteView.BrowsableMonitor)
                        {
                            flag1 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1).isUsingCountersCache();
                        }
                        if(flag1)
                        {
                            s12 = com.dragonflow.SiteView.BrowsableCache.getXmlFileName(atomicmonitor1);
                            if(operation.equals("Reload Counters"))
                            {
                                com.dragonflow.SiteView.BrowsableCache.deleteXmlFile(s12);
                                s10 = "";
                            } else
                            {
                                s10 = com.dragonflow.SiteView.BrowsableCache.getXmlFile(s12);
                            }
                        }
                        if(s10.length() == 0)
                        {
                            jgl.Array array5 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1).getConnectionProperties();
                            if(array5.size() > 0)
                            {
                                java.lang.String s13 = ((com.dragonflow.Properties.StringProperty)array5.at(0)).getName();
                                java.lang.String s14 = (java.lang.String)hashmap10.get(s13);
                                outputStream.println("Please wait while counters are retrieved from \"" + s14 + "\" . . . ");
                                outputStream.flush();
                            }
                            s10 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1).getBrowseData(stringbuffer).trim();
                            if(stringbuffer.length() == 0 && flag1)
                            {
                                com.dragonflow.SiteView.BrowsableCache.saveXmlFile(s12, s10);
                            }
                            if(!flag)
                            {
                                outputStream.println("completed!<BR>");
                            }
                        }
                        if(stringbuffer.length() == 0)
                        {
                            try
                            {
                                long l1 = 0L;
                                if(debug)
                                {
                                    l1 = com.dragonflow.SiteView.Platform.timeMillis();
                                }
                                document.setValidateOnParse(false);
                                document.loadXML(s10);
                                if(debug)
                                {
                                    com.dragonflow.Log.LogManager.log("RunMonitor", "Loaded Document, time=" + (com.dragonflow.SiteView.Platform.timeMillis() - l1) + "ms");
                                }
                            }
                            catch(java.lang.Exception exception)
                            {
                                com.dragonflow.Log.LogManager.log("error", "Error loading XML document (loadXML())");
                                if(flag1)
                                {
                                    com.dragonflow.SiteView.BrowsableCache.deleteXmlFile(s12);
                                }
                                java.lang.String s11 = "";
                                stringbuffer.append("Error load XML document, invalid format");
                            }
                        }
                    } else
                    {
                        document = com.dragonflow.SiteView.BrowsableCache.getXml(request.getValue("uniqueID"));
                    }
                    if(stringbuffer.length() > 0)
                    {
                        if((atomicmonitor1 instanceof com.dragonflow.SiteView.BrowsableMonitor) && !((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor1).isServerBased())
                        {
                            com.dragonflow.Page.monitorPage monitorpage = new monitorPage();
                            jgl.Array array4 = atomicmonitor1.getPropertiesToPassBetweenPages(request);
                            for(int l = 0; l < array4.size(); l++)
                            {
                                com.dragonflow.Properties.StringProperty stringproperty1 = (com.dragonflow.Properties.StringProperty)array4.at(l);
                                request.rawURL = com.dragonflow.HTTP.HTTPRequest.removeParameter(request.rawURL, stringproperty1.getName());
                            }

                            request.rawURL = com.dragonflow.HTTP.HTTPRequest.removeParameter(request.rawURL, "returnURL");
                            request.overrideParam("page", "monitor");
                            request.overrideParam("operation", "Add");
                            request.overrideParam("class", s1);
                            request.overrideParam("group", s2);
                            request.overrideParam("browseDataError", stringbuffer.toString());
                            request.requestMethod = "POST";
                            monitorpage.initialize(request, outputStream);
                            java.lang.String s6 = com.dragonflow.Utils.I18N.UnicodeToString(s2, com.dragonflow.Utils.I18N.nullEncoding());
                            monitorpage.printAddForm("Add", s2, s6);
                        } else
                        {
                            jgl.HashMap hashmap1 = new HashMap();
                            printConnectionProperties(atomicmonitor1, hashmap1, stringbuffer);
                        }
                    } else
                    {
                        outputStream.println("<P>SiteView can monitor these objects.  Choose up to " + atomicmonitor1.getMaxCounters() + " counters.<p>");
                        outputStream.println(getPagePOST("browsable", "") + "<input type=hidden name=returnURL value=" + request.getValue("returnURL") + ">\n");
                        outputStream.println("<input type=submit name=submit value=ExpandAll></input>\n");
                        outputStream.println("<input type=submit name=submit value=\"Clear Selections\"></input>\n");
                        outputStream.println("<input type=submit name=submit value=\"Reload Counters\"></input>\n");
                        outputStream.println("<input type=submit name=submit value=\"Cancel\"></input>\n");
                        outputStream.println("<HR>(Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"" + OPEN + "\"> to expand, and the " + "<img src=/SiteView/htdocs/artwork/Minus.gif alt=\"" + CLOSE + "\"> to collapse).<P>");
                        outputStream.println("<input type=submit name=submit value=Choose> Counters</input><br><br>\n");
                        outputStream.println("<TABLE>");
                        printXML(document, outputStream, atomicmonitor1);
                        outputStream.print("</TABLE>");
                        outputStream.println("<br><input type=hidden name=uniqueID value=\"" + request.getValue("uniqueID") + "\"></input>" + "<input type=submit name=submit value=Choose> Counters</input>\n");
                        com.dragonflow.SiteView.BrowsableCache.saveXml(request.getValue("uniqueID"), document);
                        outputStream.println("</FORM><p>\n");
                    }
                }
            } else
            {
                jgl.HashMap hashmap2 = new HashMap();
                printConnectionProperties(atomicmonitor1, hashmap2, null);
            }
        } else
        {
            outputStream.println("<B>Invalid Browsable Monitor</B>");
        }
        printFooter(outputStream);
        if(fooSet)
        {
            outputStream.print("<SCRIPT LANGUAGE = \"JavaScript\">window.location.href=\"#foo\"</SCRIPT>\n");
        }
        com.dragonflow.SiteView.BrowsableCache.saveCache(request.getValue("uniqueID"));
    }

    java.lang.String getURLparm(java.lang.String s, java.lang.String s1)
    {
        java.lang.String s2 = "";
        try
        {
            int i = s.indexOf("&" + s1 + "=");
            if(i == -1)
            {
                i = s.indexOf("?" + s1 + "=");
            }
            if(i >= 0)
            {
                i += 2 + s1.length();
                int j = s.substring(i).indexOf("&");
                if(j >= 0)
                {
                    s2 = s.substring(i, i + j);
                } else
                {
                    s2 = s.substring(i);
                }
            }
        }
        catch(java.lang.Exception exception)
        {
            s2 = "";
        }
        return s2;
    }

    void printConnectionProperties(com.dragonflow.SiteView.AtomicMonitor atomicmonitor, jgl.HashMap hashmap, java.lang.StringBuffer stringbuffer)
    {
        if(stringbuffer != null && stringbuffer.length() > 0)
        {
            outputStream.println("<P><BR><B>" + stringbuffer + "</B><BR><BR><I>Verify that the following parameters are correct.</I><BR>");
        } else
        {
            outputStream.println("<P><BR>Enter the following information and press the \"Browse\" button to see the list of available counters.<BR><BR>");
        }
        outputStream.println(getPagePOST("browsable", "") + "<TABLE>" + "<input type=hidden name=returnURL value=" + request.getValue("returnURL") + "><BR>");
        jgl.HashMap hashmap1 = com.dragonflow.SiteView.BrowsableCache.getCache(request.getValue("uniqueID"), false, false);
        jgl.HashMap hashmap2 = (jgl.HashMap)hashmap1.get("cParms");
        jgl.Array array = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).getConnectionProperties();
        for(int i = 0; i < array.size(); i++)
        {
            com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)array.at(i);
            atomicmonitor.setProperty(stringproperty.getName(), (java.lang.String)hashmap2.get(stringproperty.getName()));
            stringproperty.printProperty(this, outputStream, atomicmonitor, request, hashmap, true);
        }

        java.lang.String s = request.getValue("uniqueID");
        outputStream.println("</tr><td><input type=hidden name=uniqueID value=\"" + s + "\"></input>" + "</td><td><input type=submit name=submit value=Browse> Counters</input></td></tr>" + "</TABLE></FORM><p>\n");
    }

    public void printXML(COM.datachannel.xml.om.Document document, java.io.PrintWriter printwriter, com.dragonflow.SiteView.AtomicMonitor atomicmonitor)
        throws java.lang.Exception
    {
        if(document.getDocumentElement() != null)
        {
            try
            {
                java.lang.String s = "";
                boolean flag = false;
                jgl.HashMap hashmap = com.dragonflow.SiteView.BrowsableCache.getCurrentState(request.getValue("uniqueID"));
                java.util.Enumeration enumeration = request.getVariables();
                do
                {
                    if(!enumeration.hasMoreElements())
                    {
                        break;
                    }
                    java.lang.String s1 = (java.lang.String)enumeration.nextElement();
                    s1 = java.net.URLDecoder.decode(s1);
                    if(s1.startsWith(OPEN))
                    {
                        java.lang.String s2 = s1.substring(OPEN.length(), s1.length() - 2);
                        s = s2;
                        if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s2).equals(OPEN))
                        {
                            hashmap.put(s2, OPEN);
                            flag = true;
                        }
                    }
                    if(s1.startsWith(CLOSE))
                    {
                        java.lang.String s3 = s1.substring(CLOSE.length(), s1.length() - 2);
                        s = s3;
                        if(!com.dragonflow.Utils.TextUtils.getValue(hashmap, s3).equals(CLOSE))
                        {
                            hashmap.remove(s3);
                            flag = true;
                        }
                    }
                } while(true);
                jgl.Array array = com.dragonflow.SiteView.BrowsableCache.getSelections(request.getValue("uniqueID"), true, false);
                org.w3c.dom.NodeList nodelist = document.getDocumentElement().getChildNodes();
                int i = nodelist.getLength();
                long l = 0L;
                if(debug)
                {
                    l = com.dragonflow.SiteView.Platform.timeMillis();
                }
                for(int j = 0; j < i; j++)
                {
                    printNode(printwriter, nodelist.item(j), 1, hashmap, array, atomicmonitor, s);
                }

                if(debug)
                {
                    com.dragonflow.Log.LogManager.log("RunMonitor", "Printed Nodes, time=" + (com.dragonflow.SiteView.Platform.timeMillis() - l) + "ms");
                }
                if(flag || operation.equals("Clear Selections") || operation.equals("ExpandAll"))
                {
                    com.dragonflow.SiteView.BrowsableCache.saveCurrentState(request.getValue("uniqueID"), hashmap);
                }
            }
            catch(COM.datachannel.xml.om.XMLDOMException xmldomexception)
            {
                com.dragonflow.Log.LogManager.log("error", "browsablePage.printXML Exception, " + xmldomexception.getMessage());
                printwriter.println("Error loading XML document");
            }
        } else
        {
            com.dragonflow.Log.LogManager.log("error", "browsablePage.printXML Document Element is null");
            printwriter.println("Error loading XML document");
        }
    }

    public void printNode(java.io.PrintWriter printwriter, org.w3c.dom.Node node, int i, jgl.HashMap hashmap, jgl.Array array, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.lang.String s)
    {
        if(node.getNodeType() == 1)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(0);
            jgl.HashMap hashmap2 = (jgl.HashMap)array.at(1);
            boolean flag = false;
            org.w3c.dom.NodeList nodelist = node.getChildNodes();
            int j = nodelist.getLength();
            java.lang.String s1 = ((org.w3c.dom.Element)node).getAttribute("name");
            java.lang.String s2 = ((org.w3c.dom.Element)node).getAttribute("desc");
            java.lang.String s3 = ((org.w3c.dom.Element)node).getAttribute("bold");
            if(s1 != null)
            {
                java.lang.String s4 = getIndentHTML(i);
                printwriter.print("<TR><TD>");
                printwriter.print(s4);
                java.lang.String s6 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseName(com.dragonflow.Page.browsablePage.getNodeDisplayNames(node));
                if(operation.equals("ExpandAll"))
                {
                    if(hashmap.get(s6) == null)
                    {
                        hashmap.put(s6, OPEN);
                    }
                    flag = true;
                } else
                {
                    flag = hashmap.get(s6) != null;
                }
                java.lang.String s7 = node.getNodeName();
                if(s7.toLowerCase().equals("counter"))
                {
                    java.lang.String s8 = ((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).setBrowseID(com.dragonflow.Page.browsablePage.getNodeIdNames(node));
                    java.lang.String s10 = (java.lang.String)hashmap1.get(java.net.URLEncoder.encode(s6));
                    if(((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor).manageBrowsableSelectionsByID())
                    {
                        if(isIDSelected((com.dragonflow.SiteView.BrowsableMonitor)atomicmonitor, s8, hashmap2))
                        {
                            s10 = "CHECKED";
                        }
                    } else
                    if(s10 != null)
                    {
                        s10 = "CHECKED";
                        hashmap1.put(java.net.URLEncoder.encode(s6), "visible");
                        hashmap2.put(java.net.URLEncoder.encode(s6), java.net.URLEncoder.encode(s8));
                    } else
                    {
                        s10 = "";
                    }
                    if(s3 != null && s3.length() > 0)
                    {
                        printwriter.print("<input type=checkbox name=\"" + com.dragonflow.Properties.BrowsableProperty.BROWSE + "\" value=\"" + java.net.URLEncoder.encode(s6) + "\" " + s10 + ">" + "<input type=hidden name=\"SELECTED" + java.net.URLEncoder.encode(s6) + "ID\"" + " value=\"" + java.net.URLEncoder.encode(s8) + "\"> " + "<B>" + s1 + "</B>" + (s2 == null || s2.length() <= 0 ? "" : "<img src=/SiteView/htdocs/artwork/info.gif alt=\"" + s2 + "\">") + "</TD></TR>");
                    } else
                    {
                        printwriter.print("<input type=checkbox name=\"" + com.dragonflow.Properties.BrowsableProperty.BROWSE + "\" value=\"" + java.net.URLEncoder.encode(s6) + "\" " + s10 + ">" + "<input type=hidden name=\"SELECTED" + java.net.URLEncoder.encode(s6) + "ID\"" + " value=\"" + java.net.URLEncoder.encode(s8) + "\"> " + s1 + (s2 == null || s2.length() <= 0 ? "" : "<img src=/SiteView/htdocs/artwork/info.gif alt=\"" + s2 + "\">") + "</TD></TR>");
                    }
                } else
                {
                    java.lang.String s9 = (java.lang.String)hashmap1.get(java.net.URLEncoder.encode(s6) + "object");
                    if(s9 != null)
                    {
                        s9 = "CHECKED";
                        hashmap1.put(java.net.URLEncoder.encode(s6) + "object", "visible");
                        hashmap2.put(java.net.URLEncoder.encode(s6) + "object", java.net.URLEncoder.encode(s6));
                    } else
                    {
                        s9 = "";
                    }
                    if(s.equals(s6))
                    {
                        printwriter.print("<A NAME=foo></a>\n");
                        fooSet = true;
                    }
                    printwriter.print("<input type=checkbox name=\"" + com.dragonflow.Properties.BrowsableProperty.BROWSE + "\" value=\"" + java.net.URLEncoder.encode(s6) + "object" + "\" " + s9 + ">" + "<input type=hidden name=\"SELECTED" + java.net.URLEncoder.encode(s6) + "object" + "ID\"" + " value=\"" + java.net.URLEncoder.encode(s6) + "\"> ");
                    if(flag)
                    {
                        printwriter.print("<input type=image name=\"" + CLOSE + java.net.URLEncoder.encode(s6) + "\" src=/SiteView/htdocs/artwork/Minus.gif alt=\"" + CLOSE + "\" border=0>");
                    } else
                    {
                        printwriter.print("<input type=image name=\"" + OPEN + java.net.URLEncoder.encode(s6) + "\" src=/SiteView/htdocs/artwork/Plus.gif alt=\"" + OPEN + "\" border=0>");
                    }
                    if(s3 != null && s3.length() > 0)
                    {
                        printwriter.print("&nbsp;<B>" + s1 + "</B>" + (s2 == null || s2.length() <= 0 ? "</TD></TR>" : "<img src=/SiteView/htdocs/artwork/info.gif alt=\"" + s2 + "\">"));
                    } else
                    {
                        printwriter.print("&nbsp;" + s1 + (s2 == null || s2.length() <= 0 ? "</TD></TR>" : "<img src=/SiteView/htdocs/artwork/info.gif alt=\"" + s2 + "\">"));
                    }
                    if(j <= 0 && flag)
                    {
                        i += 2;
                        java.lang.String s5 = getIndentHTML(i);
                        printwriter.print("<TR><TD>");
                        printwriter.print(s5);
                        printwriter.print("<input type=checkbox name=noop value=noop DISABLED>No Counters Currently Available</TD></TR>");
                    }
                }
            }
            if(flag)
            {
                for(int k = 0; k < j; k++)
                {
                    printNode(printwriter, nodelist.item(k), i + 2, hashmap, array, atomicmonitor, s);
                }

            }
        }
    }

    private boolean isIDSelected(com.dragonflow.SiteView.BrowsableMonitor browsablemonitor, java.lang.String s, jgl.HashMap hashmap)
    {
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements();)
        {
            java.lang.String s1 = (java.lang.String)enumeration.nextElement();
            java.lang.String s2 = java.net.URLDecoder.decode((java.lang.String)hashmap.get(s1));
            if(browsablemonitor.areBrowseIDsEqual(s, s2))
            {
                return true;
            }
        }

        return false;
    }

    java.lang.String getIndentHTML(int i)
    {
        int j = i * 11;
        if(j == 0)
        {
            j = 1;
        }
        return "<img src=/SiteView/htdocs/artwork/empty1111.gif height=11 width=" + j + " border=0>";
    }

    public static jgl.Array getNodeDisplayNames(org.w3c.dom.Node node)
    {
        jgl.Array array = new Array();
        java.lang.String s = ((org.w3c.dom.Element)node).getAttribute("name");
        if(s == null)
        {
            return array;
        }
        array.add(s);
        org.w3c.dom.Node node1 = node.getParentNode();
        do
        {
            if(node1 == null)
            {
                break;
            }
            java.lang.String s1 = ((org.w3c.dom.Element)node1).getAttribute("name");
            if(s1 == null || s1.length() <= 0)
            {
                break;
            }
            array.add(s1);
            node1 = node1.getParentNode();
        } while(true);
        return array;
    }

    public static jgl.Array getNodeIdNames(org.w3c.dom.Node node)
    {
        jgl.Array array = new Array();
        java.lang.String s = "id";
        java.lang.String s1 = ((org.w3c.dom.Element)node).getAttribute(s);
        if(s1 == null || s1.length() == 0)
        {
            s = "name";
            s1 = ((org.w3c.dom.Element)node).getAttribute(s);
        }
        if(s1 == null)
        {
            return array;
        }
        array.add(s1);
        org.w3c.dom.Node node1 = node.getParentNode();
        do
        {
            if(node1 == null)
            {
                break;
            }
            java.lang.String s2 = ((org.w3c.dom.Element)node1).getAttribute(s);
            if(s2 == null || s2.length() <= 0)
            {
                break;
            }
            array.add(s2);
            node1 = node1.getParentNode();
        } while(true);
        return array;
    }

    public static void main(java.lang.String args[])
    {
        com.dragonflow.Page.browsablePage browsablepage = new browsablePage();
        if(args.length > 0)
        {
            browsablepage.args = args;
        }
        browsablepage.handleRequest();
    }
}
