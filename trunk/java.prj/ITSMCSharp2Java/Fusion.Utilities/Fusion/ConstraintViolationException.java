package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:09
 */
public class ConstraintViolationException extends FusionException implements ISerializable {

	public ConstraintViolationException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected ConstraintViolationException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public ConstraintViolationException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public ConstraintViolationException(String message, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}