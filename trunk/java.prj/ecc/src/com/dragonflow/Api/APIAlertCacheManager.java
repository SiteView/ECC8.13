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

public class APIAlertCacheManager implements com.dragonflow.ConfigurationManager.CfgChangesSink {

    private static com.dragonflow.Api.APIAlertCacheManager instance = null;

    private jgl.HashMap instanceInfoCache;

    private jgl.Array conditionsCache;

    static java.lang.Object instanceLock = new Object();

    public APIAlertCacheManager() {
        instanceInfoCache = null;
        conditionsCache = null;
    }

    static com.dragonflow.Api.APIAlertCacheManager getInstance() {
        if (instance == null) {
            synchronized (instanceLock) {
                if (instance == null) {
                    instance = new APIAlertCacheManager();
                    com.dragonflow.SiteView.ConfigurationChanger.registerCfgChangesSink(instance);
                }
            }
        }
        return instance;
    }

    public void notifyAdjustedGroups(com.dragonflow.SiteView.SiteViewGroup siteviewgroup, java.util.Collection collection, java.util.Collection collection1, java.util.Collection collection2) {
        instanceInfoCache = null;
        conditionsCache = null;
    }

    jgl.HashMap getInstanceInfoCache() {
        return instanceInfoCache;
    }

    void setInstanceInfoCache(jgl.HashMap hashmap) {
        instanceInfoCache = hashmap;
    }

    jgl.Array getConditionsCache() {
        return conditionsCache;
    }

    void setConditionsCache(jgl.Array array) {
        conditionsCache = array;
    }

}
