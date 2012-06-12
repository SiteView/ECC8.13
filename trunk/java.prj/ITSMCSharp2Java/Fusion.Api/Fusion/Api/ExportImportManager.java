package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:18
 */
public class ExportImportManager extends FusionAggregate {



	public void finalize() throws Throwable {
		super.finalize();
	}

	public ExportImportManager(){

	}

	/**
	 * 
	 * @param fusionObject
	 */
	public ExportImportManager(Object fusionObject){

	}

	/**
	 * 
	 * @param strFadFile
	 */
	public void ExportSystem(String strFadFile){

	}

	/**
	 * 
	 * @param strFadFile
	 * @param strName
	 * @param strVersion
	 * @param strDesc
	 * @param bUseUnicode
	 * @param strCulture
	 */
	public void GetNameDescVersionFromFadFile(String strFadFile, String strName, String strVersion, String strDesc, boolean bUseUnicode, String strCulture){

	}

	/**
	 * 
	 * @param strFadFile
	 * @param bOverwrite
	 * @param bCreateTables
	 * @param errList
	 */
	public void ImportData(String strFadFile, boolean bOverwrite, boolean bCreateTables, MessageInfoList errList){

	}

	private Fusion.BusinessLogic.ExportImportManager WhoAmI(){
		return null;
	}

}