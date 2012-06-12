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
public class SSCounter extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String id;

    public SSCounter(java.lang.String s, java.lang.String s1) {
        name = s;
        id = s1;
    }

    public java.lang.String toString() {
        return "(" + name + ", " + id + ")";
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
}
