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

import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.Date;
import java.util.StringTokenizer;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.HashMapOrdered;
import com.dragonflow.SiteViewException.SiteViewOperationalException;
import com.dragonflow.SiteViewException.SiteViewParameterException;
import com.dragonflow.StandardPreference.RemoteNTInstancePreferences;
import com.dragonflow.StandardPreference.RemoteUnixInstancePreferences;

// Referenced classes of package com.dragonflow.Api:
// APISiteView, SSInstanceProperty, SSPropertyDetails, Alert,
// SSAlertInstance, SSStringReturnValue, APIAlertCacheManager

public class APIAlert extends APISiteView
{

    static final boolean $assertionsDisabled; /* synthetic field */
    static int alertAddID;
    static int alertAnyID;
    static int alertArtID;
    static int alertCustomID;
    static int alertDelID;
    static int alertDetailID;
    static int alertDoID;
    static int alertEditID;
    static int alertErrorID;
    static int alertForID;
    static int alertGoodID;
    static int alertGroupID;
    static int alertMailID;
    static int alertMailPrefsID;
    static int alertNameID;
    static int alertOnID;
    static int alertPageID;
    static int alertPagerPrefsID;
    static int alertRunID;
    static int alertSNMPID;
    static int alertSNMPPrefsID;
    static int alertTestMailID;
    static int alertTestPagerID;
    static int alertTestSNMPID;
    static int alertWarningID;
    public static final String DISABLED_EXPRESSION = "disabled and ";
    static String english[];
    static String french[];
    static int groupArtID;
    static int helpArtID;
    static int historyArtID;
    public static final String MASTER = "_master";
    public static String REMOTE_PREFIX = "remote:";
    static int siteviewArtID;
    public static final String SSPARAM_MACHINE = "_machine";
    static 
    {
        $assertionsDisabled = !(APIAlert.class).desiredAssertionStatus();
        alertArtID = 1;
        historyArtID = 2;
        helpArtID = 3;
        siteviewArtID = 4;
        groupArtID = 5;
        alertDetailID = 6;
        alertOnID = 7;
        alertForID = 8;
        alertDoID = 9;
        alertDelID = 10;
        alertEditID = 11;
        alertAddID = 12;
        alertPagerPrefsID = 13;
        alertMailPrefsID = 14;
        alertSNMPPrefsID = 15;
        alertTestMailID = 16;
        alertTestPagerID = 17;
        alertTestSNMPID = 18;
        alertErrorID = 19;
        alertWarningID = 20;
        alertGoodID = 21;
        alertRunID = 22;
        alertMailID = 23;
        alertPageID = 24;
        alertSNMPID = 25;
        alertCustomID = 26;
        alertAnyID = 27;
        alertGroupID = 28;
        alertNameID = 29;
        english = new String[100];
        english[alertArtID] = "alerts";
        english[historyArtID] = "reports";
        english[helpArtID] = "help";
        english[siteviewArtID] = "siteview";
        english[groupArtID] = "groups";
        english[alertDetailID] = "Alert Definitions";
        english[alertOnID] = "On";
        english[alertForID] = "For";
        english[alertDoID] = "Do";
        english[alertNameID] = "Name";
        english[alertDelID] = "Del";
        english[alertEditID] = "Edit an Alert by clicking the Edit link for the Alert.";
        english[alertAddID] = "Add";
        english[alertPagerPrefsID] = "Set Preferences</a> for Pager Alerts";
        english[alertMailPrefsID] = "Set Preferences</a> for Mail Alerts";
        english[alertSNMPPrefsID] = "Set Preferences</a> for SNMP Trap Alerts";
        english[alertTestPagerID] = "Send</a> a test alert to the pager";
        english[alertTestMailID] = "Send</a> a test alert using e-mail";
        english[alertTestSNMPID] = "Send</a> a test alert using SNMP";
        english[alertErrorID] = "error";
        english[alertWarningID] = "warning";
        english[alertGoodID] = "good";
        english[alertRunID] = "Run";
        english[alertMailID] = "Send Mail to";
        english[alertPageID] = "Send Page Message";
        english[alertSNMPID] = "Send SNMP Trap Message";
        english[alertCustomID] = "Custom";
        english[alertAnyID] = "any Monitor";
        english[alertGroupID] = "any Monitor in group";
        french = new String[100];
        french[alertArtID] = "alertsfr";
        french[historyArtID] = "reportsfr";
        french[helpArtID] = "helpfr";
        french[siteviewArtID] = "siteview";
        french[groupArtID] = "groupsfr";
        french[alertDetailID] = "Alerte D&eacute;taill&eacute;e";
        french[alertOnID] = "En";
        french[alertForID] = "Pour";
        french[alertDoID] = "Faire";
        french[alertNameID] = "nom";
        french[alertDelID] = "Effacer";
        french[alertEditID] = "Editer une Alerte en cliquant sur le nom de l'Alerte.";
        french[alertAddID] = "Ajouter";
        french[alertPagerPrefsID] = "Etablir les Pr&eacute;f&eacute;rences</a> des Alertes de Pager";
        french[alertMailPrefsID] = "Etablir les Pr&eacute;f&eacute;rences</a> des Alertes de E-mail";
        french[alertSNMPPrefsID] = "Etablir les Pr&eacute;f&eacute;rences</a> des Alertes de SNMP Trap";
        french[alertTestPagerID] = "Envoyer</a> une alerte d'essai au pager";
        french[alertTestMailID] = "Envoyer</a> une alerte d'essai par email";
        french[alertTestSNMPID] = "Envoyer</a> une alerte d'essai par SNMP trap";
        french[alertErrorID] = "erreur";
        french[alertWarningID] = "attention";
        french[alertGoodID] = "bon";
        french[alertRunID] = "Perform";
        french[alertMailID] = "Envoyer par email";
        french[alertPageID] = "Envoyer au pager";
        french[alertSNMPID] = "Envoyer par SNMP Trap";
        french[alertCustomID] = "Custom";
        french[alertAnyID] = "Tous les Monitors";
        french[alertGroupID] = "Tous les Monitors dans l'equipe";
    }

    String language[];

    public APIAlert()
    {
        language = english;
    }

    private boolean actionAllowed(String s)
    {
        boolean flag = false;
        if(user != null)
        {
            if(user.getProperty("_edit").length() > 0)
            {
                flag = true;
            } else
            {
                flag = user.getProperty(s).length() > 0;
            }
        }
        return flag;
    }

    public jgl.HashMap addCondition(Alert alert, String s)
    {
        return mungeCondition(alert, s);
    }

    public void addConditions(jgl.Array array, jgl.HashMap hashmap, String s, String s1)
    {
        com.dragonflow.Utils.I18N.test(s, 1);
        for(java.util.Enumeration enumeration = hashmap.values("_alertCondition"); enumeration.hasMoreElements();)
        {
            String s2 = (String)enumeration.nextElement();
            try
            {
                jgl.HashMap hashmap1 = parseCondition(s2, hashmap, s, s1);
                array.add(hashmap1);
            }
            catch(Exception exception) { }
        }

    }

    private Alert addUpdate(boolean flag, String s, String s1, SSInstanceProperty assinstanceproperty[], String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        Alert alert = null;
        try
        {
            if(!flag)
            {
                if(!Alert.hasValidTargetList(s1))
                {
                    throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_ALERT_INVALID_TARGET_LIST, new String[] {
                        s1
                    });
                }
            } else
            if(s1 == null)
            {
                s1 = "";
            }
            String as[] = com.dragonflow.Utils.TextUtils.split(s1, ",");
            com.dragonflow.SiteView.Action action;
            if(flag)
            {
                alert = Alert.getInstance().getByID(com.dragonflow.Utils.TextUtils.toLong(s));
                action = getAction(alert);
            } else
            {
                alert = Alert.getInstance().createAlert(as);
                Alert.getInstance().addToMap(alert);
                action = com.dragonflow.SiteView.Action.createAction(s2);
            }
            if(!$assertionsDisabled && alert == null)
            {
                throw new AssertionError();
            }
            if(!$assertionsDisabled && action == null)
            {
                throw new AssertionError();
            }
            jgl.HashMap hashmap = processToOtherProperties(assinstanceproperty);
            jgl.HashMap hashmap1 = new HashMap();
            if(action != null && (hashmap1 = editActionProperties(action, hashmap, flag)).size() == 0)
            {
                String s3 = action.getActionString();
                String s4 = packCondition(hashmap, s3, hashmap1);
                String s5 = (String)hashmap.get("_UIContext");
                if(s5 != null && s5.length() > 0 && s1.length() > 0)
                {
                    alert.setContext(APISiteView.getContext(as, alert.getContext()));
                }
                s5 = (String)hashmap.get("_name");
                if(s5 != null && s5.length() > 0)
                {
                    alert.setName(s5);
                }
                if(flag)
                {
                    removeCondition(alert);
                    if(s1.length() > 0)
                    {
                        alert.update(as);
                    }
                }
                addCondition(alert, s4);
            } else
            {
                java.util.Enumeration enumeration = hashmap1.elements();
                throw new Exception((String)enumeration.nextElement());
            }
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "addUpdate"
            }, 0L, exception.getMessage());
        }
        return alert;
    }

    private String conditionName(String s, jgl.HashMap hashmap, jgl.Array array)
    {
        String s2 = null;
        if(array.size() > 3)
        {
            s2 = (String)array.at(3);
            if(s2.startsWith("_UIContext"))
            {
                s2 = "";
            }
        }
        String s1;
        if(s.equals("_master"))
        {
            if(s2 != null && s2.length() > 0)
            {
                s1 = "multiple monitors";
            } else
            {
                s1 = "any monitor";
            }
        } else
        if(isGroup(hashmap))
        {
            if(s2 != null && s2.length() > 0)
            {
                s1 = "multiple monitors";
            } else
            {
                s1 = "any monitor in group";
            }
        } else
        {
            s1 = (String)hashmap.get("_name");
        }
        if(s1.equals("multiple monitors"))
        {
            com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
            StringBuffer stringbuffer = new StringBuffer();
            jgl.Array array1 = com.dragonflow.SiteView.Platform.split(',', s2);
            for(int i = 0; i < array1.size(); i++)
            {
                String s3 = (String)array1.at(i);
                if(s3.indexOf(' ') < 0)
                {
                    continue;
                }
                com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewgroup.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(s3.replace(' ', '/')));
                if(monitor != null)
                {
                    com.dragonflow.Utils.TextUtils.addToBuffer(stringbuffer, monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
                }
            }

            if(stringbuffer.length() == 0)
            {
                stringbuffer.append(s1);
            }
            return stringbuffer.toString();
        } else
        {
            return s1;
        }
    }

    public Alert create(String s, String s1, SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return addUpdate(false, "", s1, assinstanceproperty, s);
    }

    public void delete(String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try
        {
            Alert alert = Alert.getInstance().getByID(com.dragonflow.Utils.TextUtils.toLong(s));
            if(!$assertionsDisabled && alert == null)
            {
                throw new AssertionError();
            }
            Alert.getInstance().removeFromMap(alert);
            removeCondition(alert);
            alert = null;
            com.dragonflow.SiteView.DetectConfigurationChange detectconfigurationchange = com.dragonflow.SiteView.DetectConfigurationChange.getInstance();
            detectconfigurationchange.setConfigChangeFlag();
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "delete"
            }, 0L, exception.getMessage());
        }
    }

    public String displayName(String s, jgl.Array array)
        throws Exception
    {
        String s1 = null;
        if(array.size() > 3)
        {
            s1 = (String)array.at(3);
            if(s1.startsWith("_UIContext"))
            {
                s1 = "";
            }
        }
        if(s.equals("_master"))
        {
            if(com.dragonflow.Utils.TextUtils.getValue(com.dragonflow.SiteView.MasterConfig.getMasterConfig(), "_alertGroupDisplay").length() > 0)
            {
                if(s1 != null && s1.length() > 0)
                {
                    return "multiple groups";
                } else
                {
                    return "all groups";
                }
            }
            if(s1 != null && s1.length() > 0)
            {
                com.dragonflow.SiteView.SiteViewObject siteviewobject = getSiteView();
                StringBuffer stringbuffer = new StringBuffer();
                jgl.Array array1 = com.dragonflow.SiteView.Platform.split(',', s1);
                for(int i = 0; i < array1.size(); i++)
                {
                    String s2 = (String)array1.at(i);
                    String as[] = com.dragonflow.Utils.TextUtils.split(s2);
                    String s4 = as[0];
                    com.dragonflow.SiteView.MonitorGroup monitorgroup = (com.dragonflow.SiteView.MonitorGroup)siteviewobject.getElement(s4);
                    if(monitorgroup == null)
                    {
                        continue;
                    }
                    if(as.length > 1)
                    {
                        com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)monitorgroup.getElementByID(as[1]);
                        if(monitor != null)
                        {
                            com.dragonflow.Utils.TextUtils.addToBuffer(stringbuffer, com.dragonflow.Page.CGI.getGroupFullName(getGroupIDFull(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))) + ": " + monitor.getProperty(com.dragonflow.SiteView.Monitor.pName));
                        }
                    } else
                    {
                        com.dragonflow.Utils.TextUtils.addToBuffer(stringbuffer, com.dragonflow.Page.CGI.getGroupFullName(getGroupIDFull(monitorgroup.getProperty(com.dragonflow.SiteView.Monitor.pID))));
                    }
                }

                return stringbuffer.toString();
            } else
            {
                return "all groups";
            }
        }
        if(!com.dragonflow.SiteView.Platform.isStandardAccount(account) && s.equals(account))
        {
            if(s1 != null && s1.length() > 0)
            {
                com.dragonflow.SiteView.SiteViewObject siteviewobject1 = getSiteView();
                StringBuffer stringbuffer1 = new StringBuffer();
                jgl.Array array2 = com.dragonflow.SiteView.Platform.split(',', s1);
                for(int j = 0; j < array2.size(); j++)
                {
                    String s3 = (String)array2.at(j);
                    String as1[] = com.dragonflow.Utils.TextUtils.split(s3);
                    String s5 = as1[0];
                    com.dragonflow.SiteView.MonitorGroup monitorgroup1 = (com.dragonflow.SiteView.MonitorGroup)siteviewobject1.getElement(s5);
                    if(monitorgroup1 == null)
                    {
                        continue;
                    }
                    if(as1.length > 1)
                    {
                        com.dragonflow.SiteView.Monitor monitor1 = (com.dragonflow.SiteView.Monitor)monitorgroup1.getElementByID(as1[1]);
                        if(monitor1 != null)
                        {
                            com.dragonflow.Utils.TextUtils.addToBuffer(stringbuffer1, com.dragonflow.Page.CGI.getGroupFullName(getGroupIDFull(monitorgroup1.getProperty(com.dragonflow.SiteView.Monitor.pID))) + ": " + monitor1.getProperty(com.dragonflow.SiteView.Monitor.pName));
                        }
                    } else
                    {
                        com.dragonflow.Utils.TextUtils.addToBuffer(stringbuffer1, com.dragonflow.Page.CGI.getGroupFullName(getGroupIDFull(monitorgroup1.getProperty(com.dragonflow.SiteView.Monitor.pID))));
                    }
                }

                return stringbuffer1.toString();
            } else
            {
                return account;
            }
        } else
        {
            return getGroupFullName(com.dragonflow.Utils.I18N.toDefaultEncoding(getGroupIDFull(s)));
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param action
     * @param hashmap
     * @param flag
     * @return
     */
    private jgl.HashMap editActionProperties(com.dragonflow.SiteView.Action action, jgl.HashMap hashmap, boolean flag)
    {
        jgl.HashMap hashmap1 = new HashMap();
        jgl.Array array = action.getProperties();
        array = com.dragonflow.Properties.StringProperty.sortByOrder(array);
        java.util.Enumeration enumeration = array.elements();

        while (enumeration.hasMoreElements())
            {
            com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
            if(!stringproperty.isConfigurable)
            {
                continue;
            }
            if(stringproperty.isMultiLine)
            {
                String s = (String)hashmap.get(stringproperty.getName());
                String as[] = com.dragonflow.Utils.TextUtils.split(s, "\r\n");
                if(flag && as.length > 0 || !flag)
                {
                    action.unsetProperty(stringproperty);
                    int i = 0;
                    while(i < as.length) 
                    {
                        String s3 = as[i];
                        s3 = action.verify(stringproperty, s3, null, hashmap1);
                        action.addProperty(stringproperty, s3);
                        i++;
                    }
                }
                continue;
            }
            if((stringproperty instanceof com.dragonflow.Properties.ScalarProperty) && ((com.dragonflow.Properties.ScalarProperty)stringproperty).multiple)
            {
                java.util.Enumeration enumeration1 = hashmap.values(stringproperty.getName());
                if((!flag || !enumeration1.hasMoreElements()) && flag)
                {
                    continue;
                }
                action.unsetProperty(stringproperty);

                Object obj;

                while(enumeration1.hasMoreElements()) {
                     obj = enumeration1.nextElement();
                     if(obj instanceof String) {
                         action.addProperty(stringproperty, (String)obj);
                     } else if (obj instanceof String[]) {
                        String as1[] = (String[])obj;                  
                        for (int j = 0; j < as1.length; j ++) 
                        {
                            action.addProperty(stringproperty, as1[j]);
                        }
                     }
                }
                continue;
            }

            String s1 = (String)hashmap.get(stringproperty.getName());
            String s2 = "";
            if(!flag && s1 == null)
            {
                s1 = "";
            }
            if(s1 != null)
            {
                s2 = action.verify(stringproperty, s1, null, hashmap1);
            }
            if(s2 != null && s2.length() > 0)
            {
                action.setProperty(stringproperty, s2);
            }
        } 
        return hashmap1;
    }

    private jgl.Array filterGroupsForAccount(jgl.Array array)
    {
        jgl.Array array1 = getGroupFilterForAccount("");
        if(array1 != null && array1.size() != 0)
        {
            java.util.Enumeration enumeration = array.elements();
            array = new Array();
            while (enumeration.hasMoreElements()) {
                String s = (String)enumeration.nextElement();
                if(allowedByGroupFilter(s, array1))
                {
                    array.add(s);
                }
            } 
        }
        return array;
    }

    public jgl.Array findCondition(String s, String s1, String s2)
        throws Exception
    {
        jgl.Array array = ReadGroupFrames(s);
        jgl.HashMap hashmap = findMonitor(array, s1);
        for(java.util.Enumeration enumeration = hashmap.values("_alertCondition"); enumeration.hasMoreElements();)
        {
            String s3 = (String)enumeration.nextElement();
            jgl.Array array1 = com.dragonflow.SiteView.Platform.split('\t', s3);
            if(s2.equals(array1.at(2)))
            {
                return array1;
            }
        }

        return null;
    }

    private jgl.HashMap findMonitor(jgl.Array array, String s)
        throws Exception
    {
        int i = findMonitorIndex(array, s);
        return (jgl.HashMap)array.at(i);
    }

    public com.dragonflow.SiteView.Action getAction(Alert alert)
    {
        com.dragonflow.SiteView.Action action = null;
        jgl.Array array = com.dragonflow.SiteView.Platform.split('\t', alert.getCondStr());
        if(array.size() > 1)
        {
            String s = (String)array.at(1);
            action = com.dragonflow.SiteView.Action.createAction(getActionClass(s));
            String s1 = "";
            if((s1 = alert.getContext()) != null)
            {
                action.setProperty(com.dragonflow.SiteView.Action.pUIContext, s1);
            }
            if((s1 = alert.getName()) != null)
            {
                action.setProperty(com.dragonflow.SiteView.Action.pName, s1);
            }
        }
        return action;
    }

    void getActionArguments(String s, jgl.Array array, jgl.HashMap hashmap)
    {
        int i = s.indexOf(" ");
        String as[];
        if(i >= 0)
        {
            as = com.dragonflow.Utils.TextUtils.split(s.substring(i + 1, s.length()));
        } else
        {
            as = new String[0];
        }
        for(int j = 0; j < as.length; j++)
        {
            int k = as[j].indexOf('=');
            if(k == -1)
            {
                as[j] = com.dragonflow.Utils.TextUtils.replaceString(as[j], com.dragonflow.SiteView.Action.EQUALS_SUBTITUTE, "=");
                array.add(as[j]);
            } else
            {
                as[j] = com.dragonflow.Utils.TextUtils.replaceString(as[j], com.dragonflow.SiteView.Action.EQUALS_SUBTITUTE, "=");
                hashmap.add(as[j].substring(0, k), as[j].substring(k + 1));
            }
        }

    }

    public String getActionClass(String s)
    {
        int i = s.indexOf(" ");
        if(i >= 0)
        {
            return com.dragonflow.Utils.TextUtils.toInitialUpper(s.substring(0, i));
        } else
        {
            return com.dragonflow.Utils.TextUtils.toInitialUpper(s);
        }
    }

    public SSStringReturnValue[] getAlertTypes()
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSStringReturnValue assstringreturnvalue[] = null;
        try
        {
            int i = findType("Alert");
            jgl.Array array = (jgl.Array)ssChildObjects.elementAt(i);
            assstringreturnvalue = new SSStringReturnValue[array.size()];
            for(int j = 0; j < array.size(); j++)
            {
                SSStringReturnValue ssstringreturnvalue = new SSStringReturnValue(((String[])array.at(j))[0]);
                int k = ssstringreturnvalue.getValue().lastIndexOf(".");
                if(k != -1)
                {
                    ssstringreturnvalue = new SSStringReturnValue(ssstringreturnvalue.getValue().substring(k + 1));
                }
                assstringreturnvalue[j] = ssstringreturnvalue;
            }

        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getAlertTypes"
            }, 0L, exception.getMessage());
        }
        return assstringreturnvalue;
    }

    public jgl.Array getAllowedGroupIDs()
    {
        return getAllowedGroupIDsForAccount();
    }

    private jgl.Array getAllowedGroupIDsForAccount()
    {
        jgl.Array array = com.dragonflow.Utils.I18N.toDefaultArray(com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getGroupIDs());
        return filterGroupsForAccount(array);
    }

    public int getAlwaysErrorCount(String s)
    {
        String s1 = "errorCount >= ";
        int i = s.indexOf(s1);
        if(i < 0)
        {
            s1 = "warningCount >= ";
            i = s.indexOf(s1);
        }
        if(i < 0)
        {
            s1 = "goodCount >= ";
            i = s.indexOf(s1);
        }
        if(i != -1)
        {
            return Math.max(0, com.dragonflow.Utils.TextUtils.readInteger(s, i + s1.length()));
        } else
        {
            return -1;
        }
    }

    public String getCategory(String s)
    {
        if(s.indexOf("category eq 'error'") >= 0)
        {
            return "error";
        }
        if(s.indexOf("category eq 'good'") >= 0)
        {
            return "good";
        } else
        {
            return "warning";
        }
    }

    public String getCategoryName(String s)
    {
        if(s.equals("error"))
        {
            return getString(alertErrorID);
        }
        if(s.equals("good"))
        {
            return getString(alertGoodID);
        } else
        {
            return getString(alertWarningID);
        }
    }

    private jgl.HashMap getClassAttribs(String s)
        throws Exception
    {
        jgl.HashMap hashmap = null;
        String s1 = "";
        s1 = "com.dragonflow.StandardAction." + s;
        Class class1 = Class.forName(s1);
        com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
        hashmap = siteviewobject.getClassProperties();
        return hashmap;
    }

    public SSStringReturnValue getClassAttribute(String s, String s1)
        throws Exception
    {
        jgl.HashMap hashmap = getClassAttribs(s);
        return new SSStringReturnValue((String)hashmap.get(s1));
    }

    public SSInstanceProperty[] getClassAttributes(String s)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSInstanceProperty assinstanceproperty[] = null;
        try
        {
            jgl.HashMap hashmap = getClassAttribs(s);
            int i = 0;
            assinstanceproperty = new SSInstanceProperty[hashmap.size()];
            for(java.util.Enumeration enumeration = hashmap.keys(); enumeration.hasMoreElements();)
            {
                String s1 = (String)enumeration.nextElement();
                String s2 = "";
                if(!s1.equals("elements"))
                {
                    s2 = (String)hashmap.get(s1);
                }
                assinstanceproperty[i] = new SSInstanceProperty(s1, s2);
                i++;
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getClassAttributes"
            }, 0L, exception.getMessage());
        }
        return assinstanceproperty;
    }

    public SSPropertyDetails[] getClassPropertiesDetails(String s, int i, jgl.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSPropertyDetails asspropertydetails[] = null;
        Object obj = null;
        try
        {
            String s1 = "";
            s1 = "com.dragonflow.StandardAction." + s;
            Class class1 = Class.forName(s1);
            com.dragonflow.SiteView.SiteViewObject siteviewobject = (com.dragonflow.SiteView.SiteViewObject)class1.newInstance();
            s1 = "com.dragonflow.StandardAction." + s;
            jgl.Array array = getPropertiesForClass(siteviewobject, s1, "Action", i);
            jgl.Array array1 = getSynthesizedAlertProperties(null, null, null, i);
            asspropertydetails = new SSPropertyDetails[array.size() + array1.size()];
            for(int j = 0; j < array.size(); j++)
            {
                asspropertydetails[j] = getClassProperty((com.dragonflow.Properties.StringProperty)array.at(j), (com.dragonflow.SiteView.Action)siteviewobject, hashmap);
            }

            for(int k = 0; k < array1.size(); k++)
            {
                asspropertydetails[k + array.size()] = new SSPropertyDetails(((SSInstanceProperty)array1.at(k)).getName(), "TEXT", "", ((SSInstanceProperty)array1.at(k)).getLabel(), true, false, (String)((SSInstanceProperty)array1.at(k)).getValue(), new String[0], new String[0], "", true, false, 1000 + k, "", false, false, siteviewobject.getProperty(((SSInstanceProperty)array1.at(k)).getName()));
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getClassPropertiesDetails"
            }, 0L, exception.getMessage());
        }
        return asspropertydetails;
    }

    private SSPropertyDetails getClassProperty(com.dragonflow.Properties.StringProperty stringproperty, com.dragonflow.SiteView.Action action, jgl.HashMap hashmap)
        throws Exception
    {
        boolean flag = false;
        String as[] = null;
        String as1[] = null;
        String s = "";
        String s1 = "";
        String s2 = "TEXT";
        try
        {
            com.dragonflow.HTTP.HTTPRequest httprequest = new HTTPRequest();
            httprequest.setUser(account);
            if((action instanceof com.dragonflow.StandardAction.Run) && stringproperty.getName() != null && stringproperty.getName().equals("_machine") && hashmap.get("_machine") == null)
            {
                flag = true;
            }
            if(stringproperty.isPassword)
            {
                s2 = "PASSWORD";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ServerProperty)
            {
                s2 = "SERVER";
                boolean flag1 = true;
                boolean flag2 = false;
                boolean flag3 = true;
                if(action instanceof com.dragonflow.SiteView.ServerAction)
                {
                    flag1 = false;
                    flag2 = true;
                }
                java.util.Vector vector = null;
                if(flag1)
                {
                    vector = getLocalServers();
                    vector = addServers(vector, new RemoteNTInstancePreferences().getSettingName(), true);
                } else
                {
                    vector = new Vector();
                    java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
                    String s3 = inetaddress.getHostName();
                    vector.addElement(s3);
                    vector.addElement(s3);
                    if(flag2)
                    {
                        vector = addServers(vector, new RemoteNTInstancePreferences().getSettingName(), true);
                    }
                }
                if(flag3)
                {
                    vector = addServers(vector, new RemoteUnixInstancePreferences().getSettingName(), false);
                }
                as = new String[vector.size() / 2];
                as1 = new String[vector.size() / 2];
                int i = 0;
                for(int k = 0; i < vector.size(); k++)
                {
                    as1[k] = (String)vector.elementAt(i);
                    as[k] = (String)vector.elementAt(i + 1);
                    i += 2;
                }

                s = "LIST";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScheduleProperty)
            {
                s2 = "SCHEDULE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.ScalarProperty)
            {
                s2 = "SCALAR";
                com.dragonflow.Properties.ScalarProperty scalarproperty = (com.dragonflow.Properties.ScalarProperty)stringproperty;
                Class class1 = Class.forName("com.dragonflow.Page.monitorPage");
                com.dragonflow.Page.CGI cgi = (com.dragonflow.Page.CGI)class1.newInstance();
                cgi.initialize(httprequest, null);
                if(hashmap.get("_machine") != null)
                {
                    httprequest.setValue("_machine", (String)hashmap.get("_machine"));
                    action.setProperty("_machine", (String)hashmap.get("_machine"));
                }
                java.util.Vector vector1 = action.getScalarValues(scalarproperty, httprequest, cgi);
                as = new String[vector1.size() / 2];
                as1 = new String[vector1.size() / 2];
                int j = 0;
                for(int l = 0; j < vector1.size() / 2; l += 2)
                {
                    as1[j] = (String)vector1.elementAt(l);
                    as[j] = (String)vector1.elementAt(l + 1);
                    j++;
                }

                s = "LIST";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.RateProperty)
            {
                s2 = "RATE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.PercentProperty)
            {
                s2 = "PERCENT";
                s1 = ((com.dragonflow.Properties.PercentProperty)stringproperty).getUnits();
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FrequencyProperty)
            {
                s2 = "FREQUENCY";
                s1 = "seconds";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.FileProperty)
            {
                s2 = "FILE";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.BooleanProperty)
            {
                s2 = "BOOLEAN";
            } else
            if(stringproperty instanceof com.dragonflow.Properties.NumericProperty)
            {
                s2 = "NUMERIC";
                s1 = ((com.dragonflow.Properties.NumericProperty)stringproperty).getUnits();
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getClassProperty"
            }, 0L, exception.getMessage());
        }
        return new SSPropertyDetails(stringproperty.getName(), s2, stringproperty.getDescription(), stringproperty.getLabel(), stringproperty.isEditable, stringproperty.isMultivalued, "", as, as1, s, !stringproperty.isAdvanced, flag, stringproperty.getOrder(), s1, stringproperty.isAdvanced, stringproperty.isPassword, action.getProperty(stringproperty.getName()));
    }

    public SSPropertyDetails getClassPropertyDetails(String s, String s1, jgl.HashMap hashmap)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSPropertyDetails sspropertydetails = null;
        try
        {
            SSPropertyDetails asspropertydetails[] = getClassPropertiesDetails(s1, APISiteView.FILTER_ALL, hashmap);
            int i = 0;
            do
            {
                if(i >= asspropertydetails.length)
                {
                    break;
                }
                if(asspropertydetails[i].getName().equals(s))
                {
                    sspropertydetails = asspropertydetails[i];
                    break;
                }
                i++;
            } while(true);
            if(sspropertydetails == null)
            {
                throw new SiteViewParameterException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_PARAM_API_PREFERENCE_NONEXISTANT_PROPERTY, new String[] {
                    s
                });
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getClassPropertyDetails"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    private String getClassString(String s)
    {
        return getStringParameter(s, "_class contains ");
    }

    public jgl.Array getConditions()
        throws Exception
    {
        APIAlertCacheManager apialertcachemanager = APIAlertCacheManager.getInstance();
        jgl.Array array = apialertcachemanager.getConditionsCache();
        if(array != null)
        {
            return array;
        }
        array = new Array();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        addConditions(array, hashmap, "_master", "_config");
        jgl.Array array1 = new Array();
        jgl.Array array2 = getAllowedGroupIDs();
        for(java.util.Enumeration enumeration = array2.elements(); enumeration.hasMoreElements();)
        {
            String s = (String)enumeration.nextElement();
            jgl.Array array3 = ReadGroupFrames(s);
            java.util.Enumeration enumeration2 = getMonitors(array3);
            jgl.HashMap hashmap1 = null;
            if(enumeration2.hasMoreElements())
            {
                hashmap1 = (jgl.HashMap)enumeration2.nextElement();
            } else
            {
                hashmap1 = new HashMap();
            }
            addConditions(array, hashmap1, com.dragonflow.Utils.I18N.toNullEncoding(s), "_config");
            while(enumeration2.hasMoreElements()) 
            {
                jgl.HashMap hashmap2 = (jgl.HashMap)enumeration2.nextElement();
                addConditions(array1, hashmap2, com.dragonflow.Utils.I18N.toNullEncoding(s), (String)hashmap2.get("_id"));
            }
        }

        for(java.util.Enumeration enumeration1 = array1.elements(); enumeration1.hasMoreElements(); array.add(enumeration1.nextElement())) { }
        apialertcachemanager.setConditionsCache(array);
        return array;
    }

    public String getDisabled(String s)
    {
        if(s.startsWith("disabled and "))
        {
            return "disabled";
        }
        if(s.indexOf("monitorDoneTime") >= 0)
        {
            String s1 = ">=";
            String s2 = "<=";
            String s3 = s.substring(s.indexOf("monitorDoneTime"));
            java.util.StringTokenizer stringtokenizer = new StringTokenizer(s3, " ");
            String s4 = "";
            String s5 = "";
            do
            {
                if(!stringtokenizer.hasMoreElements())
                {
                    break;
                }
                String s6 = (String)stringtokenizer.nextElement();
                if(s6.equals("monitorDoneTime"))
                {
                    String s7 = "";
                    String s8 = "";
                    if(stringtokenizer.hasMoreElements())
                    {
                        s7 = (String)stringtokenizer.nextElement();
                    }
                    if(stringtokenizer.hasMoreElements())
                    {
                        s8 = (String)stringtokenizer.nextElement();
                    }
                    if(s7.length() > 0 && s8.length() > 0)
                    {
                        if(s7.equals(s1))
                        {
                            s4 = s8;
                        } else
                        if(s7.equals(s2))
                        {
                            s5 = s8;
                        }
                    }
                }
            } while(true);
            if(s4.length() > 0)
            {
                if(s5.length() > 0)
                {
                    return "disabled until " + com.dragonflow.Utils.TextUtils.dateToString((new Long(s4)).longValue());
                } else
                {
                    return "disabled until " + com.dragonflow.Utils.TextUtils.dateToString((new Long(s4)).longValue());
                }
            }
        }
        return "";
    }

    private long getDisableScheduleTime(String s, String s1)
    {
        String s2 = "<=";
        String s3 = ">=";
        String s4 = "";
        long l = 0L;
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s1, " ");
        do
        {
            if(!stringtokenizer.hasMoreElements())
            {
                break;
            }
            String s5 = (String)stringtokenizer.nextElement();
            if(s5.equals("monitorDoneTime"))
            {
                String s6 = (String)stringtokenizer.nextElement();
                if(s6.equals(s2) && s.equals("startTimeTime"))
                {
                    s4 = (String)stringtokenizer.nextElement();
                } else
                if(s6.equals(s3) && s.equals("endTimeTime"))
                {
                    s4 = (String)stringtokenizer.nextElement();
                }
            }
        } while(true);
        if(s4.length() > 0)
        {
            l = (new Long(s4)).longValue();
        }
        return l;
    }

    public int getErrorCount(String s)
    {
        String s1 = "errorCount == ";
        int i = s.indexOf(s1);
        if(i < 0)
        {
            s1 = "warningCount == ";
            i = s.indexOf(s1);
        }
        if(i < 0)
        {
            s1 = "goodCount == ";
            i = s.indexOf(s1);
        }
        if(i != -1)
        {
            return Math.max(0, com.dragonflow.Utils.TextUtils.readInteger(s, i + s1.length()));
        } else
        {
            return -1;
        }
    }

    private com.dragonflow.SiteView.Monitor getFirstChildMonitor(com.dragonflow.SiteView.MonitorGroup monitorgroup)
    {
        for(java.util.Enumeration enumeration = monitorgroup.getMonitors(); enumeration.hasMoreElements();)
        {
            com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
            if(monitor instanceof com.dragonflow.SiteView.MonitorGroup)
            {
                monitor = getFirstChildMonitor((com.dragonflow.SiteView.MonitorGroup)monitor);
                if(monitor != null)
                {
                    return monitor;
                }
            } else
            if(monitor instanceof com.dragonflow.SiteView.SubGroup)
            {
                com.dragonflow.SiteView.MonitorGroup monitorgroup1 = com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getGroup(monitor.getProperty("_group"));
                monitor = getFirstChildMonitor(monitorgroup1);
                if(monitor != null)
                {
                    return monitor;
                }
            } else
            {
                return monitor;
            }
        }

        return null;
    }

    public String getGroupFullName(String s)
        throws Exception
    {
        com.dragonflow.Utils.I18N.test(s, 0);
        com.dragonflow.SiteView.SiteViewObject siteviewobject = com.dragonflow.SiteView.Portal.getSiteViewForID(s);
        com.dragonflow.SiteView.Monitor monitor = (com.dragonflow.SiteView.Monitor)siteviewobject.getElementByID(getGroupIDRelative(s));
        return getGroupPath(monitor, s, false);
    }

    public String getGroupIDFull(String s)
    {
        return s;
    }

    private String getGroupIDRelative(String s)
    {
        if(com.dragonflow.SiteView.Portal.isPortalID(s))
        {
            s = com.dragonflow.SiteView.Portal.getGroupID(s);
        }
        return s;
    }

    public String getGroupName(com.dragonflow.SiteView.Monitor monitor, String s)
        throws Exception
    {
        com.dragonflow.Utils.I18N.test(s, 0);
        String s1;
        if(monitor == null)
        {
            s1 = com.dragonflow.Utils.I18N.toNullEncoding(s);
            s1 = "MISSING GROUP (" + s1 + ")";
        } else
        {
            s1 = getGroupName(s);
        }
        return s1;
    }

    public String getGroupName(jgl.HashMap hashmap, String s)
    {
        String s1 = null;
        if(hashmap != null)
        {
            s1 = (String)hashmap.get("_name");
        }
        if(s1 == null || s1.equals("config") || s1.length() == 0)
        {
            s1 = com.dragonflow.Page.CGI.getGroupFullName(s);
        }
        return s1;
    }

    private String getGroupName(String s)
        throws Exception
    {
        com.dragonflow.Utils.I18N.test(s, 0);
        jgl.HashMap hashmap = null;
        jgl.Array array = ReadGroupFrames(s);
        java.util.Enumeration enumeration = array.elements();
        if(enumeration.hasMoreElements())
        {
            hashmap = (jgl.HashMap)enumeration.nextElement();
        } else
        {
            hashmap = new HashMap();
        }
        return getGroupName(hashmap, s);
    }

    private String getGroupPath(com.dragonflow.SiteView.Monitor monitor, String s, boolean flag)
        throws Exception
    {
        com.dragonflow.Utils.I18N.test(s, 0);
        com.dragonflow.SiteView.SiteViewObject siteviewobject = com.dragonflow.SiteView.Portal.getSiteViewForID(s);
        String s1 = "";
        do
        {
            if(s1.length() != 0)
            {
                s1 = ": " + s1;
            }
            String s2 = getGroupName(monitor, s);
            s = com.dragonflow.HTTP.HTTPRequest.encodeString(s);
            if(flag && s1.length() != 0)
            {
                s1 = "<A HREF=Detail" + s + ".html>" + s2 + "</a>" + s1;
            } else
            {
                s1 = s2 + s1;
            }
            if(monitor == null)
            {
                break;
            }
            s = com.dragonflow.Utils.I18N.toDefaultEncoding(monitor.getProperty("_parent"));
            if(s == null || s.length() == 0)
            {
                break;
            }
            monitor = (com.dragonflow.SiteView.Monitor)siteviewobject.getElement(s);
        } while(true);
        return s1;
    }

    public String getHostname()
    {
        String s = null;
        try
        {
            s = java.net.InetAddress.getLocalHost().toString();
            int i = s.indexOf("/");
            if(i != -1)
            {
                s = s.substring(0, i);
            }
        }
        catch(java.net.UnknownHostException unknownhostexception)
        {
            com.dragonflow.Log.LogManager.log("Error", "ApiAlert.getHostname:  Unable to retrieve local host.");
        }
        return s;
    }

    public SSInstanceProperty[] getInstanceProperties(String s, String s1, String s2, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSInstanceProperty assinstanceproperty[] = null;
        try
        {
            int j = s.lastIndexOf("/");
            if(j != -1)
            {
                s = s.substring(j + 1);
            }
            jgl.Array array = getConditions();
            if(array.size() > 0)
            {
                java.util.Enumeration enumeration = array.elements();
                while (enumeration.hasMoreElements())
                    {
                    jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                    String s3 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)hashmap.get("group"));
                    if(s3.equals("_master") || s3.equals(s2))
                    {
                        String s4 = (String)hashmap.get("id");
                        String s5 = (String)hashmap.get("monitor");
                        if((s5.equals("_config") || s5.equals(s1)) && s4.equals(s))
                        {
                            jgl.Array array1 = findCondition(com.dragonflow.Utils.I18N.toDefaultEncoding(s3), s5, s4);
                            if(array1.size() > 2)
                            {
                                String s6 = (String)array1.at(0);
                                String s7 = (String)array1.at(1);
                                packCondition(hashmap, s7, new HashMap());
                                com.dragonflow.SiteView.Action action = com.dragonflow.SiteView.Action.createAction(getActionClass(s7));
                                String s8 = "";
                                String s9 = getActionClass(s7);
                                if(array1.size() > 3)
                                {
                                    for(int k = 3; k < array1.size(); k++)
                                    {
                                        String s10 = (String)array1.at(k);
                                        if(s10.startsWith("_UIContext="))
                                        {
                                            s8 = s10.substring("_UIContext".length() + 1);
                                            continue;
                                        }
                                        if(s10.startsWith("_name="))
                                        {
                                            s9 = s10.substring("_name".length() + 1);
                                        }
                                    }

                                }
                                action.setProperty("_uniqueID", s);
                                action.setProperty("_UIContext", s8);
                                action.setProperty("_name", s9);
                                jgl.Array array2 = new Array();
                                com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                                getActionArguments(s7, array2, hashmapordered);
                                action.initializeFromArguments(array2, hashmapordered);
                                assinstanceproperty = getPropertiesForAlertInstance(action, s6, hashmap, i);
                                SSInstanceProperty assinstanceproperty1[] = new SSInstanceProperty[assinstanceproperty.length + 1];
                                System.arraycopy(assinstanceproperty, 0, assinstanceproperty1, 0, assinstanceproperty.length);
                                String s11 = Alert.getInstance().createTargetListStr(Alert.getInstance().getByID((new Long(s)).longValue()));
                                String as[] = com.dragonflow.Utils.TextUtils.split(s11, ",");
                                for(int l = 0; l < as.length; l++)
                                {
                                    as[l] = as[l].trim();
                                }

                                assinstanceproperty1[assinstanceproperty1.length - 1] = new SSInstanceProperty("_targetList", "TargetList", as);
                                assinstanceproperty = assinstanceproperty1;
                            }
                        }
                    }
                }
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getInstanceProperties"
            }, 0L, exception.getMessage());
        }
        return assinstanceproperty;
    }

    public SSInstanceProperty getInstanceProperty(String s, String s1, String s2, String s3)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSInstanceProperty ssinstanceproperty = null;
        try
        {
            SSInstanceProperty assinstanceproperty[] = null;
            int i = s1.lastIndexOf("/");
            if(i != -1)
            {
                s1 = s1.substring(i + 1);
            }
            jgl.Array array = getConditions();
            if(array.size() > 0)
            {
                java.util.Enumeration enumeration = array.elements();
                while (enumeration.hasMoreElements()) {
                    jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                    String s4 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)hashmap.get("group"));
                    if(s3.length() == 0 && s4.equals("_master") || s4.equals(s3))
                    {
                        String s5 = (String)hashmap.get("id");
                        String s6 = (String)hashmap.get("monitor");
                        if((s2.length() == 0 && s6.equals("_config") || s6.equals(s2)) && s5.equals(s1))
                        {
                            jgl.Array array1 = findCondition(com.dragonflow.Utils.I18N.toDefaultEncoding(s4), s6, s5);
                            if(array1.size() > 1)
                            {
                                String s7 = (String)array1.at(0);
                                String s8 = (String)array1.at(1);
                                packCondition(hashmap, s8, new HashMap());
                                com.dragonflow.SiteView.Action action = com.dragonflow.SiteView.Action.createAction(getActionClass(s8));
                                jgl.Array array2 = new Array();
                                com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                                getActionArguments(s8, array2, hashmapordered);
                                action.initializeFromArguments(array2, hashmapordered);
                                assinstanceproperty = getPropertiesForAlertInstance(action, s7, hashmap, APISiteView.FILTER_ALL);
                            }
                        }
                    }
                }
            }
            
            for(int j = 0; j < assinstanceproperty.length; j++)
            {
                if(assinstanceproperty[j].getName().equals(s))
                {
                    ssinstanceproperty = assinstanceproperty[j];
                }
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getInstanceProperty"
            }, 0L, exception.getMessage());
        }
        return ssinstanceproperty;
    }

    public SSPropertyDetails getInstancePropertyDetails(String s, String s1, String s2, String s3)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SSPropertyDetails sspropertydetails = null;
        try
        {
            int i = s1.lastIndexOf("/");
            if(i != -1)
            {
                s1 = s1.substring(i + 1);
            }
            jgl.Array array = getConditions();
            if(array.size() > 0)
            {
                java.util.Enumeration enumeration = array.elements();
                while (enumeration.hasMoreElements())
                    {
                    jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
                    String s4 = com.dragonflow.Utils.I18N.toDefaultEncoding((String)hashmap.get("group"));
                    if(s3.length() == 0 && s4.equals("_master") || s4.equals(s3))
                    {
                        String s5 = (String)hashmap.get("id");
                        String s6 = (String)hashmap.get("monitor");
                        if((s2.length() == 0 && s6.equals("_config") || s6.equals(s2)) && s5.equals(s1))
                        {
                            jgl.Array array1 = findCondition(com.dragonflow.Utils.I18N.toDefaultEncoding(s4), s6, s5);
                            if(array1.size() > 1)
                            {
                                String s7 = (String)array1.at(1);
                                com.dragonflow.SiteView.Action action = com.dragonflow.SiteView.Action.createAction(getActionClass(s7));
                                jgl.Array array2 = new Array();
                                com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
                                getActionArguments(s7, array2, hashmapordered);
                                action.initializeFromArguments(array2, hashmapordered);
                                boolean flag = false;
                                jgl.Array array3 = action.getProperties();
                                array3 = com.dragonflow.Properties.StringProperty.sortByOrder(array3);
                                enumeration = array3.elements();
                                while (enumeration.hasMoreElements())
                                    {
                                    com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
                                    if(!flag && s.equals(stringproperty.getName()))
                                    {
                                        sspropertydetails = getClassProperty(stringproperty, action, new HashMap());
                                        flag = true;
                                    }
                                }
                                jgl.Array array4 = getSynthesizedAlertProperties(null, null, null, APISiteView.FILTER_ALL);
                                int j = 0;
                                while(j < array4.size()) 
                                {
                                    if(!flag && s.equals(((SSInstanceProperty)array4.at(j)).getName()))
                                    {
                                        sspropertydetails = new SSPropertyDetails(((SSInstanceProperty)array4.at(j)).getName(), "TEXT", "", ((SSInstanceProperty)array4.at(j)).getLabel(), true, false, (String)((SSInstanceProperty)array4.at(j)).getValue(), new String[0], new String[0], "", true, false, 1000 + j, "", false, false, action.getProperty(((SSInstanceProperty)array4.at(j)).getName()));
                                        flag = true;
                                    }
                                    j++;
                                }
                            }
                        }
                    }
                } 
            }
        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getInstancePropertyDetails"
            }, 0L, exception.getMessage());
        }
        return sspropertydetails;
    }

    public SVAlertInstance[] getInstances(String s, String s1, int i)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        SVAlertInstance assalertinstance[] = null;
        try
        {
            java.util.Vector vector = null;
            if(i == APISiteView.FILTER_ALERT_ASSOCIATED)
            {
                vector = Alert.getInstance().getAlertsAssociatedWithGroupOrMonitor(s1, s);
            } else
            {
                vector = Alert.getInstance().getAlertsResidingInGroupOrMonitor(s1, s);
            }
            java.util.Enumeration enumeration = vector.elements();
            java.util.Vector vector1 = new Vector();
            String s2;
            String s3;
            String s4;
            SSInstanceProperty assinstanceproperty[];
            for(; enumeration.hasMoreElements(); vector1.addElement(new SVAlertInstance(s4, s3, s2, assinstanceproperty)))
            {
                Alert alert = (Alert)enumeration.nextElement();
                s2 = alert.getGroup();
                s3 = alert.getMonitorID();
                s4 = alert.getIDStr();
                assinstanceproperty = getInstanceProperties(s4, s3, s2, i);
            }

            assalertinstance = new SVAlertInstance[vector1.size()];
            for(int j = 0; j < vector1.size(); j++)
            {
                assalertinstance[j] = (SVAlertInstance)vector1.elementAt(j);
            }

        }
        catch(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
        {
            siteviewexception.fillInStackTrace();
            throw siteviewexception;
        }
        catch(Exception exception)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "getInstances"
            }, 0L, exception.getMessage());
        }
        return assalertinstance;
    }

    private int getMaxErrorCount(String s)
    {
        String s1 = "maxErrorCount == ";
        int i = s.indexOf(s1);
        if(i >= 0)
        {
            return Math.max(0, com.dragonflow.Utils.TextUtils.readInteger(s, i + s1.length()));
        } else
        {
            return -1;
        }
    }

    private java.util.Enumeration getMonitors(jgl.Array array)
    {
        jgl.Array array1 = new Array();
        java.util.Enumeration enumeration = array.elements();
        if(enumeration.hasMoreElements())
        {
            array1.add(enumeration.nextElement());
        }
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap = (jgl.HashMap)enumeration.nextElement();
            if(com.dragonflow.SiteView.Monitor.isMonitorFrame(hashmap))
            {
                array1.add(hashmap);
            }
        } 
        return array1.elements();
    }

    public int getMultipleErrorCount(String s)
    {
        String s1 = "errorCount multipleOf ";
        int i = s.indexOf(s1);
        if(i < 0)
        {
            s1 = "warningCount multipleOf ";
            i = s.indexOf(s1);
        }
        if(i < 0)
        {
            s1 = "goodCount multipleOf ";
            i = s.indexOf(s1);
        }
        if(i != -1)
        {
            return Math.max(0, com.dragonflow.Utils.TextUtils.readInteger(s, i + s1.length()));
        } else
        {
            return -1;
        }
    }

    private String getNameString(String s)
    {
        return getStringParameter(s, "_name contains ");
    }

    private int getPreviousErrorCount(String s)
    {
        String s1 = "errorCount >= ";
        int i = s.indexOf(s1);
        if(i != -1)
        {
            return Math.max(0, com.dragonflow.Utils.TextUtils.readInteger(s, i + s1.length()));
        } else
        {
            return -1;
        }
    }

    private SSInstanceProperty[] getPropertiesForAlertInstance(com.dragonflow.SiteView.Action action, String s, jgl.HashMap hashmap, int i)
        throws Exception
    {
        jgl.Array array = new Array();
        jgl.Array array1 = action.getProperties();
        array1 = com.dragonflow.Properties.StringProperty.sortByOrder(array1);
        java.util.Enumeration enumeration = array1.elements();
        while (enumeration.hasMoreElements()) {
            boolean flag = false;
            com.dragonflow.Properties.StringProperty stringproperty = (com.dragonflow.Properties.StringProperty)enumeration.nextElement();
            Class class1 = action.getClass();
            String s1 = class1.getName();
            flag = returnProperty(stringproperty, i, action, s1);
            if(flag)
            {
                array.add(stringproperty);
            }
        } 
        jgl.Array array2 = getSynthesizedAlertProperties(action, s, hashmap, i);
        SSInstanceProperty assinstanceproperty[] = new SSInstanceProperty[array.size() + array2.size()];
        int j = 0;
        for(java.util.Enumeration enumeration1 = array.elements(); enumeration1.hasMoreElements(); j++)
        {
            com.dragonflow.Properties.StringProperty stringproperty1 = (com.dragonflow.Properties.StringProperty)enumeration1.nextElement();
            String s2 = stringproperty1.getName();
            String s3 = GetPropertyLabel(stringproperty1, true);
            if((stringproperty1 instanceof com.dragonflow.Properties.ScalarProperty) && ((com.dragonflow.Properties.ScalarProperty)stringproperty1).multiple)
            {
                java.util.Enumeration enumeration2 = action.getMultipleValues(stringproperty1);
                java.util.Vector vector = new Vector();
                java.util.Vector vector1 = new Vector();
                boolean flag1 = false;
                while(enumeration2.hasMoreElements()) 
                {
                    String s6 = (String)enumeration2.nextElement();
                    if(s2.equals("_to") && s6.indexOf(":") == -1)
                    {
                        flag1 = true;
                        vector1.add(s6);
                    } else
                    {
                        vector.add(s6);
                    }
                }
                if(flag1)
                {
                    String s7 = "";
                    for(int l = 0; l < vector1.size(); l++)
                    {
                        s7 = s7 + (String)vector1.elementAt(l);
                    }

                    assinstanceproperty[j] = new SSInstanceProperty(stringproperty1.getName(), s3, "");
                    array2.put(0, new SSInstanceProperty("toOther", s7));
                    continue;
                }
                String as[] = new String[vector.size()];
                for(int i1 = 0; i1 < vector.size(); i1++)
                {
                    as[i1] = (String)vector.elementAt(i1);
                }

                assinstanceproperty[j] = new SSInstanceProperty(stringproperty1.getName(), s3, as);
                continue;
            }
            String s4 = action.getProperty(stringproperty1);
            String s5 = (String)hashmap.get(s2);
            if(s5 != null && s5.length() > 0)
            {
                s4 = s5;
            }
            if(s4 == null)
            {
                s4 = "";
            }
            if(stringproperty1.isPassword)
            {
                s4 = com.dragonflow.Utils.TextUtils.obscure(s4);
            }
            assinstanceproperty[j] = new SSInstanceProperty(stringproperty1.getName(), s3, s4);
        }

        for(int k = 0; k < array2.size(); k++)
        {
            assinstanceproperty[j + k] = (SSInstanceProperty)array2.at(k);
        }

        return assinstanceproperty;
    }

    private com.dragonflow.SiteView.SiteViewObject getSiteView()
    {
        return com.dragonflow.SiteView.Portal.getSiteViewForID("");
    }

    private String getStatusString(String s)
    {
        return getStringParameter(s, "stateString contains ");
    }

    private String getString(int i)
    {
        return language[i];
    }

    private String getStringParameter(String s, String s1)
    {
        int i = s.indexOf(s1);
        if(i >= 0)
        {
            byte byte0 = 32;
            i += s1.length();
            if(s.charAt(i) == '\'')
            {
                byte0 = 39;
                i++;
            }
            StringBuffer stringbuffer = new StringBuffer();
            char c = ' ';
            do
            {
                if(i >= s.length())
                {
                    break;
                }
                char c1 = s.charAt(i++);
                if(c1 == byte0 && c != 92)
                {
                    break;
                }
                stringbuffer.append(c1);
                c = c1;
            } while(true);
            return stringbuffer.toString();
        } else
        {
            return "";
        }
    }

    private jgl.Array getSynthesizedAlertProperties(com.dragonflow.SiteView.Action action, String s, jgl.HashMap hashmap, int i)
        throws Exception
    {
        jgl.Array array = new Array();
        if(i == FILTER_CONFIGURATION_ADD_ALL || i == FILTER_CONFIGURATION_ADD_BASIC || i == FILTER_CONFIGURATION_ADD_ADVANCED || i == FILTER_CONFIGURATION_EDIT_ALL || i == FILTER_CONFIGURATION_EDIT_BASIC || i == FILTER_CONFIGURATION_EDIT_ADVANCED || i == FILTER_CONFIGURATION_ALL || i == APISiteView.FILTER_ALL)
        {
            String s1 = "undo";
            String s3 = "";
            String s5 = "";
            String s8 = "";
            String s10 = "";
            String s11 = "";
            String s12 = "";
            String s13 = "";
            int j = -1;
            int k = -1;
            int l = -1;
            int i1 = -1;
            int j1 = -1;
            int k1 = -1;
            if(s != null)
            {
                int l1 = s.indexOf("and monitorDoneTime >=");
                if(l1 > -1)
                {
                    int i2 = s.indexOf("monitorDoneTime <=");
                    if(i2 == -1)
                    {
                        String s15 = s.substring(l1);
                        s15 = "or " + s15.substring(4);
                        String s16 = "and monitorDoneTime <= " + com.dragonflow.SiteView.Platform.timeMillis();
                        s = s.substring(0, l1) + s16 + " " + s15;
                    }
                }
                if(s5.length() == 0)
                {
                    s5 = getCategory(s);
                }
                j = getErrorCount(s);
                k = getAlwaysErrorCount(s);
                l = getMultipleErrorCount(s);
                i1 = getAlwaysErrorCount(s);
                k1 = getPreviousErrorCount(s);
                j1 = getMaxErrorCount(s);
                s8 = getNameString(s);
                s11 = getClassString(s);
                s10 = getStatusString(s);
                s12 = getDisabled(s);
                if(s.indexOf("monitorDoneTime") >= 0)
                {
                    s13 = s.substring(s.indexOf("monitorDoneTime"));
                }
            }
            if(j == -1 && l == -1)
            {
                s3 = "always";
            }
            if(j != -1)
            {
                s3 = "count";
            }
            if(l != -1)
            {
                s3 = "multiple";
            }
            if(j1 != -1)
            {
                s3 = "maxErrors";
            }
            if(s != null && s.indexOf("group.monitorsInError") >= 0)
            {
                s3 = "allErrors";
            }
            byte byte0 = -1;
            if(s5.equals("good"))
            {
                if(k1 != -1)
                {
                    byte0 = 1;
                } else
                {
                    k1 = 2;
                }
            }
            String s14 = "0";
            long l2 = 0L;
            long l3 = 0L;
            String s17 = "";
            String s18 = "";
            String s19 = "";
            String s20 = "";
            if(s12.length() > 0)
            {
                if(s12.equals("disabled"))
                {
                    s1 = "permanent";
                } else
                if(s12.startsWith("disabled until"))
                {
                    if(isTimedDisable(s13))
                    {
                        s1 = "timed";
                        s14 = "10";
                    } else
                    if(isScheduledDisable(s13))
                    {
                        s1 = "schedule";
                    }
                    l2 = getDisableScheduleTime("startTimeTime", s13);
                    l3 = getDisableScheduleTime("endTimeTime", s13);
                    s17 = com.dragonflow.Utils.TextUtils.dateToMilitaryTime(new Date(l2));
                    s18 = com.dragonflow.Utils.TextUtils.dateToMilitaryTime(new Date(l3));
                    s19 = com.dragonflow.Utils.TextUtils.prettyDatePart(new Date(l2), false);
                    s20 = com.dragonflow.Utils.TextUtils.prettyDatePart(new Date(l3), false);
                    long l4 = getDisableScheduleTime("endTimeTime", s13);
                    long l5 = l4 - com.dragonflow.SiteView.Platform.timeMillis();
                    l5 /= 1000L;
                    l5 /= 60L;
                    s14 = (new Long(l5)).toString();
                    if(s1.equals("schedule"))
                    {
                        s14 = "";
                    }
                }
            }
            if(hashmap != null && hashmap.get("category") != null)
            {
                s5 = (String)hashmap.get("category");
            }
            array.add(new SSInstanceProperty("toOther", ""));
            array.add(new SSInstanceProperty("when", "When", s3));
            array.add(new SSInstanceProperty("category", "Category", s5));
            if(j != -1)
            {
                array.add(new SSInstanceProperty("errorCount", "ErrorCount", (new Integer(j)).toString()));
            }
            if(k != -1)
            {
                array.add(new SSInstanceProperty("alwaysErrorCount", "AlwaysErrorCount", (new Integer(k)).toString()));
            }
            if(i1 != -1)
            {
                array.add(new SSInstanceProperty("multipleStartCount", "MultipleStartCount", (new Integer(i1)).toString()));
            }
            if(l != -1)
            {
                array.add(new SSInstanceProperty("multipleErrorCount", "MultipleErrorCount", (new Integer(l)).toString()));
            }
            if(k1 != -1)
            {
                array.add(new SSInstanceProperty("previousErrorCount", "PreviousErrorCount", (new Integer(k1)).toString()));
            }
            if(j1 != -1)
            {
                array.add(new SSInstanceProperty("maxErrorCount", "MaxErrorCount", (new Integer(j1)).toString()));
            }
            if(s8.length() > 0)
            {
                array.add(new SSInstanceProperty("nameMatchString", "NameMatchString", s8));
            }
            if(s10.length() > 0)
            {
                array.add(new SSInstanceProperty("statusMatchString", "StatusMatchString", s10));
            }
            if(s11.length() > 0)
            {
                array.add(new SSInstanceProperty("classMatchString", "ClassMatchString", s11));
            }
            if(s1.length() > 0)
            {
                array.add(new SSInstanceProperty("alertDisable", "AlertDisable", s1));
            }
            if(byte0 > -1)
            {
                array.add(new SSInstanceProperty("usePreviousErrorCount", "UsePreviousErrorCount", "on"));
            } else
            {
                array.add(new SSInstanceProperty("usePreviousErrorCount", "UsePreviousErrorCount", ""));
            }
            array.add(new SSInstanceProperty("disableAlertUnits", "DisableAlertUnits", "seconds"));
            if(l2 > 0L)
            {
                array.add(new SSInstanceProperty("startTimeTime", "StartTimeTime", s17));
                if(s19.length() > 0)
                {
                    array.add(new SSInstanceProperty("startTimeDate", "StartTimeDate", s19));
                }
            }
            if(s1.equals("schedule"))
            {
                array.add(new SSInstanceProperty("disableAlertTime", "DisableAlertTime", ""));
            } else
            if(s14.length() > 0)
            {
                array.add(new SSInstanceProperty("disableAlertTime", "DisableAlertTime", (new Integer(s14)).toString()));
            }
            if(l3 > 0L)
            {
                array.add(new SSInstanceProperty("endTimeTime", "EndTimeTime", s18));
            }
            if(s20.length() > 0)
            {
                array.add(new SSInstanceProperty("endTimeDate", "EndTimeDate", s20));
            }
            if(s1.equals("undo"))
            {
                array.add(new SSInstanceProperty("disableAlertTime", "DisableAlertTime", ""));
                array.add(new SSInstanceProperty("endTimeTime", "EndTimeTime", ""));
                array.add(new SSInstanceProperty("endTimeDate", "EndTimeDate", ""));
                array.add(new SSInstanceProperty("startTimeTime", "StartTimeTime", ""));
                array.add(new SSInstanceProperty("startTimeDate", "StartTimeDate", ""));
            }
        }
        if(i != APISiteView.FILTER_CONFIGURATION_ADD_ALL && i != APISiteView.FILTER_CONFIGURATION_ADD_BASIC && i != APISiteView.FILTER_CONFIGURATION_ADD_ADVANCED && i != APISiteView.FILTER_CONFIGURATION_EDIT_ALL && i != APISiteView.FILTER_CONFIGURATION_EDIT_BASIC && i != APISiteView.FILTER_CONFIGURATION_EDIT_ADVANCED)
        {
            String s2 = "";
            String s4 = "";
            String s6 = "";
            String s9 = "";
            if(hashmap != null)
            {
                if(action != null)
                {
                    String s7 = (String)action.getClassProperty("name");
                    s9 = (String)action.getClassProperty("class");
                }
                if(hashmap.get("command") != null)
                {
                    s2 = (String)hashmap.get("command");
                }
                if(hashmap.get("id") != null)
                {
                    s4 = (String)hashmap.get("id");
                }
            }
            array.add(new SSInstanceProperty("command", "Command", s2));
            array.add(new SSInstanceProperty("_id", "Id", s4));
            array.add(new SSInstanceProperty("_class", "Class", s9));
        }
        return array;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param alert
     * @return
     */
     private com.dragonflow.SiteView.Monitor getTestMonitor(Alert alert) {
        com.dragonflow.SiteView.Monitor monitor = null;
            String s = alert.getIncludeFilter();
            if(s != null && !s.equals(""))
            {
                String as[] = com.dragonflow.Utils.TextUtils.split(alert.getIncludeFilter(), ",");
                String as1[] = com.dragonflow.Utils.TextUtils.split(as[0], " ");
                com.dragonflow.SiteView.MonitorGroup monitorgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getGroup(as1[0]);
                String s1 = as1[1];
                java.util.Enumeration enumeration = monitorgroup.getMonitors();
                com.dragonflow.SiteView.Monitor monitor2;
                String s2;
                while (enumeration.hasMoreElements())
                    {
                    monitor2 = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                    s2 = monitor2.getProperty("_id");
                if (s1.equals(s2)) {
                monitor = monitor2;
                }
            }
            } else
            {
                com.dragonflow.SiteView.Monitor monitor1 = alert.getMonitor();
                if((com.dragonflow.SiteView.MonitorGroup.class).isInstance(monitor1))
                {
                    monitor = getFirstChildMonitor((com.dragonflow.SiteView.MonitorGroup)monitor1);
                } else
                {
                    monitor = monitor1;
                }
            }
        return monitor;
    }

    private boolean isGroup(jgl.HashMap hashmap)
    {
        return hashmap.get("_id") == null;
    }

    private boolean isScheduledDisable(String s)
    {
        String s1 = "<=";
        String s2 = ">=";
        boolean flag = false;
        boolean flag1 = false;
        for(java.util.StringTokenizer stringtokenizer = new StringTokenizer(s, " "); stringtokenizer.hasMoreElements();)
        {
            String s3 = (String)stringtokenizer.nextElement();
            if(s3.equals("monitorDoneTime"))
            {
                String s4 = (String)stringtokenizer.nextElement();
                if(s4.equals(s1))
                {
                    flag = true;
                } else
                if(s4.equals(s2))
                {
                    flag1 = true;
                }
            }
            if(flag1 && flag)
            {
                return true;
            }
        }

        return flag1 && flag;
    }

    private boolean isTimedDisable(String s)
    {
        String s1 = "<=";
        for(java.util.StringTokenizer stringtokenizer = new StringTokenizer(s, " "); stringtokenizer.hasMoreElements();)
        {
            String s2 = (String)stringtokenizer.nextElement();
            if(s2.equals("monitorDoneTime"))
            {
                String s3 = (String)stringtokenizer.nextElement();
                if(s3.equals(s1))
                {
                    return false;
                }
            }
        }

        return true;
    }

    private jgl.HashMap mungeCondition(Alert alert, String s)
    {
        jgl.HashMap hashmap = null;
        try
        {
            jgl.Array array = ReadGroupFrames(alert.getGroup());
            hashmap = findMonitor(array, alert.getMonitorID());
            String s1 = alert.getIDStr();
            String s2 = s + "\t" + s1;
            if(alert.getIncludeFilter().length() != 0)
            {
                s2 = s2 + "\t" + alert.getIncludeFilter();
            }
            if(alert.getContext().length() != 0)
            {
                s2 = s2 + "\t_UIContext=" + alert.getContext();
            }
            if(alert.getName().length() != 0)
            {
                s2 = s2 + "\t_name=" + alert.getName();
            }
            jgl.Array array1 = new Array();
            boolean flag = false;
            java.util.Enumeration enumeration = hashmap.values("_alertCondition");
            while (enumeration.hasMoreElements()) {
                String s3 = (String)enumeration.nextElement();
                jgl.Array array2 = com.dragonflow.SiteView.Platform.split('\t', s3);
                if(array2.at(2).equals(s1))
                {
                    if(s != null)
                    {
                        array1.add(s2);
                        flag = true;
                    }
                } else
                {
                    array1.add(s3);
                }
            } 
            
            if(!flag && s != null)
            {
                array1.add(s2);
            }
            hashmap.put("_alertCondition", array1);
            WriteGroupFrames(alert.getGroup(), array);
            com.dragonflow.SiteView.SiteViewGroup.SignalReload();
        }
        catch(java.io.IOException ioexception) { }
        catch(Exception exception) { }
        return hashmap;
    }

    public String packCondition(jgl.HashMap hashmap, String s, jgl.HashMap hashmap1)
    {
        String s1 = "";
        String s2 = "";
        String s3 = "";
        String s4 = "";
        String s5 = "";
        String s6 = "";
        String s7 = (String)hashmap.get("category");
        if(s7 == null || s7.length() == 0)
        {
            s7 = "error";
        }
        String s8 = (String)hashmap.get("when");
        if(s8 != null)
        {
            if(s8.equals("count"))
            {
                int i = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("errorCount"));
                if(i <= 0)
                {
                    i = 1;
                }
                s1 = " and " + s7 + "Count == " + i;
            } else
            if(s8.equals("always"))
            {
                int j = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("alwaysErrorCount"));
                if(j == -1)
                {
                    hashmap.put("alwaysErrorCount", "1");
                }
                s1 = " and " + s7 + "Count >= " + hashmap.get("alwaysErrorCount");
            } else
            if(s8.equals("multiple"))
            {
                int k = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("multipleStartCount"));
                if(k <= 0)
                {
                    hashmap.put("multipleStartCount", "1");
                }
                int j1 = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("multipleErrorCount"));
                if(j1 <= 0)
                {
                    hashmap1.put("when", "every count must a number greater than zero");
                }
                if(j1 <= 0)
                {
                    j1 = 1;
                }
                float f = j1;
                int k1 = k % j1;
                if(k1 < 1000)
                {
                    f += (float)k1 / 1000F;
                }
                s1 = " and " + s7 + "Count >= " + k + " and " + s7 + "Count multipleOf " + f;
            } else
            if(s8.equals("allErrors"))
            {
                s1 = " and group.monitorsInGroup == group.monitorsInError and errorCount == 1";
            } else
            if(s8.equals("maxErrors"))
            {
                int l = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("maxErrorCount"));
                if(l <= 0)
                {
                    hashmap.put("maxErrorCount", "1");
                }
                s1 = " and group.maxErrorCount == " + hashmap.get("maxErrorCount") + " and errorCount == " + hashmap.get("maxErrorCount");
            }
        }
        if(hashmap.get("nameMatchString") != null && ((String)hashmap.get("nameMatchString")).length() > 0)
        {
            s3 = " and _name contains '" + hashmap.get("nameMatchString") + "'";
        }
        if(hashmap.get("statusMatchString") != null && ((String)hashmap.get("statusMatchString")).length() > 0)
        {
            s5 = " and stateString contains '" + hashmap.get("statusMatchString") + "'";
        }
        if(hashmap.get("classMatchString") != null && ((String)hashmap.get("classMatchString")).length() > 0 && ((String)hashmap.get("classMatchString")).indexOf("Any") < 0)
        {
            s4 = " and _class contains '" + hashmap.get("classMatchString") + "'";
        }
        if(s7.equals("good") && hashmap.get("usePreviousErrorCount") != null && ((String)hashmap.get("usePreviousErrorCount")).length() > 0)
        {
            int i1 = com.dragonflow.Properties.StringProperty.toInteger((String)hashmap.get("previousErrorCount"));
            if(i1 <= 0)
            {
                hashmap1.put("previousErrorCount", "error count must a number greater than zero");
            }
            s2 = " and errorCount >= " + hashmap.get("previousErrorCount");
        }
        String s9 = "";
        String s10 = (String)hashmap.get("alertDisable");
        if(s10 == null)
        {
            s10 = "";
        }
        if(s10.equals("permanent"))
        {
            if(actionAllowed("_alertDisable"))
            {
                s9 = "disabled and ";
            } else
            {
                hashmap1.put("alertDisable", "Permission denied");
            }
        } else
        if(s10.equals("timed"))
        {
            if(actionAllowed("_alertTempDisable"))
            {
                long l1 = Long.parseLong((String)hashmap.get("disableAlertTime"));
                if(l1 <= 0L)
                {
                    hashmap1.put("disableAlertTime", "Duration of alert disable missing");
                } else
                {
                    String s11 = (String)hashmap.get("disableAlertUnits");
                    if(s11 != null)
                    {
                        if(s11.equals("minutes"))
                        {
                            l1 *= com.dragonflow.Utils.TextUtils.MINUTE_SECONDS;
                        } else
                        if(s11.equals("hours"))
                        {
                            l1 *= com.dragonflow.Utils.TextUtils.HOUR_SECONDS;
                        } else
                        if(s11.equals("days"))
                        {
                            l1 *= com.dragonflow.Utils.TextUtils.DAY_SECONDS;
                        }
                    }
                    l1 *= 1000L;
                    l1 += com.dragonflow.SiteView.Platform.timeMillis();
                    s6 = " and monitorDoneTime >= " + (new Long(l1)).toString();
                    com.dragonflow.Utils.TextUtils.debugPrint("alert disabled until " + com.dragonflow.Utils.TextUtils.dateToString(l1));
                }
            } else
            {
                hashmap1.put("alertDisable", "Permission denied");
            }
        } else
        if(s10.equals("schedule"))
        {
            if(actionAllowed("_alertTempDisable"))
            {
                if(com.dragonflow.Utils.TextUtils.isDateStringValid((String)hashmap.get("startTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid((String)hashmap.get("startTimeTime")) && com.dragonflow.Utils.TextUtils.isDateStringValid((String)hashmap.get("endTimeDate")) && com.dragonflow.Utils.TextUtils.isTimeStringValid((String)hashmap.get("endTimeTime")))
                {
                    long l2 = com.dragonflow.Utils.TextUtils.dateStringToSeconds((String)hashmap.get("startTimeDate"), (String)hashmap.get("startTimeTime"));
                    long l3 = com.dragonflow.Utils.TextUtils.dateStringToSeconds((String)hashmap.get("endTimeDate"), (String)hashmap.get("endTimeTime"));
                    if(l3 <= com.dragonflow.SiteView.Platform.timeMillis() / 1000L)
                    {
                        hashmap1.put("alertDisable", "End time is in the past");
                    }
                    if(l2 > l3)
                    {
                        hashmap1.put("alertDisable", "End time must be later than start time");
                    }
                    l2 *= 1000L;
                    l3 *= 1000L;
                    s6 = " and monitorDoneTime <= " + l2 + " or monitorDoneTime >= " + l3;
                } else
                {
                    if(!com.dragonflow.Utils.TextUtils.isDateStringValid((String)hashmap.get("startTimeDate")))
                    {
                        hashmap1.put("startTimeDate", "Start date is invalid (use MM/DD/YY format)");
                    }
                    if(!com.dragonflow.Utils.TextUtils.isTimeStringValid((String)hashmap.get("startTimeTime")))
                    {
                        hashmap1.put("startTimeTime", "Start time is invalid (use HH:MM format)");
                    }
                    if(!com.dragonflow.Utils.TextUtils.isDateStringValid((String)hashmap.get("endTimeDate")))
                    {
                        hashmap1.put("endTimeDate", "End date is invalid (use MM/DD/YY format)");
                    }
                    if(!com.dragonflow.Utils.TextUtils.isTimeStringValid((String)hashmap.get("endTimeTime")))
                    {
                        hashmap1.put("endTimeTime", "End time is invalid (use HH:MM format)");
                    }
                }
            } else
            {
                hashmap1.put("alertDisable", "Permission denied");
            }
        } else
        if(s10.equals("undo"))
        {
            if(actionAllowed("_alertDisable") || actionAllowed("_alertTempDisable"))
            {
                s6 = "";
                s9 = "";
            } else
            {
                hashmap1.put("alertDisable", "Permission denied");
            }
        }
        return s9 + "category eq '" + s7 + "'" + s1 + s2 + s3 + s5 + s4 + s6 + "\t" + s;
    }

    public jgl.HashMap parseCondition(String raw, jgl.HashMap hashmap, String group, String monitor)
        throws Exception
    {
        jgl.HashMap hashmap1 = new HashMap();
        hashmap1.put("raw", raw);
        hashmap1.put("group", group);
        hashmap1.put("monitor", monitor);
        jgl.Array array = com.dragonflow.SiteView.Platform.split('\t', raw);
        int i = array.size();
        String alertEpr = (String)array.at(0);
        String alertAction = (String)array.at(1);
        String alertid = (String)array.at(2);
        hashmap1.put("expression", alertEpr);
        hashmap1.put("id", alertid);
        hashmap1.put("action", alertAction);
        if(i >= 3)
        {
            for(int j = 3; j < i; j++)
            {
                String s6 = (String)array.at(j);
                if(s6.startsWith("_UIContext="))
                {
                    hashmap1.put("_UIContext", s6.substring("_UIContext".length() + 1));
                    continue;
                }
                if(s6.startsWith("_name="))
                {
                    hashmap1.put("_name", s6.substring("_name".length() + 1));
                }
            }

        }
        com.dragonflow.SiteView.Action action = com.dragonflow.SiteView.Action.createAction(getActionClass(alertAction));
        com.dragonflow.SiteView.SiteViewObject siteviewobject = getSiteView();
        if(!group.equals("_master"))
        {
            siteviewobject = siteviewobject.getElement(com.dragonflow.Utils.I18N.toDefaultEncoding(group));
        }
        action.setOwner(siteviewobject);
        String fullId = siteviewobject.getFullID();
        if(!monitor.equals("_config"))
        {
            fullId = fullId + "/" + monitor;
        }
        hashmap1.put("fullID", fullId + "/" + alertid);
        jgl.Array array1 = new Array();
        com.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
        getActionArguments(alertAction, array1, hashmapordered);
        action.initializeFromArguments(array1, hashmapordered);
        String category = getCategory(alertEpr);
        hashmap1.put("category", category);
        String categoryName = getCategoryName(category);
        int k = getErrorCount(alertEpr);
        if(k != -1)
        {
            categoryName = categoryName + " x " + k;
        }
        int l = getMultipleErrorCount(alertEpr);
        if(l != -1)
        {
            int i1 = getAlwaysErrorCount(alertEpr);
            categoryName = categoryName + " at least x " + i1 + ", every " + l;
        } else
        {
            int j1 = getAlwaysErrorCount(alertEpr);
            if(k == -1 && j1 > 1)
            {
                categoryName = categoryName + " at least x " + j1;
            }
        }
        int k1 = getMaxErrorCount(alertEpr);
        if(k1 != -1)
        {
            categoryName = "group error x " + k1;
        }
        if(alertEpr.indexOf("group.monitorsInError") >= 0)
        {
            categoryName = "all in error";
        }
        String s10 = getStatusString(alertEpr);
        if(s10.length() > 0)
        {
            categoryName = categoryName + ", status \"" + s10 + "\"";
        }
        String s11 = getDisabled(alertEpr);
        if(s11.length() > 0)
        {
            categoryName = "<B>(" + s11 + ")</B><BR>" + categoryName;
            hashmap1.put("disabled", "true");
        }
        hashmap1.put("on", categoryName);
        hashmap1.put("command", action.getClassProperty("label"));
        hashmap1.put("do", action.getActionDescription());
        String s12 = getNameString(alertEpr);
        String s13 = conditionName(group, hashmap, array);
        if(s12.length() > 0)
        {
            s13 = s13 + ", name \"" + s12 + "\"";
        }
        hashmap1.put("for", s13);
        hashmap1.put("groupName", displayName(group, array));
        return hashmap1;
    }

    private jgl.HashMap processToOtherProperties(SSInstanceProperty assinstanceproperty[])
    {
        jgl.HashMap hashmap = new HashMap(true);
        String s1 = "";
        for(int i = 0; i < assinstanceproperty.length; i++)
        {
            if(assinstanceproperty[i].getName().equals("toOther"))
            {
                s1 = (String)assinstanceproperty[i].getValue();
            } else
            {
                hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }
            if(!assinstanceproperty[i].getName().equals("_machine"))
            {
                continue;
            }
            String s = (String)assinstanceproperty[i].getValue();
            if(s == null)
            {
                continue;
            }
            String s2 = getHostname();
            if(s2 != null && !s2.equals(s))
            {
                hashmap.add(assinstanceproperty[i].getName(), assinstanceproperty[i].getValue());
            }
        }

        if(s1.length() > 0)
        {
            hashmap.put("_to", s1);
        }
        return hashmap;
    }

    public void removeCondition(Alert alert)
    {
        mungeCondition(alert, null);
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @param s2
     * @return
     * @throws com.dragonflow.SiteViewException.SiteViewException
     */
    public java.util.Vector test(String s, String s1, String s2)
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        try {
        java.util.Vector vector;
        java.io.StringWriter stringwriter;
        java.io.PrintWriter printwriter;
        com.dragonflow.SiteView.Monitor monitor;
            Alert alert = Alert.getInstance().getByID(Long.parseLong(s));
            stringwriter = new StringWriter();
            printwriter = new PrintWriter(stringwriter);
            monitor = null;
            if(s1 != null && !s1.equals(""))
            {
                com.dragonflow.SiteView.MonitorGroup monitorgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView().getGroup(s1);
                if(monitorgroup == null)
                {
                    throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                        "APIAlert", "test"
                    }, 0L, "Error: Could not find target monitor to test alert");
                }
                java.util.Enumeration enumeration = monitorgroup.getMonitors();
                com.dragonflow.SiteView.Monitor monitor1;
                String s4;
                while (enumeration.hasMoreElements())
                    {
                    monitor1 = (com.dragonflow.SiteView.Monitor)enumeration.nextElement();
                    s4 = monitor1.getProperty("_id");
                if (s2.equals(s4)) {
                monitor = monitor1;
                }
                    }
            } else
            {
                monitor = getTestMonitor(alert);
            }

            boolean flag = false;
        printwriter.print("Testing alert\n");
        if(monitor == null)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "test"
            }, 0L, "Error: Could not find target monitor to test alert");
        }
        java.util.Enumeration enumeration1 = monitor.getActionRules();
        while (enumeration1.hasMoreElements())
            {
            com.dragonflow.SiteView.Rule rule = (com.dragonflow.SiteView.Rule)enumeration1.nextElement();
            if(!rule.getProperty("_alertID").equals(s))
            {
                continue;
            }
            rule.doAction(monitor, printwriter);
            flag = true;
            break;
        } 
        
        if(!flag)
        {
            throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
                "APIAlert", "test"
            }, 0L, "Error: Could not find alert " + s);
        }
        String s3 = stringwriter.getBuffer().toString();
        String as[] = com.dragonflow.Utils.TextUtils.split(s3, "\n");
        vector = new Vector();
        for(int i = 0; i < as.length; i++)
        {
            vector.add(as[i]);
        }

        return vector;
        }
        catch (com.dragonflow.SiteViewException.SiteViewException e) {
        e.fillInStackTrace();
        throw e;
        }
        catch (Exception e) {
        throw new SiteViewOperationalException(com.dragonflow.Resource.SiteViewErrorCodes.ERR_OP_SS_ALERT_EXCEPTION, new String[] {
            "APIAlert", "test"
        }, 0L, e.getMessage());
        }
    }

    public Alert update(String s, String s1, SSInstanceProperty assinstanceproperty[])
        throws com.dragonflow.SiteViewException.SiteViewException
    {
        return addUpdate(true, s, s1, assinstanceproperty, "");
    }
}
