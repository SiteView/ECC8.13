/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.StandardPreference;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import COM.dragonflow.Properties.NumericProperty;
import COM.dragonflow.Properties.StringProperty;

public class LogDefaultPreferences extends COM.dragonflow.SiteView.Preferences {

    public static COM.dragonflow.Properties.StringProperty pDailyLogKeepDays;

    public static COM.dragonflow.Properties.StringProperty pDailyLogTotalLimit;

    public static COM.dragonflow.Properties.StringProperty pLogJdbcURLSiteViewLog;

    public static COM.dragonflow.Properties.StringProperty pLogJdbcDriverSiteView;

    public static COM.dragonflow.Properties.StringProperty pLogJdbcURLBackupSiteViewLog;

    public static COM.dragonflow.Properties.StringProperty pLogJdbcUserSiteViewLog;

    public static COM.dragonflow.Properties.StringProperty pLogJdbcPasswordSiteViewLog;

    public LogDefaultPreferences() {
    }

    public java.lang.String verify(COM.dragonflow.Properties.StringProperty stringproperty, java.lang.String s, COM.dragonflow.HTTP.HTTPRequest httprequest, java.util.HashMap hashmap, java.util.HashMap hashmap1) {
        if (stringproperty == pDailyLogKeepDays || stringproperty == pDailyLogTotalLimit && !s.equals("")) {
            try {
                new Integer(s.trim());
            } catch (java.lang.NumberFormatException numberformatexception) {
                hashmap1.put(stringproperty, "The entry is not a valid number.");
            }
        } else if (stringproperty == pLogJdbcPasswordSiteViewLog) {
            s = COM.dragonflow.Utils.TextUtils.obscure(s);
        }
        return s;
    }

    static {
        pDailyLogKeepDays = new NumericProperty("_dailyLogKeepDays", "40");
        pDailyLogKeepDays.setDisplayText("Daily Logs To Keep", "Enter the number of days of monitoring data to keep. Once a day, SiteView deletes any logs older than the specified number of days.");
        pDailyLogKeepDays.setParameterOptions(true, 1, false);
        pDailyLogTotalLimit = new NumericProperty("_dailyLogTotalLimit");
        pDailyLogTotalLimit.setDisplayText("Maximum Size of Logs",
                "Optional, enter the maximum size, in bytes, allowed for all monitoring logs. Once a day, SiteView checks the total size of all monitoring logs and removes any old logs that are over the maximum size. If blank, the size is not checked.");
        pDailyLogTotalLimit.setParameterOptions(true, 2, false);
        pLogJdbcURLSiteViewLog = new StringProperty("_logJdbcURLSiteViewLog");
        pLogJdbcURLSiteViewLog.setDisplayText("Database Connection URL", "Enter the URL to the database connection (for example, if the ODBC connection is called SiteViewLog, the URL would be jdbc:odbc:SiteViewLog).");
        pLogJdbcURLSiteViewLog.setParameterOptions(true, 3, false);
        pLogJdbcDriverSiteView = new StringProperty("_logJdbcDriverSiteView");
        pLogJdbcDriverSiteView.setDisplayText("Database Driver", "Enter the driver used to connect to the database.");
        pLogJdbcDriverSiteView.setParameterOptions(true, 4, false);
        pLogJdbcUserSiteViewLog = new StringProperty("_logJdbcUserSiteViewLog");
        pLogJdbcUserSiteViewLog.setDisplayText("Database Username", "Enter the username used to connect to the database.");
        pLogJdbcUserSiteViewLog.setParameterOptions(true, 5, false);
        pLogJdbcPasswordSiteViewLog = new StringProperty("_logJdbcPasswordSiteViewLog");
        pLogJdbcPasswordSiteViewLog.setDisplayText("Database Password", "Enter the password used to connect to the database.");
        pLogJdbcPasswordSiteViewLog.setParameterOptions(true, 6, false);
        pLogJdbcPasswordSiteViewLog.isPassword = true;
        pLogJdbcURLBackupSiteViewLog = new StringProperty("_logJdbcURLBackupSiteViewLog");
        pLogJdbcURLBackupSiteViewLog.setDisplayText("Backup Database Connection URL", "Optional, enter the database URL to use if the main database connection is not available.");
        pLogJdbcURLBackupSiteViewLog.setParameterOptions(true, 7, false);
        COM.dragonflow.Properties.StringProperty astringproperty[] = { pDailyLogKeepDays, pDailyLogTotalLimit, pLogJdbcURLSiteViewLog, pLogJdbcDriverSiteView, pLogJdbcURLBackupSiteViewLog, pLogJdbcUserSiteViewLog, pLogJdbcPasswordSiteViewLog };
        COM.dragonflow.StandardPreference.LogDefaultPreferences.addProperties("COM.dragonflow.StandardPreference.LogDefaultPreferences", astringproperty);
    }
}
