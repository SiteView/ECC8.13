package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:59
 */
public class DataProviderConversion {

	private String Db2Client = "DB2CLIENT";
	private String Odbc = "ODBC";
	private String OleDb = "OLEDB";
	private String OracleClient = "ORACLECLIENT";
	private String SqlClient = "SQLCLIENT";

	public DataProviderConversion(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param eDataProvider
	 */
	public static String DataProviderToString(DataProviders eDataProvider){
		return "";
	}

	/**
	 * 
	 * @param strDataProvider
	 */
	public static DataProviders StringToDataProvider(String strDataProvider){
		return null;
	}

}