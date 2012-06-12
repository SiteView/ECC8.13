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
// SSBaseReturnValues, SSInstanceProperty

public class SSGroupInstance extends com.dragonflow.Api.SSBaseReturnValues
{

    private String groupId;
    private com.dragonflow.Api.SSInstanceProperty instanceProperties[];

    public SSGroupInstance(String s, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
    {
        groupId = s;
        instanceProperties = assinstanceproperty;
    }

    public Object getReturnValueType()
    {
        Class class1 = getClass();
        return class1.getName();
    }

    public String getGroupId()
    {
        return groupId;
    }

    public com.dragonflow.Api.SSInstanceProperty[] getInstanceProperties()
    {
        return instanceProperties;
    }
}
