package Fusion.Utilities;

import Fusion.control.CollectionBase;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:08
 */
public class CacheItemInfoCollection extends CollectionBase {

	public CacheItemInfoCollection(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param item
	 */
	public int Add(CacheItemInfo item){
		return 0;
	}

	/**
	 * 
	 * @param item
	 */
	public Boolean Contains(CacheItemInfo item){
		return null;
	}

	/**
	 * 
	 * @param item
	 */
	public int IndexOf(CacheItemInfo item){
		return 0;
	}

	/**
	 * 
	 * @param index
	 * @param item
	 */
	public void Insert(int index, CacheItemInfo item){

	}

	/**
	 * 
	 * @param item
	 */
	public void Remove(CacheItemInfo item){

	}

	/**
	 * 
	 * @param index
	 */
	public CacheItemInfo getThis(int index){
		return null;
	}

}