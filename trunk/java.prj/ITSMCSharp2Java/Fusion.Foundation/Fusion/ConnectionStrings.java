package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:32:54
 */
public class ConnectionStrings {

	private String Db2ClientProvider = "";
	private String Db2OleDbProvider = "IBMDADB2";
	private String OracleClientProvider = "";
	private String OracleOleDbFromMicrosoft = "MSDAORA";
	private String OracleOleDbFromOracle = "OraOLEDB.Oracle";
	private String Provider = "Provider";
	private String SqlClientProvider = "";
	private String SqlOleDbProvider = "SQLOLEDB";

	public ConnectionStrings(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strConn
	 * @param strParm
	 * @param strValue
	 */
	public void AddToConnectionString(String strConn, String strParm, String strValue){

	}

	/**
	 * 
	 * @param idictParms
	 */
	public static String BuildConnectionString(IDictionary idictParms){
		return "";
	}

	/**
	 * 
	 * @param strProvider
	 * @param strDatabase
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 */
	public String BuildDb2ConnString(String strProvider, String strDatabase, DbLoginMethod methodLogin, String strUserId, String strPassword){
		return "";
	}

	/**
	 * 
	 * @param dbEngine
	 * @param strDataSource
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 */
	public String BuildOdbcConnString(DatabaseEngine dbEngine, String strDataSource, DbLoginMethod methodLogin, String strUserId, String strPassword){
		return "";
	}

	/**
	 * 
	 * @param strProvider
	 * @param strServer
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 */
	public String BuildOracleConnString(String strProvider, String strServer, DbLoginMethod methodLogin, String strUserId, String strPassword){
		return "";
	}

	/**
	 * 
	 * @param strProvider
	 * @param strServer
	 * @param strDatabase
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 */
	public String BuildSqlServerConnString(String strProvider, String strServer, String strDatabase, DbLoginMethod methodLogin, String strUserId, String strPassword){
		return "";
	}

	/**
	 * 
	 * @param dbEngine
	 * @param strConn
	 * @param strParmsFound
	 */
	public static boolean ContainsPoolingParameters(DatabaseEngine dbEngine, String strConn, String strParmsFound){
		return null;
	}

	/**
	 * 
	 * @param strConn
	 */
	public String DecryptPasswordInConnectionString(String strConn){
		return "";
	}

	/**
	 * 
	 * @param strConn
	 */
	public String EncryptPasswordInConnectionString(String strConn){
		return "";
	}

	public String getDb2ClientProvider(){
		return Db2ClientProvider;
	}

	public String getDb2OleDbProvider(){
		return Db2OleDbProvider;
	}

	public String getOracleClientProvider(){
		return OracleClientProvider;
	}

	public String getOracleOleDbFromMicrosoft(){
		return OracleOleDbFromMicrosoft;
	}

	public String getOracleOleDbFromOracle(){
		return OracleOleDbFromOracle;
	}

	/**
	 * 
	 * @param strConn
	 * @param strPasswordKey
	 * @param strPassword
	 * @param idictParms
	 */
	private void GetPasswordKeyAndValue(String strConn, String strPasswordKey, String strPassword, Map idictParms){

	}

	public String getSqlClientProvider(){
		return SqlClientProvider;
	}

	public String getSqlOleDbProvider(){
		return SqlOleDbProvider;
	}

	/**
	 * 
	 * @param strConn
	 */
	public String HidePasswordInConnectionString(String strConn){
		return "";
	}

	/**
	 * 
	 * @param strConn
	 */
	public static boolean IsFormatCorrect(String strConn){
		return null;
	}

	/**
	 * 
	 * @param strTag
	 */
	private static boolean IsPassword(String strTag){
		return null;
	}

	/**
	 * 
	 * @param strConn
	 * @param idictParms
	 */
	public static String ParseConnectionString(String strConn, Map idictParms){
		return "";
	}

	/**
	 * 
	 * @param strConn
	 * @param strProvider
	 * @param strDatabase
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAddParms
	 */
	public void ParseDb2ConnString(String strConn, String strProvider, String strDatabase, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAddParms){

	}

	/**
	 * 
	 * @param strConn
	 * @param strProvider
	 * @param strDataSource
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAddParms
	 */
	public void ParseOdbcConnString(String strConn, String strProvider, String strDataSource, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAddParms){

	}

	/**
	 * 
	 * @param strConn
	 * @param strProvider
	 * @param strServer
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAddParms
	 */
	public void ParseOracleConnString(String strConn, String strProvider, String strServer, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAddParms){

	}

	/**
	 * 
	 * @param strConn
	 * @param strProvider
	 * @param strServer
	 * @param strDatabase
	 * @param methodLogin
	 * @param strUserId
	 * @param strPassword
	 * @param strAddParms
	 */
	public void ParseSqlServerConnString(String strConn, String strProvider, String strServer, String strDatabase, DbLoginMethod methodLogin, String strUserId, String strPassword, String strAddParms){

	}

	/**
	 * 
	 * @param strConn
	 * @param strProviderName
	 * @param strDataSource
	 * @param strPassword
	 */
	public void ParseUnknownDatabaseOleDbConnString(String strConn, String strProviderName, String strDataSource, String strPassword){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2ClientProvider(String newVal){
		Db2ClientProvider = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDb2OleDbProvider(String newVal){
		Db2OleDbProvider = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOracleClientProvider(String newVal){
		OracleClientProvider = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOracleOleDbFromMicrosoft(String newVal){
		OracleOleDbFromMicrosoft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOracleOleDbFromOracle(String newVal){
		OracleOleDbFromOracle = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSqlClientProvider(String newVal){
		SqlClientProvider = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSqlOleDbProvider(String newVal){
		SqlOleDbProvider = newVal;
	}

	/**
	 * 
	 * @param strConn
	 * @param strStrippedConn
	 * @param strPasswordKey
	 * @param strPassword
	 */
	public void StripOutPassword(String strConn, String strStrippedConn, String strPasswordKey, String strPassword){

	}

}