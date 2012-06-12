package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:31
 */
public class PersistenceAttribute extends Attribute {

	private EmailAddressType m_addressType;
	private MessageAttributeType m_attributeType;
	private boolean m_bSaveToFusion;
	private PropertyInfo m_property;
	private String m_strAnnotation;
	private String m_strParentField;

	public PersistenceAttribute(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strAnnotation
	 */
	public PersistenceAttribute(String strAnnotation){

	}

	/**
	 * 
	 * @param strAnnotation
	 * @param addressType
	 */
	public PersistenceAttribute(String strAnnotation, EmailAddressType addressType){

	}

	/**
	 * 
	 * @param strAnnotation
	 * @param attributeType
	 */
	public PersistenceAttribute(String strAnnotation, MessageAttributeType attributeType){

	}

	/**
	 * 
	 * @param strAnnotation
	 * @param strParentField
	 */
	public PersistenceAttribute(String strAnnotation, String strParentField){

	}

	public String Annotation(){
		return "";
	}

	public boolean IsAddress(){
		return null;
	}

	public boolean IsAddressList(){
		return null;
	}

	/**
	 * 
	 * @param attributeType
	 */
	public boolean IsAttributeType(MessageAttributeType attributeType){
		return null;
	}

	public String ParentField(){
		return "";
	}

	public PropertyInfo Property(){
		return null;
	}

	public boolean SaveToFusion(){
		return null;
	}

}