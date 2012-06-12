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
public class SSInstanceProperty extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String label;

    private java.lang.Object value;

    public SSInstanceProperty(java.lang.String s, java.lang.Object obj) {
        name = s;
        value = obj;
    }

    public java.lang.String toString() {
        return "(" + name + ", " + label + ", " + (java.lang.String) value + ")";
    }

    public SSInstanceProperty(java.lang.String s, java.lang.String s1, java.lang.Object obj) {
        name = s;
        label = s1;
        value = obj;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getLabel() {
        return label;
    }

    public java.lang.Object getValue() {
        return value;
    }
}
