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
// UniqueNumber, TempFileManager
public abstract class MediaPlayerMonitorUtils {

    protected static final java.lang.String VugenPath;

    protected static final java.lang.String MDRVCommand = "mdrv";

    protected static final java.lang.String tempDir = com.dragonflow.Utils.TempFileManager.getTempDirPath();

    public MediaPlayerMonitorUtils() {
    }

    protected abstract java.lang.String getLogFileRoot();

    protected abstract java.lang.String getVugenScriptPath();

    public java.lang.String getNewMediaLog() {
        return tempDir + getLogFileRoot() + "_" + com.dragonflow.Utils.UniqueNumber.getInstance().getNumber() + ".log";
    }

    public java.lang.String getMediaCommand(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        java.lang.StringBuffer stringbuffer = new StringBuffer(VugenPath);
        stringbuffer.append("mdrv");
        stringbuffer.append(" -usr \"").append(getVugenScriptPath());
        stringbuffer.append("\" -no_popups \"").append(tempDir).append("\\mdrvpopup.log\"");
        stringbuffer.append(" -url \"").append(s);
        stringbuffer.append("\" -duration ").append(s1);
        stringbuffer.append(" -log \"").append(s2);
        stringbuffer.append("\" -drv_log_file \"").append(s2);
        stringbuffer.append("_\"");
        return stringbuffer.toString();
    }

    static {
        VugenPath = com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "bin" + java.io.File.separator;
    }
}
