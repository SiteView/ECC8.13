package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:59
 */
public class DatabaseEngineConversion {

	private String Db2 = "DB2";
	private String External = "EXTERNAL";
	private String Oracle = "ORACLE";
	private String SqlServer = "SQLSERVER";

	public DatabaseEngineConversion(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param dbEngine
	 */
	public static String DatabaseEngineToString(DatabaseEngine dbEngine){
		return "";
	}

	public String getDb2(){
		return Db2;
	}

	public String getExternal(){
		return External;
	}

	public String getOracle(){
		return Oracle;
	}

	public String getSqlServer(){
		return SqlServer;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2(String newVal){
		Db2 = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setExternal(String newVal){
		External = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOracle(String newVal){
		Oracle = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSqlServer(String newVal){
		SqlServer = newVal;
	}

	/**
	 * 
	 * @param strDbEngine
	 */
	public static DatabaseEngine StringToDatabaseEngine(String strDbEngine){
		return null;
	}

}