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

// Referenced classes of package COM.dragonflow.Utils:
// Literal, InterpreterException, TextUtils
public class NumericLiteral extends COM.dragonflow.Utils.Literal {

    float value;

    NumericLiteral(float f) {
        value = f;
    }

    java.lang.Object interpret(COM.dragonflow.SiteView.SiteViewObject siteviewobject, COM.dragonflow.SiteView.Rule rule) throws COM.dragonflow.Utils.InterpreterException {
        return new Float(value);
    }

    public java.lang.String toString(COM.dragonflow.SiteView.SiteViewObject siteviewobject) {
        return COM.dragonflow.Utils.TextUtils.floatToString(value, 0);
    }
}
