package Fusion.Api.FusionUpgrade;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:01
 */
public class DefinitionSetMessageArgs extends EventArgs {

	private MessageInfoList m_MessageInfoList;



	public void finalize() throws Throwable {
		super.finalize();
	}

	public DefinitionSetMessageArgs(){

	}

	/**
	 * 
	 * @param messList
	 */
	public DefinitionSetMessageArgs(MessageInfoList messList){

	}

	public MessageInfoList MessageList(){
		return null;
	}

}