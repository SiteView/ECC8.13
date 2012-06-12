package Fusion.Categories;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-四月-2010 11:37:41
 */
public class TabPosition {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:41
	 */
	public enum Category {
		Top,
		Bottom,
		Left,
		Right
	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 22-四月-2010 11:37:41
	 */
	public class Names {

		private string Bottom = "BOTTOM";
		private string Left = "LEFT";
		private string Right = "RIGHT";
		private string Top = "TOP";

		public Names(){

		}

		public void finalize() throws Throwable {

		}

		public string getBottom(){
			return Bottom;
		}

		public string getLeft(){
			return Left;
		}

		public string getRight(){
			return Right;
		}

		public string getTop(){
			return Top;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBottom(string newVal){
			Bottom = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setLeft(string newVal){
			Left = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setRight(string newVal){
			Right = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setTop(string newVal){
			Top = newVal;
		}

	}



	public void finalize() throws Throwable {

	}

	private TabPosition(){

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