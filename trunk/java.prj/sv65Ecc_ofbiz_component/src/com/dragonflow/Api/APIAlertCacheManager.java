/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Api;

import java.util.Collection;

import com.dragonflow.ConfigurationManager.CfgChangesSink;
import com.dragonflow.SiteView.ConfigurationChanger;
import com.dragonflow.SiteView.SiteViewGroup;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class APIAlertCacheManager implements CfgChangesSink {

    private static APIAlertCacheManager instance = null;

    private jgl.HashMap instanceInfoCache;

    private jgl.Array conditionsCache;

    static Object instanceLock = new Object();

    public APIAlertCacheManager() {
        instanceInfoCache = null;
        conditionsCache = null;
    }

    static APIAlertCacheManager getInstance() {
        if (instance == null) {
            synchronized (instanceLock) {
                if (instance == null) {
                    instance = new APIAlertCacheManager();
                    ConfigurationChanger.registerCfgChangesSink(instance);
                }
            }
        }
        return instance;
    }

    public void notifyAdjustedGroups(SiteViewGroup siteviewgroup, Collection<?> collection, Collection<?> collection1, Collection<?> collection2) {
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
