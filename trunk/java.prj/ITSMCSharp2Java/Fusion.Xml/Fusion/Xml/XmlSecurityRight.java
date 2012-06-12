package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:56
 */
public class XmlSecurityRight {

	private string Access = "Access";
	private char Add = 'A';
	private string Bool = "Bool";
	private char Delete = 'D';
	private char Edit = 'E';
	private char EditInFinalState = 'Y';
	private char False = 'F';
	private char SwitchBackToRecallState = 'Z';
	private char True = 'T';
	private char View = 'V';

	public XmlSecurityRight(){

	}

	public void finalize() throws Throwable {

	}

	public string getAccess(){
		return Access;
	}

	public char getAdd(){
		return Add;
	}

	public string getBool(){
		return Bool;
	}

	public char getDelete(){
		return Delete;
	}

	public char getEdit(){
		return Edit;
	}

	public char getEditInFinalState(){
		return EditInFinalState;
	}

	public char getFalse(){
		return False;
	}

	public char getSwitchBackToRecallState(){
		return SwitchBackToRecallState;
	}

	public char getTrue(){
		return True;
	}

	public char getView(){
		return View;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAccess(string newVal){
		Access = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAdd(char newVal){
		Add = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBool(string newVal){
		Bool = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDelete(char newVal){
		Delete = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEdit(char newVal){
		Edit = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEditInFinalState(char newVal){
		EditInFinalState = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFalse(char newVal){
		False = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSwitchBackToRecallState(char newVal){
		SwitchBackToRecallState = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrue(char newVal){
		True = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setView(char newVal){
		View = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static ModuleItemRightCategory ToModuleItemRightCategory(string strXmlCategory){
		return null;
	}

	/**
	 * 
	 * @param strXmlRights
	 */
	public static SecurityRight ToRight(string strXmlRights){
		return null;
	}

	/**
	 * 
	 * @param mirc
	 */
	public static string ToStringModuleItemRightCategory(ModuleItemRightCategory mirc){
		return "";
	}

	/**
	 * 
	 * @param rightFlags
	 */
	public static string ToStringRight(SecurityRight rightFlags){
		return "";
	}

}