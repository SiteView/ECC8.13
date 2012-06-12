/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.StandardAction;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import com.dragonflow.Api.APIGroup;

public class UpdateGroup extends com.dragonflow.SiteView.Action {

    public UpdateGroup(com.dragonflow.SiteView.Monitor monitor) {
        runType = 1;
        setMonitor(monitor);
    }

    public boolean execute() {
        try {
            (new APIGroup()).refreshGroup(monitor.getProperty(com.dragonflow.SiteView.MonitorGroup.pGroupID), false);
        } catch (java.lang.Exception exception) {
            com.dragonflow.Log.LogManager.log("Error", "UpdateGroup: failed to refresh group: " + com.dragonflow.SiteView.MonitorGroup.pGroupID + ", exception: " + exception.getMessage());
            return false;
        }
        return true;
    }

    public java.lang.String toString() {
        java.lang.String s = "update group ";
        if (monitor == null) {
            s = s + "<unknown>";
        } else {
            java.lang.String s1 = "";
            java.lang.String s2 = monitor.getProperty(com.dragonflow.SiteView.SiteViewObject.pGroupID);
            if (s2 != null) {
                s1 = s1 + s2 + ":" + monitor.getProperty(com.dragonflow.SiteView.SiteViewObject.pID) + "  ";
            }
            s1 = s1 + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName);
            s = s + s1;
        }
        return s;
    }
}
