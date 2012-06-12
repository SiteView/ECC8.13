package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:59
 */
public interface IUIInteraction {

	/**
	 * 
	 * @param busOb
	 * @param bNewWindow
	 */
	public void DisplayBusinessObject(Object busOb, boolean bNewWindow);

	/**
	 * 
	 * @param type
	 * @param detail
	 * @param busObId
	 * @param busObName
	 * @param changeDisplayOption
	 */
	public void ExecuteFormNavigationAction(String type, String detail, String busObId, String busObName, String changeDisplayOption);

	public void Refresh();

	/**
	 * 
	 * @param form
	 */
	public boolean ShowDialog(Form form);

	public Control ShowDialogOwnerControl();

}