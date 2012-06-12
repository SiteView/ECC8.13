package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:35:23
 */
public class StringTagFormatter implements ITagFormatter {

	private String LengthArgument = "Length";
	private String ReplaceArgument = "Replace";
	private String ReplaceWithArgument = "ReplaceWith";
	private String StartIndexArgument = "StartIndex";

	public StringTagFormatter(){

	}

	public void finalize() throws Throwable {

	}

	public boolean ApplyLast(){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue Capitalize(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue CapitalizeWords(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	public FusionValue Format(FusionValue val, TagFormat format){
		return null;
	}

	public String getLengthArgument(){
		return LengthArgument;
	}

	public String getReplaceArgument(){
		return ReplaceArgument;
	}

	public String getReplaceWithArgument(){
		return ReplaceWithArgument;
	}

	public String getStartIndexArgument(){
		return StartIndexArgument;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue Replace(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setLengthArgument(String newVal){
		LengthArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setReplaceArgument(String newVal){
		ReplaceArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setReplaceWithArgument(String newVal){
		ReplaceWithArgument = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStartIndexArgument(String newVal){
		StartIndexArgument = newVal;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue Substring(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue ToLower(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue ToUpper(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue TrimWhitespace(FusionValue val, TagFormat format){
		return null;
	}

	/**
	 * 
	 * @param val
	 * @param format
	 */
	private FusionValue UrlEncode(FusionValue val, TagFormat format){
		return null;
	}

}