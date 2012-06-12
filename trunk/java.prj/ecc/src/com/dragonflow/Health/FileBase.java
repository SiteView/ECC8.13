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

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Vector;

import jgl.Array;
import jgl.HashMap;

public abstract class FileBase {
    public class DoCheck {

        public void setup() {
        }

        public java.lang.String expand(java.lang.String s, HealthNode healthnode, jgl.HashMap hashmap) {
            s = com.dragonflow.Utils.TextUtils.replaceString(s, "<group>", healthnode.fileName);
            if (healthnode.parent != null) {
                s = com.dragonflow.Utils.TextUtils.replaceString(s, "<parentFileName>", healthnode.parent.fileName);
            }
            return s;
        }

        public java.lang.String getSubVal(java.lang.String s, java.lang.String s1) {
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(s, " ");
            for (int i = 0; i < as.length; i ++) {
                if (as[i].startsWith(s1 + "=")) {
                    java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(as[i], "=");
                    if (as1.length > 1) {
                        return as1[1];
                    } else {
                        return "";
                    }
                }
            }

            return "";
        }

        public java.lang.String getValue(jgl.Array array, java.lang.String s, int i) {
            java.lang.String s1 = "";
            if (i >= array.size()) {
                return s1;
            }
            if (s.length() > 0) {
                return getSubVal((java.lang.String) array.at(i), s);
            } else {
                return (java.lang.String) array.at(i);
            }
        }

        public void processNode(HealthNode healthnode, CheckMe checkme) {
			
			if(checkme.operation==null||checkme.property==null)/*dingbing.xu add this line!!*/
				return;
			
            jgl.HashMap hashmap = new HashMap(false);
            for (int i = 0; i < healthnode.frames.size(); i ++) {
                jgl.HashMap hashmap1 = (jgl.HashMap) healthnode.frames.at(i);
                jgl.Array array = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap1, "_class");
                if (i == 0 && array.size() <= 0) {
                    if (checkme.operation!=null&&!checkme.operation.startsWith("subGroupR") && !checkme.operation.startsWith("monitorR")) { /*dingbing.xu add checkme.operation!=null*/
                        processFrame(healthnode, hashmap1, checkme);
                    }
                    continue;
                }
                if (checkme.operation!=null&&checkme.operation.equals("noDupValues") && (checkme.property.equals("_id") || checkme.property.equals("_name") && com.dragonflow.Utils.TextUtils.getSingleValue(masterConfig, "_healthCheckForUniqueMonitorNames").length() > 0)) {
                    jgl.Array array1 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap1, checkme.property);
                    if (array1.size() < 1) {
                        continue;
                    }
                    java.lang.String s = null;
                    java.lang.String s2 = checkme.property + array1.at(0);
                    s = (java.lang.String) hashmap.put(s2, "");
                    try {
                        java.lang.String s3 = checkme.errorMessage;
                        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "<tag>", checkme.property);
                        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "<group>", healthnode.fileName);
                        s3 = com.dragonflow.Utils.TextUtils.replaceString(s3, "<value>", (java.lang.String) array1.at(0));
                        ErrorMessage errormessage1 = new ErrorMessage("noDupValues", s3, healthnode.fileName);
                        checkCondition(s == null, errormessage1);
                        continue;
                    } catch (java.lang.Exception exception) {
                        java.lang.String s4 = "Error Message Failed chk.errorMessage: " + checkme.errorMessage + " chk.property is a tag: " + checkme.property + " value: " + (java.lang.String) array1.at(0) + " node.fileName: " + healthnode.fileName;
                        com.dragonflow.Log.LogManager.log("Error", s4);
                        java.lang.System.out.println(s4);
                        com.dragonflow.Utils.TextUtils.debugPrint("Exception: " + exception);
                        exception.printStackTrace();
                        com.dragonflow.Log.LogManager.log("Error", "FileBase.java is unhappy: " + com.dragonflow.Utils.FileUtils.stackTraceText(exception));
                    }
                    continue;
                }
                if (checkme.operation!=null&&checkme.operation.startsWith("group")) {
                    continue;
                }
                jgl.Array array2 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap1, "_class");
                if (healthnode.fileName.endsWith(".mg")) {
                    if (checkme.property!=null&&checkme.property.equals("_class") && (checkme.property.equals("subGroupRequired") || checkme.property.equals("monitorRequired"))) {
                        java.lang.String s1 = "_class tag missing in one of the group frames, cannot determine whether to check monitor or subGroup";
                        ErrorMessage errormessage = new ErrorMessage("required", s1, healthnode.fileName);
                        checkCondition(array2.size() > 0, errormessage);
                    }
                    if (array2.size() <= 0) {
                        continue;
                    }
                    if (array2.at(0).equals("SubGroup")) {
                        if (checkme.operation!=null&&!checkme.operation.startsWith("monitorR")) {
                            processFrame(healthnode, hashmap1, checkme);
                        }
                        continue;
                    }
                    if (checkme.operation!=null&&!checkme.operation.startsWith("subGroupR")) {
                        processFrame(healthnode, hashmap1, checkme);
                    }
                    continue;
                }
                if (checkme.operation!=null&&!checkme.operation.startsWith("subGroupR") && !checkme.operation.startsWith("monitorR")) {
                    processFrame(healthnode, hashmap1, checkme);
                }
            }

            for (int j = 0; j < healthnode.children.size(); j ++) {
                HealthNode healthnode1 = (HealthNode) healthnode.children.at(j);
                processNode(healthnode1, checkme);
            }

        }

        public void processTree(jgl.Array array) {
            for (int i = 0; i < array.size(); i ++) {
                CheckMe checkme = (CheckMe) array.at(i);
                for (int j = 0; j < tree.size(); j ++) {
                    processNode((HealthNode) tree.at(j), checkme);
                }

            }

        }

        public boolean processFrame(HealthNode healthnode, jgl.HashMap hashmap, CheckMe checkme) {
            java.lang.String as[] = com.dragonflow.Utils.TextUtils.split(checkme.property, ", ");
            java.util.LinkedList linkedlist = new LinkedList();
            for (int i = 0; i < as.length; i ++) {
                java.lang.String s1 = as[i];
                java.lang.String s2 = s1;
                java.lang.String s3 = "";
                if (s1.indexOf(".") > 0) {
                    s2 = new String(s1.substring(0, s1.indexOf(".")));
                    s3 = new String(s1.substring(s1.indexOf(".") + 1));
                }
                jgl.Array array2 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, s2);
                linkedlist.add(new CheckMePropInfo(s2, s3, array2));
            }

            java.lang.String s = checkme.operation;
            CheckMePropInfo checkmepropinfo = (CheckMePropInfo) linkedlist.get(0);
            jgl.Array array = checkmepropinfo.wholeValue;
            java.lang.String s4 = checkmepropinfo.mainProp;
            java.lang.String s5 = checkmepropinfo.subProp;
            jgl.Array array3 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "_id");
            java.lang.String s7 = getValue(array3, s5, 0);
            java.lang.String s8 = new String(expand(checkme.errorMessage, healthnode, hashmap));
            ErrorMessage errormessage = new ErrorMessage(s, s8, healthnode.fileName);
            if (s.equals("single")) {
                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", array.toString());
                return checkCondition(array.size() <= 1, errormessage);
            }
            if (s.equals("required") || s.equals("groupRequired") || s.equals("subGroupRequired") || s.equals("monitorRequired")) {
                boolean flag = true;
                try {
                    errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", array.toString());
                } catch (java.lang.Exception exception) {
                    com.dragonflow.Log.LogManager.log("Error", "exception eMsg.messageTemplate: " + errormessage.messageTemplate);
                    com.dragonflow.Log.LogManager.log("Error", "exception wholeValue: " + array.toString());
                    com.dragonflow.Utils.TextUtils.debugPrint("Exception: " + exception);
                    exception.printStackTrace();
                    com.dragonflow.Log.LogManager.log("Error", "FileBase.java is unhappy: " + com.dragonflow.Utils.FileUtils.stackTraceText(exception));
                }
                if (s5.length() <= 0) {
                    if (!checkCondition(getValue(array, s5, 0).length() > 0, errormessage)) {
                        flag = false;
                    }
                } else if (array.size() > 0) {
                    for (int k = 0; k < array.size(); k ++) {
                        errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", array.at(k).toString());
                        if (!checkCondition(getValue(array, s5, k).length() > 0, errormessage)) {
                            flag = false;
                        }
                    }

                    return flag;
                }
            } else {
                if (s.equals("number")) {
                    boolean flag1 = true;
                    for (int l = 0; l < array.size(); l ++) {
                        java.lang.String s12 = getValue(array, s5, l);
                        try {
                            java.lang.Integer.parseInt(s12);
                            continue;
                        } catch (java.lang.NumberFormatException numberformatexception1) {
                            errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", array.at(l).toString());
                        }
                        checkCondition(false, errormessage);
                        flag1 = false;
                    }

                    return flag1;
                }
                if (s.startsWith("set")) {
                    int j = s.indexOf("(") + 1;
                    int i1 = s.indexOf(")");
                    java.lang.String as1[] = com.dragonflow.Utils.TextUtils.split(s.substring(j, i1), "|");
                    boolean flag5 = false;
                    for (int l2 = 0; l2 < array.size(); l2 ++) {
                        java.lang.String s19 = getValue(array, s5, l2);
                        int k3 = 0;
                        k3 = 0;
                        do {
                            if (k3 >= as1.length) {
                                break;
                            }
                            if (s19.equals(as1[k3]) || s19.equals("")) {
                                flag5 = true;
                                break;
                            }
                            k3 ++;
                        } while (true);
                        errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s19);
                        checkCondition(flag5, errormessage);
                    }

                    return flag5;
                }
                if (s.startsWith("range")) {
                    jgl.Array array4 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "_class");
                    java.lang.String s11 = getValue(array4, s5, 0);
                    int i2 = s.indexOf("(") + 1;
                    int k2 = s.indexOf(")");
                    java.lang.String as2[] = com.dragonflow.Utils.TextUtils.split(s.substring(i2, k2), ",");
                    int j3 = 0;
                    int l3 = 0;
                    if (as2.length > 0) {
                        java.lang.String as3[] = com.dragonflow.Utils.TextUtils.split(as2[0], "-");
                        if (as3.length > 1) {
                            j3 = com.dragonflow.Utils.TextUtils.toInt(as3[0]);
                            l3 = com.dragonflow.Utils.TextUtils.toInt(as3[1]);
                        }
                    }
                    boolean flag8 = false;
                    boolean flag10 = true;
                    for (int l4 = 0; l4 < array.size(); l4 ++) {
                        java.lang.String s24 = getValue(array, s5, l4);
                        int i5 = com.dragonflow.Utils.TextUtils.toInt(s24);
                        if (s11.equals("PingMonitor") && s4.equals("_timeout")) {
                            i5 /= 1000;
                        }
                        boolean flag9 = false;
                        for (int j5 = 1; j5 < as2.length; j5 ++) {
                            if (i5 == com.dragonflow.Utils.TextUtils.toInt(as2[j5])) {
                                flag9 = true;
                            }
                        }

                        errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s24);
                        if (!checkCondition(j3 <= i5 && i5 <= l3 || flag9, errormessage)) {
                            flag10 = false;
                        }
                    }

                    return flag10;
                }
                if (!s.equals("monitorOrGroup")) {
                    if (s.equals("frequencyTimeout")) {
                        boolean flag2 = true;
                        try {
                            jgl.Array array5 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "_class");
                            java.lang.String s13 = getValue(array5, s5, 0);
                            jgl.Array array6 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, "_timeout");
                            java.lang.String s17 = getValue(array6, s5, 0);
                            java.lang.String s20 = getValue(array, s5, 0);
                            if (s17.length() > 0 && s20.length() > 0) {
                                int i4 = java.lang.Integer.parseInt(s17);
                                if (s13.equals("PingMonitor")) {
                                    i4 /= 1000;
                                }
                                int j4 = java.lang.Integer.parseInt(s20);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s20);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<timeout>", s17);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<group>", healthnode.fileName);
                                checkCondition(i4 < j4 || j4 == 0, errormessage);
                            }
                        } catch (java.lang.NumberFormatException numberformatexception) {
                            ErrorMessage errormessage1 = new ErrorMessage("frequencyTimeout", numberformatexception.toString(), healthnode.fileName);
                            checkCondition(false, errormessage1);
                            flag2 = false;
                        }
                        return flag2;
                    }
                    if (!s.equals("alert")) {
                        if (s.equals("groupParentChild")) {
                            if (healthnode.parent != null) {
                                java.lang.String s9 = getValue(array, s5, 0);
                                int j1 = healthnode.parent.fileName.lastIndexOf(".mg");
                                java.lang.String s14 = healthnode.parent.fileName.substring(0, j1);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s9);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<parentFileName>", s14);
                                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<group>", healthnode.fileName);
                                checkCondition(getAt(array, 0, "String").equals(s14), errormessage);
                            }
                        } else {
                            if (s.startsWith("nextId")) {
                                boolean flag3 = true;
                                if (array.size() <= 0) {
                                    return true;
                                }
                                int k1 = s.indexOf("(") + 1;
                                int j2 = s.indexOf(")");
                                java.lang.String s16 = s.substring(k1, j2);
                                java.lang.String s18 = "0";
                                jgl.HashMap hashmap1 = (jgl.HashMap) healthnode.frames.at(0);
                                boolean flag6 = false;
                                jgl.Array array7 = new Array();
                                if (healthnode.fileName.equals("history.config")) {
                                    array7 = com.dragonflow.Utils.TextUtils.getMultipleValues(masterConfig, s16);
                                    flag6 = true;
                                } else {
                                    array7 = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap1, s16);
                                }
                                if (array7.size() >= 1) {
                                    s18 = (java.lang.String) array7.at(0);
                                } else {
                                    java.lang.String s22 = "missing : '" + s16 + "' required" + (flag6 ? " in master.config " : " ") + "to compare with tag '" + s4 + "'" + (s5.trim().length() <= 0 ? "." : " and sub-tag '" + s5 + "'");
                                    ErrorMessage errormessage2 = new ErrorMessage("required", s22, healthnode.fileName);
                                    return checkCondition(false, errormessage2);
                                }
                                for (int k4 = 0; k4 < array.size(); k4 ++) {
                                    java.lang.String s23 = getValue(array, s5, k4);
                                    flag3 = checkIDlessthanNEXTID(s23, s18, errormessage);
                                }

                                return flag3;
                            }
                            if (s.equals("noDupValues")) {
                                java.util.HashSet hashset = new HashSet();
                                boolean flag4 = true;
                                for (java.util.Iterator iterator = linkedlist.iterator(); iterator.hasNext();) {
                                    CheckMePropInfo checkmepropinfo1 = (CheckMePropInfo) iterator.next();
                                    jgl.Array array1 = checkmepropinfo1.wholeValue;
                                    s4 = checkmepropinfo1.mainProp;
                                    java.lang.String s6 = checkmepropinfo1.subProp;
                                    int i3 = 0;
                                    while (i3 < array1.size()) {
                                        java.lang.String s21 = getValue(array1, s6, i3);
                                        boolean flag7 = hashset.contains(s21);
                                        if (!flag7) {
                                            hashset.add(s21);
                                        } else {
                                            errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s21);
                                            errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<property>", s4);
                                            checkCondition(false, errormessage);
                                            flag4 = false;
                                        }
                                        i3 ++;
                                    }
                                }

                                return flag4;
                            }
                            if (s.equals("circular")) {
                                java.util.Vector vector = new Vector();
                                int l1 = healthnode.fileName.lastIndexOf(".mg");
                                java.lang.String s15 = healthnode.fileName.substring(0, l1);
                                vector.add(s15 + " " + s7);
                                if (checkCircular(vector, s4)) {
                                    errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<tag>", s4);
                                    errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<value>", vector.toString());
                                    errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<group>", healthnode.fileName);
                                    checkCondition(false, errormessage);
                                    return false;
                                }
                            } else {
                                java.lang.String s10 = "Unknown MG, master.config or history.config file checking operation: '" + s + "': programmer may need to add this case to FileBase.processFrame()";
                                java.lang.Exception exception1 = new Exception(s10);
                                com.dragonflow.Utils.TextUtils.debugPrint(exception1.toString());
                                exception1.printStackTrace();
                                com.dragonflow.Log.LogManager.log("Error", com.dragonflow.Utils.FileUtils.stackTraceText(exception1));
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }

        /**
         * CAUTION: Decompiled by hand.
         * 
         * @param s
         * @param s1
         * @param errormessage
         * @return
         */
        private boolean checkIDlessthanNEXTID(java.lang.String s, java.lang.String s1, ErrorMessage errormessage) {
            if (s.length() <= 0) {
                return true;
            }

            try {
                int i;
                int j;
                i = java.lang.Integer.parseInt(s);
                j = java.lang.Integer.parseInt(s1);
                if (j < 0) {
                    return false;
                }
                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s);
                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<nextId>", s1);
                return checkCondition(i < j, errormessage);
            } catch (java.lang.NumberFormatException numberformatexception) {
                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.messageTemplate, "<value>", s);
                errormessage.message = com.dragonflow.Utils.TextUtils.replaceString(errormessage.message, "<nextId>", s1);
                checkCondition(false, errormessage);
                return false;
            }
        }

        public DoCheck() {
            super();
        }
    }

    private static class CheckMePropInfo {

        public java.lang.String subProp;

        public java.lang.String mainProp;

        public jgl.Array wholeValue;

        public CheckMePropInfo(java.lang.String s, java.lang.String s1, jgl.Array array) {
            mainProp = s;
            subProp = s1;
            wholeValue = array;
        }
    }

    protected static class CheckMe {

        public java.lang.String property;

        public java.lang.String operation;

        public java.lang.String errorMessage;

        public CheckMe(java.lang.String property, java.lang.String operation, java.lang.String errorMessage) {
            property = new String(property);
            operation = new String(operation);
            errorMessage = new String(errorMessage);
        }
    }

    public class ErrorMessage implements java.lang.Cloneable {

        public java.lang.String messageTemplate;

        public java.lang.String message;

        public java.lang.String type;

        public java.lang.String fileName;

        public java.lang.Object clone() {
            try {
                ErrorMessage errormessage;
                errormessage = (ErrorMessage) super.clone();
                errormessage.messageTemplate = new String(messageTemplate);
                errormessage.message = new String(message);
                errormessage.type = new String(type);
                errormessage.fileName = new String(fileName);
                return errormessage;
            } catch (java.lang.CloneNotSupportedException clonenotsupportedexception) {
                return null;
            }
        }

        public ErrorMessage(java.lang.String s, java.lang.String s1, java.lang.String s2) {
            super();
            messageTemplate = "";
            message = "";
            type = "";
            fileName = "";
            type = new String(s);
            messageTemplate = new String(s1);
            message = new String(s1);
            fileName = new String(s2);
        }
    }

    public class HealthNode {

        public int selfIndex;

        public HealthNode parent;

        public jgl.Array children;

        public java.lang.String fileName;

        public jgl.Array frames;

        public int parentFrameIndex;

        public boolean nodeOK;

        public HealthNode(HealthNode healthnode, int i, jgl.Array array, java.lang.String s) {
            super();
            parent = null;
            parent = healthnode;
            parentFrameIndex = i;
            fileName = new String(s);
            frames = new Array(array);
            children = new Array();
            if (parent != null) {
                selfIndex = parent.children.size();
                parent.children.add(this);
            } else {
                selfIndex = tree.size();
                tree.add(this);
            }
            int j = fileName.lastIndexOf(".mg");
            if (j > 0) {
                java.lang.String s1 = fileName.substring(0, j);
                monitorAndGroupNames.add(s1);
                jgl.HashMap hashmap = (jgl.HashMap) frames.at(0);
                if (!hashmap.isEmpty()) {
                    circularHm.put(s1, hashmap);
                }
            }
            nodeOK = true;
        }
    }

    int numberOfTimesThroughMGs;

    java.lang.String groupsLocation;

    jgl.Array errorLog;

    jgl.HashMap masterConfig;

    protected java.util.Vector monitorAndGroupNames;

    protected java.util.HashMap circularHm;

    public static boolean debug = false;

    protected jgl.Array tree;

    public abstract jgl.Array errorCheck();

    abstract java.lang.String getClassName();

    protected boolean hasNode(java.lang.String s) {
        for (int i = 0; i < tree.size(); i ++) {
            HealthNode healthnode = (HealthNode) tree.at(i);
            if (isNode(healthnode, s)) {
                return true;
            }
        }

        return false;
    }

    private boolean isNode(HealthNode healthnode, java.lang.String s) {
        if (healthnode.fileName.equals(s)) {
            return true;
        }
        for (int i = 0; i < healthnode.children.size(); i ++) {
            if (isNode((HealthNode) healthnode.children.at(i), s)) {
                return true;
            }
        }

        return false;
    }

    public boolean checkCondition(boolean flag, ErrorMessage errormessage) {
        if (!flag) {
            errorLog.add(errormessage.clone());
            if (debug) {
                com.dragonflow.Log.LogManager.log("Error", "FileBase.checkCondition() : " + errormessage.message);
                com.dragonflow.Log.LogManager.log("Error", "FileBase.checkCondition() : errorLog.size(): " + errorLog.size());
            }
        }
        return flag;
    }

    public FileBase() {
        numberOfTimesThroughMGs = 0;
        groupsLocation = "/groups/";
        errorLog = new Array();
        masterConfig = new HashMap();
        monitorAndGroupNames = new Vector();
        circularHm = new java.util.HashMap();
        tree = new Array();
        java.lang.String s = java.lang.System.getProperty("FileBase.debug");
        if (s != null) {
            debug = true;
            com.dragonflow.Log.LogManager.log("RunMonitor", "FileBase.debug= '" + debug + "'");
        }
        tree = new Array();
        monitorAndGroupNames = new Vector();
        circularHm = new java.util.HashMap();
        masterConfig = com.dragonflow.SiteView.MasterConfig.getMasterConfig();
    }

    public java.lang.Object getAt(jgl.Array array, int i, java.lang.String s) {
        if (array.size() > i) {
            return array.at(i);
        }
        if (s.equals("String")) {
            return "";
        }
        if (s.equals("jgl.HashMap")) {
            return new HashMap();
        } else {
            return "";
        }
    }

    private boolean checkCircular(java.util.Vector vector, java.lang.String s) {
        java.lang.String s1 = (java.lang.String) vector.lastElement();
        jgl.HashMap hashmap = (jgl.HashMap) circularHm.get(s1);
        if (hashmap == null) {
            vector.remove(s1);
            return false;
        }
        jgl.Array array = com.dragonflow.Utils.TextUtils.getMultipleValues(hashmap, s);
        if (debug) {
            com.dragonflow.Log.LogManager.log("Error", "###CIRCULAR FRAME DUMP - mainProp: " + s + " wholeValue: " + array.toString() + " currentFrame: " + hashmap);
        }
        if (array == null) {
            vector.remove(s1);
            return false;
        }
        for (int i = 0; i < array.size(); i ++) {
            java.lang.String s2 = (java.lang.String) array.at(i);
            if (debug) {
                com.dragonflow.Log.LogManager.log("Error", "###CIRCULAR FRAME DUMP - Find Monitor to check? dependent: " + s2 + " monitorAndGroupNames: " + monitorAndGroupNames.toString());
                if (s1.equals("MON_CompositeEbusMon_TwoOK 5")) {
                    java.lang.System.out.println("stop! well slow down anyway");
                }
            }
            if (!monitorAndGroupNames.contains(s2)) {
                java.lang.String s3 = "Group or Monitor: '" + s1 + "', did not find group or monitor that it depends on: '" + s2 + "'. It may have been deleted.";
                ErrorMessage errormessage = new ErrorMessage("MonitorNotFound", s3, s1);
                checkCondition(false, errormessage);
                vector.remove(s1);
                return false;
            }
            if (debug) {
                com.dragonflow.Log.LogManager.log("Error", "###CIRCULAR IS dependent: '" + s2 + "' in MONITORSSoFar : '" + vector.toString() + "'");
            }
            boolean flag = vector.contains(s2);
            if (!flag) {
                vector.add(s2);
                if (checkCircular(vector, s)) {
                    return true;
                }
            } else {
                return true;
            }
        }

        vector.remove(s1);
        return false;
    }

    public DoCheck getDoCheck() {
        return new DoCheck();
    }

    public HealthNode getHealthNode(HealthNode healthnode, int i, jgl.Array array, java.lang.String s) {
        return new HealthNode(healthnode, i, array, s);
    }

    public CheckMe getCheckMe(java.lang.String s, java.lang.String s1, java.lang.String s2) {
        return new CheckMe(s, s1, s2);
    }

}
