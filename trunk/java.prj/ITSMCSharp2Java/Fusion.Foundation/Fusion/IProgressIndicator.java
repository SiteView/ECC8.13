package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:53
 */
public interface IProgressIndicator {

	public void End();

	/**
	 * 
	 * @param strMessage
	 */
	public void EndWithError(String strMessage);

	/**
	 * 
	 * @param val
	 */
	public void Increment(int val);

	/**
	 * 
	 * @param minimum
	 * @param maximum
	 */
	public void Init(int minimum, int maximum);

	/**
	 * 
	 * @param text
	 */
	public void SetPrimaryProgressLabel(String text);

	/**
	 * 
	 * @param val
	 */
	public void StepTo(int val);

}