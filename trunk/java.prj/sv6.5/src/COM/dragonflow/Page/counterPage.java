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

import jgl.Array;

// Referenced classes of package COM.dragonflow.Page:
// CGI

public class counterPage extends COM.dragonflow.Page.CGI
{

    public counterPage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        java.lang.String s = "Choose Counters";
        if(!request.isPost())
        {
            printBodyHeader(s);
        }
        if(request.isPost())
        {
            java.lang.String s1 = request.getValue("returnURL");
            java.lang.String s3 = request.getValue("group");
            java.lang.String s5 = request.getValue("id");
            java.lang.String s7 = request.getValue("operation");
            java.lang.String s9 = request.getValue("counterobjects");
            java.lang.String s10 = request.getValue("server");
            java.lang.String s12 = request.getValue("account");
            java.lang.String s14 = request.getValue("classname");
            if(s14.length() > 0)
            {
                s1 = s1 + "&class=" + s14;
            }
            if(s3.length() > 0)
            {
                s1 = s1 + "&group=" + COM.dragonflow.HTTP.HTTPRequest.encodeString(s3);
            }
            if(s5.length() > 0)
            {
                s1 = s1 + "&id=" + s5;
            }
            if(s7.length() > 0)
            {
                s1 = s1 + "&operation=" + s7;
            }
            if(s9.length() > 0)
            {
                s1 = s1 + "&counterobjects=" + COM.dragonflow.HTTP.HTTPRequest.encodeString(s9);
            }
            if(s10.length() > 0)
            {
                s1 = s1 + "&server=" + COM.dragonflow.HTTP.HTTPRequest.encodeString(s10);
            }
            if(s12.length() > 0)
            {
                s1 = s1 + "&account=" + COM.dragonflow.HTTP.HTTPRequest.encodeString(s12);
            }
            java.lang.String s16 = "";
            int i = java.lang.Integer.valueOf(request.getValue("countersize")).intValue();
            int j = java.lang.Integer.valueOf(request.getValue("maxcounters")).intValue();
            int k = 0;
            boolean flag = true;
            for(int i1 = 0; i1 < i && k < j; i1++)
            {
                java.lang.String s17 = request.getValue("counter" + i1);
                if(s17.length() <= 0)
                {
                    continue;
                }
                k++;
                if(flag)
                {
                    s1 = s1 + "&counters=" + java.net.URLEncoder.encode(s17);
                    flag = false;
                } else
                {
                    s1 = s1 + "," + java.net.URLEncoder.encode(s17);
                }
            }

            autoFollowPortalRefresh = false;
            java.lang.System.out.println("CounterPage, doing a refresh to: " + s1);
            printRefreshPage(s1, 0);
        } else
        {
            java.lang.String s2 = "Monitors.htm#remote";
            printButtonBar(s2, "");
            java.lang.String s4 = request.getValue("id");
            java.lang.String s6 = request.getValue("group");
            java.lang.String s8 = request.getValue("operation");
            java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(request.getValue("counters"), ",");
            java.lang.String s11 = request.getValue("server");
            java.lang.String s13 = request.getValue("type");
            java.lang.String s15 = request.getValue("maxcounters");
            java.lang.String s18 = request.getValue("account");
            java.lang.String s19 = request.getValue("class");
            jgl.Array array = null;
            outputStream.println("<H2 align=\"center\">Choose Counters</H2><P>\nSelect a maximum of " + s15 + " counters for this application monitor. Click the <b>Choose</b> " + " button at the bottom of the page to continue with the monitor setup.<br>  <b>Note:</b> Only the first " + s15 + " selected will be chosen." + " A maximum of 10 measurements can be used as Alerting criteria. <p>");
            outputStream.println(getPagePOST("counter", "") + "<input type=hidden name=returnURL value=" + request.getValue("returnURL") + ">\n");
            outputStream.print("<TABLE>\n");
            if(s13.equals("NTCounter"))
            {
                java.lang.String s20 = request.getValue("counterobjects");
                jgl.Array array1 = new Array();
                java.lang.String as5[] = COM.dragonflow.Utils.TextUtils.split(s20, ",");
                for(int k2 = 0; k2 < as5.length; k2++)
                {
                    java.lang.String s29 = as5[k2].trim();
                    array1.add(s29);
                }

                java.lang.StringBuffer stringbuffer = new StringBuffer();
                array = COM.dragonflow.SiteView.NTCounterBase.getPerfCounters(s11, array1, stringbuffer, "");
                outputStream.print("<input type=hidden name=\"counterobjects\" value=\"" + s20 + "\">");
            }
            if(s13.equals("SNMP"))
            {
                array = new Array();
                java.lang.String s21 = COM.dragonflow.SiteView.SNMPBase.getTemplateContent(COM.dragonflow.SiteView.SNMPBase.getTemplatePath(), request.getValue("filename"), true);
                java.lang.String as1[] = COM.dragonflow.Utils.TextUtils.split(s21, ",");
                for(int j1 = 0; j1 < as1.length; j1++)
                {
                    if(as1[j1].length() > 0)
                    {
                        array.add(as1[j1]);
                    }
                }

            }
            if(s13.equals("URLContent"))
            {
                array = new Array();
                java.lang.String s22 = COM.dragonflow.SiteView.URLContentBase.getTemplateContent(COM.dragonflow.SiteView.URLContentBase.getTemplatePath(), request.getValue("filename"), true);
                java.lang.String as2[] = COM.dragonflow.Utils.TextUtils.split(s22, ",");
                for(int k1 = 0; k1 < as2.length; k1++)
                {
                    if(as2[k1].length() > 0)
                    {
                        array.add(as2[k1]);
                    }
                }

            }
            if(s13.equals("MultiContentBase"))
            {
                java.lang.System.out.println("counterPage - MultiContentBase");
                array = new Array();
                java.lang.String s23 = COM.dragonflow.SiteView.MultiContentBase.getTemplateContent(COM.dragonflow.SiteView.MultiContentBase.getTemplatePath(), request.getValue("filename"), true);
                java.lang.String as3[] = COM.dragonflow.Utils.TextUtils.split(s23, ",");
                for(int l1 = 0; l1 < as3.length; l1++)
                {
                    if(as3[l1].length() > 0)
                    {
                        array.add(as3[l1]);
                    }
                }

            }
            if(s13.equals("DynamicHealth"))
            {
                java.lang.System.out.println("counterPage - DynamicHealth");
                array = new Array();
                java.lang.String s24 = COM.dragonflow.StandardMonitor.HealthUnixServerMonitor.getAllCounterContent();
                java.lang.String as4[] = COM.dragonflow.Utils.TextUtils.split(s24, ",");
                for(int i2 = 0; i2 < as4.length; i2++)
                {
                    if(as4[i2].length() > 0)
                    {
                        array.add(as4[i2]);
                    }
                }

            }
            java.lang.System.out.println("counterPage - counters length: " + array.size());
            outputStream.print("<input type=hidden name=\"operation\" value=\"" + s8 + "\">");
            outputStream.print("<input type=hidden name=\"id\" value=\"" + s4 + "\">");
            outputStream.print("<input type=hidden name=\"group\" value=\"" + s6 + "\">");
            outputStream.print("<input type=hidden name=\"countersize\" value=\"" + array.size() + "\">");
            outputStream.print("<input type=hidden name=\"server\" value=\"" + s11 + "\">");
            outputStream.print("<input type=hidden name=\"type\" value=\"" + s13 + "\">");
            outputStream.print("<input type=hidden name=\"account\" value=\"" + s18 + "\">");
            outputStream.print("<input type=hidden name=\"maxcounters\" value=\"" + s15 + "\">");
            outputStream.print("<input type=hidden name=\"classname\" value=\"" + s19 + "\">");
            for(int l = 0; l < array.size(); l++)
            {
                java.lang.String s25 = "";
                int j2 = 0;
                do
                {
                    if(j2 >= as.length)
                    {
                        break;
                    }
                    if(as[j2].equals(java.lang.String.valueOf(l)))
                    {
                        s25 = "CHECKED";
                        break;
                    }
                    j2++;
                } while(true);
                if(s13.equals("NTCounter"))
                {
                    java.lang.String s27 = "";
                    java.lang.String s28 = "";
                    if(((COM.dragonflow.Utils.PerfCounter)array.at(l)).instance.length() > 0)
                    {
                        s28 = " -- " + ((COM.dragonflow.Utils.PerfCounter)array.at(l)).instance;
                    }
                    s27 = ((COM.dragonflow.Utils.PerfCounter)array.at(l)).object + " -- ";
                    outputStream.print("<TR><TD><input type=checkbox name=\"counter" + l + "\" value=\"" + l + "\"" + s25 + "> " + s27 + ((COM.dragonflow.Utils.PerfCounter)array.at(l)).counterName + s28 + "</TD></TR>");
                }
                if(!s13.equals("SNMP") && !s13.equals("URLContent") && !s13.equals("MultiContentBase") && !s13.equals("DynamicHealth"))
                {
                    continue;
                }
                if(array.at(l).toString().indexOf("//") == -1)
                {
                    outputStream.print("<TR><TD width=\"20\">&nbsp;&nbsp;</TD><TD><input type=checkbox name=\"counter" + l + "\" value=\"" + l + "\"" + s25 + "> " + array.at(l) + "</TD></TR>");
                } else
                {
                    outputStream.print("<TR><TD colspan=\"2\"><b>" + array.at(l).toString().substring(2) + "</b></TD></TR>");
                }
            }

            outputStream.println("</TABLE><HR>\n");
            outputStream.println("<p><input name=counters type=submit value=Choose> these counters and return to setup</input></FORM></p>\n");
            outputStream.println("<p><FORM ACTION=\"/SiteView/cgi/go.exe/SiteView/\" METHOD=\"GET\">\n");
            for(java.util.Enumeration enumeration = request.getVariables(); enumeration.hasMoreElements();)
            {
                java.lang.String s26 = (java.lang.String)enumeration.nextElement();
                if(s26.equals("counters"))
                {
                    outputStream.println("<input type=\"hidden\" name=\"" + s26 + "\" value=\"-1\">\n");
                } else
                {
                    outputStream.println("<input type=\"hidden\" name=\"" + s26 + "\" value=\"" + request.getValue(s26) + "\">\n");
                }
            }

            outputStream.println("<input name=counters type=submit value=Clear> current counter selections</input></FORM></p>\n");
        }
        printFooter(outputStream);
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        COM.dragonflow.Page.counterPage counterpage = new counterPage();
        if(args.length > 0)
        {
            counterpage.args = args;
        }
        counterpage.handleRequest();
    }
}
