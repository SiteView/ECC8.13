/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Api;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

// Referenced classes of package com.dragonflow.Api:
// SSBaseReturnValues
public class SSInstanceProperty extends com.dragonflow.Api.SSBaseReturnValues {

    private String name;

    private String label;

    private Object value;

    public SSInstanceProperty(String s, Object obj) {
        name = s;
        value = obj;
    }

    public String toString() {
        return "(" + name + ", " + label + ", " + (String) value + ")";
    }

    public SSInstanceProperty(String s, String s1, Object obj) {
        name = s;
        label = s1;
        value = obj;
    }

    public Object getReturnValueType() {
        Class class1 = getClass();
        return class1.getName();
    }

    public String getName() {
        return name;
    }

    public String getLabel() {
        return label;
    }

    public Object getValue() {
        return value;
    }
}
