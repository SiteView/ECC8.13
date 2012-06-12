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
// TextUtils
public class RawXmlWriter {

    java.lang.StringBuffer buf;

    public RawXmlWriter(java.lang.StringBuffer stringbuffer) {
        buf = stringbuffer;
    }

    public void writeSOAPHeader(jgl.Array array) {
        if (array.size() <= 0) {
            buf.append("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
            buf.append("<SOAP-ENV:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ");
            buf.append("xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ");
            buf.append("xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">\n");
        } else {
            for (int i = 0; i < array.size(); i ++) {
                buf.append((java.lang.String) array.at(i));
            }

        }
    }

    public void startElement(java.lang.String s) {
        buf.append("<");
        buf.append(s);
        buf.append(">");
    }

    public void endElement(java.lang.String s) {
        buf.append("</");
        buf.append(s);
        buf.append(">");
    }

    public void emptyElement(java.lang.String s) {
        buf.append("<");
        buf.append(s);
        buf.append("/>");
    }

    public void startElementEnc(java.lang.String s) {
        buf.append(xmlEncode("<"));
        buf.append(xmlEncode(s));
        buf.append(xmlEncode(">"));
    }

    public void endElementEnc(java.lang.String s) {
        buf.append(xmlEncode("</"));
        buf.append(xmlEncode(s));
        buf.append(xmlEncode(">"));
    }

    public void emptyElementEnc(java.lang.String s) {
        buf.append(xmlEncode("<"));
        buf.append(xmlEncode(s));
        buf.append(xmlEncode("/>"));
    }

    public void chardata(java.lang.String s) {
        int i = s.length();
        for (int j = 0; j < i; j ++) {
            char c = s.charAt(j);
            switch (c) {
            case 60: // '<'
                buf.append("&lt;");
                break;

            case 62: // '>'
                buf.append("&gt;");
                break;

            case 34: // '"'
                buf.append("&quot;");
                break;

            case 38: // '&'
                buf.append("&amp;");
                break;

            default:
                buf.append(c);
                break;
            }
        }

    }

    public java.lang.String xmlEncode(java.lang.String s) {
        java.lang.String s1 = "&";
        java.lang.String s2 = "&amp;";
        java.lang.String s3 = s;
        for (int i = -1; (i = s3.indexOf(s1, i + 1)) != -1;) {
            s3 = s3.substring(0, i) + s2 + s3.substring(i + s1.length());
        }

        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "\"", "&quot;");
        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, ">", "&gt;");
        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "<", "&lt;");
        return s3;
    }

    public void write(char ac[]) {
        buf.append(ac);
    }

    public void write(java.lang.String s) {
        buf.append(s);
    }

    public java.lang.String toString() {
        return buf.toString();
    }

    public static java.lang.String enXMLElement(java.lang.String s) {
        return s;
    }

    public static java.lang.String enCodeElement(java.lang.String s) {
        java.lang.String s1 = "&";
        java.lang.String s2 = "&amp;";
        java.lang.String s3 = s;
        for (int i = -1; (i = s3.indexOf(s1, i + 1)) != -1;) {
            s3 = s3.substring(0, i) + s2 + s3.substring(i + s1.length());
        }

        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "\"", "&quot;");
        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, ">", "&gt;");
        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "<", "&lt;");
        return s3;
    }
}
