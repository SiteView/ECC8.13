package Fusion;

import org.omg.CORBA.portable.ApplicationException;

import Fusion.control.inter.ISerializable;
import Fusion.control.SerializationInfo;
import Fusion.control.StreamingContext;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:20
 */
public class FusionException extends ApplicationException implements ISerializable {

	private Fusion.MessageInfoList m_aFusionMessages;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public FusionException(){
		super("",null);
	}

	/**
	 * 
	 * @param message
	 */
	public FusionException(String message){
		super(message,null);
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	/*protected FusionException(SerializationInfo info, StreamingContext context){

	}*/

	/**
	 * 
	 * @param message
	 * @param inner
	 */
	/*public FusionException(String message, Exception inner){

	}*/

	/**
	 * 
	 * @param message
	 * @param source
	 */
	/*public FusionException(String message, String source){

	}
*/
	/**
	 * 
	 * @param message
	 * @param source
	 * @param inner
	 */
	/*public FusionException(String message, String source, Exception inner){

	}*/

	/**
	 * 
	 * @param info
	 */
	public void AddMessage(MessageInfo info){

	}

	/**
	 * 
	 * @param ex
	 * @param mList
	 */
	public void GetAllMessageInfoLists(Exception ex, Fusion.MessageInfoList mList){

	}

	/**
	 * 
	 * @param ex
	 * @param mList
	 */
	public void GetAllMessages(Exception ex, Fusion.MessageInfoList mList){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	private void Init(){

	}

	public Fusion.MessageInfoList MessageInfoList(){
		return null;
	}

}