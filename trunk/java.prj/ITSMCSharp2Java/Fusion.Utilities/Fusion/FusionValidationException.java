package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-����-2010 11:18:22
 */
public class FusionValidationException extends FusionException implements ISerializable {

	public FusionValidationException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected FusionValidationException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public FusionValidationException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public FusionValidationException(String message, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}