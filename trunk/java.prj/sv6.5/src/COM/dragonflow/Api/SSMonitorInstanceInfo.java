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
public class SSMonitorInstanceInfo extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String id;

    private java.lang.String groupId;

    private java.lang.String type;

    public SSMonitorInstanceInfo(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3) {
        name = s;
        id = s1;
        groupId = s2;
        type = s3;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getId() {
        return id;
    }

    public java.lang.String getGroupId() {
        return groupId;
    }

    public java.lang.String getType() {
        return type;
    }
}
