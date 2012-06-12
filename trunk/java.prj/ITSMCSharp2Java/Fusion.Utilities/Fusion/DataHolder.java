package Fusion;

import Fusion.control.DateTime;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:12
 */
public abstract class DataHolder {

	private DateTime m_CreationTime;
	private CacheDetail m_LevelOfDetail;
	private double m_TimeToLive;



	public void finalize() throws Throwable {

	}

	public DataHolder(){

	}

	/**
	 * 
	 * @param TimeToLive
	 */
	public DataHolder(int TimeToLive){

	}

	public double Age(){
		return 0;
	}

	public CacheDetail Detail(){
		return null;
	}

	public void Expire(){

	}

	public Boolean Expired(){
		return null;
	}

	public void ResetAge(){

	}

	public DateTime TimeOfCreation(){
		return null;
	}

}