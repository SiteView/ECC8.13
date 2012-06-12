package Fusion;

import Fusion.control.IComparer;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:25
 */
public class KeyValuePairComparer extends IComparer {

	public KeyValuePairComparer(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param x
	 * @param y
	 */
	public int Compare(Object x, Object y){
		return 0;
	}

}