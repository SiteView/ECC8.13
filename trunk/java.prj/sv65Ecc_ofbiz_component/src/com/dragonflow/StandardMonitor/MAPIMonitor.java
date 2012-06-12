/*
 * 
 * Created on 2005-3-7 1:20:16
 *
 * MAPIMonitor.java
 *
 * History:
 *
 */
package com.dragonflow.StandardMonitor;

/**
 * Comment for <code>MAPIMonitor</code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Enumeration;
import java.util.Vector;

import jgl.Array;
import com.dragonflow.Properties.NumericProperty;
import com.dragonflow.Properties.StringProperty;
import com.dragonflow.SiteView.AtomicMonitor;
import com.dragonflow.SiteView.Platform;
import com.dragonflow.SiteView.Rule;
import com.dragonflow.Utils.CommandLine;

import com.netaphor.smtp.Attachment;
import com.netaphor.smtp.Client;
import com.netaphor.smtp.SMTPException;
import com.siteview.ecc.util.MonitorIniValueReader;
import com.siteview.ecc.util.MonitorTypeValueReader;

public class MAPIMonitor extends AtomicMonitor {

    static StringProperty pTarget;

    static StringProperty pMailbox;

    static StringProperty pUserDomain;

    static StringProperty pUserName;

    static StringProperty pUserPwd;

    static StringProperty pSenderServer;

    static StringProperty pSenderMailbox;

    static StringProperty pSenderUserDomain;

    static StringProperty pSenderUserName;

    static StringProperty pSenderUserPwd;

    static NumericProperty pTimeout;

    static StringProperty pSMTPServer;

    static StringProperty pSenderAddress;

    static StringProperty pReceiverAddress;

    static StringProperty pAttachment;

    static NumericProperty pRoundTripValue;

    static Object mSyncLock = new Object();

    public MAPIMonitor() {
    }

    protected boolean checkForMessage(String s, StringBuffer stringbuffer) {
        CommandLine commandline = new CommandLine();
        boolean flag = useSMTP() && getProperty(pAttachment).length() > 0;
        Vector vector = new Vector();
        vector.add(Platform.getRoot() + "\\tools\\mapi_mon.exe");
        vector.add("operation=receive");
        vector.add("domain=" + getProperty(pUserDomain));
        vector.add("user=" + getProperty(pUserName));
        vector.add("pwd=" + getProperty(pUserPwd));
        vector.add("server=" + getProperty(pTarget));
        vector.add("mailbox=" + getProperty(pMailbox));
        vector.add("timeout=" + getProperty(pTimeout));
        vector.add("subject=" + s);
        vector.add("attachment=" + (flag ? "true" : "false"));
        Array array = commandline.exec(vector);
        int i = commandline.getExitValue();
        if (i == 0 && array.size() >= 1 && array.at(0).toString().startsWith("true")) {
            return true;
        }
        if (array.size() >= 2) {
            for (int j = 1; j < array.size(); j ++) {
                stringbuffer.append(array.at(j).toString() + "\n");
            }

        } else {
            stringbuffer.append(" Operation timed out.");
        }
        return false;
    }

    String getSenderProp(StringProperty stringproperty, StringProperty stringproperty1) {
        String s = getProperty(stringproperty);
        if (s.trim().length() > 0) {
            return s;
        } else {
            return getProperty(stringproperty1).trim();
        }
    }

    protected boolean sendMAPIMail(String s, String s1, String s2, StringBuffer stringbuffer) {
        CommandLine commandline = new CommandLine();
        String s3 = getSenderProp(pSenderUserDomain, pUserDomain);
        String s4 = getSenderProp(pSenderUserName, pUserName);
        String s5 = getSenderProp(pSenderUserPwd, pUserPwd);
        String s6 = getSenderProp(pSenderServer, pTarget);
        String s7 = getSenderProp(pSenderMailbox, pMailbox);
        Vector vector = new Vector();
        vector.add(Platform.getRoot() + "\\tools\\mapi_mon.exe");
        vector.add("operation=send");
        vector.add("domain=" + s3);
        vector.add("user=" + s4);
        vector.add("pwd=" + s5);
        vector.add("server=" + s6);
        vector.add("mailbox=" + s7);
        vector.add("timeout=" + getProperty(pTimeout));
        vector.add("subject=" + s);
        vector.add("recipientAddressType=" + s1);
        vector.add("recipientAddress=" + s2);
        vector.add("attachment=false");
        Array array = commandline.exec(vector);
        int i = commandline.getExitValue();
        if (i == 0 && array.size() >= 1 && array.at(0).toString().startsWith("true")) {
            return true;
        }
        if (array.size() >= 2) {
            for (int j = 1; j < array.size(); j ++) {
                stringbuffer.append(array.at(j).toString() + "\n");
            }

        } else {
            stringbuffer.append(" Operation timed out.");
        }
        return false;
    }

    protected boolean resolveMAPIEmailAddress(StringBuffer stringbuffer, Vector vector) {
        CommandLine commandline = new CommandLine();
        Vector vector1 = new Vector();
        vector1.add(Platform.getRoot() + "\\tools\\mapi_mon.exe");
        vector1.add("operation=resolve");
        vector1.add("domain=" + getProperty(pUserDomain));
        vector1.add("user=" + getProperty(pUserName));
        vector1.add("pwd=" + getProperty(pUserPwd));
        vector1.add("server=" + getProperty(pTarget));
        vector1.add("mailbox=" + getProperty(pMailbox));
        vector1.add("timeout=" + getProperty(pTimeout));
        vector1.add("subject=dummy");
        vector1.add("attachment=false");
        Array array = commandline.exec(vector1);
        int i = commandline.getExitValue();
        if (i == 0 && array.size() == 3 && array.at(0).toString().startsWith("true")) {
            vector.add(array.at(1));
            vector.add(array.at(2));
            return true;
        }
        if (array.size() >= 2) {
            for (int j = 1; j < array.size(); j ++) {
                stringbuffer.append(array.at(j).toString() + "\n");
            }

        } else {
            stringbuffer.append(" Operation timed out.");
        }
        return false;
    }

    boolean shouldSendMail() {
        return getProperty(pSMTPServer).trim().length() > 0;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param stringbuffer
     * @return
     */
    boolean sendMail(String s, StringBuffer stringbuffer) {
        try {
            String s2;
            Client client = new Client(getProperty(pSMTPServer));
            String s1 = getProperty(pAttachment);
            if (s1.length() > 0) {
                FileInputStream fileinputstream = null;
                int i = s1.lastIndexOf(File.separator);
                if (i < 0) {
                    s2 = s1;
                } else {
                    s2 = s1.substring(i + 1);
                }
                try {
                    fileinputstream = new FileInputStream(s1);
                } catch (FileNotFoundException filenotfoundexception) {
                    stringbuffer.append("Attachment file could not be found");
                    return false;
                }

                Attachment aattachment[] = new Attachment[1];
                aattachment[0] = new Attachment(s2, s2, fileinputstream);
                client.setAttachments(aattachment);
            }
            client.setSubject(s);
            String as[] = new String[1];
            as[0] = getProperty(pReceiverAddress);
            client.setToRecipients(as);
            client.setSender(getProperty(pSenderAddress));
            client.start();
            client.finish();
        } catch (SMTPException smtpexception) {
            stringbuffer.append(smtpexception.getMessage());
            return false;
        }
        return true;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     */
    protected boolean update() {
        String s;
        boolean flag;
        StringBuffer stringbuffer;
        s = currentStatus;
        currentStatus = "MAPIMonitor waiting for other MAPIMonitors to finish...";
        long l = 0L;
        flag = false;
        stringbuffer = new StringBuffer();
        Object obj = null;
        boolean flag1 = false;
        long l1;
        String s1;

        synchronized (mSyncLock) {
            StringProperty stringproperty;
            l1 = Platform.timeMillis();
            s1 = "mapi_mon" + Platform.getDefaultIPAddress() + l1;
            currentStatus = s;
            if (useSMTP()) {
                stringproperty = getMissingSMTPProp();
                if (stringproperty != null) {
                    synchronized (this) {
                        setProperty(pRoundTripValue, "n/a");
                        setProperty(pStateString, "Missing " + stringproperty.getLabel());
                        return true;
                    }
                }

                flag = sendMail(s1, stringbuffer);

            } else {
                Vector vector = new Vector();
                if (resolveMAPIEmailAddress(stringbuffer, vector)) {
                    flag = sendMAPIMail(s1, (String) vector.get(0), (String) vector.get(1), stringbuffer);
                }
            }

            if (flag) {
                flag1 = checkForMessage(s1, stringbuffer);
            }
        }

        if (!flag) {
            synchronized (this) {
                setProperty(pRoundTripValue, "n/a");
                String s2 = "Failed to send message. Error: " + stringbuffer.toString();
                setProperty(pStateString, s2);
            }
            return true;
        }

        synchronized (this) {
            if (flag1) {
                setProperty(pRoundTripValue, Platform.timeMillis() - l1);
                setProperty(pStateString, getProperty(pRoundTripValue) + " msecs");
            } else {
                setProperty(pRoundTripValue, "n/a");
                setProperty(pNoData, "n/a");
                String s3 = "Failed to retrieve message. Error: " + stringbuffer.toString();
                setProperty(pStateString, s3);
            }
        }
        return true;
    }

    public static void main(String args[]) {
    }

    public Array getLogProperties() {
        Array array = super.getLogProperties();
        array.add(pRoundTripValue);
        return array;
    }

    public String defaultTitle() {
        String s = "MAPI: mailbox " + getProperty(pMailbox);
        return s;
    }

    public String getHostname() {
        return getProperty(pTarget);
    }

    public Enumeration getStatePropertyObjects(boolean flag) {
        Array array = new Array();
        array.add(pRoundTripValue);
        return array.elements();
    }

    public String GetPropertyLabel(StringProperty stringproperty, boolean flag) {
        return stringproperty.printString();
    }

    boolean useSMTP() {
        return getProperty(pSMTPServer).trim().length() > 0 || getProperty(pSenderAddress).trim().length() > 0 || getProperty(pReceiverAddress).trim().length() > 0;
    }

    StringProperty getMissingSMTPProp() {
        if (getProperty(pSMTPServer).trim().length() <= 0) {
            return pSMTPServer;
        }
        if (getProperty(pSenderAddress).trim().length() <= 0) {
            return pSenderAddress;
        }
        if (getProperty(pReceiverAddress).trim().length() <= 0) {
            return pReceiverAddress;
        } else {
            return null;
        }
    }

    static {
        pTarget = new StringProperty("_server", "");
        pTarget.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_server", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_server", MonitorIniValueReader.DESCRIPTION));
        //pTarget.setDisplayText("Receiver Server", "MS Exchange server of the receiving mailbox.");
        pTarget.setParameterOptions(true, 21, false);
        
        pMailbox = new StringProperty("_mailbox", "");
        pMailbox.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_mailbox", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_mailbox", MonitorIniValueReader.DESCRIPTION));
        //pMailbox.setDisplayText(" Receiver Mailbox ", "The alias of the receiving mailbox.");
        pMailbox.setParameterOptions(true, 22, false);
        
        pUserDomain = new StringProperty("_userDomain", "");
        pUserDomain.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userDomain", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userDomain", MonitorIniValueReader.DESCRIPTION));
        //pUserDomain.setDisplayText("Receiver Domain ", "The domain to which both the receiving mailbox owner and the receiving MS exchange server belong.");
        pUserDomain.setParameterOptions(true, 24, false);
        
        pUserName = new StringProperty("_userName", "");
        pUserName.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userName", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userName", MonitorIniValueReader.DESCRIPTION));
        //pUserName.setDisplayText("Receiver User Name ", "Login name for the NT account of the receiving mailbox owner");
        pUserName.setParameterOptions(true, 25, false);
        
        pUserPwd = new StringProperty("_userPwd", "");
        pUserPwd.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userPwd", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_userPwd", MonitorIniValueReader.DESCRIPTION));
        //pUserPwd.setDisplayText("Receiving User Password", "The password of the above receiving account");
        pUserPwd.setParameterOptions(true, 26, false);
        pUserPwd.isPassword = true;
        
        pSenderServer = new StringProperty("_senderServer", "");
        pSenderServer.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderServer", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderServer", MonitorIniValueReader.DESCRIPTION));
        //pSenderServer.setDisplayText( "Sender Server", "name of the sender's MS Exchange server name.<BR>Notes: <BR>1. The MAPI sender is ignored if an SMTP sender is specified below.<BR>2. If no SMTP sender values are specified below, the receiver values will be used if any of the sender values are not specified");
        pSenderServer.setParameterOptions(true, 27, false);
        
        pSenderMailbox = new StringProperty("_senderMailbox", "");
        pSenderMailbox.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderMailbox", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderMailbox", MonitorIniValueReader.DESCRIPTION));
        //pSenderMailbox.setDisplayText(" Sender Mailbox ", "The alias of the sending mailbox.");
        pSenderMailbox.setParameterOptions(true, 28, false);
        
        pSenderUserDomain = new StringProperty("_senderUserDomain", "");
        pSenderUserDomain.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserDomain", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserDomain", MonitorIniValueReader.DESCRIPTION));
        //pSenderUserDomain.setDisplayText("Sender Domain ", "The domain to which both the sending mailbox owner and the sending MS exchange server belong.");
        pSenderUserDomain.setParameterOptions(true, 29, false);
        
        pSenderUserName = new StringProperty("_senderUserName", "");
        pSenderUserName.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserName", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserName", MonitorIniValueReader.DESCRIPTION));
        //pSenderUserName.setDisplayText("Sender User Name ", "Login name for the NT account of the sending mailbox owner");
        pSenderUserName.setParameterOptions(true, 30, false);
        
        pSenderUserPwd = new StringProperty("_senderUserPwd", "");
        pSenderUserPwd.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserPwd", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderUserPwd", MonitorIniValueReader.DESCRIPTION));
        //pSenderUserPwd.setDisplayText("Sender Password", "The password of the above sender account");
        pSenderUserPwd.setParameterOptions(true, 31, false);
        pSenderUserPwd.isPassword = true;
        
        pTimeout = new NumericProperty("_timeout", "25", MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_timeout", MonitorIniValueReader.UNIT));
        //pTimeout = new NumericProperty("_timeout", "25", "seconds");
        pTimeout.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_timeout", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_timeout", MonitorIniValueReader.DESCRIPTION));
        //pTimeout.setDisplayText("Transaction timeout", "Number of seconds the monitor will wait for the message to arrive");
        pTimeout.setParameterOptions(true, 1, true);
        
        pSMTPServer = new StringProperty("_SMTPServer", "");
        pSMTPServer.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_SMTPServer", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_SMTPServer", MonitorIniValueReader.DESCRIPTION));
        //pSMTPServer.setDisplayText("SMTP Server ", "SMTP server through which an outgoing message will be sent.<BR>Note: if you set any of the SMTP values (server, sender or receiver) they will override the MAPI sender options above");
        pSMTPServer.setParameterOptions(true, 2, true);
        
        pSenderAddress = new StringProperty("_senderAddress", "");
        pSenderAddress.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderAddress", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_senderAddress", MonitorIniValueReader.DESCRIPTION));
        //pSenderAddress.setDisplayText("Sender ", "SMTP Sender email address");
        pSenderAddress.setParameterOptions(true, 3, true);
        
        pReceiverAddress = new StringProperty("_receiverAddress", "");
        pReceiverAddress.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_receiverAddress", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_receiverAddress", MonitorIniValueReader.DESCRIPTION));
        //pReceiverAddress.setDisplayText("Receiver ", "Receipient email address. Must match the recipient mailbox alias above");
        pReceiverAddress.setParameterOptions(true, 4, true);
        
        pAttachment = new StringProperty("_attachment", "");
        pAttachment.setDisplayText(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_attachment", MonitorIniValueReader.LABEL),MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "_attachment", MonitorIniValueReader.DESCRIPTION));
        pAttachment.setDisplayText("Attachment ", "Full path to the file that will be attached to the outgoing SMTP message");
        pAttachment.setParameterOptions(true, 5, true);
        
        pRoundTripValue = new NumericProperty("roundTripValue", "0", MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "roundTripValue", MonitorIniValueReader.UNIT));
        //pRoundTripValue = new NumericProperty("roundTripValue", "0", " msecs");
        pRoundTripValue.setStateOptions(1);
        pRoundTripValue.setLabel(MonitorIniValueReader.getValue(MAPIMonitor.class.getName(), "roundTripValue", MonitorIniValueReader.LABEL));
        //pRoundTripValue.setLabel("Round Trip");
        StringProperty astringproperty[] = { pTarget, pMailbox, pUserDomain, pUserName, pUserPwd, pSenderServer, pSenderMailbox, pSenderUserDomain, pSenderUserName, pSenderUserPwd, pTimeout, pSMTPServer, pSenderAddress, pReceiverAddress, pAttachment,
                pRoundTripValue };
        addProperties("com.dragonflow.StandardMonitor.MAPIMonitor", astringproperty);
        addClassElement("com.dragonflow.StandardMonitor.MAPIMonitor", Rule.stringToClassifier("roundTripValue == n/a\terror"));
        addClassElement("com.dragonflow.StandardMonitor.MAPIMonitor", Rule.stringToClassifier("always\tgood"));
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "description", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.DESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "description", "Tests MS Exchange server by sending a message via MAPI.");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "help", "MAPIMon.htm");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "title", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.TITLE));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "title", "MAPI");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "class", "MAPIMonitor");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "toolName", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.TOOLNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "toolName", "Microsoft Exchange server");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "toolDescription", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.TOOLDESCRIPTION));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "toolDescription", "Test an MS Exchange server by sending and retrieving a test message.");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "topazName", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.TOPAZNAME));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "topazName", "mapimon");
        
        setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "topazType", MonitorTypeValueReader.getValue(MAPIMonitor.class.getName(), MonitorTypeValueReader.TOPAZTYPE));
        //setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "topazType", "Ghost Transaction");
        if (!Platform.isWindows()) {
            setClassProperty("com.dragonflow.StandardMonitor.MAPIMonitor", "loadable", "false");
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
