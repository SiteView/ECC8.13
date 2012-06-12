package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:24
 */
public class OdbcLowLevelWrapper extends IDisposable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:25
	 */
	private class UnsafeNativeMethods {

		public UnsafeNativeMethods(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param nHandleType
		 * @param ptrInputHandle
		 * @param ptrOutputHandle
		 */
		public static short SQLAllocHandle(short nHandleType, IntPtr ptrInputHandle, IntPtr ptrOutputHandle){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 * @param strCatalogName
		 * @param nCatalogNameLength
		 * @param strSchemaName
		 * @param nSchemaNameLength
		 * @param strTableName
		 * @param nTableNameLength
		 * @param strColumnName
		 * @param nColumnNameLength
		 */
		public static short SQLColumns(IntPtr hStmt, String strCatalogName, short nCatalogNameLength, String strSchemaName, short nSchemaNameLength, String strTableName, short nTableNameLength, String strColumnName, short nColumnNameLength){
			return 0;
		}

		/**
		 * 
		 * @param handle
		 */
		public static short SQLDisconnect(IntPtr handle){
			return 0;
		}

		/**
		 * 
		 * @param handle
		 * @param handleWnd
		 * @param strConn
		 * @param nConnStringLength
		 * @param sbOutConn
		 * @param nOutConnStringLength
		 * @param nLengthBuffer
		 * @param nPromptInfo
		 */
		public static short SQLDriverConnect(IntPtr handle, int handleWnd, String strConn, short nConnStringLength, StringBuilder sbOutConn, short nOutConnStringLength, short nLengthBuffer, short nPromptInfo){
			return 0;
		}

		/**
		 * 
		 * @param hEnvironmentHandle
		 * @param hConnectionHandle
		 * @param hStatementHandle
		 * @param sbSqlState
		 * @param nNativeError
		 * @param sbMessageText
		 * @param nBufferLength
		 * @param nTextLength
		 */
		public static short SQLError(IntPtr hEnvironmentHandle, IntPtr hConnectionHandle, IntPtr hStatementHandle, StringBuilder sbSqlState, short nNativeError, StringBuilder sbMessageText, short nBufferLength, short nTextLength){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 */
		public static short SQLFetch(IntPtr hStmt){
			return 0;
		}

		/**
		 * 
		 * @param nHandleType
		 * @param ptrHandle
		 */
		public static short SQLFreeHandle(short nHandleType, IntPtr ptrHandle){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 * @param nColumnNumber
		 * @param nTargetType
		 * @param TargetValuePtr
		 * @param nBufferLength
		 * @param nStrLen_or_IndPtr
		 */
		public static short SQLGetData(IntPtr hStmt, short nColumnNumber, short nTargetType, StringBuilder TargetValuePtr, short nBufferLength, short nStrLen_or_IndPtr){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 * @param nColumnNumber
		 * @param nTargetType
		 * @param nTargetValue
		 * @param nBufferLength
		 * @param nStrLen_or_IndPtr
		 */
		public static short SQLGetData(IntPtr hStmt, short nColumnNumber, short nTargetType, int nTargetValue, short nBufferLength, short nStrLen_or_IndPtr){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 * @param nDataType
		 */
		public static short SQLGetTypeInfo(IntPtr hStmt, short nDataType){
			return 0;
		}

		/**
		 * 
		 * @param handle
		 * @param nAttribute
		 * @param ptrValue
		 * @param nStringLength
		 */
		public static short SQLSetEnvAttr(IntPtr handle, ushort nAttribute, IntPtr ptrValue, int nStringLength){
			return 0;
		}

		/**
		 * 
		 * @param hStmt
		 * @param strCatalogName
		 * @param nNameLength1
		 * @param strSchemaName
		 * @param nNameLength2
		 * @param strTableName
		 * @param nNameLength3
		 * @param strTableType
		 * @param nNameLength4
		 */
		public static short SQLTables(IntPtr hStmt, String strCatalogName, short nNameLength1, String strSchemaName, short nNameLength2, String strTableName, short nNameLength3, String strTableType, short nNameLength4){
			return 0;
		}

	}

	private boolean m_bConnected = false;
	private IntPtr m_PtrEnv = IntPtr.Zero;
	private IntPtr m_PtrHDBC = IntPtr.Zero;
	private int SQL_ALL_TYPES = 0;
	private int SQL_ATTR_ODBC_VERSION = 200;
	private int SQL_BIGINT = -5;
	private int SQL_BINARY = -2;
	private int SQL_BIT = -7;
	private int SQL_CHAR = 1;
	private int SQL_DATE = 0x5b;
	private int SQL_DATETIME = 9;
	private int SQL_DECIMAL = 3;
	private int SQL_DOUBLE = 8;
	private int SQL_DRIVER_COMPLETE = 1;
	private int SQL_DRIVER_COMPLETE_REQUIRED = 3;
	private int SQL_DRIVER_NOPROMPT = 0;
	private int SQL_DRIVER_PROMPT = 2;
	private int SQL_ERROR = -1;
	private int SQL_FLOAT = 6;
	private int SQL_HANDLE_DBC = 2;
	private int SQL_HANDLE_DESC = 4;
	private int SQL_HANDLE_ENV = 1;
	private int SQL_HANDLE_STMT = 3;
	private int SQL_INTEGER = 4;
	private int SQL_INVALID_HANDLE = -2;
	private int SQL_LONGVARBINARY = -4;
	private int SQL_LONGVARCHAR = -1;
	private int SQL_NTS = -3;
	private int SQL_NUMERIC = 2;
	private int SQL_REAL = 7;
	private int SQL_SMALLINT = 5;
	private int SQL_SUCCESS = 0;
	private int SQL_SUCCESS_WITH_INFO = 1;
	private int SQL_TIME = 0x5c;
	private int SQL_TIMESTAMP = 0x5d;
	private int SQL_TINYINT = -6;
	private int SQL_UNKNOWN_TYPE = 0;
	private int SQL_VARBINARY = -3;
	private int SQL_VARCHAR = 12;

	public OdbcLowLevelWrapper(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	public boolean AllocateHandles(){
		return null;
	}

	/**
	 * 
	 * @param strConn
	 */
	public boolean Connect(String strConn){
		return null;
	}

	public boolean Connected(){
		return null;
	}

	public DataTable CreateColumnsDataTable(){
		return null;
	}

	public DataTable CreateSupportedDataTypesTable(){
		return null;
	}

	public void Disconnect(){

	}

	public void Dispose(){

	}

	/**
	 * 
	 * @param bDisposing
	 */
	protected void Dispose(boolean bDisposing){

	}

	/**
	 * 
	 * @param strCatalog
	 * @param strSchema
	 * @param strTableName
	 */
	public DataTable GetColumns(String strCatalog, String strSchema, String strTableName){
		return null;
	}

	public int getSQL_ALL_TYPES(){
		return SQL_ALL_TYPES;
	}

	public int getSQL_ATTR_ODBC_VERSION(){
		return SQL_ATTR_ODBC_VERSION;
	}

	public int getSQL_BIGINT(){
		return SQL_BIGINT;
	}

	public int getSQL_BINARY(){
		return SQL_BINARY;
	}

	public int getSQL_BIT(){
		return SQL_BIT;
	}

	public int getSQL_CHAR(){
		return SQL_CHAR;
	}

	public int getSQL_DATE(){
		return SQL_DATE;
	}

	public int getSQL_DATETIME(){
		return SQL_DATETIME;
	}

	public int getSQL_DECIMAL(){
		return SQL_DECIMAL;
	}

	public int getSQL_DOUBLE(){
		return SQL_DOUBLE;
	}

	public int getSQL_DRIVER_COMPLETE(){
		return SQL_DRIVER_COMPLETE;
	}

	public int getSQL_DRIVER_COMPLETE_REQUIRED(){
		return SQL_DRIVER_COMPLETE_REQUIRED;
	}

	public int getSQL_DRIVER_NOPROMPT(){
		return SQL_DRIVER_NOPROMPT;
	}

	public int getSQL_DRIVER_PROMPT(){
		return SQL_DRIVER_PROMPT;
	}

	public int getSQL_ERROR(){
		return SQL_ERROR;
	}

	public int getSQL_FLOAT(){
		return SQL_FLOAT;
	}

	public int getSQL_HANDLE_DBC(){
		return SQL_HANDLE_DBC;
	}

	public int getSQL_HANDLE_DESC(){
		return SQL_HANDLE_DESC;
	}

	public int getSQL_HANDLE_ENV(){
		return SQL_HANDLE_ENV;
	}

	public int getSQL_HANDLE_STMT(){
		return SQL_HANDLE_STMT;
	}

	public int getSQL_INTEGER(){
		return SQL_INTEGER;
	}

	public int getSQL_INVALID_HANDLE(){
		return SQL_INVALID_HANDLE;
	}

	public int getSQL_LONGVARBINARY(){
		return SQL_LONGVARBINARY;
	}

	public int getSQL_LONGVARCHAR(){
		return SQL_LONGVARCHAR;
	}

	public int getSQL_NTS(){
		return SQL_NTS;
	}

	public int getSQL_NUMERIC(){
		return SQL_NUMERIC;
	}

	public int getSQL_REAL(){
		return SQL_REAL;
	}

	public int getSQL_SMALLINT(){
		return SQL_SMALLINT;
	}

	public int getSQL_SUCCESS(){
		return SQL_SUCCESS;
	}

	public int getSQL_SUCCESS_WITH_INFO(){
		return SQL_SUCCESS_WITH_INFO;
	}

	public int getSQL_TIME(){
		return SQL_TIME;
	}

	public int getSQL_TIMESTAMP(){
		return SQL_TIMESTAMP;
	}

	public int getSQL_TINYINT(){
		return SQL_TINYINT;
	}

	public int getSQL_UNKNOWN_TYPE(){
		return SQL_UNKNOWN_TYPE;
	}

	public int getSQL_VARBINARY(){
		return SQL_VARBINARY;
	}

	public int getSQL_VARCHAR(){
		return SQL_VARCHAR;
	}

	protected IntPtr GetStatement(){
		return null;
	}

	public DataTable GetSupportedDataTypes(){
		return null;
	}

	/**
	 * 
	 * @param strCatalog
	 * @param strSchema
	 * @param strTableName
	 */
	public ArrayList GetTables(String strCatalog, String strSchema, String strTableName){
		return null;
	}

	/**
	 * 
	 * @param strCatalog
	 * @param strSchema
	 * @param strTableName
	 * @param strTableType
	 */
	protected ArrayList GetTablesAndOrViews(String strCatalog, String strSchema, String strTableName, String strTableType){
		return null;
	}

	/**
	 * 
	 * @param strCatalog
	 * @param strSchema
	 * @param strTableName
	 */
	public ArrayList GetTablesAndViews(String strCatalog, String strSchema, String strTableName){
		return null;
	}

	/**
	 * 
	 * @param strCatalog
	 * @param strSchema
	 * @param strTableName
	 */
	public ArrayList GetViews(String strCatalog, String strSchema, String strTableName){
		return null;
	}

	public boolean HandlesAllocated(){
		return null;
	}

	private ~OdbcLowLevelWrapper(){

	}

	/**
	 * 
	 * @param nValue
	 */
	protected boolean OdbcOk(int nValue){
		return null;
	}

	public void ReleaseHandles(){

	}

	/**
	 * 
	 * @param ptrHandle
	 */
	protected void ReleaseStatement(IntPtr ptrHandle){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_ALL_TYPES(int newVal){
		SQL_ALL_TYPES = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_ATTR_ODBC_VERSION(int newVal){
		SQL_ATTR_ODBC_VERSION = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_BIGINT(int newVal){
		SQL_BIGINT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_BINARY(int newVal){
		SQL_BINARY = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_BIT(int newVal){
		SQL_BIT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_CHAR(int newVal){
		SQL_CHAR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DATE(int newVal){
		SQL_DATE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DATETIME(int newVal){
		SQL_DATETIME = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DECIMAL(int newVal){
		SQL_DECIMAL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DOUBLE(int newVal){
		SQL_DOUBLE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DRIVER_COMPLETE(int newVal){
		SQL_DRIVER_COMPLETE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DRIVER_COMPLETE_REQUIRED(int newVal){
		SQL_DRIVER_COMPLETE_REQUIRED = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DRIVER_NOPROMPT(int newVal){
		SQL_DRIVER_NOPROMPT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_DRIVER_PROMPT(int newVal){
		SQL_DRIVER_PROMPT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_ERROR(int newVal){
		SQL_ERROR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_FLOAT(int newVal){
		SQL_FLOAT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_HANDLE_DBC(int newVal){
		SQL_HANDLE_DBC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_HANDLE_DESC(int newVal){
		SQL_HANDLE_DESC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_HANDLE_ENV(int newVal){
		SQL_HANDLE_ENV = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_HANDLE_STMT(int newVal){
		SQL_HANDLE_STMT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_INTEGER(int newVal){
		SQL_INTEGER = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_INVALID_HANDLE(int newVal){
		SQL_INVALID_HANDLE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_LONGVARBINARY(int newVal){
		SQL_LONGVARBINARY = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_LONGVARCHAR(int newVal){
		SQL_LONGVARCHAR = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_NTS(int newVal){
		SQL_NTS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_NUMERIC(int newVal){
		SQL_NUMERIC = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_REAL(int newVal){
		SQL_REAL = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_SMALLINT(int newVal){
		SQL_SMALLINT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_SUCCESS(int newVal){
		SQL_SUCCESS = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_SUCCESS_WITH_INFO(int newVal){
		SQL_SUCCESS_WITH_INFO = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_TIME(int newVal){
		SQL_TIME = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_TIMESTAMP(int newVal){
		SQL_TIMESTAMP = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_TINYINT(int newVal){
		SQL_TINYINT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_UNKNOWN_TYPE(int newVal){
		SQL_UNKNOWN_TYPE = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_VARBINARY(int newVal){
		SQL_VARBINARY = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSQL_VARCHAR(int newVal){
		SQL_VARCHAR = newVal;
	}

}