package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:47
 */
public class ConstraintDefContainer extends BllDefinitionObject implements IModifyConstraints {

	public ConstraintDefContainer(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ConstraintDefContainer(Object fusionObject){

	}

	/**
	 * 
	 * @param constraint
	 */
	public int AddConstraint(Fusion.Api.ConstraintDef constraint){
		return 0;
	}

	public int ConstraintCount(){
		return 0;
	}

	public List Constraints(){
		return null;
	}

	/**
	 * 
	 * @param correction
	 * @param bJustCollect
	 */
	public void CorrectNamedReference(NamedReferenceCorrection correction, boolean bJustCollect){

	}

	public void RemoveAllConstraints(){

	}

	/**
	 * 
	 * @param constraint
	 */
	public void RemoveConstraint(Fusion.Api.ConstraintDef constraint){

	}

	/**
	 * 
	 * @param iIndex
	 */
	public void RemoveConstraintAt(int iIndex){

	}

	/**
	 * 
	 * @param nIndex
	 */
	public Fusion.Api.ConstraintDef this(int nIndex){
		return null;
	}

	private Fusion.BusinessLogic.ConstraintDefContainer WhoAmI(){
		return null;
	}

}