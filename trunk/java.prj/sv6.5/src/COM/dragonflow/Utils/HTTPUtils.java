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
import jgl.HashMap;
import COM.dragonflow.Properties.HashMapOrdered;

// Referenced classes of package COM.dragonflow.Utils:
// TextUtils

public class HTTPUtils {

    public static jgl.Array locations;

    public static jgl.HashMap locationMap = new HashMap();

    public static final java.lang.String DEFAULT_LOCATION_SPEC = "this_server,this server,";

    public HTTPUtils() {
    }

    public static java.lang.String getLocationID(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 0);
    }

    public static java.lang.String getLocationName(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 1);
    }

    public static java.lang.String getLocationURL(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 2);
    }

    public static java.lang.String getPingURL(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 3);
    }

    public static java.lang.String getTraceURL(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 4);
    }

    public static java.lang.String getPortURL(java.lang.String s) {
        return COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, 5);
    }

    public static int getDisplayOrder(java.lang.String s) {
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        int i = COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_URLLocationComponent"));
        if (i <= 0) {
            i = 6;
        }
        java.lang.String s1 = COM.dragonflow.Utils.HTTPUtils.getLocationPart(s, i);
        if (s1 == null || s1.equals("") || s1.equals("0")) {
            return 1;
        } else {
            return (new Integer(s1)).intValue();
        }
    }

    public static java.lang.String getLocationNameByID(java.lang.String s) {
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = locations.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.HTTPUtils.getLocationID(s2))) {
            s1 = COM.dragonflow.Utils.HTTPUtils.getLocationName(s2);
            break;
            }
        } 
        return s1;
    }

    public static java.lang.String locationsHTML(java.lang.String s, COM.dragonflow.HTTP.HTTPRequest httprequest) {
        java.lang.StringBuffer stringbuffer = new StringBuffer();
        if (locations.size() > 1) {
            stringbuffer.append("Location: <SELECT name=location size=6>\n");
            java.util.Enumeration enumeration = locations.elements();
            COM.dragonflow.Properties.HashMapOrdered hashmapordered = new HashMapOrdered(true);
            int i;
            int j;
            for (i = 0; enumeration.hasMoreElements(); i = java.lang.Math.max(i, j)) {
                java.lang.String s1 = (java.lang.String) enumeration.nextElement();
                java.lang.String s3 = COM.dragonflow.Utils.HTTPUtils.getLocationID(s1);
                j = COM.dragonflow.Utils.HTTPUtils.getDisplayOrder(s1);
                if (j >= 0) {
                    hashmapordered.add(new Integer(j), s1);
                    continue;
                }
                COM.dragonflow.SiteView.SiteViewGroup siteviewgroup = COM.dragonflow.SiteView.SiteViewGroup.currentSiteView();
                COM.dragonflow.SiteView.MonitorGroup monitorgroup = (COM.dragonflow.SiteView.MonitorGroup) siteviewgroup.getElement(httprequest.getValue("group"));
                java.lang.String s5 = monitorgroup.getSetting("_allowInvalidNode");
                if (s5 != null && s5.indexOf(s3) >= 0) {
                    hashmapordered.add(new Integer(0), s1);
                }
            }

            for (int k = 0; k <= i; k ++) {
                java.lang.Integer integer = new Integer(k);
                java.lang.String s2;
                java.lang.String s6;
                for (java.util.Enumeration enumeration1 = hashmapordered.values(integer); enumeration1.hasMoreElements(); stringbuffer.append("<option " + s6 + " value=" + COM.dragonflow.Utils.HTTPUtils.getLocationID(s2) + ">"
                        + COM.dragonflow.Utils.HTTPUtils.getLocationName(s2) + "</option>\n")) {
                    s6 = "";
                    s2 = (java.lang.String) enumeration1.nextElement();
                    java.lang.String s4 = COM.dragonflow.Utils.HTTPUtils.getLocationID(s2);
                    if (s.indexOf(s4) >= 0) {
                        s6 = "SELECTED";
                    }
                    if (s.length() == 0 && s4.indexOf("this_server") >= 0) {
                        s6 = "SELECTED";
                    }
                }

            }

            stringbuffer.append("</SELECT><P>\n");
        }
        return stringbuffer.toString();
    }

    public static java.lang.String getTraceURLByID(java.lang.String s) {
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = locations.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.HTTPUtils.getLocationID(s2))) {
            s1 = COM.dragonflow.Utils.HTTPUtils.getTraceURL(s2);
            break;
            }
        } 
        return s1;
    }

    public static java.lang.String getPingURLByID(java.lang.String s) {
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = locations.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.HTTPUtils.getLocationID(s2))) {
            s1 = COM.dragonflow.Utils.HTTPUtils.getPingURL(s2);
            break;
            }
        } 
        return s1;
    }

    public static java.lang.String getLocationIDByURL(java.lang.String s) {
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = locations.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.HTTPUtils.getLocationURL(s2))) {
            s1 = COM.dragonflow.Utils.HTTPUtils.getLocationID(s2);
            break;
            }
        } 
        return s1;
    }

    public static java.lang.String getLocationURLByID(java.lang.String s) {
        java.lang.String s1 = "";
        java.util.Enumeration enumeration = locations.elements();
        while (enumeration.hasMoreElements()) {
            java.lang.String s2 = (java.lang.String) enumeration.nextElement();
            if (s.equals(COM.dragonflow.Utils.HTTPUtils.getLocationID(s2))) {
            s1 = COM.dragonflow.Utils.HTTPUtils.getLocationURL(s2);
            break;
            }
        } 
        return s1;
    }

    public static java.lang.String getLocationPart(java.lang.String s, int i) {
        jgl.HashMap hashmap = COM.dragonflow.SiteView.MasterConfig.getMasterConfig();
        int j = COM.dragonflow.Utils.TextUtils.toInt(COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_URLLocationComponent"));
        if (j <= 0) {
            j = 6;
        }
        java.lang.String as[] = new java.lang.String[j + 1];
        int k = COM.dragonflow.Utils.TextUtils.splitChar(s, ',', as);
        if (i < k) {
            return as[i];
        } else {
            return "";
        }
    }

    public static java.lang.String hostFromURL(java.lang.String s) {
        java.lang.String s1 = "";
        if (s.length() > 0) {
            int i = s.indexOf("://");
            if (i > 0) {
                i += 3;
                int j = s.indexOf(":", i);
                if (j < 0) {
                    j = s.indexOf('/', i);
                }
                if (j < 0) {
                    j = s.length();
                }
                s1 = s.substring(i, j);
            }
        }
        return s1;
    }

    public static java.lang.String getHTTPPart(java.lang.String s, boolean flag) {
        int i = s.length();
        int j = 0;
        do {
            int k = s.indexOf('\n', j);
            if (k == -1) {
                break;
            }
            java.lang.String s1 = s.substring(j, k).trim();
            if (s1.length() == 0) {
                i = k + 1;
                break;
            }
            j = k + 1;
        } while (true);
        if (flag) {
            return s.substring(0, i);
        } else {
            return s.substring(i);
        }
    }

    static {
        locations = new Array();
        locations.add("this_server,this server,");
    }
}
