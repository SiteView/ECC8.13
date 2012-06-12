package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:44:27
 */
public class FieldDef extends BllDefinitionObject {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:44:27
	 */
	private class MessageTags {

		private String BinaryFieldDefRights_AllowChangeLength = "BinaryFieldDefRights.AllowChangeLength";
		private String FieldDefRights_AllowChangeDataTypeId = "FieldDefRights.AllowChangeDataType";
		private String FieldDefRights_AllowChangeRuleBasedPropertiesId = "FieldDefRights.AllowChangeRuleBasedProperties";
		private String FieldDefRights_AllowChangeStateBasedRulePropertiesId = "FieldDefRights.AllowChangeStateBasedRuleProperties";
		private String TextFieldDefRights_AllowChangeLength = "TextFieldDefRights.AllowChangeLength";

		public MessageTags(){

		}

		public void finalize() throws Throwable {

		}

		public String getBinaryFieldDefRights_AllowChangeLength(){
			return BinaryFieldDefRights_AllowChangeLength;
		}

		public String getFieldDefRights_AllowChangeDataTypeId(){
			return FieldDefRights_AllowChangeDataTypeId;
		}

		public String getFieldDefRights_AllowChangeRuleBasedPropertiesId(){
			return FieldDefRights_AllowChangeRuleBasedPropertiesId;
		}

		public String getFieldDefRights_AllowChangeStateBasedRulePropertiesId(){
			return FieldDefRights_AllowChangeStateBasedRulePropertiesId;
		}

		public String getTextFieldDefRights_AllowChangeLength(){
			return TextFieldDefRights_AllowChangeLength;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBinaryFieldDefRights_AllowChangeLength(String newVal){
			BinaryFieldDefRights_AllowChangeLength = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldDefRights_AllowChangeDataTypeId(String newVal){
			FieldDefRights_AllowChangeDataTypeId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldDefRights_AllowChangeRuleBasedPropertiesId(String newVal){
			FieldDefRights_AllowChangeRuleBasedPropertiesId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFieldDefRights_AllowChangeStateBasedRulePropertiesId(String newVal){
			FieldDefRights_AllowChangeStateBasedRulePropertiesId = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTextFieldDefRights_AllowChangeLength(String newVal){
			TextFieldDefRights_AllowChangeLength = newVal;
		}

	}

	private Fusion.BusinessLogic.FieldDef m_oldField;

	public FieldDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public FieldDef(Object fusionObject){

	}

	/**
	 * 
	 * @param strPurpose
	 * @param subField
	 */
	public void AddSubField(String strPurpose, Fusion.Api.FieldDef subField){

	}

	public boolean AllowDecimal(){
		return null;
	}

	public boolean AllowEmpty(){
		return null;
	}

	public boolean AllowEndOfLineChars(){
		return null;
	}

	public boolean AllowNegative(){
		return null;
	}

	public Fusion.Api.RuleDef AutoFillRule(){
		return null;
	}

	public String BaseDefaultValue(){
		return "";
	}

	public String BaseQualifiedName(){
		return "";
	}

	public Fusion.Api.RuleDef BeforeSave(){
		return null;
	}

	public Fusion.Api.RuleDef BeforeStateChange(){
		return null;
	}

	public Fusion.Api.BinaryFieldDefRights BinaryFieldDefRights(){
		return null;
	}

	public String BinaryFieldEncoding(){
		return "";
	}

	public int BinaryFieldLength(){
		return 0;
	}

	public Fusion.Api.BusinessObjectDef BusObDef(){
		return null;
	}

	public Fusion.Api.RuleDef CalculationRule(){
		return null;
	}

	public static String ClassName(){
		return "";
	}

	public boolean ClearIfReadOnly(){
		return null;
	}

	public Fusion.Api.FieldDef Clone(){
		return null;
	}

	/**
	 * 
	 * @param defOwner
	 */
	public Fusion.Api.FieldDef Clone(Fusion.Api.DefinitionObject defOwner){
		return null;
	}

	public boolean CommonlySearched(){
		return null;
	}

	/**
	 * 
	 * @param fldCategory
	 */
	public void ConvertTo(FieldCategory fldCategory){

	}

	public Fusion.Api.FieldDef CreateVirtualCopy(){
		return null;
	}

	public String CurrencySymbol(){
		return "";
	}

	public String CustomDateFormat(){
		return "";
	}

	public String CustomTimeFormat(){
		return "";
	}

	public Fusion.Xml.DateFormat DateFormat(){
		return null;
	}

	public int DecimalDigits(){
		return 0;
	}

	public Fusion.Api.RuleDef DefaultValueRule(){
		return null;
	}

	public boolean DoNotTranslate(){
		return null;
	}

	public boolean ExcludeFromForm(){
		return null;
	}

	public boolean ExcludeFromGrid(){
		return null;
	}

	public Fusion.Api.FieldDefRights FieldDefRights(){
		return null;
	}

	public FieldCategory FieldType(){
		return null;
	}

	/**
	 * 
	 * @param sID
	 */
	public Fusion.Api.FieldDef GetSubFieldByID(String sID){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public Fusion.Api.FieldDef GetSubFieldByName(String strName){
		return null;
	}

	/**
	 * 
	 * @param strPurpose
	 */
	public Fusion.Api.FieldDef GetSubFieldByPurpose(String strPurpose){
		return null;
	}

	public Fusion.Api.RuleDef GetTableOrListValidationRule(){
		return null;
	}

	private BinaryFieldDef IAmBinaryField(){
		return null;
	}

	private DateTimeFieldDef IAmDateTimeField(){
		return null;
	}

	private LogicalFieldDef IAmLogicalField(){
		return null;
	}

	private NumberFieldDef IAmNumberField(){
		return null;
	}

	private TextFieldDef IAmTextField(){
		return null;
	}

	public boolean IsBinary(){
		return null;
	}

	public boolean IsCalculated(){
		return null;
	}

	public boolean IsDateTime(){
		return null;
	}

	public boolean IsEncrypted(){
		return null;
	}

	public boolean IsGroupDerivationField(){
		return null;
	}

	public boolean IsLinkField(){
		return null;
	}

	public boolean IsLogical(){
		return null;
	}

	public boolean IsNumber(){
		return null;
	}

	public boolean IsOrderable(){
		return null;
	}

	public boolean IsSearchable(){
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

	public boolean IsValidationField(){
		return null;
	}

	public boolean IsVirtual(){
		return null;
	}

	public boolean JustDate(){
		return null;
	}

	public boolean JustTime(){
		return null;
	}

	public CultureInfo Language(){
		return null;
	}

	public boolean LargeTextField(){
		return null;
	}

	public int MaximumAllowedLength(){
		return 0;
	}

	public int MaximumAllowedSearchLength(){
		return 0;
	}

	public boolean ObeySystemSettings(){
		return null;
	}

	public Fusion.Api.DefinitionObject ParentDef(){
		return null;
	}

	public String QualifiedName(){
		return "";
	}

	public String QualifiedStorageName(){
		return "";
	}

	public Fusion.Api.RuleDef ReadOnlyRule(){
		return null;
	}

	public String RecalculateOnLoad(){
		return "";
	}

	/**
	 * 
	 * @param strPurpose
	 */
	public void RemoveSubField(String strPurpose){

	}

	public void RemoveSubFields(){

	}

	public Fusion.Api.RuleDef RequiredRule(){
		return null;
	}

	public void Revert(){

	}

	public void SetLengthMaxForBinaryField(){

	}

	public void SetLengthMaxForTextField(){

	}

	public void SetLengthMaxSearchable(){

	}

	/**
	 * 
	 * @param defFormat
	 */
	public void SetTextFieldInLineFormat(Fusion.Api.FormatDef defFormat){

	}

	/**
	 * 
	 * @param strId
	 * @param strName
	 */
	public void SetTextFieldNamedFormat(String strId, String strName){

	}

	public boolean ShowCurrency(){
		return null;
	}

	public boolean ShowSeparator(){
		return null;
	}

	public Fusion.Api.FieldDef SubFieldParent(){
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

	public Type SystemType(){
		return null;
	}

	public Fusion.Api.TextFieldDefRights TextFieldDefRights(){
		return null;
	}

	public String TextFieldEncoding(){
		return "";
	}

	public Fusion.Api.FormatDef TextFieldFormat(){
		return null;
	}

	public boolean TextFieldHasInLineFormat(){
		return null;
	}

	public int TextFieldLength(){
		return 0;
	}

	public String TextFieldNamedFormat(){
		return "";
	}

	public String TextFieldNamedFormatId(){
		return "";
	}

	public Fusion.Xml.TimeFormat TimeFormat(){
		return null;
	}

	public boolean UseCurrencySymbol(){
		return null;
	}

	/**
	 * 
	 * @param nLength
	 */
	private void ValidateBinaryFieldMaximumLength(int nLength){

	}

	/**
	 * 
	 * @param nLength
	 */
	private void ValidateBinaryFieldMinimumLength(int nLength){

	}

	/**
	 * 
	 * @param nLength
	 */
	private void ValidateTextFieldMaximumLength(int nLength){

	}

	/**
	 * 
	 * @param nLength
	 */
	private void ValidateTextFieldMinimumLength(int nLength){

	}

	public Fusion.Api.RuleDef ValidationRule(){
		return null;
	}

	public String ValueForFalse(){
		return "";
	}

	public String ValueForTrue(){
		return "";
	}

	private Fusion.BusinessLogic.FieldDef WhoAmI(){
		return null;
	}

	public int WholeDigits(){
		return 0;
	}

}