package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:13
 */
public class NamedReferenceCorrection {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:13
	 */
	public enum ReferenceType {
		BusinessObject,
		BusinessObjectStorageName,
		Field,
		FieldStorageName,
		NamedRule,
		Relationship,
		Counter,
		Token,
		Layout,
		Dashboard,
		Other
	}

	private ArrayList m_alTouchedDefs;
	private Type m_ReferenceObjectType;
	private ReferenceType m_referenceType;
	private String m_strNewValue;
	private String m_strOldValue;
	private String m_strReferenceValue;



	public void finalize() throws Throwable {

	}

	public NamedReferenceCorrection(){

	}

	/**
	 * 
	 * @param referenceObjectType
	 * @param strReferenceValue
	 */
	public NamedReferenceCorrection(Type referenceObjectType, String strReferenceValue){

	}

	/**
	 * 
	 * @param referenceType
	 * @param oldValue
	 * @param newValue
	 */
	public NamedReferenceCorrection(ReferenceType referenceType, String oldValue, String newValue){

	}

	/**
	 * 
	 * @param referenceObjectType
	 * @param oldValue
	 * @param newValue
	 */
	public NamedReferenceCorrection(Type referenceObjectType, String oldValue, String newValue){

	}

	/**
	 * 
	 * @param o
	 */
	public void AddReferencedDefinition(Object o){

	}

	/**
	 * 
	 * @param refType
	 */
	public boolean IsType(ReferenceType refType){
		return null;
	}

	public String NewValue(){
		return "";
	}

	public Type ObjectOfReference(){
		return null;
	}

	public String OldValue(){
		return "";
	}

	public List ReferencedDefs(){
		return null;
	}

	public boolean ReferenceFound(){
		return null;
	}

	public String ReferenceValue(){
		return "";
	}

	public ReferenceType TypeOfReference(){
		return null;
	}

}