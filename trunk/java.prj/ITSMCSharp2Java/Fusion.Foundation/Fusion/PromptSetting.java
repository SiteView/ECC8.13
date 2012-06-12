package Fusion;

import java.io.Serializable;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:34:34
 */
public class PromptSetting extends SerializableDef implements Serializable {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:34:34
	 */
	private class Tags {

		private String ClassName = "PromptSetting";
		private String Name = "Name";
		private String SearchParameter = "SearchParameter";
		private String Value = "Value";

		public Tags(){

		}

		public void finalize() throws Throwable {

		}

		public String getClassName(){
			return ClassName;
		}

		public String getName(){
			return Name;
		}

		public String getSearchParameter(){
			return SearchParameter;
		}

		public String getValue(){
			return Value;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setClassName(String newVal){
			ClassName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setName(String newVal){
			Name = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSearchParameter(String newVal){
			SearchParameter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setValue(String newVal){
			Value = newVal;
		}

	}

	private String m_strPromptName;
	private String m_strPromptValue;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public PromptSetting(){

	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public PromptSetting(SerializationInfo info, StreamingContext context){

	}

	public static String ClassName(){
		return "";
	}

	public PromptSetting Clone(){
		return null;
	}

	/**
	 * 
	 * @param def
	 * @param defOwner
	 */
	protected void CopyContents(SerializableDef def, SerializableDef defOwner){

	}

	/**
	 * 
	 * @param serial
	 */
	public void Deserialize(DefSerializer serial){

	}

	/**
	 * 
	 * @param serial
	 * @param defParent
	 */
	public static SerializableDef DeserializeCreate(DefSerializer serial, SerializableDef defParent){
		return null;
	}

	/**
	 * 
	 * @param info
	 * @param context
	 */
	public void GetObjectData(SerializationInfo info, StreamingContext context){

	}

	public String PromptName(){
		return "";
	}

	public String PromptValue(){
		return "";
	}

	/**
	 * 
	 * @param serial
	 */
	public DefSerializer Serialize(DefSerializer serial){
		return null;
	}

	public String SerializeClassName(){
		return "";
	}

	public String SerializeGeneralPropertyRoot(){
		return "";
	}

}