package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:48
 */
public interface IExcelWrapper {

	public String Cell();

	public CellReferenceStyles CellReferenceStyle();

	public void CloseExcel();

	public void CloseWorkbook();

	public int Column();

	/**
	 * 
	 * @param ds
	 */
	public void Export(DataSet ds);

	/**
	 * 
	 * @param dt
	 */
	public void Export(DataTable dt);

	/**
	 * 
	 * @param o
	 */
	public void Export(Object o);

	/**
	 * 
	 * @param aObs
	 * @param bHoriz
	 */
	public void Export(object[] aObs, boolean bHoriz);

	public IList GetNames();

	/**
	 * 
	 * @param strName
	 */
	public Object GetNameValue(String strName);

	public boolean HasExcelBeenOpened();

	public boolean HasWorkbookBeenOpened();

	public Object Import();

	public boolean Insert();

	public void OpenExcel();

	/**
	 * 
	 * @param strFilename
	 */
	public void OpenWorkbook(String strFilename);

	public void Print();

	public int Row();

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
	public void SaveWorkbook(String strFilename);

	/**
	 * 
	 * @param strName
	 * @param oValue
	 */
	public void SetNameValue(String strName, Object oValue);

	public int Sheet();

	public boolean Visible();

}