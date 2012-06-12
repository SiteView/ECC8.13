package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:43
 */
public abstract class TransferDirector extends MarshalByRefObject {

	private FileInfo m_fileInformation = null;

	public TransferDirector(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public FileInfo FileInformation(){
		return null;
	}

	/**
	 * 
	 * @param indicator
	 */
	public abstract FileInfo LoadFile(IProgressIndicator indicator);

	/**
	 * 
	 * @param indicator
	 */
	public abstract void SendFile(IProgressIndicator indicator);

}