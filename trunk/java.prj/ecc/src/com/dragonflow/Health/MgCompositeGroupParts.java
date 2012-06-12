/*
 * Created on 2005-3-10 22:16:20
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Health;

/**
 * Comment for <code></code>
 * 
 * @author
 * @version 0.0
 * 
 * 
 */

import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.Vector;

public abstract class MgCompositeGroupParts {

    java.lang.String parentName;

    java.lang.String parentGroupName;

    java.lang.String FileName;

    com.dragonflow.Health.MgCompositeGroupParts parentRef;

    static java.util.HashMap fileNames = new HashMap();

    static java.util.Vector monitorNames = new Vector();

    static java.util.Vector remoteMachines = new Vector();

    static java.util.Vector remoteNTMachines = new Vector();

    java.util.Vector messages;

    java.lang.String fileTitle;

    java.lang.String fileExtension;

    public MgCompositeGroupParts() {
        parentName = null;
        parentGroupName = null;
        FileName = null;
        parentRef = null;
        messages = new Vector();
    }

    public abstract void createHTML();

    public abstract void printSelf(int i);

    public abstract boolean errorCheck();

    public abstract boolean reportToErrorLog();

    public abstract boolean addMonitorNames();

    public java.util.HashMap getFileNameList() {
        return fileNames;
    }

    public java.util.Vector getMonitorNameList() {
        return monitorNames;
    }

    public void setParentRef(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts) {
        parentRef = mgcompositegroupparts;
    }

    public void addMessage(java.lang.String s) {
        messages.add(s);
    }

    public boolean add(com.dragonflow.Health.MgCompositeGroupParts mgcompositegroupparts) {
        return true;
    }

    public java.lang.Object check_TagEqualsValue(java.lang.String s, java.lang.Object obj, boolean flag, boolean flag1) {
        if (obj == null) {
            if (flag1) {
                return null;
            } else {
                java.lang.String s1 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' tag: '" + s + "' not found.";
                messages.add(s1);
                java.lang.System.out.println(s1);
                return "";
            }
        }
        if (obj instanceof java.lang.String) {
            if (obj.equals("")) {
                java.lang.String s2 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' tag: '" + s + "' value blank.";
                messages.add(s2);
                java.lang.System.out.println(s2);
            }
        } else if (obj instanceof java.util.Vector) {
            if (!flag) {
                java.lang.String s3 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' multiple tags: '" + s + "' found. values: '" + obj.toString() + "' in header or monitor. Invalid in this situation.";
                messages.add(s3);
                java.lang.System.out.println(s3);
                return ((java.util.Vector) obj).lastElement();
            }
        } else if (obj instanceof java.util.HashMap) {
            return "";
        }
        return obj;
    }

    public void setFileName(java.lang.String s) {
        if (s == null) {
            FileName = "";
        } else {
            FileName = s;
        }
        if (!FileName.equals("")) {
            fileNames.put(FileName, " ");
        }
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param hashmapduplicates
     * @return
     */
    public boolean checkAlerts(com.dragonflow.Properties.HashMapDuplicates hashmapduplicates) {
        java.lang.Object obj;
        obj = hashmapduplicates.get("_alertCondition");
        if (obj == null) {
            obj = new String("");
            return true;
        }
        try {
            check_TagEqualsValue("_alertCondition", obj, true, false);
            java.util.Vector vector = new Vector();
            if (obj instanceof java.lang.String) {
                vector.add(obj);
            } else if (obj instanceof java.util.Vector) {
                vector = (java.util.Vector) obj;
            }
            java.lang.Object obj1 = check_TagEqualsValue("_nextConditionID", hashmapduplicates.get("_nextConditionID"), false, false);
            java.lang.Integer integer = checkCountingNumber("_nextConditionID", obj1);
            java.util.Iterator iterator = vector.iterator();
            java.util.HashMap hashmap = new HashMap();
            while (iterator.hasNext()) {
                java.lang.String s1 = (java.lang.String) iterator.next();
                java.util.StringTokenizer stringtokenizer = new StringTokenizer(s1, "\t");
                if (stringtokenizer.hasMoreTokens()) {
                    java.lang.String s2 = stringtokenizer.nextToken();
                    java.lang.String s6 = "^(disabled and )?category eq '(error|warning|good)'(\\sand\\s\\S+\\s\\S+\\s(\\S|'.*')+)*$";
                    if (com.dragonflow.Utils.TextUtils.matchExpression(s2, "/" + s6 + "/") != 200) {
                        java.lang.String s9 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' alert condition: '" + s2 + "' does not match this pattern: " + s6;
                        messages.add(s9);
                        java.lang.System.out.println(s9);
                    }
                }
                if (stringtokenizer.hasMoreTokens()) {
                    java.lang.String s3 = stringtokenizer.nextToken();
                    java.lang.String s7 = "^(mailto|page|run|SNMPTrap|Sound|DatabaseAlert|disable|NTLogEvent|Post)\\s.+$";
                    if (com.dragonflow.Utils.TextUtils.matchExpression(s3, "/" + s7 + "/") != 200) {
                        java.lang.String s10 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' alert action: '" + s3 + "' does not match this pattern: " + s7;
                        messages.add(s10);
                        java.lang.System.out.println(s10);
                    }
                }
                if (stringtokenizer.hasMoreTokens()) {
                    java.lang.String s4 = stringtokenizer.nextToken();
                    java.lang.String s8 = s4;
                    java.lang.Integer integer1 = checkCountingNumber("alert id", s8);
                    if (integer1 != null) {
                        int i = integer1.intValue();
                        java.lang.String s13 = null;
                        s13 = (java.lang.String) hashmap.put(integer1, "");
                        if (s13 != null) {
                            java.lang.String s14 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' alert id: '" + integer1 + "' found multiple alert id tags with this same number in this frame( lines between #s).";
                            messages.add(s14);
                            java.lang.System.out.println(s14);
                        }
                        if (integer != null) {
                            int j = integer.intValue();
                            if (j < i) {
                                java.lang.String s15 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' _alertCondition alert id: '" + integer1 + "' greater than _nextConditionID: '" + integer + "' for this frame( lines between #s)";
                                messages.add(s15);
                                java.lang.System.out.println(s15);
                            }
                        }
                    }
                }
                if (stringtokenizer.hasMoreTokens()) {
                    java.lang.String s5 = stringtokenizer.nextToken();
                    java.util.StringTokenizer stringtokenizer1 = new StringTokenizer(s5, ",");
                    while (stringtokenizer1.hasMoreTokens()) {
                        java.lang.String s11 = stringtokenizer1.nextToken();
                        if (fileNames.get(s11) == null && !monitorNames.contains(s11)) {
                            java.lang.String s12 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' alert monitor(Name Format: 'mgName ID#') or group name: '" + s11 + "' not found.";
                            messages.add(s12);
                            java.lang.System.out.println(s12);
                        }
                    }
                }
            }
        } catch (java.lang.Exception exception) {
            java.lang.String s = "Logger error:  Exception: " + exception.getMessage();
            java.lang.System.out.println(s);
            com.dragonflow.Log.LogManager.log(s);
        }
        return true;
    }

    protected java.lang.Integer checkCountingNumber(java.lang.String s, java.lang.Object obj) {
        java.lang.Integer integer = null;
        if (obj instanceof java.lang.String) {
            java.lang.String s1 = (java.lang.String) obj;
            if (com.dragonflow.Utils.TextUtils.matchExpression(s1, "/^[1-9][0-9]{0,7}$/") == 200) {
                integer = new Integer(s1);
            } else {
                java.lang.String s2 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' " + s + ": '" + s1 + "' is not a counting number like 1,2,3... ";
                messages.add(s2);
                java.lang.System.out.println(s2);
            }
        }
        return integer;
    }

    protected void checkForDuplicatesAndGTNextID(java.lang.String s, java.lang.Integer integer, java.util.HashMap hashmap, java.lang.String s1, java.lang.Integer integer1) {
        if (integer != null) {
            int i = integer.intValue();
            java.lang.String s2 = (java.lang.String) hashmap.put(integer, "");
            if (s2 != null) {
                java.lang.String s3 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' " + s + ": '" + integer + "' found multiple id tags with this same number in this file. May indicate # missing between monitor frames.";
                messages.add(s3);
                java.lang.System.out.println(s3);
            }
            if (integer1 != null) {
                int j = integer1.intValue();
                if (j < i) {
                    java.lang.String s4 = "ERROR, " + fileTitle + ": '" + FileName + fileExtension + "' " + s + ": '" + integer + "' greater than " + s1 + ": '" + integer1 + "'";
                    messages.add(s4);
                    java.lang.System.out.println(s4);
                }
            }
        }
    }

}
