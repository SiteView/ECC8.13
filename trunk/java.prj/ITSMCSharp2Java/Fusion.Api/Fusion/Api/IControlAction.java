package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:44:49
 */
public interface IControlAction {

	public String Action();

	public String ActionCategory();

	public Hashtable ActionParameters();

	/**
	 * 
	 * @param strParameterName
	 * @param rule
	 */
	public void AddParameter(String strParameterName, RuleDef rule);

	public String AlternateText();

	public RuleDef AlternateTextRule();

	/**
	 * 
	 * @param strParameterName
	 */
	public RuleDef GetParameter(String strParameterName);

	public String GuardBehavior();

	public String GuardMessageText();

	public RuleDef GuardRule();

	public int MinimumParameters();

	public boolean OpenInNewWindow();

	public int ParameterCount();

	public void RemoveAllParameters();

	/**
	 * 
	 * @param strParameterName
	 */
	public void RemoveParameter(String strParameterName);

	/**
	 * 
	 * @param strParameterName
	 * @param rule
	 */
	public void SetParameter(String strParameterName, RuleDef rule);

}