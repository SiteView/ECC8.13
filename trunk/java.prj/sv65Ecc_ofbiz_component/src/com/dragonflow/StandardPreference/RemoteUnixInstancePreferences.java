/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StandardPreference;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.Properties.BooleanProperty;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.siteview.ecc.util.PreferencesIniValueReader;
import com.siteview.svecc.service.Config;

public class RemoteUnixInstancePreferences extends com.dragonflow.SiteView.Preferences {

    public static com.dragonflow.Properties.StringProperty pID;

    public static com.dragonflow.Properties.StringProperty pHost;

    public static com.dragonflow.Properties.StringProperty pOs;

    public static com.dragonflow.Properties.StringProperty pMethod;

    public static com.dragonflow.Properties.StringProperty pLogin;

    public static com.dragonflow.Properties.StringProperty pPassword;

    public static com.dragonflow.Properties.StringProperty pName;

    public static com.dragonflow.Properties.StringProperty pPrompt;

    public static com.dragonflow.Properties.StringProperty pLoginPrompt;

    public static com.dragonflow.Properties.StringProperty pPasswordPrompt;

    public static com.dragonflow.Properties.StringProperty pDisableCachepTrace;

    public static com.dragonflow.Properties.StringProperty pSecondaryPrompt;

    public static com.dragonflow.Properties.StringProperty pSecondaryResponse;

    public static com.dragonflow.Properties.StringProperty pInitShellEnvironment;

    public static com.dragonflow.Properties.StringProperty pTrace;

    public static com.dragonflow.Properties.StringProperty pSshClient;

    public static com.dragonflow.Properties.StringProperty pDisableCache;

    public static com.dragonflow.Properties.StringProperty pSshConnectionsLimit;

    public static com.dragonflow.Properties.StringProperty pSshAuthMethod;

    public static com.dragonflow.Properties.StringProperty pKeyFile;

    public static com.dragonflow.Properties.StringProperty pVersion2;

    public static com.dragonflow.Properties.StringProperty pSshCommand;

    public static com.dragonflow.Properties.StringProperty pSSHPort;

    public static com.dragonflow.Properties.StringProperty pStatus;

    public RemoteUnixInstancePreferences() {
    }

    public java.util.Vector test(String s) throws Exception {
        java.util.Vector vector = new Vector();
        boolean flag = false;
        boolean flag1 = false;
        boolean flag2 = false;
        String s1 = "";
        if (s.equals("short")) {
            flag1 = true;
        } else if (s.equals("detail")) {
            flag2 = true;
        }
        String s2 = getProperty(pHost);
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        if (!siteviewgroup.internalServerActive()) {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            com.dragonflow.SiteView.Machine.registerMachines(hashmap.values(getSettingName()));
        }
        boolean flag3 = false;
        String s3 = getProperty(pID);
        com.dragonflow.SiteView.Machine machine = com.dragonflow.SiteView.Machine.getMachine(com.dragonflow.SiteView.Machine.REMOTE_PREFIX + s3);
        if (machine != null) {
            com.dragonflow.Utils.RemoteCommandLine remotecommandline = com.dragonflow.SiteView.Machine.getRemoteCommandLine(machine);
            String s4 = "echo testing connection";
            vector.add("Testing connection to : " + s2);
            jgl.Array array1 = remotecommandline.test(s4, machine, flag2);
            if (remotecommandline.exitValue != 0) {
                s1 = "remote command error " + com.dragonflow.SiteView.Monitor.lookupStatus(remotecommandline.exitValue) + " (" + remotecommandline.exitValue + ")";
            }
            for (int i = 0; i < array1.size(); i ++) {
                String s7 = (String) array1.at(i);
                if (s7.indexOf("testing connection") >= 0) {
                    flag3 = true;
                    s1 = "connection successful";
                }
                vector.add(s7);
            }

        } else {
            s1 = "unable to get machine info" + s1 + " for : " + getProperty(pID);
            flag = true;
        }
        if (!flag1) {
            if (flag3) {
                vector.add("Connection Successful, attempting monitor tests...");
                boolean flag4 = false;
                String s5 = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "java" + java.io.File.separator + "bin" + java.io.File.separator + "java";
                if (com.dragonflow.SiteView.Platform.isWindows()) {
                    s5 = s5 + " -cp .";
                }
                String s6 = s5 + " com.dragonflow.SiteView.OSAdapter " + machine.getFullID();
                if (flag2) {
                    s6 = s6 + " detail";
                }
                try {
                    Process process = com.dragonflow.Utils.CommandLine.execSync(s6);
                    boolean flag5 = false;
                    java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
                    String s8;
                    while ((s8 = bufferedreader.readLine()) != null) {
                        vector.add(s8);
                    }
                    bufferedreader.close();
                    if (flag5) {
                        s1 = s1.concat(" some commands failed");
                        flag = true;
                    }
                } catch (java.io.IOException ioexception) {
                    if (!flag4) {
                        s1 = s1.concat(", " + s6 + " failed");
                        flag = true;
                    }
                }
            } else {
                flag = true;
            }
        }
        jgl.Array array = getFrames();
        jgl.HashMap hashmap1 = findMachine(array, s3);
        hashmap1.put("_status", s1);
        try {
            saveMachines(array, getSettingName());
        } catch (Exception exception) {
            System.out.println("There was a problem updating the server status." + exception.toString());
        }
        if (flag) {
            throw new Exception(s1);
        } else {
            return vector;
        }
    }

    public boolean hasMultipleValues() {
        return true;
    }

    public String getSettingName() {
        return "_remoteMachine";
    }

    public String getReturnName() {
        return pName.getName();
    }

    public String verify(com.dragonflow.Properties.StringProperty stringproperty, String s, com.dragonflow.HTTP.HTTPRequest httprequest, java.util.HashMap hashmap, java.util.HashMap hashmap1) {
        if (stringproperty.getName().equals("_name") && (s == null || s.length() == 0)) {
            s = (String) hashmap.get(pHost.getName());
            if (s.startsWith("\\\\")) {
                s = s.substring(2);
            }
        } else if (stringproperty.getName().equals("_host") && s != null && s.length() > 0 && s.startsWith("\\\\")) {
            s = s.substring(2);
        }
        return s;
    }

    public java.util.Vector getScalarValues(com.dragonflow.Properties.ScalarProperty scalarproperty, com.dragonflow.HTTP.HTTPRequest httprequest, com.dragonflow.Page.CGI cgi) throws com.dragonflow.SiteViewException.SiteViewException {
        java.util.Vector vector = new Vector();
        if (scalarproperty == pOs) {
            jgl.Array array = com.dragonflow.SiteView.Machine.getAllowedOSs();
            for (int i = 0; i < array.size(); i ++) {
                if (((String) array.at(i)).length() > 0) {
                    vector.addElement(array.at(i));
                }
            }

        } else if (scalarproperty == pMethod) {
            jgl.Array array1 = com.dragonflow.SiteView.Machine.getAllowedMethods();
            for (int j = 0; j < array1.size(); j ++) {
                if (((String) array1.at(j)).length() > 0) {
                    vector.addElement(array1.at(j));
                }
            }

        } else if (scalarproperty == pSshAuthMethod) {
            jgl.Array array2 = com.dragonflow.SiteView.Machine.getAllowedSshAuthMethods();
            for (int k = 0; k < array2.size(); k ++) {
                if (((String) array2.at(k)).length() > 0) {
                    vector.addElement(array2.at(k));
                }
            }

        } else if (scalarproperty == pSshClient) {
            jgl.Array array3 = com.dragonflow.SiteView.Machine.getAllowedSshConnectionMethods();
            for (int l = 0; l < array3.size(); l ++) {
                if (((String) array3.at(l)).length() > 0) {
                    vector.addElement(array3.at(l));
                }
            }

        }
        return vector;
    }

    private void saveMachines(jgl.Array array, String s) {
    	Config.configDel(s);
        for (int i = 0; i < array.size(); i ++) {
            jgl.HashMap hashmap1 = (jgl.HashMap) array.at(i);
            Config.configAdd(s, com.dragonflow.Utils.TextUtils.hashMapToString(hashmap1));
        }

    }
    /*
    private void saveMachines(jgl.Array array, String s) {
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        hashmap.remove(s);
        for (int i = 0; i < array.size(); i ++) {
            jgl.HashMap hashmap1 = (jgl.HashMap) array.at(i);
            hashmap.add(s, com.dragonflow.Utils.TextUtils.hashMapToString(hashmap1));
        }

        com.dragonflow.SiteView.MasterConfig.saveMasterConfig(hashmap);
    }
*/
    private jgl.HashMap findMachine(jgl.Array array, String s) {
        java.util.Enumeration enumeration = array.elements();
        jgl.HashMap hashmap = new HashMap();
        while (enumeration.hasMoreElements()) {
            hashmap = (jgl.HashMap) enumeration.nextElement();
            if (s.equals(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_id"))) {
                return hashmap;
            }
        }
        return hashmap;
    }

    public String[] updatePreferences(java.util.HashMap hashmap, String s, String s1) throws com.dragonflow.SiteViewException.SiteViewException {
        com.dragonflow.SSH.SSHManager.getInstance().deleteRemote(s1);
        return super.updatePreferences(hashmap, s, s1);
    }

    private jgl.Array getFrames() {
        jgl.Array array = new Array();
        try {
            array = readMachines(getSettingName());
        } catch (Exception exception) {
        }
        return array;
    }
/*
    private jgl.Array readMachines(String s) {
        jgl.Array array = new Array();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        String s1;
        for (java.util.Enumeration enumeration = hashmap.values(s); enumeration.hasMoreElements(); array.add(com.dragonflow.Utils.TextUtils.stringToHashMap(s1))) {
            s1 = (String) enumeration.nextElement();
            if (s1.indexOf("_id") >= 0) {
                continue;
            }
            String s2 = "_nextRemoteID";
            if (s.equals(getSettingName())) {
                s2 = "_nextRemoteID";
            }
            String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s2);
            if (s3.length() == 0) {
                s3 = "10";
            }
            s1 = s1 + " _id=" + s3;
            hashmap.put(s2, com.dragonflow.Utils.TextUtils.increment(s3));
            com.dragonflow.SiteView.MasterConfig.saveMasterConfig(hashmap);
        }

        return array;
    }
*/
    private jgl.Array readMachines(String s) {
        jgl.Array array = new Array();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        String s1;
        for (java.util.Enumeration enumeration = hashmap.values(s); enumeration.hasMoreElements(); array.add(com.dragonflow.Utils.TextUtils.stringToHashMap(s1))) {
            s1 = (String) enumeration.nextElement();
            if (s1.indexOf("_id") >= 0) {
                continue;
            }
            String s2 = "_nextRemoteID";
            if (s.equals(getSettingName())) {
                s2 = "_nextRemoteID";
            }
            String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s2);
            if (s3.length() == 0) {
                s3 = "10";
            }
            s1 = s1 + " _id=" + s3;
            Config.configPut(s2, com.dragonflow.Utils.TextUtils.increment(s3));
        }

        return array;
    }
    
    static {
        pID = new StringProperty("_id");
        pHost = new StringProperty("_host");
        //pHost.setDisplayText("Server Address", "Enter the server address of the remote server (for example, demo.siteview.com). For HTTP connections, enter the URL of the CGI (for example, http://demo.siteview.com/cgi-bin/remote.sh).");
        pHost.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_host",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_host",PreferencesIniValueReader.DESCRIPTION));
        pHost.setParameterOptions(true, 1, false);
        pOs = new ScalarProperty("_os");
        //pOs.setDisplayText("OS", "Enter the OS on the remote server");
        pOs.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_os",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_os",PreferencesIniValueReader.DESCRIPTION));
        pOs.setParameterOptions(true, 2, false);
        pMethod = new ScalarProperty("_method");
        //pMethod.setDisplayText("Connection Method", "Enter the method used to connect to the remote server.");
        pMethod.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_method",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_method",PreferencesIniValueReader.DESCRIPTION));
        pMethod.setParameterOptions(true, 3, false);
        pLogin = new StringProperty("_login");
        //pLogin.setDisplayText("Login", "Enter the login for the remote server.");
        pLogin.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_login",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_login",PreferencesIniValueReader.DESCRIPTION));
        pLogin.setParameterOptions(true, 4, false);
        pPassword = new StringProperty("_password");
        //pPassword.setDisplayText("Password", "Enter the password for logging in to the remote server.");
        pPassword.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_password",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_password",PreferencesIniValueReader.DESCRIPTION));
        pPassword.setParameterOptions(true, 5, false);
        pPassword.isPassword = true;
        pName = new StringProperty("_name");
        //pName.setDisplayText("Title", "Optional, enter the title for the remote server, the default title is the server address.");
        pName.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_name",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_name",PreferencesIniValueReader.DESCRIPTION));
        pName.setParameterOptions(true, 6, false);
        pPrompt = new StringProperty("_prompt", "#");
        //pPrompt.setDisplayText("Prompt", "For Telnet and Rlogin connection types, enter the prompt output when the system is ready to handle a command - the default is #.");
        pPrompt.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_prompt",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_prompt",PreferencesIniValueReader.DESCRIPTION));
        pPrompt.setParameterOptions(true, 7, false);
        pLoginPrompt = new StringProperty("_loginPrompt");
        //pLoginPrompt.setDisplayText("Login Prompt", "For Telnet and Rlogin connection types, enter the prompt output when the system is waiting for the login to be entered - the default is \"ogin:\"");
        pLoginPrompt.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_loginPrompt",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_loginPrompt",PreferencesIniValueReader.DESCRIPTION));
        pLoginPrompt.setParameterOptions(true, 8, false);
        pPasswordPrompt = new StringProperty("_passwordPrompt");
        //pPasswordPrompt.setDisplayText("Password Prompt", "For Telnet connection type, enter the prompt output when the system is waiting for the password to be entered - the default is \"assword:\"");
        pPasswordPrompt.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_passwordPrompt",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_passwordPrompt",PreferencesIniValueReader.DESCRIPTION));
        pPasswordPrompt.setParameterOptions(true, 9, false);
        pSecondaryPrompt = new StringProperty("_secondaryPrompt");
        //pSecondaryPrompt.setDisplayText("Secondary Prompt", "Secondary prompt. Separate by ',' for multiple prompts.");
        pSecondaryPrompt.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_secondaryPrompt",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_secondaryPrompt",PreferencesIniValueReader.DESCRIPTION));
        pSecondaryPrompt.setParameterOptions(true, 10, false);
        pSecondaryResponse = new StringProperty("_secondaryResponse");
        //pSecondaryResponse.setDisplayText("Secondary Response", "Response to the above prompt. Separate by ',' for multiple responses.");
        pSecondaryResponse.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_secondaryResponse",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_secondaryResponse",PreferencesIniValueReader.DESCRIPTION));
        pSecondaryResponse.setParameterOptions(true, 11, false);
        pInitShellEnvironment = new StringProperty("_initShellEnvironment");
        //pInitShellEnvironment.setDisplayText("Initialize Shell Environment", "Shell commands to be executed at begining of session. Seperate by ';' for multiple commands.");
        pInitShellEnvironment.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_initShellEnvironment",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_initShellEnvironment",PreferencesIniValueReader.DESCRIPTION));
        pInitShellEnvironment.setParameterOptions(true, 12, false);
        pTrace = new BooleanProperty("_trace");
        //pTrace.setDisplayText("Trace", "Check this to trace messages to and from the remote NT server in the RunMonitor.log file.");
        pTrace.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_trace",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_trace",PreferencesIniValueReader.DESCRIPTION));
        pTrace.setParameterOptions(true, 13, false);
        pSshClient = new ScalarProperty("_sshClient");
        //pSshClient.setDisplayText("SSH Connection Method", "Select the method to use to connect to the remote server.");
        pSshClient.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshClient",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshClient",PreferencesIniValueReader.DESCRIPTION));
        pSshClient.setParameterOptions(true, 20, false);
        pDisableCache = new BooleanProperty("_disableCache");
        //pDisableCache.setDisplayText("Disable Connection Caching", "Check this box to disable caching of SSH connections ");
        pDisableCache.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_disableCache",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_disableCache",PreferencesIniValueReader.DESCRIPTION));
        pDisableCache.setParameterOptions(true, 21, false);
        pSshConnectionsLimit = new StringProperty("_sshConnectionsLimit");
        //pSshConnectionsLimit.setDisplayText("Connection Limit", "Enter the maximum number of connections allowed for this remote.");
        pSshConnectionsLimit.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshConnectionsLimit",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshConnectionsLimit",PreferencesIniValueReader.DESCRIPTION));
        pSshConnectionsLimit.setParameterOptions(true, 22, false);
        pSshAuthMethod = new ScalarProperty("_sshAuthMethod");
        //pSshAuthMethod.setDisplayText("SSH Authentication Method", "Select the method to use to authenticate to the remote server (SSH connections only)");
        pSshAuthMethod.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshAuthMethod",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshAuthMethod",PreferencesIniValueReader.DESCRIPTION));
        pSshAuthMethod.setParameterOptions(true, 23, false);
        pKeyFile = new StringProperty("_keyFile");
        //pKeyFile.setDisplayText("Key File for SSH connections", "Enter the path to the file containing the private key for this SSH connection. Only valid if authentication method is \"Key File\".");
        pKeyFile.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_keyFile",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_keyFile",PreferencesIniValueReader.DESCRIPTION));
        pKeyFile.setParameterOptions(true, 24, false);
        pVersion2 = new BooleanProperty("_version2");
        //pVersion2.setDisplayText("SSH Version 2 Only", "Check this box to force SSH to only use SSH protocol version 2. ( This SSH option is only supported using the internal java libraries connection method)");
        pVersion2.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_version2",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_version2",PreferencesIniValueReader.DESCRIPTION));
        pVersion2.setParameterOptions(true, 25, false);
        pSshCommand = new StringProperty("_sshCommand");
        //pSshCommand.setDisplayText("Custom Commandline",
        //        "Enter the command for execution of external ssh client. For substituion with above options use $host$, $user$ and $password$ respectivly. This setting is for only for connections using an external process.");
        pSshCommand.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshCommand",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshCommand",PreferencesIniValueReader.DESCRIPTION));
        pSshCommand.setParameterOptions(true, 26, false);
        pSSHPort = new NumericProperty("_sshPort", "22");
        //pSSHPort.setDisplayText("SSH Port Number", "Enter the port that the SSH service is running on.");
        pSSHPort.setDisplayText(
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshPort",PreferencesIniValueReader.LABEL), 
        		PreferencesIniValueReader.getValue(RemoteUnixInstancePreferences.class.getName(), "_sshPort",PreferencesIniValueReader.DESCRIPTION));
        pSSHPort.setParameterOptions(true, 27, true);
        pStatus = new StringProperty("_status");
        pStatus.setStateOptions(1);
        pStatus.setIsParameter(false);
        com.dragonflow.Properties.StringProperty astringproperty[] = { pID, pHost, pOs, pMethod, pLogin, pPassword, pName, pPrompt, pLoginPrompt, pPasswordPrompt, pSecondaryPrompt, pSecondaryResponse, pInitShellEnvironment, pTrace, pSshClient,
                pDisableCache, pSshConnectionsLimit, pSshAuthMethod, pKeyFile, pVersion2, pSshCommand, pSSHPort, pStatus };
        com.dragonflow.StandardPreference.RemoteUnixInstancePreferences.addProperties("com.dragonflow.StandardPreference.RemoteUnixInstancePreferences", astringproperty);
    }
}
