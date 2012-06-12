package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:37
 */
public class SqlServerFilterCriteria extends FusionAggregate implements ISqlServerFilterCriteria {

	public SqlServerFilterCriteria(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public SqlServerFilterCriteria(Object fusionObject){

	}

	public String ArticleName(){
		return "";
	}

	public String FilterName(){
		return "";
	}

	public boolean ForceInvalidateSnapshot(){
		return null;
	}

	public boolean ForceReinitSubscription(){
		return null;
	}

	public String JoinArticleName(){
		return "";
	}

	public String JoinFilterClause(){
		return "";
	}

	public boolean JoinOnUniqueKey(){
		return null;
	}

	private Fusion.BusinessLogic.SqlServerFilterCriteria WhoAmI(){
		return null;
	}

}