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

// Referenced classes of package com.dragonflow.Utils:
// CommandLine
public class Registry {

    public static final String HKEY_CLASSES_ROOT = "HKEY_CLASSES_ROOT";

    public static final String HKEY_CURRENT_USER = "HKEY_CURRENT_USER";

    public static final String HKEY_LOCAL_MACHINE = "HKEY_LOCAL_MACHINE";

    public static final String HKEY_USERS = "HKEY_USERS";

    public static final String HKEY_PERFORMANCE_DATA = "HKEY_PERFORMANCE_DATA";

    public static final String HKEY_CURRENT_CONFIG = "HKEY_CURRENT_CONFIG";

    public static final String HKEY_DYN_DATA = "HKEY_DYN_DATA";

    public static final String PERFEX_REG_PREFIX = "Registry value=";

    public static final int PERFEX_REG_PREFIX_LEN = "Registry value=".length();

    public static final String PERFEX_REG_CMD = " -reg ";

    public Registry() {
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @param s2
     * @return
     */
    public static String queryStringValue(String s, String s1, String s2) {
        String s3;
        com.dragonflow.Utils.CommandLine commandline;
        if (com.dragonflow.SiteView.Platform.isWindows()) {
            s3 = com.dragonflow.SiteView.Platform.perfexCommand("") + " -reg " + s + " \"" + s1 + "\"" + " \"" + s2 + "\"";
            commandline = new CommandLine();
            String s4;

            try {
                jgl.Array array = commandline.exec(s3);
                java.util.Enumeration enumeration = array.elements();
                while (enumeration.hasMoreElements()) {
                    s4 = (String) enumeration.nextElement();
                    if (s4.startsWith("Registry value=")) {
                        return s4.substring(PERFEX_REG_PREFIX_LEN);
                    }
                }
            } catch (Exception exception) {
                com.dragonflow.Log.LogManager.log("Error", "Registry.queryStringValue: Error running PERFEX_REG_CMD on root '" + s + "', path '" + s1 + "', entry '" + s2 + "'");
            }
        }
        return "";
    }

    public static void setValuesFromFile(String s) {
        try {
            com.dragonflow.Utils.CommandLine.execSync("regedit /s /i " + s);
        } catch (java.io.IOException ioexception) {
            com.dragonflow.Log.LogManager.log("Error", "Registry.setValuesFromFile: Error running regedit on: " + s);
        }
    }

}
