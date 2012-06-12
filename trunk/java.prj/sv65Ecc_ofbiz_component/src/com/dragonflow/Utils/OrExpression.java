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
// Expression, InterpreterException
public class OrExpression extends com.dragonflow.Utils.Expression {

    com.dragonflow.Utils.Expression left;

    com.dragonflow.Utils.Expression right;

    OrExpression(com.dragonflow.Utils.Expression expression, com.dragonflow.Utils.Expression expression1) {
        left = expression;
        right = expression1;
    }

    Object interpret(com.dragonflow.SiteView.SiteViewObject siteviewobject, com.dragonflow.SiteView.Rule rule) throws com.dragonflow.Utils.InterpreterException {
        Boolean boolean1 = (Boolean) left.interpret(siteviewobject, rule);
        Boolean boolean2 = (Boolean) right.interpret(siteviewobject, rule);
        if (!boolean1.booleanValue() && !boolean2.booleanValue()) {
            return new Boolean(false);
        } else {
            return new Boolean(true);
        }
    }

    public String toString(com.dragonflow.SiteView.SiteViewObject siteviewobject) {
        return left.toString(siteviewobject) + " OR " + right.toString(siteviewobject);
    }
}
