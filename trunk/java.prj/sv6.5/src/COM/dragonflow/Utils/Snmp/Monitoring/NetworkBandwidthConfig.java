/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Utils.Snmp.Monitoring;

import java.util.Hashtable;
import java.util.Vector;

// Referenced classes of package COM.dragonflow.Utils.Snmp.Monitoring:
// Device, Metric

public class NetworkBandwidthConfig {

    private static final java.lang.String DEVICE = "device";

    private static final java.lang.String IDENTIFIER = "identifier";

    private static final java.lang.String DISPLAY_NAME = "displayName";

    private static final java.lang.String DEVICE_METRICS = "deviceMetrics";

    private static final java.lang.String METRIC = "metric";

    private static final java.lang.String OID = "OID";

    private static final java.lang.String NAME = "metricName";

    private static final java.lang.String NAME_OID = "metricNameOID";

    private static final java.lang.String UNITS = "units";

    private static final java.lang.String REAL_TIME = "realTime";

    private static final java.lang.String SAME_GRAPH = "sameGraph";

    private static final java.lang.String MULTIPLE_INSTANCES = "multipleInstances";

    public static final java.lang.String configFilePath;

    private static int maxProperties = 25;

    private static org.w3c.dom.Document configDocument;

    private static java.util.Hashtable deviceIDToDisplayName;

    private static java.util.Hashtable deviceIDToNode;

    public NetworkBandwidthConfig() {
    }

    public static int getMaxProperties() {
        return maxProperties;
    }

    public static java.util.Vector getIDsandDisplayNames() {
        java.util.Vector vector = new Vector();
        java.lang.String s;
        for (java.util.Enumeration enumeration = deviceIDToDisplayName.keys(); enumeration.hasMoreElements(); vector.add(deviceIDToDisplayName.get(s))) {
            s = (java.lang.String) enumeration.nextElement();
            vector.add(s);
        }

        return vector;
    }

    public static COM.dragonflow.Utils.Snmp.Monitoring.Device getDeviceInstance(java.lang.String s, COM.dragonflow.Utils.Snmp.SNMPSession snmpsession, long l) {
        COM.dragonflow.Utils.Snmp.Monitoring.Device device = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getDeviceInstance(s);
        if (device != null) {
            device.setSession(snmpsession);
            device.setRealTimeDataWindow(l);
        }
        return device;
    }

    public static COM.dragonflow.Utils.Snmp.Monitoring.Device getDeviceInstance(java.lang.String s) {
        org.w3c.dom.Node node = (org.w3c.dom.Node) deviceIDToNode.get(s);
        if (node == null) {
            return null;
        }
        java.lang.String s1 = null;
        java.lang.String s2 = null;
        java.util.Vector vector = null;
        org.w3c.dom.NodeList nodelist = node.getChildNodes();
        for (int i = 0; i < nodelist.getLength(); i ++) {
            org.w3c.dom.Node node1 = nodelist.item(i);
            if (node1.getNodeName().equals("identifier")) {
                s1 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node1);
                continue;
            }
            if (node1.getNodeName().equals("displayName")) {
                s2 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node1);
                continue;
            }
            if (node1.getNodeName().equals("deviceMetrics")) {
                vector = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.createMetricsFromXML(node1);
            }
        }

        if (s1 != null && s2 != null && vector != null) {
            return new Device(s1, s2, vector);
        } else {
            return null;
        }
    }

    private static java.util.Vector createMetricsFromXML(org.w3c.dom.Node node) {
        java.util.Vector vector = new Vector();
        org.w3c.dom.NodeList nodelist = node.getChildNodes();
        java.lang.String s1;
        java.lang.String s2;
        java.lang.String s3;
        java.lang.String s4;
        java.lang.String s = s1 = s2 = s3 = s4 = null;
        boolean flag1;
        boolean flag = flag1 = false;
        for (int i = 0; i < nodelist.getLength(); i ++) {
            org.w3c.dom.Node node1 = nodelist.item(i);
            if (!node1.getNodeName().equalsIgnoreCase("metric")) {
                continue;
            }
            org.w3c.dom.NodeList nodelist1 = node1.getChildNodes();
            for (int j = 0; j < nodelist1.getLength(); j ++) {
                org.w3c.dom.Node node2 = nodelist1.item(j);
                if (node2.getNodeName().equals("OID")) {
                    s = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2);
                    continue;
                }
                if (node2.getNodeName().equals("metricName")) {
                    s1 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2);
                    continue;
                }
                if (node2.getNodeName().equals("metricNameOID")) {
                    s2 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2);
                    continue;
                }
                if (node2.getNodeName().equals("units")) {
                    s3 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2);
                    continue;
                }
                if (node2.getNodeName().equals("realTime")) {
                    flag = "true".equalsIgnoreCase(COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2));
                    continue;
                }
                if (node2.getNodeName().equals("sameGraph")) {
                    flag1 = "true".equalsIgnoreCase(COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2));
                    continue;
                }
                if (node2.getNodeName().equals("multipleInstances")) {
                    s4 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node2);
                }
            }

            COM.dragonflow.Utils.Snmp.Monitoring.Metric metric = new Metric(s, s1, s2, s3, s4, flag, flag1);
            vector.add(metric);
        }

        return vector;
    }

    public static java.lang.String getNodesTextChild(org.w3c.dom.Node node) {
        if (node.getFirstChild().getNodeType() != 3) {
            return "";
        } else {
            return node.getFirstChild().getNodeValue();
        }
    }

    static {
        configFilePath = COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.applications" + java.io.File.separator + "netbandwidth.xml";
        configDocument = null;
        javax.xml.parsers.DocumentBuilderFactory documentbuilderfactory = javax.xml.parsers.DocumentBuilderFactory.newInstance();
        try {
            javax.xml.parsers.DocumentBuilder documentbuilder = documentbuilderfactory.newDocumentBuilder();
            configDocument = documentbuilder.parse(configFilePath);
        } catch (org.xml.sax.SAXException saxexception) {
            COM.dragonflow.Log.LogManager.log("Error", "Error parsing Network Bandwidth config file " + configFilePath + ": " + saxexception.getMessage());
        } catch (java.io.IOException ioexception) {
            COM.dragonflow.Log.LogManager.log("Error", "Error parsing Network Bandwidth config file " + configFilePath + ": " + ioexception.getMessage());
        } catch (javax.xml.parsers.ParserConfigurationException parserconfigurationexception) {
            COM.dragonflow.Log.LogManager.log("Error", "Parser configuration error while parsing Network Bandwidth config file " + configFilePath + ": " + parserconfigurationexception.getMessage());
        }
        deviceIDToDisplayName = new Hashtable();
        deviceIDToNode = new Hashtable();
        org.w3c.dom.NodeList nodelist = configDocument.getElementsByTagName("device");
        int i = nodelist.getLength();
        for (int j = 0; j < i; j ++) {
            org.w3c.dom.Node node = nodelist.item(j);
            org.w3c.dom.NodeList nodelist1 = node.getChildNodes();
            java.lang.String s = "";
            java.lang.String s1 = "";
            for (int l = 0; l < nodelist1.getLength(); l ++) {
                org.w3c.dom.Node node1 = nodelist1.item(l);
                if (node1.getNodeName().equals("identifier")) {
                    s = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node1);
                    continue;
                }
                if (node1.getNodeName().equals("displayName")) {
                    s1 = COM.dragonflow.Utils.Snmp.Monitoring.NetworkBandwidthConfig.getNodesTextChild(node1);
                }
            }

            if (!"".equals(s) && !"".equals(s1)) {
                deviceIDToDisplayName.put(s, s1);
                deviceIDToNode.put(s, node);
            }
        }

        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        int k = COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_NetworkBandwidthMaxCustomCounters"));
        if (k > 0) {
            maxProperties = k;
        }
    }
}
