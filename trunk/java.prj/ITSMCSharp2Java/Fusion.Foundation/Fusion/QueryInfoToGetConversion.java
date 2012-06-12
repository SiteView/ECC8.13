package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:41
 */
public class QueryInfoToGetConversion {

	private String All = "ALL";
	private String Count = "COUNT";
	private String IdAndName = "IDNAME";
	private String Requested = "REQUESTED";

	public QueryInfoToGetConversion(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param str
	 * @param strValueToAdd
	 */
	private static void AddEnumToString(String str, String strValueToAdd){

	}

	public String getAll(){
		return All;
	}

	public String getCount(){
		return Count;
	}

	public String getIdAndName(){
		return IdAndName;
	}

	public String getRequested(){
		return Requested;
	}

	/**
	 * 
	 * @param eQueryActual
	 * @param eQueryToFind
	 */
	public static boolean HasQueryInfoToGet(QueryInfoToGet eQueryActual, QueryInfoToGet eQueryToFind){
		return null;
	}

	/**
	 * 
	 * @param eInfoToGet
	 */
	public static boolean IsQueryInfoToGetValid(QueryInfoToGet eInfoToGet){
		return null;
	}

	/**
	 * 
	 * @param eInfoToGet
	 */
	public static String QueryInfoToGetToString(QueryInfoToGet eInfoToGet){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAll(String newVal){
		All = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCount(String newVal){
		Count = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setIdAndName(String newVal){
		IdAndName = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRequested(String newVal){
		Requested = newVal;
	}

	/**
	 * 
	 * @param strInfoToGet
	 */
	public static QueryInfoToGet StringToQueryInfoToGet(String strInfoToGet){
		return null;
	}

}