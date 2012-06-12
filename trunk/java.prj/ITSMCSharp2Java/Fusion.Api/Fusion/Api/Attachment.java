package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:26
 */
public class Attachment {

	private IAttachmentWorker m_worker = null;

	public Attachment(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param worker
	 */
	public Attachment(IAttachmentWorker worker){

	}

	public FileInfo File(){
		return null;
	}

	public boolean IsComplete(){
		return false;
	}

	public void WaitForAttachment(){

	}

	public Thread WorkerThread(){
		return null;
	}

}
