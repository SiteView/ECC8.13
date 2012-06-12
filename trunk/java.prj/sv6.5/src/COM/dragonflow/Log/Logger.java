/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Log;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.util.Vector;

public abstract class Logger {

    static java.lang.String FIELD_SEPARATOR = "\t";

    protected java.util.Vector buffers;

    protected long bufferDuration;

    public java.lang.String echoTo;

    protected java.lang.String fullMonitorName;

    public Logger() {
        buffers = new Vector();
        bufferDuration = 0L;
        echoTo = "";
        fullMonitorName = null;
    }

    public Logger(long l) {
        buffers = new Vector();
        bufferDuration = 0L;
        echoTo = "";
        fullMonitorName = null;
        bufferDuration = l;
    }

    public static java.lang.String dateToString(java.util.Date date) {
        return COM.dragonflow.Utils.TextUtils.dateToString(date);
    }

    public void setEchoTo(java.lang.String s) {
        echoTo = s.toLowerCase();
    }

    java.lang.String getMonitorName(COM.dragonflow.Properties.PropertiedObject propertiedobject) {
        if (fullMonitorName == null) {
            jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
            fullMonitorName = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_fullMonitorName");
        }
        java.lang.String s = "";
        if (fullMonitorName.length() > 0) {
            s = COM.dragonflow.Page.CGI.getGroupFullName(propertiedobject.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pGroupID));
            s = s + ": " + propertiedobject.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pName);
        } else {
            s = propertiedobject.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pName);
        }
        return s;
    }

    public void log(java.lang.String s, java.util.Date date, COM.dragonflow.Properties.PropertiedObject propertiedobject) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        jgl.Array array = propertiedobject.getLogProperties();
        java.lang.String s1;
        for (java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); stringbuffer.append(s1)) {
            COM.dragonflow.Properties.StringProperty stringproperty = (COM.dragonflow.Properties.StringProperty) enumeration.nextElement();
            if (stringbuffer.length() > 0) {
                stringbuffer.append("\t");
            }
            if (stringproperty == COM.dragonflow.SiteView.Monitor.pID) {
                s1 = propertiedobject.getProperty(stringproperty) + ":" + propertiedobject.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pSample);
            } else if (stringproperty == COM.dragonflow.SiteView.AtomicMonitor.pName) {
                s1 = getMonitorName(propertiedobject);
            } else {
                s1 = propertiedobject.getProperty(stringproperty);
            }
            s1 = s1.replace('\r', ' ');
            s1 = s1.replace('\n', ' ');
            s1 = s1.replace('\t', ' ');
        }

        if (propertiedobject.getProperty(COM.dragonflow.SiteView.Monitor.pCategory).equals(COM.dragonflow.SiteView.Monitor.ERROR_CATEGORY)) {
            stringbuffer.append("\t");
            if (((COM.dragonflow.SiteView.AtomicMonitor) propertiedobject).getProperty(COM.dragonflow.SiteView.AtomicMonitor.pNoData).length() > 0) {
                stringbuffer.append(COM.dragonflow.SiteView.Monitor.FAILURE);
            } else {
                stringbuffer.append(COM.dragonflow.SiteView.Monitor.NON_FAILURE);
            }
        }
        log(s, date, stringbuffer.toString());
    }

    public void log(java.lang.String s, java.util.Date date, java.lang.String s1) {
    }

    public void close() {
    }

    public java.lang.String customLogName() {
        return "";
    }

    public long getBufferDuration() {
        return bufferDuration;
    }

    public void flush() {
        for (; buffers.size() > 0; flush(buffers.remove(0))) {
        }
    }

    public void flush(java.lang.Object obj) {
    }

}
