package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:40
 */
public class FusionEditorAttribute extends Attribute {

	private String m_strLabelResourceName;
	private String m_strNotificationCategory;
	private String m_strType;
	private TargetMedium m_TargetMedium;
	private Type m_type;

	public FusionEditorAttribute(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strType
	 * @param strLabelResourceName
	 * @param strNotificationCategory
	 */
	public FusionEditorAttribute(String strType, String strLabelResourceName, String strNotificationCategory){

	}

	/**
	 * 
	 * @param type
	 * @param strLabelResourceName
	 * @param strNotificationCategory
	 */
	public FusionEditorAttribute(Type type, String strLabelResourceName, String strNotificationCategory){

	}

	/**
	 * 
	 * @param strType
	 * @param strLabelResourceName
	 * @param strNotificationCategory
	 * @param tMedium
	 */
	public FusionEditorAttribute(String strType, String strLabelResourceName, String strNotificationCategory, TargetMedium tMedium){

	}

	/**
	 * 
	 * @param type
	 * @param strLabelResourceName
	 * @param strNotificationCategory
	 * @param tMedium
	 */
	public FusionEditorAttribute(Type type, String strLabelResourceName, String strNotificationCategory, TargetMedium tMedium){

	}

	public Type EditorType(){
		return null;
	}

	public String EditorTypeAsString(){
		return "";
	}

	public String LabelResourceName(){
		return "";
	}

	public String NotificationCategory(){
		return "";
	}

	public TargetMedium SupportedMediums(){
		return null;
	}

}