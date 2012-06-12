/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * NetworkMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>NetworkMonitor</code>
 * 
 * @author 
 * @version 0.0
 *
 *
 */

import com.dragonflow.Properties.*;
import com.dragonflow.SiteView.*;
import com.dragonflow.Utils.TextUtils;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

import java.io.PrintStream;
import java.util.Date;
import jgl.Array;

public class NetworkMonitor extends AtomicMonitor
{

    static NumericProperty pConnections;
    static RateProperty pBytesInPerSecond;
    static RateProperty pBytesOutPerSecond;
    static RateProperty pPacketErrorsPerSecond;
    static NumericProperty pLastBytesIn;
    static NumericProperty pLastBytesOut;
    static NumericProperty pLastPacketErrors;
    static NumericProperty pLastMeasurement;

    public NetworkMonitor()
    {
    }

    public String getHostname()
    {
        return "";
    }

    public String getTestURL()
    {
        return "/SiteView/cgi/go.exe/SiteView?page=network";
    }

    static boolean isError(long al[])
    {
        return al[0] == -1L || al[1] == -1L || al[2] == -1L || al[3] == -1L;
    }

    protected boolean update()
    {
        long l = 0L;
        long l1 = 0L;
        long l2 = 0L;
        long l3 = 0L;
        try
        {
            l = Long.parseLong(getProperty(pLastBytesIn));
            l1 = Long.parseLong(getProperty(pLastBytesOut));
            l2 = Long.parseLong(getProperty(pLastPacketErrors));
            l3 = Long.parseLong(getProperty(pLastMeasurement));
        }
        catch(NumberFormatException numberformatexception) { }
        boolean flag = true;
        if(l3 == 0L)
        {
            long al[] = Platform.getNetStats();
            Date date = new Date();
            l3 = date.getTime();
            if(!isError(al))
            {
                l = al[0];
                l1 = al[1];
                l2 = al[2];
                Platform.sleep(2000L);
            } else
            {
                flag = false;
            }
        }
        long al1[] = Platform.getNetStats();
        Date date1 = new Date();
        long l4 = date1.getTime();
        float f = al1[0];
        float f1 = al1[1];
        long l5 = al1[2];
        long l6 = al1[3];
        float f2 = l4 - l3;
        float f3 = -1F;
        float f4 = -1F;
        float f5 = -1F;
        if(!isError(al1) && (double)f2 > 0.0D)
        {
            f2 /= 1000F;
            f3 = (f - (float)l) / f2;
            f4 = (f1 - (float)l1) / f2;
            f5 = (float)(l5 - l2) / f2;
        } else
        {
            flag = false;
        }
        if(stillActive())
        {
            synchronized(this)
            {
                if(flag)
                {
                    setProperty(pLastBytesIn, String.valueOf(f));
                    setProperty(pLastBytesOut, String.valueOf(f1));
                    setProperty(pLastPacketErrors, String.valueOf(l5));
                    setProperty(pLastMeasurement, String.valueOf(l4));
                    setProperty(pBytesInPerSecond, String.valueOf(f3));
                    setProperty(pBytesOutPerSecond, String.valueOf(f4));
                    setProperty(pPacketErrorsPerSecond, String.valueOf(f5));
                    setProperty(pConnections, String.valueOf(l6));
                    String s = TextUtils.bytesToString((long)f3) + " in/sec., ";
                    s = s + TextUtils.bytesToString((long)f4) + " out/sec., ";
                    s = s + TextUtils.floatToString(f5, 2) + " packet errors/sec., ";
                    s = s + l6 + " current connections.";
                    setProperty(pStateString, s);
                } else
                {
                    if(isError(al1))
                    {
                        setProperty(pStateString, "net statistics not found");
                    } else
                    {
                        setProperty(pStateString, "no data");
                    }
                    setProperty(pMeasurement, getMeasurement(pBytesOutPerSecond, 0x20000L));
                    setProperty(pLastBytesIn, "n/a");
                    setProperty(pLastBytesOut, "n/a");
                    setProperty(pLastPacketErrors, "n/a");
                    setProperty(pLastMeasurement, String.valueOf(0));
                    setProperty(pBytesInPerSecond, "n/a");
                    setProperty(pBytesOutPerSecond, "n/a");
                    setProperty(pPacketErrorsPerSecond, "n/a");
                    setProperty(pConnections, "n/a");
                    setProperty(pNoData, "n/a");
                }
            }
        }
        return true;
    }

    public Array getLogProperties()
    {
        Array array = super.getLogProperties();
        array.add(pBytesInPerSecond);
        array.add(pBytesOutPerSecond);
        array.add(pPacketErrorsPerSecond);
        array.add(pConnections);
        return array;
    }

    public static void main(String args[])
    {
        System.out.println("\n---------------------------");
        System.out.println("  Testing Network Monitor");
        System.out.println("---------------------------\n");
        NetworkMonitor networkmonitor = new NetworkMonitor();
        networkmonitor.update();
        System.out.println("\n--------");
        System.out.println("  done");
        System.out.println("--------\n");
    }

    static 
    {
    	pBytesOutPerSecond = new RateProperty("outBytesPerSecond", "0", MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "outBytesPerSecond", MonitorIniValueReader.UNIT));
        //pBytesOutPerSecond = new RateProperty("outBytesPerSecond", "0", "bytes", "seconds");
    	pBytesOutPerSecond.setLabel(MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "outBytesPerSecond", MonitorIniValueReader.LABEL));
        //pBytesOutPerSecond.setLabel("bytes/sec sent");
        pBytesOutPerSecond.setStateOptions(1);
        
        pBytesInPerSecond = new RateProperty("inBytesPerSecond", "0", MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "inBytesPerSecond", MonitorIniValueReader.UNIT));
        //pBytesInPerSecond = new RateProperty("inBytesPerSecond", "0", "bytes", "seconds");
        pBytesInPerSecond.setLabel(MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "inBytesPerSecond", MonitorIniValueReader.LABEL));
        //pBytesInPerSecond.setLabel("bytes/sec received");
        pBytesInPerSecond.setStateOptions(2);
        
        pConnections = new NumericProperty("connections", "0", MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "connections", MonitorIniValueReader.UNIT));
        //pConnections = new NumericProperty("connections", "0", "connections");
        pConnections.setLabel(MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "connections", MonitorIniValueReader.LABEL));
        pConnections.setLabel("Active connections");
        pConnections.setStateOptions(3);
        
        pPacketErrorsPerSecond = new RateProperty("errorsPerSecond", "0", MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "errorsPerSecond", MonitorIniValueReader.UNIT));
        //pPacketErrorsPerSecond = new RateProperty("errorsPerSecond", "0", "errors", "seconds");
        pPacketErrorsPerSecond.setLabel(MonitorIniValueReader.getValue(NetworkMonitor.class.getName(), "errorsPerSecond", MonitorIniValueReader.LABEL));
        //pPacketErrorsPerSecond.setLabel("packet errors/sec");
        pPacketErrorsPerSecond.setStateOptions(4);
        
        pLastBytesIn = new NumericProperty("lastBytesIn");
        
        pLastBytesOut = new NumericProperty("lastBytesOut");
        
        pLastPacketErrors = new NumericProperty("lastPacketErrors");
        
        pLastMeasurement = new NumericProperty("lastMeasurement");
        StringProperty astringproperty[] = {
            pBytesOutPerSecond, pBytesInPerSecond, pConnections, pPacketErrorsPerSecond, pLastBytesIn, pLastBytesOut, pLastPacketErrors, pLastMeasurement
        };
        addProperties("com.dragonflow.StandardMonitor.NetworkMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.NetworkMonitor", Rule.stringToClassifier("errorsPerSecond != 0\terror", true));
        addClassElement("com.dragonflow.StandardMonitor.NetworkMonitor", Rule.stringToClassifier("outBytesPerSecond > 50000\twarning", true));
        addClassElement("com.dragonflow.StandardMonitor.NetworkMonitor", Rule.stringToClassifier("outBytesPerSecond == n/a\terror"));
        addClassElement("com.dragonflow.StandardMonitor.NetworkMonitor", Rule.stringToClassifier("always\tgood"));
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "description", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "description", "Measure network statistics");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "help", "NetworkMon.htm");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "title", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.TITLE));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "title", "Network");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "class", "NetworkMonitor");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "classType", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "classType", "server");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "toolName", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.TOOLNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "toolName", "Network");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "topazName", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "topazName", "Network");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "topazType", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "topazType", "System Resources");
        
        setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "toolDescription", MonitorTypeValueReader.getValue(NetworkMonitor.class.getName(), MonitorTypeValueReader.TOOLDESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "toolDescription", "Display the server's network interface status and active connections.");
        if(Platform.isWindows())
        {
            setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "loadable", "true");
        } else
        {
            setClassProperty("com.dragonflow.StandardMonitor.NetworkMonitor", "loadable", "false");
        }
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
