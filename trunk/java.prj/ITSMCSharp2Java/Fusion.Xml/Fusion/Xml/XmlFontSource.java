package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:52
 */
public class XmlFontSource {

	private string Default = "DEFAULT";
	private string Specified = "SPECIFIED";
	private string SystemDefined = "SYSTEMDEFINED";
	private string User = "USER";

	public XmlFontSource(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param source
	 */
	public static string FontSourceToXmlFontSource(FontSource source){
		return "";
	}

	public string getDefault(){
		return Default;
	}

	public string getSpecified(){
		return Specified;
	}

	public string getSystemDefined(){
		return SystemDefined;
	}

	public string getUser(){
		return User;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDefault(string newVal){
		Default = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSpecified(string newVal){
		Specified = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSystemDefined(string newVal){
		SystemDefined = newVal;
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
	 * @param strXmlFontSource
	 */
	public static FontSource XmlFontSourceToFontSource(string strXmlFontSource){
		return null;
	}

}