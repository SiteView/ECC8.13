/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package COM.dragonflow.Api:
// SSBaseReturnValues
public class SSAlertInstanceInfo extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String alertFullId;

    private java.lang.String alertId;

    private java.lang.String uniqueAlertId;

    private java.lang.String groupId;

    private java.lang.String monitorId;

    private java.lang.String type;

    public SSAlertInstanceInfo(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5) {
        name = s;
        alertFullId = s1;
        alertId = s2;
        groupId = s3;
        monitorId = s4;
        type = s5;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getAlertFullId() {
        return alertFullId;
    }

    public java.lang.String getAlertId() {
        return alertId;
    }

    public java.lang.String getUniqueAlertId() {
        return uniqueAlertId;
    }

    public java.lang.String getGroupId() {
        return groupId;
    }

    public java.lang.String getMonitorId() {
        return monitorId;
    }

    public java.lang.String getType() {
        return type;
    }
}
