/*
 * 
 * Created on 2005-2-28 6:57:39
 *
 * FrequencyProperty.java
 *
 * History:
 *
 */
package com.dragonflow.Properties;

/**
 * Comment for <code>FrequencyProperty</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */
import java.io.PrintWriter;
import java.util.Map;

import jgl.HashMap;

import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Page.CGI;
import com.dragonflow.SiteView.SiteViewObject;

//Referenced classes of package com.dragonflow.Properties:
//         NumericProperty

public class FrequencyProperty extends NumericProperty {

	static final int daySeconds = 0x15180;
	static final int hourSeconds = 3600;
	static final int minuteSeconds = 60;

	public FrequencyProperty(String s, String s1) {
		super(s, s1);
	}

	public static int toSeconds(int i, String s) {
		if (s.equals("days")) {
			return i * daySeconds;
		}
		if (s.equals("hours")) {
			return i * hourSeconds;
		}
		if (s.equals("minutes")) {
			return i * minuteSeconds;
		} else {
			return i;
		}
	}

	public void printProperty(CGI cgi, PrintWriter printwriter,
			SiteViewObject siteviewobject, HTTPRequest httprequest,
			HashMap hashmap, boolean flag) {
		Object obj = hashmap.get(this);
		String s = "";
		if (obj != null) {
			s = (String) obj;
		}
		int i = siteviewobject.getPropertyAsInteger(this);
		String s1 = "";
		String s2 = "";
		String s3 = "";
		String s4 = "";
		if (i == 0) {
			s3 = "SELECTED";
		} else if (i % daySeconds == 0) {
			i /= daySeconds;
			s1 = "SELECTED";
		} else if (i % hourSeconds == 0) {
			i /= hourSeconds;
			s2 = "SELECTED";
		} else if (i % minuteSeconds == 0) {
			i /= minuteSeconds;
			s3 = "SELECTED";
		} else {
			s4 = "SELECTED";
		}
		String s5 = "";
		if (i != 0) {
			s5 = "" + i;
		}
		printwriter
				.println("<TR><TD ALIGN=\"RIGHT\" VALIGN=\"TOP\">"
						+ getLabel()
						+ "</TD>"
						+ "<TD><TABLE><TR><TD ALIGN=\"left\" VALIGN=\"top\"><input type=text name="
						+ getName()
						+ " size=5 maxlength=4 value="
						+ s5
						+ ">"
						+ "<select name="
						+ getName()
						+ "Units size=1>"
						+ "<OPTION "
						+ s4
						+ ">seconds<OPTION "
						+ s3
						+ ">minutes<OPTION "
						+ s2
						+ ">hours<OPTION "
						+ s1
						+ ">days"
						+ "</SELECT></TD></TR>"
						+ "<TR><TD ALIGN=\"left\" VALIGN=\"top\"><FONT SIZE=-1>"
						+ getDescription() + "</FONT></TD></TR>"
						+ "</TABLE></TD><TD><I>" + s + "</I></TD></TR>");
	}
	public int getRealValueWithUnit(String val)
	{
		if (val == null || "".equals(val))
		{
			return getRealValueWithUnit(0);
		}
		return getRealValueWithUnit(Integer.parseInt(val));
	}

	public int getRealValueWithUnit(int val)
	{
		int retval = val;
		if (retval == 0) {
		} else if (retval % daySeconds == 0) {
			retval /= daySeconds;
		} else if (retval % hourSeconds == 0) {
			retval /= hourSeconds;
		} else if (retval % minuteSeconds == 0) {
			retval /= minuteSeconds;
		}
		return retval;
	}
	public String getCurUnit(String val)
	{
		if (val == null || "".equals(val))
		{
			return getCurUnit(0);
		}
		return getCurUnit(Integer.parseInt(val));
	}
	public String getCurUnit(int val)
	{
		String curUnit = "minutes";
		if (val == 0) {
		} else if (val % daySeconds == 0) {
			curUnit = "days";
		} else if (val % hourSeconds == 0) {
			curUnit = "hours";
		} else if (val % minuteSeconds == 0) {
			curUnit = "minutes";
		} else {
			curUnit = "seconds";
		}
		return curUnit;
	}
	
	public Map<String, Integer> getListOption() {
		Map<String, Integer> retmap = new java.util.HashMap<String, Integer>();
		retmap.put("seconds", 1);
		retmap.put("minutes", minuteSeconds);
		retmap.put("hours", hourSeconds);
		retmap.put("days", daySeconds);
		return retmap;
	}
}