package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:43
 */
public interface IAggregateFactory {

	/**
	 * 
	 * @param fusionObj
	 */
	public AggregateBase Create(Object fusionObj);

	/**
	 * 
	 * @param fusionObj
	 */
	public boolean HasAggregate(Object fusionObj);

	/**
	 * 
	 * @param DefClassName
	 */
	public boolean HasAggregate(String DefClassName);

}