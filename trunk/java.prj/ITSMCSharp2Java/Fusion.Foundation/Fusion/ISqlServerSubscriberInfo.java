package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:57
 */
public interface ISqlServerSubscriberInfo {

	public DateTime SubscriberActiveEndDateTime();

	public DateTime SubscriberActiveStartDateTime();

	public String SubscriberDescription();

	public int SubscriberFrequencyInterval();

	public int SubscriberFrequencyRecurrenceFactor();

	public int SubscriberFrequencyRelativeInterval();

	public int SubscriberFrequencySubday();

	public int SubscriberFrequencySubdayInterval();

	public int SubscriberFrequencyType();

	public String SubscriberLoginForPublisher();

	public String SubscriberPasswordForPublisher();

	public int SubscriberSecurityMode();

	public String SubscriberServerName();

}