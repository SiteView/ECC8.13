package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:20
 */
public class SoapTransferDirector extends TransferDirector {

	private SoapTransferAgent m_agent = null;
	private byte m_nBuffer[] = null;
	private final int m_nBuffSize = 0x8000;

	public SoapTransferDirector(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param agent
	 */
	public SoapTransferDirector(SoapTransferAgent agent){

	}

	/**
	 * 
	 * @param indicator
	 */
	public FileInfo LoadFile(IProgressIndicator indicator){
		return null;
	}

	/**
	 * 
	 * @param indicator
	 */
	public void SendFile(IProgressIndicator indicator){

	}

}