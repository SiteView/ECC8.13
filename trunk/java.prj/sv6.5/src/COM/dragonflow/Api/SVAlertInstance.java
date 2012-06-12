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
// SSBaseReturnValues, SSInstanceProperty

public class SVAlertInstance extends COM.dragonflow.Api.SSBaseReturnValues
{

    private java.lang.String alertId;
    private java.lang.String monitorId;
    private java.lang.String groupId;
    private COM.dragonflow.Api.SSInstanceProperty instanceProperties[];

    public SVAlertInstance(java.lang.String s, java.lang.String s1, java.lang.String s2, COM.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
    {
        alertId = s;
        monitorId = s1;
        groupId = s2;
        instanceProperties = assinstanceproperty;
    }

    public java.lang.Object getReturnValueType()
    {
        java.lang.Class class1 = getClass();
        return class1.getName();
    }

    public java.lang.String getAlertId()
    {
        return alertId;
    }

    public java.lang.String getMonitorId()
    {
        return monitorId;
    }

    public java.lang.String getGroupId()
    {
        return groupId;
    }

    public COM.dragonflow.Api.SSInstanceProperty[] getInstanceProperties()
    {
        return instanceProperties;
    }
}
