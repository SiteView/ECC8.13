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
// Literal, InterpreterException
public class StringLiteral extends com.dragonflow.Utils.Literal {

    String string;

    StringLiteral(String s) {
        string = s;
    }

    Object interpret(com.dragonflow.SiteView.SiteViewObject siteviewobject, com.dragonflow.SiteView.Rule rule) throws com.dragonflow.Utils.InterpreterException {
        return string;
    }

    public String toString(com.dragonflow.SiteView.SiteViewObject siteviewobject) {
        return string;
    }
}