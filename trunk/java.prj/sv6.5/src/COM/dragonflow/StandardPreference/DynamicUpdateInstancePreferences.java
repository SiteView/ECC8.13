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

import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import jgl.LessString;
import COM.dragonflow.Properties.BooleanProperty;
import COM.dragonflow.Properties.NumericProperty;
import COM.dragonflow.Properties.ScalarProperty;
import COM.dragonflow.Properties.StringProperty;

public class DynamicUpdateInstancePreferences extends COM.dragonflow.SiteView.Preferences {

    public static COM.dragonflow.Properties.StringProperty pMonitorSet;

    public static COM.dragonflow.Properties.StringProperty pGroupSet;

    public static COM.dragonflow.Properties.StringProperty pGroup;

    public static COM.dragonflow.Properties.StringProperty pParent;

    public static COM.dragonflow.Properties.StringProperty pCheckFrequency;

    public static COM.dragonflow.Properties.StringProperty pExcludeIP;

    public static COM.dragonflow.Properties.StringProperty pName;

    public static COM.dragonflow.Properties.StringProperty pHost;

    public static COM.dragonflow.Properties.StringProperty pRootOID;

    public static COM.dragonflow.Properties.StringProperty pOtherOID;

    public static COM.dragonflow.Properties.StringProperty pPoolIncluded;

    public static COM.dragonflow.Properties.StringProperty pCommunity;

    public static COM.dragonflow.Properties.StringProperty pDBConnectionURL;

    public static COM.dragonflow.Properties.StringProperty pDBDriver;

    public static COM.dragonflow.Properties.StringProperty pDBSqlQuery;

    public static COM.dragonflow.Properties.StringProperty pDBUsername;

    public static COM.dragonflow.Properties.StringProperty pDBPassword;

    public static COM.dragonflow.Properties.StringProperty pDBConnectTimeout;

    public static COM.dragonflow.Properties.StringProperty pDBQueryTimeout;

    public DynamicUpdateInstancePreferences() {
    }

    public java.lang.String verify(COM.dragonflow.Properties.StringProperty stringproperty, java.lang.String s, COM.dragonflow.HTTP.HTTPRequest httprequest, java.util.HashMap hashmap, java.util.HashMap hashmap1) {
        if (stringproperty == pCheckFrequency) {
            try {
                new Integer(s.trim());
            } catch (java.lang.NumberFormatException numberformatexception) {
                hashmap1.put(stringproperty, "The entry is not a valid number.");
            }
        } else if (stringproperty == pDBPassword) {
            s = COM.dragonflow.Utils.TextUtils.obscure(s);
        } else if (stringproperty == pName && (s == null || s.length() == 0)) {
            s = (java.lang.String) hashmap.get(pHost.getName());
        } else if (stringproperty == pRootOID || stringproperty == pMonitorSet || stringproperty == pParent) {
            checkIfValid((COM.dragonflow.Properties.ScalarProperty) stringproperty, s, httprequest, hashmap1);
        }
        return s;
    }

    public java.util.Vector getScalarValues(COM.dragonflow.Properties.ScalarProperty scalarproperty, COM.dragonflow.HTTP.HTTPRequest httprequest) throws COM.dragonflow.SiteViewException.SiteViewException {
        java.util.Vector vector = new Vector();
        if (scalarproperty == pRootOID) {
            vector.addElement("BIGIP-4.1.1PoolIncluded-(1.3.6.1.4.1.3375.1.1.8.2.1.1)");
            vector.addElement("BIGIP-4.1.1PoolIncluded-(1.3.6.1.4.1.3375.1.1.8.2.1.1)");
            vector.addElement("other");
            vector.addElement("other");
        } else if (scalarproperty == pMonitorSet) {
            java.util.Vector vector1 = COM.dragonflow.SiteView.SiteViewGroup.getTemplateList("templates.sets", httprequest);
            for (int i = 0; i < vector1.size(); i ++) {
                vector.addElement(vector1.elementAt(i));
                vector.addElement(vector1.elementAt(i));
            }

        } else if (scalarproperty == pParent) {
            vector.addElement("");
            vector.addElement("-- SiteView Panel --");
            COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            jgl.Array array = siteviewgroup.getGroupIDs();
            jgl.Array array1 = new Array();
            jgl.HashMap hashmap = new HashMap();
            for (int j = 0; j < array.size(); j ++) {
                java.lang.String s = (java.lang.String) array.at(j);
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup.getElement(s);
                if (monitorgroup != null) {
                    java.lang.String s3 = COM.dragonflow.Page.CGI.getGroupPath(monitorgroup, COM.dragonflow.Page.CGI.getGroupIDFull(s, siteviewgroup), false);
                    array1.add(s3);
                    hashmap.add(s3, s);
                }
            }

            jgl.Sorting.sort(array1, new LessString());
            for (int k = 0; k < array1.size(); k ++) {
                java.lang.String s1 = (java.lang.String) array1.at(k);
                java.lang.String s2 = (java.lang.String) hashmap.get(s1);
                vector.addElement(s2);
                vector.addElement(s1);
            }

        }
        return vector;
    }

    static {
        pMonitorSet = new ScalarProperty("_set");
        pMonitorSet.setDisplayText("Template Set", "Select the Monitor Set Template used to create new monitors.");
        pMonitorSet.setParameterOptions(true, 1, false);
        pGroupSet = new StringProperty("_groupSet", "$NODE-IP$");
        pGroupSet.setDisplayText("Monitor Set Subgroup Name", "Enter the monitor group name to be assigned to each set of monitors created using the above template. Default is IP address. Enter an optional text string to be appended to default name. ");
        pGroupSet.setParameterOptions(true, 2, false);
        pGroup = new StringProperty("_group");
        pGroup.setDisplayText("Group Name", "Enter a name for the group to be created to contain all subgroups created using the template selected above.");
        pGroup.setParameterOptions(true, 3, false);
        pParent = new ScalarProperty("_parent");
        pParent.setDisplayText("SiteView Parent Group", "Select an existing SiteView group to which the above container group will be added as a subgroup. Choose SiteView Panel to create a new group on the SiteView Main Panel");
        pParent.setParameterOptions(true, 4, false);
        pCheckFrequency = new NumericProperty("_frequency", "600", "seconds");
        pCheckFrequency.setDisplayText("Update Frequency", "Enter the frequency (in seconds) that SiteView will query the MIB or database for new nodes and create monitor sets for new nodes.");
        pCheckFrequency.setParameterOptions(true, 5, false);
        pExcludeIP = new StringProperty("_excludeIP");
        pExcludeIP.setDisplayText("Exclude IP", "Enter IP addresses to be excluded from the Update Set, for example, the default gateway IP. To exclude multiple IP address, separate them by commas.");
        pExcludeIP.setParameterOptions(true, 6, false);
        pName = new StringProperty("_name");
        pName.setDisplayText("Title", "Optional, enter the title for this Dynamic Update Set.  The default title is the server address.");
        pName.setParameterOptions(true, 7, false);
        pHost = new StringProperty("_host");
        pHost.setDisplayText("Server Address", "The server or console where the SNMP MIB is found. Enter the UNC style name (For example:\\servername) or the IP address.");
        pHost.setParameterOptions(true, 8, false);
        pRootOID = new ScalarProperty("_oid");
        pRootOID.setDisplayText("SNMP Object ID", "Enter the root OID for the object that returns the node IP addresses to be monitored.");
        pRootOID.setParameterOptions(true, 9, false);
        pOtherOID = new StringProperty("_otheroid");
        pOtherOID.setDisplayText("Other", "");
        pOtherOID.setParameterOptions(true, 10, false);
        pPoolIncluded = new BooleanProperty("_poolIncluded", "");
        pPoolIncluded.setDisplayText("Pool Included", "Check this if the pool IP Address is included in the result of the oid walk (Note: for F5 servers).");
        pPoolIncluded.setParameterOptions(true, 11, false);
        pCommunity = new StringProperty("_community", "public");
        pCommunity.setDisplayText("Community", "Enter the community variable for the SNMP MIB.  The default is public.");
        pCommunity.setParameterOptions(true, 12, false);
        pDBConnectionURL = new StringProperty("_dbConnectionURL");
        pDBConnectionURL.setDisplayText("Database Connection URL", "Enter the URL to the database connection (for example, jdbc:inetdae:myserver.mycompany.com:1433?database=master).");
        pDBConnectionURL.setParameterOptions(true, 13, false);
        pDBDriver = new StringProperty("_dbDriver", "com.inet.tds.TdsDriver");
        pDBDriver.setDisplayText("Database Driver", "Enter the driver used to connect to the database (for example, com.inet.tds.TdsDriver) ");
        pDBDriver.setParameterOptions(true, 14, false);
        pDBSqlQuery = new StringProperty("_dbSqlQuery");
        pDBSqlQuery.setDisplayText("SQL Query", "Enter the SQL query to run against a table in the database that returns the list of IP addresses to be monitored.");
        pDBSqlQuery.setParameterOptions(true, 15, false);
        pDBUsername = new StringProperty("_dbUserName");
        pDBUsername.setDisplayText("Database Username", "Enter the username for connecting to the database.");
        pDBUsername.setParameterOptions(true, 16, false);
        pDBPassword = new StringProperty("_dbPassword");
        pDBPassword.setDisplayText("Database Password", "Enter the password used to connect to the database.");
        pDBPassword.setParameterOptions(true, 17, false);
        pDBConnectTimeout = new StringProperty("_dbConnectTimeout", "60");
        pDBConnectTimeout.setDisplayText("Connection Timeout", "Enter the connection timeout (in seconds) to use for the database.");
        pDBConnectTimeout.setParameterOptions(true, 18, false);
        pDBQueryTimeout = new StringProperty("_dbQueryTimeout", "60");
        pDBQueryTimeout.setDisplayText("Query Timeout", "Enter the query timeout (in seconds) to use for the database.");
        pDBQueryTimeout.setParameterOptions(true, 19, false);
        COM.dragonflow.Properties.StringProperty astringproperty[] = { pMonitorSet, pGroupSet, pGroup, pParent, pCheckFrequency, pExcludeIP, pName, pHost, pRootOID, pOtherOID, pPoolIncluded, pCommunity, pDBConnectionURL, pDBDriver, pDBSqlQuery,
                pDBUsername, pDBPassword, pDBConnectTimeout, pDBQueryTimeout };
        COM.dragonflow.StandardPreference.DynamicUpdateInstancePreferences.addProperties("COM.dragonflow.StandardPreference.DynamicUpdateInstancePreferences", astringproperty);
    }
}
