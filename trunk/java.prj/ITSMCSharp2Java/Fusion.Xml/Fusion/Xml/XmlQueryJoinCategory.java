package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:54
 */
public class XmlQueryJoinCategory {

	private string LeftOuterJoin = "LeftOuterJoin";
	private string Natural = "Natural";
	private string None = "None";
	private string RightOuterJoin = "RightOuterJoin";

	public XmlQueryJoinCategory(){

	}

	public void finalize() throws Throwable {

	}

	public string getLeftOuterJoin(){
		return LeftOuterJoin;
	}

	public string getNatural(){
		return Natural;
	}

	public string getNone(){
		return None;
	}

	public string getRightOuterJoin(){
		return RightOuterJoin;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLeftOuterJoin(string newVal){
		LeftOuterJoin = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNatural(string newVal){
		Natural = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNone(string newVal){
		None = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRightOuterJoin(string newVal){
		RightOuterJoin = newVal;
	}

	/**
	 * 
	 * @param strQueryJoinCategory
	 */
	public static QueryJoinCategory ToCategory(string strQueryJoinCategory){
		return null;
	}

	/**
	 * 
	 * @param queryJoinCategory
	 */
	public static string ToString(QueryJoinCategory queryJoinCategory){
		return "";
	}

}