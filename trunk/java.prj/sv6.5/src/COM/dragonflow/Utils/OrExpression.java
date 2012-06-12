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
// Expression, InterpreterException
public class OrExpression extends COM.dragonflow.Utils.Expression {

    COM.dragonflow.Utils.Expression left;

    COM.dragonflow.Utils.Expression right;

    OrExpression(COM.dragonflow.Utils.Expression expression, COM.dragonflow.Utils.Expression expression1) {
        left = expression;
        right = expression1;
    }

    java.lang.Object interpret(COM.dragonflow.SiteView.SiteViewObject siteviewobject, COM.dragonflow.SiteView.Rule rule) throws COM.dragonflow.Utils.InterpreterException {
        java.lang.Boolean boolean1 = (java.lang.Boolean) left.interpret(siteviewobject, rule);
        java.lang.Boolean boolean2 = (java.lang.Boolean) right.interpret(siteviewobject, rule);
        if (!boolean1.booleanValue() && !boolean2.booleanValue()) {
            return new Boolean(false);
        } else {
            return new Boolean(true);
        }
    }

    public java.lang.String toString(COM.dragonflow.SiteView.SiteViewObject siteviewobject) {
        return left.toString(siteviewobject) + " OR " + right.toString(siteviewobject);
    }
}
