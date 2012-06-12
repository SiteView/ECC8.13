package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:48
 */
public interface IFileManager {

	/**
	 * 
	 * @param strFileDetails
	 */
	public FileStream Load(String strFileDetails);

	/**
	 * 
	 * @param strFileDetails
	 * @param fsFileData
	 */
	public void Save(String strFileDetails, FileStream fsFileData);

}