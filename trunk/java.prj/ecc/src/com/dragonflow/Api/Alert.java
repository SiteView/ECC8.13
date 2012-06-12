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

import java.util.HashMap;
import java.util.HashSet;
import java.util.Vector;

import com.dragonflow.SiteViewException.SiteViewParameterException;

// Referenced classes of package com.dragonflow.Api:
// APISiteView

public class Alert
    implements com.dragonflow.SiteView.IObjectWithUniqueId
{

    private static java.util.Map alertMap = null;
    public static final java.lang.String MASTER = "_master";
    public static final java.lang.String CONFIG = "_config";
    public static final int EXPR_IDX = 0;
    public static final int ACTION_IDX = 1;
    public static final int ID_IDX = 2;
    public static final int INCLUDE_FILTER_IDX = 3;
    public static final java.lang.String EXPR = "_expr";
    public static final java.lang.String ACTION = "_action";
    public static final java.lang.String ID = "_id";
    public static final java.lang.String INCLUDE_FILTER = "_includeFilter";
    public static final java.lang.String UI_CONTEXT = "_UIContext";
    public static final java.lang.String NAME = "_name";
    public static final java.lang.String TARGET_LIST = "_targetList";
    public static final java.lang.String UNIQUE_ID = "_uniqueID";
    public static final java.lang.String COND_SEPARATOR = "\t";
    public static final char COND_SEPARATOR_CHAR = 9;
    public static final java.lang.String TARGET_LIST_SEPARATOR = ",";
    public static final java.lang.String TARGET_SEPARATOR = " ";
    public static final java.lang.String DEFAULT_NAME = "Alert";
    public static final java.lang.String ALERT_COND_PROP_NAME = "_alertCondition";
    private static com.dragonflow.Api.Alert _alertSingleton;
    private java.lang.String _group;
    private java.lang.String _monitorID;
    private java.lang.String _condStr;
    private java.util.Map _condMap;
    private com.dragonflow.SiteView.Monitor _monitor;
    private com.dragonflow.SiteView.MonitorGroup _parentGroup;
    private long _ID;
    private java.lang.String _name;
    private java.lang.String _context;
    private java.lang.String _includeFilter;
    static final boolean $assertionsDisabled; /* synthetic field */

    public com.dragonflow.Api.Alert createAlert(java.lang.String as[])
    {
        return new Alert(as);
    }

    public static com.dragonflow.Api.Alert getInstance()
    {
        if(_alertSingleton == null)
        {
            _alertSingleton = new Alert();
            alertMap = new HashMap();
        }
        return _alertSingleton;
    }

    Alert()
    {
        _group = "";
        _monitorID = "";
        _condStr = "";
        _condMap = null;
        _monitor = null;
        _parentGroup = null;
        _ID = -666L;
        _name = "";
        _context = "";
        _includeFilter = "";
    }

    private Alert(java.lang.String s)
    {
        _group = "";
        _monitorID = "";
        _condStr = "";
        _condMap = null;
        _monitor = null;
        _parentGroup = null;
        _ID = -666L;
        _name = "";
        _context = "";
        _includeFilter = "";
        setID(s);
    }

    private Alert(java.lang.String as[])
    {
        _group = "";
        _monitorID = "";
        _condStr = "";
        _condMap = null;
        _monitor = null;
        _parentGroup = null;
        _ID = -666L;
        _name = "";
        _context = "";
        _includeFilter = "";
        setID(com.dragonflow.ConfigurationManager.InternalIdsManager.getInstance().getNextSiteviewId());
        processTargetList(as);
    }

    public void update(java.lang.String as[])
    {
        processTargetList(as);
    }

    public java.lang.String createTargetListStr(com.dragonflow.Api.Alert alert)
    {
        if(alert == null)
        {
            throw new IllegalArgumentException("alert cannot be null");
        }
        java.lang.String s;
        if(alert.getGroup().equals("_master"))
        {
            if(alert.getIncludeFilter().length() > 0)
            {
                s = alert.getIncludeFilter();
            } else
            {
                s = "_master";
            }
        } else
        if(alert.getMonitorID().equals("_config"))
        {
            if(alert.getIncludeFilter().length() > 0)
            {
                s = alert.getIncludeFilter();
            } else
            {
                s = alert.getGroup();
            }
        } else
        {
            s = alert.getGroup() + ' ' + alert.getMonitorID();
        }
        return s;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param l
     * @return
     */
    public com.dragonflow.Api.Alert getByID(long l)
    {
        synchronized (alertMap) {
        if(l < 0L)
        {
            throw new IllegalArgumentException("alertID must be > 0.");
        }
        return (com.dragonflow.Api.Alert)alertMap.get(new Long(l));
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param alert
     */
    public void addToMap(com.dragonflow.Api.Alert alert)
    {
        synchronized(alertMap)
        {
            if(null == alert)
            {
                throw new IllegalArgumentException("null alert passed.");
            }
            if(!$assertionsDisabled && getByID(alert.getID()) != null)
            {
                throw new AssertionError();
            }
            alertMap.put(new Long(alert.getID()), alert);
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    public static boolean hasValidTargetList(java.lang.String s)
    {
        java.lang.String as[];
        if(s == null || s.length() == 0)
        {
            return false;
        }
        as = com.dragonflow.Utils.TextUtils.split(s, ",");
        if(!$assertionsDisabled && as[0].equals("_master") && as.length > 1)
        {
            throw new AssertionError();
        }
        if(as.length == 1 && as[0].equals("_master"))
        {
            return true;
        }

        for (int i = 0; i < as.length; i ++) {

        java.lang.String as1[];
        java.lang.String s1 = as[i];
        as1 = com.dragonflow.Utils.TextUtils.split(s1, ",");
        int j = as1.length;
        if(j < 1 || j > 2)
        {
            return false;
        }
        for(int k = 0; k < j; k++)
        {
            if(as1[k].length() == 0)
            {
                return false;
            }
        }

        if(j != 2)
        {
            continue;
        }
        
        try {
        int l = java.lang.Integer.parseInt(as1[1]);
        if(l < 0)
        {
            return false;
        }
        }
        catch (java.lang.NumberFormatException numberformatexception) {
        return false;
        }
        }
        return true;
    }

    public void removeFromMap(com.dragonflow.Api.Alert alert)
    {
        synchronized(alertMap)
        {
            alertMap.remove(new Long(alert.getID()));
        }
    }

    public java.lang.String getGroup()
    {
        return _group;
    }

    public java.lang.String getMonitorID()
    {
        return _monitorID;
    }

    public java.lang.String getIDStr()
    {
        return java.lang.Long.toString(_ID);
    }

    public java.lang.String getName()
    {
        return _name;
    }

    public java.lang.String getActionStr()
    {
        return (java.lang.String)_condMap.get("_action");
    }

    public java.lang.String getExpressionStr()
    {
        return (java.lang.String)_condMap.get("_expr");
    }

    public void setName(java.lang.String s)
    {
        if(s == null)
        {
            throw new IllegalArgumentException("alert name cannot be set to null.");
        } else
        {
            _name = s;
            return;
        }
    }

    public java.lang.String getContext()
    {
        return _context;
    }

    public void setContext(java.lang.String s)
    {
        if(s == null)
        {
            throw new IllegalArgumentException("alert context cannot be set to null.");
        }
        if(s.equals(""))
        {
            s = "_master";
        }
        _context = s;
    }

    public java.lang.String getIncludeFilter()
    {
        return _includeFilter;
    }

    private void processTargetList(java.lang.String as[])
    {
        if(as == null)
        {
            throw new IllegalArgumentException("targetList cannot be null");
        }
        java.lang.String s = "";
        setGroup("");
        setMonitorID("");
        setIncludeFilter("");
        java.lang.String s1 = "";
        java.lang.String s2 = "";
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s5 = as[i].trim();
            if(s5.equals("_master"))
            {
                s1 = "_master";
                s2 = "_config";
                break;
            }
            java.lang.String s3 = "_config";
            java.lang.String s4 = s5;
            int j = s5.indexOf(" ");
            if(j != -1)
            {
                s4 = s5.substring(0, j);
                s3 = s5.substring(j + 1);
            }
            if(s1.length() == 0)
            {
                s1 = s4;
                s2 = s3;
                continue;
            }
            if(!s1.equals(s4))
            {
                s = createIncludeFilter(s, s1, s2, s4, s3);
                s1 = "_master";
                s2 = "_config";
            } else
            {
                s = createIncludeFilter(s, s1, s2, s4, s3);
                s2 = "_config";
            }
        }

        setGroup(s1);
        setMonitorID(s2);
        if(s.length() > 0)
        {
            if(s.endsWith(","))
            {
                s = s.substring(0, s.length() - 1);
            }
            setIncludeFilter(s);
        }
        setContext(com.dragonflow.Api.APISiteView.getContext(as, getContext()));
    }

    private java.lang.String createIncludeFilter(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4)
    {
        if(s4.equals("_config"))
        {
            s4 = "";
        }
        if(s2.equals("_config"))
        {
            s2 = "";
        }
        if(0 == s.length())
        {
            s = s1 + " " + s2 + "," + s3 + " " + s4;
        } else
        {
            s = s + "," + s3 + " " + s4;
        }
        return s;
    }

    private void parsePre79Condition(java.lang.String s, java.util.Map map)
    {
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, "\t");
        if(!$assertionsDisabled && as.length <= 2)
        {
            throw new AssertionError();
        }
        java.lang.String s1 = as[0];
        java.lang.String s2 = as[1];
        java.lang.String s3 = as[2];
        java.lang.String s4 = "";
        if(as.length > 3 && !as[3].startsWith("_UIContext") && !as[3].startsWith("_name"))
        {
            s4 = as[3];
        }
        if(!$assertionsDisabled && s1 == null)
        {
            throw new AssertionError();
        }
        map.put("_expr", s1);
        if(!$assertionsDisabled && s2 == null)
        {
            throw new AssertionError();
        }
        map.put("_action", s2);
        if(!$assertionsDisabled && s3 == null)
        {
            throw new AssertionError();
        } else
        {
            map.put("_id", s3);
            map.put("_includeFilter", s4);
            return;
        }
    }

    public void parseCondition(java.lang.String s, java.util.Map map)
    {
        parsePre79Condition(s, map);
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, "\t");
        map.put("_UIContext", "");
        map.put("_name", "");
        if(as.length > 2)
        {
            for(int i = 3; i < as.length; i++)
            {
                java.lang.String s1 = as[i];
                if(s1.startsWith("_UIContext="))
                {
                    map.put("_UIContext", s1.substring("_UIContext".length() + 1));
                    continue;
                }
                if(s1.startsWith("_name="))
                {
                    map.put("_name", s1.substring("_name".length() + 1));
                }
            }

        }
    }

    public java.lang.String getGroupNameFromPath(java.lang.String s)
    {
        if(!$assertionsDisabled && s == null)
        {
            throw new AssertionError();
        }
        int i = 0;
        int j = s.length();
        int k = s.lastIndexOf(java.io.File.separator);
        if(k != -1)
        {
            i = k + 1;
        }
        int l = s.lastIndexOf(".mg");
        if(l != -1)
        {
            j = l;
        }
        if(!$assertionsDisabled && (i >= j || j >= s.length()))
        {
            throw new AssertionError();
        } else
        {
            return s.substring(i, j);
        }
    }

    private com.dragonflow.Api.Alert createAlertFromPropertyMap(java.lang.String s, java.lang.String s1, java.util.Map map)
    {
        com.dragonflow.Api.Alert alert = new Alert((java.lang.String)map.get("_id"));
        alert.setGroup(s);
        alert.setIncludeFilter((java.lang.String)map.get("_includeFilter"));
        alert.setMonitorID(s1);
        java.lang.String s2 = (java.lang.String)map.get("_UIContext");
        alert.setContext(s2);
        alert.setName((java.lang.String)map.get("_name"));
        alert.setCondMap(map);
        return alert;
    }

    public void replaceAlertCondProp(com.dragonflow.SiteView.Monitor monitor, jgl.Array array)
    {
        monitor.unsetProperty("_alertCondition");
        for(int i = 0; i < array.size(); i++)
        {
            monitor.addProperty("_alertCondition", (java.lang.String)array.at(i));
        }

    }

    public java.lang.String createCondStr(java.util.Map map)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append(map.get("_expr") + "\t");
        stringbuffer.append(map.get("_action") + "\t");
        stringbuffer.append(map.get("_id") + "\t");
        java.lang.String s = (java.lang.String)map.get("_includeFilter");
        if(0 < s.length())
        {
            stringbuffer.append(s + "\t");
        }
        java.lang.String s1 = (java.lang.String)map.get("_UIContext");
        if(s1 != null)
        {
            stringbuffer.append("_UIContext=" + map.get("_UIContext") + "\t");
        }
        java.lang.String s2 = (java.lang.String)map.get("_name");
        if(s2 != null)
        {
            stringbuffer.append("_name=" + map.get("_name"));
        }
        return stringbuffer.toString();
    }

    public java.lang.String assignUniqueID(java.util.Map map, long l)
    {
        if(!$assertionsDisabled && null == map)
        {
            throw new AssertionError();
        } else
        {
            map.put("_id", java.lang.Integer.toString((int)l));
            return createCondStr(map);
        }
    }

    private void setGroup(java.lang.String s)
    {
        if(s == null)
        {
            throw new IllegalArgumentException("alert group cannot be set to null.");
        } else
        {
            _group = s;
            return;
        }
    }

    private void setMonitorID(java.lang.String s)
    {
        if(s == null)
        {
            throw new IllegalArgumentException("alert monitorID cannot be null.");
        } else
        {
            _monitorID = s;
            return;
        }
    }

    private long getID()
    {
        return _ID;
    }

    private void setID(java.lang.String s)
    {
        if(s == null || s.length() == 0)
        {
            throw new IllegalArgumentException("alert ID must not be null or zero length.");
        }
        long l;
        try
        {
            l = java.lang.Long.parseLong(s);
        }
        catch(java.lang.NumberFormatException numberformatexception)
        {
            throw new IllegalArgumentException("alert ID must be a numeric string.");
        }
        setID(l);
    }

    private void setID(long l)
    {
        if(l < 0L)
        {
            throw new IllegalArgumentException("alert ID must be >= 0.");
        } else
        {
            _ID = l;
            return;
        }
    }

    private void setIncludeFilter(java.lang.String s)
    {
        if(s == null)
        {
            throw new IllegalArgumentException("alert includeFilter cannot be set to null.");
        } else
        {
            _includeFilter = s;
            return;
        }
    }

    public com.dragonflow.SiteView.Monitor getMonitor()
    {
        return _monitor;
    }

    public void setMonitor(com.dragonflow.SiteView.Monitor monitor)
    {
        _monitor = monitor;
    }

    public com.dragonflow.SiteView.SiteViewObject getParentGroup()
    {
        return _parentGroup;
    }

    public void setParentGroup(com.dragonflow.SiteView.MonitorGroup monitorgroup)
    {
        _parentGroup = monitorgroup;
    }

    public int getUniqueInternalId()
    {
        return (int)getID();
    }

    public void setUniqueInternalId(int i)
    {
        jgl.Array array = _monitor.getProperties("_alertCondition");
        int j = findIdxOfMatchingAlert(array, getCondStr());
        if(!$assertionsDisabled && j == -1)
        {
            throw new AssertionError();
        } else
        {
            java.util.HashMap hashmap = new HashMap();
            parseCondition((java.lang.String)array.at(j), hashmap);
            java.lang.String s = assignUniqueID(hashmap, i);
            array.put(j, s);
            setCondStr(s, array);
            setID(i);
            return;
        }
    }

    private int findIdxOfMatchingAlert(jgl.Array array, java.lang.String s)
    {
        int i = -1;
        int j = 0;
        do
        {
            if(j >= array.size())
            {
                break;
            }
            java.lang.String s1 = (java.lang.String)array.at(j);
            if(s1.equals(s))
            {
                i = j;
                break;
            }
            j++;
        } while(true);
        return i;
    }

    public void getAlerts(com.dragonflow.SiteView.MonitorGroup monitorgroup, com.dragonflow.SiteView.Monitor monitor, java.util.Vector vector, java.util.Set set)
    {
        if(!$assertionsDisabled && vector == null)
        {
            throw new AssertionError();
        }
        if(monitor == null)
        {
            monitor = monitorgroup;
        }
        jgl.Array array = monitor.getProperties("_alertCondition");
        java.lang.String s = monitor.getProperty("_id");
        java.lang.String s1 = "";
        if(s.equals("SiteView"))
        {
            s1 = "_master";
            s = "_config";
        } else
        {
            s1 = getGroupNameFromPath(monitorgroup.getFile().getPath());
        }
        if(s1.equals(s))
        {
            s = "_config";
        }
        monitor.unsetProperty("_alertCondition");
        for(int i = 0; i < array.size(); i++)
        {
            java.lang.String s2 = (java.lang.String)array.at(i);
            java.util.HashMap hashmap = new HashMap();
            parseCondition(s2, hashmap);
            com.dragonflow.Api.Alert alert = createAlertFromPropertyMap(s1, s, hashmap);
            alert.setMonitor(monitor);
            alert.setParentGroup(monitorgroup);
            java.lang.String s3 = s2;
            if(set != null && hasOldConditionFormat(hashmap))
            {
                s3 = createNewFormatCondStrFromPropMap(hashmap, alert);
                array.put(i, s3);
                set.add(monitorgroup);
            }
            alert.setCondStr(s3);
            vector.add(alert);
        }

    }

    private java.lang.String createNewFormatCondStrFromPropMap(java.util.Map map, com.dragonflow.Api.Alert alert)
    {
        map.put("_name", "Alert");
        java.lang.String s1 = com.dragonflow.Api.APISiteView.getContext(com.dragonflow.Utils.TextUtils.split(createTargetListStr(alert), ","), null);
        if(s1.equals(""))
        {
            s1 = "_master";
        }
        map.put("_UIContext", s1);
        java.lang.String s = createCondStr(map);
        return s;
    }

    private boolean hasOldConditionFormat(java.util.Map map)
    {
        return map.get("_UIContext") == null || ((java.lang.String)map.get("_UIContext")).length() == 0;
    }

    public void updateAlertMap(java.util.Vector vector)
    {
        synchronized(alertMap)
        {
            alertMap.clear();
            com.dragonflow.Api.Alert alert;
            for(java.util.Iterator iterator = vector.iterator(); iterator.hasNext(); alertMap.put(new Long(alert.getID()), alert))
            {
                alert = (com.dragonflow.Api.Alert)iterator.next();
            }

        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    public boolean groupHasAlerts(java.lang.String s)
    {
        synchronized (alertMap) {
        boolean flag;
        if(!$assertionsDisabled && s == null)
        {
            throw new AssertionError();
        }
        java.util.Iterator iterator = alertMap.values().iterator();
        flag = false;
        while (iterator.hasNext())
            {
            com.dragonflow.Api.Alert alert = (com.dragonflow.Api.Alert)iterator.next();
            java.lang.String s1 = getGroupNameFromPath(((com.dragonflow.SiteView.MonitorGroup)alert.getParentGroup()).getFile().getPath());
            if(s1.equals(s))
            {
            flag = true;
            break;
            }
        }
        return flag;
        }

    }

    public java.lang.String getCondStr()
    {
        return _condStr;
    }

    private void setCondMap(java.util.Map map)
    {
        _condMap = map;
    }

    public void setCondStr(java.lang.String s)
    {
        _condStr = s;
        _monitor.addProperty("_alertCondition", s);
    }

    public void setCondStr(java.lang.String s, jgl.Array array)
    {
        _condStr = s;
        _monitor.unsetProperty("_alertCondition");
        for(int i = 0; i < array.size(); i++)
        {
            _monitor.addProperty("_alertCondition", (java.lang.String)array.at(i));
        }

    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @return
     */
    public java.util.Vector getAlertsByTarget(java.lang.String s) {
        synchronized (alertMap) {
            java.util.Vector vector;
            java.util.Iterator iterator;
            vector = new Vector();
            iterator = alertMap.values().iterator();
            s = s.trim();

            while(iterator.hasNext()) {
            com.dragonflow.Api.Alert alert = (com.dragonflow.Api.Alert)iterator.next();
            java.lang.String s1 = createTargetListStr(alert);
            String[] as = com.dragonflow.Utils.TextUtils.split(s1, ",");
    
                for (int i = 0; i < as.length; i ++) {
                    java.lang.String s2 = as[i].trim();
                    if(s2.equals(s)) {
                        vector.add(alert);
                    }
                }
            }
            return vector;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @return
     */
    public java.util.Vector getAlertsResidingInGroupOrMonitor(java.lang.String s, java.lang.String s1)
    {
        if(!$assertionsDisabled && s == null)
        {
            throw new AssertionError();
        }
        if(s.length() == 0)
        {
            s = "_master";
        }
        java.util.Vector vector = new Vector();
        synchronized (alertMap) {
        java.util.Iterator iterator = alertMap.keySet().iterator();
        while (iterator.hasNext())
            {
            com.dragonflow.Api.Alert alert = (com.dragonflow.Api.Alert)alertMap.get(iterator.next());
            com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)alert.getParentGroup();
            java.lang.String s2 = monitorgroup.getProperty(com.dragonflow.SiteView.MonitorGroup.pID);
            if(s2.equals("SiteView"))
            {
                s2 = "_master";
            }
            if(s2.equals(s))
            {
                if(s1 != null && s1.length() > 0)
                {
                    if(alert.getMonitorID().equals(s1))
                    {
                        vector.add(alert);
                    }
                } else
                if(alert.getMonitorID().equals("_config"))
                {
                    vector.add(alert);
                }
            }
        } 
        return vector;
        }

    }

    public java.util.Vector getAlertsAssociatedWithGroupOrMonitor(java.lang.String s, java.lang.String s1)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        if(s == null || s.equals(""))
        {
            return new Vector(alertMap.values());
        }
        java.util.Vector vector = new Vector();
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        com.dragonflow.SiteView.MonitorGroup monitorgroup = siteviewgroup.getGroup(s);
        if(monitorgroup == null)
        {
            throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_GROUP_SUBGROUP_NOT_FOUND, new java.lang.String[] {
                s
            });
        }
        if(s1 != null && !s1.equals(""))
        {
            vector.addAll(getAlertsResidingInGroupOrMonitor(s, s1));
        }
        java.util.HashSet hashset = new HashSet();
        if(s1 == null || s1.equals(""))
        {
            java.util.HashSet hashset1 = new HashSet();
            hashset1.add(monitorgroup);
            java.util.Vector vector1 = new Vector();
            com.dragonflow.SiteView.ConfigurationChanger.getGroupsMonitors(hashset1, null, vector1, true);
            hashset.add(s);
            for(int i = 0; i < vector1.size(); i++)
            {
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)vector1.elementAt(i);
                hashset.add(monitor.getProperty("_id"));
            }

            getAlertsApplyingToAnyOf(hashset, vector);
        }
        java.util.HashSet hashset2 = new HashSet();
        hashset2.add(monitorgroup.getProperty("_id"));
        for(com.dragonflow.SiteView.SiteViewObject siteviewobject = monitorgroup.getParent(); siteviewobject != null;)
        {
            if((com.dragonflow.SiteView.SubGroup.class).isInstance(siteviewobject))
            {
                hashset2.add(siteviewobject.getProperty("_group"));
                siteviewobject = ((com.dragonflow.SiteView.SubGroup)siteviewobject).getParent();
            } else
            if((com.dragonflow.SiteView.MonitorGroup.class).isInstance(siteviewobject))
            {
                hashset2.add(siteviewobject.getProperty("_id"));
                siteviewobject = ((com.dragonflow.SiteView.MonitorGroup)siteviewobject).getParent();
            } else
            {
                siteviewobject = null;
            }
        }

        hashset2.add("_master");
        java.util.Vector vector2 = new Vector();
        java.lang.String s3;
        for(java.util.Iterator iterator = hashset2.iterator(); iterator.hasNext(); vector2.addAll(getAlertsResidingInGroupOrMonitor(s3, null)))
        {
            s3 = (java.lang.String)iterator.next();
        }

        java.lang.String s2 = s;
        if(s1 != null && !s1.equals(""))
        {
            s2 = s2 + " " + s1;
        }
        filterAlertsByTargetOrChildGroups(vector2, s2, hashset, vector);
        java.util.HashSet hashset3 = new HashSet(vector);
        java.util.Vector vector3 = new Vector(hashset3);
        return vector3;
    }

    private void filterAlertsByTargetOrChildGroups(java.util.Vector vector, java.lang.String s, java.util.Set set, java.util.Vector vector1)
    {
        for(int i = 0; i < vector.size(); i++)
        {
            com.dragonflow.Api.Alert alert = (com.dragonflow.Api.Alert)vector.elementAt(i);
            java.lang.String s1 = alert.getIncludeFilter();
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1, ",");
            java.util.HashSet hashset = new HashSet(java.util.Arrays.asList(as));
            if(s1.equals("") || hashset.contains(s))
            {
                vector1.add(alert);
                continue;
            }
            if(set.size() <= 0)
            {
                continue;
            }
            for(int j = 0; j < as.length; j++)
            {
                java.lang.String s2 = as[j];
                int k = s2.indexOf(" ");
                if(k != -1)
                {
                    s2 = s2.substring(0, k);
                }
                if(set.contains(s2))
                {
                    vector1.add(alert);
                }
            }

        }

    }

    private void getAlertsApplyingToAnyOf(java.util.Set set, java.util.Vector vector)
    {
        synchronized(alertMap)
        {
            java.util.Iterator iterator = alertMap.values().iterator();
            while (iterator.hasNext()) {
                com.dragonflow.Api.Alert alert = (com.dragonflow.Api.Alert)iterator.next();
                java.lang.String s = alert.getGroup();
                if(set.contains(s))
                {
                    vector.add(alert);
                }
            } 
        }
    }

    static 
    {
        $assertionsDisabled = !(com.dragonflow.Api.Alert.class).desiredAssertionStatus();
    }
}
