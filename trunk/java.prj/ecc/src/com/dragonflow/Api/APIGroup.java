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

import java.io.File;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.SiteView.Group;
import com.dragonflow.SiteViewException.SiteViewOperationalException;
import com.dragonflow.SiteViewException.SiteViewParameterException;

// Referenced classes of package com.dragonflow.Api:
// APISiteView, SSStringReturnValue, SSPropertyDetails, APIAlert,
// SSInstanceProperty, SSGroupInstance, Alert

public class APIGroup extends com.dragonflow.Api.APISiteView
{

    public APIGroup()
    {
    }

    public com.dragonflow.Api.SSStringReturnValue create(java.lang.String s, java.lang.String s1, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s2 = null;
        try
        {
            if(s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_NAME_MISSING);
            }
            if(!com.dragonflow.Utils.I18N.isI18N)
            {
                s2 = com.dragonflow.Utils.TextUtils.keepChars(s, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
            } else
            {
                s2 = com.dragonflow.Utils.FileUtils.getGroupNewFileName();
            }
            s2 = computeGroupName(s2);
            if(s2.length() == 0)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_NAME_EMPTY);
            }
            if(s2.equalsIgnoreCase("siteview"))
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_NAME_SITEVIEW);
            }
            if(assinstanceproperty == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_PROPERTIES_NOT_NULL);
            }
            jgl.HashMap hashmap = new HashMap();
            for(int i = 0; i < assinstanceproperty.length; i++)
            {
                hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            if(!com.dragonflow.SiteView.Platform.isStandardAccount(account))
            {
                s2 = computeGroupName(account + "$" + s2);
            } else
            {
                s2 = computeGroupName(s2);
                jgl.Array array = new Array();
                com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                updateConfig("_name", "config", hashmap, hashmapordered);
                if(s1 != null && s1.length() != 0)
                {
                    hashmapordered.put("_parent", s1);
                    jgl.Array array1 = ReadGroupFrames(s1);
                    jgl.HashMap hashmap1 = (jgl.HashMap)array1.at(0);
                    java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_nextID");
                    if(s3.length() == 0)
                    {
                        s3 = "1";
                    }
                    jgl.HashMap hashmap2 = new HashMap();
                    hashmap2.put("_id", s3);
                    hashmap2.put("_class", "SubGroup");
                    hashmap2.put("_group", s2);
                    hashmap2.put("_name", s);
                    array1.insert(array1.size(), hashmap2);
                    java.lang.String s4 = com.dragonflow.Utils.TextUtils.increment(s3);
                    hashmap1.put("_nextID", s4);
                    WriteGroupFrames(s1, array1);
                }
                if(!s.equals(s2))
                {
                    hashmapordered.put("_name", s);
                }
                array.add(hashmapordered);
                hashmapordered.put("_nextID", "1");
                updateConfig("_dependsOn", "", hashmap, hashmapordered);
                updateConfig("_dependsCondition", "good", hashmap, hashmapordered);
                updateConfig("_httpCharSet", "", hashmap, hashmapordered);
                updateConfig("__template", "", hashmap, hashmapordered);
                updateConfig("_frequency", "", hashmap, hashmapordered);
                updateConfig("_description", "", hashmap, hashmapordered);
                WriteGroupFrames(s2, array);
                com.dragonflow.Api.APIGroup.forceConfigurationRefresh();
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "create"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s2);
    }

    public void update(java.lang.String s, com.dragonflow.Api.SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            if(assinstanceproperty.length <= 0)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_PROPERTIES_NOT_NULL);
            }
            jgl.Array array = ReadGroupFrames(s);
            java.util.Enumeration enumeration = array.elements();
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            jgl.HashMap hashmap1 = new HashMap();
            for(int i = 0; i < assinstanceproperty.length; i++)
            {
                hashmap1.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }

            updateConfig("_name", "config", hashmap1, hashmap);
            updateConfig("_dependsOn", "", hashmap1, hashmap);
            updateConfig("_dependsCondition", "good", hashmap1, hashmap);
            updateConfig("_httpCharSet", "", hashmap1, hashmap);
            updateConfig("__template", "", hashmap1, hashmap);
            updateConfig("_frequency", "", hashmap1, hashmap);
            updateConfig("_description", "", hashmap1, hashmap);
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_parent");
            if(s1.length() != 0)
            {
                jgl.Array array1 = ReadGroupFrames(s1);
                int j = findSubGroupIndex(array1, s);
                jgl.HashMap hashmap2 = (jgl.HashMap)array1.at(j);
                updateConfig("_name", "config", hashmap1, hashmap2);
                WriteGroupFrames(s1, array1);
            }
            WriteGroupFrames(s, array);
            com.dragonflow.Api.APIGroup.forceConfigurationRefresh();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "update"
            }, 0L, exception.getMessage());
        }
    }

    public void delete(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            deleteGroupInternal(s);
            saveGroups();
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "delete"
            }, 0L, exception.getMessage());
        }
    }

    public com.dragonflow.Api.SSStringReturnValue move(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s2 = null;
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            if(s != null && s1 != null && s.equals(s1))
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_MOVE_DESTINATION_SELF);
            }
            java.lang.String s3 = null;
            java.lang.String s4 = s1;
            do
            {
                jgl.Array array = ReadGroupFrames(s4);
                java.util.Enumeration enumeration = array.elements();
                com.dragonflow.Properties.HashMapOrdered hashmapordered = (com.dragonflow.Properties.HashMapOrdered)enumeration.nextElement();
                s3 = (java.lang.String)hashmapordered.get("_parent");
                if(s3 != null && s3.equals(s))
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_MOVE_DESTINATION_SUBGROUP);
                }
                s4 = s3;
            } while(s3 != null && s3.length() > 0);
            s2 = moveGroup(s, s1, new HashMap(), false);
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "move"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s2);
    }

    public com.dragonflow.Api.SSStringReturnValue copy(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s2 = null;
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            if(s != null && s1 != null && s.equals(s1))
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_COPY_DESTINATION_SELF);
            }
            java.lang.String s3 = null;
            java.lang.String s4 = s1;
            if(s4 != null && s4.length() > 0)
            {
                do
                {
                    jgl.Array array = ReadGroupFrames(s4);
                    java.util.Enumeration enumeration = array.elements();
                    com.dragonflow.Properties.HashMapOrdered hashmapordered = (com.dragonflow.Properties.HashMapOrdered)enumeration.nextElement();
                    s3 = (java.lang.String)hashmapordered.get("_parent");
                    if(s3 != null && s3.equals(s))
                    {
                        throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_COPY_DESTINATION_SUBGROUP);
                    }
                    s4 = s3;
                } while(s3 != null && s3.length() > 0);
            }
            s2 = moveGroup(s, s1, new HashMap(), true);
            com.dragonflow.Api.APIGroup.forceConfigurationRefresh();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "copy"
            }, 0L, exception.getMessage());
        }
        return new SSStringReturnValue(s2);
    }

    public com.dragonflow.Api.SSPropertyDetails getClassPropertyDetails(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails sspropertydetails = null;
        try
        {
            java.lang.String s1 = "com.dragonflow.SiteView.Group";
            java.lang.Class class1 = java.lang.Class.forName(s1);
            com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
            com.dragonflow.Properties.StringProperty stringproperty = siteviewobject.getPropertyObject(s);
            if(stringproperty == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_COPY_DESTINATION_SUBGROUP, new java.lang.String[] {
                    s
                });
            }
            sspropertydetails = getClassProperty(stringproperty, null);
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getClassPropertyDetails"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    public com.dragonflow.Api.SSPropertyDetails[] getClassPropertiesDetails(int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails asspropertydetails[] = null;
        try
        {
            java.lang.String s = "com.dragonflow.SiteView.Group";
            java.lang.Class class1 = java.lang.Class.forName(s);
            com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
            jgl.Array array = getPropertiesForClass(siteviewobject, s, "Group", i);
            asspropertydetails = new com.dragonflow.Api.SSPropertyDetails[array.size()];
            for(int j = 0; j < array.size(); j++)
            {
                asspropertydetails[j] = getClassProperty((com.dragonflow.Properties.StringProperty)array.at(j), null);
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getClassPropertiesDetails"
            }, 0L, exception.getMessage());
        }
        return asspropertydetails;
    }

    public com.dragonflow.Api.SSPropertyDetails getInstancePropertyScalars(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSPropertyDetails sspropertydetails = null;
        try
        {
            java.lang.String s2 = "com.dragonflow.SiteView.Group";
            java.lang.Class class1 = java.lang.Class.forName(s2);
            com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
            com.dragonflow.Properties.StringProperty stringproperty = siteviewobject.getPropertyObject(s);
            sspropertydetails = getClassProperty(stringproperty, s1);
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getInstancePropertyScalars"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    public com.dragonflow.Api.SSGroupInstance[] getInstances(java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        if(!isGroupAllowedForAccount(s))
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_ACCESS_EXCEPTION);
        }
        com.dragonflow.Api.SSGroupInstance assgroupinstance[] = null;
        try
        {
            boolean flag = true;
            if(s != null && s.length() > 0)
            {
                flag = false;
            }
            java.util.Vector vector = new Vector();
            java.lang.Object obj = null;
            if(flag)
            {
                obj = com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getTopLevelGroups();
            } else
            {
                obj = getSubGroups(s);
            }
            com.dragonflow.Api.APIAlert apialert = new APIAlert();
            java.util.Iterator iterator = ((java.util.Collection) (obj)).iterator();
            while (iterator.hasNext()) {
                com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)iterator.next();
                java.lang.String s1 = monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pID);
                if(isGroupAllowedForAccount(s1))
                {
                    java.lang.String s2 = monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pParent);
                    if(flag && (s2 == null || s2.length() == 0) || !flag && s2 != null && s2.equals(s))
                    {
                        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = getInstanceProperties(s1, i);
                        int k = 0;
                        boolean flag1 = false;
                        if(com.dragonflow.Api.Alert.getInstance().groupHasAlerts(s1))
                        {
                            flag1 = true;
                            k++;
                        }
                        boolean flag2 = false;
                        if(hasSubGroupDependencies(s1))
                        {
                            flag2 = true;
                            k++;
                        }
                        int l = 0;
                        com.dragonflow.Api.SSInstanceProperty assinstanceproperty1[] = new com.dragonflow.Api.SSInstanceProperty[assinstanceproperty.length + k];
                        if(flag1)
                        {
                            assinstanceproperty1[l] = new SSInstanceProperty("hasDependencies", "true");
                            l++;
                        }
                        if(flag2)
                        {
                            assinstanceproperty1[l] = new SSInstanceProperty("hasSubDependencies", "true");
                        }
                        for(int i1 = 0; i1 < assinstanceproperty.length; i1++)
                        {
                            if(assinstanceproperty[i1].getName().equals("_name") && assinstanceproperty[i1].getValue().equals("config"))
                            {
                                assinstanceproperty1[i1 + k] = new SSInstanceProperty("_name", s1);
                            } else
                            {
                                assinstanceproperty1[i1 + k] = assinstanceproperty[i1];
                            }
                        }

                        vector.add(new SSGroupInstance(s1, assinstanceproperty1));
                    }
                }
            } 
            assgroupinstance = new com.dragonflow.Api.SSGroupInstance[vector.size()];
            for(int j = 0; j < vector.size(); j++)
            {
                assgroupinstance[j] = (com.dragonflow.Api.SSGroupInstance)vector.get(j);
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getInstances"
            }, 0L, exception.getMessage());
        }
        return assgroupinstance;
    }

    public com.dragonflow.Api.SSInstanceProperty[] getInstanceProperties(java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty assinstanceproperty[] = null;
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            jgl.Array array = getPropertiesForGroupInstance("com.dragonflow.SiteView.Group", i);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = com.dragonflow.SiteView.SiteViewGroup.getMonitorGroup(s);
            int j = 0;
            com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
            try
            {
                if(i == com.dragonflow.Api.APISiteView.FILTER_CONFIGURATION_ALL || i == com.dragonflow.Api.APISiteView.FILTER_ALL)
                {
                    j = 1;
//                    ssstringreturnvalue = getTopazID(s);
                }
            }
            catch(java.lang.Exception exception1)
            {
                j = 0;
            }
            assinstanceproperty = new com.dragonflow.Api.SSInstanceProperty[j + array.size()];
            int k = 0;
            for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements();)
            {
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                java.lang.String s1 = monitorgroup.getProperty(stringproperty.getName());
                if(stringproperty.isPassword)
                {
                    s1 = com.dragonflow.Utils.TextUtils.obscure(s1);
                }
                assinstanceproperty[k] = new SSInstanceProperty(stringproperty.getName(), s1);
                k++;
            }

            if(j > 0)
            {
//                assinstanceproperty[k] = new SSInstanceProperty("topazGroupID", com.dragonflow.SiteView.TopazInfo.getTopazName() + " Group ID", ssstringreturnvalue.getValue());
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getInstanceProperties"
            }, 0L, exception.getMessage());
        }
        return assinstanceproperty;
    }

    public com.dragonflow.Api.SSInstanceProperty getInstanceProperty(java.lang.String s, java.lang.String s1, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        com.dragonflow.Api.SSInstanceProperty ssinstanceproperty = null;
        try
        {
            if(s1.length() == 0 || s1 == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            jgl.Array array = getPropertiesForGroupInstance("com.dragonflow.SiteView.Group", i);
            com.dragonflow.SiteView.MonitorGroup monitorgroup = com.dragonflow.SiteView.SiteViewGroup.getMonitorGroup(s1);
            java.util.Enumeration enumeration = array.elements();
            while (enumeration.hasMoreElements()) {
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                java.lang.String s2 = monitorgroup.getProperty(stringproperty.getName());
                if(stringproperty.isPassword)
                {
                    s2 = com.dragonflow.Utils.TextUtils.obscure(s2);
                }
                if(stringproperty.getName().equals(s))
                {
                    ssinstanceproperty = new SSInstanceProperty(stringproperty.getName(), s2);
                }
            } 
            
            if(s.equals("topazGroupID"))
            {
                try
                {
//                    com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = getTopazID(s1);
//                    ssinstanceproperty = new SSInstanceProperty("topazGroupID", com.dragonflow.SiteView.TopazInfo.getTopazName() + " Group ID", ssstringreturnvalue.getValue());
                }
                catch(java.lang.Exception exception1)
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_TOPAZ_NOT_CONFIGURED);
                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getInstanceProperty"
            }, 0L, exception.getMessage());
        }
        return ssinstanceproperty;
    }

    public java.util.Collection getAllGroupInstances()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return getAllAllowedGroups();
    }

    public java.util.Collection getChildGroupInstances(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return getSubGroups(s);
    }

    public void refreshGroup(java.lang.String s, boolean flag)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(s.length() == 0 || s == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getElementByID(s);
            if(monitorgroup == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_NOT_VALID, new java.lang.String[] {
                    s
                });
            }
            com.dragonflow.SiteView.MonitorGroup _tmp = monitorgroup;
            monitorgroup.setProperty(com.dragonflow.SiteView.MonitorGroup.pLastUpdate, java.lang.String.valueOf(java.lang.System.currentTimeMillis()));
            java.util.Vector vector = new Vector();
            vector.add(monitorgroup);
            java.util.Vector vector1 = new Vector();
            com.dragonflow.SiteView.ConfigurationChanger.getGroupsMonitors(vector, vector1, null, flag);
            for(int i = 0; i < vector1.size(); i++)
            {
                ((com.dragonflow.SiteView.AtomicMonitor)vector1.get(i)).runUpdate(false);
            }

        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "refreshGroup"
            }, 0L, exception.getMessage());
        }
    }

//    public com.dragonflow.Api.SSStringReturnValue getTopazID(java.lang.String s)
//        throws com.dragonflow.SiteViewException.SiteViewException
//    {
//        com.dragonflow.Api.SSStringReturnValue ssstringreturnvalue = null;
////        com.dragonflow.TopazIntegration.TopazServerSettings topazserversettings = com.dragonflow.TopazIntegration.TopazManager.getInstance().getTopazServerSettings();
//        if(topazserversettings.isConnected())
//        {
//            ssstringreturnvalue = new SSStringReturnValue((new Integer(com.dragonflow.TopazIntegration.TopazConfigManager.getInstance().getGroup(s).getTopazId())).toString());
//        } else
//        {
//            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_TOPAZ_NOT_CONFIGURED);
//        }
//        return ssstringreturnvalue;
//    }

    private jgl.Array getPropertiesForGroupInstance(java.lang.String s, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        jgl.Array array = new Array();
        try
        {
            com.dragonflow.SiteView.Group group = new Group();
            jgl.Array array1 = group.getProperties();
            array1 = com.dragonflow.Properties.StringProperty.sortByOrder(array1);
            java.util.Enumeration enumeration = array1.elements();
            while (enumeration.hasMoreElements()) {
                boolean flag = false;
                com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                int j = s.lastIndexOf(".");
                flag = returnProperty(stringproperty, i, group, s.substring(j + 1));
                if(flag)
                {
                    array.add(stringproperty);
                }
            } 
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getPropertiesForGroupInstance"
            }, 0L, exception.getMessage());
        }
        return array;
    }

    private com.dragonflow.Api.SSPropertyDetails getClassProperty(com.dragonflow.Properties.StringProperty stringproperty, java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s1 = "TEXT";
        java.lang.String s2 = "LIST";
        java.lang.String as[] = null;
        java.lang.String as1[] = null;
        com.dragonflow.SiteView.SiteViewObject siteviewobject = null;
        java.lang.String s3 = "";
        try
        {
            if(stringproperty == null)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                    "APIGroup", "getClassProperty"
                });
            }
            if(stringproperty.isPassword)
            {
                s1 = "PASSWORD";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ServerProperty)
            {
                s1 = "SERVER";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScheduleProperty)
            {
                s1 = "SCHEDULE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScalarProperty)
            {
                s1 = "SCALAR";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.RateProperty)
            {
                s1 = "RATE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.PercentProperty)
            {
                s1 = "PERCENT";
                s3 = ((com.dragonflow.Properties.PercentProperty)stringproperty).getUnits();
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FrequencyProperty)
            {
                s1 = "FREQUENCY";
                s3 = "seconds";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FileProperty)
            {
                s1 = "FILE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.BrowsableProperty)
            {
                s1 = "BROWSABLE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.BooleanProperty)
            {
                s1 = "BOOLEAN";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.NumericProperty)
            {
                s1 = "NUMERIC";
                s3 = ((com.dragonflow.Properties.NumericProperty)stringproperty).getUnits();
            }
            com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            if(stringproperty instanceof com.dragonflow.Properties.ScalarProperty)
            {
                com.dragonflow.Properties.ScalarProperty scalarproperty = (com.dragonflow.Properties.ScalarProperty)stringproperty;
                java.lang.Class class1 = java.lang.Class.forName("com.dragonflow.SiteView.Group");
                if(s != null)
                {
                    httprequest.setValue("groupID", s);
                }
                siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
                java.lang.Class class2 = java.lang.Class.forName("com.dragonflow.Page.groupPage");
                com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI)class2.newInstance();
                cgi.initialize(httprequest, null);
                java.util.Vector vector = siteviewobject.getScalarValues(scalarproperty, httprequest, cgi);
                as = new java.lang.String[vector.size() / 2];
                as1 = new java.lang.String[vector.size() / 2];
                int i = 0;
                for(int j = 0; i < vector.size() / 2; j += 2)
                {
                    as1[i] = (java.lang.String)vector.elementAt(j);
                    as[i] = (java.lang.String)vector.elementAt(j + 1);
                    i++;
                }

            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getClassProperty"
            }, 0L, exception.getMessage());
        }
        return new SSPropertyDetails(stringproperty.getName(), s1, stringproperty.getDescription(), stringproperty.getLabel(), stringproperty.isEditable, stringproperty.isMultivalued, stringproperty.getDefault(), as, as1, s2, false, false, stringproperty.getOrder(), s3, stringproperty.isAdvanced, stringproperty.isPassword, siteviewobject.getProperty(stringproperty.getName()));
    }

    private java.lang.String moveGroup(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap, boolean flag)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.lang.String s2 = null;
        try
        {
            java.lang.String s3 = "";
            if(s.length() == 0)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_EMPTY);
            }
            if(s.equalsIgnoreCase("siteview"))
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_NAME_SITEVIEW);
            }
            com.dragonflow.Properties.HashMapOrdered hashmapordered = null;
            jgl.Array array = ReadGroupFrames(s);
            java.util.Enumeration enumeration = array.elements();
            hashmapordered = (com.dragonflow.Properties.HashMapOrdered)enumeration.nextElement();
            java.lang.String s4 = (java.lang.String)hashmapordered.get("_name");
            if(s4.equals("config"))
            {
                s4 = s;
            }
            if(exceedsLicenseLimit(array, s))
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_LICENSE_LIMIT);
            }
            if(flag)
            {
                s = computeGroupName(s);
            }
            s2 = s;
            if(s1 == null || s1.length() == 0)
            {
                s1 = "";
            }
            if(!flag)
            {
                s3 = (java.lang.String)hashmapordered.get("_parent");
            }
            hashmapordered.put("_name", "config");
            if(s3 != null && s3.length() != 0)
            {
                jgl.Array array1 = ReadGroupFrames(s3);
                java.util.Enumeration enumeration1 = array1.elements();
                enumeration1.nextElement();
                int i = findSubGroupIndex(array1, s4);
                array1.remove(i);
                WriteGroupFrames(s3, array1);
            }
            if(!s4.equals(s))
            {
                hashmapordered.put("_name", s4);
            }
            hashmapordered.put("_parent", s1);
            if(s1 != null && s1.length() > 0)
            {
                try
                {
                    jgl.Array array2 = ReadGroupFrames(s1);
                    jgl.HashMap hashmap1 = (jgl.HashMap)array2.at(0);
                    jgl.HashMap hashmap2 = new HashMap();
                    java.lang.String s5 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_nextID");
                    if(s5.length() == 0)
                    {
                        s5 = "1";
                    }
                    hashmap2.put("_id", s5);
                    hashmap2.put("_class", "SubGroup");
                    hashmap2.put("_group", s);
                    java.lang.String s6 = com.dragonflow.Utils.TextUtils.increment(s5);
                    hashmap1.put("_nextID", s6);
                    hashmap2.put("_name", s4);
                    array2.insert(array2.size(), hashmap2);
                    WriteGroupFrames(s1, array2);
                }
                catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception1)
                {
                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_CREATE_EXCEPTION, new java.lang.String[] {
                        siteviewexception1.toString()
                    });
                }
            }
            updateConfig("_dependsOn", "", hashmap, hashmapordered);
            updateConfig("_dependsCondition", "good", hashmap, hashmapordered);
            updateConfig("_httpCharSet", "", hashmap, hashmapordered);
            updateConfig("__template", "", hashmap, hashmapordered);
            updateConfig("_description", "", hashmap, hashmapordered);
            try
            {
                removeAlertContextProperties(array);
                WriteGroupFrames(s, array);
                com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
                detectconfigurationchange.setConfigChangeFlag();
            }
            catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception2)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_CREATE, new java.lang.String[] {
                    siteviewexception2.getMessage()
                });
            }
            try
            {
                copySubGroups(s);
            }
            catch(java.lang.Exception exception1)
            {
                throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_COPY_SUBGROUP, new java.lang.String[] {
                    exception1.getMessage()
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "moveGroup"
            }, 0L, exception.getMessage());
        }
        return s2;
    }

    private void removeAlertContextProperties(jgl.Array array)
    {
        boolean flag = false;
        for(int i = 0; i < array.size(); i++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)array.at(i);
            jgl.Array array1 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "_alertCondition");
            java.util.HashMap hashmap1 = new java.util.HashMap();
            for(int j = 0; j < array1.size(); j++)
            {
                hashmap1.clear();
                com.dragonflow.Api.Alert.getInstance().parseCondition((java.lang.String)array1.at(j), hashmap1);
                if(hashmap1.get("_UIContext") != null)
                {
                    hashmap1.put("_UIContext", "");
                    array1.put(j, com.dragonflow.Api.Alert.getInstance().createCondStr(hashmap1));
                    flag = true;
                }
            }

            if(flag)
            {
                hashmap.put("_alertCondition", array1);
            }
        }

    }

    private void copySubGroups(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            jgl.Array array = new Array();
            jgl.Array array1 = ReadGroupFrames(s);
            java.util.Enumeration enumeration = array1.elements();
            boolean flag = false;
            while (enumeration.hasMoreElements()) {
                jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                if(com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap) && hashmap.get("_class").equals("SubGroup"))
                {
                    java.lang.String s1 = com.dragonflow.Utils.I18N.toDefaultEncoding(com.dragonflow.Utils.TextUtils.getValue(hashmap, "_group"));
                    jgl.Array array2 = ReadGroupFrames(s1);
                    s1 = computeGroupName(s1);
                    if(array2.size() > 0)
                    {
                        jgl.HashMap hashmap1 = (jgl.HashMap)array2.at(0);
                        java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_name");
                        if(s3 != null && s3.length() > 0 && s3.equalsIgnoreCase("config"))
                        {
                            hashmap1.put("_name", com.dragonflow.Utils.TextUtils.getValue(hashmap, "_name"));
                        }
                        hashmap1.put("_parent", s);
                        WriteGroupFrames(s1, array2);
                        hashmap.put("_group", s1);
                        array.add(s1);
                        flag = true;
                    }
                }
            } 
            
            if(flag)
            {
                WriteGroupFrames(s, array1);
            }
            java.lang.String s2;
            for(java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); copySubGroups(s2))
            {
                s2 = (java.lang.String)enumeration1.nextElement();
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "copySubGroups"
            }, 0L, exception.getMessage());
        }
    }

    private void updateConfig(java.lang.String s, java.lang.String s1, jgl.HashMap hashmap, jgl.HashMap hashmap1)
    {
        java.lang.String s2 = "";
        java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, s);
        if(s3 != null && s3.length() > 0)
        {
            s2 = s3;
        } else
        {
            java.lang.String s4 = (java.lang.String)hashmap1.get(s);
            if(s4 == null || s4.length() == 0)
            {
                s2 = s1;
            }
        }
        if(s2 != null && s2.length() > 0)
        {
            if(s.equals("_description"))
            {
                updateDescription(hashmap1, s2);
            } else
            {
                hashmap1.put(s, s2);
            }
        }
    }

    private void updateDescription(jgl.HashMap hashmap, java.lang.String s)
    {
        hashmap.remove("_description");
        jgl.Array array = com.dragonflow.SiteView.Platform.split('\n', s);
        for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); hashmap.add("_description", enumeration.nextElement())) { }
    }

    private boolean exceedsLicenseLimit(jgl.Array array, java.lang.String s)
    {
        boolean flag = com.dragonflow.Utils.LUtils.wouldExceedLimit(array, s);
        return flag;
    }

    private jgl.Array getReportFrameList()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        jgl.Array array = new Array();
        try
        {
            if(!com.dragonflow.SiteView.Platform.isStandardAccount(account))
            {
                array = ReadGroupFrames(account);
            } else
            {
                array = com.dragonflow.Properties.FrameFile.readFromFile(com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "groups" + java.io.File.separator + "history.config");
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            array = new Array();
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "getReportFrameList"
            }, 0L, exception.getMessage());
        }
        return array;
    }

    private int findSubGroupIndex(jgl.Array array, java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Enumeration enumeration = array.elements();
        int i = 0;
        enumeration.nextElement();
        i++;
        int j = -1;
        for(; enumeration.hasMoreElements(); i++)
        {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            if(!com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap))
            {
                continue;
            }
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_group");
            if(s1.length() == 0 || !s1.equals(s))
            {
                continue;
            }
            j = i;
            break;
        }

        if(j == -1)
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_SUBGROUP_NOT_FOUND, new java.lang.String[] {
                "APIGroup", "getPropertiesForGroupInstance", s
            });
        } else
        {
            return j;
        }
    }

    private void saveReportFrameList(jgl.Array array, java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(!com.dragonflow.SiteView.Platform.isStandardAccount(s))
            {
                WriteGroupFrames(s, array);
            } else
            {
                com.dragonflow.Properties.FrameFile.writeToFile(com.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "groups" + java.io.File.separator + "history.config", array);
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_EXCEPTION, new java.lang.String[] {
                "APIGroup", "saveReportFrameList"
            }, 0L, exception.getMessage());
        }
    }

    private void deleteGroupFromReport()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        deleteMonitorFromReport();
    }

    private void deleteMonitorFromReport()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            jgl.Array array = new Array();
            jgl.Array array1 = getReportFrameList();
            java.util.Enumeration enumeration = array1.elements();
            while (enumeration.hasMoreElements()) {
                jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                if(!com.dragonflow.SiteView.Monitor.isReportFrame(hashmap))
                {
                    array.add(hashmap);
                } else
                {
                    jgl.HashMap hashmap1 = copyHashMap(hashmap);
                    hashmap1.remove("monitors");
                    java.util.Enumeration enumeration1 = hashmap.values("monitors");
                    while (enumeration1.hasMoreElements()) {
                        java.lang.String s = (java.lang.String)enumeration1.nextElement();
                        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s);
                        if(as.length >= 1)
                        {
                            hashmap1.add("monitors", s);
                        }
                    }
                    enumeration1 = hashmap1.values("monitors");
                    if(enumeration1.hasMoreElements())
                    {
                        array.add(hashmap1);
                    }
                }
            } 
            saveReportFrameList(array, account);
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "deleteMonitorFromReport"
            }, 0L, exception.getMessage());
        }
    }

    private jgl.HashMap copyHashMap(jgl.HashMap hashmap)
    {
        java.lang.Object obj;
        if(hashmap instanceof com.dragonflow.Properties.HashMapOrdered)
        {
            obj = new HashMapOrdered(true);
        } else
        {
            obj = new HashMap();
        }
        java.lang.Object obj1;
        for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements(); ((jgl.HashMap) (obj)).put(obj1, hashmap.get(obj1)))
        {
            obj1 = enumeration.nextElement();
        }

        return ((jgl.HashMap) (obj));
    }

    private void deleteGroupInternal(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("DELETING GROUP " + s);
            }
            java.io.File file = new File(getGroupFilePath(s, ".mg"));
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("DELETING GROUP IN FILE " + file);
            }
            if(!file.exists())
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_ID_NOT_VALID, new java.lang.String[] {
                    s
                });
            }
            jgl.Array array = getGroupFrames(s);
            java.util.Enumeration enumeration = array.elements();
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_parent");
            if(s1.length() != 0)
            {
                jgl.Array array1 = getGroupFrames(s1);
                int i = findSubGroupIndex(array1, s);
                if(i >= 1)
                {
                    array1.remove(i);
                }
            }
            jgl.Array array2 = new Array();
            jgl.Array array3 = new Array();
            while (enumeration.hasMoreElements()) {
                jgl.HashMap hashmap1 = (jgl.HashMap)enumeration.nextElement();
                java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_class");
                if(s2.equals("SubGroup"))
                {
                    java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_group");
                    if(s3.length() != 0)
                    {
                        array2.add(s3);
                    }
                } else
                {
                    com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                    java.lang.String s4 = com.dragonflow.Utils.TextUtils.getValue(hashmap1, "_id");
                    java.lang.String s5 = com.dragonflow.Utils.I18N.toDefaultEncoding(s + com.dragonflow.SiteView.SiteViewGroup.ID_SEPARATOR + s4);
                    com.dragonflow.SiteView.AtomicMonitor atomicmonitor = (com.dragonflow.SiteView.AtomicMonitor)siteviewgroup.getElement(s5);
                    if(atomicmonitor != null)
                    {
                        if(!s2.equals("SubGroup"))
                        {
                            siteviewgroup.notifyMonitorDeletion(atomicmonitor);
                        }
//                        if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered() && !s2.equals("SubGroup"))
//                        {
//                            array3.add(atomicmonitor);
//                        }
                    }
                }
            } 
//            if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                java.lang.StringBuffer stringbuffer = new StringBuffer();
//                com.dragonflow.SiteView.TopazConfigurator.updateTopaz(array3, 1, stringbuffer, false, null);
//                if(stringbuffer.length() > 0)
//                {
//                    com.dragonflow.Log.LogManager.log("Topaz", " Error occurred during delete of group in " + com.dragonflow.SiteView.TopazInfo.getTopazName() + " " + stringbuffer);
//                }
//            }
            for(int j = 0; j < array2.size(); j++)
            {
                deleteGroupInternal((java.lang.String)array2.at(j));
            }

            if(com.dragonflow.Properties.JdbcConfig.configInDB())
            {
                com.dragonflow.Properties.JdbcConfig.deleteGroupFromDB(s);
            }
//            if(com.dragonflow.SiteView.TopazConfigurator.configInTopazAndRegistered())
//            {
//                com.dragonflow.SiteView.TopazConfigurator.deleteGroupFromTopaz(s);
//            }
            deleteGroupFromReport();
            if(debug)
            {
                com.dragonflow.Utils.TextUtils.debugPrint("DELETING FILE " + file);
            }
            file.delete();
            java.io.File file1 = new File(getGroupFilePath(s, ".mg.bak"));
            if(file1.exists())
            {
                file1.delete();
            }
            java.io.File file2 = new File(getGroupFilePath(s, ".dyn"));
            if(file2.exists())
            {
                file2.delete();
            }
            java.io.File file3 = new File(getGroupFilePath(s, ".dyn.bak"));
            if(file3.exists())
            {
                file3.delete();
            }
            groups.remove(s);
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(java.lang.Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_GROUP_EXCEPTION, new java.lang.String[] {
                "APIGroup", "deleteGroupInternal"
            }, 0L, exception.getMessage());
        }
    }

    private java.lang.String computeGroupName(java.lang.String s)
    {
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        jgl.Array array = siteviewgroup.getGroupFileIDs();
        java.lang.String s1 = s.toUpperCase() + ".";
        int i = -1;
        java.util.Enumeration enumeration = array.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String)enumeration.nextElement();
            s2 = s2.toUpperCase() + '.';
            if(s2.startsWith(s1))
            {
                int j = com.dragonflow.Utils.TextUtils.readInteger(s2, s1.length());
                if(j < 0)
                {
                    j = 0;
                }
                if(j > i)
                {
                    i = j;
                }
            }
        } 
        
        if(i++ >= 0)
        {
            s = s + "." + i;
        }
        return s;
    }

    public boolean hasSubGroupDependencies(java.lang.String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        java.util.Collection collection = getChildGroupInstances(s);
        return collection != null && collection.size() > 0;
    }
}
