package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:48
 */
public interface IGatherStatistics {

	public String BusObName();

	public String FieldName();

	public String GroupByFieldName1();

	public String GroupByFieldName2();

	public String Id();

	public String Name();

	public QueryFunctions QueryFunction();

	public String QueryGroupName();

	public Scope QueryGroupScope();

	public String QueryGroupScopeOwner();

	public int RefreshFrequency();

	public TimeUnit RefreshFrequencyTimeUnit();

}