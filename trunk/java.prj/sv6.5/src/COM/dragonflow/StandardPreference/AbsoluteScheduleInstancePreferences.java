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

import java.util.HashMap;
import java.util.TreeMap;
import java.util.Vector;

import COM.dragonflow.HTTP.HTTPRequest;
import COM.dragonflow.Properties.StringProperty;
import COM.dragonflow.SiteViewException.SiteViewException;
import COM.dragonflow.SiteViewException.SiteViewOperationalException;

// Referenced classes of package COM.dragonflow.StandardPreference:
// ScheduleInstancePreferences

public class AbsoluteScheduleInstancePreferences extends COM.dragonflow.StandardPreference.ScheduleInstancePreferences {

    public static final int SUNDAY = 0;

    public static final int MONDAY = 1;

    public static final int TUESDAY = 2;

    public static final int WEDNESDAY = 3;

    public static final int THURSDAY = 4;

    public static final int FRIDAY = 5;

    public static final int SATURDAY = 6;

    public static COM.dragonflow.Properties.StringProperty pAtSunday;

    public static COM.dragonflow.Properties.StringProperty pAtMonday;

    public static COM.dragonflow.Properties.StringProperty pAtTuesday;

    public static COM.dragonflow.Properties.StringProperty pAtWednesday;

    public static COM.dragonflow.Properties.StringProperty pAtThursday;

    public static COM.dragonflow.Properties.StringProperty pAtFriday;

    public static COM.dragonflow.Properties.StringProperty pAtSaturday;

    public AbsoluteScheduleInstancePreferences() {
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public java.util.Vector getPreferenceProperties(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, int i) throws COM.dragonflow.SiteViewException.SiteViewException {
        java.util.Vector vector = new Vector();
        java.util.Vector vector1;

        try {
            vector1 = new Vector();
            java.lang.String s4 = "COM.dragonflow.StandardPreference." + s;
            java.lang.Class class1 = java.lang.Class.forName(s4);
            COM.dragonflow.SiteView.Preferences preferences = (COM.dragonflow.SiteView.Preferences) class1.newInstance();
            jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
            if (hashmap == null) {
                throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_RETRIEVE_MASTER_SETTINGS);
            }
            Object obj1 = null;
            Object obj2 = null;
            if (s1 != null && s1.length() > 0) {
                java.util.Enumeration enumeration = hashmap.values(s1);
                while (enumeration.hasMoreElements()) {
                    java.util.HashMap hashmap1 = new HashMap();
                    java.lang.String s5 = "";
                    boolean flag = false;
                    s5 = (java.lang.String) enumeration.nextElement();
                    java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s5);
                    for (int l = 0; l < as.length; l ++) {
                        int j1 = as[l].indexOf('=');
                        if (j1 <= 0) {
                            continue;
                        }
                        java.lang.String s8 = as[l].substring(0, j1);
                        if (!s8.equals("_schedule")) {
                            continue;
                        }
                        java.lang.String s10 = as[l].substring(j1 + 1).replace('_', ' ');
                        if (s10.startsWith("*")) {
                            flag = true;
                        }
                    }

                    if (!flag) {
                        continue;
                    }
                    for (int i1 = 0; i1 < as.length; i1 ++) {
                        int k1 = as[i1].indexOf('=');
                        if (k1 <= 0) {
                            continue;
                        }
                        java.lang.String s9 = as[i1].substring(0, k1);
                        java.lang.String s11 = as[i1].substring(k1 + 1).replace('_', ' ');
                        if (s9 != null && !s9.equals("_schedule")) {
                            hashmap1.put(s9, s11);
                        } else {
                            hashmap1 = synthesizePropertiesForSchedule(hashmap1, s11);
                        }
                    }

                    if (i == COM.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL) {
                        hashmap1.put("_class", s);
                    }
                    if (s3 != null && s3 != "") {
                        java.lang.String s7 = (java.lang.String) hashmap1.get(s2);
                        if (!s3.equals(s7)) {
                            continue;
                        }
                        vector.add(hashmap1);
                        break;
                    }
                    vector.add(hashmap1);
                }
            } else {
                java.util.HashMap hashmap2 = new HashMap();
                jgl.Array array = preferences.getProperties();
                for (int k = 0; k < array.size(); k ++) {
                    java.lang.String s6 = (java.lang.String) hashmap.get(((COM.dragonflow.Properties.StringProperty) array.at(k)).getName());
                    if (s6 == null) {
                        s6 = "";
                    }
                    hashmap2.put(((COM.dragonflow.Properties.StringProperty) array.at(k)).getName(), s6);
                }

                if (i == COM.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL) {
                    hashmap2.put("_class", s);
                }
                vector.add(hashmap2);
            }
            if (vector != null) {
                for (int j = 0; j < vector.size(); j ++) {
                    java.util.HashMap hashmap3 = new HashMap();
                    COM.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
                    java.util.HashMap hashmap4 = (java.util.HashMap) vector.get(j);
                    java.util.Set set = hashmap4.keySet();
                    java.util.Iterator iterator = set.iterator();
                    while (iterator.hasNext()) {
                        java.lang.String s12 = (java.lang.String) iterator.next();
                        java.lang.String s13 = (java.lang.String) hashmap4.get(s12);
                        hashmap4.put(s12, s13);
                        COM.dragonflow.Properties.StringProperty stringproperty = preferences.getPropertyObject(s12);
                        if (stringproperty != null) {
                            java.lang.String s14 = verify((COM.dragonflow.Properties.StringProperty) stringproperty, s13, httprequest, hashmap4, hashmap3);
                            if (s14 != null && s14 != "") {
                                hashmap4.put(s12, s14);
                            }
                        }
                    }
                    vector1.add(hashmap4);
                }

                return vector1;
            }
        } catch (SiteViewException e) {
            e.fillInStackTrace();
            throw e;
        } catch (Exception e) {
            throw new SiteViewOperationalException(COM.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_PREFERENCE_EXCEPTION, new java.lang.String[] { "AbsoluteScheduleInstancePreferences", "getPreferenceProperties" }, 0L, e.getMessage());
        }
        return vector;
    }

    protected java.lang.String singleAbsoluteSchedule(java.lang.String s, java.lang.String s1, java.util.HashMap hashmap) {
        java.lang.StringBuffer stringbuffer = new StringBuffer("");
        java.lang.StringBuffer stringbuffer1 = new StringBuffer("");
        if (s1 != null) {
            s1 = COM.dragonflow.Utils.TextUtils.removeChars(s1, " ");
            s1 = s1.replace(',', COM.dragonflow.Properties.ScheduleProperty.absolute_trigger_separator);
            boolean flag = false;
            if (s1.length() != 0) {
                boolean flag1 = false;
                java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s1, COM.dragonflow.Properties.ScheduleProperty.absolute_trigger_separator_str);
                for (int i = 0; i < as.length; i ++) {
                    as[i] = COM.dragonflow.Properties.ScheduleProperty.validateTime(as[i], "00:00", stringbuffer1);
                    if (stringbuffer1.length() > 0) {
                        hashmap.put("at" + days[COM.dragonflow.Utils.TextUtils.dayLetterToNumber(s)], stringbuffer1.toString());
                        return stringbuffer.toString();
                    }
                    flag1 = true;
                }

                if (flag1) {
                    if (flag) {
                        stringbuffer.append(COM.dragonflow.Properties.ScheduleProperty.schedule_day_separator);
                    }
                    flag = true;
                    java.lang.String s2 = getDayLetter(s);
                    stringbuffer.append(s2);
                    int j;
                    for (j = 0; j < as.length - 1; j ++) {
                        stringbuffer.append(as[j]);
                        stringbuffer.append(COM.dragonflow.Properties.ScheduleProperty.absolute_trigger_separator);
                    }

                    stringbuffer.append(as[j]);
                }
            }
        }
        return stringbuffer.toString();
    }

    public java.util.HashMap synthesizePropertiesForSchedule(java.util.HashMap hashmap, java.lang.String s) {
        java.lang.String as[] = COM.dragonflow.Utils.TextUtils.split(s, COM.dragonflow.Properties.ScheduleProperty.schedule_day_separator);
        for (int i = 0; i < days.length; i ++) {
            boolean flag = false;
            for (int j = 0; j < as.length; j ++) {
                if (as[j].startsWith(COM.dragonflow.Properties.ScheduleProperty.absolute_prefix + dayLetters[i])) {
                    if (as[j].length() > 2) {
                        java.lang.String s1 = as[j].substring(2);
                        s1 = s1.replaceAll(COM.dragonflow.Properties.ScheduleProperty.absolute_trigger_separator_str, COM.dragonflow.Properties.ScheduleProperty.schedule_day_separator);
                        hashmap.put("at" + days[i], s1);
                        flag = true;
                    }
                    continue;
                }
                if (as[j].startsWith(dayLetters[i]) && as[j].length() > 2) {
                    java.lang.String s2 = as[j].substring(1);
                    s2 = s2.replaceAll(COM.dragonflow.Properties.ScheduleProperty.absolute_trigger_separator_str, COM.dragonflow.Properties.ScheduleProperty.schedule_day_separator);
                    hashmap.put("at" + days[i], s2);
                    flag = true;
                }
            }

            if (!flag) {
                hashmap.put("at" + days[i], "");
            }
        }

        return hashmap;
    }

    public java.util.HashMap validateProperties(java.util.HashMap hashmap, jgl.Array array, java.util.HashMap hashmap1) throws java.lang.Exception {
        java.util.Set set = hashmap.keySet();
        java.util.Iterator iterator = set.iterator();
        java.util.HashMap hashmap2 = new HashMap();
        java.lang.String s = "";
        java.util.TreeMap treemap = new TreeMap();
        while (iterator.hasNext()) {
            java.lang.String s1 = (java.lang.String) iterator.next();
            java.lang.String s2 = (java.lang.String) hashmap.get(s1);
            if (s1.matches("at.*")) {
                int i = COM.dragonflow.Utils.TextUtils.dayLetterToNumber(getDayLetter(s1));
                if (i >= 0) {
                    s2 = singleAbsoluteSchedule(s1, s2, hashmap1);
                    treemap.put(new Integer(i), s2);
                }
            } else {
                hashmap2.put(s1, s2);
            }
        } 
        java.util.Collection collection = treemap.values();
        for (java.util.Iterator iterator1 = collection.iterator(); iterator1.hasNext();) {
            s = appendSchedule((java.lang.String) iterator1.next(), s);
        }

        s = COM.dragonflow.Properties.ScheduleProperty.absolute_prefix + s;
        hashmap2.put("_schedule", s);
        return super.validateProperties(hashmap2, array, hashmap1);
    }

    static {
        pAtSunday = new StringProperty("atSunday");
        pAtSunday.setDisplayText("at", "");
        pAtSunday.setParameterOptions(true, 1, false);
        pAtMonday = new StringProperty("atMonday");
        pAtMonday.setDisplayText("at", "");
        pAtMonday.setParameterOptions(true, 2, false);
        pAtTuesday = new StringProperty("atTuesday");
        pAtTuesday.setDisplayText("at", "");
        pAtTuesday.setParameterOptions(true, 3, false);
        pAtWednesday = new StringProperty("atWednesday");
        pAtWednesday.setDisplayText("at", "");
        pAtWednesday.setParameterOptions(true, 4, false);
        pAtThursday = new StringProperty("atThursday");
        pAtThursday.setDisplayText("at", "");
        pAtThursday.setParameterOptions(true, 5, false);
        pAtFriday = new StringProperty("atFriday");
        pAtFriday.setDisplayText("at", "");
        pAtFriday.setParameterOptions(true, 6, false);
        pAtSaturday = new StringProperty("atSaturday");
        pAtSaturday.setDisplayText("at", "");
        pAtSaturday.setParameterOptions(true, 7, false);
        COM.dragonflow.Properties.StringProperty astringproperty[] = { pAtSunday, pAtMonday, pAtTuesday, pAtWednesday, pAtThursday, pAtFriday, pAtSaturday };
        COM.dragonflow.StandardPreference.AbsoluteScheduleInstancePreferences.addProperties("COM.dragonflow.StandardPreference.AbsoluteScheduleInstancePreferences", astringproperty);
    }
}
