package com.siteview.ecc.init;

import org.ofbiz.base.util.Debug;

import SiteViewMain.SiteViewSupport;

public class SiteViewThread extends Thread {
	public static final String module = SiteViewThread.class.getName();
	public SiteViewThread()
	{
        SiteViewSupport.InitProcess();
        SiteViewSupport.InitProcess2();
        SiteViewSupport.StartProcess();/*∆Ù∂Øº‡≤‚œﬂ≥Ã*/
		
	}
	public void run()
	{
		try {
			SiteViewSupport.WaitForProcess();
		} finally {
	    	 SiteViewSupport.ShutdownProcess();
	    	 Debug.logInfo("Monitor service be stoped!", module);
		}
	}
}
