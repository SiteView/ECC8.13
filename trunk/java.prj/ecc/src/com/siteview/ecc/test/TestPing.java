package com.siteview.ecc.test;

import java.util.Vector;

import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.StandardMonitor.PingMonitor;

public class TestPing {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
		Vector monitors = siteviewgroup.getAtomicMonitors();
		System.out.println("-------------");

	}

}
