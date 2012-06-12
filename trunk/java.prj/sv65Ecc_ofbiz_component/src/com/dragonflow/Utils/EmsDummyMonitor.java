/*
 * Created on 2005-2-9 3:06:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils;

import com.dragonflow.Properties.StringProperty;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

public class EmsDummyMonitor extends com.dragonflow.SiteView.AtomicMonitor {

    public EmsDummyMonitor() {
    }

    public String getHostname() {
        return "EmsDummyMonitor";
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
	static{
		addProperties(EmsDummyMonitor.class.getName(),
                new StringProperty[0]);
	}
}
