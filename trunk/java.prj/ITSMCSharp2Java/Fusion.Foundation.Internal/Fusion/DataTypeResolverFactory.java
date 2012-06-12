package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 21-ËÄÔÂ-2010 10:50:18
 */
public class DataTypeResolverFactory {

	public DataTypeResolverFactory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param dbEngine
	 */
	public static IDataTypeResolver Create(DatabaseEngine dbEngine){
		return null;
	}

	/**
	 * 
	 * @param strDbEngine
	 */
	public static IDataTypeResolver Create(String strDbEngine){
		return null;
	}

	/**
	 * 
	 * @param dbEngine
	 * @param svcDataStore
	 * @param strDataStoreName
	 */
	public static IDataTypeResolver Create(DatabaseEngine dbEngine, IDataStoreService svcDataStore, String strDataStoreName){
		return null;
	}

	/**
	 * 
	 * @param strDbEngine
	 * @param svcDataStore
	 * @param strDataStoreName
	 */
	public static IDataTypeResolver Create(String strDbEngine, IDataStoreService svcDataStore, String strDataStoreName){
		return null;
	}

}