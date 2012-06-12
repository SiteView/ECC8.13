package Fusion.Xml;

/**
 * @author Administrator
 * @version 1.0
 * @created 22-ËÄÔÂ-2010 11:37:29
 */
public class ElementItems {

	private string Action = "Action";
	private string Condition = "Condition";
	private string End = "End";
	private string GoTo = "GoTo";
	private string Insert = "Insert";
	private string Repeat = "Repeat";
	private string Switch = "Switch";
	private string Trigger = "Trigger";
	private string WaitEvent = "WaitEvent";

	public ElementItems(){

	}

	public void finalize() throws Throwable {

	}

	/**
	 * 
	 * @param strConst
	 */
	public static string ConvertConstantToDisplayText(string strConst){
		return "";
	}

	public string getAction(){
		return Action;
	}

	public string getCondition(){
		return Condition;
	}

	public string getEnd(){
		return End;
	}

	public string getGoTo(){
		return GoTo;
	}

	public string getInsert(){
		return Insert;
	}

	public string getRepeat(){
		return Repeat;
	}

	public string getSwitch(){
		return Switch;
	}

	public string getTrigger(){
		return Trigger;
	}

	public string getWaitEvent(){
		return WaitEvent;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setAction(string newVal){
		Action = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setCondition(string newVal){
		Condition = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setEnd(string newVal){
		End = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setGoTo(string newVal){
		GoTo = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setInsert(string newVal){
		Insert = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setRepeat(string newVal){
		Repeat = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setSwitch(string newVal){
		Switch = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setTrigger(string newVal){
		Trigger = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setWaitEvent(string newVal){
		WaitEvent = newVal;
	}

}