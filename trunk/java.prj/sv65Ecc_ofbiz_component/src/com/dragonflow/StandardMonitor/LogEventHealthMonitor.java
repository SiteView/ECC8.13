/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * LogEventHealthMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>LogEventHealthMonitor</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.util.Vector;

import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Health.logEventHealth;
import com.dragonflow.Log.LogManager;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.MultiContentBase;
import com.dragonflow.SiteView.Rule;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

public class LogEventHealthMonitor extends MultiContentBase {

    static StringProperty pCounters;

    protected static StringProperty pStatus;

    static String returnURL;

    public static String templateFile;

    protected static StringProperty pLogValues[];

    public LogEventHealthMonitor() {
    }

    protected StringProperty getStateValue(int i) {
        return pLogValues[i];
    }

    protected StringProperty[] getStateValues() {
        return pLogValues;
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    protected boolean update() {
        try {
            for (int i = 0; i < pLogValues.length; i ++) {
                unsetProperty(pLogValues[i]);
            }

            String as[] = buildThresholdsArray();
            StringBuffer stringbuffer = new StringBuffer(as.length * 50);
            for (int j = 0; j < as.length; j ++) {
                Vector vector = logEventHealth.getMatches(as[j]);
                int k = vector == null ? 0 : vector.size();
                String s = Integer.toString(k);
                setProperty(pLogValues[j], s);
                pLogValues[j].setLabel(as[j]);
                stringbuffer.append(as[j]).append(":&nbsp;").append(s);
                if (j < as.length - 1) {
                    stringbuffer.append(", ");
                }
            }

            setProperty(pStatus, "ok");
            setProperty(pStateString, stringbuffer.toString());
            return true;
        } catch (Exception e) {
            setProperty(pStateString, e.getMessage());
            setProperty(pStatus, "Error");
            return false;
        }
    }

    public String getCountersContent() {
        return getProperty(pCounters);
    }

    public StringProperty getCountersProperty() {
        return pCounters;
    }

    public void setCountersContent(String s) {
        setProperty(pCounters, s);
    }

    public String getReturnURL() {
        return returnURL;
    }

    public String getTemplateFile() {
        return templateFile;
    }

    public String verify(StringProperty stringproperty, String s, HTTPRequest httprequest, HashMap hashmap) {
        if (stringproperty == getCountersProperty()) {
            String s1 = getCountersContent();
            if (s1.length() <= 0) {
                hashmap.put(stringproperty, "No counters selected");
            }
            return s;
        } else {
            return super.verify(stringproperty, s, httprequest, hashmap);
        }
    }

    public void initialize(HashMap hashmap) {
        super.initialize(hashmap);
        String as[] = buildThresholdsArray();
        for (int i = 0; i < as.length; i ++) {
            logEventHealth.addSearchString(as[i]);
        }

    }

    public String getTestTitle() {
        return "Reset";
    }

    public String getTestURL() {
        String s = "/SiteView/cgi/go.exe/SiteView?page=reset&class=logEventHealth&id=" + getProperty(pID);
        return s;
    }

    public void reset() {
        logEventHealth.reset();
    }

    public int getCostInLicensePoints() {
        return 0;
    }

    static {
        returnURL = "/SiteView/cgi/go.exe/SiteView/?page=monitor&class=LogEventHealthMonitor";
        templateFile = "counters.logEvents";
        String s = (com.dragonflow.StandardMonitor.LogEventHealthMonitor.class).getName();
        pCounters = new StringProperty("_counters", getTemplateContent(getTemplatePath(), templateFile, false), MonitorIniValueReader.getValue(LogEventHealthMonitor.class.getName(), "_counters", MonitorIniValueReader.UNIT));
        //pCounters = new StringProperty("_counters", getTemplateContent(getTemplatePath(), templateFile, false), "Log Event Health Monitor Selected Counters");
        String counters_description=MonitorIniValueReader.getValue(LogEventHealthMonitor.class.getName(), "_counters", MonitorIniValueReader.DESCRIPTION);
        try {
        	counters_description=counters_description.replaceAll("1%", URLEncoder.encode(returnURL, "UTF-8"));
        	counters_description=counters_description.replaceAll("2%", ""+nMaxCounters);
        	counters_description=counters_description.replaceAll("3%", templateFile);
        	pCounters.setDisplayText(MonitorIniValueReader.getValue(LogEventHealthMonitor.class.getName(), "_counters", MonitorIniValueReader.LABEL), counters_description);
            //pCounters.setDisplayText("Counters", "the current selection of counters</TD></TR><TR><TD></TD><TD><A HREF=\"/SiteView/cgi/go.exe/SiteView/?page=counter&returnURL=" + URLEncoder.encode(returnURL, "UTF-8") + "&maxcounters=" + nMaxCounters
            //        + "&filename=" + templateFile + "&type=URLContent\">choose counters</A>");
        } catch (UnsupportedEncodingException unsupportedencodingexception) {
            LogManager.log("error", "Failed to encode URL in LogEventHealthMonitor static initializer: " + unsupportedencodingexception);
        }
        pCounters.setParameterOptions(true, 1, false);
        pCounters.isMultiLine = true;
        
        pStatus = new StringProperty("status", "n/a");
        StringProperty astringproperty[] = new StringProperty[nMaxCounters + 2];
        astringproperty[0] = pStatus;
        astringproperty[1] = pCounters;
        pLogValues = staticInitializer(nMaxCounters);
        for (int i = 0; i < nMaxCounters; i ++) {
            astringproperty[i + 2] = pLogValues[i];
        }

        addProperties(s, astringproperty);
        setClassProperty(s, "class", "LogEventHealthMonitor");
        
        setClassProperty(s, "description", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty(s, "description", "Monitors log entries");
        
        setClassProperty(s, "title", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.TITLE));
        //setClassProperty(s, "title", "Log Event Health Monitor");
        
        setClassProperty(s, "help", "LogEventHealthMonitor.htm");
        
        setClassProperty(s, "target", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.TARGET));
        //setClassProperty(s, "target", "_server");
        
        setClassProperty(s, "topazName", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty(s, "topazName", "Log Event Health Monitor");
        
        setClassProperty(s, "classType", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
        //setClassProperty(s, "classType", "application");
        
        setClassProperty(s, "applicationType", MonitorTypeValueReader.getValue(LogEventHealthMonitor.class.getName(), MonitorTypeValueReader.APPLICATIONTYPE));
        //setClassProperty(s, "applicationType", "MultiContentBase");
        
        setClassProperty(s, "addable", "false");
        addClassElement(s, Rule.stringToClassifier("status != 'ok'\terror"));
        addClassElement(s, Rule.stringToClassifier("status == 'ok'\tgood"));
    }

	@Override
	public boolean getSvdbRecordState(String paramName, String operate,
			String paramValue) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getSvdbkeyValueStr() {
		// TODO Auto-generated method stub
		return null;
	}
}
