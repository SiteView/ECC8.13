package Fusion;

import Fusion.control.XmlTextReader;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:19
 */
public class FadFileUtils {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:19
	 */
	private class Tags {

		private String Culture = "Culture";
		private String DbName = "DbName";
		private String Description = "Description";
		private String DoubleByte = "DoubleByte";
		private String Fad = "FAD";
		private String SystemTables = "SystemTables";
		private String Version = "Version";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getCulture(){
			return Culture;
		}

		public String getDbName(){
			return DbName;
		}

		public String getDescription(){
			return Description;
		}

		public String getDoubleByte(){
			return DoubleByte;
		}

		public String getFad(){
			return Fad;
		}

		public String getSystemTables(){
			return SystemTables;
		}

		public String getVersion(){
			return Version;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setCulture(String newVal){
			Culture = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDbName(String newVal){
			DbName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDescription(String newVal){
			Description = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDoubleByte(String newVal){
			DoubleByte = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setFad(String newVal){
			Fad = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSystemTables(String newVal){
			SystemTables = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVersion(String newVal){
			Version = newVal;
		}

	}

	public FadFileUtils(){

	}

	public void finalize() throws Throwable {

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
	public static void GetNameDescVersionFromFadFile(String strFadFile, String strName, String strVersion, String strDesc, Boolean bUseUnicode, String strCulture){

	}

	/**
	 * 
	 * @param reader
	 * @param strName
	 * @param strVersion
	 * @param strDesc
	 * @param bUseUnicode
	 * @param strCulture
	 */
	public static void GetNameDescVersionFromFadFile(XmlTextReader reader, String strName, String strVersion, String strDesc, Boolean bUseUnicode, String strCulture){

	}

}