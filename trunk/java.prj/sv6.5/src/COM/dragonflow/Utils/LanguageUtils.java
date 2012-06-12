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

import jgl.HashMap;

// Referenced classes of package COM.dragonflow.Utils:
// TextUtils

public class LanguageUtils {

    static jgl.HashMap languageCache = new HashMap();

    public LanguageUtils() {
    }

    static jgl.HashMap getLanguage(java.lang.String s) {
        jgl.HashMap hashmap = (jgl.HashMap) languageCache.get(s);
        if (hashmap == null) {
            try {
                jgl.Array array = COM.dragonflow.Properties.FrameFile.readFromFile(COM.dragonflow.SiteView.Platform.getRoot() + java.io.File.separator + "templates.language" + java.io.File.separator + s + ".txt");
                hashmap = (jgl.HashMap) array.front();
                languageCache.put(s, hashmap);
            } catch (java.lang.Exception exception) {
            }
        }
        return hashmap;
    }

    public static java.lang.String getString(java.lang.String s, java.lang.String s1) {
        jgl.HashMap hashmap = COM.dragonflow.Utils.LanguageUtils.getLanguage(s1);
        java.lang.String s2;
        if (hashmap == null) {
            s2 = "(error: missing language for " + s1 + ".txt)";
        } else {
            s2 = COM.dragonflow.Utils.TextUtils.getValue(hashmap, s);
            if (s2.length() == 0) {
                s2 = "(error: missing string for " + s + ")";
            }
        }
        return s2;
    }

}
