package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:58
 */
public interface ISystemLiaison {

	public SoapTransferAgent GetSoapTransferAgent();

	/**
	 * 
	 * @param agent
	 */
	public SoapTransferAgent LoadAttachment(SoapTransferAgent agent);

	/**
	 * 
	 * @param agent
	 */
	public void SaveAttachment(SoapTransferAgent agent);

}