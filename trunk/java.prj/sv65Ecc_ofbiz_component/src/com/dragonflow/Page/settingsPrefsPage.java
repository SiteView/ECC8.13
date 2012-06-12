/*
 * 
 * Created on 2005-3-9 22:12:36
 *
 * .java
 *
 * History:
 *
 */
package com.dragonflow.Page;

import jgl.Array;

// Referenced classes of package com.dragonflow.Page:
// prefsPage

public class settingsPrefsPage extends com.dragonflow.Page.prefsPage {

    public settingsPrefsPage() {
    }

    public String saveAdditionalPrefs(String s,
            String s1, jgl.HashMap hashmap) {
        String s2 = "_nextAdditional" + s + "ID";
        String s3 = "_additional" + s;
        try {
            jgl.HashMap hashmap1 = getSettings();
            if (s1.startsWith("new")) {
                s1 = (String) hashmap1.get(s2);
                if (s1 == null) {
                    s1 = "1";
                }
                hashmap1.put(s2, com.dragonflow.Utils.TextUtils.increment(s1));
            }
            hashmap.put("_id", s1);
            jgl.Array array = new Array();
            boolean flag = false;
            for (java.util.Enumeration enumeration = com.dragonflow.Page.settingsPrefsPage
                    .getValues(hashmap1, s3); enumeration.hasMoreElements();) {
                jgl.HashMap hashmap2 = com.dragonflow.Utils.TextUtils
                        .stringToHashMap((String) enumeration
                                .nextElement());
                if (com.dragonflow.Page.settingsPrefsPage.getValue(hashmap2,
                        "_id").equals(s1)) {
                    array.add(hashmap);
                    flag = true;
                } else {
                    array.add(hashmap2);
                }
            }

            if (!flag) {
                array.add(hashmap);
            }
            hashmap1.remove(s3);
            for (int i = 0; i < array.size(); i++) {
                hashmap1.add(s3, com.dragonflow.Utils.TextUtils
                        .hashMapToOrderedString((jgl.HashMap) array.at(i)));
            }

            saveSettings(hashmap1);
        } catch (Exception ioexception) {
            printError("The preferences could not be saved",
                    "master.config file could not be saved", "10");
        }
        return s1;
    }

    /**
     * CAUTION: Decompiled by hand.
     * 
     * @param s
     * @param hashmap
     * @return
     */
    public jgl.HashMap findAdditionalSetting(String s, jgl.HashMap hashmap) {

        jgl.HashMap hashmap1 = getSettings();
        String s1 = "_additional" + s;
        java.util.Enumeration enumeration = com.dragonflow.Page.settingsPrefsPage.getValues(hashmap1, s1);
        jgl.HashMap hashmap2;
        boolean flag;
        while (enumeration.hasMoreElements()) {
            hashmap2 = com.dragonflow.Utils.TextUtils.stringToHashMap((String) enumeration.nextElement());
            java.util.Enumeration enumeration1 = hashmap.keys();
            flag = true;
            String s2;
            while (enumeration1.hasMoreElements()) {
                s2 = (String) enumeration1.nextElement();
                if (!com.dragonflow.Page.settingsPrefsPage.getValue(hashmap, s2).equals(com.dragonflow.Page.settingsPrefsPage.getValue(hashmap2, s2))) {
                    flag = false;
                }
                if (flag && com.dragonflow.Page.settingsPrefsPage.getValue(hashmap2, "_disabled").length() == 0) {
                    return hashmap2;
                }
            }
        }

        return null;
    }

    public void deleteAdditionalSetting(String s, String s1) {
        String s2 = "_additional" + s;
        jgl.HashMap hashmap = getSettings();
        jgl.Array array = new Array();
        java.util.Enumeration enumeration = com.dragonflow.Page.settingsPrefsPage
                .getValues(hashmap, s2);
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap1 = com.dragonflow.Utils.TextUtils
                    .stringToHashMap((String) enumeration
                            .nextElement());
            if (!com.dragonflow.Page.settingsPrefsPage.getValue(hashmap1, "_id")
                    .equals(s1)) {
                array.add(hashmap1);
            }
        } 
        
        hashmap.remove(s2);
        for (int i = 0; i < array.size(); i++) {
            hashmap.add(s2, com.dragonflow.Utils.TextUtils
                    .hashMapToOrderedString((jgl.HashMap) array.at(i)));
        }

        try {
            saveSettings(hashmap);
        } catch (Exception ioexception) {
            printError("The preferences could not be saved",
                    "master.config file could not be saved", "10");
        }
    }

    public jgl.HashMap getAdditionalSettings(String s, String s1) {
        jgl.HashMap hashmap = null;
        if (s1.length() > 0) {
            String s2 = getSettingsGroup().getAdditionalSettings(s,
                    s1);
            if (s2.length() > 0) {
                hashmap = com.dragonflow.Utils.TextUtils.stringToHashMap(s2);
            }
        }
        return hashmap;
    }
}
