package com.siteview.ecc.init;

import org.ofbiz.base.util.Debug;

import SiteViewMain.SiteViewSupport;

public class SiteViewThread extends Thread {
	public static final String module = SiteViewThread.class.getName();
	public SiteViewThread()
	{
        SiteViewSupport.InitProcess();
        SiteViewSupport.InitProcess2();
	}
	public void run()
	{
		try {
			SiteViewSupport.StartProcess();/*∆Ù∂Øº‡≤‚œﬂ≥Ã*/
			SiteViewSupport.WaitForProcess();
		} finally {
	    	SiteViewSupport.ShutdownProcess();
	    	Debug.logInfo("SiteView service be stoped!", module);
		}
	}
	
}
