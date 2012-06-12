package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:43:49
 */
public class CounterDef extends DefinitionObject {

	public CounterDef(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public CounterDef(Object fusionObject){

	}

	public int AmountToIncrement(){
		return 0;
	}

	public CounterCategory CategoryOfCounter(){
		return null;
	}

	public String CategoryOfCounterAsString(){
		return "";
	}

	public static String ClassName(){
		return "";
	}

	public String CommitValue(){
		return "";
	}

	public String CustomValues(){
		return "";
	}

	public String InitialValue(){
		return "";
	}

	public boolean IsResetFrequencyBasedOnResetValue(){
		return null;
	}

	public boolean IsResetFrequencyBasedOnTime(){
		return null;
	}

	public String ResetDay(){
		return "";
	}

	public CounterResetFrequency ResetFrequency(){
		return null;
	}

	public String ResetFrequencyAsString(){
		return "";
	}

	public int ResetIncrement(){
		return 0;
	}

	public String ResetValue(){
		return "";
	}

	public Date StartResetsFrom(){
		return null;
	}

	public boolean UseCommitValue(){
		return null;
	}

	private Fusion.BusinessLogic.CounterDef WhoAmI(){
		return null;
	}

}