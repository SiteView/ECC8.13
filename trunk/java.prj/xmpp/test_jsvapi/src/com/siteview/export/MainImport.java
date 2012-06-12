package com.siteview.export;

public class MainImport {
	public static void main(String[] args) 
	{

		long l=System.currentTimeMillis();
		StringBuffer sb = new StringBuffer();
		
		SvCiTypeCategory svCiTypeCategory = new SvCiTypeCategory();
		svCiTypeCategory.run();
		sb.append(svCiTypeCategory.errorMsg);
		
		ImportEntityAndMonitor monitor = new ImportEntityAndMonitor();
		monitor.run();
		sb.append(monitor.errorMsg);
		
		SvMonitorEntityRelation relation = new SvMonitorEntityRelation();
		relation.run();
		sb.append(relation.errorMsg);
		
		
		AlertImport alert = new AlertImport();
		alert.run();
		sb.append(alert.errorMsg);
		
		System.out.println("¹Ø¼üÐÅÏ¢:\n" + sb.toString());
		
		System.out.println((System.currentTimeMillis()-l)/1000+"sec.");
	}
}