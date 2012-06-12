package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:27
 */
public class Operator {

	private String defAnd = "And";
	private String defBetween = "Between";
	private String defEmpty = "Empty";
	private String defEquals = "Equals";
	private String defGreaterThan = "GreaterThan";
	private String defGreaterThanOrEqual = "GreaterThanOrEqual";
	private String defLessThan = "LessThan";
	private String defLessThanOrEqual = "LessThanOrEqual";
	private String defLike = "Like";
	private String defMatch = "Match";
	private String defNotBetween = "NotBetween";
	private String defNotEmpty = "NotEmpty";
	private String defNotEqual = "NotEqual";
	private String defNotLike = "NotLike";
	private String defNotNull = "NotNull";
	private String defNull = "Null";
	private String defOr = "Or";
	private Operators m_oOperator;



	public void finalize() throws Throwable {

	}

	public Operator(){

	}

	/**
	 * 
	 * @param oOperator
	 */
	public Operator(Operators oOperator){

	}

	/**
	 * 
	 * @param strOperator
	 */
	public Operator(String strOperator){

	}

	public Operator Clone(){
		return null;
	}

	public String EnglishOperator(){
		return "";
	}

	public Operators EnumOperator(){
		return null;
	}

	public String getdefAnd(){
		return defAnd;
	}

	public String getdefBetween(){
		return defBetween;
	}

	public String getdefEmpty(){
		return defEmpty;
	}

	public String getdefEquals(){
		return defEquals;
	}

	public String getdefGreaterThan(){
		return defGreaterThan;
	}

	public String getdefGreaterThanOrEqual(){
		return defGreaterThanOrEqual;
	}

	public String getdefLessThan(){
		return defLessThan;
	}

	public String getdefLessThanOrEqual(){
		return defLessThanOrEqual;
	}

	public String getdefLike(){
		return defLike;
	}

	public String getdefMatch(){
		return defMatch;
	}

	public String getdefNotBetween(){
		return defNotBetween;
	}

	public String getdefNotEmpty(){
		return defNotEmpty;
	}

	public String getdefNotEqual(){
		return defNotEqual;
	}

	public String getdefNotLike(){
		return defNotLike;
	}

	public String getdefNotNull(){
		return defNotNull;
	}

	public String getdefNull(){
		return defNull;
	}

	public String getdefOr(){
		return defOr;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefAnd(String newVal){
		defAnd = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefBetween(String newVal){
		defBetween = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefEmpty(String newVal){
		defEmpty = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefEquals(String newVal){
		defEquals = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefGreaterThan(String newVal){
		defGreaterThan = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefGreaterThanOrEqual(String newVal){
		defGreaterThanOrEqual = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLessThan(String newVal){
		defLessThan = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLessThanOrEqual(String newVal){
		defLessThanOrEqual = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefLike(String newVal){
		defLike = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefMatch(String newVal){
		defMatch = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNotBetween(String newVal){
		defNotBetween = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNotEmpty(String newVal){
		defNotEmpty = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNotEqual(String newVal){
		defNotEqual = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNotLike(String newVal){
		defNotLike = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNotNull(String newVal){
		defNotNull = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefNull(String newVal){
		defNull = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setdefOr(String newVal){
		defOr = newVal;
	}

	/**
	 * 
	 * @param strOperator
	 */
	public static Operators StringToOperators(String strOperator){
		return null;
	}

	/**
	 * 
	 * @param eOperator
	 */
	public static String ToString(Operators eOperator){
		return "";
	}

}