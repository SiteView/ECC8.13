package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:39
 */
public class FusionDisplayAttribute extends Attribute {

	private String Alpha = "Alpha";
	private String m_Priority;
	private DesignPropertyLayout.TabPages m_TabPage;

	public FusionDisplayAttribute(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param tabPage
	 */
	public FusionDisplayAttribute(DesignPropertyLayout.TabPages tabPage){

	}

	/**
	 * 
	 * @param tabPage
	 * @param Priority
	 */
	public FusionDisplayAttribute(DesignPropertyLayout.TabPages tabPage, String Priority){

	}

	public String getAlpha(){
		return Alpha;
	}

	public String Priority(){
		return "";
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAlpha(String newVal){
		Alpha = newVal;
	}

	public DesignPropertyLayout.TabPages TabPage(){
		return null;
	}

}