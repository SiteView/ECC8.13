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

import COM.dragonflow.Properties.ScheduleProperty;
import COM.dragonflow.Properties.StringProperty;
import COM.dragonflow.SiteViewException.SiteViewParameterException;

public class ScheduleInstancePreferences extends COM.dragonflow.SiteView.Preferences {

    public static final java.lang.String dayLetters[] = { "U", "M", "T", "W", "R", "F", "S" };

    public static java.lang.String ADDITINAL_SCHEDULE_SETTING_KEY = "_additionalSchedule";

    private java.lang.String settingName;

    protected java.lang.String days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    public static COM.dragonflow.Properties.StringProperty pName;

    public static COM.dragonflow.Properties.StringProperty pSchedule;

    public ScheduleInstancePreferences() {
        settingName = ADDITINAL_SCHEDULE_SETTING_KEY;
    }

    public boolean hasMultipleValues() {
        return true;
    }

    public java.lang.String getSettingName() {
        return settingName;
    }

    public java.lang.String getReturnName() {
        return pName.getName();
    }

    public java.lang.String[] updatePreferences(java.util.HashMap hashmap, java.lang.String s, java.lang.String s1) throws COM.dragonflow.SiteViewException.SiteViewException {
        java.lang.String as[] = super.updatePreferences(hashmap, s, s1);
        COM.dragonflow.SiteView.ScheduleManager schedulemanager = COM.dragonflow.SiteView.ScheduleManager.getInstance();
        java.lang.String s2 = (java.lang.String) hashmap.get("_schedule");
        schedulemanager.updateSchedule(as[1], s2);
        return as;
    }

    public void deletePreferences(java.lang.String s, java.lang.String s1) throws COM.dragonflow.SiteViewException.SiteViewException {
        COM.dragonflow.SiteView.ScheduleManager schedulemanager = COM.dragonflow.SiteView.ScheduleManager.getInstance();
        if (!schedulemanager.hasMonitorReferences(s1)) {
            super.deletePreferences(s, s1);
        } else {
            throw new SiteViewParameterException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_PREFERENCE_MONITOR_REF_SCHEDULE);
        }
    }

    protected java.lang.String appendSchedule(java.lang.String s, java.lang.String s1) {
        if (s != null) {
            if (s1.length() > 0 && s.length() > 0) {
                s1 = s1 + ",";
            }
            s1 = s1 + s;
        }
        return s1;
    }

    protected java.lang.String getDayLetter(java.lang.String s) {
        java.lang.String s1 = "";
        if (s != null) {
            if (s.indexOf(days[0]) != -1) {
                return dayLetters[0];
            }
            if (s.indexOf(days[1]) != -1) {
                return dayLetters[1];
            }
            if (s.indexOf(days[2]) != -1) {
                return dayLetters[2];
            }
            if (s.indexOf(days[3]) != -1) {
                return dayLetters[3];
            }
            if (s.indexOf(days[4]) != -1) {
                return dayLetters[4];
            }
            if (s.indexOf(days[5]) != -1) {
                return dayLetters[5];
            }
            if (s.indexOf(days[6]) != -1) {
                return dayLetters[6];
            }
        }
        return s1;
    }

    static {
        pName = new StringProperty("_name");
        pName.setDisplayText("Setting Name", "Enter the name of the e-mail settings used to specify e-mail targets when adding alerts.");
        pName.setParameterOptions(true, 8, false);
        pSchedule = new ScheduleProperty("_schedule", "");
        pSchedule.setDisplayText("Schedule", "");
        pSchedule.setParameterOptions(true, 9, false);
        COM.dragonflow.Properties.StringProperty astringproperty[] = { pName, pSchedule };
        COM.dragonflow.StandardPreference.ScheduleInstancePreferences.addProperties("COM.dragonflow.StandardPreference.ScheduleInstancePreferences", astringproperty);
    }
}
