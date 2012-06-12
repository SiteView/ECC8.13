package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:43
 */
public interface IAggregate {

	public AggregateBase Aggregate();

	public String AggregateClassName();

	/**
	 * 
	 * @param factory
	 */
	public AggregateBase CreateAggregate(IAggregateFactory factory);

}