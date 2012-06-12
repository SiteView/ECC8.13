package Fusion;

import java.util.Date;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:05
 */
public class DebugProgressIndicator implements IProgressIndicator {

	private int m_current = 0;
	private boolean m_IsSucceded = true;
	private int m_maximum = 0;
	private int m_minimum = 0;
	private Date m_startTime = new Date();
	private String m_strLabel = "";

	public DebugProgressIndicator(){

	}

	public void finalize() throws Throwable {

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
		return false;
	}

	public boolean IsSuceeded(){
		return false;
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