package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:48
 */
public interface IFileStore {

	/**
	 * 
	 * @param strPathName
	 */
	public void Delete(String strPathName);

	/**
	 * 
	 * @param strPathName
	 */
	public boolean Exists(String strPathName);

	public SoapTransferAgent GetSoapTransferAgent();

	/**
	 * 
	 * @param strRelativePathName
	 * @param indicator
	 */
	public FileInfo Load(String strRelativePathName, IProgressIndicator indicator);

	public String RootPath();

	/**
	 * 
	 * @param strPath
	 * @param file
	 * @param indicator
	 */
	public void Save(String strPath, FileInfo file, IProgressIndicator indicator);

	/**
	 * 
	 * @param strPath
	 * @param file
	 * @param agent
	 */
	public void Save(String strPath, FileInfo file, SoapTransferAgent agent);

}