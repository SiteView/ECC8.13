package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:40
 */
public class BusObSecurity extends IBusObSecurity {

	private IBusObSecurity m_realBusObSecurity = null;

	public BusObSecurity(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param realBusObSecurity
	 */
	public BusObSecurity(IBusObSecurity realBusObSecurity){

	}

	/**
	 * 
	 * @param strItemName
	 * @param right
	 */
	public boolean HasItemRight(String strItemName, SecurityRight right){
		return null;
	}

	/**
	 * 
	 * @param right
	 */
	public boolean HasRight(SecurityRight right){
		return null;
	}

}