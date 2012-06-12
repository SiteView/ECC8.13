package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:34
 */
public class ProxyAuthenticationException extends FusionException implements ISerializable {

	private String m_strServer;

	public ProxyAuthenticationException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public ProxyAuthenticationException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param server
	 * @param inner
	 */
	public ProxyAuthenticationException(String message, String source, String server, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	public String Server(){
		return "";
	}

}