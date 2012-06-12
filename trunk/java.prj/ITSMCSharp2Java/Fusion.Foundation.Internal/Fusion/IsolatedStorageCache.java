package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:25
 */
public class IsolatedStorageCache extends IDisposable {

	private String LogMessageFormat = "{0}\r\n[\r\n{1}\r\n]";
	private boolean m_bIsDisposed;
	private IsolatedStorageFile m_isoFile;
	private System.IO.IsolatedStorage.IsolatedStorageScope m_scope;
	private String m_strDirectory;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public IsolatedStorageCache(){

	}

	/**
	 * 
	 * @param scope
	 */
	public IsolatedStorageCache(System.IO.IsolatedStorage.IsolatedStorageScope scope){

	}

	/**
	 * 
	 * @param strFileName
	 */
	private String AddDirectoryIfNeeded(String strFileName){
		return "";
	}

	/**
	 * 
	 * @param strFileName
	 */
	public void DeleteFile(String strFileName){

	}

	public String DirectoryName(){
		return "";
	}

	public void Dispose(){

	}

	/**
	 * 
	 * @param isDisposing
	 */
	protected void Dispose(boolean isDisposing){

	}

	/**
	 * 
	 * @param strFileName
	 * @param mode
	 */
	public IsolatedStorageFileStream GetFile(String strFileName, FileMode mode){
		return null;
	}

	public long GetRemainingStorageSpace(){
		return 0;
	}

	private IsolatedStorageFile GetStore(){
		return null;
	}

	private ~IsolatedStorageCache(){

	}

	protected System.IO.IsolatedStorage.IsolatedStorageScope IsolatedStorageScope(){
		return null;
	}

}