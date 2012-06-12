package Fusion.Categories;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:37
 */
public class Region {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:37
	 */
	public enum Category {
		Region,
		Layout,
		Splitter,
		TabGroup,
		Presentation,
		MultiPartPresentation,
		Object
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:37
	 */
	public class Names {

		private string Layout = "LAYOUT";
		private string MultiPartPresentation = "MULTIPARTPRESENTATION";
		private string Object = "OBJECT";
		private string Presentation = "PRESENTATION";
		private string Region = "REGION";
		private string Splitter = "SPLITTER";
		private string TabGroup = "TABGROUP";

		public Names(){

		}

		public void finalize() throws Throwable {

		}

		public string getLayout(){
			return Layout;
		}

		public string getMultiPartPresentation(){
			return MultiPartPresentation;
		}

		public string getObject(){
			return Object;
		}

		public string getPresentation(){
			return Presentation;
		}

		public string getRegion(){
			return Region;
		}

		public string getSplitter(){
			return Splitter;
		}

		public string getTabGroup(){
			return TabGroup;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLayout(string newVal){
			Layout = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setMultiPartPresentation(string newVal){
			MultiPartPresentation = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setObject(string newVal){
			Object = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setPresentation(string newVal){
			Presentation = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRegion(string newVal){
			Region = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setSplitter(string newVal){
			Splitter = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTabGroup(string newVal){
			TabGroup = newVal;
		}

	}



	public void finalize() throws Throwable {

	}

	private Region(){

	}

	/**
	 * 
	 * @param strCategory
	 */
	public static Category FromString(string strCategory){
		return null;
	}

	/**
	 * 
	 * @param cat
	 */
	public static string ToString(Category cat){
		return "";
	}

}