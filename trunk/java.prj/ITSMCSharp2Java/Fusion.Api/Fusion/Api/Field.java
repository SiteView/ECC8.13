package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:24
 */
public class Field extends MetaObject {

	private boolean m_bHasCheckedRight;
	private boolean m_bHasViewRight;

	public Field(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public Field(Object fusionObject){

	}

	/**
	 * 
	 * @param busOb
	 * @param field
	 * @param relationship
	 * @param linkField
	 */
	public static String BuildBusObField(String busOb, String field, String relationship, String linkField){
		return "";
	}

	/**
	 * 
	 * @param busOb
	 * @param field
	 * @param relationship
	 * @param purpose
	 */
	public static String BuildBusObFieldWithPurpose(String busOb, String field, String relationship, String purpose){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public void Clear(){

	}

	/**
	 * 
	 * @param name
	 * @param category
	 */
	public static Fusion.Api.Field CreateVirtualField(String name, FieldCategory category){
		return null;
	}

	public Fusion.Api.FieldDef Definition(){
		return null;
	}

	public FieldCategory FieldType(){
		return null;
	}

	public void FireNotificationsBasedOnField(){

	}

	/**
	 * 
	 * @param ur
	 */
	public void FireNotificationsBasedOnField(UpdateResult ur){

	}

	/**
	 * 
	 * @param linkField
	 */
	public static String GetPurposeFromLinkField(String linkField){
		return "";
	}

	public String GetString(){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.Field GetSubFieldByName(String strName){
		return null;
	}

	/**
	 * 
	 * @param strPurpose
	 */
	public Fusion.Api.Field GetSubFieldByPurpose(String strPurpose){
		return null;
	}

	public Fusion.Api.RuleDef GetTableOrListValidationRule(){
		return null;
	}

	/**
	 * 
	 * @param right
	 */
	protected boolean HasRight(SecurityRight right){
		return null;
	}

	/**
	 * 
	 * @param right
	 * @param bDeniedBecauseInFinalState
	 */
	protected boolean HasRight(SecurityRight right, boolean bDeniedBecauseInFinalState){
		return null;
	}

	public boolean IsBinary(){
		return null;
	}

	/**
	 * 
	 * @param fv
	 */
	public boolean IsDataDifferent(FusionValue fv){
		return null;
	}

	public boolean IsDateTime(){
		return null;
	}

	public boolean IsDirty(){
		return null;
	}

	public boolean IsEmpty(){
		return null;
	}

	public boolean IsLogical(){
		return null;
	}

	public boolean IsNumber(){
		return null;
	}

	public boolean IsReadOnly(){
		return null;
	}

	public boolean IsStateField(){
		return null;
	}

	public boolean IsSubField(){
		return null;
	}

	public boolean IsText(){
		return null;
	}

	/**
	 * 
	 * @param linkField
	 */
	public static boolean LinkFieldIsPurpose(String linkField){
		return null;
	}

	public Object NativeValue(){
		return null;
	}

	public FusionValue OldValue(){
		return null;
	}

	public FusionValue OriginalValue(){
		return null;
	}

	public Fusion.Api.BusinessObject OwningBusOb(){
		return null;
	}

	/**
	 * 
	 * @param val
	 */
	public UpdateResult SetValue(FusionValue val){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param bIgnoreDuplicateCheck
	 */
	public UpdateResult SetValue(FusionValue val, boolean bIgnoreDuplicateCheck){
		return null;
	}

	/**
	 * 
	 * @param result
	 * @param val
	 */
	public UpdateResult SetValue(UpdateResult result, FusionValue val){
		return null;
	}

	/**
	 * 
	 * @param result
	 * @param val
	 * @param bIgnoreDuplicateCheck
	 */
	public UpdateResult SetValue(UpdateResult result, FusionValue val, boolean bIgnoreDuplicateCheck){
		return null;
	}

	/**
	 * 
	 * @param BusObField
	 * @param BusObName
	 * @param FieldName
	 */
	public static void SplitBusObField(String BusObField, String BusObName, String FieldName){

	}

	/**
	 * 
	 * @param BusObField
	 * @param BusOb
	 * @param Field
	 * @param Relationship
	 * @param LinkField
	 */
	public static void SplitBusObField(String BusObField, String BusOb, String Field, String Relationship, String LinkField){

	}

	/**
	 * 
	 * @param fieldSubField
	 * @param field
	 * @param subFieldPurpose
	 */
	public static void SplitFieldSubFieldPurpose(String fieldSubField, String field, String subFieldPurpose){

	}

	public Fusion.Api.Field SubFieldParent(){
		return null;
	}

	public String SubFieldPurpose(){
		return "";
	}

	public List SubFieldPurposes(){
		return null;
	}

	public List SubFields(){
		return null;
	}

	/**
	 * 
	 * @param fldOld
	 */
	public void TransferFrom(Fusion.Api.Field fldOld){

	}

	public FusionValue Value(){
		return null;
	}

	/**
	 * 
	 * @param result
	 */
	private void VerifyRightsToChangeField(UpdateResult result){

	}

	private Fusion.BusinessLogic.Field WhoAmI(){
		return null;
	}

}