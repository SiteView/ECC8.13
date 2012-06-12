package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:50
 */
public interface IEditTag {

	/**
	 * 
	 * @param sender
	 * @param e
	 */
	public void Closing(Object sender, CancelEventArgs e);

	public Fusion.TagItem TagItem();

}