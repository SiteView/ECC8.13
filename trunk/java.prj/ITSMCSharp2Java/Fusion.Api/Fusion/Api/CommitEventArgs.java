package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:43
 */
public class CommitEventArgs extends FusionAggregate {

	public CommitEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public CommitEventArgs(Object fusionObject){

	}

	public PlaceHolder CompareDef(){
		return null;
	}

	public int CurrentComparePosition(){
		return 0;
	}

	public PlaceHolder CurrentDef(){
		return null;
	}

	public int CurrentPosition(){
		return 0;
	}

	/**
	 * 
	 * @param nTotal
	 * @param nCurrent
	 */
	public void SetCount(int nTotal, int nCurrent){

	}

	public ValidationStatus Status(){
		return null;
	}

	public int TotalCompareObjects(){
		return 0;
	}

	public int TotalObjects(){
		return 0;
	}

	private Fusion.BusinessLogic.CommitEventArgs WhoAmI(){
		return null;
	}

}