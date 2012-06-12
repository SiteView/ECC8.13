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


// Referenced classes of package com.dragonflow.Utils:
// MimeMessage

public class emailMessage
{

    boolean isOkay;
    java.lang.String statusMsg;
    java.lang.String from;
    java.lang.String to;
    java.lang.String cc;
    java.lang.String bcc;
    java.lang.String subject;
    java.lang.String xmailer;
    java.lang.String mimeVersion;
    java.lang.String contentType;
    java.lang.String date;
    java.lang.String returnPath;
    java.lang.String received;
    java.lang.String messageID;
    jgl.Array bodies;

    public emailMessage(java.lang.String as[])
    {
        isOkay = true;
        statusMsg = "";
        from = null;
        to = null;
        cc = null;
        bcc = null;
        subject = null;
        xmailer = null;
        mimeVersion = null;
        contentType = null;
        date = null;
        returnPath = null;
        received = null;
        messageID = null;
        bodies = null;
        com.dragonflow.Utils.MimeMessage mimemessage = new MimeMessage(as);
        from = mimemessage.getHeaderVal("From");
        to = mimemessage.getHeaderVal("To");
        cc = mimemessage.getHeaderVal("CC");
        bcc = mimemessage.getHeaderVal("BCC");
        subject = mimemessage.getHeaderVal("Subject");
        xmailer = mimemessage.getHeaderVal("X-Mailer");
        mimeVersion = mimemessage.getHeaderVal("MIME-Version");
        contentType = mimemessage.getHeaderVal("Content-Type");
        date = mimemessage.getHeaderVal("Date");
        returnPath = mimemessage.getHeaderVal("Return-Path");
        received = mimemessage.getHeaderVal("Received");
        messageID = mimemessage.getHeaderVal("Message-ID");
        bodies = mimemessage.getBodies();
        isOkay = mimemessage.isOkay();
        statusMsg = mimemessage.getStatusMsg();
    }

    public boolean isOkay()
    {
        return isOkay;
    }

    public java.lang.String getStatusMsg()
    {
        return statusMsg;
    }

    public java.lang.String getSubject()
    {
        if(subject != null)
        {
            return subject;
        } else
        {
            return "";
        }
    }

    public int getBodyCount()
    {
        return bodies.size();
    }

    public java.lang.String[] getIthBody(int i)
    {
        if(i >= 0 && i < bodies.size())
        {
            return (java.lang.String[])bodies.at(i);
        } else
        {
            return null;
        }
    }

    public java.lang.String toString()
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append("From = " + from + "\nTo = " + to + "\nCC = " + cc + "\nBCC = " + bcc + "\n");
        stringbuffer.append("Subject = " + subject + "\nX-Mailer = " + xmailer + "\n");
        stringbuffer.append("MIME-Version = " + mimeVersion + "\nContent-Type = " + contentType + "\n");
        stringbuffer.append("Date = " + date + "\nReturn-Path = " + returnPath + "\n");
        stringbuffer.append("Message-ID = " + messageID + "\n");
        for(int i = 0; i < bodies.size(); i++)
        {
            stringbuffer.append("\nBody #" + i + "\n");
            java.lang.String as[] = (java.lang.String[])bodies.at(i);
            for(int j = 0; j < as.length; j++)
            {
                stringbuffer.append(as[j]);
            }

        }

        return new String(stringbuffer);
    }
}
