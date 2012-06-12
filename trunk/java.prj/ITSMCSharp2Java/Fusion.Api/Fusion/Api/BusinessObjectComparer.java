package Fusion.Api;

import java.util.Comparator;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:33
 */
public class BusinessObjectComparer implements Comparator {

	private boolean m_bAscending;
	private String m_strFieldComparer;

	public BusinessObjectComparer(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strFieldComparer
	 * @param bAscending
	 */
	public BusinessObjectComparer(String strFieldComparer, boolean bAscending){

	}

	/**
	 * 
	 * @param x
	 * @param y
	 */
	@Override
	public int compare(Object o1, Object o2) {
		// TODO Auto-generated method stub
		return 0;
	}

}