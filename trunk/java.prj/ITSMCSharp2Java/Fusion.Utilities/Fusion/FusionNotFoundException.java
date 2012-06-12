package Fusion;

import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;
import Fusion.control.inter.ISerializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:21
 */
public class FusionNotFoundException extends FusionException implements ISerializable {

	private String m_errorMsg;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public FusionNotFoundException(){

	}

	/**
	 * 
	 * @param databaseName
	 */
	public FusionNotFoundException(String databaseName){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	protected FusionNotFoundException(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param databaseName
	 * @param inner
	 */
	public FusionNotFoundException(String databaseName, Exception inner){

	}

	/**
	 * 
	 * @param databaseName
	 * @param source
	 */
	public FusionNotFoundException(String databaseName, String source){

	}

	/**
	 * 
	 * @param databaseName
	 * @param source
	 * @param inner
	 */
	public FusionNotFoundException(String databaseName, String source, Exception inner){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	/**
	 * 
	 * @param databaseName
	 */
	private void LoadErrorMessage(String databaseName){

	}

	public String Message(){
		return "";
	}

}