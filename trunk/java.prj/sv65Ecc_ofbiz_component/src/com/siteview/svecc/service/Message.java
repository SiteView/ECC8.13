package com.siteview.svecc.service;

import java.util.List;
import java.util.Map;

import org.ofbiz.base.util.Debug;
import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;
import org.ofbiz.entity.condition.EntityCondition;
import org.ofbiz.entity.condition.EntityOperator;
import org.ofbiz.service.DispatchContext;
import org.ofbiz.service.ServiceUtil;

public class Message extends BaseClass{
	public static final String module = Message.class.getName();
	
	public static String getMessage(Long messageCode) throws Exception
	{
		return getMessage(messageCode,getGenericDelegator());
	}
	public static String getMessage(Long messageCode,GenericDelegator delegator) throws Exception
	{
        EntityCondition whereCondition = EntityCondition.makeCondition("id", EntityOperator.EQUALS, messageCode);
        
        List<GenericValue> list = delegator.findList("SvMessage", whereCondition,null,null,null,false);
        
        for (GenericValue val : list)
        {
        	return val.getString("message");
        }
        if (messageCode.equals(0L)) new Exception("UNKNOWN ERROR");
        throwException(THROW_TYPE_UNKNOWN);
        return null;
 	}
	public static Map<?, ?> getMessage(DispatchContext ctx, Map<?, ?> context) {
		try {
			Long messageCode = (Long) getNotOptionalValue(context,"messageCode");
			Map<String, Object> retresult = ServiceUtil.returnSuccess();
			retresult.put("result", getMessage(messageCode,ctx.getDelegator()));
			return retresult;
		} catch (Exception e) {
			Debug.logWarning(e, module);
			Map<String, Object> retresult = ServiceUtil.returnError("Error getMessage: " + e.toString());
			retresult.put("result", "");
			retresult.put("message", e.toString());
			return retresult;
		}
	}	
}
