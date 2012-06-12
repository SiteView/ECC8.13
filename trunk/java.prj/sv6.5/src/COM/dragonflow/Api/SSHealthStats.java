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
public class SSHealthStats extends COM.dragonflow.Api.SSBaseReturnValues {

    private java.lang.String name;

    private java.lang.String status;

    private java.lang.String type;

    private java.lang.Object measurement1;

    private java.lang.Object measurement2;

    public static final java.lang.String CURRENT_MONITORS_PER_MINUTE = "CURRENT_MONITORS_PER_MINUTE";

    public static final java.lang.String CURRENT_MONITORS_RUNNING = "CURRENT_MONITORS_RUNNING";

    public static final java.lang.String CURRENT_MONITORS_WAITING = "CURRENT_MONITORS_WAITING";

    public static final java.lang.String MAXIMUM_MONITORS_PER_MINUTE = "MAXIMUM_MONITORS_PER_MINUTE";

    public static final java.lang.String MAXIMUM_MONITORS_RUNNING = "MAXIMUM_MONITORS_RUNNING";

    public static final java.lang.String MAXIMUM_MONITORS_WAITING = "MAXIMUM_MONITORS_WAITING";

    public static final java.lang.String LOG_MONITOR_STATS = "LOG_MONITOR_STATS";

    public static final java.lang.String SERVER_LOAD_STATS = "SERVER_LOAD_STATS";

    public static final java.lang.String RUNNING_MONITOR_STATS = "RUNNING_MONITOR_STATS";

    public SSHealthStats(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.Object obj, java.lang.Object obj1) {
        name = s;
        status = s1;
        measurement1 = obj;
        measurement2 = obj1;
    }

    public java.lang.Object getReturnValueType() {
        java.lang.Class class1 = null;
        try {
            class1 = java.lang.Class.forName("java.lang.Object");
            if (type.equals("CURRENT_MONITORS_PER_MINUTE")) {
                class1 = java.lang.Class.forName("java.lang.Float");
            } else if (type.equals("CURRENT_MONITORS_RUNNING")) {
                class1 = java.lang.Class.forName("java.lang.Integer");
            } else if (type.equals("CURRENT_MONITORS_WAITING")) {
                class1 = java.lang.Class.forName("java.lang.Integer");
            }
            if (type.equals("MAXIMUM_MONITORS_PER_MINUTE")) {
                class1 = java.lang.Class.forName("java.lang.Float");
            } else if (type.equals("MAXIMUM_MONITORS_RUNNING")) {
                class1 = java.lang.Class.forName("java.lang.Float");
            } else if (type.equals("MAXIMUM_MONITORS_WAITING")) {
                class1 = java.lang.Class.forName("java.lang.Float");
            } else if (type.equals("LOG_MONITOR_STATS")) {
                class1 = java.lang.Class.forName("java.lang.Integer");
            } else if (type.equals("SERVER_LOAD_STATS")) {
                class1 = java.lang.Class.forName("java.lang.String");
            } else if (type.equals("RUNNING_MONITOR_STATS")) {
                class1 = java.lang.Class.forName("java.lang.String");
            }
        } catch (java.lang.ClassNotFoundException classnotfoundexception) {
            class1 = null;
        }
        return class1;
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getStatus() {
        return status;
    }

    public java.lang.Object getMeasurement1() {
        return measurement1;
    }

    public java.lang.Object getMeasurement2() {
        return measurement2;
    }
}
