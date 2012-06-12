package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:10
 */
public class Presentation implements IPresentation {

	private IOrchestrator m_orch = null;

	public Presentation(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param orch
	 */
	public Presentation(IOrchestrator orch){

	}

	/**
	 * 
	 * @param Name
	 */
	public Fusion.Api.GridDef CreateGridDefForBusOb(String Name){
		return null;
	}

	/**
	 * 
	 * @param Name
	 */
	public Fusion.Api.GridDef GetGridDef(String Name){
		return null;
	}

	/**
	 * 
	 * @param Id
	 */
	public Fusion.Api.GridDef GetGridDefById(String Id){
		return null;
	}

	/**
	 * 
	 * @param Name
	 */
	public Fusion.Api.LayoutDef GetLayoutDef(String Name){
		return null;
	}

	/**
	 * 
	 * @param Id
	 */
	public Fusion.Api.LayoutDef GetLayoutDefById(String Id){
		return null;
	}

	/**
	 * 
	 * @param Name
	 */
	public Fusion.Api.PanelDef GetPanelDef(String Name){
		return null;
	}

	/**
	 * 
	 * @param Id
	 */
	public Fusion.Api.PanelDef GetPanelDefById(String Id){
		return null;
	}

	/**
	 * 
	 * @param fldDef
	 */
	protected int GetWidthForField(Fusion.BusinessLogic.FieldDef fldDef){
		return 0;
	}

}