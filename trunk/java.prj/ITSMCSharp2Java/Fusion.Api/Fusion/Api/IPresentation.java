package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:53
 */
public interface IPresentation {

	/**
	 * 
	 * @param Name
	 */
	public GridDef CreateGridDefForBusOb(String Name);

	/**
	 * 
	 * @param Name
	 */
	public GridDef GetGridDef(String Name);

	/**
	 * 
	 * @param Id
	 */
	public GridDef GetGridDefById(String Id);

	/**
	 * 
	 * @param Name
	 */
	public LayoutDef GetLayoutDef(String Name);

	/**
	 * 
	 * @param Id
	 */
	public LayoutDef GetLayoutDefById(String Id);

	/**
	 * 
	 * @param Name
	 */
	public PanelDef GetPanelDef(String Name);

	/**
	 * 
	 * @param Id
	 */
	public PanelDef GetPanelDefById(String Id);

}