package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-四月-2010 14:33:08
 */
public class DefQuery {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 20-四月-2010 14:33:08
	 */
	public enum QueryType {
		Definition,
		PlaceHolderList,
		DefinitionList,
		UniqueCheck
	}

	private boolean m_bIgnoreCache = false;
	private boolean m_bIgnoreLinkedTo = false;
	private boolean m_bStepUpChain = true;
	private QueryType m_queryType = QueryType.Definition;
	private Fusion.Xml.Scope m_scope = Fusion.Xml.Scope.Global;
	private String m_strDefType = "";
	private String m_strId = "";
	private String m_strLinkedTo = "(Unlinked)";
	private String m_strName = "";
	private String m_strPerspective = "(Base)";
	private String m_strScopeOwner = "GLOBAL";
	private String m_strSpecialInstruction = "";

	public DefQuery(){

	}

	public void finalize() throws Throwable {

	}

	public String DefType(){
		return "";
	}

	public String Id(){
		return "";
	}

	public boolean IgnoreCache(){
		return null;
	}

	public boolean IgnoreLinkedTo(){
		return null;
	}

	public String LinkedTo(){
		return "";
	}

	public String Name(){
		return "";
	}

	public String Perspective(){
		return "";
	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public String ScopeOwner(){
		return "";
	}

	public String SpecializedInstruction(){
		return "";
	}

	public boolean StepUpChain(){
		return null;
	}

	public QueryType TypeOfQuery(){
		return null;
	}

}