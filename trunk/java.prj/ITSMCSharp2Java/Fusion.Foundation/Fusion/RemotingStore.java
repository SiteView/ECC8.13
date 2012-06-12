package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:45
 */
public class RemotingStore implements IFileStore {

	private IFileStore m_remoteStore = null;

	public RemotingStore(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param remoteStore
	 */
	public RemotingStore(IFileStore remoteStore){

	}

	/**
	 * 
	 * @param strPathname
	 */
	public void Delete(String strPathname){

	}

	/**
	 * 
	 * @param strPathname
	 */
	public boolean Exists(String strPathname){
		return null;
	}

	public SoapTransferAgent GetSoapTransferAgent(){
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

}