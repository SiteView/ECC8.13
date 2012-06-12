/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class JMXInterface {

    public Class MBeanServerClass;

    public Class QueryExpClass;

    public Class QueryClass;

    public Class AttributeValueExpClass;

    public Class StringValueExpClass;

    public Class ObjectNameClass;

    public Class MBeanInfoClass;

    public Class MBeanAttributeInfoClass;

    public Method finalSubStringMethod;

    public Method attrMethod;

    public Method valueMethod;

    public Method queryNamesMethod;

    public Method getAttributeMethod;

    public Method getMBeanInfoMethod;

    public Method invokeMethod;

    public Constructor objectNameCtr;

    public Method equalsMethod;

    public Method getKeyPropertyMethod;

    public Method getAttributesMethod;

    public Method getInfoDescriptionMethod;

    public Method isReadableMethod;

    public Method getTypeMethod;

    public Method getNameMethod;

    public Method getDescriptionMethod;

    public JMXInterface() {
        ClassLoader classloader = Thread.currentThread().getContextClassLoader();
        try {
            QueryClass = classloader.loadClass("javax.management.Query");
            QueryExpClass = classloader.loadClass("javax.management.QueryExp");
            AttributeValueExpClass = classloader.loadClass("javax.management.AttributeValueExp");
            StringValueExpClass = classloader.loadClass("javax.management.StringValueExp");
            MBeanServerClass = classloader.loadClass("javax.management.MBeanServer");
            ObjectNameClass = classloader.loadClass("javax.management.ObjectName");
            MBeanInfoClass = classloader.loadClass("javax.management.MBeanInfo");
            MBeanAttributeInfoClass = classloader.loadClass("javax.management.MBeanAttributeInfo");
            finalSubStringMethod = QueryClass.getMethod("finalSubString", new Class[] { AttributeValueExpClass, StringValueExpClass });
            attrMethod = QueryClass.getMethod("attr", new Class[] { String.class });
            valueMethod = QueryClass.getMethod("value", new Class[] { String.class });
            queryNamesMethod = MBeanServerClass.getMethod("queryNames", new Class[] { ObjectNameClass, QueryExpClass });
            getAttributeMethod = MBeanServerClass.getMethod("getAttribute", new Class[] { ObjectNameClass, String.class });
            getMBeanInfoMethod = MBeanServerClass.getMethod("getMBeanInfo", new Class[] { ObjectNameClass });
            invokeMethod = MBeanServerClass.getMethod("invoke", new Class[] { ObjectNameClass, String.class, Object[].class, String[].class });
            objectNameCtr = ObjectNameClass.getConstructor(new Class[] { String.class });
            equalsMethod = ObjectNameClass.getMethod("equals", new Class[] { Object.class });
            getKeyPropertyMethod = ObjectNameClass.getMethod("getKeyProperty", new Class[] { String.class });
            getAttributesMethod = MBeanInfoClass.getMethod("getAttributes", null);
            getInfoDescriptionMethod = MBeanInfoClass.getMethod("getDescription", null);
            isReadableMethod = MBeanAttributeInfoClass.getMethod("isReadable", null);
            getTypeMethod = MBeanAttributeInfoClass.getMethod("getType", null);
            getNameMethod = MBeanAttributeInfoClass.getMethod("getName", null);
            getDescriptionMethod = MBeanAttributeInfoClass.getMethod("getDescription", null);
        } catch (Exception exception) {
            System.err.println("Failed to load javax.management class or method: " + exception.toString());
        }
    }
}
