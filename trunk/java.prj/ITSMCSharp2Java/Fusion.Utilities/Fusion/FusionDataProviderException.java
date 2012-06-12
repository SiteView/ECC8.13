package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:20
 */
public class FusionDataProviderException extends FusionException implements ISerializable {

	public FusionDataProviderException(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected FusionDataProviderException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 */
	public FusionDataProviderException(String message, String source){

	}

	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	public FusionDataProviderException(String message, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

}