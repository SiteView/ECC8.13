package com.siteview.eccservice;

import java.util.HashMap;

public class RetMapInMap
{
	private String										estr;
	private boolean										retbool;
	private HashMap<String, HashMap<String, String>>	fmap;
	
	public RetMapInMap()
	{
		estr = null;
		retbool = false;
		fmap = null;
	}
	
	public RetMapInMap(boolean isok, String inestr, HashMap<String, HashMap<String, String>> infmap)
	{
		retbool = isok;
		estr = inestr;
		fmap = infmap;
	}
	
	public String getEstr()
	{
		return estr;
	}
	
	public boolean getRetbool()
	{
		return retbool;
	}
	
	public HashMap<String, HashMap<String, String>> getFmap()
	{
		return fmap;
	}
	
	public void setEstr(String inestr)
	{
		estr = inestr;
	}
	
	public void setRetbool(boolean isok)
	{
		retbool = isok;
	}
	
	public void setFmap(HashMap<String, HashMap<String, String>> infmap)
	{
		fmap = infmap;
	}
	
}
