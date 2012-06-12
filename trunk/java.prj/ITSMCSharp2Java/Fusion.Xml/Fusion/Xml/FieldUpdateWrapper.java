package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:31
 */
public class FieldUpdateWrapper {

	private bool m_bSubField;
	private ICollection m_iSubFields;
	private string m_strParent;
	private XmlElement m_xeField;

	public FieldUpdateWrapper(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param elField
	 */
	public FieldUpdateWrapper(XmlElement elField){

	}

	/**
	 * 
	 * @param elField
	 * @param strParent
	 */
	public FieldUpdateWrapper(XmlElement elField, string strParent){

	}

	public string FieldName(){
		return "";
	}

	public string FieldValue(){
		return "";
	}

	public bool IsSubField(){
		return null;
	}

	public string SubFieldParent(){
		return "";
	}

	public string SubFieldPurpose(){
		return "";
	}

	public ICollection SubFields(){
		return null;
	}

}