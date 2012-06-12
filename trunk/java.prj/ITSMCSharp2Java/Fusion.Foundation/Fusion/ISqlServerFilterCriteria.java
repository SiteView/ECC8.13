package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:56
 */
public interface ISqlServerFilterCriteria {

	public String ArticleName();

	public String FilterName();

	public boolean ForceInvalidateSnapshot();

	public boolean ForceReinitSubscription();

	public String JoinArticleName();

	public String JoinFilterClause();

	public boolean JoinOnUniqueKey();

}