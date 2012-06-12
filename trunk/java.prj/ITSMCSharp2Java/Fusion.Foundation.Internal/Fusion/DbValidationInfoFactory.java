package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:21
 */
public class DbValidationInfoFactory {

	public DbValidationInfoFactory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param dbEngine
	 */
	public static DbValidationInfo Create(DatabaseEngine dbEngine){
		return null;
	}

	/**
	 * 
	 * @param strDbEngine
	 */
	public static DbValidationInfo Create(String strDbEngine){
		return null;
	}

	/**
	 * 
	 * @param dbEngine
	 * @param svcDataStore
	 * @param strDataStoreName
	 */
	public static DbValidationInfo Create(DatabaseEngine dbEngine, IDataStoreService svcDataStore, String strDataStoreName){
		return null;
	}

	/**
	 * 
	 * @param strDbEngine
	 * @param svcDataStore
	 * @param strDataStoreName
	 */
	public static DbValidationInfo Create(String strDbEngine, IDataStoreService svcDataStore, String strDataStoreName){
		return null;
	}

	public static DbValidationInfo CreateForAllEngines(){
		return null;
	}

}