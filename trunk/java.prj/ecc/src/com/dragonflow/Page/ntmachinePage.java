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
import com.dragonflow.Utils.CounterLock;
import com.dragonflow.Utils.SSHCommandLine;

// Referenced classes of package com.dragonflow.Page:
// remoteBase

public class ntmachinePage extends com.dragonflow.Page.remoteBase
{

    public ntmachinePage()
    {
    }

    java.lang.String getTestMachineID()
    {
        java.lang.String s = getMachineID();
        return s;
    }

    java.lang.String getTestMachineName()
    {
        jgl.HashMap hashmap = getTestMachineFrame();
        return com.dragonflow.Utils.TextUtils.getValue(hashmap, "_host");
    }

    java.lang.String getTestDescription()
    {
        return new String("<p>This test checks for both network connectivity and permissions to access  the selected machine.\nIf an access permission error is returned,\n make sure the user name and password are correct.\nIf a network connectivity error is returned check the network connection.\n");
    }

    com.dragonflow.SiteView.Machine getTestMachine()
    {
        java.lang.String s = getTestMachineName();
        com.dragonflow.SiteView.Machine machine = com.dragonflow.SiteView.Machine.getNTMachine(s);
        return machine;
    }

    boolean getTestMachineTrace()
    {
        jgl.HashMap hashmap = getTestMachineFrame();
        java.lang.String s = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_trace");
        boolean flag = s.length() > 0;
        return flag;
    }

    java.lang.String getTestCentra()
    {
        return "_centrascopeRemoteNTTestMatch";
    }

    java.lang.String getHelpPage()
    {
        return "NTRemote.htm";
    }

    java.lang.String getPage()
    {
        return "ntmachine";
    }

    java.lang.String getIDName()
    {
        return "ntMachineID";
    }

    java.lang.String getNextMachineName()
    {
        return "_nextNTRemoteID";
    }

    java.lang.String getRemoteName()
    {
        return "_remoteNTMachine";
    }

    java.lang.String getListTitle()
    {
        return "Remote NT Servers";
    }

    java.lang.String getListSubtitle()
    {
        return "A list of Win NT/2000 servers with connectivity and remote access permissions  for monitoring from this SiteView instance. Remote connection options include NetBIOS or SSH.  <b>Note:</b> Connections using SSH version 2 require additional set up.";
    }

    java.lang.String getPrefTitle()
    {
        return "NT Remotes";
    }

    java.lang.String getPrintFormSubmit()
    {
        return "Remote NT Server";
    }

    boolean displayFormTable(jgl.HashMap hashmap, java.lang.String s)
    {
        boolean flag = true;
        outputStream.println(field("NT Server Address", "<input type=text name=host size=50 value=\"" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_host") + "\">", "Enter the UNC style name (example:  \\\\machinename) or the IP address of the remote machine.  To use the same login credentials for multiple servers, enter multiple server addresses  separated by commas. "));
        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_method");
        if(s1.length() == 0)
        {
            s1 = "NetBIOS";
        }
        outputStream.println(field("Connection Method", "<select name=method size=1>" + com.dragonflow.Page.ntmachinePage.getOptionsHTML(com.dragonflow.SiteView.Machine.getNTAllowedMethods(), s1) + "</select>", "Select the method used to connect to the remote server. Requires that applicable services be enabled on the remote machine"));
        if(flag)
        {
            formLogin(hashmap);
        }
        java.lang.String s2 = com.dragonflow.Page.ntmachinePage.getValue(hashmap, "_trace").length() <= 0 ? "" : "CHECKED";
        outputStream.println(field("Trace", "<input type=checkbox name=trace " + s2 + ">", "Check to enable trace messages to and from the remote NT server in the RunMonitor.log file"));
        outputStream.println(field(s + " and Test", "<input type=\"radio\" name=\"addtest\" value=\"test\" CHECKED>", "Check to " + s + " the profile and test the connection"));
        outputStream.println(field(s + " Only", "<input type=\"radio\" name=\"addtest\" value=\"add\">", "Check to " + s + " the profile only"));
        outputStream.println(getAdnvacedSSHOptions(hashmap));
        return flag;
    }

    void saveAddProperties(java.lang.String s, jgl.HashMap hashmap, java.lang.String s1)
    {
        super.saveAddProperties(s, hashmap, s1);
        java.lang.String s2 = request.getValue("method");
        if(s2.length() == 0)
        {
            s2 = "NetBIOS";
        }
        java.lang.String s3 = (java.lang.String)hashmap.get("_host");
        if(!s3.startsWith("\\") && !request.getValue("method").equals("ssh"))
        {
            s3 = "\\\\" + s3;
        }
        if(s3.startsWith("\\") && request.getValue("method").equals("ssh"))
        {
            s3 = s3.substring(2);
        }
        hashmap.put("_id", s1);
        hashmap.put("_host", s3);
        hashmap.put("_method", s2);
        java.lang.String s4 = request.getValue("login");
        if(s4.indexOf("\\") == -1 && !request.getValue("method").equals("ssh"))
        {
            s4 = s3.substring(2) + "\\" + s4;
        }
        hashmap.put("_login", s4);
        hashmap.put("_trace", request.getValue("trace"));
        hashmap.put("_os", "NT");
        hashmap.put("_status", "unknown");
    }

    jgl.Array getListTableHeaders(java.lang.String s)
    {
        jgl.Array array = new Array();
        array.add(new String("Name"));
        array.add(new String("Server"));
        array.add(new String("Status"));
        array.add(new String("Method"));
        if(request.actionAllowed("_preference") || s.length() > 0)
        {
            array.add(new String("Edit"));
            array.add(new String("Test"));
            array.add(new String("Del"));
        }
        return array;
    }

    int doSSHTest(com.dragonflow.SiteView.Machine machine)
    {
        com.dragonflow.Utils.SSHCommandLine sshcommandline = new SSHCommandLine();
        sshcommandline.progressStream = outputStream;
        sshcommandline.exec("perfex.exe LogicalDisk", machine, true);
        if(sshcommandline.exitValue != 0)
        {
            return 100;
        }
        java.lang.String s = com.dragonflow.SiteView.Platform.perfexCommand("") + " -s";
        s = s.substring(s.indexOf("perfex"));
        sshcommandline.exec(s, machine, true);
        return sshcommandline.exitValue == 0 ? 0 : 100;
    }

    jgl.Array getListTableRow(jgl.HashMap hashmap, java.lang.String s)
    {
        com.dragonflow.SiteView.Machine.getAllowedMethods();
        jgl.Array array = new Array();
        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_id");
        java.lang.String s2 = com.dragonflow.Page.ntmachinePage.getValue(hashmap, "_name");
        if(s2.length() == 0)
        {
            s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_host");
        }
        array.add(new String("<b>" + s2 + "</b>"));
        array.add(new String(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_host")));
        array.add(new String("<b><i>" + com.dragonflow.Utils.TextUtils.getValue(hashmap, "_status") + "</i></b>"));
        array.add(new String(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_method")));
        if(request.actionAllowed("_preference") || s.length() > 0)
        {
            array.add(new String("<A href=" + getPageLink("ntmachine", "Edit") + "&ntMachineID=" + s1 + "&storeID=" + s + ">Edit</a>"));
            array.add(new String("<A href=" + getPageLink("ntmachine", "Test") + "&ntMachineID=" + s1 + "&storeID=" + s + "&link=true>Test</a>"));
            array.add(new String("<A href=" + getPageLink("ntmachine", "Delete") + "&ntMachineID=" + s1 + "&storeID=" + s + ">X</a>"));
        }
        return array;
    }

    void doTest(com.dragonflow.SiteView.Machine machine)
    {
        boolean flag = false;
        int i = 0;
        java.lang.String s = "";
        boolean flag1 = getTestMachineTrace();
        if(machine != null)
        {
            outputStream.println("<p>Testing connection to : <b>" + machine.getProperty(com.dragonflow.SiteView.Machine.pHost) + "</b>");
            outputStream.println("<HR><PRE>");
            outputStream.flush();
            if(machine.getProperty(com.dragonflow.SiteView.Machine.pMethod).equals("ssh"))
            {
                i = doSSHTest(machine);
            } else
            if(com.dragonflow.SiteView.SiteViewGroup.currentSiteView().internalServerActive())
            {
                i = checkNTPermissions(machine, flag1);
            }
            if(i != 0)
            {
                if(i == 53)
                {
                    s = "remote server not found";
                } else
                if(i == 1723)
                {
                    s = "remote server not accepting performance monitoring connections";
                } else
                if(i == 5)
                {
                    s = "access permissions error";
                } else
                if(i == 100)
                {
                    s = "ssh connection cannot be established";
                } else
                {
                    s = "unknown error (" + i + ")";
                }
                outputStream.println("<hr><p>SiteView was unable to connect to the remote server. <p>Reason: <b>" + s + ".</b><br><hr>");
                if(i == 5)
                {
                    s = "invalid user login or password";
                    outputStream.println("<br><p>" + s + ".</p>");
                }
                outputStream.println("</PRE><HR>");
            } else
            {
                flag = true;
            }
        } else
        {
            s = s.concat(" connection failed");
            outputStream.println("<HR><p>Could not get machine information for " + getTestMachineName() + "</p><HR>");
        }
        if(flag)
        {
            s = "connection successful";
            outputStream.println("<p><B>Connection Successful</B></P>");
        }
        jgl.Array array = getFrames();
        jgl.HashMap hashmap = findMachine(array, machine.getProperty(com.dragonflow.SiteView.Machine.pID));
        hashmap.put("_status", s);
        try
        {
            saveMachines(array, getRemoteName());
        }
        catch(java.lang.Exception exception)
        {
            java.lang.System.out.println("There was a problem updating the server status." + exception.toString());
        }
    }

    public int checkNTPermissions(com.dragonflow.SiteView.Machine machine, boolean flag)
    {
        int i = 0;
        jgl.Array array = new Array();
        i = com.dragonflow.SiteView.Platform.CheckPermissions(machine.getProperty(com.dragonflow.SiteView.Machine.pHost), getMasterConfig(), array);
        if(flag)
        {
            outputStream.println("<HR><H3>Checking Performance Counters</H3><HR>");
            java.lang.String s;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); outputStream.println(s))
            {
                s = (java.lang.String)enumeration.nextElement();
            }

            if(i != 0)
            {
                return i;
            }
            array = new Array();
            outputStream.println("<HR><H3>Checking Services</H3><HR>");
            i = com.dragonflow.SiteView.Platform.readProcessList(array, machine.getProperty(com.dragonflow.SiteView.Machine.pHost), new CounterLock(1), false);
            java.lang.String s1;
            for(java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); outputStream.println(s1))
            {
                s1 = (java.lang.String)enumeration1.nextElement();
            }

        }
        return i;
    }

    public static void main(java.lang.String args[])
    {
        (new ntmachinePage()).handleRequest();
    }

    public java.lang.String getRemoteUniqueId()
    {
        return request.getValue("ntMachineID") + "NT";
    }
}
