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
// MgCompositeGroupParts

public class MgCompositeGroup extends com.dragonflow.Health.MgCompositeGroupParts {

    java.util.Vector CompositeParts;

    java.util.Vector GroupFileHashMaps;

    java.lang.String _nameInParent;

    java.lang.String _groupInParent;

    MgCompositeGroup(java.util.Vector vector) {
        _nameInParent = null;
        _groupInParent = null;
        CompositeParts = new Vector();
        GroupFileHashMaps = vector;
        fileTitle = "Group";
        fileExtension = ".mg";
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) GroupFileHashMaps.firstElement();
        java.lang.Object obj;
        for (java.util.Iterator iterator = hashmapduplicates.keySet().iterator(); iterator.hasNext(); java.lang.System.out.println(" key: " + obj + " value: " + hashmapduplicates.get(obj))) {
            obj = iterator.next();
        }

    }

    public java.lang.String getFileName() {
        return FileName;
    }

    public void set_nameInParent(java.lang.String s) {
        _nameInParent = s;
    }

    public void set_groupInParent(java.lang.String s) {
        _groupInParent = s;
    }

    public void createHTML() {
    }

    public void printSelf(int i) {
        for (int j = 0; j < i; j ++) {
            java.lang.System.out.print('\t');
        }

        java.lang.System.out.println("Header and Frames for Group FileName: " + FileName);
        i ++;
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) GroupFileHashMaps.firstElement();
        java.lang.Object obj;
        for (java.util.Iterator iterator = hashmapduplicates.keySet().iterator(); iterator.hasNext(); java.lang.System.out.println("Level: " + i + " key: " + obj + " value: " + hashmapduplicates.get(obj))) {
            for (int k = 0; k < i; k ++) {
                java.lang.System.out.print('\t');
            }

            obj = iterator.next();
        }

        for (java.util.Iterator iterator1 = CompositeParts.iterator(); iterator1.hasNext(); ((com.dragonflow.Health.MgCompositeGroupParts) iterator1.next()).printSelf(i)) {
        }
    }

    public boolean errorCheck() {
        boolean flag = true;
        checkORPHANGroups();
        checkNextID();
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) GroupFileHashMaps.firstElement();
        checkAlerts(hashmapduplicates);
        java.lang.Object obj = check_TagEqualsValue("_dependsOn", hashmapduplicates.get("_dependsOn"), false, true);
        if (obj != null && !monitorNames.contains(obj)) {
            java.lang.String s = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "', did not find monitor that it depends on: '" + obj + "'. May have been deleted.";
            messages.add(s);
            java.lang.System.out.println(s);
        }
        java.util.Iterator iterator = CompositeParts.iterator();
        while (iterator.hasNext()) {
            if (!((com.dragonflow.Health.MgCompositeGroupParts) iterator.next()).errorCheck()) {
                flag = false;
            }
        } 
        if (messages.size() > 0) {
            flag = false;
        }
        return flag;
    }

    private void checkORPHANGroups() {
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) GroupFileHashMaps.firstElement();
        java.lang.Object obj = check_TagEqualsValue("_name", hashmapduplicates.get("_name"), false, false);
        java.lang.Object obj1 = check_TagEqualsValue("O/S File Name", FileName, false, false);
        if (parentRef != null) {
            if (_nameInParent != null) {
                java.lang.Object obj2 = check_TagEqualsValue("_name TagInParent MG file", _nameInParent, false, false);
                if (FileName.equals(obj2)) {
                    if (!obj.equals("config") && !obj.equals(obj1)) {
                        java.lang.String s = "ERROR, ORPHAN " + fileTitle + ": '" + obj1 + fileExtension + "' _name in header: '" + obj + "' must be 'config' or : '" + obj1 + "' in this situation.";
                        messages.add(s);
                        java.lang.System.out.println(s);
                    }
                } else if (!obj.equals(obj2)) {
                    java.lang.String s1 = "ERROR, ORPHAN " + fileTitle + ": '" + obj1 + fileExtension + "' _name in header: '" + obj + "' must match _name tag in parent ref: '" + obj2 + "' in this situation.";
                    messages.add(s1);
                    java.lang.System.out.println(s1);
                }
            }
            java.lang.Object obj3 = check_TagEqualsValue("_parent", hashmapduplicates.get("_parent"), false, false);
            if (obj3 instanceof java.lang.String) {
                if (!parentRef.FileName.equals(obj3)) {
                    java.lang.String s2 = "ERROR, ORPHAN " + fileTitle + ": '" + FileName + "' _parent: '" + obj3 + "' does not match parent filename: '" + parentRef.FileName + "'";
                    messages.add(s2);
                    java.lang.System.out.println(s2);
                }
            } else if (!(obj3 instanceof java.util.Vector))
                ;
            if (_groupInParent != null && !_groupInParent.equals(FileName)) {
                java.lang.String s3 = "ERROR, ORPHAN " + fileTitle + ": '" + FileName + "' _group in parent: '" + _groupInParent + "' does not match file name: '" + FileName + "'";
                messages.add(s3);
                java.lang.System.out.println(s3);
            }
        }
    }

    private void checkNextID() {
        java.util.Iterator iterator = GroupFileHashMaps.iterator();
        com.dragonflow.Properties.HashMapDuplicates hashmapduplicates = (com.dragonflow.Properties.HashMapDuplicates) iterator.next();
        java.lang.Object obj = check_TagEqualsValue("_nextID", hashmapduplicates.get("_nextID"), false, false);
        java.lang.Integer integer = null;
        checkCountingNumber("_nextID", obj);
        java.util.HashMap hashmap = new HashMap();
        Object obj1 = null;
        java.lang.Integer integer1;
        for (; iterator.hasNext(); checkForDuplicatesAndGTNextID("_id", integer1, hashmap, "_nextID", integer)) {
            com.dragonflow.Properties.HashMapDuplicates hashmapduplicates1 = (com.dragonflow.Properties.HashMapDuplicates) iterator.next();
            java.lang.Object obj2 = check_TagEqualsValue("_id", hashmapduplicates1.get("_id"), false, false);
            integer1 = null;
            checkCountingNumber("_id", obj2);
        }

    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public boolean reportToErrorLog() {
        java.util.Iterator iterator = messages.iterator();
        while (iterator.hasNext()) {
            java.lang.String s = (java.lang.String) iterator.next();
            if (s.startsWith("ERROR,")) {
                int i = s.indexOf(',');
                java.lang.String s1 = s.substring(i + 1);
                java.lang.System.out.println("error.log MgHealth: " + s1);
                com.dragonflow.Log.LogManager.log("Error", "MgHealth: " + s1);
            }
        }

        java.util.Iterator iterator1 = CompositeParts.iterator();
        while (iterator1.hasNext()) {
            ((com.dragonflow.Health.MgCompositeGroupParts) iterator1.next()).reportToErrorLog();
        }
        return true;
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    public boolean add(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts) {
        try {
            mgcompositegroupparts.setParentRef(this);
            if (mgcompositegroupparts instanceof com.dragonflow.Health.MgCompositeGroup) {
                if (!findSelfUpLine(this, ((com.dragonflow.Health.MgCompositeGroup) mgcompositegroupparts).FileName)) {
                    CompositeParts.add(mgcompositegroupparts);
                } else {
                    java.lang.String s = "ERROR, " + fileTitle + ": '" + ((com.dragonflow.Health.MgCompositeGroup) mgcompositegroupparts).getFileName() + fileExtension + "' found itself upline.";
                    messages.add(s);
                    java.lang.System.out.println(s);
                    return false;
                }
            } else {
                CompositeParts.add(mgcompositegroupparts);
                mgcompositegroupparts.addMonitorNames();
            }
        } catch (java.lang.Exception exception) {
            java.lang.String s1 = "ERROR, ERROR: adding group or monitor to MgHealth tree.";
            messages.add(s1);
            java.lang.System.out.println(s1);
        }
        return true;
    }

    public boolean findSelfUpLine(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts, java.lang.String s) {
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
