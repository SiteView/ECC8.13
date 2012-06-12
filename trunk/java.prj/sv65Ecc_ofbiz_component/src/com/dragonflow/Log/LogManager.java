/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Log;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.ArrayList;
import java.util.List;

import jgl.Array;
import jgl.HashMap;
import jgl.HashMapIterator;

import org.ofbiz.entity.GenericDelegator;
import org.ofbiz.entity.GenericValue;

import com.dragonflow.SiteView.Health;
import com.dragonflow.SiteView.MasterConfig;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.SiteView.SiteViewGroup;
import com.dragonflow.SiteView.SiteViewObject;

// Referenced classes of package com.dragonflow.Log:
// LogThread, ConsoleLogger, DailyFileLogger, FileLogger,
// Logger, JdbcLogger, TopazLogger, SSEELogger

public class LogManager {

    static boolean unittest = false;

    static boolean shutdown = false;

    static HashMap loggers = new HashMap(true);

    static long lastLogTime = 0L;

    static JdbcLogger jdbcLogger = null;

//    static TopazLogger topazLogger = null;

    static SSEELogger sseeLogger = null;

    static HashMap rtConfig;

    static String strLoggers[];

    static LogThread logThread = null;

    public LogManager() {
    }

    public static void initialize(String s, int i, int j, int k, boolean flag, boolean flag1, int l, long l1) {
        logThread = new LogThread();
        logThread.start();
        HashMap hashmap = MasterConfig.getMasterConfig();
        if (flag) {
            ConsoleLogger consolelogger = new ConsoleLogger();
            registerLogger("RunMonitor", consolelogger);
            registerLogger("Error", consolelogger);
            registerLogger("Alert", consolelogger);
            registerLogger("URL", consolelogger);
            registerLogger("SiteViewLog", consolelogger);
            registerLogger("AccountSiteViewLog", consolelogger);
        }
        String s1 = s + java.io.File.separator + "logs" + java.io.File.separator;
        try {
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_createDailyErrorLog").length() > 0) {
                DailyFileLogger dailyfilelogger = new DailyFileLogger(s1 + "error.log", l1, l);
                registerLogger("Error", dailyfilelogger);
            } else {
                FileLogger filelogger = new FileLogger(s1 + "error.log", j, 0);
                registerLogger("Error", filelogger);
            }
        } catch (java.io.IOException ioexception) {
            System.err.println("Could not open error.log");
        }
        try {
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_createDailyRunMonitorLog").length() > 0) {
                DailyFileLogger dailyfilelogger1 = new DailyFileLogger(s1 + "RunMonitor.log", l1, l);
                registerLogger("RunMonitor", dailyfilelogger1);
            } else {
                FileLogger filelogger1 = new FileLogger(s1 + "RunMonitor.log", j, 0);
                registerLogger("RunMonitor", filelogger1);
            }
        } catch (java.io.IOException ioexception1) {
            System.err.println("Could not open text log");
        }
        try {
            FileLogger filelogger2 = new FileLogger(s1 + "Operator.log", j, 0);
            registerLogger("Operator", filelogger2);
        } catch (java.io.IOException ioexception2) {
            System.err.println("Could not open operator log");
        }
        try {
            Object obj = null;
            if (flag1) {
                obj = new DailyFileLogger(s1 + "SiteView.log", l1, l);
            } else {
                obj = new FileLogger(s1 + "SiteView.log", i, k);
            }
            registerLogger("SiteViewLog", ((Logger) (obj)));
        } catch (java.io.IOException ioexception3) {
            System.err.println("Could not open SiteView.log");
        }
        try {
            if (com.dragonflow.Utils.TextUtils.getValue(hashmap, "_createDailyAccessLog").length() > 0) {
                DailyFileLogger dailyfilelogger2 = new DailyFileLogger(s1 + "access.log", l1, l);
                registerLogger("HTTP", dailyfilelogger2);
            } else {
                FileLogger filelogger3 = new FileLogger(s1 + "access.log", j, 0);
                filelogger3.setWriteDate(false);
                registerLogger("HTTP", filelogger3);
            }
        } catch (java.io.IOException ioexception4) {
            System.err.println("Could not open access.log");
        }
        try {
            FileLogger filelogger4 = new FileLogger(s1 + "alert.log", j, 0);
            registerLogger("Alert", filelogger4);
        } catch (java.io.IOException ioexception5) {
            System.err.println("Could not open alert.log");
        }
        try {
            FileLogger filelogger5 = new FileLogger(s1 + "url.log", j, 0);
            registerLogger("URL", filelogger5);
        } catch (java.io.IOException ioexception6) {
            System.err.println("Could not open url.log");
        }
        Object obj1 = null;
        try {
            jgl.Array array = getCustomLoggerClasses();
            obj1 = array;
            for (int i1 = 0; i1 < array.size(); i1 ++) {
                Class<?> class1 = (Class<?>) array.at(i1);
                obj1 = class1;
                Logger logger = (Logger) class1.newInstance();
                String logName = "SiteViewLog";
                if (logger.customLogName().length() > 0) {
                	logName = logger.customLogName();
                }
                registerLogger(logName, logger);
            }

        } catch (Exception exception) {
            System.err.println("Could not open Custom Logger " + obj1 + " exception: " + exception);
        }
    }

    public static long getLastLogTime() {
        return lastLogTime;
    }

    public static void unregisterLogger(String s, Logger logger) {
        java.util.Enumeration enumeration = loggers.values(s.toLowerCase());
        while (enumeration.hasMoreElements()) {
            Logger logger1 = (Logger) enumeration.nextElement();
            if (logger.equals(logger1)) {
                loggers.remove(s.toLowerCase());
            }
        } 
        logThread.removeLogger(logger);
    }

    public static void registerLogger(String logName, Logger logger) {
        boolean flag = false;
        if (strLoggers.length == 0) {
            flag = true;
        } else {
            String s1 = logger.getClass().toString();
            String s2 = s1.substring(s1.lastIndexOf(".") + 1);
            
            for (String strLogger : strLoggers){
            	if (strLogger == null) continue;
            	if (strLogger.equals(logName.toLowerCase() + "=" + s2.toLowerCase())) {
            		flag = true;
            		break;
            	}
            }
        }
        if (flag) {
            loggers.add(logName.toLowerCase(), logger);
            logThread.addLogger(logger);
            if (logName.startsWith("SiteViewLog")) {
                if (jdbcLogger == null && (logger instanceof JdbcLogger)) {
                    jdbcLogger = (JdbcLogger) logger;
                }
                if (!logName.equals("SiteViewLog") && jdbcLogger != null) {
                    loggers.add(logName.toLowerCase(), jdbcLogger);
                }
//                if (topazLogger == null && (logger instanceof TopazLogger)) {
//                    topazLogger = (TopazLogger) logger;
//                }
                if (sseeLogger == null && (logger instanceof SSEELogger)) {
                    sseeLogger = (SSEELogger) logger;
                }
//                if (!s.equals("SiteViewLog") && topazLogger != null) {
//                    loggers.add(s.toLowerCase(), topazLogger);
//                }
            }
        }
    }

    public static void shutdown() {
        shutdown = true;
        for (HashMapIterator hashmapiterator = loggers.begin(); !hashmapiterator.atEnd(); hashmapiterator.advance()) {
            ((Logger) hashmapiterator.value()).close();
        }

        logThread.end();
    }

    public static boolean loggerRegistered(String s) {
        return loggers.get(s.toLowerCase()) != null;
    }

    public static void log(String s) {
        log("", s);
    }

    public static void log(String s, String s1) {
        log(s, s1, Platform.makeDate());
    }

    public static void log(String s, String s1, java.util.Date date) {
        if (unittest || shutdown) {
            System.out.println(s1);
            return;
        }
        s = s.toLowerCase();
        try {
            boolean flag = false;
            java.util.Enumeration enumeration = loggers.values(s);
            while (enumeration.hasMoreElements()) {
                Logger logger = (Logger) enumeration.nextElement();
                logger.log(s, date, s1);
                flag = true;
                if (logger.echoTo.length() > 0) {
                    log(logger.echoTo, s1, date);
                }
            } 
            if (flag) {
                lastLogTime = Platform.timeMillis();
            }
        } catch (Exception exception) {
            System.out.println("LOGERROR: " + exception.toString());
        }
        if (s.equalsIgnoreCase("Error")) {
            com.dragonflow.Health.logEventHealth.log(s1);
        }
    }

    public static void log(com.dragonflow.Properties.PropertiedObject propertiedobject) {
        log("", propertiedobject);
    }

    public static void log(String s, com.dragonflow.Properties.PropertiedObject propertiedobject) {
        log(s, propertiedobject, Platform.makeDate());
    }

    public static void log(String s, com.dragonflow.Properties.PropertiedObject propertiedobject, java.util.Date date) {
        if (unittest || shutdown) {
            return;
        }
        SiteViewGroup siteviewgroup = SiteViewGroup.currentSiteView();
        String s1 = siteviewgroup.getProperty("_healthDisableLogging");
        if (s1.length() > 0 && (propertiedobject instanceof SiteViewObject)) {
            SiteViewObject siteviewobject = ((SiteViewObject) propertiedobject).getOwner();
            if (Health.isInHealth(siteviewobject)) {
                return;
            }
        }
        s = s.toLowerCase();
        boolean flag = false;
        java.util.Enumeration enumeration = loggers.values(s);
        while (enumeration.hasMoreElements()) {
            Logger logger = (Logger) enumeration.nextElement();
            String s2 = logger.getClass().getName();
            int i = s2.lastIndexOf('.');
            if (i > 0) {
                s2 = s2.substring(i + 1);
            }
            propertiedobject.currentStatus = "logging...";
            logger.log(s, date, propertiedobject);
            flag = true;
            if (logger.echoTo.length() > 0) {
                log(logger.echoTo, propertiedobject, date);
            }
        } 
        if (flag) {
            lastLogTime = Platform.timeMillis();
        }
    }

/*    private static jgl.Array getCustomLoggerClasses() {
        jgl.Array array = new Array();
        java.io.File file = new File(Platform.getRoot() + "/classes/CustomLogger/");
        if (!file.exists()) {
            return array;
        }
        String files[] = file.list();
        if (files != null) {
            for (String filename: files) {
                if (!filename.endsWith("Logger.class")) {
                    continue;
                }
                int index = filename.lastIndexOf(".class");
                String className = filename.substring(0, index);
                try {
                    Class<?> class1 = Class.forName("CustomLogger." + className);
                    array.add(class1);
                } catch (Exception exception) {
                    System.out.println("Could not create Custom Logger class " + className + "  " + exception);
                }
            }
        }
        return array;
    }*/
    
    //edit by hailong.yi
    private static jgl.Array getCustomLoggerClasses(){
        jgl.Array array = new Array();
        for (String className: getLoggerClasses()) {
            try {
            	if (className == null) continue;
                Class<?> class1 = Class.forName(className);
                array.add(class1);
            } catch (Exception exception) {
                System.out.println("Could not create Custom Logger class " + className + "  " + exception);
            }
        }
        return array;
    }    
    private static List<String> getLoggerClasses()
    {
        List<String> retlist = new ArrayList<String>();
    	try{
            List<GenericValue> values = getDelegator().findList("SvLoggerType", null, null,null,null,false);
    		for (GenericValue val : values)
    		{
    			retlist.add(val.getString("className"));
    		}
    	}catch (Exception e){
    	}
		return retlist;
    }
    ////////end hailong.yi
    
    
	private static GenericDelegator localdelegator = null;
	private static GenericDelegator getDelegator()
	{
		if (localdelegator == null) localdelegator = GenericDelegator.getGenericDelegator("default");
		return localdelegator;
	}

    public static String getStackTrace(Throwable throwable) {
        StackTraceElement astacktraceelement[] = throwable.getStackTrace();
        StringBuffer stringbuffer = new StringBuffer(throwable.getClass().getName() + "\n");
        for (int i = 0; i < astacktraceelement.length; i ++) {
            StackTraceElement stacktraceelement = astacktraceelement[i];
            stringbuffer.append(stacktraceelement.toString() + "\n");
        }

        return stringbuffer.toString();
    }

    public static void logException(Throwable throwable) {
        log("error", getStackTrace(throwable));
    }

    public static void triggerLogging(Logger logger) {
        logThread.triggerLogging(logger);
    }

    static {
        rtConfig = SiteViewGroup.loadRTConfig();
        strLoggers = com.dragonflow.Utils.TextUtils.split(com.dragonflow.Utils.TextUtils.getValue(rtConfig, "_loggers").toLowerCase(), ";");
        String s = System.getProperty("LogManager.unittest");
        if (s != null && s.length() > 0) {
            unittest = true;
        }
    }
}
