package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:16
 */
public class AggregateUtils {

	private static IAggregateFactory AggregateFactory = null;

	public AggregateUtils(){

	}

	public void finalize() throws Throwable {

	}

	public IAggregateFactory getAggregateFactory(){
		return AggregateFactory;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAggregateFactory(IAggregateFactory newVal){
		AggregateFactory = newVal;
	}

}