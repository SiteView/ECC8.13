package com.siteview.eccservice;

import java.util.HashMap;
import java.util.Vector;

public class RetMapInVector
{
	private String							estr;
	private boolean							retbool;
	private Vector<HashMap<String, String>>	vmap;
	
	public RetMapInVector()
	{
		estr = null;
		retbool = false;
		vmap = null;
	}
	
	public RetMapInVector(boolean isok, String inestr, Vector<HashMap<String, String>> invmap)
	{
		retbool = isok;
		estr = inestr;
		vmap = invmap;
	}
	
	public String getEstr()
	{
		return estr;
	}
	
	public boolean getRetbool()
	{
		return retbool;
	}
	
	public Vector<HashMap<String, String>> getVmap()
	{
		return vmap;
	}
	
	public void setEstr(String inestr)
	{
		estr = inestr;
	}
	
	public void setRetbool(boolean isok)
	{
		retbool = isok;
	}
	
	public void setVmap(Vector<HashMap<String, String>> invmap)
	{
		vmap = invmap;
	}
	
}
