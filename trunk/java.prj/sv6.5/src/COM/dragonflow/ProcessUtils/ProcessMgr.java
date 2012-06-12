/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.ProcessUtils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.StringTokenizer;

import jgl.HashMap;

// Referenced classes of package COM.dragonflow.ProcessUtils:
// ProcessPool

public class ProcessMgr {

    public static final int LOG_LEVEL_NONE = 0;

    public static final int LOG_LEVEL_ERROR = 1;

    public static final int LOG_LEVEL_WARNING = 2;

    public static final int LOG_LEVEL_INFO = 3;

    public static final int LOG_LEVEL_ALL_DATA = 4;

    public static jgl.HashMap ProcessPoolMap;

    public static int processTimeout = -1;

    public static int maxProcessesPerPool = 20;

    public static int processKillTimeout = 0x1d4c0;

    public static int logLevel = 0;

    public ProcessMgr() {
    }

    public static boolean exec(java.lang.String s, jgl.Array array, int ai[], COM.dragonflow.SiteView.AtomicMonitor atomicmonitor) throws java.io.IOException {
        if (s == null || s.trim().equals("")) {
            return false;
        }
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s);
        java.lang.String s1 = stringtokenizer.nextToken();
        COM.dragonflow.ProcessUtils.ProcessPool processpool = (COM.dragonflow.ProcessUtils.ProcessPool) ProcessPoolMap.get(COM.dragonflow.ProcessUtils.ProcessMgr.getExeName(s1));
        if (processpool != null) {
            boolean flag = processpool.exec(s, array, ai, atomicmonitor);
            if (!flag) {
                flag = processpool.exec(s, array, ai, atomicmonitor);
            }
            return true;
        } else {
            return false;
        }
    }

    private static java.lang.String getExeName(java.lang.String s) {
        int i = s.lastIndexOf("\\");
        int j = s.lastIndexOf("/");
        java.lang.String s1 = s.substring(i <= j ? j + 1 : i + 1);
        int k = s1.indexOf(".");
        if (k > -1) {
            s1 = s1.substring(0, k);
        }
        return s1;
    }

    public static void stopAllProcesses() {
        for (java.util.Enumeration enumeration = ProcessPoolMap.elements(); enumeration.hasMoreElements(); ((COM.dragonflow.ProcessUtils.ProcessPool) enumeration.nextElement()).stopProcesses()) {
        }
    }

    static {
        ProcessPoolMap = new HashMap();
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_processPoolTimeout");
        if (s.length() > 0) {
            processTimeout = COM.dragonflow.Utils.TextUtils.toInt(s);
        } else {
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            processTimeout = (siteviewgroup.getSettingAsLong("_restartDelay", 24) + 1) * 3600;
        }
        java.lang.String s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_processPoolMaxPerPool");
        if (s1.length() > 0) {
            maxProcessesPerPool = COM.dragonflow.Utils.TextUtils.toInt(s1);
        }
        java.lang.String s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_processPoolKillTimeout");
        if (s2.length() > 0) {
            processKillTimeout = COM.dragonflow.Utils.TextUtils.toInt(s2);
        }
        java.lang.String s3 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_processPoolDebugLevel");
        if (s3.length() > 0) {
            logLevel = COM.dragonflow.Utils.TextUtils.toInt(s3);
        }
        ProcessPoolMap.put("perfex", new ProcessPool(COM.dragonflow.SiteView.Platform.perfexCommand("")));
    }
}
