package Fusion;

import Fusion.control.Regex;
import Fusion.control.RegexOptions;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:17
 */
public class EmailAddressValidator {

	private Boolean bIsValid;
	private String CloseBr = "\\]";
	private String CloseParen = "\\)";
	private String CRList = "\n\015";
	private String Ctrl = "\000-\037";
	private String Escape = "\\";
	private String NonAscii = "\\x80-\\xff";
	private String OpenBr = "\\[";
	private String OpenParen = "\\(";
	private static final Regex oRegex = new Regex(InitRegex(), RegexOptions.IgnorePatternWhitespace | RegexOptions.Compiled);
	private String Period = "\\.";
	private String sDomain;
	private String sLocalPart;
	private String Space = "\040";
	private String Tab = "\t";



	public void finalize() throws Throwable {

	}

	public EmailAddressValidator(){

	}

	/**
	 * 
	 * @param emailAddy
	 */
	public EmailAddressValidator(String emailAddy){

	}

	public String Domain(){
		return "";
	}

	private static String InitRegex(){
		return "";
	}

	public Boolean IsValid(){
		return null;
	}

	public String LocalPart(){
		return "";
	}

	/**
	 * 
	 * @param email
	 */
	public Boolean Parse(String email){
		return null;
	}

}