package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:22
 */
public class StoreWorker {

	protected DirectoryInfo m_destinationPath = null;
	protected FileInfo m_file = null;
	protected IProgressIndicator m_indicator = null;
	protected IFileStore m_store = null;
	protected String m_strFileName = "";
	protected String m_strPath = "";
	protected Thread m_workerThread = null;

	public StoreWorker(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param store
	 * @param file
	 * @param strFileName
	 * @param strPath
	 * @param indicator
	 */
	public StoreWorker(IFileStore store, FileInfo file, String strFileName, String strPath, IProgressIndicator indicator){

	}

	public void Copy(){

	}

	public FileInfo File(){
		return null;
	}

	public void Load(){

	}

	public IProgressIndicator ProgressIndicator(){
		return null;
	}

	public void Save(){

	}

	public void StartCopying(){

	}

	public void StartLoading(){

	}

	public void StartSaving(){

	}

	public Thread WorkerThread(){
		return null;
	}

}