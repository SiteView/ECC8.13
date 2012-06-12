package Fusion;

import Fusion.control.inter.ISerializable;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:09
 */
public class ConcurrencyViolationException extends FusionException implements ISerializable {

	public ConcurrencyViolationException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected ConcurrencyViolationException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public ConcurrencyViolationException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public ConcurrencyViolationException(String message, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}