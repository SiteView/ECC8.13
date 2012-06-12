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
// MediaPlayerMonitorUtils
public class WindowsMediaPlayerMonitorUtils extends COM.dragonflow.Utils.MediaPlayerMonitorUtils {

    private static java.lang.String VugenScriptPath = COM.dragonflow.SiteView.Platform.getRoot() + "\\media\\mms\\media.usr";

    private static java.lang.String logFileRoot = "\\WindowsMedia";

    public WindowsMediaPlayerMonitorUtils() {
    }

    protected java.lang.String getLogFileRoot() {
        return logFileRoot;
    }

    protected java.lang.String getVugenScriptPath() {
        return VugenScriptPath;
    }

}
