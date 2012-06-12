 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package COM.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

import java.io.ByteArrayOutputStream;
import java.io.RandomAccessFile;
import java.util.Date;

import COM.dragonflow.Log.ConsoleErrorLogger;
import COM.dragonflow.Log.FileLogger;
import COM.dragonflow.Properties.FindObjectsOfClassVisitor;

// Referenced classes of package COM.dragonflow.Utils:
// TextUtils, FileUtils, ThreadLister

public class DebugWatcher
    implements java.lang.Runnable
{

    public static COM.dragonflow.Utils.DebugWatcher debugWatcher = null;
    long printInterval;
    boolean periodicChecks;

    public static void initializeDebugWatcher(java.lang.String s, boolean flag, boolean flag1)
    {
        if(flag)
        {
            COM.dragonflow.Log.ConsoleErrorLogger consoleerrorlogger = new ConsoleErrorLogger();
            COM.dragonflow.Log.LogManager.registerLogger("Debug", consoleerrorlogger);
        }
        try
        {
            COM.dragonflow.Log.LogManager.registerLogger("Debug", new FileLogger(s + java.io.File.separator + "logs" + java.io.File.separator + "debug.log", 0xf4240));
        }
        catch(java.io.IOException ioexception)
        {
            java.lang.System.err.println("Could not open debug log file");
        }
        if(flag1)
        {
            debugWatcher = new DebugWatcher();
        }
    }

    DebugWatcher()
    {
        printInterval = 60000L;
        periodicChecks = true;
        java.lang.Thread thread = new Thread(this);
        thread.setName("Debug Watcher");
        thread.setPriority(7);
        thread.setDaemon(true);
        thread.start();
    }

    public void run()
    {
        do
        {
            do
            {
                COM.dragonflow.SiteView.Platform.sleep(printInterval);
            } while(!periodicChecks);
            runChecks();
        } while(true);
    }

    public void runChecks()
    {
        COM.dragonflow.Utils.DebugWatcher.checkScheduler();
        COM.dragonflow.Utils.DebugWatcher.checkMonitors();
        COM.dragonflow.Utils.DebugWatcher.checkThreads();
    }

    public static java.lang.String checkMonitors()
    {
        if(COM.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView != null)
        {
            COM.dragonflow.Properties.FindObjectsOfClassVisitor findobjectsofclassvisitor = new FindObjectsOfClassVisitor("COM.dragonflow.SiteView.AtomicMonitor");
            COM.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.acceptVisitor(findobjectsofclassvisitor);
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            stringbuffer.append("------- Monitors -------\n");
            int i = 0;
            for(java.util.Enumeration enumeration = findobjectsofclassvisitor.getResults().elements(); enumeration.hasMoreElements(); stringbuffer.append("\n"))
            {
                COM.dragonflow.SiteView.AtomicMonitor atomicmonitor = (COM.dragonflow.SiteView.AtomicMonitor)enumeration.nextElement();
                i++;
                stringbuffer.append(atomicmonitor.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pRunning));
                stringbuffer.append("  ");
                COM.dragonflow.Utils.TextUtils.appendStringRightJustify(stringbuffer, atomicmonitor.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pFrequency), 6);
                stringbuffer.append("  ");
                long l = 0L;
                try
                {
                    l = java.lang.Long.parseLong(atomicmonitor.getProperty(COM.dragonflow.SiteView.AtomicMonitor.pLastUpdate));
                }
                catch(java.lang.NumberFormatException numberformatexception) { }
                if(l > 0L)
                {
                    stringbuffer.append(COM.dragonflow.Utils.TextUtils.dateToString(new Date(l)));
                } else
                {
                    stringbuffer.append("    no sample    ");
                }
                stringbuffer.append("  ");
                stringbuffer.append(atomicmonitor.getProperty(COM.dragonflow.SiteView.Monitor.pName));
            }

            stringbuffer.append("===  " + i + " monitors\n");
            java.lang.String s = stringbuffer.toString();
            COM.dragonflow.Log.LogManager.log("Debug", s);
            return s;
        } else
        {
            return "no SiteViewGroup object";
        }
    }

    public static java.lang.String checkThreads()
    {
        java.lang.String s = "";
        try
        {
            java.io.ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
            java.io.PrintWriter printwriter = COM.dragonflow.Utils.FileUtils.MakeOutputWriter(bytearrayoutputstream);
            COM.dragonflow.Utils.ThreadLister.listAllThreads(printwriter);
            printwriter.flush();
            bytearrayoutputstream.flush();
            s = bytearrayoutputstream.toString();
            COM.dragonflow.Log.LogManager.log("Debug", s);
        }
        catch(java.lang.Exception exception)
        {
            s = exception.toString();
        }
        return s;
    }

    public static java.lang.String checkScheduler()
    {
        return COM.dragonflow.Utils.DebugWatcher.checkScheduler("all");
    }

    public static java.lang.String checkScheduler(java.lang.String s)
    {
        java.lang.String s1 = "";
        java.lang.Object obj = COM.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.monitorScheduler;
        if(obj != null && (s.equals("all") || s.equalsIgnoreCase("monitorScheduler")))
        {
            java.lang.String s2 = ((COM.dragonflow.SiteView.Scheduler) (obj)).internalState();
            s1 = s1 + s2;
            COM.dragonflow.Log.LogManager.log("Debug", s2);
        }
        obj = COM.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.maintenanceScheduler;
        if(obj != null && (s.equals("all") || s.equalsIgnoreCase("maintenanceScheduler")))
        {
            java.lang.String s3 = ((COM.dragonflow.SiteView.Scheduler) (obj)).internalState();
            s1 = s1 + s3;
            COM.dragonflow.Log.LogManager.log("Debug", s3);
        }
        obj = COM.dragonflow.SiteView.SiteViewGroup.cCurrentSiteView.reportScheduler;
        if(obj != null && (s.equals("all") || s.equalsIgnoreCase("reportScheduler")))
        {
            java.lang.String s4 = ((COM.dragonflow.SiteView.Scheduler) (obj)).internalState();
            s1 = s1 + s4;
            COM.dragonflow.Log.LogManager.log("Debug", s4);
        }
        obj = COM.dragonflow.SiteView.Action.retryScheduler;
        if(obj != null && (s.equals("all") || s.equalsIgnoreCase("retryScheduler")))
        {
            java.lang.String s5 = ((COM.dragonflow.SiteView.Scheduler) (obj)).internalState();
            s1 = s1 + s5;
            COM.dragonflow.Log.LogManager.log("Debug", s5);
        }
        return s1;
    }

    public static java.lang.String lastLogLines()
    {
        java.lang.String s = COM.dragonflow.SiteView.Platform.getRoot() + "/logs/RunMonitor.log";
        Object obj = null;
        java.lang.String s1 = "Could not access " + s;
        try
        {
            java.lang.StringBuffer stringbuffer = new StringBuffer();
            java.io.RandomAccessFile randomaccessfile = new RandomAccessFile(s, "r");
            long l = randomaccessfile.length() - 8000L;
            if(l < 0L)
            {
                l = 0L;
            }
            for(java.lang.String s2 = randomaccessfile.readLine(); (s2 = randomaccessfile.readLine()) != null;)
            {
                stringbuffer.append(s2);
                stringbuffer.append("\n");
            }

            randomaccessfile.close();
            s1 = stringbuffer.toString();
        }
        catch(java.io.IOException ioexception) { }
        return s1;
    }

    public static void main(java.lang.String args[])
        throws java.io.IOException
    {
        java.io.PrintWriter printwriter = COM.dragonflow.Utils.FileUtils.MakeOutputWriter(java.lang.System.out);
        COM.dragonflow.Utils.ThreadLister.listAllThreads(printwriter);
        printwriter.flush();
    }

}
