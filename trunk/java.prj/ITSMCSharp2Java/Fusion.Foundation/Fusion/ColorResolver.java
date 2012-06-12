package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:51
 */
public class ColorResolver {

	private static ColorResolver m_ColorResolver = null;
	private String NamedColor = "NAMED";
	private String RawColor = "RAW";
	private String SystemColor = "SYSTEM";
	private String UserColor = "USER";



	public void finalize() throws Throwable {

	}

	protected ColorResolver(){

	}

	/**
	 * 
	 * @param strCategoryAndName
	 * @param strCategory
	 * @param strName
	 */
	private void GetColorCategoryAndName(String strCategoryAndName, String strCategory, String strName){

	}

	/**
	 * 
	 * @param strColorCategory
	 * @param strColorName
	 */
	public Color GetColorForPair(String strColorCategory, String strColorName){
		return null;
	}

	/**
	 * 
	 * @param cl
	 */
	public String GetFusionColorForColor(Color cl){
		return "";
	}

	public String getNamedColor(){
		return NamedColor;
	}

	/**
	 * 
	 * @param strColor
	 */
	public Color GetNamedColorForString(String strColor){
		return null;
	}

	public String getRawColor(){
		return RawColor;
	}

	/**
	 * 
	 * @param strColor
	 */
	public Color GetRawColorForString(String strColor){
		return null;
	}

	public String getSystemColor(){
		return SystemColor;
	}

	/**
	 * 
	 * @param strColor
	 */
	public Color GetSystemColorForString(String strColor){
		return null;
	}

	public String getUserColor(){
		return UserColor;
	}

	/**
	 * 
	 * @param strColor
	 */
	public Color GetUserColorForString(String strColor){
		return null;
	}

	public static void InitializeColorResolver(){

	}

	/**
	 * 
	 * @param strCategoryAndName
	 */
	public boolean IsColorCategoryValid(String strCategoryAndName){
		return null;
	}

	/**
	 * 
	 * @param strCategoryAndName
	 */
	public Color ResolveColor(String strCategoryAndName){
		return null;
	}

	public static ColorResolver Resolver(){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNamedColor(String newVal){
		NamedColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRawColor(String newVal){
		RawColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSystemColor(String newVal){
		SystemColor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUserColor(String newVal){
		UserColor = newVal;
	}

}