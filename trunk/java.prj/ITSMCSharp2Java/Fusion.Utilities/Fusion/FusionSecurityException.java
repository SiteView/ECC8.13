package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:21
 */
public class FusionSecurityException extends FusionException implements ISerializable {



	public void finalize() throws Throwable {
		super.finalize();
	}

	public FusionSecurityException(){

	}

	/**
	 * 
	 * @param message
	 */
	public FusionSecurityException(String message){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected FusionSecurityException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param inner
	 */
	public FusionSecurityException(String message, Exception inner){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public FusionSecurityException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public FusionSecurityException(String message, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}