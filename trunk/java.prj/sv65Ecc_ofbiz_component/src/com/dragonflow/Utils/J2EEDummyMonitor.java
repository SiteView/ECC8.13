/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class J2EEDummyMonitor extends com.dragonflow.SiteView.AtomicMonitor {

    public J2EEDummyMonitor() {
    }

    public String getHostname() {
        return "J2EEDummyMonitor";
    }

	@Override
	public boolean getSvdbRecordState(String paramName, String operate,
			String paramValue) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getSvdbkeyValueStr() {
		// TODO Auto-generated method stub
		return null;
	}

}
