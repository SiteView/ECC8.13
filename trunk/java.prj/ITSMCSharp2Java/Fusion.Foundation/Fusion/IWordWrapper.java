package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:00
 */
public interface IWordWrapper {

	public void CloseDocument();

	public void CloseWord();

	/**
	 * 
	 * @param str
	 */
	public void Export(String str);

	/**
	 * 
	 * @param str
	 * @param bIsRtf
	 */
	public void Export(String str, boolean bIsRtf);

	public IList GetMailMergeFields();

	public boolean HasDocumentBeenOpened();

	public boolean HasWordBeenOpened();

	/**
	 * 
	 * @param strFilename
	 */
	public void OpenDocument(String strFilename);

	public void OpenWord();

	/**
	 * 
	 * @param dt
	 */
	public void PerformMailMerge(DataTable dt);

	public void Print();

	/**
	 * 
	 * @param strName
	 * @param aArgs
	 */
	public void RunMacro(String strName, Object[] aArgs);

	/**
	 * 
	 * @param strFilename
	 */
	public void SaveDocument(String strFilename);

	/**
	 * 
	 * @param dt
	 */
	public void SetUpMailMerge(DataTable dt);

	public boolean Visible();

}