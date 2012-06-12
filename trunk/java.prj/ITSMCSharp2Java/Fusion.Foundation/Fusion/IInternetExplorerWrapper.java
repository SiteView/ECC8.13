package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:49
 */
public interface IInternetExplorerWrapper {

	public void CloseIE();

	public IList GetForms();

	public boolean HasIEBeenOpened();

	/**
	 * 
	 * @param strUrl
	 */
	public void Navigate(String strUrl);

	public void OpenIE();

	/**
	 * 
	 * @param defForm
	 */
	public void SetForm(HtmlFormDef defForm);

	/**
	 * 
	 * @param defForm
	 */
	public void SubmitForm(HtmlFormDef defForm);

	public boolean Visible();

}