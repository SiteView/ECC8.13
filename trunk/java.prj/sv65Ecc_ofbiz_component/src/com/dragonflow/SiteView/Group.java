/*
 * 
 * Created on 2005-2-16 15:14:00
 *
 * Group.java
 *
 * History:
 *
 */
package com.dragonflow.SiteView;

/**
 * Comment for <code>Group</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.util.Enumeration;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Page.CGI;
import com.dragonflow.Properties.FrequencyProperty;
import com.dragonflow.Properties.ScalarProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteViewException.SiteViewException;
import com.dragonflow.Utils.TextUtils;

// Referenced classes of package com.dragonflow.SiteView:
// SiteViewObject, MonitorGroup, Monitor, SubGroup,
// SiteViewGroup, MasterConfig

public class Group extends SiteViewObject {

    public static StringProperty pName;

    public static StringProperty pParent;

    public static StringProperty pDescription;

    public static StringProperty pDependsOn;

    public static StringProperty pDependsCondition;

    public static StringProperty pHttpCharSet;

    public static StringProperty pFrequency;

    public Group() {
    }

    public String verify(StringProperty stringproperty, String s,
            HTTPRequest httprequest, HashMap hashmap) {
        return s;
    }
    public static Vector getScalarValues(ScalarProperty stringproperty,
            String groupId) throws SiteViewException {
    	HTTPRequest httprequest = new HTTPRequest();
    	httprequest.setValue("groupID", groupId);
    	return new Group().getScalarValues(stringproperty, httprequest, null);
    }

    public Vector getScalarValues(ScalarProperty scalarproperty,
            HTTPRequest httprequest, CGI cgi) throws SiteViewException {
        if (scalarproperty == pDependsOn) {
            Vector vector = new Vector();
            vector.addElement("");
            vector.addElement("None");
            SiteViewGroup siteviewgroup = SiteViewGroup.currentSiteView();
            Array array = SiteViewGroup.currentSiteView().getGroupIDs();
            for (Enumeration enumeration1 = array.elements(); enumeration1
                    .hasMoreElements();) {
                String s1 = (String) enumeration1.nextElement();
                MonitorGroup monitorgroup = (MonitorGroup) siteviewgroup
                        .getElement(s1);
                if (monitorgroup != null
                        && (httprequest.hasValue("groupID")
                                && !httprequest.getValue("groupID").equals(s1) || !httprequest
                                .hasValue("groupID"))) {
                    String s3 = CGI.getGroupPath(monitorgroup, s1, false);
                    Enumeration enumeration2 = monitorgroup.getMonitors();
                    while (enumeration2.hasMoreElements()) {
                        Monitor monitor = (Monitor) enumeration2.nextElement();
                        if (!(monitor instanceof SubGroup)) {
                            String s5 = monitor.getProperty(Monitor.pID);
                            String s6 = monitor.getProperty(Monitor.pName);
                            vector.addElement(s1 + " " + s5);
                            vector.addElement(s3 + ": " + s6);
                        }
                    }
                }
            }

            return vector;
        } else {
            if (scalarproperty == pDependsCondition) {
                Vector vector1 = new Vector();
                vector1.addElement("good");
                vector1.addElement("OK");
                vector1.addElement("error");
                vector1.addElement("Error");
                return vector1;
            }
            if (scalarproperty == pHttpCharSet) {
                HashMap hashmap = MasterConfig.getMasterConfig();
                Vector vector2 = new Vector();
                String s2;
                for (Enumeration enumeration = hashmap
                        .values("_httpCharSetOption"); enumeration
                        .hasMoreElements(); vector2.addElement(s2)) {
                    String s = (String) enumeration.nextElement();
                    String as[] = TextUtils.split(s, ",");
                    s2 = as[0];
                    String s4 = "";
                    if (as.length > 1) {
                        s4 = as[1];
                    }
                    vector2.addElement(s4);
                }

                if (vector2.size() == 0) {
                    vector2.addElement("");
                    vector2.addElement("default");
                }
                return vector2;
            } else {
                return super.getScalarValues(scalarproperty, httprequest, cgi);
            }
        }
    }

    public static void main(String args[]) {
        HTTPRequest httprequest = new HTTPRequest();
        Group group = new Group();
        HashMap hashmap = new HashMap();
        String s = group.verify(group.pID, "", httprequest, hashmap);
        System.out.println("value = " + s);
        System.out.println("error message = " + hashmap.get(group.pID));
    }

    static {
        pName = new StringProperty("_name");
        pName.setDisplayText("Group Name:", "Valid group name characters are alphanumeric characters, dashes (-), underscores (_), periods (.), and spaces( ).<code><font size=2>[a-zA-Z0-9-_. ]</font></code>");
        pName.setParameterOptions(true, 1, false);
        pParent = new StringProperty("_parent", "");
        pDescription = new StringProperty("_description", "");
        pDescription
                .setDisplayText(
                        "Description:",
                        "Enter an optional description that is displayed at the top of the Group Detail page. You can enter a multi-row, two column table by entering decription name value pairs seperated by a ':' Placed one pair per line.");
        pDescription.setParameterOptions(true, 1, true);
        pDependsOn = new ScalarProperty("_dependsOn", "");
        pDependsOn
                .setDisplayText(
                        "Depends On:",
                        "Choose the monitor to that controls whether monitors in this group are enabled.");
        pDependsOn.setParameterOptions(true, 2, true);
        pDependsCondition = new ScalarProperty("_dependsCondition", "good");
        pDependsCondition
                .setDisplayText(
                        "Depends Condition:",
                        "If OK, this group is only enabled if the Depends On monitor is OK. Use this to disable monitoring when a router or an entire server goes down.  If Error, this group is only enabled when the Depends On monitor is in Error. Use this to enable \"failover\" monitoring if another monitoring system goes downEnter the password used to connect to the database.");
        pDependsCondition.setParameterOptions(true, 3, true);
        pHttpCharSet = new ScalarProperty("_httpCharSet", "default");
        pHttpCharSet
                .setDisplayText(
                        "Encoding:",
                        "If the monitors in this group and its subgroups should use a different character encoding");
        pHttpCharSet.setParameterOptions(true, 4, true);
        pFrequency = new FrequencyProperty("_frequency", "600");
/*        pFrequency.setDisplayText("Update every",
                "amount of time between checks of a monitor");
*/
        pFrequency.setDisplayText("Update every",
        "Refresh all the monitors in this group according to this schedule. This frequency should not be less than 60 seconds. When defining a group schedule, the monitors of this group will not run by their own schedule.");
        pFrequency.setParameterOptions(true, 5, true);
        StringProperty astringproperty[] = { pName, pParent, pDescription,
                pDependsOn, pDependsCondition, pHttpCharSet, pFrequency };
        addProperties("com.dragonflow.SiteView.Group", astringproperty);
    }
}
