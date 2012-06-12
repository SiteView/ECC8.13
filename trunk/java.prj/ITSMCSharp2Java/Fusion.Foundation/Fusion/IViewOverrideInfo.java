package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:59
 */
public interface IViewOverrideInfo {

	public IViewOverrideInfo Clone();

	public String DefId();

	public String DefName();

	public String DefType();

	public String LinkDefId();

	public String LinkDefName();

	public String Perspective();

	public Fusion.Xml.ViewBehavior ViewBehavior();

}