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

// Referenced classes of package com.dragonflow.Utils:
// Literal
public class PropertyNameLiteral extends com.dragonflow.Utils.Literal {

    java.lang.String propertySpec;

    PropertyNameLiteral(java.lang.String s) {
        propertySpec = s;
    }

    java.lang.Object interpret(com.dragonflow.SiteView.SiteViewObject siteviewobject, com.dragonflow.SiteView.Rule rule) {
        java.lang.String s = propertySpec;
        int i = s.indexOf(".");
        if (i >= 0) {
            java.lang.String s1 = s.substring(0, i);
            s = s.substring(i + 1);
            com.dragonflow.SiteView.SiteViewObject siteviewobject1 = siteviewobject.resolveObjectReference(s1);
            if (siteviewobject1 != null) {
                siteviewobject = siteviewobject1;
            }
        }
        if (siteviewobject.hasProperty(s)) {
            java.lang.String s2 = siteviewobject.getProperty(s);
            return s2;
        }
        java.lang.String s3 = siteviewobject.getProperty(s);
        if (s3.length() > 0) {
            return s3;
        }
        if (rule != null) {
            java.lang.String s4 = siteviewobject.getProperty(s + rule.getFullID());
            if (s4.length() > 0) {
                return s4;
            }
        }
        return s;
    }

    public java.lang.String getPropertyName() {
        return propertySpec;
    }

    public java.lang.String toString(com.dragonflow.SiteView.SiteViewObject siteviewobject) {
        java.lang.String s = siteviewobject.getProperty(propertySpec);
        if (s == "") {
            return propertySpec;
        } else {
            return propertySpec + "(value: " + s + ")";
        }
    }
}
