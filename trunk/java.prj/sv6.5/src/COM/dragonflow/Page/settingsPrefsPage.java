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

// Referenced classes of package COM.dragonflow.Page:
// prefsPage

public class settingsPrefsPage extends COM.dragonflow.Page.prefsPage {

    public settingsPrefsPage() {
    }

    public java.lang.String saveAdditionalPrefs(java.lang.String s,
            java.lang.String s1, jgl.HashMap hashmap) {
        java.lang.String s2 = "_nextAdditional" + s + "ID";
        java.lang.String s3 = "_additional" + s;
        try {
            jgl.HashMap hashmap1 = getSettings();
            if (s1.startsWith("new")) {
                s1 = (java.lang.String) hashmap1.get(s2);
                if (s1 == null) {
                    s1 = "1";
                }
                hashmap1.put(s2, COM.dragonflow.Utils.TextUtils.increment(s1));
            }
            hashmap.put("_id", s1);
            jgl.Array array = new Array();
            boolean flag = false;
            for (java.util.Enumeration enumeration = COM.dragonflow.Page.settingsPrefsPage
                    .getValues(hashmap1, s3); enumeration.hasMoreElements();) {
                jgl.HashMap hashmap2 = COM.dragonflow.Utils.TextUtils
                        .stringToHashMap((java.lang.String) enumeration
                                .nextElement());
                if (COM.dragonflow.Page.settingsPrefsPage.getValue(hashmap2,
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
                hashmap1.add(s3, COM.dragonflow.Utils.TextUtils
                        .hashMapToOrderedString((jgl.HashMap) array.at(i)));
            }

            saveSettings(hashmap1);
        } catch (java.io.IOException ioexception) {
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
    public jgl.HashMap findAdditionalSetting(java.lang.String s, jgl.HashMap hashmap) {

        jgl.HashMap hashmap1 = getSettings();
        java.lang.String s1 = "_additional" + s;
        java.util.Enumeration enumeration = COM.dragonflow.Page.settingsPrefsPage.getValues(hashmap1, s1);
        jgl.HashMap hashmap2;
        boolean flag;
        while (enumeration.hasMoreElements()) {
            hashmap2 = COM.dragonflow.Utils.TextUtils.stringToHashMap((java.lang.String) enumeration.nextElement());
            java.util.Enumeration enumeration1 = hashmap.keys();
            flag = true;
            java.lang.String s2;
            while (enumeration1.hasMoreElements()) {
                s2 = (java.lang.String) enumeration1.nextElement();
                if (!COM.dragonflow.Page.settingsPrefsPage.getValue(hashmap, s2).equals(COM.dragonflow.Page.settingsPrefsPage.getValue(hashmap2, s2))) {
                    flag = false;
                }
                if (flag && COM.dragonflow.Page.settingsPrefsPage.getValue(hashmap2, "_disabled").length() == 0) {
                    return hashmap2;
                }
            }
        }

        return null;
    }

    public void deleteAdditionalSetting(java.lang.String s, java.lang.String s1) {
        java.lang.String s2 = "_additional" + s;
        jgl.HashMap hashmap = getSettings();
        jgl.Array array = new Array();
        java.util.Enumeration enumeration = COM.dragonflow.Page.settingsPrefsPage
                .getValues(hashmap, s2);
        while (enumeration.hasMoreElements()) {
            jgl.HashMap hashmap1 = COM.dragonflow.Utils.TextUtils
                    .stringToHashMap((java.lang.String) enumeration
                            .nextElement());
            if (!COM.dragonflow.Page.settingsPrefsPage.getValue(hashmap1, "_id")
                    .equals(s1)) {
                array.add(hashmap1);
            }
        } 
        
        hashmap.remove(s2);
        for (int i = 0; i < array.size(); i++) {
            hashmap.add(s2, COM.dragonflow.Utils.TextUtils
                    .hashMapToOrderedString((jgl.HashMap) array.at(i)));
        }

        try {
            saveSettings(hashmap);
        } catch (java.io.IOException ioexception) {
            printError("The preferences could not be saved",
                    "master.config file could not be saved", "10");
        }
    }

    jgl.HashMap getAdditionalSettings(java.lang.String s, java.lang.String s1) {
        jgl.HashMap hashmap = null;
        if (s1.length() > 0) {
            java.lang.String s2 = getSettingsGroup().getAdditionalSettings(s,
                    s1);
            if (s2.length() > 0) {
                hashmap = COM.dragonflow.Utils.TextUtils.stringToHashMap(s2);
            }
        }
        return hashmap;
    }
}
