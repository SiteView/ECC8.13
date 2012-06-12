package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:34
 */
public class SettingChangedEventArgs extends EventArgs {

	private Object m_oNewValue;
	private Fusion.Xml.Scope m_scope;
	private String m_strScopeOwner;
	private String m_strSettingId;

	public SettingChangedEventArgs(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param strSettingId
	 * @param oNewValue
	 */
	public SettingChangedEventArgs(String strSettingId, Object oNewValue){

	}

	/**
	 * 
	 * @param strSettingId
	 * @param scope
	 * @param strScopeOwner
	 * @param oNewValue
	 */
	public SettingChangedEventArgs(String strSettingId, Fusion.Xml.Scope scope, String strScopeOwner, Object oNewValue){

	}

	public Object NewValue(){
		return null;
	}

	public Fusion.Xml.Scope Scope(){
		return null;
	}

	public String ScopeOwner(){
		return "";
	}

	public String SettingId(){
		return "";
	}

}