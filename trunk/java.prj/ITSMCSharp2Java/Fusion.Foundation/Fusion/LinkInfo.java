package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:05
 */
public class LinkInfo {

	private EmailAddressType m_addressType;
	private MessageAttributeType m_attributeType;
	private Object m_data;
	private String m_strParentField;

	public LinkInfo(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param data
	 * @param addressType
	 */
	public LinkInfo(Object data, EmailAddressType addressType){

	}

	/**
	 * 
	 * @param data
	 * @param attributeType
	 */
	public LinkInfo(Object data, MessageAttributeType attributeType){

	}

	/**
	 * 
	 * @param data
	 * @param strParentField
	 */
	public LinkInfo(Object data, String strParentField){

	}

	public Object Data(){
		return null;
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

}