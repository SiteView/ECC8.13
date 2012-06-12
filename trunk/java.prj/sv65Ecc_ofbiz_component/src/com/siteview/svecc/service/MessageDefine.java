package com.siteview.svecc.service;

import java.text.SimpleDateFormat;

public interface MessageDefine {
	public static final Long THROW_TYPE_UNKNOWN = 0000L;
	public static final Long THROW_TYPE_OPTIONAL_PARAM = 0006L;
	public static final Long THROW_TYPE_PARAM_NOT_FOUND = 1003L;
	public static final Long THROW_TYPE_PARAM_DUPLICATE = 1002L;
	public static final Long THROW_TYPE_PASSWORD_NOT_VALID = 1001L;
	public static final Long THROW_TYPE_PASSWORD_EQUALS = 1007L;
	
	public static final String MONITOR_DISPATCHER_NAME = "monitorDispatcher";
	public static final String MONITOR_DELEGATOR_NAME = "default";
	
	public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss S");
	
	public static final String PARAMDATA_REPLACE = "%n";

	public static final String NO_CHANGED_PASSWORD = "********";
	
}
