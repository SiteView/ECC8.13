package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:48
 */
public class ReportLibrary extends MarshalByRefObject {

	private Fusion.CrystalSettingsManager m_CrystalSettingsManager = null;
	private IFileStore m_store = null;

	public ReportLibrary(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param store
	 * @param crystalSettingsManager
	 */
	public ReportLibrary(IFileStore store, Fusion.CrystalSettingsManager crystalSettingsManager){

	}

	/**
	 * 
	 * @param strReportPath
	 * @param strReportName
	 * @param strDestinationDirectory
	 * @param indicator
	 */
	public StoreWorker CopyReport(String strReportPath, String strReportName, String strDestinationDirectory, IProgressIndicator indicator){
		return null;
	}

	public Fusion.CrystalSettingsManager CrystalSettingsManager(){
		return null;
	}

	/**
	 * 
	 * @param strReportPath
	 * @param strReportName
	 */
	public void Delete(String strReportPath, String strReportName){

	}

	public IFileStore FileStorage(){
		return null;
	}

	/**
	 * 
	 * @param strReportPath
	 * @param strReportName
	 * @param strDestinationDirectory
	 * @param indicator
	 */
	public StoreWorker LoadReport(String strReportPath, String strReportName, String strDestinationDirectory, IProgressIndicator indicator){
		return null;
	}

	/**
	 * 
	 * @param strReportPath
	 * @param strReportName
	 * @param file
	 * @param indicator
	 */
	public void SaveReport(String strReportPath, String strReportName, FileInfo file, IProgressIndicator indicator){

	}

	/**
	 * 
	 * @param strPath
	 */
	private void SetFileStorePath(String strPath){

	}

}