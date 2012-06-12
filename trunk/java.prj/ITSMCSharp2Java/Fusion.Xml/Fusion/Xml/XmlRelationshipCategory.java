package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:55
 */
public class XmlRelationshipCategory {

	private string Associated = "ASSOCIATED";
	private string AssociatedEmbedded = "ASSOCIATEDEMBEDDED";
	private string Contained = "CONTAINED";
	private string Contains = "CONTAINS";
	private string ContainsEmbedded = "CONTAINSEMBEDDED";

	public XmlRelationshipCategory(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param catRelationship
	 */
	public static string CategoryToXmlCategory(RelationshipCategory catRelationship){
		return "";
	}

	public string getAssociated(){
		return Associated;
	}

	public string getAssociatedEmbedded(){
		return AssociatedEmbedded;
	}

	public string getContained(){
		return Contained;
	}

	public string getContains(){
		return Contains;
	}

	public string getContainsEmbedded(){
		return ContainsEmbedded;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAssociated(string newVal){
		Associated = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAssociatedEmbedded(string newVal){
		AssociatedEmbedded = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setContained(string newVal){
		Contained = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setContains(string newVal){
		Contains = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setContainsEmbedded(string newVal){
		ContainsEmbedded = newVal;
	}

	/**
	 * 
	 * @param strXmlCategory
	 */
	public static RelationshipCategory XmlCategoryToCategory(string strXmlCategory){
		return null;
	}

}