package Fusion.Api;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:45:39
 */
public class SqlServerSubscriberInfo extends FusionAggregate implements ISqlServerSubscriberInfo {

	public SqlServerSubscriberInfo(){

	}

	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param fusionObject
	 */
	public SqlServerSubscriberInfo(Object fusionObject){

	}

	public Date SubscriberActiveEndDateTime(){
		return null;
	}

	public Date SubscriberActiveStartDateTime(){
		return null;
	}

	public String SubscriberDescription(){
		return "";
	}

	public int SubscriberFrequencyInterval(){
		return 0;
	}

	public int SubscriberFrequencyRecurrenceFactor(){
		return 0;
	}

	public int SubscriberFrequencyRelativeInterval(){
		return 0;
	}

	public int SubscriberFrequencySubday(){
		return 0;
	}

	public int SubscriberFrequencySubdayInterval(){
		return 0;
	}

	public int SubscriberFrequencyType(){
		return 0;
	}

	public String SubscriberLoginForPublisher(){
		return "";
	}

	public String SubscriberPasswordForPublisher(){
		return "";
	}

	public int SubscriberSecurityMode(){
		return 0;
	}

	public String SubscriberServerName(){
		return "";
	}

	private Fusion.BusinessLogic.SqlServerSubscriberInfo WhoAmI(){
		return null;
	}

}