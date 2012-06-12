package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:47
 */
public class TableValidation extends RuleDef implements IModifyConstraints {

	public TableValidation(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public TableValidation(Object fusionObject){

	}

	/**
	 * 
	 * @param validationConstraint
	 */
	public int AddConstraint(Fusion.Api.ConstraintDef validationConstraint){
		return 0;
	}

	/**
	 * 
	 * @param query
	 * @param busObCurrent
	 */
	public XmlElement BuildConstraintsForQuery(FusionQuery query, Fusion.Api.BusinessObject busObCurrent){
		return null;
	}

	/**
	 * 
	 * @param query
	 * @param busObCurrent
	 * @param strToCompare
	 */
	public XmlElement BuildConstraintsForQuery(FusionQuery query, Fusion.Api.BusinessObject busObCurrent, String strToCompare){
		return null;
	}

	/**
	 * 
	 * @param busObjectCurrent
	 * @param fieldCurrent
	 * @param bExactValue
	 */
	public FusionQuery BuildQuery(Fusion.Api.BusinessObject busObjectCurrent, Fusion.Api.Field fieldCurrent, boolean bExactValue){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public int ConstraintCount(){
		return 0;
	}

	public List Constraints(){
		return null;
	}

	public String DefToBriefString(){
		return "";
	}

	public ValueSource DisplaySource(){
		return null;
	}

	public boolean Enforced(){
		return null;
	}

	public boolean MultiSelect(){
		return null;
	}

	public void RemoveAllConstraints(){

	}

	/**
	 * 
	 * @param validationConstraint
	 */
	public void RemoveConstraint(Fusion.Api.ConstraintDef validationConstraint){

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

	public boolean UneforcedDontBlankOnUnfound(){
		return null;
	}

	public boolean UnenforcedPopOnDupe(){
		return null;
	}

	public boolean UnenforcedPopOnNotFound(){
		return null;
	}

	public ValueSource ValidationSource(){
		return null;
	}

	private Fusion.BusinessLogic.Rules.TableValidation WhoAmI(){
		return null;
	}

}