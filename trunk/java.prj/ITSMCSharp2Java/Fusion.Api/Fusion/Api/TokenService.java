package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:58
 */
public class TokenService implements ITokenService {

	private IOrchestrator m_orch = null;

	public TokenService(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public TokenService(IOrchestrator orch){

	}

	public List GetTokenPlaceHolderList(){
		return null;
	}

	/**
	 * 
	 * @param strTokenName
	 */
	public String GetTokenValue(String strTokenName){
		return "";
	}

	/**
	 * 
	 * @param strId
	 */
	public String GetTokenValueById(String strId){
		return "";
	}

	/**
	 * 
	 * @param strTokenName
	 */
	public boolean TokenExists(String strTokenName){
		return null;
	}

}