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
public class SSGroupInstanceInfo extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String groupId;

    private java.lang.String parentGroupId;

    public SSGroupInstanceInfo(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        name = s;
        groupId = s1;
        parentGroupId = s2;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getGroupId() {
        return groupId;
    }

    public java.lang.String getParentGroupId() {
        return parentGroupId;
    }
}
