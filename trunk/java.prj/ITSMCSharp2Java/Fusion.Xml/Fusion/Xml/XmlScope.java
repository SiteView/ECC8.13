package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:56
 */
public class XmlScope {

	private string Dependent = "DEPENDENT";
	private string Global = "GLOBAL";
	private string Internal = "INTERNAL";
	private string Role = "ROLE";
	private string SecurityGroup = "SECURITYGROUP";
	private string Team = "TEAM";
	private string Unknown = "UNKNOWN";
	private string User = "USER";

	public XmlScope(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param scopeCategory
	 */
	public static string CategoryToXmlCategory(Scope scopeCategory){
		return "";
	}

	public string getDependent(){
		return Dependent;
	}

	public string getGlobal(){
		return Global;
	}

	public string getInternal(){
		return Internal;
	}

	public string getRole(){
		return Role;
	}

	public string getSecurityGroup(){
		return SecurityGroup;
	}

	public string getTeam(){
		return Team;
	}

	public string getUnknown(){
		return Unknown;
	}

	public string getUser(){
		return User;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDependent(string newVal){
		Dependent = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGlobal(string newVal){
		Global = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInternal(string newVal){
		Internal = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRole(string newVal){
		Role = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSecurityGroup(string newVal){
		SecurityGroup = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTeam(string newVal){
		Team = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUnknown(string newVal){
		Unknown = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setUser(string newVal){
		User = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static Scope XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}