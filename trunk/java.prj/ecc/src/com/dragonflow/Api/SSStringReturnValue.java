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
public class SSStringReturnValue extends com.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String value;

    public SSStringReturnValue(java.lang.String s) {
        value = s;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = null;
        try {
            class1 = java.lang.Class.forName("java.lang.String");
        } catch (java.lang.Exception exception) {
            exception.printStackTrace();
        }
        return class1.getName();
    }

    public java.lang.String getValue() {
        return value;
    }
}
