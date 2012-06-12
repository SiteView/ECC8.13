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
import java.io.FileOutputStream;
import java.util.Date;
import java.util.Hashtable;

import jgl.Array;
import jgl.HashMap;
import COM.dragonflow.Properties.HashMapOrdered;
import COM.dragonflow.SiteView.Platform;
import COM.dragonflow.Utils.SMTP;
import COM.dragonflow.Utils.TextUtils;

public class GSRPage extends COM.dragonflow.Page.CGI {
    
    java.lang.String replacestr[] = {
            "\r", "\n", "&CR;", "&LF;"
    };
    java.lang.String putbackstr[] = {
            "&CR;", "&LF;", "\r", "\n"
    };
    java.lang.String eraselinefeeds[] = {
            "&CR;", "&LF;", "", ""
    };
    java.lang.String xmlreplace[] = {
            "&", "<", ">", "'", "\"", "&amp;", "&lt;", "&gt;", "&apos;", "&quot"
    };
    java.lang.String xmlputback[] = {
            "&amp;", "&lt;", "&gt;", "&apos;", "&quot", "&", "<", ">", "'", "\""
    };
    java.lang.String groupnamereplace[] = {
            " ", "", "_", ""
    };
    public static java.lang.String OPEN_VARIABLE = "open";
    public static java.lang.String CLOSE_VARIABLE = "close";
    java.lang.String runbookscope[] = {
            "internal", "external", "both"
    };
    java.lang.String escalate_type[] = {
            "Phone", "Pager", "Email"
    };
    public int RUNBOOKGROUP_SELECT;
    public static boolean debug = false;
    
    public GSRPage() {
        RUNBOOKGROUP_SELECT = 8;
    }
    
    public void printBody() throws java.lang.Exception {
        if(!(new File(Platform.getRoot() + "/groups/GSRRunbook.config")).exists()) {
            jgl.Array array = new Array();
            jgl.HashMap hashmap = new HashMap();
            hashmap.put("_nextid", "0");
            hashmap.put("_account", "");
            hashmap.put("_emailto", "");
            java.lang.String s2 = "";
            try {
                java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
                s2 = inetaddress.getHostName();
            }
            catch(java.net.UnknownHostException unknownhostexception) {
                /* empty */
            }
            hashmap.put("_server", s2);
            array.add(hashmap);
            saveGSRRunbook(array);
        }
        java.lang.String s = request.getValue("action");
        java.lang.String s1 = request.getValue("operation");
        printBodyHeader("GSR Runbook Page");
        printButtonBar("gsrunbook.htm", "");
        if(s.equals("NEW RUNBOOK ENTRY")) {
            if(request.getValue("newform") != null && request.getValue("newform").equals("SUBMIT"))
            {
                printNewRunbook(outputStream, true);
                printselectedMonitorsGroups(outputStream);
                outputStream.println("</form>");
            } else
                if(s1.equals("choose"))
                {
                    java.lang.String s3 = "";
                    if(request.getValue("sequence").equals("start"))
                    {
                        s3 = request.getValue("runbook_select");
                    } else
                    {
                        s3 = request.getValue("id_selection");
                    }
                    printListForm(s, s3);
                } else
                    if(!s1.equals("verify"))
                    {
                        if(s1.equals("save"))
                        {
                            jgl.HashMap hashmap1 = new HashMap();
                            hashmap1.add("_name", request.getValue("runbook_name"));
                            hashmap1.add("_type", "runbook");
                            hashmap1.add("_scope", request.getValue("runbook_scope"));
                            hashmap1.add("_value", COM.dragonflow.Utils.TextUtils.replaceString(request.getValue("runbook_details"), replacestr));
                            saveRunbookEntry(hashmap1, "_runbookid");
                            createCustomEdit("_runbookid", "runbook", "Runbook Entry", "The Runbook Entry to assing to this monitor");
                            printMenu(outputStream);
                            outputStream.println("<br><br><font color=red size=+1>The following Entry was Added:</font><br><b>Name:</b>" + request.getValue("runbook_name") + "<br>" + "<b>Scope:</b>" + runbookscope[COM.dragonflow.Utils.TextUtils.toInt(request.getValue("runbook_scope")) - 1] + "<br>" + "<b>Runbook Entry Preview:</b><br><hr>" + request.getValue("runbook_details") + "<hr><br>");
                        } else
                        {
                            printMenu(outputStream);
                        }
                    }
        } else
            if(s.equals("EDIT RUNBOOK ENTRY"))
            {
                if(request.getValue("newform") != null && request.getValue("newform").equals("SUBMIT"))
                {
                    java.lang.String s4 = "";
                    java.lang.String s9 = "";
                    java.lang.String s13 = "";
                    java.lang.String s22 = "";
                    java.lang.String s27 = "";
                    if(request.getValue("id_selection") != null)
                    {
                        jgl.HashMap hashmap12 = loadGSRFramebyID(request.getValue("id_selection"));
                        if(hashmap12 != null)
                        {
                            if(hashmap12.get("_id") != null)
                            {
                                s4 = (java.lang.String)hashmap12.get("_id");
                            }
                            if(hashmap12.get("_name") != null)
                            {
                                s9 = (java.lang.String)hashmap12.get("_name");
                            }
                            if(hashmap12.get("_scope") != null)
                            {
                                s13 = (java.lang.String)hashmap12.get("_scope");
                            }
                            if(hashmap12.get("_value") != null)
                            {
                                s22 = (java.lang.String)hashmap12.get("_value");
                            }
                            if(hashmap12.get("_type") != null)
                            {
                                s27 = (java.lang.String)hashmap12.get("_type");
                            }
                            if(s27.equals("runbook"))
                            {
                                printRunbookForm(outputStream, true, s4, s9, s13, s22);
                                printselectedMonitorsGroups(outputStream);
                                outputStream.println("</form>");
                            } else
                                if(s27.equals("runbookgroup"))
                                {
                                    printRunbookGroupForm(s4, s9, "EDIT RUNBOOK GROUP", s13, s22);
                                    printselectedMonitorsGroups(outputStream);
                                    outputStream.println("</form>");
                                } else
                                {
                                    printMenu(outputStream);
                                }
                        }
                    } else
                    {
                        printMenu(outputStream);
                    }
                } else
                    if(s1.equals("choose"))
                    {
                        java.lang.String s5 = "";
                        if(request.getValue("sequence").equals("start"))
                        {
                            s5 = request.getValue("runbook_select");
                        } else
                        {
                            s5 = request.getValue("id_selection");
                        }
                        printListForm(s, s5);
                    } else
                        if(!s1.equals("verify"))
                        {
                            if(s1.equals("save"))
                            {
                                jgl.HashMap hashmap2 = new HashMap();
                                hashmap2.put("_id", request.getValue("id_selection"));
                                hashmap2.put("_name", request.getValue("runbook_name"));
                                hashmap2.put("_scope", request.getValue("runbook_scope"));
                                hashmap2.put("_type", "runbook");
                                hashmap2.put("_value", COM.dragonflow.Utils.TextUtils.replaceString(request.getValue("runbook_details"), replacestr));
                                clearRunbookids(request.getValue("id_selection"));
                                updateRunbookEntry(hashmap2, "_runbookid");
                                printMenu(outputStream);
                                outputStream.println("<br><br><font color=red size=+1>The following Entry was Updated to:</font><br><b>Name:</b>" + request.getValue("runbook_name") + "<br>" + "<b>Scope:</b>" + runbookscope[COM.dragonflow.Utils.TextUtils.toInt(request.getValue("runbook_scope")) - 1] + "<br>" + "<b>Runbook Entry Preview:</b><br><hr>" + request.getValue("runbook_details") + "<hr><br>");
                            } else
                            {
                                printMenu(outputStream);
                            }
                        }
            } else
                if(s.equals("CREATE ESCALATION GROUP"))
                {
                    if(request.getValue("newform").equals("SUBMIT"))
                    {
                        printEscalationGroupForm();
                        printselectedMonitorsGroups(outputStream);
                    } else
                        if(s1.equals("choose"))
                        {
                            printListForm(s, "");
                        } else
                            if(s1.equals("save"))
                            {
                                jgl.HashMap hashmap3 = new HashMap();
                                java.lang.String s10 = "";
                                int i;
                                for(i = 1; i < 3; i++)
                                {
                                    s10 = s10 + "" + request.getValue("elevel" + i) + ",";
                                }
                                
                                s10 = s10 + "" + request.getValue("elevel" + i);
                                hashmap3.put("_type", "escalationgroup");
                                hashmap3.put("_name", request.getValue("escalate_name"));
                                hashmap3.put("_value", s10);
                                saveRunbookEntry(hashmap3, "_escalationid");
                                createCustomEdit("_escalationid", "escalationgroup", "Escalation Entry", "The Esclation Group Entry to assign to this monitor");
                                printMenu(outputStream);
                                outputStream.println("<br><br><font color=red size=+1>The following Entry was Added:</font><br><b>Name:</b>" + request.getValue("runbook_name") + "<br>" + "<b>Escalation Entry Preview:</b><br><hr>" + s10 + "<hr><br>");
                            }
                } else
                    if(s.equals("CREATE RUNBOOK GROUP"))
                    {
                        jgl.HashMap hashmap4 = runbookToHashMap();
                        if(request.getValue("newform").equals("SUBMIT"))
                        {
                            printRunbookGroupForm();
                            printselectedMonitorsGroups(outputStream);
                        } else
                            if(s1.equals("choose"))
                            {
                                printListForm(s, "");
                            } else
                                if(s1.equals("save"))
                                {
                                    jgl.HashMap hashmap7 = new HashMap();
                                    java.lang.String s14 = "";
                                    int j;
                                    for(j = 1; j < RUNBOOKGROUP_SELECT; j++)
                                    {
                                        s14 = s14 + "" + request.getValue("runbook" + j) + ",";
                                    }
                                    
                                    s14 = s14 + "" + request.getValue("runbook" + j);
                                    java.lang.String s28 = "";
                                    if(!request.getValue("morerunbooks").equals(""))
                                    {
                                        if(request.getValue("morerunbooks").startsWith(","))
                                        {
                                            s28 = request.getValue("morerunbooks");
                                        } else
                                        {
                                            s28 = "," + request.getValue("morerunbooks");
                                        }
                                        java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s28, ",");
                                        s28 = "";
                                        for(int j1 = 1; j1 < as.length; j1++)
                                        {
                                            if(hashmap4.get(as[j1]) != null && ((java.lang.String)hashmap4.get(as[j1] + "_type")).equals("runbook"))
                                            {
                                                s28 = "," + as[j1];
                                            }
                                        }
                                        
                                    }
                                    hashmap7.put("_type", "runbookgroup");
                                    hashmap7.put("_scope", request.getValue("runbook_scope"));
                                    hashmap7.put("_name", request.getValue("runbook_name"));
                                    hashmap7.put("_value", s14 + s28);
                                    saveRunbookEntry(hashmap7, "_runbookid");
                                    createCustomEdit("_runbookid", "runbook", "Runbook Entry", "The Runbook Entry to assign to this monitor");
                                    printMenu(outputStream);
                                    outputStream.println("<br><br><font color=red size=+1>The following Entry was Added:</font><br><b>Name:</b>" + request.getValue("runbook_name") + "<br>" + "<b>Runbook Entry Preview:</b><br><hr>" + s14 + "," + s28 + "<hr><br>");
                                }
                    } else
                        if(s.equals("EDIT RUNBOOK GROUP"))
                        {
                            jgl.HashMap hashmap5 = new HashMap();
                            jgl.HashMap hashmap8 = runbookToHashMap();
                            java.lang.String s15 = "";
                            if(TextUtils.toInt(request.getValue("runbook_scope")) > 0)
                            {
                                s15 = runbookscope[TextUtils.toInt(request.getValue("runbook_scope")) - 1];
                            }
                            java.lang.String s23 = "";
                            int i1;
                            for(i1 = 1; i1 < RUNBOOKGROUP_SELECT; i1++)
                            {
                                s23 = s23 + "" + request.getValue("runbook" + i1) + ",";
                            }
                            
                            s23 = s23 + "" + request.getValue("runbook" + i1);
                            java.lang.String s30 = "";
                            if(!request.getValue("morerunbooks").equals(""))
                            {
                                if(request.getValue("morerunbooks").startsWith(","))
                                {
                                    s30 = request.getValue("morerunbooks");
                                } else
                                {
                                    s30 = "," + request.getValue("morerunbooks");
                                }
                                java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(s30, ",");
                                s30 = "";
                                for(int k1 = 0; k1 < as1.length; k1++)
                                {
                                    if(hashmap8.get(as1[k1]) != null && ((java.lang.String)hashmap8.get("" + as1[k1] + "_type")).equals("runbook"))
                                    {
                                        s30 = s30 + "," + as1[k1];
                                    }
                                }
                                
                            }
                            hashmap5.put("_id", request.getValue("id_selection"));
                            hashmap5.put("_type", "runbookgroup");
                            hashmap5.put("_name", request.getValue("runbook_name"));
                            hashmap5.put("_value", s23 + s30);
                            hashmap5.put("_scope", request.getValue("runbook_scope"));
                            clearRunbookids(request.getValue("id_selection"));
                            updateRunbookEntry(hashmap5, "_runbookid");
                            createCustomEdit("_runbookid", "runbook", "Runbook Entry", "The Runbook Entry to assign to this monitor");
                            printMenu(outputStream);
                            outputStream.println("<br><br><font color=red size=+1>The following Entry was Updated to:</font><br><b>Name:</b>" + request.getValue("runbook_name") + "<br>" + "<b>Runbook Group: " + s23 + s30);
                        } else
                            if(s.equals("EDIT ESCALATION GROUP"))
                            {
                                jgl.HashMap hashmap6 = new HashMap();
                                java.lang.String s11 = "";
                                if(COM.dragonflow.Utils.TextUtils.toInt(request.getValue("escalate_type")) > 0)
                                {
                                    s11 = escalate_type[COM.dragonflow.Utils.TextUtils.toInt(request.getValue("escalate_type")) - 1];
                                }
                                java.lang.String s16 = "";
                                int k;
                                for(k = 1; k < 3; k++)
                                {
                                    s16 = s16 + "" + request.getValue("elevel" + k) + ",";
                                }
                                
                                s16 = s16 + "" + request.getValue("elevel" + k);
                                hashmap6.put("_id", request.getValue("id_selection"));
                                hashmap6.put("_type", "escalationgroup");
                                hashmap6.put("_name", request.getValue("escalate_name"));
                                hashmap6.put("_value", s16);
                                clearRunbookids(request.getValue("id_selection"), "_escalationid");
                                updateRunbookEntry(hashmap6, "_escalationid");
                                createCustomEdit("_esclationid", "escalationgroup", "Escalation Entry", "The Esclation Group Entry to assign to this monitor");
                                printMenu(outputStream);
                                outputStream.println("<br><br><font color=red size=+1>The following Entry was Updated to:</font><br><b>Name:</b>" + request.getValue("escalate_name") + "<br>" + "<b>Escalation Group: " + s16);
                            } else
                                if(s.equals("EDIT ESCALATION"))
                                {
                                    if(s1.equals("choose") || request.getValue("newform") != null && request.getValue("newform").equals("SUBMIT"))
                                    {
                                        java.lang.String s6 = "";
                                        java.lang.String s12 = "";
                                        java.lang.String s17 = "";
                                        java.lang.String s24 = "";
                                        java.lang.String s29 = "";
                                        if(request.getValue("id_selection") != null && !request.getValue("id_selection").equals(""))
                                        {
                                            request.setValue("escalation_select", request.getValue("id_selection"));
                                        }
                                        if(request.getValue("escalation_select") != null)
                                        {
                                            jgl.HashMap hashmap13 = loadGSRFramebyID(request.getValue("escalation_select"));
                                            if(hashmap13 != null)
                                            {
                                                if(hashmap13.get("_id") != null)
                                                {
                                                    s6 = (java.lang.String)hashmap13.get("_id");
                                                }
                                                if(hashmap13.get("_name") != null)
                                                {
                                                    s12 = (java.lang.String)hashmap13.get("_name");
                                                }
                                                if(hashmap13.get("_subtype") != null)
                                                {
                                                    s17 = (java.lang.String)hashmap13.get("_subtype");
                                                }
                                                if(hashmap13.get("_value") != null)
                                                {
                                                    s24 = (java.lang.String)hashmap13.get("_value");
                                                }
                                                if(hashmap13.get("_type") != null)
                                                {
                                                    s29 = (java.lang.String)hashmap13.get("_type");
                                                }
                                                java.lang.String s32 = "";
                                                if(COM.dragonflow.Utils.TextUtils.toInt(s17) > 0)
                                                {
                                                    s32 = escalate_type[COM.dragonflow.Utils.TextUtils.toInt(s17) - 1];
                                                }
                                                if(s29.equals("escalation"))
                                                {
                                                    editEscalationForm(outputStream, true, s6, s32, s12, s17, s24, "EDIT ESCALATION");
                                                    outputStream.println("</form>");
                                                } else
                                                    if(s29.equals("escalationgroup"))
                                                    {
                                                        if(request.getValue("newform").equals("SUBMIT"))
                                                        {
                                                            printEscalationGroupForm(s6, s12, "EDIT ESCALATION GROUP", s24);
                                                            printselectedMonitorsGroups(outputStream);
                                                            outputStream.println("</form>");
                                                        } else
                                                        {
                                                            printListForm("EDIT ESCALATION", s6);
                                                        }
                                                    } else
                                                    {
                                                        printMenu(outputStream);
                                                    }
                                            }
                                        }
                                    } else
                                        if(s1.equals("save"))
                                        {
                                            jgl.Array array1 = loadGSRRunbook();
                                            jgl.HashMap hashmap9 = new HashMap();
                                            java.lang.String s18 = "";
                                            if(COM.dragonflow.Utils.TextUtils.toInt(request.getValue("escalate_type")) > 0)
                                            {
                                                s18 = escalate_type[COM.dragonflow.Utils.TextUtils.toInt(request.getValue("escalate_type")) - 1];
                                            }
                                            int l = 1;
                                            do
                                            {
                                                if(l >= array1.size())
                                                {
                                                    break;
                                                }
                                                jgl.HashMap hashmap10 = (jgl.HashMap)array1.at(l);
                                                if(((java.lang.String)hashmap10.get("_id")).equals(request.getValue("id_selection")))
                                                {
                                                    hashmap10.put("_name", request.getValue("escalate_name"));
                                                    hashmap10.put("_subtype", request.getValue("escalate_type"));
                                                    hashmap10.put("_value", request.getValue("escalate_details"));
                                                    array1.put(l, hashmap10);
                                                    break;
                                                }
                                                l++;
                                            } while(true);
                                            saveGSRRunbook(array1);
                                            printMenu(outputStream);
                                            outputStream.println("<br><br><font color=red size=+1>The following Entry was Updated to:</font><br><b>Name:</b>" + request.getValue("escalate_name") + "<br>" + "<b>Scope:</b>" + s18 + "<br>" + "<b>Escalation Entry: " + request.getValue("escalate_details"));
                                        }
                                } else
                                    if(s.equals("CREATE STATIC RUNBOOK"))
                                    {
                                        if(request.getValue("newform") != null && request.getValue("newform").equals("SUBMIT"))
                                        {
                                            printXSLchoosepage();
                                        } else
                                            if(s1.equals("choose"))
                                            {
                                                printListForm(s, "");
                                            } else
                                            {
                                                java.lang.String s7 = "";
                                                java.util.Enumeration enumeration = request.getValues("xsltemplates");
                                                java.lang.String s19 = "";
                                                if(enumeration.hasMoreElements())
                                                {
                                                    s19 = (java.lang.String)enumeration.nextElement();
                                                }
                                                s7 = createXML();
                                                if(s19.equals(""))
                                                {
                                                    printXSLchoosepage();
                                                    outputStream.println("<h2>XML Debug output.</h2>");
                                                    outputStream.println("<pre>");
                                                    outputStream.println(COM.dragonflow.Utils.TextUtils.escapeHTML(s7));
                                                    outputStream.println("</pre>");
                                                } else
                                                {
                                                    java.lang.String s25 = s19.substring(0, s19.indexOf(".xsl")) + ".html";
                                                    outputStream.println("<b>Processed XSL file:</b>" + s19 + "--><a href=/SiteView/htdocs/" + s25 + " target=runbook>" + s25 + "</a><br>");
                                                    applyXSLsheets(s19);
                                                    java.lang.String s20;
                                                    for(; enumeration.hasMoreElements(); applyXSLsheets(s20))
                                                    {
                                                        s20 = (java.lang.String)enumeration.nextElement();
                                                        java.lang.String s26 = s20.substring(0, s20.indexOf(".xsl")) + ".html";
                                                        outputStream.println("<b>Processed XSL file:</b>" + s20 + "--><a href=/SiteView/htdocs/" + s26 + " target=runbook>" + s26 + "</a><br>");
                                                    }
                                                    
                                                    outputStream.println("<br><br>");
                                                    printMenu(outputStream);
                                                }
                                            }
                                    } else
                                        if(s.equals("EXPORT RUNBOOK"))
                                        {
                                            if(request.getValue("newform") != null && request.getValue("newform").equals("SUBMIT"))
                                            {
                                                printExportForm();
                                            } else
                                                if(s1.equals("choose"))
                                                {
                                                    printListForm(s, "");
                                                } else
                                                {
                                                    java.lang.String s8 = "";
                                                    java.util.Enumeration enumeration1 = request.getValues("scope");
                                                    java.lang.String s21 = request.getValue("mailto");
                                                    if(s21 == null || s21.equals("null"))
                                                    {
                                                        s21 = "";
                                                    }
                                                    jgl.Array array2 = loadGSRRunbook();
                                                    jgl.HashMap hashmap11 = (jgl.HashMap)array2.at(0);
                                                    java.lang.String s31 = "";
                                                    java.lang.String s33 = "";
                                                    java.lang.String s34 = "";
                                                    if(s21.equals("") && hashmap11.get("_emailto") != null)
                                                    {
                                                        s21 = (java.lang.String)hashmap11.get("_emailto");
                                                    }
                                                    if(hashmap11.get("_account") != null)
                                                    {
                                                        s34 = (java.lang.String)hashmap11.get("_account");
                                                    }
                                                    jgl.HashMap hashmap14 = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
                                                    if(hashmap14.get("_mailServer") != null)
                                                    {
                                                        s33 = (java.lang.String)hashmap14.get("_mailServer");
                                                    }
                                                    if(hashmap14.get("_autoemail") != null)
                                                    {
                                                        s31 = (java.lang.String)hashmap14.get("_autoemail");
                                                    }
                                                    s8 = createXML();
                                                    jgl.Array array3 = new Array();
                                                    try
                                                    {
                                                        COM.dragonflow.Utils.SMTP smtp = new SMTP(s33, 60000, array3);
                                                        smtp.send(s31, s21, "", "GSR RUNBOOK UPDATE: ACCOUNT=" + s34, s8, null);
                                                        smtp.close();
                                                    }
                                                    catch(java.lang.Exception exception)
                                                    {
                                                        outputStream.println(exception + "\n");
                                                    }
                                                    java.util.Enumeration enumeration2 = array3.elements();
                                                    outputStream.println("<h2>MAIL SENT TO " + s21 + "</H2><BR><B>DETAILS:</B><BR><PRE>");
                                                    for(; enumeration2.hasMoreElements(); outputStream.println(COM.dragonflow.Utils.TextUtils.escapeHTML(COM.dragonflow.Utils.TextUtils.replaceString((java.lang.String)enumeration2.nextElement(), "<CRLF>", "<CRLF>\n")))) { }
                                                    outputStream.println("</pre>");
                                                }
                                        } else
                                            if(s.equals("NEW ESCALATION"))
                                            {
                                                if(s1.equals("choose"))
                                                {
                                                    printEscalationForm();
                                                } else
                                                    if(s1.equals("save"))
                                                    {
                                                        saveEscalation();
                                                        outputStream.println("<h2>Saved Escalation</h2><br>");
                                                        printMenu(outputStream);
                                                    }
                                            } else
                                                if(s.equals("DELETE RUNBOOK ENTRY"))
                                                {
                                                    if(request.getValue("runbook_select") != null)
                                                    {
                                                        clearRunbookids(request.getValue("runbook_select"));
                                                        deleteRunbookID(request.getValue("runbook_select"));
                                                        outputStream.println("<h2>Deleted Runbook Entry</h2><br>");
                                                    } else
                                                    {
                                                        outputStream.println("<h2>Delete failed. Please choose an item to delete.</h2><br>");
                                                    }
                                                    printMenu(outputStream);
                                                } else
                                                    if(s.equals("DELETE ESCALATION"))
                                                    {
                                                        if(request.getValue("escalation_select") != null)
                                                        {
                                                            deleteRunbookID(request.getValue("escalation_select"));
                                                            outputStream.println("<h2>Deleted Escalation Entry</h2><br>");
                                                        } else
                                                        {
                                                            outputStream.println("<h2>Delete failed. Please choose an item to delete.</h2><br>");
                                                        }
                                                        printMenu(outputStream);
                                                    } else
                                                    {
                                                        printMenu(outputStream);
                                                    }
        printFooter(outputStream);
    }
    
    public void printMenu(java.io.PrintWriter printwriter)
    {
        java.lang.String as[] = selectboxes_create();
        java.lang.String s = as[0];
        java.lang.String s1 = as[1];
        printwriter.println("<FORM METHOD=GET ACTION=\"/SiteView/cgi/go.exe/SiteView\"><input type=hidden name=page value=GSR><input type=hidden name=operation value=choose><input type=hidden name=sequence value=start><input type=hidden name=account value=" + request.getAccount() + ">" + "<br><br><br><center><TABLE BORDER=0><TR><TH BGCOLOR=ccffff>RUNBOOK ENTRIES</TH><TH BGCOLOR=ccffff>ESCALATION ENTRIES</TH></TR>" + "<TR><TD bgcolor=000000><center>" + s + "<br><input type=SUBMIT name=action value=\"NEW RUNBOOK ENTRY\"><BR>" + "<INPUT TYPE=SUBMIT name=action value = \"EDIT RUNBOOK ENTRY\"><br>" + "<input type=SUBMIT name=action value=\"DELETE RUNBOOK ENTRY\"><BR>" + "<input type=SUBMIT name=action value=\"CREATE RUNBOOK GROUP\"><br>" + "</center></TD><TD BGCOLOR=000000><center>" + s1 + "<br><input type=SUBMIT SIZE=40 name=action value=\"NEW ESCALATION\"><BR>" + "<INPUT TYPE=SUBMIT  name=action value = \"EDIT ESCALATION\"><br>" + "<input type=SUBMIT name=action value=\"DELETE ESCALATION\"><BR>" + "<input type=SUBMIT name=action value=\"CREATE ESCALATION GROUP\"><BR>" + "</center></TD></TR><TR><TD COLSPAN=2 bgcolor=ccffff>" + "<center>" + "<INPUT TYPE=SUBMIT  NAME=action value=\"CREATE STATIC RUNBOOK\"><br>" + "<INPUT TYPE=SUBMIT  NAME=action value=\"EXPORT RUNBOOK\"><br>" + "</td></tr></TABLE></center></FORM><BR><BR><BR><BR>");
    }
    
    public java.lang.String[] selectboxes_create()
    {
        java.lang.String as[] = null;
        as = selectboxes_create(true);
        return as;
    }
    
    public java.lang.String[] selectboxes_create(boolean flag)
    {
        java.lang.String as[] = {
                null, null
        };
        java.lang.String s = "<select name=runbook_select size=10><option value=></option>";
        java.lang.String s1 = "<select name=escalation_select size=10><option value=></option>";
        jgl.Array array = loadGSRRunbook();
        if(array != null)
        {
            for(int i = 1; i < array.size(); i++)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                if(hashmap.get("_type") == null)
                {
                    continue;
                }
                if(((java.lang.String)hashmap.get("_type")).equals("runbook") || ((java.lang.String)hashmap.get("_type")).equals("runbookgroup") && flag)
                {
                    java.lang.String s2 = (java.lang.String)hashmap.get("_id");
                    java.lang.String s4 = (java.lang.String)hashmap.get("_name");
                    s = s + "<option value=" + s2 + ">[" + s2 + "] " + s4 + "</option>";
                    continue;
                }
                if(((java.lang.String)hashmap.get("_type")).equals("escalation") || ((java.lang.String)hashmap.get("_type")).equals("escalationgroup") && flag)
                {
                    java.lang.String s3 = (java.lang.String)hashmap.get("_id");
                    java.lang.String s5 = (java.lang.String)hashmap.get("_name");
                    s1 = s1 + "<option value=" + s3 + ">[" + s3 + "] " + s5 + "</option>";
                }
            }
            
            as[0] = s + "</select>";
            as[1] = s1 + "</select>";
            return as;
        } else
        {
            s = s + "</select>";
            s1 = s1 + "</select>";
            as[0] = s;
            as[1] = s1;
            return as;
        }
    }
    
    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public jgl.Array loadGSRRunbook()
    {
        jgl.Array array = null;
        try {
            array = COM.dragonflow.Properties.FrameFile.readFromFile(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/GSRRunbook.config");
            if(array != null && array.size() > 0)
            {
                return array;
            }
            return null;
        }
        catch (java.io.IOException ioexception) {
            ioexception.printStackTrace();
            return array;
        }
    }
    
    public void printNewRunbook(java.io.PrintWriter printwriter, boolean flag)
    {
        printwriter.println("<br><br><h2>New Runbook Entry</h2><br><form method=post action=/SiteView/cgi/go.exe/SiteView ><br>Name<input type=text name=runbook_name size=40><br>Scope:<select name=runbook_scope ><option value=1>Internal</option><option value=2>External</option><option value=3>Both</option></select><br>Runbook Entry<br><textarea name=runbook_details rows=20 cols=80></textarea><br><input type=hidden name=page value=GSR><input type=hidden name=operation value=save><input type=hidden name=action value=\"NEW RUNBOOK ENTRY\"><input type=submit value=SUBMIT>");
    }
    
    public void printRunbookForm(java.io.PrintWriter printwriter, boolean flag, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        java.lang.String s4 = "";
        if(COM.dragonflow.Utils.TextUtils.toInt(s2) - 1 > 0)
        {
            s4 = runbookscope[COM.dragonflow.Utils.TextUtils.toInt(s2) - 1];
        }
        printwriter.println("<br><br><h2>New Runbook Entry</h2><br><form method=post action=/SiteView/cgi/go.exe/SiteView ><input type=hidden name=id_selection value=" + s + ">" + "<br>Name<input type=text name=runbook_name size=40 value=\"" + s1 + "\"><br>" + "Scope:<select name=runbook_scope ><option value=" + s2 + ">" + s4 + "</option>" + "<option value=1>Internal</option><option value=2>External</option><option value=3>Both</option></select>" + "<br>Runbook Entry<br><textarea name=runbook_details rows=20 cols=80>" + COM.dragonflow.Utils.TextUtils.replaceString(s3, putbackstr) + "</textarea><br>" + "<input type=hidden name=page value=GSR><input type=hidden name=operation value=save>" + "<input type=hidden name=action value=\"EDIT RUNBOOK ENTRY\">" + "<input type=submit value=SUBMIT>");
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
    
    private java.lang.String printGroup(COM.dragonflow.SiteView.MonitorGroup monitorgroup, jgl.HashMap hashmap, jgl.HashMap hashmap1, int i, boolean flag, java.lang.String s)
    {
        java.lang.String s1 = monitorgroup.getProperty(COM.dragonflow.SiteView.Monitor.pID);
        java.lang.String s2 = monitorgroup.getProperty(COM.dragonflow.SiteView.MonitorGroup.pParent);
        boolean flag1 = flag;
        boolean flag2 = hashmap.get(s1) != null;
        java.lang.String s3 = getIndentHTML(i);
        java.lang.String s4 = COM.dragonflow.SiteView.Platform.getURLPath("htdocs", request.getAccount()) + "/Detail";
        if(!flag1)
        {
            outputStream.print("<TR><TD>");
            outputStream.print(s3);
            if(flag2)
            {
                outputStream.print("<input type=image name=close" + s1 + " src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\" border=0>");
            } else
            {
                flag1 = true;
                outputStream.print("<input type=image name=open" + s1 + " src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\" border=0>");
            }
            outputStream.print("<input type=checkbox name=group value=\"" + s1 + "\" " + COM.dragonflow.Utils.TextUtils.getValue(hashmap1, s1) + "><B>");
            outputStream.print("<A HREF=" + s4 + COM.dragonflow.HTTP.HTTPRequest.encodeString(monitorgroup.getProperty(COM.dragonflow.SiteView.Monitor.pID)) + ".html>" + monitorgroup.getProperty(COM.dragonflow.SiteView.Monitor.pName));
            outputStream.println("</A></B></TD></TR>");
        } else
            if(flag1 && hashmap1.get(s1) != null && ((java.lang.String)hashmap1.get(s1)).equals("checked"))
            {
                outputStream.print("<input type=hidden name=group  value=\"" + s1 + "\">");
                s = s + "Group:" + s1 + "\n";
            }
        s3 = getIndentHTML(i + 3);
        java.util.Enumeration enumeration = monitorgroup.getMonitors();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor)enumeration.nextElement();
            if(monitor instanceof COM.dragonflow.SiteView.SubGroup)
            {
                java.lang.String s5 = monitor.getProperty(COM.dragonflow.SiteView.SubGroup.pGroup);
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                COM.dragonflow.SiteView.MonitorGroup monitorgroup1 = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s5);
                if(monitorgroup1 != null)
                {
                    s = printGroup(monitorgroup1, hashmap, hashmap1, i + 2, flag1, s);
                }
            } else
            {
                java.lang.String s6 = s1 + " " + monitor.getProperty(COM.dragonflow.SiteView.Monitor.pID);
                if(!flag1 && flag2)
                {
                    outputStream.print("<TR><TD>");
                    outputStream.print(s3);
                    outputStream.print("<input type=checkbox name=monitor value=\"" + s6 + "\" " + COM.dragonflow.Utils.TextUtils.getValue(hashmap1, s6) + ">");
                    outputStream.print(monitor.getProperty(COM.dragonflow.SiteView.Monitor.pName));
                } else
                    if(hashmap1.get(s6) != null && ((java.lang.String)hashmap1.get(s6)).equals("checked"))
                    {
                        outputStream.print("<input type=hidden name=monitor value=\"" + s6 + "\">");
                        s = s + "" + s1 + ":" + monitor.getProperty(COM.dragonflow.SiteView.Monitor.pName) + "\n";
                    }
                if(monitor.getProperty(COM.dragonflow.SiteView.Monitor.pDisabled).length() > 0 && flag2)
                {
                    outputStream.println(" <B>(disabled)</B>");
                }
                if(flag2)
                {
                    outputStream.println("</TD></TR>");
                }
            }
        } while(true);
        return s;
    }
    
    public void printListForm(java.lang.String s, java.lang.String s1)
    throws java.lang.Exception
    {
        java.lang.String s2 = "";
        java.lang.String s3 = null;
        java.lang.String s4 = null;
        java.lang.String s5 = request.getValue("sequence");
        java.lang.String s6 = request.getValue("runbook_select");
        java.lang.String s7 = request.getValue("escalation_select");
        if(s6 != null && !s6.equals(""))
        {
            s3 = s6;
            s4 = "_runbookid";
        } else
        {
            s3 = s7;
            s4 = "_escalationid";
        }
        java.lang.String s8 = COM.dragonflow.SiteView.Platform.getDirectoryPath("groups", request.getAccount());
        java.lang.String s9 = s8 + java.io.File.separator + "tree.dyn";
        jgl.Array array = null;
        try
        {
            array = COM.dragonflow.Properties.FrameFile.readFromFile(s9);
        }
        catch(java.lang.Exception exception)
        {
            array = new Array();
        }
        jgl.HashMap hashmap = null;
        java.lang.String s10 = request.getAccount();
        boolean flag = false;
        for(int i = 0; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            if(COM.dragonflow.Utils.TextUtils.getValue(hashmap1, "_user").equals(s10))
            {
                hashmap = hashmap1;
            }
        }
        
        if(hashmap == null)
        {
            hashmap = new HashMap();
            array.add(hashmap);
            hashmap.put("_user", s10);
        }
        java.util.Enumeration enumeration = request.getVariables();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            java.lang.String s11 = (java.lang.String)enumeration.nextElement();
            if(s11.startsWith(OPEN_VARIABLE))
            {
                java.lang.String s12 = s11.substring(OPEN_VARIABLE.length(), s11.length() - 2);
                if(debug)
                {
                    COM.dragonflow.Utils.TextUtils.debugPrint("OPEN " + s12);
                }
                if(!COM.dragonflow.Utils.TextUtils.getValue(hashmap, s12).equals("open"))
                {
                    hashmap.put(s12, "open");
                    flag = true;
                }
            }
            if(s11.startsWith(CLOSE_VARIABLE))
            {
                java.lang.String s13 = s11.substring(CLOSE_VARIABLE.length(), s11.length() - 2);
                if(debug)
                {
                    COM.dragonflow.Utils.TextUtils.debugPrint("CLOSE " + s13);
                }
                if(!COM.dragonflow.Utils.TextUtils.getValue(hashmap, s13).equals("close"))
                {
                    hashmap.remove(s13);
                    flag = true;
                }
            }
        } while(true);
        jgl.HashMap hashmap2 = new HashMap();
        java.util.Enumeration enumeration1 = request.getValues("monitor");
        if(s5.equals("start") && s4 != null && s3 != null && !s3.equals(""))
        {
            jgl.Array array1 = null;
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            array1 = siteviewgroup.getGroupFileIDs();
            for(int j = 0; j < array1.size(); j++)
            {
                hashmap2 = findItemsWithID(hashmap2, (java.lang.String)array1.at(j), s4, s3);
            }
            
        } else
        {
            for(; enumeration1.hasMoreElements(); hashmap2.put(enumeration1.nextElement(), "checked")) { }
            for(java.util.Enumeration enumeration2 = request.getValues("group"); enumeration2.hasMoreElements(); hashmap2.put(enumeration2.nextElement(), "checked")) { }
        }
        COM.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        jgl.Array array2 = getGroupNameList(hashmapordered, null, null, true);
        outputStream.println("<H2>GSR Runbook and Escalation Configuration</H2><P>Select one or more groups and monitors and then choose the action you wish to perform.<p><FORM METHOD=POST ACTION=/SiteView/cgi/go.exe/SiteView><INPUT TYPE=HIDDEN NAME=operation value=choose><INPUT TYPE=HIDDEN NAME=id_selection value=" + s1 + ">" + "<INPUT TYPE=HIDDEN NAME=action value=\"" + s + "\">" + "<INPUT TYPE=HIDDEN NAME=page VALUE=GSR>" + "<INPUT TYPE=HIDDEN NAME=account VALUE=" + s10 + ">");
        outputStream.println("<HR>(Click the <img src=/SiteView/htdocs/artwork/Plus.gif alt=\"open\"> to expand a group, and the <img src=/SiteView/htdocs/artwork/Minus.gif alt=\"close\"> to collapse a group).<P><TABLE BORDER=0>");
        for(java.util.Enumeration enumeration4 = array2.elements(); enumeration4.hasMoreElements();)
        {
            java.lang.String s14 = (java.lang.String)enumeration4.nextElement();
            java.util.Enumeration enumeration3 = hashmapordered.values(s14);
            while(enumeration3.hasMoreElements()) 
            {
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)enumeration3.nextElement();
                s2 = printGroup(monitorgroup, hashmap, hashmap2, 0, false, s2);
            }
        }
        
        outputStream.println("</TABLE>");
        outputStream.println("<br><input type=submit name=newform value=SUBMIT><br>");
        outputStream.println("<BR><FONT COLOR=RED>HIDDEN SELECTED MONITORS AND GROUPS</FONT><BR><textarea rows=10 cols=80 name=hiddens>" + s2 + "</textarea><br>");
        outputStream.println("</FORM>");
        if(flag)
        {
            if(debug)
            {
                COM.dragonflow.Utils.TextUtils.debugPrint("SAVING TREE STATE");
            }
            COM.dragonflow.Properties.FrameFile.writeToFile(s9, array);
        }
    }
    
    public jgl.Array loadgroup(java.lang.String s)
    {
        java.lang.String s1 = "";
        if(s != null && !s.equals("null"))
        {
            s1 = COM.dragonflow.Utils.TextUtils.replaceString(s, groupnamereplace);
        }
        if(!s1.equals("") && (new File(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/" + s1 + ".mg")).exists())
        {
            jgl.Array array = null;
            try
            {
                array = COM.dragonflow.Properties.FrameFile.readFromFile(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/" + s1 + ".mg");
            }
            catch(java.io.IOException ioexception)
            {
                ioexception.printStackTrace();
                return null;
            }
            return array;
        } else
        {
            return null;
        }
    }
    
    public boolean savegroup(java.lang.String s, jgl.Array array)
    {
        try
        {
            COM.dragonflow.Properties.FrameFile.writeToFile(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/" + s + ".mg", array, "", true, true);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
            return false;
        }
        return true;
    }
    
    public void updateRunbookidValue(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        jgl.Array array = null;
        array = loadgroup(s);
        if(array != null)
        {
            for(int i = 0; i < array.size(); i++)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                java.lang.String s4 = (java.lang.String)hashmap.get("_class");
                if((s4 == null || !s4.equals("SubGroup")) && hashmap.get(s1) != null && ((java.lang.String)hashmap.get(s1)).equals(s3))
                {
                    hashmap.put(s1, s2);
                    array.put(i, hashmap);
                } else
                {
                    updategroup_recursive((java.lang.String)hashmap.get("_group"), s1, s2);
                }
            }
            
            savegroup(s, array);
        }
    }
    
    public void updategroup(java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        jgl.Array array = null;
        array = loadgroup(s);
        if(array != null)
        {
            for(int i = 0; i < array.size(); i++)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                java.lang.String s3 = (java.lang.String)hashmap.get("_class");
                if(s3 == null || !s3.equals("SubGroup"))
                {
                    hashmap.put(s1, s2);
                    array.put(i, hashmap);
                }
            }
            
            savegroup(s, array);
        }
    }
    
    public void updategroup_recursive(java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        jgl.Array array = null;
        array = loadgroup(s);
        if(array != null)
        {
            for(int i = 0; i < array.size(); i++)
            {
                jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
                java.lang.String s3 = (java.lang.String)hashmap.get("_class");
                if(s3 == null || !s3.equals("SubGroup"))
                {
                    hashmap.put(s1, s2);
                    array.put(i, hashmap);
                } else
                {
                    updategroup_recursive((java.lang.String)hashmap.get("_group"), s1, s2);
                }
            }
            
            savegroup(s, array);
        }
    }
    
    public jgl.HashMap findItemsWithID(jgl.HashMap hashmap, java.lang.String s, java.lang.String s1, java.lang.String s2)
    {
        jgl.Array array = null;
        jgl.HashMap hashmap1 = new HashMap();
        array = loadgroup(s);
        if(array != null)
        {
            for(int i = 0; i < array.size(); i++)
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)array.at(i);
                if(hashmap2.get(s1) != null && hashmap2.get("_class") != null && ((java.lang.String)hashmap2.get(s1)).equals(s2) && !((java.lang.String)hashmap2.get("_class")).equals("SubGroup"))
                {
                    java.lang.String s3 = (java.lang.String)hashmap2.get("_id");
                    if(s3 == null)
                    {
                        s3 = "";
                    }
                    hashmap.put("" + s + " " + s3, "checked");
                    continue;
                }
                if(hashmap2.get("_class") != null && ((java.lang.String)hashmap2.get("_class")).equals("SubGroup"))
                {
                    hashmap = findItemsWithID(hashmap, (java.lang.String)hashmap2.get("_group"), s1, s2);
                    continue;
                }
                if(i == 0 && hashmap2.get(s1) != null && ((java.lang.String)hashmap2.get(s1)).equals(s2))
                {
                    hashmap.put("" + s, "checked");
                }
            }
            
        }
        return hashmap;
    }
    
    public void printselectedMonitorsGroups(java.io.PrintWriter printwriter)
    {
        java.lang.String s = request.getValue("toGroupID");
        jgl.Array array = new Array();
        jgl.Array array1 = new Array();
        java.lang.String s1 = "";
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array2 = new Array();
        jgl.Array array3 = new Array();
        if(s.length() > 0)
        {
            array3.add(s);
        }
        java.util.Enumeration enumeration = request.getValues("monitor");
        int i = 1;
        java.lang.String s2 = new String("");
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            java.lang.String s4 = (java.lang.String)enumeration.nextElement();
            int k = s4.indexOf(' ');
            java.lang.String s5 = "";
            java.lang.String s9 = "";
            if(k >= 0)
            {
                java.lang.String s6 = s4.substring(0, k);
                java.lang.String s10 = s4.substring(k + 1);
                if(array3.size() == 0)
                {
                    array3.add(s6);
                }
                COM.dragonflow.SiteView.Monitor monitor = (COM.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s4.replace(' ', '/'));
                java.lang.String s3 = monitor.getFullID();
                if(monitor != null)
                {
                    java.lang.String s12 = COM.dragonflow.Page.GSRPage.getGroupFullName(s6) + ":" + monitor.getProperty(COM.dragonflow.SiteView.Monitor.pName) + "";
                    array1.add(s12);
                    s1 = s1 + "\n<INPUT TYPE=HIDDEN NAME=monitor" + i + " VALUE=\"" + s4 + "\">";
                    i++;
                }
            }
        } while(true);
        enumeration = request.getValues("group");
        int j = 1;
        java.util.Hashtable hashtable = new Hashtable();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            java.lang.String s7 = (java.lang.String)enumeration.nextElement();
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement(s7);
            if(monitorgroup != null)
            {
                java.lang.String s11 = monitorgroup.getProperty("_parent");
                boolean flag1 = false;
                do
                {
                    if(s11.length() <= 0)
                    {
                        break;
                    }
                    COM.dragonflow.SiteView.Monitor monitor1 = (COM.dragonflow.SiteView.Monitor)siteviewgroup.getElement(s11);
                    if(monitor1 == null)
                    {
                        break;
                    }
                    if(hashtable.containsKey(s11))
                    {
                        flag1 = true;
                        break;
                    }
                    s11 = monitor1.getProperty("_parent");
                } while(true);
                if(!flag1)
                {
                    hashtable.put(s7, enumeration);
                    if(array3.size() == 0)
                    {
                        array3.add(s7);
                    }
                    java.lang.String s13 = COM.dragonflow.Page.GSRPage.getGroupFullName(s7);
                    array.add(s13);
                    s1 = s1 + "\n<INPUT TYPE=HIDDEN NAME=group" + j + " VALUE=\"" + s7 + "\">";
                    j++;
                    excludeAllSubGroups(monitorgroup, array2);
                }
            }
        } while(true);
        java.lang.String s8 = "Item";
        boolean flag = true;
        if(array.size() == 0)
        {
            s8 = "Monitor";
            flag = false;
        } else
            if(array1.size() == 0)
            {
                s8 = "Group";
                flag = false;
            }
        if(array.size() + array1.size() > 1)
        {
            s8 = s8 + "s";
        }
        printwriter.println("<br><br><FONT COLOR=RED>SELECTED MONITORS AND GROUPS FOR THIS OPERATION</FONT><br><textarea rows=10 cols=80>");
        for(int l = 0; l < array.size(); l++)
        {
            if(flag)
            {
                printwriter.print("Group ");
            }
            printwriter.print(array.at(l) + "\n");
        }
        
        for(int i1 = 0; i1 < array1.size(); i1++)
        {
            if(flag)
            {
                printwriter.print("Monitor ");
            }
            printwriter.print(array1.at(i1) + "\n");
        }
        
        printwriter.println("</TEXTAREA><br>" + s1);
    }
    
    void excludeAllSubGroups(COM.dragonflow.SiteView.Monitor monitor, jgl.Array array)
    {
        array.add(monitor.getProperty(COM.dragonflow.SiteView.Monitor.pID));
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        java.util.Enumeration enumeration = monitor.getMonitors();
        do
        {
            if(!enumeration.hasMoreElements())
            {
                break;
            }
            COM.dragonflow.SiteView.Monitor monitor1 = (COM.dragonflow.SiteView.Monitor)enumeration.nextElement();
            if(monitor1 instanceof COM.dragonflow.SiteView.SubGroup)
            {
                COM.dragonflow.SiteView.Monitor monitor2 = (COM.dragonflow.SiteView.Monitor)siteviewgroup.getElement(monitor1.getProperty(COM.dragonflow.SiteView.SubGroup.pGroup));
                if(monitor2 != null)
                {
                    excludeAllSubGroups(monitor2, array);
                }
            }
        } while(true);
    }
    
    public jgl.Array getMonitorGroupLists()
    {
        jgl.Array array = new Array();
        jgl.Array array1 = new Array();
        jgl.Array array2 = new Array();
        int i = 1;
        do
        {
            java.lang.String s = request.getValue("group" + i);
            if(s.length() <= 0)
            {
                break;
            }
            array1.add(s);
            array2.add(request.getValue("groupName" + i));
            i++;
        } while(true);
        jgl.Array array3 = new Array();
        jgl.Array array4 = new Array();
        i = 1;
        do
        {
            java.lang.String s1 = request.getValue("monitor" + i);
            if(s1.length() > 0)
            {
                array3.add(s1);
                array4.add(request.getValue("monitorName" + i));
                i++;
            } else
            {
                array.add(array1);
                array.add(array2);
                array.add(array3);
                array.add(array4);
                return array;
            }
        } while(true);
    }
    
    public void saveRunbookEntry(jgl.HashMap hashmap, java.lang.String s)
    {
        saveRunbookEntry(hashmap, s, false);
    }
    
    public void saveRunbookEntry(jgl.HashMap hashmap, java.lang.String s, boolean flag)
    {
        jgl.Array array = getMonitorGroupLists();
        jgl.Array array1 = (jgl.Array)array.at(0);
        jgl.Array array2 = (jgl.Array)array.at(2);
        jgl.Array array3 = null;
        jgl.HashMap hashmap1 = new HashMap();
        boolean flag1 = false;
        int j = 0;
        array3 = loadGSRRunbook();
        if(flag)
        {
            jgl.HashMap hashmap2 = new HashMap();
            int k = 1;
            do
            {
                if(k >= array3.size())
                {
                    break;
                }
                jgl.HashMap hashmap3 = (jgl.HashMap)array3.at(k);
                if(((java.lang.String)hashmap3.get("_id")).equals((java.lang.String)hashmap.get("_id")))
                {
                    array3.put(k, hashmap);
                    j = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("_id"));
                    break;
                }
                k++;
            } while(true);
        } else
        {
            if(array3 != null && array3.size() > 0)
            {
                hashmap1 = (jgl.HashMap)array3.at(0);
            } else
            {
                hashmap1.add("_nextid", "0");
                array3.put(0, hashmap1);
            }
            int i = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap1.get("_nextid"));
            j = i;
            hashmap.add("_id", "" + i);
            array3.add(hashmap);
            i++;
            hashmap1.put("_nextid", "" + i);
        }
        saveGSRRunbook(array3);
        java.lang.String s1;
        for(java.util.Enumeration enumeration = array1.elements(); enumeration.hasMoreElements(); updategroup_recursive(s1, s, "" + j))
        {
            s1 = (java.lang.String)enumeration.nextElement();
        }
        
        java.util.Enumeration enumeration1 = array2.elements();
        do
        {
            if(!enumeration1.hasMoreElements())
            {
                break;
            }
            java.lang.String s4 = (java.lang.String)enumeration1.nextElement();
            int l = s4.indexOf(" ");
            java.lang.String s3 = s4.substring(0, l);
            java.lang.String s2 = s4.substring(l + 1, s4.length());
            jgl.Array array4 = loadgroup(s3);
            if(array4 != null)
            {
                jgl.HashMap hashmap4 = new HashMap();
                for(int i1 = 0; i1 < array4.size(); i1++)
                {
                    jgl.HashMap hashmap5 = (jgl.HashMap)array4.at(i1);
                    java.lang.String s5 = (java.lang.String)hashmap5.get("_id");
                    if(s5 != null && s5.equals(s2))
                    {
                        hashmap5.put(s, "" + j);
                        array4.put(i1, hashmap5);
                    }
                }
                
                savegroup(s3, array4);
            }
        } while(true);
    }
    
    public void createCustomEdit(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        jgl.Array array = loadGSRRunbook();
        jgl.HashMap hashmap = new HashMap();
        java.lang.String s4 = "<select name=\"$NAME$\"><option selected value=\"$VALUE$\">[$VALUE$]";
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            if(hashmap1.get("_type") != null && ((java.lang.String)hashmap1.get("_type")).equals(s1) || s1.equals("runbook") && ((java.lang.String)hashmap1.get("_type")).equals("runbookgroup"))
            {
                s4 = s4 + "<option value=" + (java.lang.String)hashmap1.get("_id") + ">[" + (java.lang.String)hashmap1.get("_id") + "] " + (java.lang.String)hashmap1.get("_name") + "</option>";
            }
        }
        
        java.lang.String s5 = "" + s + "|" + s2 + "|" + s3 + "| |";
        s5 = s5 + "" + s4 + "</select>";
        try
        {
            jgl.HashMap hashmap2 = (jgl.HashMap)COM.dragonflow.SiteView.MasterConfig.getMasterConfig().clone();
            hashmap2.allowsDuplicates();
            java.util.Enumeration enumeration = hashmap2.values("_monitorEditCustom");
            hashmap2.remove("_monitorEditCustom");
            do
            {
                if(!enumeration.hasMoreElements())
                {
                    break;
                }
                java.lang.String s6 = (java.lang.String)enumeration.nextElement();
                java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s6, "|");
                if(!as[0].equals(s))
                {
                    hashmap2.add("_monitorEditCustom", s6);
                }
            } while(true);
            hashmap2.add("_monitorEditCustom", s5);
            saveMasterConfig(hashmap2);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }
    
    public jgl.HashMap loadGSRFramebyID(java.lang.String s)
    {
        jgl.Array array = loadGSRRunbook();
        jgl.HashMap hashmap = new HashMap();
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            if(hashmap1.get("_id") != null && ((java.lang.String)hashmap1.get("_id")).equals(s))
            {
                return hashmap1;
            }
        }
        
        return null;
    }
    
    public void clearRunbookids(java.lang.String s)
    {
        clearRunbookids(s, "_runbookid");
    }
    
    public void clearRunbookids(java.lang.String s, java.lang.String s1)
    {
        jgl.Array array = null;
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        array = siteviewgroup.getGroupFileIDs();
        for(int i = 0; i < array.size(); i++)
        {
            updateRunbookidValue((java.lang.String)array.at(i), s1, "", s);
        }
        
    }
    
    public void updateRunbookEntry(jgl.HashMap hashmap, java.lang.String s)
    {
        saveRunbookEntry(hashmap, s, true);
    }
    
    public jgl.HashMap runbookToHashMap()
    {
        jgl.Array array = loadGSRRunbook();
        jgl.HashMap hashmap = new HashMap();
        jgl.HashMap hashmap1 = new HashMap();
        java.lang.String s = "";
        java.lang.String s2 = "";
        java.lang.String s4 = "";
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap2 = (jgl.HashMap)array.at(i);
            if(hashmap2.get("_id") == null)
            {
                continue;
            }
            java.lang.String s5 = (java.lang.String)hashmap2.get("_id");
            if(hashmap2.get("_type") != null)
            {
                java.lang.String s1 = (java.lang.String)hashmap2.get("_type");
                if(s1 != null && !s1.equals(""))
                {
                    hashmap.put("" + s5 + "_type", s1);
                }
            }
            if(hashmap2.get("_scope") != null)
            {
                java.lang.String s3 = (java.lang.String)hashmap2.get("_scope");
                if(s3 != null && !s3.equals(""))
                {
                    hashmap.put("" + s5 + "_scope", s3);
                }
            }
            if(hashmap2.get("_value") != null)
            {
                java.lang.String s6 = COM.dragonflow.Utils.TextUtils.replaceString((java.lang.String)hashmap2.get("_value"), putbackstr);
                hashmap.put("" + s5, s6);
            }
        }
        
        return hashmap;
    }
    
    public java.lang.String createXML()
    {
        jgl.HashMap hashmap = runbookToHashMap();
        jgl.Array array = loadGSRRunbook();
        jgl.HashMap hashmap1 = (jgl.HashMap)array.at(0);
        java.lang.String s = "";
        java.lang.String s1 = "";
        if(hashmap1.get("_account") != null)
        {
            s = (java.lang.String)hashmap1.get("_account");
        }
        if(hashmap1.get("_server") != null)
        {
            s1 = (java.lang.String)hashmap1.get("_server");
        }
        java.lang.String s2 = "";
        jgl.Array array1 = getMonitorGroupLists();
        jgl.Array array2 = (jgl.Array)array1.at(0);
        if(array2.size() == 0)
        {
            array2 = getTopLevelGroups();
        }
        s2 = s2 + "<?xml version=\"1.0\"?>\n";
        s2 = s2 + "<GSR>\n";
        s2 = s2 + "<account>" + s + "</account>\n";
        s2 = s2 + "<server>" + s1 + "</server>\n";
        java.util.Date date = new Date();
        java.lang.String s3 = "" + (date.getYear() + 1900);
        java.lang.String s4 = "" + (date.getMonth() + 1);
        java.lang.String s5 = "" + date.getDate();
        java.lang.String s6 = "" + s3 + "/" + s4 + "/" + s5 + " ";
        s6 = s6 + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds();
        s2 = s2 + "<timestamp>" + s6 + "</timestamp>\n";
        s2 = s2 + "<GSRRUNBOOK>\n";
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap2 = (jgl.HashMap)array.at(i);
            if(hashmap2.get("_id") != null && hashmap2.get("_value") != null && hashmap2.get("_type") != null && !((java.lang.String)hashmap2.get("_type")).equals("escalationgroup") && !((java.lang.String)hashmap2.get("_type")).equals("runbookgroup"))
            {
                s2 = s2 + "<id value=\"" + (java.lang.String)hashmap2.get("_id") + "\">";
                s2 = s2 + "<type>" + (java.lang.String)hashmap2.get("_type") + "</type>\n";
                s2 = s2 + "<value><![CDATA[" + COM.dragonflow.Utils.TextUtils.replaceString((java.lang.String)hashmap2.get("_value"), eraselinefeeds) + "]]></value>\n";
                s2 = s2 + "</id>\n";
            }
        }
        
        s2 = s2 + "</GSRRUNBOOK>\n";
        for(int j = 0; j < array2.size(); j++)
        {
            s2 = s2 + recurse_groupsforXML((java.lang.String)array2.at(j), "TOPLEVEL", hashmap);
        }
        
        s2 = s2 + "</GSR>\n";
        java.lang.String s7 = COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/runbook/runbook.xml";
        try
        {
            java.io.PrintWriter printwriter = COM.dragonflow.Utils.FileUtils.MakeOutputWriter(new FileOutputStream(s7));
            printwriter.println(s2);
            printwriter.close();
        }
        catch(java.io.IOException ioexception)
        {
            outputStream.println("Couldn't save file:<br>");
            ioexception.printStackTrace();
        }
        catch(java.lang.Exception exception)
        {
            outputStream.println("Couldn't save file:<br>");
            exception.printStackTrace();
        }
        return s2;
    }
    
    public java.lang.String createCommaDelimited()
    {
        jgl.HashMap hashmap = new HashMap();
        java.lang.String s = "";
        jgl.HashMap hashmap1 = runbookToHashMap();
        jgl.Array array = getMonitorGroupLists();
        jgl.Array array1 = (jgl.Array)array.at(0);
        if(array1.size() == 0)
        {
            array1 = getTopLevelGroups();
        }
        jgl.Array array2 = loadGSRRunbook();
        java.lang.String s1 = "";
        jgl.HashMap hashmap2 = new HashMap();
        for(int i = 1; i < array2.size(); i++)
        {
            boolean flag = false;
            jgl.HashMap hashmap3 = (jgl.HashMap)array2.at(i);
            java.lang.String s2 = "";
            java.lang.String s3 = "";
            java.lang.String s4 = "";
            java.lang.String s5 = "";
            java.lang.String s6 = "";
            java.lang.String s7 = "";
            if(hashmap3.get("_id") != null)
            {
                s2 = (java.lang.String)hashmap3.get("_id");
            }
            if(hashmap3.get("_name") != null)
            {
                s3 = (java.lang.String)hashmap3.get("_name");
            }
            if(hashmap3.get("_type") != null)
            {
                s4 = (java.lang.String)hashmap3.get("_type");
            }
            if(hashmap3.get("_scope") != null)
            {
                s5 = (java.lang.String)hashmap3.get("_scope");
            }
            if(hashmap3.get("_escalationtype") != null)
            {
                s6 = (java.lang.String)hashmap3.get("_esclationtype");
            }
            if(hashmap3.get("_value") != null)
            {
                s7 = (java.lang.String)hashmap3.get("_value");
            }
            if(s4.equals("runbookgroup") || s4.equals("runbook"))
            {
                hashmap.put(s2, s5);
            }
            java.util.Enumeration enumeration = request.getValues("scope");
            while (enumeration.hasMoreElements())
                {
                if(s5.equals((java.lang.String)enumeration.nextElement()))
                {
                    flag = true;
                }
            } 
            
            if(flag || s4.equals("escalation") || s4.equals("escalationgroup"))
            {
                s1 = s1 + "" + s2 + ",'" + s3 + "'," + s4 + ",";
                s1 = s1 + s5 + "," + s6 + ",'" + s7 + "'<CRLF>";
            }
        }
        
        for(int j = 0; j < array1.size(); j++)
        {
            s = s + recurse_groupsforCommaDelimited((java.lang.String)array1.at(j), "TOPLEVEL", hashmap1, hashmap);
        }
        
        s = s + "##########<CRLF>";
        s = s + s1;
        return s;
    }
    
    public java.lang.String escapeXML(java.lang.String s)
    {
        s = "<![CDATA[" + s + "]]>";
        return s;
    }
    
    public void applyXSLsheets(java.lang.String s)
    {
        java.lang.String s1 = COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/runbook/runbook.xml";
        java.lang.String s2 = s.substring(0, s.indexOf(".xsl")) + ".html";
        try
        {
            COM.dragonflow.Utils.XSLUtils.convert(s1, COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/runbook/" + s, COM.dragonflow.SiteView.Platform.getRoot() + "/htdocs/" + s2);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
        java.lang.String s3 = "";
        try
        {
            s3 = COM.dragonflow.Utils.FileUtils.readFile(COM.dragonflow.SiteView.Platform.getRoot() + "/htdocs/" + s2).toString();
        }
        catch(java.io.IOException ioexception1)
        {
            ioexception1.printStackTrace();
        }
        s3 = COM.dragonflow.Utils.TextUtils.replaceString(s3, xmlputback);
        try
        {
            java.io.PrintWriter printwriter = COM.dragonflow.Utils.FileUtils.MakeOutputWriter(new FileOutputStream(COM.dragonflow.SiteView.Platform.getRoot() + "/htdocs/" + s2));
            printwriter.println(s3);
            printwriter.close();
        }
        catch(java.io.IOException ioexception2)
        {
            outputStream.println("Couldn't save file:<br>");
            ioexception2.printStackTrace();
        }
        catch(java.lang.Exception exception)
        {
            outputStream.println("Couldn't save file:<br>");
            exception.printStackTrace();
        }
    }
    
    public java.lang.String recurse_groupsforXML(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap)
    {
        java.lang.String s2 = "";
        jgl.Array array = null;
        java.lang.String s3 = "";
        java.lang.String s4 = COM.dragonflow.Page.CGI.getGroupName(s);
        array = loadgroup(s);
        if(array != null)
        {
            s2 = s2 + "<group name=\"" + s + "\" parent=\"" + s1 + "\">\n";
            s2 = s2 + "<name><![CDATA[" + s4 + "]]></name>\n";
            for(int i = 1; i < array.size(); i++)
            {
                jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
                java.lang.String s5 = (java.lang.String)hashmap1.get("_class");
                if(s5 == null || !s5.equals("SubGroup"))
                {
                    java.lang.String s6 = "";
                    java.lang.String s7 = "";
                    java.lang.String s9 = "";
                    java.lang.String s11 = "";
                    java.lang.String s13 = "";
                    java.lang.String s14 = "";
                    java.lang.String s15 = "";
                    boolean flag = false;
                    java.lang.String as[] = null;
                    if(hashmap1.get("_runbookid") != null)
                    {
                        s6 = (java.lang.String)hashmap1.get("_runbookid");
                    }
                    if(hashmap.get(s6) != null)
                    {
                        java.lang.String s8 = (java.lang.String)hashmap.get(s6);
                        if(hashmap.get("" + s6 + "_type") != null && ((java.lang.String)hashmap.get("" + s6 + "_type")).equals("runbookgroup"))
                        {
                            flag = true;
                            as = COM.dragonflow.Utils.TextUtils.split(s8, ",");
                        } else
                        {
                            s8 = (java.lang.String)hashmap.get(s6);
                        }
                    }
                    if(hashmap1.get("_escalationid") != null)
                    {
                        java.lang.String s10 = (java.lang.String)hashmap1.get("_escalationid");
                        if(hashmap.get(s10) != null && hashmap.get("" + s10 + "_type") != null && ((java.lang.String)hashmap.get("" + s10 + "_type")).equals("escalationgroup"))
                        {
                            java.lang.String s12 = (java.lang.String)hashmap.get(s10);
                            if(s12 != null && !s12.equals(""))
                            {
                                java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(s12, ",");
                                if(as1.length == 3)
                                {
                                    s13 = as1[0];
                                    s14 = as1[1];
                                    s15 = as1[2];
                                }
                            }
                        }
                    }
                    s2 = s2 + "<monitor id=\"" + (java.lang.String)hashmap1.get("_id") + "\">\n";
                    s2 = s2 + "<name><![CDATA[" + (java.lang.String)hashmap1.get("_name") + "]]></name>";
                    if(flag && s6 != null && !s6.equals(""))
                    {
                        for(int j = 0; j < as.length; j++)
                        {
                            s2 = s2 + "<runbook id=\"" + (j + 1) + "\" value=\"" + as[j] + "\"/>\n";
                        }
                        
                    } else
                    {
                        s2 = s2 + "<runbook id=\"1\" value=\"" + s6 + "\"/>\n";
                    }
                    s2 = s2 + "<escalation>\n";
                    s2 = s2 + "<level id=\"1\" value=\"" + s13 + "\"/>\n";
                    s2 = s2 + "<level id=\"2\" value=\"" + s14 + "\"/>\n";
                    s2 = s2 + "<level id=\"3\" value=\"" + s15 + "\"/>\n";
                    s2 = s2 + "</escalation>\n";
                    s2 = s2 + "</monitor>\n";
                } else
                {
                    s3 = s3 + recurse_groupsforXML((java.lang.String)hashmap1.get("_group"), s, hashmap);
                }
            }
            
            s2 = s2 + "</group>";
            s2 = s2 + s3;
        }
        return s2;
    }
    
    public java.lang.String recurse_groupsforCommaDelimited(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap, jgl.HashMap hashmap1)
    {
        java.lang.String s2 = "";
        java.lang.String s3 = "none";
        jgl.Array array = null;
        array = loadgroup(s);
        if(array != null)
        {
            jgl.Array array1 = loadGSRRunbook();
            jgl.HashMap hashmap2 = (jgl.HashMap)array1.at(0);
            for(int i = 1; i < array.size(); i++)
            {
                boolean flag = false;
                jgl.HashMap hashmap3 = (jgl.HashMap)array.at(i);
                java.lang.String s4 = (java.lang.String)hashmap3.get("_class");
                if(s4 == null || !s4.equals("SubGroup"))
                {
                    java.lang.String s5 = "0";
                    java.lang.String s6 = "";
                    java.lang.String s7 = "0";
                    java.lang.String s8 = "";
                    java.lang.String s9 = "";
                    if(hashmap3.get("_runbookid") != null && !((java.lang.String)hashmap3.get("_runbookid")).equals(""))
                    {
                        s5 = (java.lang.String)hashmap3.get("_runbookid");
                    }
                    if(hashmap3.get("_escalationid") != null && !((java.lang.String)hashmap3.get("_escalationid")).equals(""))
                    {
                        s7 = (java.lang.String)hashmap3.get("_escalationid");
                    }
                    if(hashmap.get(s5) != null && !((java.lang.String)hashmap.get(s5)).equals(""))
                    {
                        s6 = (java.lang.String)hashmap.get(s5);
                    }
                    if(hashmap2.get("_account") != null)
                    {
                        s8 = (java.lang.String)hashmap2.get("_account");
                    }
                    if(hashmap2.get("_server") != null)
                    {
                        s9 = (java.lang.String)hashmap2.get("_server");
                    }
                    if(hashmap1.get(s5) != null)
                    {
                        s3 = (java.lang.String)hashmap1.get(s5);
                    }
                    java.util.Enumeration enumeration = request.getValues("scope");
                    while (enumeration.hasMoreElements())
                        {
                        if(s3.equals((java.lang.String)enumeration.nextElement()))
                        {
                            flag = true;
                        }
                    } 
                    
                    if(flag)
                    {
                        s2 = s2 + "" + s9 + "," + s8 + "," + s + "," + s1 + "," + (java.lang.String)hashmap3.get("_name") + "," + s5 + "," + s7 + "<CRLF>";
                    }
                } else
                {
                    s2 = s2 + recurse_groupsforCommaDelimited((java.lang.String)hashmap3.get("_group"), s, hashmap, hashmap1);
                }
            }
            
        }
        return s2;
    }
    
    public void printEscalationForm()
    {
        outputStream.println("<br><br><h3>Create New  Escalation</h3><br>");
        outputStream.println("<form method=post action=/SiteView ><br>Name<input type=text name=escalate_name size=40><br><input type=hidden name=action value=\"NEW ESCALATION\">Type<select name=escalate_type ><option value=1>Phone<option value=2>Pager<option value=3>Email</select><br>Details<input type=text name=escalate_details size=80><br><input type=hidden name=page value=GSR><input type=hidden name=operation value=save><input type=submit value=SUBMIT></form>");
    }
    
    public void editEscalationForm(java.io.PrintWriter printwriter, boolean flag, java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, 
            java.lang.String s5)
    {
        printwriter.println("<br><br><h3>Edit  Escalation</h3><br>");
        printwriter.println("<form method=post action=/SiteView ><br>Name<input type=text name=escalate_name size=40 value=\"" + s2 + "\"><br>" + "<input type=hidden name=action value=\"" + s5 + "\">" + "<input type=hidden name=id_selection value=\"" + s + "\">" + "Type<select name=escalate_type ><option value=" + s3 + ">" + s1 + "</option><option value=1>Phone<option value=2>Pager<option value=3>Email</select><br>" + "Details<input type=text name=escalate_details size=80 value=\"" + s4 + "\"><br>" + "<input type=hidden name=page value=GSR><input type=hidden name=operation value=save>" + "<input type=submit value=SUBMIT></form>");
    }
    
    public void saveEscalation()
    {
        jgl.Array array = loadGSRRunbook();
        int i = 0;
        jgl.HashMap hashmap = (jgl.HashMap)array.at(0);
        if(hashmap.get("_nextid") != null)
        {
            i = COM.dragonflow.Utils.TextUtils.toInt((java.lang.String)hashmap.get("_nextid"));
        }
        hashmap.put("_nextid", "" + (i + 1));
        array.put(0, hashmap);
        jgl.HashMap hashmap1 = new HashMap();
        hashmap1.add("_id", "" + i);
        hashmap1.add("_name", request.getValue("escalate_name"));
        hashmap1.add("_type", "escalation");
        hashmap1.add("_subtype", request.getValue("escalate_type"));
        hashmap1.add("_value", request.getValue("escalate_details"));
        array.add(hashmap1);
        saveGSRRunbook(array);
    }
    
    public void deleteRunbookID(java.lang.String s)
    {
        jgl.Array array = loadGSRRunbook();
        jgl.HashMap hashmap = new HashMap();
        java.lang.String s1 = "";
        java.lang.String s3 = "";
        java.lang.String s5 = "";
        for(int i = 1; i < array.size(); i++)
        {
            jgl.HashMap hashmap1 = (jgl.HashMap)array.at(i);
            java.lang.String s2 = (java.lang.String)hashmap1.get("_id");
            java.lang.String s4 = (java.lang.String)hashmap1.get("_value");
            java.lang.String s6 = (java.lang.String)hashmap1.get("_type");
            if(s2.equals(s))
            {
                array.remove(i);
            }
            if(!s6.equals("runbookgroup") && !s6.equals("escalationgroup"))
            {
                continue;
            }
            boolean flag = false;
            java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s4, ",");
            for(int j = 0; j < as.length; j++)
            {
                if(as[j].equals(s))
                {
                    as[j] = "";
                    flag = true;
                }
            }
            
            if(!flag)
            {
                continue;
            }
            for(int k = 0; k < as.length; k++)
            {
                s4 = s4 + as[k] + ",";
            }
            
            COM.dragonflow.Utils.TextUtils.chomp(s4);
            hashmap1.put("_value", s4);
            array.put(i, hashmap1);
        }
        
        saveGSRRunbook(array);
    }
    
    public void saveGSRRunbook(jgl.Array array)
    {
        try
        {
            COM.dragonflow.Properties.FrameFile.writeToFile(COM.dragonflow.SiteView.Platform.getRoot() + "/groups/GSRRunbook.config", array, "", true, true);
        }
        catch(java.io.IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }
    
    public void printEscalationGroupForm()
    {
        printEscalationGroupForm(null, null, "CREATE ESCALATION GROUP", null);
    }
    
    public void printEscalationGroupForm(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3)
    {
        java.lang.String as[] = selectboxes_create(false);
        java.lang.String s4 = as[1];
        java.lang.String s5 = COM.dragonflow.Utils.TextUtils.replaceString(s4, "escalation_select", "elevel1");
        java.lang.String s6 = COM.dragonflow.Utils.TextUtils.replaceString(s4, "escalation_select", "elevel2");
        java.lang.String s7 = COM.dragonflow.Utils.TextUtils.replaceString(s4, "escalation_select", "elevel3");
        if(s1 == null)
        {
            s1 = "";
        }
        if(s3 != null)
        {
            java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(s3, ",");
            java.lang.String s8 = as1[0];
            java.lang.String s9 = as1[1];
            java.lang.String s10 = as1[2];
            s5 = COM.dragonflow.Utils.TextUtils.replaceString(s5, "<option value=" + s8 + ">", "<option value=" + s8 + " SELECTED>");
            s6 = COM.dragonflow.Utils.TextUtils.replaceString(s6, "<option value=" + s9 + ">", "<option value=" + s9 + " SELECTED>");
            s7 = COM.dragonflow.Utils.TextUtils.replaceString(s7, "<option value=" + s10 + ">", "<option value=" + s10 + " SELECTED>");
        }
        outputStream.println("<br><br><h3>Create New  Escalation Group</h3><br>");
        outputStream.println("<form method=post action=/SiteView ><br>Name<input type=text name=escalate_name size=40 value=\"" + s1 + "\"><br>" + "<table><tr><th bgcolor=ccffff>Primary Contact</th><th  bgcolor=ccffff>Secondary Contact</th><th  bgcolor=ccffff>Final Contact</th></tr>" + "<tr><td bgcolor=000000>" + s5 + "</td><td bgcolor=000000>" + s6 + "</td><td bgcolor=000000>" + s7 + "</td></tr>" + "</table><br>" + "<input type=hidden name=id_selection value=" + s + ">" + "<input type=hidden name=action value=\"" + s2 + "\">" + "<input type=hidden name=page value=GSR><input type=hidden name=operation value=save>" + "<input type=submit value=SUBMIT>");
    }
    
    public void printRunbookGroupForm()
    {
        printRunbookGroupForm(null, null, "CREATE RUNBOOK GROUP", null, null);
    }
    
    public void printRunbookGroupForm(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4)
    {
        java.lang.String as[] = selectboxes_create(false);
        java.lang.String s5 = as[0];
        java.lang.String as1[] = null;
        java.lang.String s6 = "";
        java.lang.String as2[] = new java.lang.String[RUNBOOKGROUP_SELECT];
        if(s4 != null)
        {
            as1 = COM.dragonflow.Utils.TextUtils.split(s4, ",");
        }
        for(int i = 0; i < RUNBOOKGROUP_SELECT; i++)
        {
            as2[i] = COM.dragonflow.Utils.TextUtils.replaceString(s5, "runbook_select", "runbook" + (i + 1));
            if(s4 != null && as1 != null && i < as1.length)
            {
                as2[i] = COM.dragonflow.Utils.TextUtils.replaceString(as2[i], "<option value=" + as1[i] + ">", "<option value=" + as1[i] + " SELECTED>");
            } else
            {
                as2[i] = COM.dragonflow.Utils.TextUtils.replaceString(as2[i], "<option value=>", "<option value= SELECTED>");
            }
        }
        
        if(s4 != null && as1.length > RUNBOOKGROUP_SELECT)
        {
            int j;
            for(j = RUNBOOKGROUP_SELECT; j < as1.length - 1; j++)
            {
                s6 = s6 + as1[j] + ",";
            }
            
            s6 = s6 + as1[j];
        }
        if(s1 == null)
        {
            s1 = "";
        }
        outputStream.println("<br><br><h3>Create New  Runbook Group</h3><br>");
        outputStream.println("<form method=post action=/SiteView ><br>Name<input type=text name=runbook_name size=40 value=\"" + s1 + "\"><br>" + "<input type=hidden name=runbook_scope value=2><br>" + "<table>");
        for(int k = 0; k < RUNBOOKGROUP_SELECT; k += 4)
        {
            COM.dragonflow.Utils.TextUtils.debugPrint("printing runbook line:" + k + "\n");
            outputStream.println("<tr><th bgcolor=ccffff><b>" + (k + 1) + "</b></th><th  bgcolor=ccffff><b>" + (k + 2) + "</b></th><th  bgcolor=ccffff><b>" + (k + 3) + "</b></th></th><th  bgcolor=ccffff><b>" + (k + 4) + "</b></th></tr>");
            outputStream.println("<tr>");
            for(int l = 0; l < 4; l++)
            {
                COM.dragonflow.Utils.TextUtils.debugPrint("print runbook column:" + l + "\n");
                if(as2 != null && k + l < as2.length)
                {
                    outputStream.println("<td bgcolor=000000>" + as2[k + l] + "</td>");
                } else
                {
                    outputStream.println("<td bgcolor=000000></td>");
                }
            }
            
            outputStream.println("</tr>");
        }
        
        outputStream.println("</table><br><b>Additional Runbook Snippets in comma-delimited format (ie. 1,2,7,6)</b><br><input type=text size=40 name=morerunbooks value=\"" + s6 + "\"><br>" + "<input type=hidden name=id_selection value=" + s + ">" + "<input type=hidden name=action value=\"" + s2 + "\">" + "<input type=hidden name=page value=GSR><input type=hidden name=operation value=save>" + "<input type=submit value=SUBMIT>");
    }
    
    public void printXSLchoosepage()
    {
        outputStream.println("<br><br><center><h3>Choose XSL Templates to apply to the Runbook XML Document</h3><br><font color=red>To see the XML Document choose no items and hit the submit button</font></center><br><form method=post action=\"/SiteView/cgi/go.exe/SiteView\"><input type=hidden name=page value=GSR><input type=hidden name=action value=\"CREATE STATIC RUNBOOK\"><input type=hidden name=operation value=save><input type=hidden name=account value=" + request.getAccount() + ">" + "<center><table border=0><tr><th><B>XSL FILES</B></th><th><b>HTML FILES</B></TH></TR>" + "<TR><TD BGCOLOR=CCFFFF WIDTH=300>" + "<center><select name=xsltemplates size=10 multiple>");
        java.io.File file = new File(COM.dragonflow.SiteView.Platform.getRoot() + "/templates.view/runbook");
        try
        {
            java.lang.String as[] = file.list();
            java.lang.String s = "<center>";
            java.lang.String s1 = "";
            outputStream.println("<option value=\"\" ></option>");
            for(int i = 0; i < as.length; i++)
            {
                if(COM.dragonflow.Utils.TextUtils.match(as[i], "/.*.xsl$/"))
                {
                    outputStream.println("<option value=\"" + as[i] + "\" ");
                    java.lang.String s2 = as[i].substring(0, as[i].indexOf(".xsl")) + ".html";
                    s = s + "<a href=/SiteView/htdocs/" + s2 + " target=runbook>" + s2 + "</a><br>";
                    outputStream.println(">" + as[i] + " </option>");
                }
            }
            
            outputStream.println("</select></center></TD><TD bgcolor=ccffcc width=300>" + s + "</center></td></tr></table></center><br>");
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
        }
        outputStream.println("<BR><center><INPUT TYPE=SUBMIT VALUE=\"SUBMIT\"></center>");
        printselectedMonitorsGroups(outputStream);
        outputStream.println("</FORM>");
    }
    
    public void printExportForm()
    {
        outputStream.println("<br><br><center><h3>Export Runbook Data</h3><br><form method=post action=\"/SiteView/cgi/go.exe/SiteView\"><input type=hidden name=page value=GSR><input type=hidden name=action value=\"EXPORT RUNBOOK\"><input type=hidden name=operation value=save><input type=hidden name=account value=" + request.getAccount() + ">" + "<b>Email:</b><input type type=text size=40 name=mailto><br>" + "<b>Scope:</b><select name=scope multiple size =5>" + "<option value=1>Internal</option>" + "<option value=2 selected>External</option>" + "<option value=3 >Both</option>" + "</select>");
        printselectedMonitorsGroups(outputStream);
        outputStream.println("<br><input type=submit value=SUBMIT><br></form>");
    }
    
    public jgl.Array getTopLevelGroups()
    {
        jgl.Array array = new Array();
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array1 = siteviewgroup.getGroupFileIDs();
        for(int i = 0; i < array1.size(); i++)
        {
            COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup)siteviewgroup.getElement((java.lang.String)array1.at(i));
            java.lang.String s = monitorgroup.getProperty("_parent");
            COM.dragonflow.Utils.TextUtils.debugPrint("Group: " + (java.lang.String)array1.at(i) + " parent: " + s + "\n");
            if(array1.at(i) != null && !((java.lang.String)array1.at(i)).equals("") && (s == null || s.equals("") || s.equals("null")))
            {
                array.add((java.lang.String)array1.at(i));
            }
         }
        
        return array;
    }
    
    public static void main(java.lang.String args[])
    throws java.io.IOException
    {
        COM.dragonflow.Page.GSRPage gsrpage = new GSRPage();
        if(args.length > 0)
        {
            gsrpage.args = args;
        }
        gsrpage.handleRequest();
    }
    
}
