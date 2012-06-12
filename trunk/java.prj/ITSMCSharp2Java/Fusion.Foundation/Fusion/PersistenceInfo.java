package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:31
 */
public class PersistenceInfo {

	private static CaseInsensitiveComparer comparer = new CaseInsensitiveComparer();
	private static CaseInsensitiveHashCodeProvider hashProvider = new CaseInsensitiveHashCodeProvider();
	private Hashtable m_dictPersistenceInfo = new Hashtable(hashProvider, comparer);
	private String m_strMessageId = "";



	public void finalize() throws Throwable {

	}

	public PersistenceInfo(){

	}

	public String AnnotationGroup(){
		return "";
	}

	public List AttributeAnnotations(){
		return null;
	}

	/**
	 * 
	 * @param strFormat
	 */
	public String BuildLayout(String strFormat){
		return "";
	}

	/**
	 * 
	 * @param strName
	 */
	public boolean HasAttribute(String strName){
		return null;
	}

	private void Init(){

	}

	public LinkToBusOb LinkedTo(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 */
	public PersistenceAttribute LookupAttribute(String strName){
		return null;
	}

	public String MessageId(){
		return "";
	}

	public List PersistenceAttributes(){
		return null;
	}

	/**
	 * 
	 * @param strName
	 * @param bSave
	 */
	public void SetPropertySaveState(String strName, boolean bSave){

	}

}