package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:32
 */
public class SearchRequestEventArgs {

	private IFusionApi m_Api = null;
	private boolean m_bAllowSearchForMultipleBOs = false;
	private DefinitionLibrary m_HeldDefinitionLibrary = null;
	private Fusion.QueryGroupDef m_QueryGroupDef = null;
	private String m_strBusObName = "";
	private String m_strSearchPanelName = "";
	private String m_strSearchResultFormName = "";
	private String m_strSearchResultGridName = "";
	private String m_strSearchResultLayoutName = "";

	public SearchRequestEventArgs(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param api
	 * @param defLib
	 * @param strBusobName
	 * @param def
	 * @param strSearchPanelName
	 * @param strSearchResultLayoutName
	 * @param strSearchResultFormName
	 * @param strSearchResultGridName
	 * @param bAllowSearchForMultipleBOs
	 */
	public SearchRequestEventArgs(IFusionApi api, DefinitionLibrary defLib, String strBusobName, Fusion.QueryGroupDef def, String strSearchPanelName, String strSearchResultLayoutName, String strSearchResultFormName, String strSearchResultGridName, boolean bAllowSearchForMultipleBOs){

	}

	public boolean AllowSearchForMultipleBOs(){
		return null;
	}

	public String BusObName(){
		return "";
	}

	public IFusionApi HeldApi(){
		return null;
	}

	public DefinitionLibrary HeldDefinitionLibrary(){
		return null;
	}

	public Fusion.QueryGroupDef QueryGroupDef(){
		return null;
	}

	public String SearchPanelName(){
		return "";
	}

	public String SearchResultFormName(){
		return "";
	}

	public String SearchResultGridName(){
		return "";
	}

	public String SearchResultLayoutName(){
		return "";
	}

}