package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:54
 */
public class XmlLineCap {

	private string AnchorMask = "ANCHORMASK";
	private string ArrowAnchor = "ARROWANCHOR";
	private string Custom = "CUSTOM";
	private string DiamondAnchor = "DIAMONDANCHOR";
	private string Flat = "FLAT";
	private string NoAnchor = "NOANCHOR";
	private string Round = "ROUND";
	private string RoundAnchor = "ROUNDANCHOR";
	private string Square = "SQUARE";
	private string SquareAnchor = "SQUAREANCHOR";
	private string Triangle = "TRIANGLE";

	public XmlLineCap(){

	}

	public void finalize() throws Throwable {

	}

	public string getAnchorMask(){
		return AnchorMask;
	}

	public string getArrowAnchor(){
		return ArrowAnchor;
	}

	public string getCustom(){
		return Custom;
	}

	public string getDiamondAnchor(){
		return DiamondAnchor;
	}

	public string getFlat(){
		return Flat;
	}

	public string getNoAnchor(){
		return NoAnchor;
	}

	public string getRound(){
		return Round;
	}

	public string getRoundAnchor(){
		return RoundAnchor;
	}

	public string getSquare(){
		return Square;
	}

	public string getSquareAnchor(){
		return SquareAnchor;
	}

	public string getTriangle(){
		return Triangle;
	}

	/**
	 * 
	 * @param cap
	 */
	public static string LineCapToXmlLineCap(LineCap cap){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAnchorMask(string newVal){
		AnchorMask = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setArrowAnchor(string newVal){
		ArrowAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCustom(string newVal){
		Custom = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDiamondAnchor(string newVal){
		DiamondAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setFlat(string newVal){
		Flat = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setNoAnchor(string newVal){
		NoAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRound(string newVal){
		Round = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRoundAnchor(string newVal){
		RoundAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSquare(string newVal){
		Square = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSquareAnchor(string newVal){
		SquareAnchor = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTriangle(string newVal){
		Triangle = newVal;
	}

	/**
	 * 
	 * @param strXmlLineCap
	 */
	public static LineCap XmlLineCapToLineCap(string strXmlLineCap){
		return null;
	}

}