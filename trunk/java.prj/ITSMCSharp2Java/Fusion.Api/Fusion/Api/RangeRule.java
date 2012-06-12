package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:15
 */
public class RangeRule extends RuleDef {

	public RangeRule(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public RangeRule(Object fusionObject){

	}

	public static String ClassName(){
		return "";
	}

	public CompareMethod CompareValueMethod(){
		return null;
	}

	public String DefToBriefString(){
		return "";
	}

	public ValueSource LowerBound(){
		return null;
	}

	public boolean LowerBoundInclusive(){
		return false;
	}

	public ValueSource SourceValue(){
		return null;
	}

	public ValueSource UpperBound(){
		return null;
	}

	public boolean UpperBoundInclusive(){
		return false;
	}

	private Fusion.BusinessLogic.Rules.RangeRule WhoAmI(){
		return null;
	}

}