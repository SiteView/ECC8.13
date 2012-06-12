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

import java.io.IOException;
import java.net.URL;

import jgl.Array;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.NTCredentials;
import org.apache.commons.httpclient.UsernamePasswordCredentials;
import org.apache.commons.httpclient.methods.GetMethod;
import org.apache.commons.httpclient.methods.PostMethod;

import COM.datachannel.xml.om.Document;

// Referenced classes of package com.dragonflow.Utils:
// RawXmlWriter, XSLUtils, TextUtils

public class SoapRpc
{

    java.lang.String methodName;
    static final int REQUESTRESPONSE = 2;
    static final int ONEWAY = 1;
    int transmission;
    public static boolean debug = false;
    static final java.lang.String types[] = {
        "String", "Integer", "Boolean", "Double", "Date", "Base64", "Struct", "Array", "Nil"
    };
    public static final java.lang.String WSDL_XMLNS = "http://schemas.xmlsoap.org/wsdl/";
    public static final java.lang.String SOAPENV_XMLNS = "http://schemas.xmlsoap.org/soap/envelope/";
    public static final java.lang.String SOAPENC_XMLNS = "http://schemas.xmlsoap.org/soap/encoding/";
    private static final java.lang.String SOAP_CONTENT_TYPE = "text/xml; charset=\"utf-8\"";
    public static java.lang.String DEF_EL = "definitions";
    public static java.lang.String SERVICE_EL = "service";
    public static java.lang.String SOAPADDRS_EL = "soap:address";
    public static java.lang.String SOAPOPER_EL = "soap:operation";
    public static java.lang.String OPERATION_EL = "operation";
    public static java.lang.String BINDING_EL = "binding";
    public static java.lang.String PART_EL = "part";
    public static java.lang.String MESSAGE_EL = "message";
    public static java.lang.String PORT_EL = "port";
    public static java.lang.String PORTTYPE_EL = "portType";
    public static java.lang.String INPUT_EL = "input";
    public static java.lang.String OUTPUT_EL = "output";
    public static java.lang.String NAME_ATTR = "name";
    public static java.lang.String ROOTNS_ATTR = "targetNamespace";
    public static java.lang.String SOAPACTION_ATTR = "soapAction";
    public static java.lang.String LOCATION_ATTR = "location";
    public static java.lang.String WSDLNS_ATTR = "xmlns";
    public static java.lang.String METHODNS_ATTR = "namespace";
    public static java.lang.String PARAMETERORDER_ATTR = "parameterOrder";
    public static java.lang.String MESSAGE_ATTR = "message";
    public static java.lang.String TYPE_ATTR = "type";
    public static java.lang.String SOAPBODY_EL = "SOAP-ENV:Body";
    public static java.lang.String SOAPENV_EL = "SOAP-ENV:Envelope";
    public static java.lang.String SOAPFAULT_EL = "SOAP-ENV:Fault";
    java.lang.StringBuffer xmlContent;
    public static final int exec_status = 0;
    public static final int exec_response = 1;
    public static final int exec_duration = 2;
    public static final int exec_fault = 3;
    private final int iRequest = 0;
    private final int iResponseHeaders = 1;
    private final int iResponseBody = 2;
    private final int ntlmResponseSize = 3;

    public SoapRpc()
    {
        transmission = 0;
        xmlContent = new StringBuffer();
    }

    public static java.lang.String stripEncoding(java.lang.String s)
    {
        java.lang.String s1 = s.substring(s.indexOf("?>"));
        return "<?xml version=\"1.0\"  " + s1;
    }

    private java.lang.String getFaultString(org.w3c.dom.Node node)
    {
        java.lang.String s = "";
        jgl.Array array = new Array();
        try
        {
            com.dragonflow.Utils.XSLUtils.findElements(node, SOAPENV_EL + "." + SOAPBODY_EL + "." + SOAPFAULT_EL, array);
            java.util.Enumeration enumeration = array.elements();
            while (enumeration.hasMoreElements()) {
                org.w3c.dom.Node node1 = (org.w3c.dom.Node)enumeration.nextElement();
                if(node1.getNodeName().equals(SOAPFAULT_EL))
                {
                    org.w3c.dom.NodeList nodelist = node1.getChildNodes();
                    int i = 0;
                    while(i < nodelist.getLength()) 
                    {
                        s = s + nodelist.item(i).getNodeName();
                        s = s + ": " + nodelist.item(i).getFirstChild().getNodeValue() + " ";
                        i++;
                    }
                }
            }
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
        }
        return s;
    }

    private java.lang.String getAttrValue(org.w3c.dom.Node node, java.lang.String s, java.lang.String s1, java.lang.StringBuffer stringbuffer)
    {
        jgl.Array array = new Array();
        java.lang.String s2 = null;
        try
        {
            if(s.length() > 0)
            {
                com.dragonflow.Utils.XSLUtils.findElements(node, s, array);
                java.util.Enumeration enumeration = array.elements();
                org.w3c.dom.Node node1 = (org.w3c.dom.Node)enumeration.nextElement();
                s2 = ((COM.datachannel.xml.om.Element)node1).getAttribute(s1);
            } else
            {
                s2 = ((COM.datachannel.xml.om.Element)node).getAttribute(s1);
            }
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            stringbuffer.append(" Error getting the attribute. Check wsdl file ");
            stringbuffer.append(exception.toString() + " " + s);
        }
        return s2;
    }

    public java.lang.Object[] execute(java.lang.String s, java.util.Vector vector, java.lang.String s1, java.lang.String as[], java.lang.String s2, java.lang.String s3, java.lang.String s4, 
            java.lang.String s5, java.lang.String s6, java.lang.String s7, java.lang.String s8, java.lang.String s9, java.lang.String s10, java.lang.String s11, 
            java.lang.String s12, java.lang.StringBuffer stringbuffer, java.lang.String s13, boolean flag)
        throws java.io.IOException
    {
        java.lang.StringBuffer stringbuffer1 = new StringBuffer();
        java.lang.String s14 = "";
        java.lang.String s16 = "\"" + s5 + "\"";
        java.lang.String s15;
        long al[];
        try
        {
            java.lang.StringBuffer stringbuffer2 = new StringBuffer();
            com.dragonflow.Utils.RawXmlWriter rawxmlwriter = new RawXmlWriter(stringbuffer2);
            rawxmlwriter.writeSOAPHeader(new Array());
            writeRequest(rawxmlwriter, s, vector, as, s4, flag);
            com.dragonflow.Utils.SoapRpc.status("SOAP req: " + stringbuffer2.toString());
            java.lang.String as1[] = new java.lang.String[3];
            al = httpPost(s7, s8, s9, s10, s11, s12, s13, s16, s6, stringbuffer2.toString(), as1);
            stringbuffer1.append(as1[2]);
            stringbuffer.append("(REQUEST)\n\n" + com.dragonflow.Utils.TextUtils.encodeArgs(as1[0]) + "\n\n");
            stringbuffer.append("(RESPONSE)\n\n" + as1[1] + "\n" + com.dragonflow.Utils.TextUtils.encodeArgs(as1[2]));
            s15 = stringbuffer1.toString();
            com.dragonflow.Utils.SoapRpc.status("SOAP resp: " + s15);
            boolean flag1 = true;
            if(al[0] < 200L || al[0] > 299L || al[0] == 204L)
            {
                flag1 = false;
            } else
            if(s15.indexOf("<?xml version=") < 0)
            {
                flag1 = false;
            }
            if(flag1)
            {
                try
                {
                    COM.datachannel.xml.om.Document document = new Document();
                    document.loadXML(com.dragonflow.Utils.SoapRpc.stripEncoding(s15));
                    s14 = getFaultString(document.getDocumentElement());
                }
                catch(java.lang.Exception exception1)
                {
                    exception1.printStackTrace();
                    al[0] = com.dragonflow.StandardMonitor.URLMonitor.kXMLFormatError;
                    com.dragonflow.Log.LogManager.log("Error", "SoapRpc.execute: " + exception1.getMessage());
                }
            }
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            throw new IOException(exception.getMessage());
        }
        java.lang.Object aobj[] = new java.lang.Object[4];
        aobj[0] = new Long(al[0]);
        aobj[1] = s15;
        aobj[2] = new Long(al[1]);
        aobj[3] = s14;
        return aobj;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param stringbuffer
     * @param stringbuffer1
     * @return
     */
    public static int getWSDLContent(java.lang.String s, java.lang.StringBuffer stringbuffer, java.lang.StringBuffer stringbuffer1)
    {
        org.apache.commons.httpclient.HttpClient httpclient;
        org.apache.commons.httpclient.methods.GetMethod getmethod;
        char c = '\310';
        httpclient = new HttpClient();
        getmethod = new GetMethod(s);
        jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
        java.lang.String s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_URLUserAgent");
        
        int i;
        try {
        if(s1.length() > 0)
        {
            getmethod.setRequestHeader("User-Agent", s1);
        }
        i = httpclient.executeMethod(getmethod);
        com.dragonflow.Utils.SoapRpc.status("HTTP Status: " + i);
        stringbuffer.append(getmethod.getResponseBodyAsString());
        getmethod.releaseConnection();
        }
        catch (RuntimeException e) {
            getmethod.releaseConnection();
            throw e;
        }
        catch (Exception exception) {
        i = 500;
        stringbuffer1.append(exception.toString());
        com.dragonflow.Log.LogManager.log("Error", "SoapRpc.getWSDLContent: " + exception.getMessage());
        exception.printStackTrace();
        getmethod.releaseConnection();
        }
        return i;
    }

    private void writeRequest(com.dragonflow.Utils.RawXmlWriter rawxmlwriter, java.lang.String s, java.util.Vector vector, java.lang.String as[], java.lang.String s1, boolean flag)
    {
        java.lang.String s2 = "ns1:" + s;
        try
        {
            rawxmlwriter.startElement(SOAPBODY_EL);
            if(s1.length() > 0)
            {
                if(flag)
                {
                    rawxmlwriter.startElement(s + " xmlns=\"" + s1 + "\"");
                } else
                {
                    rawxmlwriter.startElement(s2 + " xmlns:ns1=\"" + s1 + "\"");
                }
            } else
            {
                rawxmlwriter.startElement(s);
            }
            int i = vector.size();
            for(int j = 0; j < i; j++)
            {
                java.lang.String s5 = ((java.lang.String)vector.elementAt(j)).trim();
                int k = as[j].indexOf('(');
                if(k > 0)
                {
                    java.lang.String s3 = as[j].substring(0, k).trim();
                    int l = as[j].indexOf(')');
                    java.lang.String s4 = as[j].substring(k + 1, l);
                    if(s5.length() <= 0)
                    {
                        rawxmlwriter.emptyElement(s3);
                    } else
                    {
                        rawxmlwriter.startElement(s3 + " xsi:type=\"xsd:" + s4 + "\"");
                        rawxmlwriter.write(s5);
                        rawxmlwriter.endElement(s3);
                    }
                } else
                {
                    rawxmlwriter.write(s5);
                }
            }

            if(s1.length() > 0 && !flag)
            {
                rawxmlwriter.endElement(s2);
            } else
            {
                rawxmlwriter.endElement(s);
            }
            rawxmlwriter.endElement(SOAPBODY_EL);
            rawxmlwriter.endElement(SOAPENV_EL);
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            com.dragonflow.Log.LogManager.log("Error", "SoapRpc.writeRequest exception: " + exception.getMessage());
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param s1
     * @param s2
     * @param s3
     * @param s4
     * @param s5
     * @param s6
     * @param s7
     * @param s8
     * @param s9
     * @param as
     * @return
     * @throws java.lang.Exception
     */
    public long[] httpPost(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, java.lang.String s5, java.lang.String s6, 
            java.lang.String s7, java.lang.String s8, java.lang.String s9, java.lang.String as[])
        throws java.lang.Exception
    {
        long al[];
        org.apache.commons.httpclient.HttpClient httpclient;
        org.apache.commons.httpclient.methods.PostMethod postmethod;
        al = new long[2];
        com.dragonflow.Utils.SoapRpc.status("Doing Web Service HTTP Post auth with credentials: " + s1 + "/" + s2 + "/" + s6);
        if(s6 == null)
        {
            s6 = "";
        }
        httpclient = new HttpClient();
        httpclient.getState().setAuthenticationPreemptive(true);
        if(s1 == null || s1.length() == 0)
        {
            jgl.HashMap hashmap = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
            s1 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_defaultAuthUsername");
            if(s1.length() > 0)
            {
                if(s1.indexOf("\\") != -1)
                {
                    java.lang.String as1[] = (new String(s1)).split("\\\\");
                    if(as1.length == 2)
                    {
                        s6 = as1[0];
                        s1 = as1[1];
                    }
                }
                s2 = com.dragonflow.Utils.TextUtils.getValue(hashmap, "_defaultAuthPassword");
                httpclient.getState().setAuthenticationPreemptive(false);
            }
        }
        if(s1 != null && s1.length() > 0)
        {
            java.lang.String s10;
            try
            {
                java.net.InetAddress inetaddress = java.net.InetAddress.getLocalHost();
                s10 = inetaddress.getHostName();
            }
            catch(java.net.UnknownHostException unknownhostexception)
            {
                s10 = "";
                com.dragonflow.Log.LogManager.log("Error", "SoapRPC.httpPost is unable to get local host");
                unknownhostexception.printStackTrace();
            }
            org.apache.commons.httpclient.NTCredentials ntcredentials = new NTCredentials(s1, s2, s10, s6);
            httpclient.getState().setCredentials(null, null, ntcredentials);
            com.dragonflow.Utils.SoapRpc.status("Username found and credentials being set");
        }
        java.net.URL url = null;
        if(s3.length() > 0)
        {
            try
            {
                url = new URL(s3);
            }
            catch(java.lang.Exception exception)
            {
                com.dragonflow.Log.LogManager.log("Error", "Invalid proxy server specified: " + s3);
            }
        }
        if(url != null)
        {
            int i = url.getPort();
            org.apache.commons.httpclient.HostConfiguration hostconfiguration = httpclient.getHostConfiguration();
            hostconfiguration.setProxy(url.getHost(), i >= 0 ? i : 80);
            org.apache.commons.httpclient.UsernamePasswordCredentials usernamepasswordcredentials = new UsernamePasswordCredentials(s4, s5);
            httpclient.getState().setProxyCredentials(null, null, usernamepasswordcredentials);
            com.dragonflow.Utils.SoapRpc.status("Proxying at: " + url.toString() + " / " + s4 + " / " + s5);
        }
        postmethod = new PostMethod(s);
        postmethod.setDoAuthentication(true);
        postmethod.setRequestHeader("Content-type", "text/xml; charset=\"utf-8\"");
        postmethod.setRequestHeader("SOAPAction", s7);
        if(s8.length() > 0)
        {
            postmethod.setRequestHeader("User-Agent", s8);
        }
        postmethod.setRequestBody(s9);
        
        try {
        long l = java.lang.System.currentTimeMillis();
        int j = httpclient.executeMethod(postmethod);
        long l1 = java.lang.System.currentTimeMillis();
        as[0] = getRequestString(postmethod);
        as[1] = getResponseHeaders(postmethod);
        as[2] = postmethod.getResponseBodyAsString();
        al[0] = j;
        al[1] = l1 - l;
        postmethod.releaseConnection();
        }
        catch (RuntimeException exception1) {
        postmethod.releaseConnection();
        throw exception1;
        }
        com.dragonflow.Utils.SoapRpc.status("SOAP Request: " + as[0]);
        com.dragonflow.Utils.SoapRpc.status("SOAP Response: " + as[2]);
        return al;
    }

    private java.lang.String getRequestString(org.apache.commons.httpclient.methods.PostMethod postmethod)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        java.lang.String s = "HTTP/" + (postmethod.isHttp11() ? "1.1" : "1.0");
        stringbuffer.append(postmethod.getName() + " " + postmethod.getPath() + " " + s + "\n");
        org.apache.commons.httpclient.Header aheader[] = postmethod.getRequestHeaders();
        for(int i = 0; i < aheader.length; i++)
        {
            stringbuffer.append(aheader[i].toString());
        }

        stringbuffer.append("\n");
        try
        {
            stringbuffer.append(ParameterUtils.getRequestBodyAsString(postmethod.getParameters()));
        }
        catch(java.lang.Exception exception)
        {
            exception.printStackTrace();
            com.dragonflow.Log.LogManager.log("Error", exception.toString());
        }
        return stringbuffer.toString();
    }

    private java.lang.String getResponseHeaders(org.apache.commons.httpclient.methods.PostMethod postmethod)
    {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append(postmethod.getStatusLine().toString() + "\n");
        org.apache.commons.httpclient.Header aheader[] = postmethod.getResponseHeaders();
        for(int i = 0; i < aheader.length; i++)
        {
            stringbuffer.append(aheader[i].toString());
        }

        return stringbuffer.toString();
    }

    private static void status(java.lang.String s)
    {
        if(debug)
        {
            java.lang.System.out.println(s);
        }
    }

    static 
    {
        java.lang.String s = java.lang.System.getProperty("SoapRpc.debug", "false");
        if(s.equalsIgnoreCase("true"))
        {
            debug = true;
        }
    }
}
