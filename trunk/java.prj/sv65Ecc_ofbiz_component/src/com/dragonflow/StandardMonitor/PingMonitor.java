/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * PingMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>PingMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */

import jgl.Array;
import jgl.HashMap;

import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.PercentProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.SiteView.Rule;
import com.dragonflow.Utils.I18N;
import com.dragonflow.Utils.TextUtils;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

public class PingMonitor extends AtomicMonitor
{

    static StringProperty pHost;
    static StringProperty pTimeout;
    static StringProperty pSize;
    static StringProperty pStatus;
    static StringProperty pRoundTripTime;
    static StringProperty pPacketsSent;
    static StringProperty pPacketsReceived;
    static StringProperty pPercentGood;
    static StringProperty pPercentFailed;
    static int kInitialPacketCount = 1;
    static int kRetryPacketCount = 3;

    public PingMonitor()
    {
    }

    public String getHostname()
    {
        return getProperty(pHost);
    }

    public String getTestURL()
    {
        return "/SiteView/cgi/go.exe/SiteView?page=ping&host=" + getProperty(pHost) + "&group=" + HTTPRequest.encodeString(I18N.toDefaultEncoding(getProperty(pGroupID)));
    }

    protected boolean update()
    {
        String s = getProperty(pHost);
        int i = getPropertyAsInteger(pTimeout);
        int j = getPropertyAsInteger(pSize);
        int k = getSettingAsLong("_pingPacketsInitial", kInitialPacketCount);
        int l = getSettingAsLong("_pingPacketsRetry", kRetryPacketCount);
        int execResult[] = Platform.ping(s, i, k, j, this);
        if(execResult[1] != k && l != 0)
        {
            k = l;
            execResult = Platform.ping(s, i, k, j, this);
        }
        int i1 = execResult[1];
        int j1 = execResult[0];
        currentStatus = "PingMonitor analyzing results...";
        if(stillActive())
        {
            synchronized(this)
            {
                if(i1 > 0)
                {
                    setProperty(pStatus, "ok");
                    float f = (float)j1 / (float)i1;
                    if(f < 10F && getSetting("_singleDigitMillis").length() <= 0)
                    {
                        f = 10F;
                    }
                    String s1;
                    if(getSetting("_singleDigitMillis").length() <= 0)
                    {
                        s1 = TextUtils.floatToString(f / 1000F, 2) + " sec";
                    } else
                    {
                        s1 = TextUtils.floatToString(f / 1000F, 3) + " sec";
                    }
                    if(i1 != k)
                    {
                        int k1 = k - i1;
                        s1 = k1 + " out of " + k + " missing, " + s1;
                    }
                    setProperty(pPacketsReceived, i1);
                    setProperty(pPercentGood, TextUtils.floatToString(((float)i1 / (float)k) * 100F, 0));
                    setProperty(pPercentFailed, TextUtils.floatToString((((float)k - (float)i1) / (float)k) * 100F, 0));
                    setProperty(pRoundTripTime, f);
                    setProperty(pMeasurement, getMeasurement(pRoundTripTime, 200L));
                    setProperty(pStateString, s1);
                } else
                {
                    setProperty(pPacketsReceived, 0);
                    setProperty(pPercentGood, 0);
                    setProperty(pPercentFailed, 0);
                    setProperty(pMeasurement, 0);
                    setProperty(pRoundTripTime, "n/a");
                    setProperty(pStatus, "failed");
                    if(j1 == Platform.PING_COMMAND_FAILED)
                    {
                        setProperty(pNoData, "n/a");
                        setProperty(pStateString, "Data Unavailable command failed to execute");
                    } else
                    {
                        setProperty(pStateString, "failed");
                    }
                }
            }
        }
        return true;
    }

    public Array getLogProperties()
    {
        Array array = super.getLogProperties();
        array.add(pStatus);
        array.add(pRoundTripTime);
        array.add(pPercentGood);
        return array;
    }

    public String verify(StringProperty stringproperty, String s, HTTPRequest httprequest, HashMap hashmap)
    {
        if(stringproperty == pHost)
        {
            if(s.length() == 0)
            {
                hashmap.put(stringproperty, stringproperty.getLabel() + " missing");
            } else
            if(TextUtils.hasSpaces(s))
            {
                hashmap.put(stringproperty, "no spaces are allowed");
            }
            return s;
        }
        if(stringproperty == pTimeout)
        {
            if(TextUtils.digits(s) != s.length())
            {
                hashmap.put(stringproperty, "time out must be a number");
            } else
            if(TextUtils.toInt(s) < 100)
            {
                hashmap.put(stringproperty, "time out must be greater than 100 (remember, the timeout is in milliseconds)");
            }
            return s;
        }
        if(stringproperty == pSize)
        {
            if(TextUtils.digits(s) != s.length())
            {
                hashmap.put(stringproperty, "packet size must be a positive number");
            } else
            if(TextUtils.toInt(s) < 1 || TextUtils.toInt(s) > 60000)
            {
                hashmap.put(stringproperty, "packet size must be a number between 1 and 60000");
            }
            return s;
        } else
        {
            return super.verify(stringproperty, s, httprequest, hashmap);
        }
    }

    public String getProperty(StringProperty stringproperty)
        throws NullPointerException
    {
        if(stringproperty == pDiagnosticText)
        {
            if(getProperty(pCategory).equals("good"))
            {
                return "";
            } else
            {
                return DIAGNOSTIC_HEADER + diagnosticTraceRoute(getProperty(pHost)) + "";
            }
        } else
        {
            return super.getProperty(stringproperty);
        }
    }

    static 
    {
        pHost = new StringProperty("_hostname", "", "host name");        
        String description=MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_hostname", MonitorIniValueReader.DESCRIPTION);
        description=description.replaceAll("%1", Platform.exampleDomain);
        pHost.setDisplayText(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_hostname", MonitorIniValueReader.LABEL), description);
        //pHost.setDisplayText("Host Name", "the IP address or host name that will be pinged (examples: 206.168.191.21 or demo." + Platform.exampleDomain + ")");
        pHost.setParameterOptions(true, 1, false);
        
        pTimeout = new NumericProperty("_timeout", "5000", MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_timeout", MonitorIniValueReader.UNIT));
        //pTimeout = new NumericProperty("_timeout", "5000", "milliseconds");
        pTimeout.setDisplayText(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_timeout", MonitorIniValueReader.LABEL), MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_timeout", MonitorIniValueReader.DESCRIPTION));
        //pTimeout.setDisplayText("Timeout", "the time out per packet, in milliseconds, to wait for ping replies\n");
        
        pTimeout.setParameterOptions(true, 2, true);
        pSize = new NumericProperty("_packetSize", "32", "bytes");   
        pSize.setDisplayText(MonitorIniValueReader.getValue(PingMonitor.class.getName(),"_packetSize",MonitorIniValueReader.LABEL), MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_packetSize", MonitorIniValueReader.DESCRIPTION));
        //pSize.setDisplayText("Size", "the size, in bytes, of the ping message");
        
        pSize.setParameterOptions(true, 3, true);
        pRoundTripTime = new NumericProperty("roundTripTime", "0", "milliseconds");
        pRoundTripTime.setLabel(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_roundTripTime", MonitorIniValueReader.LABEL));
        //pRoundTripTime.setLabel("round trip time");
        
        pRoundTripTime.setStateOptions(1);
        pStatus = new StringProperty("status", "no data");
        pPercentGood = new PercentProperty("percentGood");
        pPercentGood.setLabel(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_percentGood", MonitorIniValueReader.LABEL));
        //pPercentGood.setLabel("% packets good");
        
        pPercentGood.setStateOptions(3);
        pPercentFailed = new PercentProperty("percentFailed");
        pPercentFailed.setLabel(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_percentFailed", MonitorIniValueReader.LABEL));
        //pPercentFailed.setLabel("% packets failed");
        
        pPacketsSent = new NumericProperty("packetsSent");
        pPacketsSent.setLabel(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_packetsSent", MonitorIniValueReader.LABEL));
        //pPacketsSent.setLabel("packets sent");
        
        pPacketsReceived = new NumericProperty("packetsReceived");
        pPacketsReceived.setLabel(MonitorIniValueReader.getValue(PingMonitor.class.getName(), "_packetsReceived", MonitorIniValueReader.LABEL));
        //pPacketsReceived.setLabel("packets received");
        
        StringProperty astringproperty[] = {
            pHost, pTimeout, pSize, pStatus, pRoundTripTime, pPacketsSent, pPacketsReceived, pPercentGood, pPercentFailed
        };
        addProperties("com.dragonflow.StandardMonitor.PingMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.PingMonitor", Rule.stringToClassifier("percentGood == 0\terror", true));
        addClassElement("com.dragonflow.StandardMonitor.PingMonitor", Rule.stringToClassifier("roundTripTime == n/a\terror"));
        addClassElement("com.dragonflow.StandardMonitor.PingMonitor", Rule.stringToClassifier("percentGood < 100\twarning", true));
        addClassElement("com.dragonflow.StandardMonitor.PingMonitor", Rule.stringToClassifier("percentGood == 100\tgood", true));
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","description",MonitorTypeValueReader.getValue(PingMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "description", "Pings a device on the network.");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "help", "PingMon.htm");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","title",MonitorTypeValueReader.getValue(PingMonitor.class.getName(),  MonitorTypeValueReader.TITLE));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "title", "Ping");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "class", "PingMonitor");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","target",MonitorTypeValueReader.getValue(PingMonitor.class.getName(), MonitorTypeValueReader.TARGET));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "target", "_hostname");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","toolName",MonitorTypeValueReader.getValue(PingMonitor.class.getName(),  MonitorTypeValueReader.TOOLNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "toolName", "Ping");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","toolDescription",MonitorTypeValueReader.getValue(PingMonitor.class.getName(),  MonitorTypeValueReader.TOOLDESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "toolDescription", "Performs a roundtrip test on the network.");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","topazName",MonitorTypeValueReader.getValue(PingMonitor.class.getName(),  MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "topazName", "Ping");
        
        setClassProperty("com.dragonflow.StandardMonitor.PingMonitor","topazType",MonitorTypeValueReader.getValue(PingMonitor.class.getName(),  MonitorTypeValueReader.TOPAZTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.PingMonitor", "topazType", "System Resources");
    }

	@Override
	public boolean getSvdbRecordState(String paramName, String operate,
			String paramValue) {
		if ("packetsGoodPercent".equals(paramName)){
			float val = PercentProperty.toFloat(getProperty(pPercentGood.getName()));
			float paramVal = PercentProperty.toFloat(paramValue);
			if ("==".equals(operate)){
				return val == paramVal;
			}else if ("<=".equals(operate)){
				return val <= paramVal;
			}else if (">".equals(operate)){
				return val > paramVal;
			}
				
		}
		return false;
	}

	@Override
	public String getSvdbkeyValueStr() {
		StringBuffer bf = new StringBuffer();
		bf.append("包成功率(%)=" );
		bf.append(getProperty(pPercentGood.getName()));
		bf.append(",数据往返时间(ms)=" );
		bf.append(getProperty(pRoundTripTime.getName()));
		bf.append(",状态值=" );
		bf.append(getProperty(pStatus.getName()));
		return bf.toString();
	}
}
