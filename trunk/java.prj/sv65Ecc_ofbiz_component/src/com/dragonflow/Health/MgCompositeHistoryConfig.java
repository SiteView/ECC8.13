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
import java.util.Vector;

// Referenced classes of package com.dragonflow.Health:
// MgCompositeGroupParts, MgCompositeMasterConfig

public class MgCompositeHistoryConfig extends com.dragonflow.Health.MgCompositeGroupParts {

    java.util.Vector CompositeParts;

    java.util.Vector FileHashMaps;

    com.dragonflow.Health.MgCompositeMasterConfig MgCompMasterConfig;

    MgCompositeHistoryConfig(java.util.Vector vector, com.dragonflow.Health.MgCompositeMasterConfig mgcompositemasterconfig) {
        CompositeParts = new Vector();
        MgCompMasterConfig = mgcompositemasterconfig;
        FileHashMaps = vector;
        fileTitle = "File";
        fileExtension = ".config";
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) FileHashMaps.firstElement();
        Object obj;
        for (java.util.Iterator iterator = hashmapduplicates.keySet().iterator(); iterator.hasNext(); System.out.println(" key: " + obj + " value: " + hashmapduplicates.get(obj))) {
            obj = iterator.next();
        }

    }

    public String getFileName() {
        return FileName;
    }

    public void createHTML() {
    }

    public void printSelf(int i) {
        System.out.println("Frames for history.config: " + FileName);
        for (java.util.Iterator iterator = FileHashMaps.iterator(); iterator.hasNext(); System.out.println("#")) {
            com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) iterator.next();
            Object obj;
            for (java.util.Iterator iterator1 = hashmapduplicates.keySet().iterator(); iterator1.hasNext(); System.out.println(" key: " + obj + " value: " + hashmapduplicates.get(obj))) {
                obj = iterator1.next();
            }

        }

    }

    public boolean errorCheck() {
        boolean flag = true;
        checkNextID();
        if (messages.size() > 0) {
            flag = false;
        }
        return flag;
    }

    private void checkNextID() {
        java.util.Iterator iterator = FileHashMaps.iterator();
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) iterator.next();
        Integer integer = null;
        if (MgCompMasterConfig != null) {
            integer = MgCompMasterConfig.getNextReportID();
        }
        java.util.HashMap hashmap = new HashMap();
        Object obj = null;
        while (iterator.hasNext()) {
            com.dragonflow.Properties.HashMapDuplicates hashmapduplicates1 = (com.dragonflow.Properties.HashMapDuplicates) iterator.next();
            Object obj1 = check_TagEqualsValue("id", hashmapduplicates1.get("id"), false, false);
            Integer integer1 = null;
            checkCountingNumber("_id", obj1);
            checkForDuplicatesAndGTNextID("id", integer1, hashmap, "_nextReportID(master.config)", integer);
            Object obj2 = check_TagEqualsValue("monitors", hashmapduplicates1.get("monitors"), true, true);
            if (fileNames.get(obj2) == null && !monitorNames.contains(obj2)) {
                String s = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "', did not find monitor or group that it reports on: '" + obj2 + "'. May have been deleted.";
                messages.add(s);
                System.out.println(s);
            }
        } 
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
        for (java.util.Iterator iterator1 = CompositeParts.iterator(); iterator1.hasNext(); ((com.dragonflow.Health.MgCompositeGroupParts) iterator1.next()).reportToErrorLog()) {
        }
        return true;
    }

    public boolean add(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts) {
        return true;
    }

    public boolean findSelfUpLine(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts, String s) {
        if (!mgcompositegroupparts.FileName.equals(s)) {
            if (mgcompositegroupparts.parentRef == null) {
                return false;
            }
            return findSelfUpLine(mgcompositegroupparts.parentRef, s);
        } else {
            return true;
        }
    }

    public boolean addMonitorNames() {
        return true;
    }
}
