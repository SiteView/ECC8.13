package Fusion.HoursOfOperation.Controller;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 11:18:16
 */
public abstract class EditHOPSaverBase {

	protected EditHOPFormData.HOPRow mHOPData;



	public void finalize() throws Throwable {

	}

	protected EditHOPSaverBase(){

	}

	protected abstract void DoSaveEndDate();

	protected abstract void DoSaveEndMaxOccurrences();

	protected abstract void DoSaveEndNone();

	protected abstract void DoSaveEveryNthDay();

	protected abstract void DoSaveEveryWeekday();

	protected abstract void DoSaveMonthlyDay();

	protected abstract void DoSaveMonthlyDayOfWeek();

	protected abstract void DoSaveMonthlyWeekDay();

	protected abstract void DoSaveName();

	protected abstract void DoSaveRange();

	protected abstract void DoSaveStatus();

	protected abstract void DoSaveTime();

	protected abstract void DoSaveWeekly();

	protected abstract void DoSaveYearlyDay();

	protected abstract void DoSaveYearlyDayOfWeek();

	protected abstract void DoSaveYearlyWeekDay();

	/**
	 * 
	 * @param hopData
	 */
	protected void Execute(EditHOPFormData.HOPRow hopData){

	}

	private void SaveDaily(){

	}

	private void SaveMonthly(){

	}

	private void SaveRange(){

	}

	private void SaveRecurrence(){

	}

	private void SaveYearly(){

	}

}
