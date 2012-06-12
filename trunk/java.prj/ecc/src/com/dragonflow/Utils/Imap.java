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

import java.net.Socket;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;

// Referenced classes of package com.dragonflow.Utils:
// popStatus, TextUtils

public class Imap {

    final int AUTHORIZATION = 1;

    final int AUTHENTICATION = 2;

    final int TRANSACTION = 3;

    final int UPDATE = 4;

    protected int _TotalMsgs;

    protected int _TotalSize;

    protected boolean _StatusOK;

    protected int State;

    protected java.lang.String Host;

    protected java.lang.String User;

    protected java.lang.String Password;

    boolean isConnected;

    private java.util.Hashtable pendingRequests;

    private int xmitCounter;

    protected int Port;

    java.lang.StringBuffer inputBuff;

    java.net.Socket socket;

    private java.io.InputStream in;

    private java.io.OutputStream out;

    private java.io.PrintWriter output;

    public int socketTimeout;

    public com.dragonflow.SiteView.AtomicMonitor monitor;

    public Imap(java.lang.String s, java.lang.String s1, java.lang.String s2, com.dragonflow.SiteView.AtomicMonitor atomicmonitor, java.io.PrintWriter printwriter) {
        _TotalMsgs = 0;
        _TotalSize = 0;
        _StatusOK = false;
        State = 0;
        Host = null;
        User = null;
        Password = null;
        Port = 143;
        socket = null;
        in = null;
        out = null;
        output = null;
        socketTimeout = 0x493e0;
        monitor = null;
        Host = s;
        User = s1;
        Password = s2;
        monitor = atomicmonitor;
        output = printwriter;
        isConnected = false;
        inputBuff = new StringBuffer();
        pendingRequests = new Hashtable(5);
        xmitCounter = 0;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @return
     */
    public synchronized com.dragonflow.Utils.popStatus connect() {
        com.dragonflow.Utils.popStatus popstatus;
        java.util.Vector vector;
        popstatus = new popStatus();
        vector = new Vector();
        debug("--> connecting to " + Host + ":" + Port);
        if (isConnected) {
            popstatus._Response = "Can't connect: already connected!";
            debug("--> Can't connect: already connected!");
            popstatus._OK = false;
            return popstatus;
        }
        try {
            socket = new Socket(Host, Port, true);
            if (socket == null) {
                debug("<-- -ERR could not connect to server");
                popstatus._OK = false;
                popstatus._Response = "-ERR Error while connecting to IMAP server";
                return popstatus;
            }

            debug("<-- -OK created a socket.");
            in = socket.getInputStream();
            out = socket.getOutputStream();
        } catch (java.io.IOException ioexception) {
            java.lang.String s = "-ERR " + ioexception.toString();
            debug("<-- " + s);
            popstatus._OK = false;
            popstatus._Response = s;
            socket = null;
            return popstatus;
        }
        isConnected = true;
        popstatus = roundTrip("CAPABILITY", vector);
        if (!com.dragonflow.Utils.Imap.replyToken(vector, "OK") || !popstatus._OK) {
            debug("<-- -ERR could not connect to server");
            popstatus._OK = false;
            popstatus._Response = "Badly formed CAPABILITY request or CAPABILITY request denied";
            return popstatus;
        } else {
            debug("<-- -OK connected to the IMAP server.");
            popstatus._Responses = new java.lang.String[vector.size()];
            vector.copyInto(popstatus._Responses);
            State = 1;
            return popstatus;
        }
    }

    public static boolean replyToken(java.util.Vector vector, java.lang.String s) {
        java.lang.String s1 = (java.lang.String) vector.elementAt(vector.size() - 1);
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s1);
        stringtokenizer.nextToken();
        java.lang.String s2 = stringtokenizer.nextToken();
        return s2.equals(s);
    }

    public com.dragonflow.Utils.popStatus roundTrip(java.lang.String s, java.util.Vector vector) {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        boolean flag = false;
        java.lang.String s2 = new String("Fake!");
        send(s);
        do {
            if (flag) {
                break;
            }
            try {
                s = recv();
                debug("Recieved: " + s);
                popstatus._OK = true;
                _StatusOK = true;
            } catch (java.lang.Exception exception) {
                java.lang.String s3 = "-IMAP Server IO Error: " + exception.toString();
                debug("<-- " + s3);
                popstatus._OK = false;
                popstatus._Response = s3;
                return popstatus;
            }
            vector.addElement(s);
            java.util.StringTokenizer stringtokenizer = new StringTokenizer(s);
            java.lang.String s1 = stringtokenizer.nextToken();
            if (!s1.equals("*")) {
                if (pendingRequests.containsKey(s1)) {
                    pendingRequests.remove(s1);
                    flag = true;
                    s2 = stringtokenizer.nextToken();
                } else {
                    debug("Found an unexpected Imap response.");
                    popstatus._OK = false;
                }
            }
        } while (true);
        if (!s2.equals("OK")) {
            popstatus._OK = false;
        } else {
            popstatus._OK = true;
        }
        return popstatus;
    }

    public com.dragonflow.Utils.popStatus login(java.lang.String s, java.lang.String s1) {
        User = s;
        Password = s1;
        return login();
    }

    public synchronized com.dragonflow.Utils.popStatus login() {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        if (User == null || Password == null) {
            popstatus._Response = "-BAD Userid or Password not specified";
            return popstatus;
        }
        java.util.Vector vector = new Vector();
        if (!isConnected) {
            java.lang.String s = "Unable to perform LOGIN when not connected to a server or if already logged in to a\n server";
            debug("<---" + s);
            popstatus._OK = false;
        }
        popstatus = roundTrip("LOGIN " + User + " " + Password, vector);
        if (!com.dragonflow.Utils.Imap.replyToken(vector, "OK") || !popstatus._OK) {
            java.lang.String s1 = "Badly formed LOGIN request";
            debug("<---" + s1);
            popstatus._OK = false;
            return popstatus;
        } else {
            debug("<-- -OK performed LOGIN request");
            popstatus._Responses = new java.lang.String[vector.size()];
            vector.copyInto(popstatus._Responses);
            popstatus._OK = true;
            State = 2;
            return popstatus;
        }
    }

    public synchronized void close() {
        debug("--> closing connection");
        try {
            if (socket != null) {
                socket.close();
                isConnected = false;
            }
            State = 0;
        } catch (java.io.IOException ioexception) {
            debug("Failure in Server.close()");
        }
    }

    public synchronized com.dragonflow.Utils.popStatus quit() {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        if (!isConnected) {
            java.lang.String s = "Unable to perform LOGOUT when not connected to a server";
            debug("<---" + s);
            popstatus._Response = s;
            popstatus._OK = false;
            return popstatus;
        }
        if (socket != null) {
            popstatus = roundTrip("LOGOUT", vector);
            if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
                debug("<-- LOGOUT command is performed");
                popstatus._Responses = new java.lang.String[vector.size()];
                vector.copyInto(popstatus._Responses);
                State = 4;
            } else {
                java.lang.String s1 = "Unable to perform LOGOUT when not connected to a server";
                debug("<---" + s1);
                popstatus._Response = s1;
                popstatus._OK = false;
            }
        } else {
            java.lang.String s2 = "Unable to perform LOGOUT when no socket to a server";
            debug("<---" + s2);
            popstatus._Response = s2;
            popstatus._OK = false;
            return popstatus;
        }
        return popstatus;
    }

    public synchronized com.dragonflow.Utils.popStatus select(java.lang.String s) {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        if (!isConnected) {
            java.lang.String s1 = "Unable to perform SELECT when not connected to a server";
            debug("<---" + s1);
            popstatus._Response = s1;
            popstatus._OK = false;
            return popstatus;
        }
        if (socket != null) {
            popstatus = roundTrip("SELECT " + s, vector);
            if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
                debug("<-- -OK was able to SELECT mailbox");
                popstatus._Responses = new java.lang.String[vector.size()];
                vector.copyInto(popstatus._Responses);
                popstatus._OK = true;
                State = 4;
            } else {
                java.lang.String s2 = "Unable to send SELECT to the IMAP server";
                debug("<-- -ERR" + s2);
                popstatus._Response = s2;
                popstatus._OK = false;
            }
        } else {
            popstatus._OK = false;
        }
        return popstatus;
    }

    public synchronized com.dragonflow.Utils.popStatus fetch(int i) {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        java.lang.Integer integer = new Integer(i);
        java.lang.String s = integer.toString();
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_imapFetchQuery");
        if (s1.length() == 0) {
            s1 = "BODY[TEXT]";
        }
        if (socket != null) {
            popstatus = roundTrip("FETCH " + s + " " + s1, vector);
            if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
                popstatus._Responses = new java.lang.String[vector.size()];
                vector.copyInto(popstatus._Responses);
                debug("<-- OK was able to get the message via FETCH");
            } else {
                java.lang.String s2 = "Unable to send FETCH command to the server. ";
                debug("<---" + s2);
                popstatus._Response = s2;
                popstatus._OK = false;
            }
        } else {
            popstatus._OK = false;
        }
        return popstatus;
    }

    public synchronized com.dragonflow.Utils.popStatus noop() {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        if (!isConnected) {
            java.lang.String s = "Unable to perform NOOP when not connected to a server or if already logged in to a\n server";
            debug("<---" + s);
            popstatus._OK = false;
            popstatus._Response = "-BAD Invalid response";
            return popstatus;
        }
        popstatus = roundTrip("NOOP", vector);
        if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
            popstatus._Responses = new java.lang.String[vector.size()];
            vector.copyInto(popstatus._Responses);
        } else {
            popstatus._Response = "-BAD Invalid response";
        }
        return popstatus;
    }

    void send(java.lang.String s) {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.StringTokenizer stringtokenizer = new StringTokenizer(s, " ", false);
        java.lang.String s2 = new String("A" + xmitCounter + " ");
        java.lang.String s1 = new String(s2 + s);
        byte abyte0[] = new byte[s1.length() + 2];
        pendingRequests.put(s2.substring(0, s2.length() - 1), stringtokenizer.nextToken());
        xmitCounter ++;
        s1.getBytes(0, s1.length(), abyte0, 0);
        abyte0[s1.length()] = 13;
        abyte0[s1.length() + 1] = 10;
        try {
            out.write(abyte0);
            debug("Send: " + s1);
            out.flush();
            _StatusOK = true;
            popstatus._OK = true;
        } catch (java.lang.Exception exception) {
            java.lang.System.err.println("Send: Unexpected exception: " + exception.toString());
            _StatusOK = false;
            popstatus._OK = false;
            popstatus._Response = "-ERR Invalid response";
            return;
        }
    }

    java.lang.String recv() {
        byte abyte0[] = new byte[256];
        int i = 0;
        int k = 0;
        com.dragonflow.SiteView.Platform.setSocketTimeout(socket, socketTimeout);
        java.lang.String s1 = inputBuff.toString();
        boolean flag;
        if (s1.indexOf("\r\n") != -1) {
            flag = true;
        } else {
            flag = false;
        }
        do {
            if (flag) {
                break;
            }
            try {
                i = in.read(abyte0, 0, 256);
            } catch (java.lang.Exception exception) {
                java.lang.System.err.println("Read: Unexpected exception: " + exception.toString());
                flag = true;
            }
            inputBuff.append(new String(abyte0, 0, 0, i));
            s1 = inputBuff.toString();
            if (s1.indexOf("\r\n") != -1 || i == -1) {
                flag = true;
            }
        } while (true);
        char ac[] = new char[s1.indexOf("\r\n")];
        inputBuff.getChars(0, s1.indexOf("\r\n"), ac, 0);
        inputBuff = new StringBuffer(s1.substring(s1.indexOf("\r\n") + 2, s1.length()));
        java.lang.String s = new String(ac);
        if (s.length() > 1 && s.charAt(s.length() - 1) == '}') {
            int l = s.lastIndexOf('{');
            if (l != -1) {
                java.lang.String s3 = s.substring(l + 1, s.length() - 1);
                int j = java.lang.Integer.valueOf(s3, 10).intValue();
                java.lang.String s4;
                if (j == 0) {
                    s4 = "";
                } else {
                    abyte0 = new byte[j];
                    if (j < inputBuff.length()) {
                        k = j;
                    } else {
                        k = inputBuff.length();
                    }
                    java.lang.String s2 = inputBuff.toString();
                    s2.getBytes(0, k, abyte0, 0);
                    if (k == inputBuff.length()) {
                        inputBuff = new StringBuffer("");
                    } else {
                        inputBuff = new StringBuffer(s2.substring(k));
                    }
                }
                for (; k < j; k += i) {
                    try {
                        i = in.read(abyte0, k, j - k);
                    } catch (java.lang.Exception exception1) {
                        java.lang.System.err.println("Read: Unexpected exception:" + exception1.toString());
                        debug("End of file reached on a read of the network to IMAP Server!");
                    }
                    if (i == -1) {
                        debug("End of file reached on a read of the network to IMAP Server!");
                    }
                }

                s4 = new String(abyte0, 0, 0, j);
                s = s + s4 + recv();
            }
        }
        return s;
    }

    public synchronized com.dragonflow.Utils.popStatus dele(int i) {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        java.lang.String s = "+";
        java.lang.String s1 = "(\\deleted)";
        if (!isConnected) {
            java.lang.String s2 = "Unable to perform DELETE when not connected to a server or if already logged in to a\n server";
            debug("<---" + s2);
            popstatus._OK = false;
            popstatus._Response = "-BAD Invalid response";
            return popstatus;
        }
        popstatus = roundTrip("STORE " + i + " " + s + "FLAGS " + s1, vector);
        if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
            popstatus._Responses = new java.lang.String[vector.size()];
            vector.copyInto(popstatus._Responses);
            debug("<-- -OK message tagged for deletion");
        } else {
            popstatus._Response = "-BAD Invalid response";
        }
        return popstatus;
    }

    public synchronized com.dragonflow.Utils.popStatus expunge() {
        com.dragonflow.Utils.popStatus popstatus = new popStatus();
        java.util.Vector vector = new Vector();
        if (!isConnected) {
            java.lang.String s = "Unable to perform EXPUNGE when not connected to a server or if already logged in to a\n server";
            debug("<---" + s);
            popstatus._OK = false;
            popstatus._Response = "-BAD Invalid response";
            return popstatus;
        }
        popstatus = roundTrip("EXPUNGE", vector);
        if (com.dragonflow.Utils.Imap.replyToken(vector, "OK") || popstatus._OK) {
            popstatus._Responses = new java.lang.String[vector.size()];
            vector.copyInto(popstatus._Responses);
            debug("<-- -OK message was expunged");
        } else {
            popstatus._Response = "-BAD Invalid response";
        }
        return popstatus;
    }

    public void debug(java.lang.String s) {
        if (output != null) {
            output.println(s + "\n");
            output.flush();
        }
        if (monitor != null) {
            monitor.progressString += s + "\n";
        }
    }
}
