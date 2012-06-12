package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:07
 */
public class LocalStore extends MarshalByRefObject implements IFileStore {

	private DirectoryInfo m_rootDirectory;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public LocalStore(){

	}

	/**
	 * 
	 * @param strPath
	 */
	public LocalStore(String strPath){

	}

	/**
	 * 
	 * @param strPathName
	 */
	public void Delete(String strPathName){

	}

	/**
	 * 
	 * @param strPathName
	 */
	public boolean Exists(String strPathName){
		return null;
	}

	/**
	 * 
	 * @param strPath
	 */
	private DirectoryInfo GetDirectory(String strPath){
		return null;
	}

	public SoapTransferAgent GetSoapTransferAgent(){
		return null;
	}

	public Object InitializeLifetimeService(){
		return null;
	}

	/**
	 * 
	 * @param strRelativePathName
	 * @param indicator
	 */
	public FileInfo Load(String strRelativePathName, IProgressIndicator indicator){
		return null;
	}

	protected DirectoryInfo RootDirectory(){
		return null;
	}

	public String RootPath(){
		return "";
	}

	/**
	 * 
	 * @param strPath
	 * @param file
	 * @param indicator
	 */
	public void Save(String strPath, FileInfo file, IProgressIndicator indicator){

	}

	/**
	 * 
	 * @param strPath
	 * @param file
	 * @param agent
	 */
	public void Save(String strPath, FileInfo file, SoapTransferAgent agent){

	}

	/**
	 * 
	 * @param strRootPath
	 */
	protected void SetRootDirectory(String strRootPath){

	}

}