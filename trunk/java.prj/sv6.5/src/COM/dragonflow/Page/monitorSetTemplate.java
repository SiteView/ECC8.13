/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package COM.dragonflow.Page;

import jgl.Array;
import jgl.HashMap;

// Referenced classes of package COM.dragonflow.Page:
// monitorSetPage

public class monitorSetTemplate {

    public static java.lang.String fileSuffix = "mset";

    static java.lang.String templateVar = "$";

    static final java.lang.String templateName = "_monitorTemplateName";

    static final java.lang.String templateDescription = "_monitorTemplateDescription";

    public static final java.lang.String FOREACH = "FOREACH";

    public static final java.util.regex.Pattern FOREACH_PATTERN = java.util.regex.Pattern
            .compile(".*\\@(\\w+)\\{(\\w+)\\}.*");

    public static final int FOREACH_NAME_GRP = 1;

    public static final int FOREACH_INDEX_GRP = 2;

    static final java.lang.String TRUNCATE_PROP = "_truncateProperty";

    static final java.lang.String TRUNCATE_PATTERN = "_truncatePattern";

    static final java.lang.String TRUNCATE_LENGTH = "_truncateWhenLongerThan";

    java.lang.String m_templateFile;

    private jgl.Array m_frames;

    private jgl.HashMap m_varTbl;

    private jgl.HashMap m_foreachVarTbl;

    private jgl.HashMap m_whereVarUsed;

    private jgl.HashMap m_replacementList;

    private java.lang.String truncatePropertyName;

    private java.util.regex.Pattern truncatePattern;

    private int truncateLength;

    public monitorSetTemplate(java.lang.String s) {
        m_templateFile = s;
        try {
            m_frames = COM.dragonflow.Properties.FrameFile.readFromFile(s);
        } catch (java.lang.Exception exception) {
            java.lang.System.out.println("Error reading set template:"
                    + exception);
        }
        if (m_frames != null) {
            getTruncateVariables(s);
        }
    }

    private void getTruncateVariables(java.lang.String s) {
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(0);
        java.lang.String s1 = (java.lang.String) hashmap
                .get("_truncateWhenLongerThan");
        java.lang.String s2 = (java.lang.String) hashmap
                .get("_truncatePattern");
        java.lang.String s3 = (java.lang.String) hashmap
                .get("_truncateProperty");
        if (s1 != null && s2 != null && s3 != null) {
            try {
                truncateLength = java.lang.Integer.parseInt(s1);
            } catch (java.lang.NumberFormatException numberformatexception) {
                COM.dragonflow.Log.LogManager.log("Error",
                        "Couldn't parse _truncateWhenLongerThan from template file "
                                + s);
                setTruncateDefaults();
                return;
            }
            truncatePattern = java.util.regex.Pattern.compile(s2);
            truncatePropertyName = s3;
        } else {
            setTruncateDefaults();
        }
    }

    private void setTruncateDefaults() {
        truncateLength = -1;
        truncatePattern = null;
        truncatePropertyName = "";
    }

    monitorSetTemplate(jgl.Array array) {
        m_frames = array;
    }

    /**
     * CAUTION: Decompiled by hand.
     *
     */
    private void parseTemplate() {
        m_varTbl = new HashMap();
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(0);
        java.util.Enumeration enumeration = hashmap.keys();
        while (enumeration.hasMoreElements()) {
            java.lang.String s = (java.lang.String) enumeration.nextElement();
            java.lang.String s1 = (java.lang.String) hashmap.get(s);
            if (s.startsWith(templateVar) && s.endsWith(templateVar)) {
                jgl.HashMap hashmap2 = COM.dragonflow.Utils.TextUtils
                        .stringToHashMap(s1);
                m_varTbl.add(s, hashmap2);
            }
        } 
        
        m_whereVarUsed = new HashMap();
        for (int i = 1; i < m_frames.size(); i ++) {
            jgl.HashMap hashmap1 = (jgl.HashMap) m_frames.at(i);
            java.util.Enumeration enumeration1 = hashmap1.keys();
            java.lang.String s2 = (java.lang.String) hashmap1.get("_class");
            while (enumeration1.hasMoreElements()) {
                java.lang.String s3 = (java.lang.String) enumeration1
                        .nextElement();
                java.lang.Object obj = hashmap1.get(s3);
                if (obj instanceof java.lang.String) {
                    java.lang.String s4 = (java.lang.String) obj;
                    java.util.Enumeration enumeration2 = m_varTbl.keys();
                    while (enumeration2.hasMoreElements()) {
                        java.lang.String s5 = (java.lang.String) enumeration2
                                .nextElement();
                        if (s4.indexOf(s5) > -1) {
                            if (m_whereVarUsed.get(s5) == null) {
                                m_whereVarUsed.add(s5, new HashMap());
                            }
                            jgl.HashMap hashmap3 = (jgl.HashMap) m_whereVarUsed
                                    .get(s5);
                            hashmap3.add(s2, "");
                        }
                    }
                }
            }
        } 
    }

    public int getMonitorCount() {
        return m_frames.size() - 1;
    }

    public jgl.HashMap getNthMonitor(int i) {
        return (jgl.HashMap) m_frames.at(i + 1);
    }

    java.lang.String verifyNthMonitor(int i) {
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(i + 1);
        if (COM.dragonflow.Utils.TextUtils.getValue(hashmap, "_class").length() == 0) {
            return "_class missing from #" + (i + 1)
                    + " monitor in this template";
        } else {
            return "";
        }
    }

    public java.lang.String getName() {
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(0);
        java.lang.String s = COM.dragonflow.Utils.TextUtils.getValue(hashmap,
                "_monitorTemplateName");
        return s;
    }

    public java.lang.String getSetting(java.lang.String s) {
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(0);
        return COM.dragonflow.Utils.TextUtils.getValue(hashmap, s);
    }

    public java.lang.String getSetDescriptor() {
        jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(0);
        java.lang.String s = COM.dragonflow.Utils.TextUtils.getValue(hashmap,
                "_monitorTemplateDescription");
        return s;
    }

    public java.lang.String[] getVariables() {
        if (m_varTbl == null) {
            parseTemplate();
        }
        java.lang.String as[] = new java.lang.String[m_varTbl.size()];
        java.util.Enumeration enumeration = m_varTbl.keys();
        for (int i = 0; enumeration.hasMoreElements(); i++) {
            as[i] = (java.lang.String) enumeration.nextElement();
        }

        return as;
    }

    jgl.HashMap getVariableInfo(java.lang.String s) {
        if (m_varTbl == null) {
            parseTemplate();
        }
        jgl.HashMap hashmap = (jgl.HashMap) m_varTbl.get(s);
        return hashmap;
    }

    java.lang.String[] getWhereUsed(java.lang.String s) {
        if (m_whereVarUsed == null) {
            parseTemplate();
        }
        java.lang.String as[] = null;
        jgl.HashMap hashmap = (jgl.HashMap) m_whereVarUsed.get(s);
        if (hashmap != null) {
            as = new java.lang.String[hashmap.size()];
            java.util.Enumeration enumeration = hashmap.keys();
            for (int i = 0; enumeration.hasMoreElements(); i++) {
                as[i] = (java.lang.String) enumeration.nextElement();
            }

        }
        return as;
    }

    public void replaceVariable(java.lang.String s, java.lang.String s1) {
        label0: for (int i = 0; i < m_frames.size(); i++) {
            jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(i);
            java.util.Enumeration enumeration = hashmap.keys();
            do {
                if (!enumeration.hasMoreElements()) {
                    continue label0;
                }
                java.lang.String s2 = (java.lang.String) enumeration
                        .nextElement();
                java.lang.Object obj = hashmap.get(s2);
                boolean flag = false;
                if (obj instanceof java.lang.String) {
                    java.lang.String s3 = (java.lang.String) obj;
                    java.lang.String s4 = COM.dragonflow.Utils.TextUtils
                            .replaceString(s3, s, s1);
                    if (s.equals("$server$") || s.equals("$host$")) {
                        if (s1.toString().matches("remote:\\d+")) {
                            java.lang.String s5 = COM.dragonflow.SiteView.Machine
                                    .getMachineName(s1);
                            s4 = COM.dragonflow.Utils.TextUtils.replaceString(
                                    s4, "$serverName$", s5);
                        } else {
                            s4 = COM.dragonflow.Utils.TextUtils.replaceString(
                                    s4, "$serverName$", s1);
                        }
                    }
                    if (!s4.equals(s3)) {
                        flag = true;
                        s4 = reCalculateCounterIdLengthPrefixIfNecessary(s2, s4);
                    }
                    hashmap.put(s2, s4);
                } else if (obj instanceof jgl.Array) {
                    int j = ((jgl.Array) obj).size();
                    for (int k = 0; k < j; k++) {
                        java.lang.String s6 = (java.lang.String) ((jgl.Array) obj)
                                .at(k);
                        java.lang.String s7 = COM.dragonflow.Utils.TextUtils
                                .replaceString(s6, s, s1);
                        if (s.equals("$server$") || s.equals("$host$")) {
                            if (s1.toString().matches("remote:\\d+")) {
                                java.lang.String s8 = COM.dragonflow.SiteView.Machine
                                        .getMachineName(s1);
                                s7 = COM.dragonflow.Utils.TextUtils
                                        .replaceString(s7, "$serverName$", s8);
                            } else {
                                s7 = COM.dragonflow.Utils.TextUtils
                                        .replaceString(s7, "$serverName$", s1);
                            }
                        }
                        ((jgl.Array) obj).put(k, s7);
                        if (!s7.equals(s6)) {
                            flag = true;
                        }
                    }

                } else {
                    java.lang.System.out.println("key = " + s2
                            + " is not a String or jgl.Array");
                }
                if (flag) {
                    addReplacementList(i, s2);
                }
            } while (true);
        }

    }

    private java.lang.String reCalculateCounterIdLengthPrefixIfNecessary(
            java.lang.String s, java.lang.String s1) {
        if (s
                .indexOf(COM.dragonflow.SiteView.BrowsableBase.PROPERTY_NAME_COUNTER_ID) < 0) {
            return s1;
        }
        if (s1.matches("^\\d+ .*")) {
            int i = s1.indexOf(' ') + 1;
            if (i > 0) {
                java.lang.String s2 = s1.substring(i);
                return s2.length() + " " + s2;
            }
        }
        return s1;
    }

    void addReplacementList(int i, java.lang.String s) {
        if (m_replacementList == null) {
            m_replacementList = new HashMap();
        }
        java.lang.String s1 = java.lang.String.valueOf(i);
        if (m_replacementList.get(s1) == null) {
            m_replacementList.add(s1, new HashMap());
        }
        jgl.HashMap hashmap = (jgl.HashMap) m_replacementList.get(s1);
        if (hashmap.get(s) == null) {
            hashmap.add(s, "");
        }
    }

    public boolean didReplacement(int i, java.lang.String s) {
        i++;
        if (m_replacementList != null) {
            java.lang.String s1 = java.lang.String.valueOf(i);
            jgl.HashMap hashmap = (jgl.HashMap) m_replacementList.get(s1);
            if (hashmap != null && hashmap.get(s) != null) {
                return true;
            }
        }
        return false;
    }

    public void doForeachSubstitution() {
        jgl.Array array = new Array();
        int i = 1;
        array.add(m_frames.at(0));
        for (int j = 1; j < m_frames.size(); j++) {
            jgl.HashMap hashmap = (jgl.HashMap) m_frames.at(j);
            if (hashmap.get("FOREACH") != null) {
                java.lang.String s = (java.lang.String) hashmap.get("FOREACH");
                jgl.HashMap hashmap1;
                for (java.util.Enumeration enumeration = m_foreachVarTbl
                        .values(s); enumeration.hasMoreElements(); array
                        .add(replaceAllForeachVariablesInFrame(s, hashmap1,
                                hashmap, i++))) {
                    hashmap1 = (jgl.HashMap) enumeration.nextElement();
                }

            } else {
                array.add(hashmap);
            }
        }

        m_frames = array;
    }

    private jgl.HashMap replaceAllForeachVariablesInFrame(java.lang.String s,
            jgl.HashMap hashmap, jgl.HashMap hashmap1, int i) {
        jgl.HashMap hashmap2 = new HashMap();
        java.util.Enumeration enumeration = hashmap1.keys();
        label0: do {
            if (enumeration.hasMoreElements()) {
                java.lang.String s1 = (java.lang.String) enumeration
                        .nextElement();
                java.lang.String s2 = new String((java.lang.String) hashmap1
                        .get(s1));
                java.util.Enumeration enumeration1 = hashmap.keys();
                do {
                    if (!enumeration1.hasMoreElements()) {
                        continue label0;
                    }
                    java.lang.String s3 = (java.lang.String) enumeration1
                            .nextElement();
                    java.lang.String s4 = "@" + s + "{" + s3 + "}";
                    if (s2.indexOf(s4) > -1) {
                        java.lang.String s5 = escapeBrackets(s4);
                        java.lang.String s6 = (java.lang.String) hashmap
                                .get(s3);
                        if (s3.equals("name")) {
                            hashmap2.put(s1, s2.replaceAll(s5,
                                    removeNamePrefix(s6, s1)));
                        } else {
                            hashmap2.put(s1, s2.replaceAll(s5, s6));
                        }
                        addReplacementList(i, s1);
                        continue label0;
                    }
                    hashmap2.put(s1, s2);
                } while (true);
            }
            return hashmap2;
        } while (true);
    }

    private java.lang.String removeNamePrefix(java.lang.String s,
            java.lang.String s1) {
        java.lang.String s2 = "";
        java.util.regex.Matcher matcher = COM.dragonflow.Page.monitorSetPage.FOREACH_VARNAME_PATTERN
                .matcher(s);
        if (matcher.matches()) {
            int i = s.indexOf(':');
            if (i++ < s.length()) {
                s2 = s.substring(i + 1);
            }
        }
        if (truncateLength > 0) {
            s2 = truncateVariableIfNecessary(s1, s2);
        }
        return s2;
    }

    private java.lang.String truncateVariableIfNecessary(java.lang.String s,
            java.lang.String s1) {
        if (truncateLength > 0 && truncatePattern != null
                && truncatePropertyName != null
                && s.equals(truncatePropertyName)
                && s1.length() > truncateLength) {
            java.util.regex.Matcher matcher = truncatePattern.matcher(s1);
            if (matcher.matches()) {
                if (matcher.groupCount() >= 1) {
                    s1 = matcher.group(1);
                } else {
                    s1 = matcher.group(0);
                }
            }
        }
        return s1;
    }

    public void replaceAllVariables(jgl.HashMap hashmap, jgl.HashMap hashmap1) {
        if (hashmap1 != null) {
            m_foreachVarTbl = hashmap1;
            doForeachSubstitution();
        }
        java.lang.String s;
        java.lang.String s1;
        for (java.util.Enumeration enumeration = hashmap.keys(); enumeration
                .hasMoreElements(); replaceVariable(s, s1)) {
            s = (java.lang.String) enumeration.nextElement();
            s1 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s);
            jgl.HashMap hashmap2 = getVariableInfo(s);
            if (hashmap2.get("_boolean") == null) {
                continue;
            }
            if (s1.length() > 0) {
                s1 = (java.lang.String) hashmap2.get("_onTrue");
            } else {
                s1 = (java.lang.String) hashmap2.get("_onFalse");
            }
            s = "BOOLEAN[" + s + "]";
        }

    }

    private java.lang.String escapeBrackets(java.lang.String s) {
        java.lang.String s1 = s.replaceAll("\\{", "\\\\{");
        s1 = s1.replaceAll("\\}", "\\\\}");
        return s1;
    }

}
