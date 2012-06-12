package Fusion;

/**
 * @author Administrator
 * @version 1.0
 * @created 20-ËÄÔÂ-2010 14:33:01
 */
public class DateTimeFormat {

	private CultureInfo m_CultureInfo = CultureInfo.CurrentCulture;
	private Fusion.Xml.DateFormat m_DateFormat = Fusion.Xml.DateFormat.SystemShortDate;
	private Fusion.DateTimeCategory m_DateTimeCategory = Fusion.DateTimeCategory.Date;
	private String m_strCustomDateFormat = "";
	private String m_strCustomFormat = "";
	private String m_strCustomTimeFormat = "";
	private Fusion.Xml.TimeFormat m_TimeFormat = Fusion.Xml.TimeFormat.SystemShortTime;

	public DateTimeFormat(){

	}

	public void finalize() throws Throwable {

	}

	public String CustomDateFormat(){
		return "";
	}

	public String CustomFormat(){
		return "";
	}

	public String CustomTimeFormat(){
		return "";
	}

	public Fusion.Xml.DateFormat DateFormat(){
		return null;
	}

	public Fusion.DateTimeCategory DateTimeCategory(){
		return null;
	}

	/**
	 * 
	 * @param dt
	 */
	public String Format(DateTime dt){
		return "";
	}

	public CultureInfo Language(){
		return null;
	}

	private void SetCustomFormat(){

	}

	public Fusion.Xml.TimeFormat TimeFormat(){
		return null;
	}

}