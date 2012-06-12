package Fusion;

import java.util.Hashtable;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:09
 */
public class ConcurrencyResolutionException extends ConcurrencyViolationException {

	private Hashtable m_auditHistory;
	private Hashtable m_changeList;
	private String m_xmlBO;

	public ConcurrencyResolutionException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected ConcurrencyResolutionException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public ConcurrencyResolutionException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public ConcurrencyResolutionException(String message, String source, Exception inner){

	}

	public Hashtable AuditHistory(){
		return null;
	}

	public Hashtable ChangeList(){
		return null;
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	public String XmlBO(){
		return "";
	}

}