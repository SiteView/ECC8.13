package Fusion;

import Fusion.control.inter.ILogicalThreadAffinative;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:18
 */
public class ErrorInfo extends MessageInfo implements ILogicalThreadAffinative {

	private Boolean m_bWarning;
	private ErrorSeverity m_severity;
	private String m_strFieldAlias;
	private String m_strFieldName;
	private String m_strObjectId;
	private String m_strObjectName;
	private String m_strReasonCode;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ErrorInfo(){

	}

	/**
	 * 
	 * @param bWarning
	 */
	public ErrorInfo(Boolean bWarning){

	}

	public MessageCategory Category(){
		return null;
	}

	public String FieldAlias(){
		return "";
	}

	public String FieldName(){
		return "";
	}

	public String ObjectId(){
		return "";
	}

	public String ObjectName(){
		return "";
	}

	public String ReasonCode(){
		return "";
	}

	public ErrorSeverity Severity(){
		return null;
	}

}