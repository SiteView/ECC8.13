package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:51
 */
public final class XmlDragHandle {

	private string BottomLeft = "BottomLeft";
	private string BottomMiddle = "BottomMiddle";
	private string BottomRight = "BottomRight";
	private string MiddleLeft = "MiddleLeft";
	private string MiddleRight = "MiddleRight";
	private string Resize = "Resize";
	private string TopLeft = "TopLeft";
	private string TopMiddle = "TopMiddle";
	private string TopRight = "TopRight";



	public void finalize() throws Throwable {

	}

	private XmlDragHandle(){

	}

	/**
	 * 
	 * @param strDragHandle
	 * @param parent
	 * @param rectOriginal
	 * @param ptOriginal
	 * @param iCurrentX
	 * @param iCurrentY
	 */
	public static Rectangle CalculateStandardRectangle(string strDragHandle, ScrollableControl parent, Rectangle rectOriginal, Point ptOriginal, int iCurrentX, int iCurrentY){
		return null;
	}

	/**
	 * 
	 * @param strDragHandle
	 */
	public static Cursor CursorFromDragHandle(string strDragHandle){
		return null;
	}

	public string getBottomLeft(){
		return BottomLeft;
	}

	public string getBottomMiddle(){
		return BottomMiddle;
	}

	public string getBottomRight(){
		return BottomRight;
	}

	public string getMiddleLeft(){
		return MiddleLeft;
	}

	public string getMiddleRight(){
		return MiddleRight;
	}

	public string getResize(){
		return Resize;
	}

	public string getTopLeft(){
		return TopLeft;
	}

	public string getTopMiddle(){
		return TopMiddle;
	}

	public string getTopRight(){
		return TopRight;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottomLeft(string newVal){
		BottomLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottomMiddle(string newVal){
		BottomMiddle = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBottomRight(string newVal){
		BottomRight = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMiddleLeft(string newVal){
		MiddleLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setMiddleRight(string newVal){
		MiddleRight = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setResize(string newVal){
		Resize = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopLeft(string newVal){
		TopLeft = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopMiddle(string newVal){
		TopMiddle = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTopRight(string newVal){
		TopRight = newVal;
	}

}