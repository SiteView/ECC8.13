package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:45
 */
public interface IBusObSecurity {

	/**
	 * 
	 * @param strItemName
	 * @param right
	 */
	public boolean HasItemRight(String strItemName, SecurityRight right);

	/**
	 * 
	 * @param right
	 */
	public boolean HasRight(SecurityRight right);

}