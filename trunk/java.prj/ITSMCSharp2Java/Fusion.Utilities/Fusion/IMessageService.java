package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-����-2010 11:18:25
 */
public interface IMessageService {

	/**
	 * 
	 * @param mif
	 */
	public String GetMessage(MessageInfo mif);

	/**
	 * 
	 * @param strResourceId
	 */
	public String GetResourceString(String strResourceId);

}