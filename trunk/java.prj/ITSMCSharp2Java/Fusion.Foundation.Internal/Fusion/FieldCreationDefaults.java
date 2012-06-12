package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:22
 */
public class FieldCreationDefaults {

	private boolean AllowNullDefault = true;
	private String DefaultValueDefault = "";
	private boolean FixedWidthDefault = false;
	private boolean HasUniqueValuesDefault = false;
	private boolean m_bFieldAllowsNull;
	private boolean m_bFieldHasUniqueValues;
	private boolean m_bFieldIsFixedWidth;
	private boolean m_bFieldUsesUnicode;
	private String m_strFieldDefaultValue;
	private boolean UseUnicodeDefault = false;



	public void finalize() throws Throwable {

	}

	protected FieldCreationDefaults(){

	}

	/**
	 * 
	 * @param settings
	 */
	public FieldCreationDefaults(ISettings settings){

	}

	/**
	 * 
	 * @param bUseUnicode
	 */
	public FieldCreationDefaults(boolean bUseUnicode){

	}

	/**
	 * 
	 * @param bFixedWidth
	 * @param bNullAllowed
	 * @param bUniqueValues
	 * @param bUseUnicode
	 * @param strDefaultValue
	 */
	public FieldCreationDefaults(boolean bFixedWidth, boolean bNullAllowed, boolean bUniqueValues, boolean bUseUnicode, String strDefaultValue){

	}

	public FieldCreationDefaults Clone(){
		return null;
	}

	/**
	 * 
	 * @param fldDefaults
	 */
	public boolean Compare(FieldCreationDefaults fldDefaults){
		return null;
	}

	/**
	 * 
	 * @param fldDefaults
	 */
	public void CopyContents(FieldCreationDefaults fldDefaults){

	}

	public boolean FieldAllowsNull(){
		return null;
	}

	public String FieldDefaultValue(){
		return "";
	}

	public boolean FieldHasUniqueValues(){
		return null;
	}

	public boolean FieldIsFixedWidth(){
		return null;
	}

	public boolean FieldUsesUnicode(){
		return null;
	}

	public boolean getAllowNullDefault(){
		return AllowNullDefault;
	}

	public String getDefaultValueDefault(){
		return DefaultValueDefault;
	}

	public boolean getFixedWidthDefault(){
		return FixedWidthDefault;
	}

	public boolean getHasUniqueValuesDefault(){
		return HasUniqueValuesDefault;
	}

	public boolean getUseUnicodeDefault(){
		return UseUnicodeDefault;
	}

	/**
	 * 
	 * @param settings
	 */
	public void LoadFromSettings(ISettings settings){

	}

	/**
	 * 
	 * @param settings
	 */
	public void SaveToSettings(ISettings settings){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAllowNullDefault(boolean newVal){
		AllowNullDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefaultValueDefault(String newVal){
		DefaultValueDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFixedWidthDefault(boolean newVal){
		FixedWidthDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHasUniqueValuesDefault(boolean newVal){
		HasUniqueValuesDefault = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUseUnicodeDefault(boolean newVal){
		UseUnicodeDefault = newVal;
	}

}