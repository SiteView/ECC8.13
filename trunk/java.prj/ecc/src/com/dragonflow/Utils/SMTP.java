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

import java.io.FileInputStream;
import java.io.IOException;
import java.net.ProtocolException;
import java.net.Socket;

import jgl.Array;

// Referenced classes of package com.dragonflow.Utils:
// Base64Encoder, TextUtils, I18N, FileUtils

public class SMTP
{

    public static int defaultTimeout = 60000;
    public static jgl.Array noLogging = null;
    public static int defaultSMTPPort = 25;
    public static java.lang.String CRLF = "\r\n";
    private java.lang.String contentType;
    private java.lang.String subjectCharSet;
    private java.io.BufferedReader reply;
    private java.io.PrintWriter send;
    private java.net.Socket server;
    private jgl.Array log;
    private java.lang.String value;

    public SMTP(java.lang.String s, int i, jgl.Array array)
        throws java.net.UnknownHostException, java.io.IOException
    {
        contentType = null;
        subjectCharSet = null;
        reply = null;
        send = null;
        server = null;
        log = null;
        value = "";
        log = array;
        int j = defaultSMTPPort;
        java.lang.String s1 = s;
        int k = s1.indexOf(':');
        if(k != -1)
        {
            j = com.dragonflow.Utils.TextUtils.readInteger(s1, k + 1);
            s1 = s1.substring(0, k);
        }
        if(array != null)
        {
            array.add("-->  connecting to " + s1 + ":" + j + ", timeout=" + i);
        }
        server = new Socket(s1, j);
        com.dragonflow.SiteView.Platform.setSocketTimeout(server, i);
        InitMailEncoding();
        java.lang.String s2 = readResult();
        if(!s2.startsWith("220"))
        {
            throw new ProtocolException(s2);
        } else
        {
            return;
        }
    }

    public void close()
    {
        try
        {
            sendData("QUIT");
            if(log != null)
            {
                log.add("<-- closing connection");
            }
            server.close();
        }
        catch(java.io.IOException ioexception)
        {
            if(log != null)
            {
                log.add("--> close error:" + ioexception);
            }
        }
    }

    private java.lang.String formatContentType(java.lang.String s)
    {
        if(s == null || s.length() == 0)
        {
            return "Content-Type: text/plain";
        } else
        {
            return "Content-Type: text/plain; charset=\"" + s + "\"";
        }
    }

    private java.lang.String formatSubjectCharSet(java.lang.String s)
    {
        return "=?" + s + "?B?<subject>?=";
    }

    private void InitMailEncoding()
        throws java.io.IOException
    {
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s = null;
        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_httpCharSet");
        if(s1 != null && s1.length() > 0)
        {
            contentType = formatContentType(s1);
            subjectCharSet = formatSubjectCharSet(s1);
            s = s1;
        }
        java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailCharSet");
        if(s2 != null && s2.length() > 0)
        {
            contentType = formatContentType(s2);
            s = s2;
        } else
        {
            if(contentType == null)
            {
                contentType = formatContentType(com.dragonflow.Utils.I18N.isI18N ? "UTF-8" : null);
            }
            if(s == null)
            {
                s = com.dragonflow.Utils.I18N.isI18N ? "UTF-8" : com.dragonflow.Utils.I18N.getDefaultEncoding();
            }
        }
        reply = com.dragonflow.Utils.FileUtils.MakeInputReader(server.getInputStream(), s);
        send = com.dragonflow.Utils.FileUtils.MakeOutputWriter(server.getOutputStream(), s);
        java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailSubjectCharSet");
        if(s3 != null && s3.length() > 0)
        {
            subjectCharSet = formatSubjectCharSet(s3);
        } else
        if(subjectCharSet == null)
        {
            subjectCharSet = com.dragonflow.Utils.I18N.isI18N ? formatSubjectCharSet("UTF-8") : null;
        }
    }

    java.lang.String encodeSubject(java.lang.String s)
    {
        java.lang.String s1 = s;
        if(subjectCharSet != null)
        {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            java.lang.String s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailSubjectCharSet");
            if(s2 == null || s2.equals(""))
            {
                s2 = com.dragonflow.Utils.I18N.isI18N ? "UTF-8" : com.dragonflow.Utils.I18N.getDefaultEncoding();
            }
            java.lang.String s3 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_mailjavaCharSet");
            com.dragonflow.Utils.Base64Encoder base64encoder = new Base64Encoder(s, s2);
            s1 = base64encoder.processString();
            s1 = com.dragonflow.Utils.TextUtils.replaceString(s1, "\n", "");
            s1 = com.dragonflow.Utils.TextUtils.replaceString(subjectCharSet, "<subject>", s1);
        }
        return s1;
    }

    public void send(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4)
        throws java.io.IOException, java.net.ProtocolException
    {
        send(s, s1, s2, s3, s4, null);
    }

    public void sendSecure(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5, java.lang.String s6, 
            java.lang.String s7)
        throws java.io.IOException, java.net.ProtocolException
    {
        s4 = com.dragonflow.Utils.I18N.toDefaultEncoding(s4);
        if(s3.length() > 0)
        {
            s3 = com.dragonflow.Utils.I18N.isI18N ? new String(s3.getBytes("ISO-8859-1")) : s3;
        }
        java.lang.String s8 = "";
        try
        {
            java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
            s8 = inetaddress.getHostName();
        }
        catch(java.net.UnknownHostException unknownhostexception) { }
        java.lang.String s9 = "EHLO " + s8;
        sendCommandWithResult(s9);
        java.lang.String s12 = value;
        if(s12.length() > 0 && s12.indexOf("AUTH") > 0)
        {
            if(s6.startsWith("["))
            {
                java.lang.String s15 = s6.substring(1, s6.indexOf("]"));
                s6 = s6.substring(s15.length() + 2);
                s9 = "AUTH " + s15;
            } else
            {
                s9 = "AUTH LOGIN";
            }
            sendCommandWithResult(s9);
            java.lang.String s13 = value;
            com.dragonflow.Log.LogManager.log("RunMonitor", " value login " + s13);
            com.dragonflow.Utils.Base64Encoder base64encoder = new Base64Encoder(s6);
            s9 = base64encoder.processString();
            sendCommandWithResult(s9);
            s13 = value;
            com.dragonflow.Log.LogManager.log("RunMonitor", " value username " + s13);
            if(s7.length() > 0)
            {
                com.dragonflow.Utils.Base64Encoder base64encoder1 = new Base64Encoder(s7);
                s9 = base64encoder1.processString();
                sendCommandWithResult(s9);
                java.lang.String s14 = value;
                com.dragonflow.Log.LogManager.log("RunMonitor", " value password " + s14);
            }
        }
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
        {
            s9 = "MAIL FROM: " + s;
        } else
        {
            s9 = "MAIL FROM:<" + s + ">";
        }
        sendCommand(s9);
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1, ",");
        for(int i = 0; i < as.length; i++)
        {
            java.lang.String s10;
            if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
            {
                s10 = "RCPT TO: " + as[i];
            } else
            {
                s10 = "RCPT TO:<" + as[i] + ">";
            }
            sendCommand(s10);
        }

        if(s2.length() > 0)
        {
            java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s2, ",");
            for(int j = 0; j < as1.length; j++)
            {
                java.lang.String s11;
                if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
                {
                    s11 = "RCPT TO: " + as1[j];
                } else
                {
                    s11 = "RCPT TO:<" + as1[j] + ">";
                }
                sendCommand(s11);
            }

        }
        sendData("DATA");
        java.lang.String s16 = readResult();
        if(!s16.startsWith("354"))
        {
            throw new ProtocolException(s16);
        }
        java.lang.String s17 = "[attachments]";
        java.lang.String s18 = "";
        int k = s3.indexOf(s17);
        if(k != -1)
        {
            java.lang.String s19 = s3.substring(k + s17.length());
            boolean flag = s19.indexOf("Related") != -1;
            s3 = s3.substring(0, k);
            sendData("From: " + s);
            sendData("To: " + s1);
            if(s2.length() > 0)
            {
                sendData("Cc: " + s2);
            }
            if(log != null)
            {
                log.add("--> Subject: " + s3);
            }
            sendData("Subject: " + encodeSubject(s3));
            sendData("X-Mailer: SiteView");
            sendData("MIME-Version: 1.0");
            if(flag)
            {
                java.lang.String s20 = com.dragonflow.Utils.I18N.isI18N ? " charset=\"UTF-8\"" : "";
                sendData("Content-Type: multipart/related; boundary=\"" + s19 + "\"; type=text/html" + s20);
            } else
            {
                sendData("Content-Type: multipart/mixed; boundary=\"" + s19 + "\"");
            }
        } else
        if(s3.indexOf("[skipheaders]") == -1)
        {
            sendData("From: " + s);
            sendData("To: " + s1);
            if(s2.length() > 0)
            {
                sendData("Cc: " + s2);
            }
            if(log != null)
            {
                log.add("--> Subject: " + s3);
            }
            sendData("Subject: " + encodeSubject(s3));
            sendData("X-Mailer: SiteView");
            if(contentType != null)
            {
                sendData(contentType);
            }
        }
        sendData("Date: " + com.dragonflow.Utils.SMTP.RFCDateFormat(com.dragonflow.SiteView.Platform.makeDate()));
        sendData("");
        sendData(com.dragonflow.Utils.SMTP.convertNewlines(s4));
        if(s5 != null)
        {
            java.io.FileInputStream fileinputstream = new FileInputStream(s5);
            java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(fileinputstream);
            do
            {
                java.lang.String s21 = bufferedreader.readLine();
                if(s21 == null)
                {
                    break;
                }
                sendData(com.dragonflow.Utils.SMTP.convertNewlines(s21));
            } while(true);
            bufferedreader.close();
        }
        sendCommand(".");
    }

    public void send(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5)
        throws java.io.IOException, java.net.ProtocolException
    {
        s4 = com.dragonflow.Utils.I18N.toDefaultEncoding(s4);
        if(s3.length() > 0)
        {
            s3 = com.dragonflow.Utils.I18N.isI18N ? new String(s3.getBytes("ISO-8859-1")) : s3;
        }
        java.lang.String s6 = "";
        try
        {
            java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
            s6 = inetaddress.getHostName();
        }
        catch(java.net.UnknownHostException unknownhostexception) { }
        java.lang.String s7 = "HELO " + s6;
        sendCommand(s7);
        com.dragonflow.SiteView.SiteViewGroup siteviewgroup = com.dragonflow.SiteView.SiteViewGroup.currentSiteView();
        if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
        {
            s7 = "MAIL FROM: " + s;
        } else
        {
            s7 = "MAIL FROM:<" + s + ">";
        }
        sendCommand(s7);
        java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s1, ",");
        for(int i = 0; i < as.length; i++)
        {
            try
            {
                java.lang.String s8;
                if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
                {
                    s8 = "RCPT TO: " + as[i];
                } else
                {
                    s8 = "RCPT TO:<" + as[i] + ">";
                }
                sendCommand(s8);
            }
            catch(java.lang.Exception exception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Recipient: " + as[i] + ", has error: " + exception.toString());
            }
        }

        if(s2.length() > 0)
        {
            java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s2, ",");
            for(int j = 0; j < as1.length; j++)
            {
                try
                {
                    java.lang.String s9;
                    if(siteviewgroup.getSetting("_mailToFromRemoveBrackets").length() > 0)
                    {
                        s9 = "RCPT TO: " + as1[j];
                    } else
                    {
                        s9 = "RCPT TO:<" + as1[j] + ">";
                    }
                    sendCommand(s9);
                }
                catch(java.lang.Exception exception1)
                {
                    com.dragonflow.Log.LogManager.log("Error", "Recipient: " + as1[j] + ", has error: " + exception1.toString());
                }
            }

        }
        sendData("DATA");
        java.lang.String s10 = readResult();
        if(!s10.startsWith("354"))
        {
            throw new ProtocolException(s10);
        }
        java.lang.String s11 = "[attachments]";
        java.lang.String s12 = "";
        int k = s3.indexOf(s11);
        if(k != -1)
        {
            java.lang.String s13 = s3.substring(k + s11.length());
            boolean flag = s13.indexOf("Related") != -1;
            s3 = s3.substring(0, k);
            sendData("From: " + s);
            sendData("To: " + s1);
            if(s2.length() > 0)
            {
                sendData("Cc: " + s2);
            }
            if(log != null)
            {
                log.add("--> Subject: " + s3);
            }
            sendData("Subject: " + encodeSubject(s3));
            sendData("X-Mailer: SiteView");
            sendData("MIME-Version: 1.0");
            if(flag)
            {
                sendData("Content-Type: multipart/related; boundary=\"" + s13 + "\"; type=text/html");
            } else
            {
                sendData("Content-Type: multipart/mixed; boundary=\"" + s13 + "\"");
            }
        } else
        if(s3.indexOf("[skipheaders]") == -1)
        {
            sendData("From: " + s);
            sendData("To: " + s1);
            if(s2.length() > 0)
            {
                sendData("Cc: " + s2);
            }
            if(log != null)
            {
                log.add("--> Subject: " + s3);
            }
            sendData("Subject: " + encodeSubject(s3));
            sendData("X-Mailer: SiteView");
            if(contentType != null)
            {
                sendData(contentType);
            }
        }
        sendData("Date: " + com.dragonflow.Utils.SMTP.RFCDateFormat(com.dragonflow.SiteView.Platform.makeDate()));
        sendData("");
        sendData(com.dragonflow.Utils.SMTP.convertNewlines(s4));
        if(s5 != null)
        {
            java.io.FileInputStream fileinputstream = new FileInputStream(s5);
            java.io.BufferedReader bufferedreader = com.dragonflow.Utils.FileUtils.MakeInputReader(fileinputstream);
            do
            {
                java.lang.String s14 = bufferedreader.readLine();
                if(s14 == null)
                {
                    break;
                }
                sendData(com.dragonflow.Utils.SMTP.convertNewlines(s14));
            } while(true);
            bufferedreader.close();
        }
        sendCommand(".");
    }

    java.lang.String readResult()
    {
        value = "";
        java.lang.String s;
        try
        {
            s = reply.readLine();
            if(s == null)
            {
                throw new IOException("error reading from SMTP server");
            }
            if(log != null)
            {
                log.add("<-- " + s);
            }
            for(value += s; !com.dragonflow.Utils.TextUtils.isStatusLine(s); value += s)
            {
                s = reply.readLine();
                if(s == null)
                {
                    throw new IOException("error reading from SMTP server");
                }
                if(log != null)
                {
                    log.add("<-- " + s);
                }
            }

        }
        catch(java.io.IOException ioexception)
        {
            s = "" + ioexception;
        }
        return s;
    }

    void sendData(java.lang.String s)
    {
        s = s + CRLF;
        send.print(s);
        send.flush();
        if(log != null && s.indexOf("Subject: =?") == -1)
        {
            log.add("--> " + s);
        }
    }

    java.lang.String sendCommandWithResult(java.lang.String s)
        throws java.net.ProtocolException, java.io.IOException
    {
        sendData(s);
        java.lang.String s1 = readResult();
        if(!s1.startsWith("250") && !s1.startsWith("334") && !s1.startsWith("235"))
        {
            throw new ProtocolException(s1);
        } else
        {
            return s1;
        }
    }

    void sendCommand(java.lang.String s)
        throws java.net.ProtocolException, java.io.IOException
    {
        sendData(s);
        java.lang.String s1 = readResult();
        if(!s1.startsWith("250"))
        {
            throw new ProtocolException(s1);
        } else
        {
            return;
        }
    }

    static java.lang.String twoDigits(int i)
    {
        if(i < 10)
        {
            return "0" + i;
        } else
        {
            return "" + i;
        }
    }

    static java.lang.String convertNewlines(java.lang.String s)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer(s.length() + 100);
        for(int i = 0; i < s.length(); i++)
        {
            char c = s.charAt(i);
            if(c == '\r')
            {
                continue;
            }
            if(c == '\n')
            {
                stringbuffer.append(CRLF);
            } else
            {
                stringbuffer.append(c);
            }
        }

        return stringbuffer.toString();
    }

    static java.lang.String RFCDateFormat(java.util.Date date)
    {
        java.lang.String s;
        if(date.getTimezoneOffset() < 0)
        {
            s = "+";
        } else
        {
            s = "-";
        }
        java.lang.String s1;
        if(date.getYear() > 99)
        {
            s1 = java.lang.String.valueOf(date.getYear() + 1900);
        } else
        {
            s1 = java.lang.String.valueOf(date.getYear());
        }
        java.lang.String as[] = {
            "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
        };
        java.lang.String as1[] = {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", 
            "Nov", "Dec"
        };
        return as[date.getDay()] + ", " + java.lang.String.valueOf(date.getDate()) + " " + as1[date.getMonth()] + " " + s1 + " " + com.dragonflow.Utils.SMTP.twoDigits(date.getHours()) + ":" + com.dragonflow.Utils.SMTP.twoDigits(date.getMinutes()) + ":" + com.dragonflow.Utils.SMTP.twoDigits(date.getSeconds()) + " " + s + com.dragonflow.Utils.SMTP.twoDigits(java.lang.Math.abs(date.getTimezoneOffset()) / 60) + com.dragonflow.Utils.SMTP.twoDigits(java.lang.Math.abs(date.getTimezoneOffset()) % 60);
    }

    public static void main(java.lang.String args[])
        throws java.lang.Exception
    {
        jgl.Array array = new Array();
        java.lang.String s = "siteseer1.dragonflowinteractive.com";
        java.lang.String s1 = "siteviewtest@siteview.com";
        java.lang.String s2 = "siteviewtest@siteview.com";
        java.lang.String s3 = "";
        java.lang.String s4 = "this is a two line message\nsecond line";
        java.lang.String s5 = "test";
        int i = defaultTimeout;
        if(args.length > 0)
        {
            s5 = args[0];
        }
        if(args.length > 1)
        {
            s = args[1];
        }
        if(args.length > 2)
        {
            s1 = args[2];
        }
        if(args.length > 3)
        {
            i = com.dragonflow.Utils.TextUtils.toInt(args[3]);
        }
        try
        {
            com.dragonflow.Utils.SMTP smtp = new SMTP(s, i, array);
            smtp.send(s2, s1, s3, s5, s4, null);
            smtp.close();
        }
        catch(java.lang.Exception exception)
        {
            java.lang.System.out.println(exception + "\n");
        }
        for(java.util.Enumeration enumeration = array.elements(); enumeration.hasMoreElements(); java.lang.System.out.println(enumeration.nextElement())) { }
    }

}
