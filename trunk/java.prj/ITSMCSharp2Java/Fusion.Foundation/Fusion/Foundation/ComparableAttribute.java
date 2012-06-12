package Fusion.Foundation;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 15:22:42
 */
public final class ComparableAttribute extends Attribute {

	private boolean m_bComparable;
	private boolean m_buseAsDefaultKeyInCollection;
	private boolean m_buseAsUltimateKeyInCollection;
	private CompareType m_compareType;
	private String m_strClassName;
	private String m_strCustomGroupName;
	private String m_strId;
	private String m_strMethodName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ComparableAttribute(){

	}

	/**
	 * 
	 * @param strID
	 */
	public ComparableAttribute(String strID){

	}

	/**
	 * 
	 * @param bComparable
	 * @param strID
	 */
	public ComparableAttribute(boolean bComparable, String strID){

	}

	/**
	 * 
	 * @param strID
	 * @param compareType
	 */
	public ComparableAttribute(String strID, CompareType compareType){

	}

	/**
	 * 
	 * @param bComparable
	 * @param strID
	 * @param compareType
	 */
	public ComparableAttribute(boolean bComparable, String strID, CompareType compareType){

	}

	/**
	 * 
	 * @param bComparable
	 * @param strID
	 * @param compareType
	 * @param strCustomGroupName
	 */
	public ComparableAttribute(boolean bComparable, String strID, CompareType compareType, String strCustomGroupName){

	}

	public String ClassName(){
		return "";
	}

	public boolean Comparable(){
		return null;
	}

	public CompareType ComparisonType(){
		return null;
	}

	public String CustomGroupName(){
		return "";
	}

	/**
	 * 
	 * @param obj
	 */
	public boolean Equals(Object obj){
		return null;
	}

	public int GetHashCode(){
		return 0;
	}

	public String Id(){
		return "";
	}

	public String MethodName(){
		return "";
	}

	public boolean UseAsDefaultKeyInCollection(){
		return null;
	}

	public boolean UseAsUltimateKeyInCollection(){
		return null;
	}

}