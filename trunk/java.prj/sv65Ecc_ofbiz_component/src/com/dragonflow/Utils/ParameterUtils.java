package com.dragonflow.Utils;

import org.apache.commons.httpclient.NameValuePair;

public class ParameterUtils {
	public static String getRequestBodyAsString(NameValuePair[] parameters)
	{
		StringBuffer retbuf = new StringBuffer();
		for (NameValuePair param : parameters)
		{
			if (retbuf.length() > 0) retbuf.append("&");
			retbuf.append(param.getName());
			retbuf.append("=");
			retbuf.append(param.getValue());
		}
		return retbuf.toString();
	}
}
