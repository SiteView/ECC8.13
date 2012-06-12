package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:21
 */
public class RelationshipDefRights extends DefRights {

	public RelationshipDefRights(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RelationshipDefRights(Object fusionObject){

	}

	public boolean AllowChangeCardinality(){
		return false;
	}

	public boolean AllowChangeConstraint(){
		return false;
	}

	public boolean AllowChangeRollUp(){
		return false;
	}

	public boolean AllowChangeRuleBasedProperties(){
		return false;
	}

	public static String ClassName(){
		return "";
	}

	private Fusion.BusinessLogic.RelationshipDefRights WhoAmI(){
		return null;
	}

}