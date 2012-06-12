/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.ConfigurationManager;

import java.util.Collection;

import com.dragonflow.SiteView.SiteViewGroup;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public interface CfgChangesSink {

    public abstract void notifyAdjustedGroups(SiteViewGroup siteviewgroup, Collection<?> collection, Collection<?> collection1, Collection<?> collection2);
}
