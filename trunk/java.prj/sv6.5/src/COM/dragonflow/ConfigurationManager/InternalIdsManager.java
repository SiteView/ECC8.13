/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.ConfigurationManager;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Vector;

// Referenced classes of package COM.dragonflow.ConfigurationManager:
// CfgChangesSink

public class InternalIdsManager {

    private int nextSiteViewId;

    java.lang.String settingsFilePath;

    static COM.dragonflow.ConfigurationManager.InternalIdsManager manager = null;

    private java.util.Vector cfgChangesSinks;

    java.lang.String moveDestination;

    java.lang.Object moveDestinationSync;

    public InternalIdsManager() {
        nextSiteViewId = 10000;
        settingsFilePath = null;
        cfgChangesSinks = new Vector();
        moveDestination = null;
        moveDestinationSync = new Object();
        settingsFilePath = COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "cache" + java.io.File.separator + "persistent" + java.io.File.separator + "ConfigurationManager" + java.io.File.separator + "internalIdsManager";
        if ((new File(settingsFilePath)).exists()) {
            try {
                java.io.ObjectInputStream objectinputstream = new ObjectInputStream(new FileInputStream(settingsFilePath));
                nextSiteViewId = objectinputstream.readInt();
            } catch (java.io.IOException ioexception) {
                COM.dragonflow.Log.LogManager.logException(ioexception);
            }
        }
        detectNextInternalId();
    }

    public static COM.dragonflow.ConfigurationManager.InternalIdsManager getInstance() {
        if (manager == null) {
            manager = new InternalIdsManager();
        }
        return manager;
    }

    public synchronized void registerCfgChangesSink(COM.dragonflow.ConfigurationManager.CfgChangesSink cfgchangessink) {
        cfgChangesSinks.add(cfgchangessink);
    }

    public synchronized void unregisterCfgChangesSink(COM.dragonflow.ConfigurationManager.CfgChangesSink cfgchangessink) {
        cfgChangesSinks.remove(cfgchangessink);
    }

    public synchronized int getNextSiteviewId() {
        nextSiteViewId ++;
        return nextSiteViewId - 1;
    }

    public java.util.Collection validateInternalIds() {
        java.util.Vector vector = new Vector();
        java.util.Vector vector1 = new Vector();
        java.util.Vector vector2 = new Vector();
        java.util.Vector vector3 = new Vector();
        java.util.HashMap hashmap = new HashMap();
        java.util.HashSet hashset = new HashSet();
        COM.dragonflow.SiteView.ConfigurationChanger.getCurrentConfiguration(vector, vector1, vector2, hashset);
        vector3.addAll(vector1);
        vector3.addAll(vector2);
        groupByInternalIds(vector3, hashmap, hashset);
        java.util.Collection collection = hashmap.values();
        resolveDuplicateIds(collection, hashset);
        COM.dragonflow.Api.Alert.getInstance().updateAlertMap(vector2);
        if (hashset.size() > 0) {
            saveSettings();
        }
        return hashset;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param collection
     * @param hashset
     */
    private void resolveDuplicateIds(java.util.Collection collection, java.util.HashSet hashset) {
        java.util.Iterator iterator = collection.iterator();
        while (iterator.hasNext()) {
            java.util.Vector vector = (java.util.Vector) iterator.next();
            if (vector.size() > 1) {
                int i = getValidInternalIdIndex(vector);
                for (int j = 0; j < vector.size(); j ++) {
                    COM.dragonflow.SiteView.IObjectWithUniqueId iobjectwithuniqueid = (COM.dragonflow.SiteView.IObjectWithUniqueId) vector.elementAt(j);
                    if (j != i) {
//                        if (COM.dragonflow.TopazIntegration.TopazFileLogger.getLogger().isLoggable(java.util.logging.Level.FINE)) {
//                            COM.dragonflow.TopazIntegration.TopazFileLogger.getLogger().fine("Invalid internal ID detected, assigning new ID to monitor: " + iobjectwithuniqueid.getName());
//                        }
                        setNewInternalId(iobjectwithuniqueid);
                        hashset.add(iobjectwithuniqueid.getParentGroup());
                    }
                }
            }
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param vector
     * @return
     */
    private int getValidInternalIdIndex(java.util.Vector vector) {
        synchronized (moveDestinationSync) {
            if (moveDestination != null) {
                COM.dragonflow.SiteView.Monitor monitor;
                for (int i = 0; i < vector.size(); i ++) {
                    monitor = (COM.dragonflow.SiteView.Monitor) vector.elementAt(i);
                    if (monitor != null && monitor.getProperty(COM.dragonflow.SiteView.MonitorGroup.pID).equalsIgnoreCase(moveDestination)) {
                        return i;
                    }
                }
            }
        }
        return 0;
    }

    private void groupByInternalIds(java.util.Vector vector, java.util.HashMap hashmap, java.util.Collection collection) {
        java.util.Vector vector1 = vector;
        for (int i = 0; i < vector1.size(); i ++) {
            java.lang.Object obj = vector1.elementAt(i);
            if (!(obj instanceof COM.dragonflow.SiteView.IObjectWithUniqueId)) {
                continue;
            }
            COM.dragonflow.SiteView.IObjectWithUniqueId iobjectwithuniqueid = (COM.dragonflow.SiteView.IObjectWithUniqueId) obj;
            int j = iobjectwithuniqueid.getUniqueInternalId();
            if (j >= nextSiteViewId) {
                nextSiteViewId = j + 1;
            }
            if (j <= 0) {
                j = setNewInternalId(iobjectwithuniqueid);
                collection.add(iobjectwithuniqueid.getParentGroup());
            }
            java.lang.Integer integer = new Integer(j);
            java.util.Vector vector2 = (java.util.Vector) hashmap.get(integer);
            if (vector2 == null) {
                vector2 = new Vector();
            }
            vector2.add(iobjectwithuniqueid);
            hashmap.put(integer, vector2);
        }

    }

    private int setNewInternalId(COM.dragonflow.SiteView.IObjectWithUniqueId iobjectwithuniqueid) {
        int i = getNextSiteviewId();
        iobjectwithuniqueid.setUniqueInternalId(i);
        return i;
    }

    public void detectNextInternalId() {
        java.util.Vector vector = new Vector();
        java.util.Vector vector1 = new Vector();
        COM.dragonflow.SiteView.ConfigurationChanger.getCurrentConfiguration(vector, vector1, vector1, null);
        int i = 1;
        for (int j = 0; j < vector1.size(); j ++) {
            COM.dragonflow.SiteView.IObjectWithUniqueId iobjectwithuniqueid = (COM.dragonflow.SiteView.IObjectWithUniqueId) vector1.elementAt(j);
            int k = iobjectwithuniqueid.getUniqueInternalId();
            if (k >= i) {
                i = k + 1;
            }
        }

//        if (COM.dragonflow.TopazIntegration.TopazFileLogger.getLogger().isLoggable(java.util.logging.Level.FINE)) {
//            COM.dragonflow.TopazIntegration.TopazFileLogger.getLogger().fine("Next internal ID: " + nextSiteViewId);
//        }
        if (i > nextSiteViewId) {
            nextSiteViewId = i;
            saveSettings();
        }
    }

    private void saveSettings() {
        try {
            if (!(new File(settingsFilePath)).exists()) {
                COM.dragonflow.Utils.FileUtils.verifyFileExists(settingsFilePath, false);
            }
            java.io.ObjectOutputStream objectoutputstream = new ObjectOutputStream(new FileOutputStream(settingsFilePath));
            objectoutputstream.writeInt(nextSiteViewId);
            objectoutputstream.flush();
            objectoutputstream.close();
        } catch (java.io.IOException ioexception) {
            COM.dragonflow.Log.LogManager.logException(ioexception);
        }
    }

    public void markAsDestinationForMove(java.lang.String s) {
        synchronized (moveDestinationSync) {
            moveDestination = s;
        }
    }

}
