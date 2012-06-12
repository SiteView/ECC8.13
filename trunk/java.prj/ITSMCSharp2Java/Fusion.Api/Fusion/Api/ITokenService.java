package Fusion.Api;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:54
 */
public interface ITokenService {

	public List GetTokenPlaceHolderList();

	/**
	 * 
	 * @param strTokenName
	 */
	public String GetTokenValue(String strTokenName);

	/**
	 * 
	 * @param strId
	 */
	public String GetTokenValueById(String strId);

	/**
	 * 
	 * @param strTokenName
	 */
	public boolean TokenExists(String strTokenName);

}