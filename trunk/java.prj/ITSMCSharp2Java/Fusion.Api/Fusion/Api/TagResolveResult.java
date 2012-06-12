package Fusion.Api;

import java.util.ArrayList;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 14:45:55
 */
public class TagResolveResult {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 14:45:55
	 */
	public enum Status {
		Success,
		Failure,
		PartialFailure
	}

	private ArrayList m_alErrors;
	private ArrayList m_alResolved;
	private Fusion.Api.BusinessObject m_BusOb;
	private Status m_statusCode = Status.Success;
	private String m_strResolved = "";

	public TagResolveResult(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strError
	 */
	public void AddError(String strError){

	}

	/**
	 * 
	 * @param strResolved
	 */
	public void AddResolvedString(String strResolved){

	}

	public Fusion.Api.BusinessObject BusinessObject(){
		return null;
	}

	public int ErrorCount(){
		return 0;
	}

	public List Errors(){
		return null;
	}

	public String ResolvedString(){
		return "";
	}

	public List ResolvedStringCollection(){
		return null;
	}

	public Status StatusCode(){
		return null;
	}

}