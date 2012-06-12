/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Health;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.Vector;

import com.dragonflow.StandardPreference.RemoteNTInstancePreferences;
import com.dragonflow.StandardPreference.RemoteUnixInstancePreferences;

// Referenced classes of package com.dragonflow.Health:
// MgCompositeGroupParts

public class MgCompositeMasterConfig extends com.dragonflow.Health.MgCompositeGroupParts {

    com.dragonflow.Properties.HashMapDuplicates myHm;

    Integer nextReportIDInt;

    MgCompositeMasterConfig(com.dragonflow.Properties.HashMapDuplicates hashmapduplicates) {
        myHm = hashmapduplicates;
        fileTitle = "File";
        fileExtension = ".config";
    }

    public void createHTML() {
    }

    public Integer getNextReportID() {
        return nextReportIDInt;
    }

    public void printSelf(int i) {
        System.out.println("FILE: master.config: ");
        Object obj;
        for (java.util.Iterator iterator = myHm.keySet().iterator(); iterator.hasNext(); System.out.println("Level: " + i + " key: " + obj + " value: " + myHm.get(obj))) {
            for (int j = 0; j < i; j ++) {
                System.out.print('\t');
            }

            obj = iterator.next();
        }

    }
    private static String settingNameUnix = new RemoteUnixInstancePreferences().getSettingName();
    private static String settingNameNT = new RemoteUnixInstancePreferences().getSettingName();

    public boolean errorCheck() {
        boolean flag = true;
        Object obj = check_TagEqualsValue("_nextConditionID", myHm.get("_nextConditionID"), false, false);
        Object obj1 = check_TagEqualsValue("_nextNTRemoteID", myHm.get("_nextNTRemoteID"), false, false);
        Integer integer = checkCountingNumber("_nextNTRemoteID", obj1);
        Object obj2 = check_TagEqualsValue("_nextRemoteID", myHm.get("_nextRemoteID"), false, false);
        Integer integer1 = checkCountingNumber("_nextRemoteID", obj2);
        Object obj3 = check_TagEqualsValue("_nextReportID", myHm.get("_nextReportID"), false, false);
        nextReportIDInt = checkCountingNumber("_nextReportID", obj3);
        checkAlerts(myHm);
        Object obj4 = check_TagEqualsValue(settingNameUnix, myHm.get(settingNameUnix), true, true);
        if (obj4 != null) {
            java.util.Vector vector = new Vector();
            if (obj4 instanceof String) {
                vector.add(obj4);
            } else if (obj4 instanceof java.util.Vector) {
                vector = (java.util.Vector) obj4;
            }
            java.util.Iterator iterator = vector.iterator();
            java.util.HashMap hashmap = new HashMap();
            while (iterator.hasNext()) {
                String s = (String) iterator.next();
                java.util.StringTokenizer stringtokenizer = new StringTokenizer(s);
                while (stringtokenizer.hasMoreTokens()) {
                    String s2 = stringtokenizer.nextToken();
                    int i = s2.indexOf("_id=");
                    if (i == 0) {
                        String s4 = s2.substring(4);
                        Integer integer2 = checkCountingNumber("_id=", s4);
                        checkForDuplicatesAndGTNextID("_id=", integer2, hashmap, "_nextRemoteID", integer1);
                        if (integer2 != null) {
                            remoteMachines.add(integer2);
                        }
                    }
                }
            }
            Object obj9 = check_TagEqualsValue(settingNameNT, myHm.get(settingNameNT), true, true);
            if (obj9 != null) {
                vector.clear();
                if (obj4 instanceof String) {
                    vector.add(obj4);
                } else if (obj4 instanceof java.util.Vector) {
                    vector = (java.util.Vector) obj4;
                }
                java.util.Iterator iterator1 = vector.iterator();
                Object obj6 = null;
                Object obj7 = null;
                Object obj8 = null;
                hashmap.clear();
                while (iterator1.hasNext()) {
                    String s1 = (String) iterator1.next();
                    java.util.StringTokenizer stringtokenizer1 = new StringTokenizer(s1);
                    while (stringtokenizer1.hasMoreTokens()) {
                        String s3 = stringtokenizer1.nextToken();
                        int j = s3.indexOf("_id=");
                        if (j == 0) {
                            String s5 = s3.substring(4);
                            Integer integer3 = checkCountingNumber("_id=", s5);
                            checkForDuplicatesAndGTNextID("_id=", integer3, hashmap, "_nextRemoteID", integer1);
                            if (integer3 != null) {
                                remoteNTMachines.add(integer3);
                            }
                        }
                    }
                }
            }
        }
        Object obj5 = check_TagEqualsValue(settingNameNT, myHm.get(settingNameNT), true, true);
        if (messages.size() > 0) {
            flag = false;
        }
        return flag;
    }

    public boolean reportToErrorLog() {
        java.util.Iterator iterator = messages.iterator();
        while (iterator.hasNext()) {
            String s = (String) iterator.next();
            if (s.startsWith("ERROR,")) {
                int i = s.indexOf(',');
                String s1 = s.substring(i + 1);
                System.out.println("error.log MgHealth: " + s1);
                com.dragonflow.Log.LogManager.log("Error", "MgHealth: " + s1);
            }
        } 
        return true;
    }

    public boolean addMonitorNames() {
        return true;
    }
}
