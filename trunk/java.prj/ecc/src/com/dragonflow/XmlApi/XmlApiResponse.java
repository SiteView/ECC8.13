/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.XmlApi;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */


public class XmlApiResponse extends jgl.HashMap
{

    public static final int OPERATIONAL_ERROR = 0;
    public static final int AVAILABILITY_ERROR = 1;
    public static final int PARAMETER_ERROR = 2;
    public static final java.lang.String OPERATIONAL_STR = "operational";
    public static final java.lang.String AVAILABILITY_STR = "availability";
    public static final java.lang.String PARAMETER_STR = "parameter";
    public static final java.lang.String NEW_RESPONSE_KEY = "newresponse";
    public static final java.lang.String ERROR_CODE_KEY = "errorcode";
    public static final java.lang.String VECTOR_KEY = "vector";
    public static final java.lang.String ERROR_PARAMETERS_KEY = "errorparameters";
    public static final java.lang.String ERROR_ARGS_KEY = "errorargs";
    public static final java.lang.String ERROR_KEY = "error";
    public static final java.lang.String ERROR_TYPE_KEY = "errortype";
    public static final java.lang.String ERROR_APP_CODE_KEY = "applicationerrorcode";
    public static final java.lang.String ERROR_APP_MSG_KEY = "applicationerrormessage";

    public XmlApiResponse()
    {
    }

    public void setError(java.lang.String s)
    {
        if(s != null)
        {
            put("error", s);
        }
    }

    public java.lang.String getError()
    {
        return (java.lang.String)get("error");
    }

    public void setErrorCode(java.lang.String s)
    {
        if(s != null)
        {
            put("errorcode", s);
        }
    }

    public java.lang.String getErrorCode()
    {
        return (java.lang.String)get("errorcode");
    }

    public void setReturnVector(java.util.Vector vector)
    {
        if(vector != null)
        {
            put("vector", vector);
        }
    }

    public void setParameterErrors(java.util.Map map)
    {
        if(map != null)
        {
            put("errorparameters", map);
        }
    }

    public java.util.Map getParameterErrors()
    {
        return (java.util.Map)get("errorparameters");
    }

    public void setErrorArguments(java.lang.String as[])
    {
        if(as != null)
        {
            put("errorargs", as);
        }
    }

    public java.lang.String[] getErrorArguments()
    {
        return (java.lang.String[])get("errorargs");
    }

    public void setApplicationErrorCode(java.lang.String s)
    {
        if(s != null)
        {
            put("applicationerrorcode", s);
        }
    }

    public java.lang.String getApplicationErrorCode()
    {
        return (java.lang.String)get("applicationerrorcode");
    }

    public void setApplicationErrorMessage(java.lang.String s)
    {
        if(s != null)
        {
            put("applicationerrormessage", s);
        }
    }

    public java.lang.String getApplicationErrorMessage()
    {
        return (java.lang.String)get("applicationerrormessage");
    }

    public void setErrorType(int i)
    {
        if(i == 0)
        {
            put("errortype", "operational");
        } else
        if(i == 1)
        {
            put("errortype", "availability");
        } else
        if(i == 2)
        {
            put("errortype", "parameter");
        }
    }

    public java.lang.String getErrorType()
    {
        return (java.lang.String)get("errortype");
    }

    public boolean hasErrors()
    {
        boolean flag = false;
        java.lang.String s = (java.lang.String)get("errortype");
        if(s != null && s.length() > 0)
        {
            flag = true;
        }
        return flag;
    }

    public boolean isParameterError()
    {
        boolean flag = false;
        java.lang.String s = (java.lang.String)get("errortype");
        if(s != null && s.length() > 0 && s.equals("parameter"))
        {
            flag = true;
        }
        return flag;
    }

    public boolean isOperationalError()
    {
        boolean flag = false;
        java.lang.String s = (java.lang.String)get("errortype");
        if(s != null && s.length() > 0 && s.equals("operational"))
        {
            flag = true;
        }
        return flag;
    }

    public boolean isAvailabilityError()
    {
        boolean flag = false;
        java.lang.String s = (java.lang.String)get("errortype");
        if(s != null && s.length() > 0 && s.equals("availability"))
        {
            flag = true;
        }
        return flag;
    }

    public java.util.Vector getReturnVector()
    {
        return (java.util.Vector)get("vector");
    }

    public void setErrorResponse(com.dragonflow.SiteViewException.SiteViewException siteviewexception)
    {
        setError(siteviewexception.getMessage());
        setErrorCode((new Long(siteviewexception.getErrorCode())).toString());
        setErrorArguments(siteviewexception.getFormattedErrorArgs());
        if(siteviewexception instanceof com.dragonflow.SiteViewException.SiteViewParameterException)
        {
            setErrorType(2);
            setParameterErrors(((com.dragonflow.SiteViewException.SiteViewParameterException)siteviewexception).getErrorParameterMap());
        } else
        if(siteviewexception instanceof com.dragonflow.SiteViewException.SiteViewOperationalException)
        {
            setErrorType(0);
            setApplicationErrorCode((new Long(((com.dragonflow.SiteViewException.SiteViewOperationalException)siteviewexception).getApplicationErrorCode())).toString());
            setApplicationErrorMessage(((com.dragonflow.SiteViewException.SiteViewOperationalException)siteviewexception).getApplicationErrorMessage());
        } else
        if(siteviewexception instanceof com.dragonflow.SiteViewException.SiteViewAvailabilityException)
        {
            setErrorType(1);
            setApplicationErrorCode((new Long(((com.dragonflow.SiteViewException.SiteViewAvailabilityException)siteviewexception).getApplicationErrorCode())).toString());
            setApplicationErrorMessage(((com.dragonflow.SiteViewException.SiteViewAvailabilityException)siteviewexception).getApplicationErrorMessage());
        }
    }
}
