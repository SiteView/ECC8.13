package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:08
 */
public class DefinitionStatus {

	private IDefinition m_def;
	private DefStatus m_defStatus;
	private DefinitionStatus m_parentStatus;



	public void finalize() throws Throwable {

	}

	public DefinitionStatus(){

	}

	/**
	 * 
	 * @param def
	 * @param defStatus
	 */
	public DefinitionStatus(IDefinition def, DefStatus defStatus){

	}

	public DefinitionStatus Clone(){
		return null;
	}

	/**
	 * 
	 * @param defStatus
	 */
	protected void CopyContents(DefinitionStatus defStatus){

	}

	public IDefinition Definition(){
		return null;
	}

	public DefinitionStatus ParentStatus(){
		return null;
	}

	public DefStatus Status(){
		return null;
	}

}