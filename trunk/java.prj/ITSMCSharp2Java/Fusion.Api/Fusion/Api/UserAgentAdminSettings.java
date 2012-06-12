package Fusion.Api;

import java.util.Hashtable;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-ËÄÔÂ-2010 14:46:00
 */
public class UserAgentAdminSettings {

	private Hashtable m_htEmailBusObs;
	private String m_strAppointmentBusOb;
	private String m_strCurrentCalendar;
	private String m_strCurrentEmail;
	private String m_strEmailBusOb;
	private String m_strMeetingBusOb;
	private String SETTING_APPOINTMENT_BUSOB = "AppointmentBusinessObject";
	private String SETTING_CURRENT_CALENDAR = "CurrentCalendar";
	private String SETTING_CURRENT_EMAIL = "CurrentEmail";
	private String SETTING_EMAIL_BUS_OBS = "EmailBusObs";
	private String SETTING_GROUP = "Fusion.UserAgentAdmin";
	private String SETTING_GROUP_CURRENT_AGENTS = "Fusion.UserAgentAdmin.CurrentAgents";
	private String SETTING_KEY_VERSION = "Version";
	private String SETTING_MAIL_BUSOB = "EmailBusinessObject";
	private String SETTING_MEETING_BUSOB = "MeetingBusinessObject";
	private int USER_AGENT_ADMIN_SETTINGS_VERSION = 1;



	public void finalize() throws Throwable {

	}

	public UserAgentAdminSettings(){

	}

	/**
	 * 
	 * @param fusionSettingsService
	 */
	public UserAgentAdminSettings(ISettings fusionSettingsService){

	}

	public String AppointmentBusinessObject(){
		return "";
	}

	public String CurrentCalendar(){
		return "";
	}

	public String CurrentEmail(){
		return "";
	}

	public String EmailBusinessObject(){
		return "";
	}

	public Map EmailBusObs(){
		return null;
	}

	public String MeetingRequestBusinessObject(){
		return "";
	}

	/**
	 * 
	 * @param fusionSettingsService
	 */
	public void SaveToFusion(ISettings fusionSettingsService){

	}

}