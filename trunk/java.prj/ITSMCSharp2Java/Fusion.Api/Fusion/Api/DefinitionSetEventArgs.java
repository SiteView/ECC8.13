package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:01
 */
public class DefinitionSetEventArgs extends EventArgs {

	private IDefinition m_Definition = null;

	public DefinitionSetEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param objectDefintion
	 */
	public DefinitionSetEventArgs(IDefinition objectDefintion){

	}

	public IDefinition HeldDefinition(){
		return null;
	}

}