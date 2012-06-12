/*
 * 
 * Created on 2005-3-9 18:55:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Utils.Snmp.Monitoring;

import java.util.Date;

public class Metric {

    private static final java.lang.String ALL = "all";

    private static final java.lang.String MIN = "min";

    private static final java.lang.String MAX = "max";

    private static final java.lang.String AVERAGE = "average";

    private java.lang.String oid;

    private java.lang.String name;

    private java.lang.String nameOid;

    private java.lang.String units;

    private boolean isRealTime;

    private boolean onSameGraph;

    private java.lang.String multipleInstances;

    private long time;

    private com.dragonflow.Utils.Snmp.SNMPSession session;

    private java.lang.String values[];

    private java.lang.String perInstanceNames[];

    private long minValue;

    private long maxValue;

    private long averageValue;

    public Metric(java.lang.String s, java.lang.String s1, java.lang.String s2, java.lang.String s3, java.lang.String s4, boolean flag, boolean flag1) {
        oid = s;
        name = s1;
        nameOid = s2;
        units = s3;
        multipleInstances = s4;
        isRealTime = flag;
        onSameGraph = flag1;
    }

    public void setSession(com.dragonflow.Utils.Snmp.SNMPSession snmpsession) {
        session = snmpsession;
    }

    public boolean isRealTime() {
        return isRealTime;
    }

    public java.lang.String getMultipleInstances() {
        return multipleInstances;
    }

    public java.lang.String getName() {
        return name;
    }

    public java.lang.String getLabel(int i) {
        if (perInstanceNames != null && perInstanceNames.length > i) {
            return perInstanceNames[i];
        }
        if (values != null && values.length > 1) {
            return name + "Instance #" + i + " (" + units + ")";
        } else {
            return name + " (" + units + ")";
        }
    }

    public java.lang.String getOid() {
        return oid;
    }

    public boolean isOnSameGraph() {
        return onSameGraph;
    }

    public java.lang.String getUnits() {
        return units;
    }

    public long getTime() {
        return time;
    }

    public java.lang.String[] getValues() {
        if (multipleInstances.equalsIgnoreCase("all")) {
            return values;
        }
        java.lang.String as[] = new java.lang.String[1];
        if (multipleInstances.equalsIgnoreCase("min")) {
            as[0] = java.lang.Long.toString(minValue);
        } else if (multipleInstances.equalsIgnoreCase("max")) {
            as[0] = java.lang.Long.toString(maxValue);
        } else if (multipleInstances.equalsIgnoreCase("average")) {
            as[0] = java.lang.Long.toString(averageValue);
        }
        return as;
    }

    public boolean refresh(java.lang.StringBuffer stringbuffer) {
        com.dragonflow.Utils.Snmp.SNMPVariableBinding asnmpvariablebinding[] = session.getTableColumn(oid);
        java.lang.String s = session.getError();
        if (s != null && !s.equals("") && !s.equals("noError")) {
            stringbuffer.append(s);
            return false;
        }
        if (nameOid != null) {
            retrieveNames(asnmpvariablebinding.length);
        }
        time = (new Date()).getTime() / 1000L;
        if (values == null) {
            values = new java.lang.String[asnmpvariablebinding.length];
        }
        boolean flag = false;
        long l = 0L;
        for (int i = 0; i < asnmpvariablebinding.length; i ++) {
            values[i] = asnmpvariablebinding[i].getValue();
            long l1 = 0L;
            try {
                l1 = java.lang.Long.parseLong(values[i]);
            } catch (java.lang.NumberFormatException numberformatexception) {
                if (!flag || multipleInstances.equalsIgnoreCase("min") || multipleInstances.equalsIgnoreCase("max") || multipleInstances.equalsIgnoreCase("average")) {
                    com.dragonflow.Log.LogManager.log("Error", "Could not calculate " + multipleInstances + " for metric with OID: " + oid);
                    flag = true;
                    continue;
                }
            }
            l += l1;
            if (l1 < minValue) {
                minValue = l1;
            }
            if (l1 > maxValue) {
                maxValue = l1;
            }
        }

        averageValue = computeAverage(l, asnmpvariablebinding.length);
        return true;
    }

    public java.lang.String[] getInstanceOIDs(java.lang.StringBuffer stringbuffer) {
        com.dragonflow.Utils.Snmp.SNMPVariableBinding asnmpvariablebinding[] = session.getTableColumn(oid);
        java.lang.String s = session.getError();
        if (s != null && !s.equals("") && !s.equals("noError")) {
            stringbuffer.append(s);
            return null;
        }
        java.lang.String as[] = new java.lang.String[asnmpvariablebinding.length];
        for (int i = 0; i < asnmpvariablebinding.length; i ++) {
            as[i] = asnmpvariablebinding[i].getOIDAsString();
        }

        return as;
    }

    public java.lang.String[] getInstanceNames(java.lang.StringBuffer stringbuffer) {
        com.dragonflow.Utils.Snmp.SNMPVariableBinding asnmpvariablebinding[] = session.getTableColumn(oid);
        if (asnmpvariablebinding != null) {
            retrieveNames(asnmpvariablebinding.length);
            if (perInstanceNames != null && perInstanceNames.length > 0) {
                return perInstanceNames;
            }
            java.lang.String as[] = new java.lang.String[asnmpvariablebinding.length];
            for (int i = 0; i < as.length; i ++) {
                as[i] = getLabel(i);
            }

            return as;
        } else {
            return (new java.lang.String[] { name });
        }
    }

    private long computeAverage(long l, int i) {
        if (i > 0) {
            return l / (long) i;
        } else {
            return 0L;
        }
    }

    private void retrieveNames(int i) {
        session.formatOctetStrings = false;
        com.dragonflow.Utils.Snmp.SNMPVariableBinding asnmpvariablebinding[] = session.getTableColumn(nameOid);
        session.formatOctetStrings = true;
        java.lang.String s = session.getError();
        if (s != null && !s.equals("") && !s.equals("noError")) {
            java.lang.StringBuffer stringbuffer = new StringBuffer("Error retrieving metric names with OID: ");
            stringbuffer.append(oid).append(". Using default naming style: ").append(name).append(" instanceNum.");
            com.dragonflow.Log.LogManager.log("Error", stringbuffer.toString());
            setDefaultNames();
        } else if (asnmpvariablebinding.length != i) {
            java.lang.StringBuffer stringbuffer1 = new StringBuffer("Inequal number of metric names to instances with OID: ");
            stringbuffer1.append(oid).append(". Using default naming style: ").append(name).append(" instanceNum.");
            com.dragonflow.Log.LogManager.log("Error", stringbuffer1.toString());
            setDefaultNames();
        } else {
            if (perInstanceNames == null || perInstanceNames.length != asnmpvariablebinding.length) {
                perInstanceNames = new java.lang.String[asnmpvariablebinding.length];
            }
            for (int j = 0; j < perInstanceNames.length; j ++) {
                perInstanceNames[j] = asnmpvariablebinding[j].getValue() + " (" + units + ")";
            }

        }
    }

    private void setDefaultNames() {
        if (perInstanceNames == null || values == null || perInstanceNames.length != values.length) {
            if (values == null) {
                perInstanceNames = new java.lang.String[1];
                perInstanceNames[0] = name + " (" + units + ")";
                return;
            }
            perInstanceNames = new java.lang.String[values.length];
        }
        for (int i = 0; i < perInstanceNames.length; i ++) {
            perInstanceNames[i] = name + " " + i + " (" + units + ")";
        }

    }

    public int getNumRequests() {
        return nameOid == null ? 1 : 2;
    }
}
