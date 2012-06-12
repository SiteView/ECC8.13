 /*
  * Created on 2005-2-9 3:06:20
  *
  * .java
  *
  * History:
  *
  */
  package com.dragonflow.Utils;

 /**
     * Comment for <code></code>
     * 
     * @author
     * @version 0.0
     * 
     * 
     */

import java.io.BufferedInputStream;

import jgl.Array;
import com.dragonflow.SiteView.Machine;

// Referenced classes of package com.dragonflow.Utils:
// RemoteCommandLine, TextUtils, FileUtils

public class RloginCommandLine extends com.dragonflow.Utils.RemoteCommandLine
{

    public static boolean debug = false;

    public RloginCommandLine()
    {
    }

    public java.lang.String getMethodName()
    {
        return "rlogin";
    }

    public java.lang.String getMethodDisplayName()
    {
        return "rlogin";
    }

    public jgl.Array exec(java.lang.String s, com.dragonflow.SiteView.Machine machine, boolean flag)
    {
        super.exec(s, machine, flag);
        long l = com.dragonflow.Properties.StringProperty.toLong(machine.getProperty(com.dragonflow.SiteView.Machine.pTimeout));
        if(l == 0L)
        {
            l = 60000L;
        } else
        {
            l *= 1000L;
        }
        java.net.Socket socket = null;
        Object obj = null;
        java.io.PrintWriter printwriter = null;
        java.io.BufferedInputStream bufferedinputstream = null;
        java.lang.String s1 = machine.getProperty(com.dragonflow.SiteView.Machine.pHost);
        int i = 513;
        int j = s1.indexOf(':');
        if(j != -1)
        {
            i = com.dragonflow.Utils.TextUtils.readInteger(s1, j + 1);
            s1 = s1.substring(0, j);
        }
        java.lang.String s2 = machine.getProperty(com.dragonflow.SiteView.Machine.pLogin);
        java.lang.String s3 = machine.getProperty(com.dragonflow.SiteView.Machine.pPassword);
        java.lang.String s4 = machine.getProperty(com.dragonflow.SiteView.Machine.pLocalUser);
        java.lang.String s5 = machine.getProperty(com.dragonflow.SiteView.Machine.pPasswordPrompt);
        java.lang.String s6 = machine.getProperty(com.dragonflow.SiteView.Machine.pPrompt);
        java.lang.String s7 = "";
        java.lang.String s8 = "tty/9600";
        int k = com.dragonflow.StandardMonitor.URLMonitor.kURLok;
        byte abyte0[] = new byte[s2.length() + s4.length() + s8.length() + 4];
        int i1 = 0;
        abyte0[i1++] = 0;
        for(int j1 = 0; j1 < s4.length(); j1++)
        {
            abyte0[i1++] = (byte)s4.charAt(j1);
        }

        abyte0[i1++] = 0;
        for(int k1 = 0; k1 < s2.length(); k1++)
        {
            abyte0[i1++] = (byte)s2.charAt(k1);
        }

        abyte0[i1++] = 0;
        for(int l1 = 0; l1 < s8.length(); l1++)
        {
            abyte0[i1++] = (byte)s8.charAt(l1);
        }

        abyte0[i1++] = 0;
        traceMessage(s2 + "," + s4 + "," + s8, machine, TO_REMOTE);
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        progressMessage("Connecting to " + s1 + "...");
        try
        {
            socket = com.dragonflow.Utils.RloginCommandLine.getReservedPort(s1, i);
            progressMessage("Logging In...");
            java.io.OutputStream outputstream = socket.getOutputStream();
            outputstream.write(abyte0);
            outputstream.flush();
            printwriter = com.dragonflow.Utils.FileUtils.MakeOutputWriter(outputstream, "Cp1252");
            bufferedinputstream = new BufferedInputStream(socket.getInputStream());
            long l2 = com.dragonflow.SiteView.Platform.timeMillis() + l * 1000L;
            int j2 = 0;
            boolean flag1 = false;
            boolean flag2 = false;
            do
            {
                if(j2 == -1)
                {
                    break;
                }
                j2 = readChar(bufferedinputstream, socket, l2);
                if(j2 == 65535)
                {
                    for(int k2 = 0; k2 < 11; k2++)
                    {
                        j2 = readChar(bufferedinputstream, socket, l2);
                    }

                    byte abyte1[] = new byte[12];
                    abyte1[0] = -1;
                    abyte1[1] = -1;
                    abyte1[2] = 115;
                    abyte1[3] = 115;
                    abyte1[4] = 0;
                    abyte1[5] = 24;
                    abyte1[6] = 0;
                    abyte1[7] = 80;
                    abyte1[8] = 4;
                    abyte1[9] = 0;
                    abyte1[10] = 4;
                    abyte1[11] = 0;
                    outputstream.write(abyte1);
                    outputstream.flush();
                    continue;
                }
                if(j2 == -1)
                {
                    continue;
                }
                stringbuffer.append(j2);
                java.lang.String s10 = toEncoding(stringbuffer.toString());
                if(detail && progressStream != null)
                {
                    progressStream.print(j2);
                }
                if(s7.length() > 0 && s10.endsWith(s7))
                {
                    progressMessage("Login Failed");
                    k = 401;
                    break;
                }
                if(!flag2 && stringbuffer.length() < 15)
                {
                    if(s10.endsWith(s5))
                    {
                        traceMessage("Password: " + com.dragonflow.Utils.TextUtils.filledString('*', s3.length()), machine, TO_REMOTE);
                        progressMessage("Sending Password...");
                        printwriter.print(s3 + '\n');
                        printwriter.flush();
                        stringbuffer = new StringBuffer();
                        s7 = machine.getProperty("_loginIncorrectPrompt");
                        if(s7.length() == 0)
                        {
                            s7 = "ogin incorrect";
                        }
                    }
                    continue;
                }
                if(!s10.endsWith(s6))
                {
                    continue;
                }
                if(flag1)
                {
                    progressMessage("Command completed...");
                    break;
                }
                progressMessage("Running command...");
                traceMessage(s, machine, TO_REMOTE);
                printwriter.print(s + '\n');
                printwriter.flush();
                stringbuffer = new StringBuffer();
                resetBuffer();
                flag1 = true;
                flag2 = true;
                s7 = "";
            } while(true);
        }
        catch(java.net.UnknownHostException unknownhostexception)
        {
            k = com.dragonflow.StandardMonitor.URLMonitor.kURLBadHostNameError;
        }
        catch(java.net.SocketException socketexception)
        {
            if(com.dragonflow.SiteView.Platform.noRoute(socketexception))
            {
                k = com.dragonflow.StandardMonitor.URLMonitor.kURLNoRouteToHostError;
            } else
            {
                k = com.dragonflow.StandardMonitor.URLMonitor.kURLNoConnectionError;
            }
        }
        catch(java.io.InterruptedIOException interruptedioexception)
        {
            k = com.dragonflow.StandardMonitor.URLMonitor.kURLTimeoutError;
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            java.lang.System.err.println(exception + " error: " + exception.getMessage());
            k = com.dragonflow.StandardMonitor.URLMonitor.kURLUnknownError;
        }
        finally
        {
            try
            {
                if(printwriter != null)
                {
                    printwriter.close();
                }
                if(bufferedinputstream != null)
                {
                    bufferedinputstream.close();
                }
                if(socket != null)
                {
                    socket.close();
                }
            }
            catch(java.io.IOException ioexception)
            {
                java.lang.System.err.println("Could not close FTP streams");
            }
        }
        jgl.Array array = null;
        if(k == com.dragonflow.StandardMonitor.URLMonitor.kURLok)
        {
            array = com.dragonflow.SiteView.Platform.split('\n', toEncoding(stringbuffer.toString()));
            if(!flag)
            {
                if(array.size() > 0)
                {
                    array.popFront();
                }
                int i2 = com.dragonflow.SiteView.Machine.stringToOS(machine.getProperty(com.dragonflow.SiteView.Machine.pOS));
                if((com.dragonflow.SiteView.Platform.isSGI(i2) || com.dragonflow.SiteView.Platform.isSolaris(i2)) && array.size() > 0)
                {
                    java.lang.String s9 = (java.lang.String)array.at(0);
                    if(s9.trim().length() == 0)
                    {
                        array.popFront();
                    }
                }
                if(array.size() > 0)
                {
                    array.popBack();
                }
            }
            traceMessage(array, machine, FROM_REMOTE);
        } else
        {
            progressMessage("Connection failed: " + com.dragonflow.SiteView.Monitor.lookupStatus(k));
            array = new Array();
            traceMessage("ERROR - STATUS = " + k, machine, FROM_REMOTE);
            exitValue = k;
        }
        return array;
    }

    public static void main(java.lang.String args[])
    {
        java.lang.String s = args[0];
        java.lang.String s1 = args[1];
        java.lang.String s2 = args[2];
        java.lang.String s3 = args[3];
        java.lang.String s4 = "ls";
        com.dragonflow.SiteView.Machine machine = new Machine();
        machine.setProperty(com.dragonflow.SiteView.Machine.pHost, s);
        machine.setProperty(com.dragonflow.SiteView.Machine.pLogin, s1);
        machine.setProperty(com.dragonflow.SiteView.Machine.pPassword, s2);
        machine.setProperty(com.dragonflow.SiteView.Machine.pLocalUser, s3);
        if(args.length >= 5)
        {
            s4 = args[4];
        }
        machine.setProperty("_trace", "true");
        com.dragonflow.Utils.RloginCommandLine rlogincommandline = new RloginCommandLine();
        rlogincommandline.exec(s4, machine, false);
    }

}
