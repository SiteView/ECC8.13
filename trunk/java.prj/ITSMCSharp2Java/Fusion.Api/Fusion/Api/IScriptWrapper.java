package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:53
 */
public interface IScriptWrapper {

	/**
	 * 
	 * @param currentBusOb
	 * @param currentField
	 */
	public Object Process(BusinessObject currentBusOb, Field currentField);

}