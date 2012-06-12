package Fusion.Api.FusionUpgrade;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:58
 */
public class DefinitionResolveConflictArgs extends EventArgs {

	private boolean m_bSkipDef;
	private Fusion.Api.FusionUpgrade.ConflictType m_conflictType;
	private IDefinition m_def1;
	private IDefinition m_def2;
	private String m_strDefName1;
	private String m_strDefName2;
	private String m_strDefType;
	private String m_strNewDefinitionName;
	private String m_strNewFieldName;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DefinitionResolveConflictArgs(){

	}

	/**
	 * 
	 * @param def
	 * @param defDB
	 * @param ct
	 */
	public DefinitionResolveConflictArgs(IDefinition def, IDefinition defDB, Fusion.Api.FusionUpgrade.ConflictType ct){

	}

	/**
	 * 
	 * @param strDefType
	 * @param strDefName1
	 * @param strDefName2
	 * @param ct
	 */
	public DefinitionResolveConflictArgs(String strDefType, String strDefName1, String strDefName2, Fusion.Api.FusionUpgrade.ConflictType ct){

	}

	public Fusion.Api.FusionUpgrade.ConflictType ConflictType(){
		return null;
	}

	public IDefinition Def1(){
		return null;
	}

	public IDefinition Def2(){
		return null;
	}

	public String DefinitionName1(){
		return "";
	}

	public String DefinitionName2(){
		return "";
	}

	public String DefinitionType(){
		return "";
	}

	public String NewDefinitionName(){
		return "";
	}

	public String NewFieldName(){
		return "";
	}

	public boolean SkipDefinition(){
		return false;
	}

}