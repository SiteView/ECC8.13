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

import jgl.Array;
import SiteViewMain.ServicePrinter;

// Referenced classes of package COM.dragonflow.Utils:
// CounterLock, RemoteCommandLine, ThreadPool, FileUtils,
// SocketSession, TextUtils

public class CommandLine
{

    public static java.lang.String PERFEX_EXECSYNC_CMD = "-execsync ";
    public static java.lang.String PERFEX_EXECSYNC_TIMEOUT = "ERROR: process timeout";
    public static java.lang.String PERFEX_EXECSYNC_LOGON_FAILURE = "ERROR: Logon failed";
    public int exitValue;
    public long duration;
    long startTime;
    private static boolean showDebug = false;
    static boolean useProcessPool = true;
    static java.lang.Object execLock = new Object();
    public static boolean recording = false;
    public static boolean playback = false;
    public static jgl.Array recorded = null;
    public static long timeout = -1L;

    public CommandLine()
    {
        exitValue = -1;
    }

    public static void main(java.lang.String args[])
    {
    }

    public static java.lang.Process execSync(java.lang.String s)
        throws java.io.IOException
    {
        java.lang.Process process;
        synchronized(execLock)
        {
            process = java.lang.Runtime.getRuntime().exec(s);
        }
        return process;
    }

    public static java.lang.Process execSync(java.lang.String as[])
        throws java.io.IOException
    {
        java.lang.Process process;
        synchronized(execLock)
        {
            process = java.lang.Runtime.getRuntime().exec(as);
        }
        return process;
    }

    protected java.lang.String quoteCommandLineArg(java.lang.String s)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer("\"");
        int i = 0;
        while (true)
        {
            int j = s.indexOf('"', i);
            if(j != -1)
            {
                stringbuffer.append(s.substring(i, j));
                stringbuffer.append("\\\"");
                i = j + 1;
            } else
            {
                stringbuffer.append(s.substring(i));
                stringbuffer.append("\"");
                return stringbuffer.toString();
            }
        }
    }

    public jgl.Array exec(java.util.Vector vector)
    {
        return exec(vector, true);
    }

    public jgl.Array exec(java.util.Vector vector, boolean flag)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.util.Iterator iterator = vector.iterator();
        while (iterator.hasNext())
            {
            java.lang.String s = (java.lang.String)iterator.next();
            if(s != null)
            {
                if(stringbuffer.length() > 0)
                {
                    stringbuffer.append(" ");
                }
                if(flag)
                {
                    stringbuffer.append(quoteCommandLineArg(s));
                } else
                {
                    stringbuffer.append(s);
                }
            }
        } 
        return exec(stringbuffer.toString());
    }

    public jgl.Array exec(java.lang.String s)
    {
        return exec(s, new CounterLock(1));
    }

    public jgl.Array exec(java.lang.String s, java.lang.String s1)
    {
        return exec(s, s1, new CounterLock(1));
    }

    public jgl.Array exec(java.lang.String s, java.lang.String s1, COM.dragonflow.Utils.CounterLock counterlock, COM.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        return exec(s, s1, counterlock, -1, atomicmonitor);
    }

    public jgl.Array exec(java.lang.String s, java.lang.String s1, COM.dragonflow.Utils.CounterLock counterlock)
    {
        return exec(s, s1, counterlock, -1, null);
    }

    public jgl.Array exec(java.lang.String s, java.lang.String s1, COM.dragonflow.Utils.CounterLock counterlock, int i)
    {
        return exec(s, s1, counterlock, i, null);
    }

    public jgl.Array exec(java.lang.String s, java.lang.String s1, COM.dragonflow.Utils.CounterLock counterlock, int i, COM.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String,String,CounterLock) called with command \"" + s + "\"");
        }
        boolean flag = false;
        COM.dragonflow.SiteView.Machine machine = null;
        if(i > 0)
        {
            s = COM.dragonflow.Utils.CommandLine.getExecSyncCmd(s1, s, i, true);
        }
        if(COM.dragonflow.SiteView.Platform.isNTRemote(s1) || COM.dragonflow.SiteView.Machine.isNTSSH(s1))
        {
            machine = COM.dragonflow.SiteView.Machine.getNTMachine(s1);
            if(machine != null && machine.getSetting("_method").equals("ssh"))
            {
                flag = true;
            }
        }
        if(!flag && (s1.length() == 0 || COM.dragonflow.SiteView.Platform.isNTRemote(s1)))
        {
            return exec(s, counterlock, atomicmonitor);
        }
        if(machine == null)
        {
            machine = COM.dragonflow.SiteView.Machine.getMachine(s1);
        }
        if(machine != null)
        {
            COM.dragonflow.Utils.RemoteCommandLine remotecommandline = COM.dragonflow.SiteView.Machine.getRemoteCommandLine(machine);
            if(remotecommandline != null)
            {
                if(playback)
                {
                    return COM.dragonflow.Utils.CommandLine.nextOutput();
                }
                jgl.Array array = remotecommandline.exec(s, machine);
                exitValue = remotecommandline.exitValue;
                if(recording)
                {
                    COM.dragonflow.Utils.CommandLine.recordOutput(array);
                }
                return array;
            }
            COM.dragonflow.Log.LogManager.log("Error", "Unknown Remote Command Line method: " + machine.getProperty(COM.dragonflow.SiteView.Machine.pMethod) + " for machine " + machine.getProperty(COM.dragonflow.SiteView.Machine.pName));
        } else
        {
            COM.dragonflow.Log.LogManager.log("Error", "Could not find machine " + s1 + " to run remote");
        }
        return new Array();
    }

    public jgl.Array exec(java.lang.String s, COM.dragonflow.Utils.CounterLock counterlock)
    {
        return exec(s, counterlock, ((COM.dragonflow.SiteView.AtomicMonitor) (null)));
    }

    public jgl.Array exec(java.lang.String s, COM.dragonflow.Utils.CounterLock counterlock, COM.dragonflow.SiteView.AtomicMonitor atomicmonitor)
    {
        if(timeout > 0L)
        {
            return exec1(null, s, counterlock);
        }
        if(playback)
        {
            return COM.dragonflow.Utils.CommandLine.nextOutput();
        }
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String,CounterLock) called with command \"" + s + "\"");
        }
        if(s.startsWith("http://"))
        {
            return runHTTPCommand(s);
        }
        jgl.Array array = new Array();
        startTime = java.lang.System.currentTimeMillis();
        if(showDebug)
        {
            java.lang.System.out.println("EXEC calling runtime exec");
        }
        boolean flag = false;
        java.lang.Process process = null;
        java.io.BufferedReader bufferedreader = null;
        if(useProcessPool && s.indexOf("webtrace") == -1)
        {
            int ai[] = new int[1];
            try
            {
                flag = COM.dragonflow.ProcessUtils.ProcessMgr.exec(s, array, ai, atomicmonitor);
            }
            catch(java.io.IOException ioexception)
            {
                COM.dragonflow.Log.LogManager.log("Error", "ProcessPool: Failed to execute: " + s + " exception: " + ioexception.getMessage());
            }
            if(flag)
            {
                exitValue = ai[0];
            }
        }
        if(!flag)
        {
            try
            {
                counterlock.get();
                process = COM.dragonflow.Utils.CommandLine.execSync(s);
                if(showDebug)
                {
                    java.lang.System.out.println("EXEC runtime exec returned");
                }
                if(s.indexOf("webtrace") == -1)
                {
                    COM.dragonflow.Utils.ThreadPool.SingleThread singlethread = SiteViewMain.ServicePrinter.servicePrinterThreadPool.getThread();
                    SiteViewMain.ServicePrinter serviceprinter = new ServicePrinter();
                    serviceprinter.printing = showDebug;
                    serviceprinter.stream = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getErrorStream());
                    singlethread.activate(serviceprinter);
                    bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
                } else
                {
                    bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getErrorStream());
                }
                while(true)
                {
                    java.lang.String s1 = bufferedreader.readLine();
                    if(s1 == null)
                    {
                        break;
                    }
                    array.add(s1);
                } 
                if(showDebug)
                {
                    java.lang.System.out.println("EXEC calling waitFor");
                }
                exitValue = process.waitFor();
                if(showDebug)
                {
                    java.lang.System.out.println("EXEC waitFor returned");
                }
            }
            catch(java.lang.Exception exception)
            {
                if(showDebug)
                {
                    java.lang.System.out.println("*** exec Exception");
                    java.lang.System.out.println("  cmd:" + s);
                    java.lang.System.out.println(" exit:" + exitValue);
                    java.lang.System.out.println("lines:" + array.size());
                    java.lang.System.out.println("error:" + exception.toString());
                }
            }
            finally
            {
                if(process != null)
                {
                    process.destroy();
                }
                process = null;
                try
                {
                    if(bufferedreader != null)
                    {
                        bufferedreader.close();
                    }
                }
                catch(java.io.IOException ioexception1)
                {
                    COM.dragonflow.Log.LogManager.log("Error", "Failed to close the BufferedReader, exception " + ioexception1.getMessage());
                }
                counterlock.release();
            }
        }
        duration = java.lang.System.currentTimeMillis() - startTime;
        if(showDebug)
        {
            java.lang.System.out.println("*** exec");
            java.lang.System.out.println("  cmd:" + s);
            java.lang.System.out.println(" exit:" + exitValue);
            java.lang.System.out.println("lines:" + array.size());
            java.lang.System.out.println(" time:" + duration + "ms");
        }
        if(recording)
        {
            COM.dragonflow.Utils.CommandLine.recordOutput(array);
        }
        return array;
    }

    public jgl.Array exec(java.lang.String as[], java.lang.String s)
    {
        return exec(as, s, new CounterLock(1));
    }

    public jgl.Array exec(java.lang.String as[], java.lang.String s, COM.dragonflow.Utils.CounterLock counterlock)
    {
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String[],String,CounterLock) called with command \"" + as + "\"");
        }
        if(s.length() == 0 || COM.dragonflow.SiteView.Platform.isNTRemote(s))
        {
            return exec(as, counterlock);
        }
        COM.dragonflow.SiteView.Machine machine = COM.dragonflow.SiteView.Machine.getMachine(s);
        if(machine != null)
        {
            COM.dragonflow.Utils.RemoteCommandLine remotecommandline = COM.dragonflow.SiteView.Machine.getRemoteCommandLine(machine);
            if(remotecommandline != null)
            {
                if(playback)
                {
                    return COM.dragonflow.Utils.CommandLine.nextOutput();
                }
                jgl.Array array = remotecommandline.exec(as, machine);
                exitValue = remotecommandline.exitValue;
                if(recording)
                {
                    COM.dragonflow.Utils.CommandLine.recordOutput(array);
                }
                return array;
            }
            COM.dragonflow.Log.LogManager.log("Error", "Unknown Remote Command Line method: " + machine.getProperty(COM.dragonflow.SiteView.Machine.pMethod) + " for machine " + machine.getProperty(COM.dragonflow.SiteView.Machine.pName));
        } else
        {
            COM.dragonflow.Log.LogManager.log("Error", "Could not find machine " + s + " to run remote");
        }
        return new Array();
    }

    public jgl.Array exec(java.lang.String as[])
    {
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String[]) called with command \"" + as + "\"");
        }
        return exec(as, new CounterLock(1));
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param as
     * @param counterlock
     * @return
     */
    public jgl.Array exec(java.lang.String as[], COM.dragonflow.Utils.CounterLock counterlock)
    {
        jgl.Array array;
        java.lang.Process process;
        if(timeout > 0L)
        {
            return exec1(as, null, counterlock);
        }
        if(playback)
        {
            return COM.dragonflow.Utils.CommandLine.nextOutput();
        }
        array = new Array();
        process = null;
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String[],CounterLock) called with command \"" + as + "\"");
            for(int i = 0; i < as.length; i++)
            {
                java.lang.System.out.println(i + " [" + as[i] + "]");
            }

        }
        
        try {
        counterlock.get();
        startTime = java.lang.System.currentTimeMillis();
        if(showDebug)
        {
            java.lang.System.out.println("EXEC calling Runtime");
        }
        process = COM.dragonflow.Utils.CommandLine.execSync(as);
        if(showDebug)
        {
            java.lang.System.out.println("EXEC Runtime returned");
        }
        COM.dragonflow.Utils.ThreadPool.SingleThread singlethread = SiteViewMain.ServicePrinter.servicePrinterThreadPool.getThread();
        SiteViewMain.ServicePrinter serviceprinter = new ServicePrinter();
        serviceprinter.printing = showDebug;
        serviceprinter.stream = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getErrorStream());
        singlethread.activate(serviceprinter);
        java.io.BufferedReader bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
        while (true)
        {
            java.lang.String s = bufferedreader.readLine();
            if(showDebug)
            {
                java.lang.System.out.println("*** line (" + s + ")");
            }
            if(s == null)
            {
                break;
            }
            array.add(s);
        } 
        
        if(showDebug)
        {
            java.lang.System.out.println("EXEC calling waitFor");
        }
        exitValue = process.waitFor();
        if(showDebug)
        {
            java.lang.System.out.println("EXEC waitFor returned");
        }
        process = null;
        duration = java.lang.System.currentTimeMillis() - startTime;
        counterlock.release();
        }
        catch (RuntimeException exception1) {
            counterlock.release();
            throw exception1;
        }
        catch (java.lang.Exception exception) {
        if(showDebug)
        {
            java.lang.System.out.println("*** exec: " + as + ", exit: " + exitValue + ", lines: " + array.size() + ", error: " + exception);
        }
        counterlock.release();
        }
    
        if(process != null)
        {
            process.destroy();
        }
        if(showDebug)
        {
            java.lang.System.out.println("**** exec: " + as + ", exit: " + exitValue + ", lines: " + array.size());
        }
        if(recording)
        {
            COM.dragonflow.Utils.CommandLine.recordOutput(array);
        }
        return array;
    }

    public int getExitValue()
    {
        return exitValue;
    }

    public jgl.Array runHTTPCommand(java.lang.String s)
    {
        return COM.dragonflow.Utils.CommandLine.runHTTPCommand(s, "", "", "", "", "", "", this);
    }

    public static jgl.Array runHTTPCommand(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5, java.lang.String s6, COM.dragonflow.Utils.CommandLine commandline)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        COM.dragonflow.Utils.SocketSession socketsession = COM.dragonflow.Utils.SocketSession.getSession(null);
        COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        long l = siteviewgroup.getSettingAsLong("urlContentMatchMax", 51200);
        int i = COM.dragonflow.Utils.TextUtils.toInt(s6) * 1000;
        if(i <= 0)
        {
            i = COM.dragonflow.StandardMonitor.URLMonitor.DEFAULT_TIMEOUT;
        }
        long al[] = COM.dragonflow.StandardMonitor.URLMonitor.checkURL(socketsession, s, "", "", s3, s4, s5, null, s1, s2, "", stringbuffer, l, "", 0, i, null);
        long l1 = al[0];
        socketsession.close();
        if(l1 != 200L)
        {
            COM.dragonflow.Log.LogManager.log("Error", "HTTP CommandLine Error: " + l1);
            COM.dragonflow.Log.LogManager.log("Error", "URL was: " + s);
            COM.dragonflow.Log.LogManager.log("Error", "Content was:\n" + stringbuffer);
        }
        if(commandline != null)
        {
            commandline.exitValue = (int)l1;
            if(commandline.exitValue == COM.dragonflow.StandardMonitor.URLMonitor.kURLok)
            {
                commandline.exitValue = 0;
            }
            commandline.duration = al[1];
        }
        int j = -1;
        byte byte0 = -1;
        java.lang.String s7 = COM.dragonflow.StandardMonitor.URLMonitor.getHTTPContent(stringbuffer.toString());
        jgl.Array array = new Array();
        boolean flag = false;
            int k;
            while ((k = s7.indexOf("\n", j + 1)) >= 0)
            {
            java.lang.String s8 = s7.substring(j + 1, k);
            j = k;
            if(!flag && s8.startsWith("<PRE>"))
            {
                flag = true;
                continue;
            }
            if(flag && s8.startsWith("</PRE>"))
            {
                flag = false;
                break;
            }
            if(flag)
            {
                array.add(s8);
            }
        } 
        return array;
    }

    public static void startRecording()
    {
        recorded = new Array();
        recording = true;
    }

    public static void recordOutput(jgl.Array array)
    {
        if(recording)
        {
            recorded.add(array);
        }
    }

    public static void stopRecording()
    {
        recording = false;
    }

    public static void startPlayback()
    {
        COM.dragonflow.Utils.CommandLine.stopRecording();
        playback = true;
    }

    public static jgl.Array nextOutput()
    {
        jgl.Array array;
        if(recorded.size() >= 1)
        {
            array = (jgl.Array)recorded.popFront();
        } else
        {
            array = new Array();
            array.add("*** no more output to play back ***");
        }
        return array;
    }

    public static void stopPlayback()
    {
        playback = false;
        recorded = null;
    }

    static java.lang.String arrayToString(jgl.Array array)
    {
        java.lang.String s = "";
        for(int i = 0; i < array.size(); i++)
        {
            s = s + array.at(i);
            s = s + "\n";
        }

        return s;
    }

    boolean parseInput(char c, java.lang.StringBuffer stringbuffer)
    {
        if(c == '\n')
        {
            return true;
        }
        if(c != '\r')
        {
            stringbuffer.append(c);
        }
        return false;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param as
     * @param s
     * @param counterlock
     * @return
     */
    jgl.Array exec1(java.lang.String as[], java.lang.String s, COM.dragonflow.Utils.CounterLock counterlock)
    {
        byte byte0;
        java.lang.StringBuffer stringbuffer;
        jgl.Array array;
        java.lang.Process process;
        byte0 = 2;
        if(playback)
        {
            return COM.dragonflow.Utils.CommandLine.nextOutput();
        }
        stringbuffer = new StringBuffer("");
        if(s != null)
        {
            stringbuffer.append(s);
        } else
        {
            for(int i = 0; i < as.length; i++)
            {
                stringbuffer.append(i + " [" + as[i] + "],");
            }

        }
        array = new Array();
        process = null;
        if(showDebug)
        {
            java.lang.System.out.println("EXEC (String,CounterLock) called with command: \"" + stringbuffer.toString() + "\"");
        }
        
        try {
        counterlock.get();
        for(int j = 0; j < byte0; j++)
        {
            startTime = java.lang.System.currentTimeMillis();
            long l = startTime + timeout;
            if(showDebug)
            {
                java.lang.System.out.println("EXEC calling Runtime, loopCnt=" + j);
            }
            if(s != null)
            {
                process = COM.dragonflow.Utils.CommandLine.execSync(s);
            } else
            {
                process = COM.dragonflow.Utils.CommandLine.execSync(as);
            }
            if(showDebug)
            {
                java.lang.System.out.println("EXEC Runtime returned");
            }
            java.io.BufferedReader bufferedreader = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getInputStream());
            java.io.BufferedReader bufferedreader1 = COM.dragonflow.Utils.FileUtils.MakeInputReader(process.getErrorStream());
            java.lang.StringBuffer stringbuffer2 = new StringBuffer("");
            java.lang.StringBuffer stringbuffer3 = new StringBuffer("");
            boolean flag = false;
            int k = 0;
            while (!flag)
                {
                try
                {
                    while (bufferedreader.ready())
                        {
                        if(parseInput((char)bufferedreader.read(), stringbuffer3))
                        {
                            array.add(stringbuffer3.toString());
                            stringbuffer3.setLength(0);
                            l = java.lang.System.currentTimeMillis() + timeout;
                        }
                    } 
                    
                    while (bufferedreader1.ready()) {
                        stringbuffer2.append((char)bufferedreader1.read());
                    }
                    
                    exitValue = process.exitValue();
                    flag = true;
                    j = byte0;
                    while (bufferedreader.ready())
                        {
                        if(parseInput((char)bufferedreader.read(), stringbuffer3))
                        {
                            array.add(stringbuffer3.toString());
                            stringbuffer3.setLength(0);
                        }
                    } 
                    
                    while (bufferedreader1.ready()) {
                        stringbuffer2.append((char)bufferedreader1.read());
                    }
                    if(stringbuffer3.length() > 0)
                    {
                        array.add(stringbuffer3.toString());
                        stringbuffer3.setLength(0);
                    }
                }
                catch(java.lang.IllegalThreadStateException illegalthreadstateexception)
                {
                    if(java.lang.System.currentTimeMillis() >= l)
                    {
                        process.destroy();
                        flag = true;
                        java.lang.StringBuffer stringbuffer5 = new StringBuffer("***** exec: Process destroyed, cmd:" + stringbuffer.toString());
                        COM.dragonflow.Log.LogManager.log("Error", stringbuffer5.toString());
                        if(showDebug)
                        {
                            java.lang.System.out.println(stringbuffer5.toString());
                        }
                    } else
                    {
                        COM.dragonflow.SiteView.Platform.sleep(k >= 10 ? '\u01F4' : 150);
                        k++;
                    }
                }
            } 
            
            if(showDebug)
            {
                java.lang.System.out.println("***** exec # lines=" + array.size() + ", err.length()=" + stringbuffer2.length());
            }
            if(stringbuffer2.length() <= 0)
            {
                continue;
            }
            java.lang.StringBuffer stringbuffer4 = new StringBuffer("***** exec: errorBuffer=" + stringbuffer2.toString() + ", cmd:" + stringbuffer.toString());
            COM.dragonflow.Log.LogManager.log("Error", stringbuffer4.toString());
            if(showDebug)
            {
                java.lang.System.out.println(stringbuffer4.toString());
            }
        }

        process = null;
        duration = java.lang.System.currentTimeMillis() - startTime;
        counterlock.release();
        }
        catch (RuntimeException exception1) {
            counterlock.release();
            throw exception1;
            }
        catch (java.lang.Exception exception) {
        java.lang.StringBuffer stringbuffer1 = new StringBuffer("***** exec: Exception:" + exception.toString() + ", cmd:" + stringbuffer.toString());
        COM.dragonflow.Log.LogManager.log("Error", stringbuffer1.toString());
        if(showDebug)
        {
            java.lang.System.out.println(stringbuffer1.toString());
            java.lang.System.out.println(" exit:" + exitValue);
            java.lang.System.out.println("lines:" + array.size());
            java.lang.System.out.println("error:" + exception.toString());
        }
        counterlock.release();
        }
        
        if(process != null)
        {
            process.destroy();
        }
        if(showDebug)
        {
            java.lang.System.out.println("*** exec cmd:" + stringbuffer.toString());
            java.lang.System.out.println(" exit:" + exitValue);
            java.lang.System.out.println("lines:" + array.size());
            java.lang.System.out.println(" time:" + duration + "ms");
        }
        if(recording)
        {
            COM.dragonflow.Utils.CommandLine.recordOutput(array);
        }
        return array;
    }

    public static java.lang.String getExecSyncCmd(java.lang.String s, java.lang.String s1, int i, boolean flag)
    {
        return COM.dragonflow.Utils.CommandLine.getExecSyncCmd(s, s1, i, flag, "", "", "", "", false);
    }

    public static java.lang.String getExecSyncCmd(java.lang.String s, java.lang.String s1, int i, boolean flag, java.lang.String s2)
    {
        return COM.dragonflow.Utils.CommandLine.getExecSyncCmd(s, s1, i, flag, s2, "", "", "", false);
    }

    public static java.lang.String getExecSyncCmd(java.lang.String s, java.lang.String s1, int i, boolean flag, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5, 
            boolean flag1)
    {
        boolean flag2 = false;
        if(COM.dragonflow.SiteView.Platform.isWindows())
        {
            if(s == null || s.length() == 0)
            {
                flag2 = true;
            } else
            {
                COM.dragonflow.SiteView.Machine machine = null;
                Object obj = null;
                machine = COM.dragonflow.SiteView.Machine.getNTMachine(s);
                if(machine != null)
                {
                    java.lang.String s7 = machine.getSetting("_method");
                    if(s7.equals("") || s7.equalsIgnoreCase("NetBIOS"))
                    {
                        flag2 = true;
                    }
                }
            }
        }
        if(!flag2)
        {
            return s1;
        }
        java.lang.String s6 = " 0 ";
        if(flag)
        {
            s6 = " 1 ";
        }
        if(s2 == null || s2.length() == 0)
        {
            s2 = "default";
        }
        java.lang.String s8 = "";
        if(s3.length() > 0)
        {
            s8 = s8 + " -u " + s3;
        }
        if(s5.length() > 0)
        {
            s8 = s8 + " -p " + s5;
        }
        if(s4.length() > 0)
        {
            s8 = s8 + " -do " + s4;
        }
        if(COM.dragonflow.SiteView.Platform.isWindows())
        {
            s1 = COM.dragonflow.Utils.TextUtils.replaceChar(s1, '"', "\\\"");
            return COM.dragonflow.SiteView.Platform.perfexCommand(s) + PERFEX_EXECSYNC_CMD + "\"" + s1 + "\" " + i + s6 + s2 + (flag1 ? " 1" : " 0") + s8;
        } else
        {
            return s1;
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param i
     * @return
     */
    public static java.lang.Process killProcessesByName(java.lang.String s, int i)
    {
        try {
        if(COM.dragonflow.SiteView.Platform.isWindows())
        {
        return COM.dragonflow.Utils.CommandLine.execSync(COM.dragonflow.Utils.CommandLine.getExecSyncCmd("", COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "tools" + java.io.File.separator + "kill " + s, i, true));
        }
        }
        catch (java.io.IOException ioexception) {
        ioexception.printStackTrace();
        }
        return null;
    }

    static 
    {
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s = COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_processPool");
        if(s.length() > 0 && s.equals("false"))
        {
            useProcessPool = false;
        }
        showDebug = java.lang.System.getProperty("CommandLine.debug") != null;
    }
}
