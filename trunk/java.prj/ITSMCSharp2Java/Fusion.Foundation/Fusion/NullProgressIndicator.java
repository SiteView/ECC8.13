package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:34:19
 */
public class NullProgressIndicator implements IProgressIndicator {

	private int m_Current = -1;
	private String m_ErrorMessage = "";
	private boolean m_IsSucceded = true;
	private String m_Label = "";
	private int m_Maximum = -1;
	private int m_Minimum = -1;

	public NullProgressIndicator(){

	}

	public void finalize() throws Throwable {

	}

	private int Current(){
		return 0;
	}

	public void End(){

	}

	/**
	 * 
	 * @param strMessage
	 */
	public void EndWithError(String strMessage){

	}

	public String ErrorMessage(){
		return "";
	}

	/**
	 * 
	 * @param val
	 */
	public void Increment(int val){

	}

	/**
	 * 
	 * @param minimum
	 * @param maximum
	 */
	public void Init(int minimum, int maximum){

	}

	public boolean IsCompleted(){
		return null;
	}

	public boolean IsSuceeded(){
		return null;
	}

	public String ProgressLabel(){
		return "";
	}

	/**
	 * 
	 * @param text
	 */
	public void SetPrimaryProgressLabel(String text){

	}

	/**
	 * 
	 * @param val
	 */
	public void StepTo(int val){

	}

}