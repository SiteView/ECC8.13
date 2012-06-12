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

// Referenced classes of package COM.dragonflow.Utils:
// CommandLine
public class Registry {

    public static final java.lang.String HKEY_CLASSES_ROOT = "HKEY_CLASSES_ROOT";

    public static final java.lang.String HKEY_CURRENT_USER = "HKEY_CURRENT_USER";

    public static final java.lang.String HKEY_LOCAL_MACHINE = "HKEY_LOCAL_MACHINE";

    public static final java.lang.String HKEY_USERS = "HKEY_USERS";

    public static final java.lang.String HKEY_PERFORMANCE_DATA = "HKEY_PERFORMANCE_DATA";

    public static final java.lang.String HKEY_CURRENT_CONFIG = "HKEY_CURRENT_CONFIG";

    public static final java.lang.String HKEY_DYN_DATA = "HKEY_DYN_DATA";

    public static final java.lang.String PERFEX_REG_PREFIX = "Registry value=";

    public static final int PERFEX_REG_PREFIX_LEN = "Registry value=".length();

    public static final java.lang.String PERFEX_REG_CMD = " -reg ";

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
    public static java.lang.String queryStringValue(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        java.lang.String s3;
        COM.dragonflow.Utils.CommandLine commandline;
        if (COM.dragonflow.SiteView.Platform.isWindows()) {
            s3 = COM.dragonflow.SiteView.Platform.perfexCommand("") + " -reg " + s + " \"" + s1 + "\"" + " \"" + s2 + "\"";
            commandline = new CommandLine();
            java.lang.String s4;

            try {
                jgl.Array array = commandline.exec(s3);
                java.util.Enumeration enumeration = array.elements();
                while (enumeration.hasMoreElements()) {
                    s4 = (java.lang.String) enumeration.nextElement();
                    if (s4.startsWith("Registry value=")) {
                        return s4.substring(PERFEX_REG_PREFIX_LEN);
                    }
                }
            } catch (java.lang.Exception exception) {
                COM.dragonflow.Log.LogManager.log("Error", "Registry.queryStringValue: Error running PERFEX_REG_CMD on root '" + s + "', path '" + s1 + "', entry '" + s2 + "'");
            }
        }
        return "";
    }

    public static void setValuesFromFile(java.lang.String s) {
        try {
            COM.dragonflow.Utils.CommandLine.execSync("regedit /s /i " + s);
        } catch (java.io.IOException ioexception) {
            COM.dragonflow.Log.LogManager.log("Error", "Registry.setValuesFromFile: Error running regedit on: " + s);
        }
    }

}
