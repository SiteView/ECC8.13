package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:03
 */
public class ValueSource extends FusionAggregate {

	private LiteralValue m_oldValue;

	public ValueSource(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ValueSource(Object fusionObject){

	}

	/**
	 * 
	 * @param functionCat
	 * @param fusionApi
	 */
	public ValueSource(FunctionCategory functionCat, IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param valueType
	 * @param fusionApi
	 */
	public ValueSource(ValueFrom valueType, IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param valueType
	 * @param strValue
	 * @param fusionApi
	 */
	public ValueSource(ValueFrom valueType, String strValue, IFusionApi fusionApi){

	}

	/**
	 * 
	 * @param vs
	 * @param fusionApi
	 * @param strValue
	 */
	public ValueSource(ValueSources vs, IFusionApi fusionApi, String strValue){

	}

	public static String ClassName(){
		return "";
	}

	/**
	 * 
	 * @param valueFrom
	 * @param fusionApi
	 */
	public void ConvertTo(ValueFrom valueFrom, FusionApi fusionApi){

	}

	public String Counter(){
		return "";
	}

	public FieldCategory DataType(){
		return null;
	}

	public EventHandler DefinitionChanged(){
		return null;
	}

	public String FieldRef(){
		return "";
	}

	public FunctionCategory FunctionType(){
		return null;
	}

	/**
	 * 
	 * @param evalBundle
	 */
	public FusionValue GetFusionValue(Fusion.Api.EvaluationBundle evalBundle){
		return null;
	}

	public String GetValueTypeAndValueAsString(){
		return "";
	}

	private CounterValue IAmCounter(){
		return null;
	}

	private DateTimeValue IAmDateTime(){
		return null;
	}

	private FieldValue IAmField(){
		return null;
	}

	private FieldRelationshipValue IAmFieldRelationship(){
		return null;
	}

	private FunctionValue IAmFunction(){
		return null;
	}

	private FusionQueryValue IAmFusionQuery(){
		return null;
	}

	private LiteralValue IAmLiteral(){
		return null;
	}

	private RuleRefValue IAmRuleRef(){
		return null;
	}

	private TokenValue IAmToken(){
		return null;
	}

	public boolean IsDateTime(){
		return false;
	}

	public boolean IsReferenced(){
		return false;
	}

	public boolean IsTimeSpan(){
		return false;
	}

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	private void OnDefChanged(Object sender, EventArgs e){

	}

	public FusionQuery Query(){
		return null;
	}

	public FusionQuery QueryDef(){
		return null;
	}

	public String QueryId(){
		return "";
	}

	public String QueryName(){
		return "";
	}

	public void Revert(){

	}

	public String RuleRef(){
		return "";
	}

	public String SerializableValue(){
		return "";
	}

	/**
	 * 
	 * @param strValue
	 * @param dtUnits
	 */
	public void SetDateTime(String strValue, DateTimeUnits dtUnits){

	}

	/**
	 * 
	 * @param literalValue
	 * @param dtUnits
	 */
	public void SetDateTimeLiteral(ValueSource literalValue, DateTimeUnits dtUnits){

	}

	/**
	 * 
	 * @param strRuleRef
	 * @param bIsRefId
	 */
	public void SetRuleRef(String strRuleRef, boolean bIsRefId){

	}

	public String Token(){
		return "";
	}

	public DateTimeUnits Units(){
		return null;
	}

	public FusionValue Value(){
		return null;
	}

	public String ValueToString(){
		return "";
	}

	public ValueFrom ValueType(){
		return null;
	}

	private LiteralValue WhoAmI(){
		return null;
	}

}