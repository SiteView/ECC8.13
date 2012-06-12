package Fusion.Categories;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:36
 */
public class Orientation {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:36
	 */
	public enum Category {
		Horizontal,
		Vertical
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:36
	 */
	public class Names {

		private string Horizontal = "HORIZONTAL";
		private string Vertical = "VERTICAL";

		public Names(){

		}

		public void finalize() throws Throwable {

		}

		public string getHorizontal(){
			return Horizontal;
		}

		public string getVertical(){
			return Vertical;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setHorizontal(string newVal){
			Horizontal = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setVertical(string newVal){
			Vertical = newVal;
		}

	}



	public void finalize() throws Throwable {

	}

	private Orientation(){

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