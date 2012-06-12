 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package COM.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */
import jgl.Array;
import COM.dragonflow.SiteView.Machine;

// Referenced classes of package COM.dragonflow.Utils:
// RemoteCommandLine, TextUtils

public class SSHCommandLine extends COM.dragonflow.Utils.RemoteCommandLine
{

    public SSHCommandLine()
    {
    }

    public java.lang.String getMethodName()
    {
        return "ssh";
    }

    public java.lang.String getMethodDisplayName()
    {
        return "SSH";
    }

    public jgl.Array exec(java.lang.String s, COM.dragonflow.SiteView.Machine machine, boolean flag)
    {
        super.exec(s, machine, flag);
        java.lang.String s1 = "";
        if(s == null || s.length() == 0)
        {
            s1 = "SSH Command error: null or zero length command on machine: " + machine.getProperty(COM.dragonflow.SiteView.Machine.pName);
        }
        if(s1.length() > 0)
        {
            COM.dragonflow.Log.LogManager.log("Error", s1);
            exitValue = COM.dragonflow.SiteView.Monitor.kURLUnknownError;
            return new Array();
        }
        int i = COM.dragonflow.Properties.StringProperty.toInteger(machine.getProperty(COM.dragonflow.SiteView.Machine.pTimeout));
        if(i == 0)
        {
            i = 60000;
        } else
        {
            i *= 1000;
        }
        if(machine.getSetting("_os").equals("NT") && machine.getSetting("_method").equals("ssh"))
        {
            jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
            java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_NTSSHTimeout");
            if(s2.length() > 0)
            {
                int k = COM.dragonflow.Utils.TextUtils.toInt(s2) * 1000;
                if(k > 0)
                {
                    i = k;
                }
            }
        }
        jgl.Array array = new Array();
        exitValue = COM.dragonflow.SSH.SSHManager.getInstance().execute(this, machine, s, i, flag, progressStream, array);
        for(int j = 0; j < array.size(); j++)
        {
            java.lang.String s3 = new String(toEncoding((java.lang.String)array.at(j)));
            array.put(j, s3);
        }

        return array;
    }

    public static void main(java.lang.String args[])
    {
        java.lang.String s = args[0];
        java.lang.String s1 = args[1];
        java.lang.String s2 = args[2];
        java.lang.String s3 = args[3];
        COM.dragonflow.SiteView.Machine machine = new Machine();
        machine.setProperty(COM.dragonflow.SiteView.Machine.pHost, s);
        machine.setProperty(COM.dragonflow.SiteView.Machine.pLogin, s1);
        machine.setProperty(COM.dragonflow.SiteView.Machine.pPassword, s2);
        machine.setProperty(COM.dragonflow.SiteView.Machine.pLocalUser, s3);
        if(args.length >= 5)
        {
            machine.setProperty(COM.dragonflow.SiteView.Machine.pPrompt, args[4]);
        }
        machine.setProperty("_trace", "true");
        COM.dragonflow.Utils.SSHCommandLine sshcommandline = new SSHCommandLine();
        sshcommandline.debug = true;
        jgl.Array array = sshcommandline.exec("ps -ef", machine, false);
        for(int i = 0; i < array.size(); i++)
        {
            java.lang.System.out.println("RESULT=" + array.at(i));
        }

    }
}
