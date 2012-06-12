/*
 * 
 * Created on 2005-3-7 1:22:18
 *
 * HistoryHealthMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>HistoryHealthMonitor</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import com.dragonflow.Health.HistoryHealth;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.Rule;
import com.siteview.ecc.util.MonitorTypeValueReader;

// Referenced classes of package com.dragonflow.StandardMonitor:
// HealthMonitorBase

public class HistoryHealthMonitor extends HealthMonitorBase {

    public HistoryHealthMonitor() {
    }

    /**
     * CAUTION: Decompiled by hand.
     */
    protected boolean update() {
        try {
			HistoryHealth hh=new HistoryHealth();
            setStatus(hh);
            return true;
        } catch (Exception e) {
            setProperty(pStateString, e.getMessage());
            return false;
        }
    }

    public static void main(String args[]) {
        HistoryHealthMonitor historyhealthmonitor = new HistoryHealthMonitor();
        historyhealthmonitor.update();
        System.out.println("health: " + historyhealthmonitor.getProperty(HealthMonitorBase.pNumErrors));
        System.exit(0);
    }

    static {
        String s = (com.dragonflow.StandardMonitor.HistoryHealthMonitor.class).getName();
        StringProperty astringproperty[] = new StringProperty[0];
        addProperties(s, astringproperty);
        setClassProperty(s, "class", "HistoryHealthMonitor");
        
        setClassProperty(s, "description", MonitorTypeValueReader.getValue(HistoryHealthMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty(s, "description", "Monitors health of history.config configuration file");
        
        setClassProperty(s, "title", MonitorTypeValueReader.getValue(HistoryHealthMonitor.class.getName(), MonitorTypeValueReader.TITLE));
        //setClassProperty(s, "title", "History Health Monitor");
        
        setClassProperty(s, "help", "HistoryHealthMonitor.htm");
        
        setClassProperty(s, "target", MonitorTypeValueReader.getValue(HistoryHealthMonitor.class.getName(), MonitorTypeValueReader.TARGET));
        //setClassProperty(s, "target", "_server");
        
        setClassProperty(s, "topazName", MonitorTypeValueReader.getValue(HistoryHealthMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty(s, "topazName", "History Health Monitor");
        
        setClassProperty(s, "classType", MonitorTypeValueReader.getValue(HistoryHealthMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
        //setClassProperty(s, "classType", "application");        
        
        setClassProperty(s, "addable", "false");
        addClassElement(s, Rule.stringToClassifier("numErrors > 0\terror", true));
        addClassElement(s, Rule.stringToClassifier("always\tgood"));
    }
}
