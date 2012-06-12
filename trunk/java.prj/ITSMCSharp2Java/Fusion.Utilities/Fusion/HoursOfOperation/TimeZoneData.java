package Fusion.HoursOfOperation;

import Fusion.control.DateTime;
import Fusion.control.FILETIME;

/**
 * @author Administrator
 * @version 1.0
 * @created 15-四月-2010 11:18:41
 */
public class TimeZoneData {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:41
	 */
	private static class NativeMethods {

		private String KERNEL32 = "kernel32.dll";

		public NativeMethods(){

		}

		public void finalize() throws Throwable {

		}

		/**
		 * 
		 * @param lpFileTime
		 * @param lpSystemTime
		 */
		public static Boolean FileTimeToSystemTime(FILETIME lpFileTime, TimeZoneData.SYSTEMTIME lpSystemTime){
			return null;
		}

		/**
		 * 
		 * @param lpTimeZoneInformation
		 */
		public static Integer GetTimeZoneInformation(TimeZoneData.TIME_ZONE_INFORMATION lpTimeZoneInformation){
			return null;
		}

		/**
		 * 
		 * @param lpSystemTime
		 * @param lpFileTime
		 */
		public static Boolean SystemTimeToFileTime(TimeZoneData.SYSTEMTIME lpSystemTime, FILETIME lpFileTime){
			return null;
		}

		/**
		 * 
		 * @param lpTimeZone
		 * @param lpUniversalTime
		 * @param lpLocalTime
		 */
		public static Boolean SystemTimeToTzSpecificLocalTime(TimeZoneData.TIME_ZONE_INFORMATION lpTimeZone, TimeZoneData.SYSTEMTIME lpUniversalTime, TimeZoneData.SYSTEMTIME lpLocalTime){
			return null;
		}

		/**
		 * 
		 * @param lpTimeZone
		 * @param lpLocalTime
		 * @param lpUniversalTime
		 */
		public static Boolean TzSpecificLocalTimeToSystemTime(TimeZoneData.TIME_ZONE_INFORMATION lpTimeZone, TimeZoneData.SYSTEMTIME lpLocalTime, TimeZoneData.SYSTEMTIME lpUniversalTime){
			return null;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:41
	 */
	private class SYSTEMTIME {

		private short wDay;
		private short wDayOfWeek;
		private short wHour;
		private short wMilliseconds;
		private short wMinute;
		private short wMonth;
		private short wSecond;
		private short wYear;

		public SYSTEMTIME(){

		}

		public void finalize() throws Throwable {

		}

		public short getwDay(){
			return wDay;
		}

		public short getwDayOfWeek(){
			return wDayOfWeek;
		}

		public short getwHour(){
			return wHour;
		}

		public short getwMilliseconds(){
			return wMilliseconds;
		}

		public short getwMinute(){
			return wMinute;
		}

		public short getwMonth(){
			return wMonth;
		}

		public short getwSecond(){
			return wSecond;
		}

		public short getwYear(){
			return wYear;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwDay(short newVal){
			wDay = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwDayOfWeek(short newVal){
			wDayOfWeek = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwHour(short newVal){
			wHour = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwMilliseconds(short newVal){
			wMilliseconds = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwMinute(short newVal){
			wMinute = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwMonth(short newVal){
			wMonth = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwSecond(short newVal){
			wSecond = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setwYear(short newVal){
			wYear = newVal;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:41
	 */
	private class TIME_ZONE_INFORMATION {

		private int Bias;
		private int DaylightBias;
		private TimeZoneData.SYSTEMTIME DaylightDate;
		private String DaylightName;
		private int StandardBias;
		private TimeZoneData.SYSTEMTIME StandardDate;
		private String StandardName;

		public TIME_ZONE_INFORMATION(){

		}

		public void finalize() throws Throwable {

		}

		public int getBias(){
			return Bias;
		}

		public int getDaylightBias(){
			return DaylightBias;
		}

		public TimeZoneData.SYSTEMTIME getDaylightDate(){
			return DaylightDate;
		}

		public String getDaylightName(){
			return DaylightName;
		}

		public int getStandardBias(){
			return StandardBias;
		}

		public TimeZoneData.SYSTEMTIME getStandardDate(){
			return StandardDate;
		}

		public String getStandardName(){
			return StandardName;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setBias(int newVal){
			Bias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDaylightBias(int newVal){
			DaylightBias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDaylightDate(TimeZoneData.SYSTEMTIME newVal){
			DaylightDate = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setDaylightName(String newVal){
			DaylightName = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStandardBias(int newVal){
			StandardBias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStandardDate(TimeZoneData.SYSTEMTIME newVal){
			StandardDate = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setStandardName(String newVal){
			StandardName = newVal;
		}

	}

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 15-四月-2010 11:18:42
	 */
	private class TZI {

		private int bias;
		private int daylightBias;
		private TimeZoneData.SYSTEMTIME daylightDate;
		private int standardBias;
		private TimeZoneData.SYSTEMTIME standardDate;

		public TZI(){

		}

		public void finalize() throws Throwable {

		}

		public int getbias(){
			return bias;
		}

		public int getdaylightBias(){
			return daylightBias;
		}

		public TimeZoneData.SYSTEMTIME getdaylightDate(){
			return daylightDate;
		}

		public int getstandardBias(){
			return standardBias;
		}

		public TimeZoneData.SYSTEMTIME getstandardDate(){
			return standardDate;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setbias(int newVal){
			bias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setdaylightBias(int newVal){
			daylightBias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setdaylightDate(TimeZoneData.SYSTEMTIME newVal){
			daylightDate = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setstandardBias(int newVal){
			standardBias = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setstandardDate(TimeZoneData.SYSTEMTIME newVal){
			standardDate = newVal;
		}

	}

	private byte m_byteTzi[];
	private DateTime m_DaylightDate;
	private String m_daylightName;
	private String m_displayName;
	private int m_index;
	private String m_name;
	private int m_nBias;
	private int m_nDaylightBias;
	private int m_nStandardBias;
	private DateTime m_StandardDate;
	private String m_standardName;
	private TZI m_tzi;
	private String REGKEY = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\";
	private static final Object s_lockZones = new Object();
	private static TimeZoneData s_zones[] = null;
	private String TZIKEY = "TZI";

	public TimeZoneData(){

	}

	public void finalize() throws Throwable {

	}

	public int Bias(){
		return 0;
	}

	/**
	 * 
	 * @param dt
	 */
	private static SYSTEMTIME DateTimeToSystemTime(DateTime dt){
		return null;
	}

	public int DaylightBias(){
		return 0;
	}

	public String DaylightName(){
		return "";
	}

	public String DisplayName(){
		return "";
	}

	/**
	 * 
	 * @param index
	 */
	public static TimeZoneData FromIndex(int index){
		return null;
	}

	/**
	 * 
	 * @param name
	 */
	public static TimeZoneData FromName(String name){
		return null;
	}

	/**
	 * 
	 * @param utc
	 */
	public DateTime FromUniversalTime(DateTime utc){
		return null;
	}

	/**
	 * 
	 * @param index
	 * @param utc
	 */
	public static DateTime FromUniversalTime(int index, DateTime utc){
		return null;
	}

	public int getBias(){
		return m_nBias;
	}

	/**
	 * 
	 * @param data
	 * @param offset
	 */
	private static DateTime GetDateTimeFromBytes(byte[] data, int offset){
		return null;
	}

	/**
	 * 
	 * @param data
	 * @param offset
	 * @param referenceDateTime
	 */
	private static DateTime GetDateTimeFromBytes(byte[] data, int offset, DateTime referenceDateTime){
		return null;
	}

	public int getDaylightBias(){
		return m_nDaylightBias;
	}

	public DateTime getDaylightDate(){
		return m_DaylightDate;
	}

	/**
	 * 
	 * @param inLocalDateTime
	 */
	public DateTime GetHOPZoneDateTimeUsingAlgorithm(DateTime inLocalDateTime){
		return null;
	}

	/**
	 * 
	 * @param inLocalDateTime
	 */
	public DateTime GetHOPZoneDateTimeUsingWinApi(DateTime inLocalDateTime){
		return null;
	}

	public int getStandardBias(){
		return m_nStandardBias;
	}

	public DateTime getStandardDate(){
		return m_StandardDate;
	}

	public static TimeZoneData[] GetTimeZones(){
		return null;
	}

	/**
	 * 
	 * @param data
	 * @param offset
	 */
	private static int GetValueFromBytes(byte[] data, int offset){
		return 0;
	}

	public TimeZoneData GetZoneData(){
		return null;
	}

	public int Index(){
		return 0;
	}

	/**
	 * 
	 * @param info
	 */
	private void InitTzi(byte[] info){

	}

	/**
	 * 
	 * @param low
	 * @param high
	 */
	private static int MakeInt(short low, short high){
		return 0;
	}

	/**
	 * 
	 * @param low
	 * @param high
	 */
	private static Short MakeUShort(byte low, byte high){
		return null;
	}

	public String Name(){
		return "";
	}

	/**
	 * 
	 * @param tziData
	 * @param dateTime
	 */
	public void ReSetTimeZoneFields(byte[] tziData, DateTime dateTime){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setBias(int newVal){
		m_nBias = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDaylightBias(int newVal){
		m_nDaylightBias = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setDaylightDate(DateTime newVal){
		m_DaylightDate = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStandardBias(int newVal){
		m_nStandardBias = newVal;
	}

	/**
	 * 
	 * @param newVal
	 */
	public void setStandardDate(DateTime newVal){
		m_StandardDate = newVal;
	}

	/**
	 * 
	 * @param tziData
	 */
	public void SetTimeZoneFields(byte[] tziData){

	}

	/**
	 * 
	 * @param strTimeZone
	 */
	public void SetTimeZoneInfo(String strTimeZone){

	}

	public int StandardBias(){
		return 0;
	}

	public String StandardName(){
		return "";
	}

	/**
	 * 
	 * @param st
	 */
	private static DateTime SystemTimeToDateTime(SYSTEMTIME st){
		return null;
	}

	public String ToString(){
		return "";
	}

	/**
	 * 
	 * @param local
	 */
	public DateTime ToUniversalTime(DateTime local){
		return null;
	}

	/**
	 * 
	 * @param index
	 * @param local
	 */
	public static DateTime ToUniversalTime(int index, DateTime local){
		return null;
	}

	/**
	 * 
	 * @param hopDateTime
	 */
	public DateTime TranslateHOPZoneDateTimeToLocalTime(DateTime hopDateTime){
		return null;
	}

	private TIME_ZONE_INFORMATION TziNative(){
		return null;
	}

}