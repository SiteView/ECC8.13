/*
 * 
 * Created on 2005-3-5 14:18:52
 *
 * ArmSisMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>ArmSisMonitor</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;
import com.dragonflow.HTTP.HTTPRequest;
import com.dragonflow.Properties.PropertiedObject;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Monitor;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.Utils.EmsDummyMonitor;
import com.dragonflow.Utils.LUtils;
import com.dragonflow.ems.Shared.EmsConfigFileProperty;
import com.dragonflow.ems.Shared.EmsMeasurementConfigFileProperty;
import com.dragonflow.ems.Shared.EmsTimeDiffProperty;
import com.dragonflow.ems.xmlMonitor.EmsBaseMonitor;
import com.dragonflow.ems.xmlMonitor.StaticInitializer;
import com.siteview.ecc.util.MonitorTypeValueReader;
//import com.dragonflow.topaz.ems.arm.ArmMonitor;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.JdbcConfiguration;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.JdbcMonitor;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.JdbcMonitorCallback;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.JdbcMonitorContext;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.util.ResultSetEnumerator;
//import com.dragonflow.topaz.ems.monitorComps.jdbcMonitor.util.SimpleResultSetEnumerator;
//import com.dragonflow.topaz.ems.monitorComps.pullMonitor.lifeCycle.MonitorEmulator;

public class ArmSisMonitor extends AtomicMonitor //implements JdbcMonitorCallback 
{

//    private MonitorEmulator emulator;

    private static final String EMS_NAME = "Application Relationship Mapping";

    private static final String NOT_AVAILABLE = "n/a";

    private static final String MONITOR_NAME = "com.dragonflow.StandardMonitor.ArmSisMonitor";

    private static StringProperty pStatus;

    public ArmSisMonitor() {
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    private Timestamp getStartTime() {
        String measure = getProperty("pStartTime");
        Timestamp start = null;
        try {
            if (measure != null && measure.length() > 4) {
                start = new Timestamp(Long.parseLong(measure));
            }
            if (start == null) {
                start = new Timestamp(System.currentTimeMillis() - getTimeDiffValue() * 1000L);
            }
        } catch (Throwable t) {
            if (start == null) {
                start = new Timestamp(System.currentTimeMillis() - getTimeDiffValue() * 1000L);
            }
        } finally {
            if (start == null) {
                start = new Timestamp(System.currentTimeMillis() - getTimeDiffValue() * 1000L);
            }
        }
        return start;
    }

    protected static void handleEmsLicense(String className) {
        PropertiedObject.setClassProperty(className, "loadable", LUtils.isValidSSforXLicense(new EmsDummyMonitor()) ? "true" : "false");
    }

    protected long getTimeDiffValue() {
        long l = 0L;
        EmsTimeDiffProperty p = (EmsTimeDiffProperty) getPropertyObject("_emsTimeDiff");
        if (p != null) {
            l = p.getEmsTimeDiff(this);
        }
        return l;
    }

    public void setMonitorStatus(int status) {
        setProperty("pMStatus", Integer.toString(status));
        switch (status) {
        case 2: // '\002'
            setProperty(Monitor.pCategory, Monitor.ERROR_CATEGORY);
            break;

        case 1: // '\001'
            setProperty(Monitor.pCategory, Monitor.WARNING_CATEGORY);
            break;

        default:
            setProperty(Monitor.pCategory, Monitor.GOOD_CATEGORY);
            break;
        }
    }

    public boolean isEmsMaufacturer() {
        return true;
    }

    public String verify(StringProperty property, String value, HTTPRequest request, HashMap errors) {
        EmsTimeDiffProperty p = (EmsTimeDiffProperty) getPropertyObject("_emsTimeDiff");
        StringProperty ps = getPropertyObject("_pDbPassword");
        StringProperty user = getPropertyObject("_pDbUserName");
        EmsConfigFileProperty path = (EmsConfigFileProperty) getPropertyObject("_emsConfigFilePath");
        if (property == p) {
            if (p != null) {
                return p.verify(property, value, request, errors);
            } else {
                return "0";
            }
        }
        if (property != null && property == ps || property == user) {
            if (value == null || "null".equals(value) || value.length() == 0) {
                errors.add(property, "You must enter Database user name and password");
            }
            return value;
        }
        if (property != null && property.getName().equals("_emsConfigFilePath")) {
            return ((EmsConfigFileProperty) property).verifyConfigFile(this, value, errors);
        } else {
            return super.verify(property, value, request, errors);
        }
    }

    public boolean runOwnRules() {
        return true;
    }

    public void initialize(HashMap args) {
        super.initialize(args);
//        if (emulator == null) {
//            emulator = MonitorEmulator.createInstance(new Integer(getUniqueInternalId()), this);
//        }
//        JdbcConfiguration cfg = createJdbcConf(args);
//        emulator.init(cfg, isDisabled());
    }

//    private JdbcConfiguration createJdbcConf(HashMap args) {
//        Object obj[] = new Object[5];
//        obj[0] = args.get("_pDbDriverName");
//        obj[1] = args.get("_pDbUrl");
//        obj[2] = args.get("_pDbUserName");
//        obj[3] = args.get("_pDbPassword");
//        obj[4] = EmsMeasurementConfigFileProperty.getMeasurementConfigFilePath("ApplicationRelationshipMappings", (String) args.get("_emsConfigFilePath"));
//        for (int i = 0; i < obj.length; i ++) {
//            obj[i] = obj[i] != null ? obj[i] : ((Object) (new String("")));
//        }
//
//        return new JdbcConfiguration(obj[0].toString(), obj[1].toString(), obj[2].toString(), obj[3].toString(), obj[4].toString(), getTimeDiffValue());
//    }

    public void notifyDelete() {
//        emulator.notifyDelete();
        super.notifyDelete();
    }

    protected void stopMonitor() {
//        emulator.stop();
        super.stopMonitor();
    }

    public void setStartTime(String startTime) {
        setProperty("pStartTime", startTime);
    }

    public void setMonitorStateString(String stateString) {
        setProperty(Monitor.pStateString, stateString);
    }

    public String getHostname() {
        return "Arm";
    }

//    public void setResultSetEnumerator(ResultSetEnumerator rse) {
//        setStartTime(Long.toString(rse.valueAsLong()));
//    }

    protected boolean update() {
        Timestamp start = getStartTime();
//        emulator.update(new JdbcMonitorContext(getUniqueInternalId(), getTopazParent(), new SimpleResultSetEnumerator(start, "ar.A_UPDATETIME")), this);
        return true;
    }

    public void setNumberOfMeasurements(long count) {
        setProperty("pCollected", Long.toString(count));
    }

//    public JdbcMonitor createJdbcMonitor() {
//        return new ArmMonitor();
//    }

    public Array getLogProperties() {
        Array a = super.getLogProperties();
        a.add(getPropertyObject("pCollected"));
        return a;
    }

    static {
        String xmlName = Platform.getRoot() + "/classes/com/dragonflow/topaz/ems/arm/arm.xml";
        StringProperty props[] = StaticInitializer.initialize(xmlName);
        pStatus = new StringProperty("pMStatus");
        Vector vec = new Vector(Arrays.asList(props));
        vec.add(pStatus);
        PropertiedObject.addProperties("com.dragonflow.StandardMonitor.ArmSisMonitor", (StringProperty[]) vec.toArray(props));
        
        String armsisdescription=MonitorTypeValueReader.getValue(ArmSisMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION);
        armsisdescription=armsisdescription.replaceAll("1%", EmsBaseMonitor.MEASUREMENT_TYPE.toLowerCase());
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "description", armsisdescription);
        //PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "description", "Delivers " + EmsBaseMonitor.MEASUREMENT_TYPE.toLowerCase() + "s from " + "Application Relationship Mapping" + " Server(s) to Topaz");
        
        String armsistitle=MonitorTypeValueReader.getValue(ArmSisMonitor.class.getName(), MonitorTypeValueReader.TITLE);
        armsistitle=armsistitle.replaceAll("1%", EmsBaseMonitor.MEASUREMENT_TYPE);
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "title",armsistitle);
        //PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "title", "Application Relationship Mapping " + EmsBaseMonitor.MEASUREMENT_TYPE);
        
        String armsistopazname=MonitorTypeValueReader.getValue(ArmSisMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME);
        armsistopazname=armsistopazname.replaceAll("1%", EmsBaseMonitor.MEASUREMENT_TYPE);
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "topazName", armsistopazname);
        //PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "topazName", "com.dragonflow.StandardMonitor.ArmSisMonitor" + EmsBaseMonitor.MEASUREMENT_TYPE);
        
        handleEmsLicense("com.dragonflow.StandardMonitor.ArmSisMonitor");
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "class", "ArmSisMonitor");
        
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "topazType", MonitorTypeValueReader.getValue(ArmSisMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
        //PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "topazType", "System Resources");
        
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "help", "AppRelMapMonitor.htm");
        
        PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "classType", MonitorTypeValueReader.getValue(ArmSisMonitor.class.getName(), MonitorTypeValueReader.CLASSTYPE));
        //PropertiedObject.setClassProperty("com.dragonflow.StandardMonitor.ArmSisMonitor", "classType", "advanced");
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