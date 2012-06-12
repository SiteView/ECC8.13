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

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequestException;

// Referenced classes of package com.dragonflow.Page:
// CGI

public class commandPage extends com.dragonflow.Page.CGI
{

    public static java.lang.String CRLF = "\r\n";

    public commandPage()
    {
    }

    public void printBody()
        throws java.lang.Exception
    {
        if(!request.actionAllowed("_command"))
        {
            throw new HTTPRequestException(557);
        }
        char c = '\310';
        java.lang.String s = null;
        outputStream.println("<?xml version=\"1.0\"?>");
        outputStream.println("<SOAP-Envelope>");
        outputStream.println("<SOAP-Body>");
        try
        {
            java.lang.String s1 = request.getValue("object");
            java.lang.String s2 = request.getValue("method");
            java.lang.String s3 = request.getValue("name");
            outputStream.println("<method>" + s2 + "</method>");
            if(s1.length() > 0)
            {
                outputStream.println("<object>" + s1 + "</object>");
            }
            if(s3.length() > 0)
            {
                outputStream.println("<name>" + s3 + "</name>");
            }
            if(s2.equals("help") || s2.length() == 0)
            {
                outputStream.println("<help>");
                outputStream.println("<object>user</object>");
                outputStream.println("<method>edit</method>");
                outputStream.println("<param>name</param>");
                outputStream.println("<param>_prop=value</param>");
                outputStream.println("<description>edit a SiteView user property</description>");
                outputStream.println("</help>");
                outputStream.println("<help>");
                outputStream.println(" <object>globals</object>");
                outputStream.println(" <method>edit</method>");
                outputStream.println("<param>_prop=value</param>");
                outputStream.println(" <description>edit a SiteView global property</description>");
                outputStream.println("</help>");
                throw new Exception("usage");
            }
            if(s1.equals("user"))
            {
                if(s2.equals("list"))
                {
                    jgl.Array array = com.dragonflow.SiteView.User.readUsers();
                    for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); outputStream.println("</user>"))
                    {
                        jgl.HashMap hashmap3 = (jgl.HashMap)enumeration.nextElement();
                        java.util.Enumeration enumeration4 = hashmap3.keys();
                        java.lang.String s10 = "";
                        outputStream.println("<user>");
                        while(enumeration4.hasMoreElements()) 
                        {
                            java.lang.String s15 = (java.lang.String)enumeration4.nextElement();
                            outputStream.println("<" + s15 + ">" + hashmap3.get(s15) + "</" + s15 + ">");
                            java.lang.String s11 = ",";
                        }
                    }

                } else
                if(s2.equals("edit"))
                {
                    jgl.Array array1 = com.dragonflow.SiteView.User.readUsers();
                    jgl.HashMap hashmap2 = com.dragonflow.SiteView.User.findUser(array1, s3);
                    if(hashmap2 == null)
                    {
                        throw new Exception("unknown user: " + s3);
                    }
                    java.util.Enumeration enumeration3 = request.getVariables();
                    do
                    {
                        if(!enumeration3.hasMoreElements())
                        {
                            break;
                        }
                        java.lang.String s8 = (java.lang.String)enumeration3.nextElement();
                        if(s8.startsWith("_"))
                        {
                            java.lang.String s12 = (java.lang.String)hashmap2.get(s8);
                            java.lang.String s16 = request.getValue(s8);
                            outputStream.println("<edit>");
                            outputStream.println(" <param>" + s8 + "</param>");
                            outputStream.println(" <old-value>" + s12 + "</old-value>");
                            outputStream.println(" <new-value>" + s16 + "</new-value>");
                            outputStream.println("</edit>");
                            hashmap2.put(s8, s16);
                        }
                    } while(true);
                    com.dragonflow.SiteView.User.writeUsers(array1);
                } else
                {
                    throw new Exception("unknown method: " + s2 + ", object=user");
                }
            } else
            if(s1.equals("group"))
            {
                if(!s2.equals("add") && !s2.equals("edit"))
                {
                    throw new Exception("unknown method: " + s2 + ", object=group");
                }
                java.lang.String s4 = request.getValue("group");
                jgl.Array array2;
                jgl.HashMap hashmap4;
                if(s2.equals("edit"))
                {
                    array2 = ReadGroupFrames(s4);
                    if(array2.size() > 0)
                    {
                        hashmap4 = (jgl.HashMap)array2.at(0);
                    } else
                    {
                        hashmap4 = new HashMap();
                        hashmap4.put("_nextID", "1");
                        array2.add(hashmap4);
                    }
                } else
                {
                    if((new File(com.dragonflow.Page.commandPage.getGroupFilePath(s4, request, ".mg"))).exists())
                    {
                        throw new Exception("group exists: method=" + s2 + ", group=" + s4 + ", object=group");
                    }
                    array2 = new Array();
                    hashmap4 = new HashMap();
                    hashmap4.put("_nextID", "1");
                    array2.add(hashmap4);
                }
                outputStream.println("<" + s2 + ">");
                outputStream.println("<group>" + s4 + "</group>");
                java.util.Enumeration enumeration5 = request.getVariables();
                do
                {
                    if(!enumeration5.hasMoreElements())
                    {
                        break;
                    }
                    java.lang.String s13 = (java.lang.String)enumeration5.nextElement();
                    if(s13.startsWith("_"))
                    {
                        java.lang.String s17 = (java.lang.String)hashmap4.get(s13);
                        java.lang.String s20 = request.getValue(s13);
                        outputStream.println("<edit>");
                        outputStream.println(" <param>" + s13 + "</param>");
                        outputStream.println(" <old-value>" + s17 + "</old-value>");
                        outputStream.println(" <new-value>" + s20 + "</new-value>");
                        outputStream.println("</edit>");
                        hashmap4.put(s13, s20);
                    }
                } while(true);
                outputStream.println("</" + s2 + ">");
                WriteGroupFrames(s4, array2);
                com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s4);
                com.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
            } else
            if(s1.equals("monitor"))
            {
                if(!s2.equals("add") && !s2.equals("edit"))
                {
                    throw new Exception("unknown method: " + s2 + ", object=monitor");
                }
                java.lang.String s5 = request.getValue("group");
                if(s5.length() == 0)
                {
                    throw new Exception("missing group parameter, method=" + s2 + ", object=monitor");
                }
                jgl.Array array3;
                jgl.HashMap hashmap5;
                if((new File(com.dragonflow.Page.commandPage.getGroupFilePath(s5, request, ".mg"))).exists())
                {
                    array3 = ReadGroupFrames(s5);
                    if(array3.size() > 0)
                    {
                        hashmap5 = (jgl.HashMap)array3.at(0);
                    } else
                    {
                        hashmap5 = new HashMap();
                        hashmap5.put("_nextID", "1");
                        array3.add(hashmap5);
                    }
                } else
                {
                    array3 = new Array();
                    hashmap5 = new HashMap();
                    hashmap5.put("_nextID", "1");
                    array3.add(hashmap5);
                }
                int i = com.dragonflow.Utils.TextUtils.toInt(request.getValue("ordering"));
                if(i <= 1)
                {
                    i = 1;
                }
                jgl.HashMap hashmap6;
                if(s2.equals("add"))
                {
                    java.lang.String s18 = com.dragonflow.Utils.TextUtils.getValue(hashmap5, "_nextID");
                    if(s18.length() == 0)
                    {
                        s18 = "1";
                    }
                    hashmap6 = new HashMap();
                    hashmap6.put("_id", s18);
                    if(request.getValue("_class").length() == 0)
                    {
                        throw new Exception("missing class parameter, method=" + s2 + ", object=monitor");
                    }
                    array3.insert(i, hashmap6);
                    java.lang.String s21 = com.dragonflow.Utils.TextUtils.increment(s18);
                    hashmap5.put("_nextID", s21);
                } else
                {
                    java.lang.String s19 = request.getValue("id");
                    if(s19.length() == 0)
                    {
                        throw new Exception("missing id parameter, method=" + s2 + ", object=monitor");
                    }
                    int j = com.dragonflow.Page.commandPage.findMonitorIndex(array3, s19);
                    hashmap6 = (jgl.HashMap)array3.at(j);
                    array3.remove(j);
                    array3.insert(i, hashmap6);
                }
                outputStream.println("<" + s2 + ">");
                outputStream.println("<group>" + s5 + "</group>");
                java.util.Enumeration enumeration6 = request.getVariables();
                do
                {
                    if(!enumeration6.hasMoreElements())
                    {
                        break;
                    }
                    java.lang.String s22 = (java.lang.String)enumeration6.nextElement();
                    if(s22.startsWith("_"))
                    {
                        java.lang.String s23 = (java.lang.String)hashmap6.get(s22);
                        java.lang.String s24 = request.getValue(s22);
                        outputStream.println("<edit>");
                        outputStream.println(" <param>" + s22 + "</param>");
                        outputStream.println(" <old-value>" + s23 + "</old-value>");
                        outputStream.println(" <new-value>" + s24 + "</new-value>");
                        outputStream.println("</edit>");
                        hashmap6.put(s22, s24);
                    }
                } while(true);
                outputStream.println("</" + s2 + ">");
                WriteGroupFrames(s5, array3);
                com.dragonflow.SiteView.SiteViewGroup.updateStaticPages(s5);
                com.dragonflow.SiteView.SiteViewGroup.updateStaticPages();
            } else
            if(s1.equals("globals"))
            {
                if(s2.equals("list"))
                {
                    jgl.HashMap hashmap = getMasterConfig();
                    outputStream.println("<globals>");
                    java.lang.String s6;
                    for(java.util.Enumeration enumeration1 = hashmap.keys(); enumeration1.hasMoreElements(); outputStream.println("<" + s6 + ">" + hashmap.get(s6) + "</" + s6 + ">"))
                    {
                        s6 = (java.lang.String)enumeration1.nextElement();
                    }

                    outputStream.println("</globals>");
                } else
                if(s2.equals("edit"))
                {
                    jgl.HashMap hashmap1 = getMasterConfig();
                    java.util.Enumeration enumeration2 = request.getVariables();
                    do
                    {
                        if(!enumeration2.hasMoreElements())
                        {
                            break;
                        }
                        java.lang.String s7 = (java.lang.String)enumeration2.nextElement();
                        if(s7.startsWith("_"))
                        {
                            java.lang.String s9 = com.dragonflow.Page.commandPage.getValue(hashmap1, s7);
                            java.lang.String s14 = request.getValue(s7);
                            outputStream.println("<edit>");
                            outputStream.println(" <param>" + s7 + "</param>");
                            outputStream.println(" <old-value>" + s9 + "</old-value>");
                            outputStream.println(" <new-value>" + s14 + "</new-value>");
                            outputStream.println("</edit>");
                            hashmap1.put(s7, s14);
                        }
                    } while(true);
                    saveMasterConfig(hashmap1);
                } else
                {
                    throw new Exception("unknown method: " + s2 + ", object=globals");
                }
            } else
            {
                throw new Exception("unknown object: " + s1);
            }
        }
        catch(java.lang.Exception exception)
        {
            s = exception.getMessage();
            c = '\u01F4';
        }
        finally
        {
            if(c != '\310')
            {
                outputStream.println("<SOAP-Fault>");
                outputStream.println(" <faultcode>SOAP-ENV:Server</faultcode>");
                outputStream.println(" <faultstring>Server Error</faultstring>");
                outputStream.println(" <detail>");
                outputStream.println(" <siteview-fault>");
                outputStream.println("  <siteview-error>" + (int)c + "</siteview-error>");
                outputStream.println("  <siteview-errormessage>" + s + "</siteview-errormessage>");
                outputStream.println(" </siteview-fault>");
                outputStream.println(" </detail>");
                outputStream.println("</SOAP-Fault>");
            }
            outputStream.println("</SOAP-Body>");
            outputStream.println("</SOAP-Envelope>");
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

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        com.dragonflow.Page.commandPage commandpage = new commandPage();
        if(args.length > 0)
        {
            commandpage.args = args;
        }
        commandpage.handleRequest();
    }

}
