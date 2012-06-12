/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.XmlApi;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.io.StringReader;
import java.util.Vector;

import jgl.HashMap;

import org.xml.sax.InputSource;

// Referenced classes of package COM.dragonflow.XmlApi:
// XmlApiRequest, XmlApiObject

public class XmlApiRequestXML extends COM.dragonflow.XmlApi.XmlApiRequest {

    private static java.lang.String headers[] = { "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n" };

    java.lang.StringBuffer xmlResponse;

    java.lang.String xmlRequest;

    public static final java.lang.String ALPHABETIC = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    public static final java.lang.String NUMERIC = "0123456789";

    public static final java.lang.String ALPHANUMERIC = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    private boolean encodeValues;

    public XmlApiRequestXML(java.lang.String s) {
        xmlResponse = null;
        xmlRequest = null;
        encodeValues = true;
        if (debug) {
            java.lang.System.out.println("xmlRequest=" + s);
        }
        xmlRequest = s;
        javax.xml.parsers.DocumentBuilderFactory documentbuilderfactory = javax.xml.parsers.DocumentBuilderFactory.newInstance();
        org.w3c.dom.Document document = null;
        try {
            javax.xml.parsers.DocumentBuilder documentbuilder = documentbuilderfactory.newDocumentBuilder();
            document = documentbuilder.parse(new InputSource(new StringReader(s)));
        } catch (java.lang.Exception exception) {
            COM.dragonflow.Log.LogManager.log("Error", "SiteView API: Exception, " + exception.getMessage());
            return;
        }
        if (document.getDocumentElement() != null) {
            encodeValues = true;
            processNode(document.getDocumentElement(), request);
        } else {
            COM.dragonflow.Log.LogManager.log("error", "APIRequestXML: Document element is null");
        }
    }

    public java.lang.Object getRequest() {
        return xmlRequest;
    }

    public java.lang.Object getResponse() {
        return getResponse(true);
    }

    public java.lang.Object getResponse(boolean flag) {
        xmlResponse = new StringBuffer();
        if (flag) {
            for (int i = 0; i < headers.length; i ++) {
                xmlResponse.append(headers[i]);
            }

        }
        addXmlElement(request);
        endXmlElement(request);
        return xmlResponse.toString();
    }

    private void processNode(org.w3c.dom.Node node, COM.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        if (node.getNodeType() == 1) {
            java.lang.String s = node.getNodeName();
            if (s != null && s.length() > 0) {
                jgl.HashMap hashmap = new HashMap();
                org.w3c.dom.NamedNodeMap namednodemap = node.getAttributes();
                for (int i = 0; i < namednodemap.getLength(); i ++) {
                    org.w3c.dom.Attr attr = (org.w3c.dom.Attr) namednodemap.item(i);
                    if (attr.getName() != null && attr.getName().equals("encodeValues") && attr.getValue() != null && (attr.getValue().equals("false") || attr.getValue().equals("true"))) {
                        encodeValues = (new Boolean(attr.getValue())).booleanValue();
                        continue;
                    }
                    java.lang.String s1 = attr.getValue();
                    if (s1 != null) {
                        s1 = COM.dragonflow.Utils.TextUtils.enlighten(s1);
                    }
                    hashmap.put(attr.getName(), s1);
                }

                org.w3c.dom.NodeList nodelist = node.getChildNodes();
                java.util.Vector vector = findPropNodes(nodelist);
                for (int j = 0; j < vector.size(); j ++) {
                    org.w3c.dom.Node node1 = (org.w3c.dom.Node) vector.elementAt(j);
                    org.w3c.dom.NodeList nodelist1 = node1.getChildNodes();
                    java.lang.String s2 = findPropertyName(nodelist1);
                    java.lang.String as[] = findValueNodes(nodelist1);
                    if (as.length > 1) {
                        hashmap.put(s2, as);
                        continue;
                    }
                    if (as.length == 1) {
                        hashmap.put(s2, as[0]);
                    } else {
                        hashmap.put(s2, "");
                    }
                }

                xmlapiobject.setProperties(hashmap);
                xmlapiobject.setName(s);
                java.util.Vector vector1 = findChildrenNodes(nodelist);
                for (int k = 0; k < vector1.size(); k ++) {
                    org.w3c.dom.Node node2 = (org.w3c.dom.Node) vector1.elementAt(k);
                    processNode(node2, xmlapiobject.add());
                }

            }
        }
    }

    private java.util.Vector findPropNodes(org.w3c.dom.NodeList nodelist) {
        java.util.Vector vector = new Vector();
        int i = nodelist.getLength();
        for (int j = 0; j < i; j ++) {
            org.w3c.dom.Node node = nodelist.item(j);
            if (node.getNodeType() == 1 && node.getNodeName().equals("property")) {
                vector.addElement(node);
            }
        }

        return vector;
    }

    private java.lang.String findPropertyName(org.w3c.dom.NodeList nodelist) {
        java.lang.String s = "";
        int i = nodelist.getLength();
        for (int j = 0; j < i; j ++) {
            org.w3c.dom.Node node = nodelist.item(j);
            if (!node.getNodeName().equals("#text")) {
                continue;
            }
            java.lang.String s1 = node.getNodeValue().trim();
            if (s1.length() <= 0) {
                continue;
            }
            s = s1;
            break;
        }

        return s;
    }

    private java.lang.String[] findValueNodes(org.w3c.dom.NodeList nodelist) {
        java.util.Vector vector = new Vector();
        int i = nodelist.getLength();
        for (int j = 0; j < i; j ++) {
            org.w3c.dom.Node node = nodelist.item(j);
            if (!node.getNodeName().equals("value")) {
                continue;
            }
            org.w3c.dom.Node node1 = node.getFirstChild();
            java.lang.String s = "";
            if (node1 != null) {
                s = node1.getNodeValue();
            }
            vector.addElement(s);
        }

        java.lang.String as[] = new java.lang.String[vector.size()];
        for (int k = 0; k < vector.size(); k ++) {
            as[k] = (java.lang.String) vector.elementAt(k);
        }

        return as;
    }

    private java.util.Vector findChildrenNodes(org.w3c.dom.NodeList nodelist) {
        java.util.Vector vector = new Vector();
        int i = nodelist.getLength();
        for (int j = 0; j < i; j ++) {
            org.w3c.dom.Node node = nodelist.item(j);
            if (node.getNodeType() == 1 && !node.getNodeName().equals("property")) {
                vector.addElement(node);
            }
        }

        return vector;
    }

    private void addXmlElement(COM.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        startXmlElement(xmlapiobject.getName(), xmlapiobject.getProperties(false));
        COM.dragonflow.XmlApi.XmlApiObject xmlapiobject1;
        for (java.util.Enumeration enumeration = xmlapiobject.elements(); enumeration.hasMoreElements(); endXmlElement(xmlapiobject1)) {
            xmlapiobject1 = (COM.dragonflow.XmlApi.XmlApiObject) enumeration.nextElement();
            addXmlElement(xmlapiobject1);
        }

    }

    private void startXmlElement(java.lang.String s, jgl.HashMap hashmap) {
        boolean flag = false;
        java.util.Vector vector = null;
        xmlResponse.append("<" + s);
        if (hashmap != null) {
            java.util.Enumeration enumeration = hashmap.keys();
            while (enumeration.hasMoreElements()) {
                java.lang.String s1 = enumeration.nextElement().toString();
                java.lang.Object obj = hashmap.get(s1);
                if (obj instanceof java.lang.String[]) {
                    flag = true;
                    if (vector == null) {
                        vector = new Vector();
                    }
                    vector.addElement(s1);
                } else if (obj instanceof java.lang.String) {
                    if (COM.dragonflow.Utils.I18N.isNullEncoding(obj.toString())) {
                        xmlResponse.append(" " + s1 + "=\"" + COM.dragonflow.Utils.TextUtils.escapeHTML(COM.dragonflow.Utils.I18N.toDefaultEncoding(obj.toString())) + "\"");
                    } else {
                        xmlResponse.append(" " + s1 + "=\"" + COM.dragonflow.Utils.TextUtils.escapeHTML(obj.toString()) + "\"");
                    }
                }
            } 
            xmlResponse.append(">\r\n");
            if (flag) {
                for (int i = 0; i < vector.size(); i ++) {
                    java.lang.String s2 = (java.lang.String) vector.elementAt(i);
                    java.lang.String as[] = (java.lang.String[]) hashmap.get(s2);
                    xmlResponse.append("<property>\r\n");
                    xmlResponse.append(s2 + "\r\n");
                    for (int j = 0; j < as.length; j ++) {
                        if (as[j] == null) {
                            continue;
                        }
                        if (encodeValues) {
                            java.lang.String s3 = COM.dragonflow.XmlApi.XmlApiRequestXML.escapeXML(as[j]);
                            xmlResponse.append("<value>" + s3 + "</value>\r\n");
                        } else {
                            xmlResponse.append("<value>" + as[j] + "</value>\r\n");
                        }
                    }

                    xmlResponse.append("</property>\r\n");
                }

            }
        }
    }

    private void endXmlElement(COM.dragonflow.XmlApi.XmlApiObject xmlapiobject) {
        xmlResponse.append("</" + xmlapiobject.getName() + ">\r\n");
    }

    private static int isEscaped(java.lang.StringBuffer stringbuffer, java.lang.String s, int i) {
        if (s.substring(i).startsWith("&gt;")) {
            stringbuffer.append("&gt;");
            return 4;
        }
        if (s.substring(i).startsWith("&lt;")) {
            stringbuffer.append("&lt;");
            return 4;
        }
        if (s.substring(i).startsWith("&#") || s.substring(i).startsWith("&amp;#")) {
            int j = 0;
            byte byte0 = ((byte) (s.substring(i).startsWith("&#") ? 2 : 6));
            for (j = i + byte0; j < s.length() && java.lang.Character.isDigit(s.charAt(j)); j ++) {
            }
            if (j < s.length() && s.charAt(j) == ';') {
                stringbuffer.append("&#");
                stringbuffer.append(s.substring(i + byte0, j + 1));
                return (j - i) + 1;
            }
        } else if (s.substring(i).startsWith("&amp;")) {
            stringbuffer.append("&amp;");
            return 5;
        }
        return 0;
    }

    public static java.lang.String escapeHTMLPlusSpaces(java.lang.String s) {
        java.lang.String s1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-.:/";
        java.lang.StringBuffer stringbuffer = new StringBuffer(s.length());
        int i = 0;
        do {
            if (i >= s.length()) {
                break;
            }
            for (int j = 0; (j = COM.dragonflow.XmlApi.XmlApiRequestXML.isEscaped(stringbuffer, s, i)) > 0 && i < s.length(); i += j) {
            }
            if (i >= s.length()) {
                break;
            }
            char c = s.charAt(i ++);
            if (s1.indexOf(c) >= 0) {
                stringbuffer.append(c);
            } else {
                COM.dragonflow.Utils.TextUtils.escapeChar(c, stringbuffer);
            }
        } while (true);
        return stringbuffer.toString();
    }

    private static java.lang.String escapeXML(java.lang.String s) {
        java.lang.StringBuffer stringbuffer = new StringBuffer(s.length());
        int i = 0;
        do {
            if (i >= s.length()) {
                break;
            }
            char c = s.charAt(i ++);
            if (!COM.dragonflow.XmlApi.XmlApiRequestXML.escapeSpecial(c, stringbuffer)) {
                stringbuffer.append(c);
            }
        } while (true);
        return stringbuffer.toString();
    }

    private static boolean escapeSpecial(char c, java.lang.StringBuffer stringbuffer) {
        boolean flag = true;
        if (c == '>') {
            stringbuffer.append("&gt;");
        } else if (c == '<') {
            stringbuffer.append("&lt;");
        } else if (c == '&') {
            stringbuffer.append("&amp;");
        } else {
            flag = false;
        }
        return flag;
    }

}
