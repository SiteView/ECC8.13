package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:04
 */
public class DbPoolingOptions {

	private String ConnectionTimeout = "Connection Lifetime";
	private int EXT_DB_FADE_DEFAULT = 180;
	private int EXT_DB_HOLD_DEFAULT = 0;
	private int EXT_DB_MAX_DEFAULT = 100;
	private int EXT_DB_MIN_DEFAULT = 0;
	private boolean EXT_DB_POOLING_DEFAULT = true;
	private int EXT_DB_TIMEOUT_DEFAULT = 600;
	private int FADE_DEFAULT = 180;
	private int HOLD_DEFAULT = 30;
	private int MAX_DEFAULT = 100;
	private String MaxPoolSize = "Max Pool Size";
	private int MIN_DEFAULT = 10;
	private String MinPoolSize = "Min Pool Size";
	private String OleDbServices = "OLE DB Services";
	private String Pooling = "Pooling";
	private boolean POOLING_DEFAULT = true;
	private String SqlServerConnReset = "Connection Reset";
	private int TIMEOUT_DEFAULT = 600;

	public DbPoolingOptions(){

	}

	public void finalize() throws Throwable {

	}

	public String getConnectionTimeout(){
		return ConnectionTimeout;
	}

	public int getEXT_DB_FADE_DEFAULT(){
		return EXT_DB_FADE_DEFAULT;
	}

	public int getEXT_DB_HOLD_DEFAULT(){
		return EXT_DB_HOLD_DEFAULT;
	}

	public int getEXT_DB_MAX_DEFAULT(){
		return EXT_DB_MAX_DEFAULT;
	}

	public int getEXT_DB_MIN_DEFAULT(){
		return EXT_DB_MIN_DEFAULT;
	}

	public boolean getEXT_DB_POOLING_DEFAULT(){
		return EXT_DB_POOLING_DEFAULT;
	}

	public int getEXT_DB_TIMEOUT_DEFAULT(){
		return EXT_DB_TIMEOUT_DEFAULT;
	}

	public int getFADE_DEFAULT(){
		return FADE_DEFAULT;
	}

	public int getHOLD_DEFAULT(){
		return HOLD_DEFAULT;
	}

	public int getMAX_DEFAULT(){
		return MAX_DEFAULT;
	}

	public String getMaxPoolSize(){
		return MaxPoolSize;
	}

	public int getMIN_DEFAULT(){
		return MIN_DEFAULT;
	}

	public String getMinPoolSize(){
		return MinPoolSize;
	}

	public String getOleDbServices(){
		return OleDbServices;
	}

	public String getPooling(){
		return Pooling;
	}

	public boolean getPOOLING_DEFAULT(){
		return POOLING_DEFAULT;
	}

	public String getSqlServerConnReset(){
		return SqlServerConnReset;
	}

	public int getTIMEOUT_DEFAULT(){
		return TIMEOUT_DEFAULT;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setConnectionTimeout(String newVal){
		ConnectionTimeout = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_FADE_DEFAULT(int newVal){
		EXT_DB_FADE_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_HOLD_DEFAULT(int newVal){
		EXT_DB_HOLD_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_MAX_DEFAULT(int newVal){
		EXT_DB_MAX_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_MIN_DEFAULT(int newVal){
		EXT_DB_MIN_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_POOLING_DEFAULT(boolean newVal){
		EXT_DB_POOLING_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEXT_DB_TIMEOUT_DEFAULT(int newVal){
		EXT_DB_TIMEOUT_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFADE_DEFAULT(int newVal){
		FADE_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setHOLD_DEFAULT(int newVal){
		HOLD_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMAX_DEFAULT(int newVal){
		MAX_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMaxPoolSize(String newVal){
		MaxPoolSize = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMIN_DEFAULT(int newVal){
		MIN_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMinPoolSize(String newVal){
		MinPoolSize = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setOleDbServices(String newVal){
		OleDbServices = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPooling(String newVal){
		Pooling = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setPOOLING_DEFAULT(boolean newVal){
		POOLING_DEFAULT = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSqlServerConnReset(String newVal){
		SqlServerConnReset = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTIMEOUT_DEFAULT(int newVal){
		TIMEOUT_DEFAULT = newVal;
	}

}