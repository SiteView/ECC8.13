package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:21
 */
public class AggregateFactory extends IAggregateFactory {

	public AggregateFactory(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObj
	 */
	public AggregateBase Create(Object fusionObj){
		return null;
	}

	/**
	 * 
	 * @param fusionObj
	 */
	public boolean HasAggregate(Object fusionObj){
		return false;
	}

	/**
	 * 
	 * @param strDefClassName
	 */
	public boolean HasAggregate(String strDefClassName){
		return false;
	}

}

