package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:25
 */
public class InvalidSessionException extends FusionException {

	public InvalidSessionException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param message
	 */
	public InvalidSessionException(String message){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected InvalidSessionException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param innerException
	 */
	public InvalidSessionException(String message, Exception innerException){

	}

}